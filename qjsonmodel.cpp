

#include "qjsonmodel.h"
#include <QFile>
#include <QDebug>
#include <QFont>

Summary* QJsonTreeItem::summary = new Summary();

QJsonTreeItem::QJsonTreeItem(QJsonTreeItem* parent)
{
	mParent = parent;
}

QJsonTreeItem::~QJsonTreeItem()
{
	qDeleteAll(mChilds);
}

void QJsonTreeItem::appendChild(QJsonTreeItem* item)
{
	mChilds.append(item);
}

QJsonTreeItem* QJsonTreeItem::child(int row)
{
	return mChilds.value(row);
}

QJsonTreeItem* QJsonTreeItem::parent()
{
	return mParent;
}

int QJsonTreeItem::childCount() const
{
	return mChilds.count();
}

int QJsonTreeItem::row() const
{
	if (mParent)
		return mParent->mChilds.indexOf(const_cast<QJsonTreeItem*>(this));

	return 0;
}

void QJsonTreeItem::setKey(const QString& key)
{
	mKey = key;
}

void QJsonTreeItem::setValue(const QVariant& value)
{
	mValue = value;
}

void QJsonTreeItem::setType(const QJsonValue::Type& type)
{
	mType = type;
}

QString QJsonTreeItem::key() const
{
	return mKey;
}

QVariant QJsonTreeItem::value() const
{
	return mValue;
}

QJsonValue::Type QJsonTreeItem::type() const
{
	return mType;
}

QJsonTreeItem* QJsonTreeItem::load(const QJsonValue& value, QJsonTreeItem* parent)
{
	QJsonTreeItem* rootItem = new QJsonTreeItem(parent);
	rootItem->setKey("root");

	if (value.isObject())
	{
		//Get all QJsonValue childs
		for (QString key : value.toObject().keys()) {
			QJsonValue v = value.toObject().value(key);
			QJsonTreeItem* child = load(v, rootItem);
			child->setKey(key);
			child->setType(v.type());
			rootItem->appendChild(child);
		}
		summary->setObjectCount(summary->getObjectCount() + 1);
	}

	else if (value.isArray())
	{
		//Get all QJsonValue childs
		int index = 0;
		for (QJsonValue v : value.toArray()) {

			QJsonTreeItem* child = load(v, rootItem);
			child->setKey(QString::number(index));
			child->setType(v.type());
			rootItem->appendChild(child);
			++index;
		}
		summary->setArrayCount(summary->getArrayCount() + 1);
	}
	else
	{
		rootItem->setValue(value.toVariant());
		rootItem->setType(value.type());

		if (value.type() == QJsonValue::Type::Bool) summary->setBooleanCount(summary->getBooleanCount()+1);
		else if (value.type() == QJsonValue::Type::Double) summary->setNumberCount(summary->getNumberCount() + 1);
		else if (value.type() == QJsonValue::Type::Null) summary->setNullCount(summary->getNullCount() + 1);
		else if (value.type() == QJsonValue::Type::String) summary->setStringCount(summary->getStringCount() + 1);
	}

	return rootItem;
}

//=========================================================================

inline uchar hexdig(uint u)
{
	return (u < 0xa ? '0' + u : 'a' + u - 0xa);
}

QByteArray escapedString(const QString& s)
{
	QByteArray ba(s.length(), Qt::Uninitialized);
	uchar* cursor = reinterpret_cast<uchar*>(const_cast<char*>(ba.constData()));
	const uchar* ba_end = cursor + ba.length();
	const ushort* src = reinterpret_cast<const ushort*>(s.constBegin());
	const ushort* const end = reinterpret_cast<const ushort*>(s.constEnd());
	while (src != end)
	{
		if (cursor >= ba_end - 6)
		{
			// ensure we have enough space
			int pos = cursor - (const uchar*)ba.constData();
			ba.resize(ba.size() * 2);
			cursor = (uchar*)ba.data() + pos;
			ba_end = (const uchar*)ba.constData() + ba.length();
		}
		uint u = *src++;
		if (u < 0x80)
		{
			if (u < 0x20 || u == 0x22 || u == 0x5c)
			{
				*cursor++ = '\\';
				switch (u)
				{
				case 0x22:
					*cursor++ = '"';
					break;
				case 0x5c:
					*cursor++ = '\\';
					break;
				case 0x8:
					*cursor++ = 'b';
					break;
				case 0xc:
					*cursor++ = 'f';
					break;
				case 0xa:
					*cursor++ = 'n';
					break;
				case 0xd:
					*cursor++ = 'r';
					break;
				case 0x9:
					*cursor++ = 't';
					break;
				default:
					*cursor++ = 'u';
					*cursor++ = '0';
					*cursor++ = '0';
					*cursor++ = hexdig(u >> 4);
					*cursor++ = hexdig(u & 0xf);
				}
			}
			else
			{
				*cursor++ = (uchar)u;
			}
		}
		else if (QUtf8Functions::toUtf8<QUtf8BaseTraits>(u, cursor, src, end) < 0)
		{
			// failed to get valid utf8 use JSON escape sequence
			*cursor++ = '\\';
			*cursor++ = 'u';
			*cursor++ = hexdig(u >> 12 & 0x0f);
			*cursor++ = hexdig(u >> 8 & 0x0f);
			*cursor++ = hexdig(u >> 4 & 0x0f);
			*cursor++ = hexdig(u & 0x0f);
		}
	}
	ba.resize(cursor - (const uchar*)ba.constData());
	return ba;
}

QJsonModel::QJsonModel(QObject* parent)
	: QAbstractItemModel(parent)
	, mRootItem{ new QJsonTreeItem }
{
	mHeaders.append("Key");
	mHeaders.append("Value");
}

QJsonModel::QJsonModel(const QString& fileName, QObject* parent)
	: QAbstractItemModel(parent)
	, mRootItem{ new QJsonTreeItem }
{
	mHeaders.append("Key");
	mHeaders.append("Value");
	load(fileName);
}

QJsonModel::QJsonModel(QIODevice* device, QObject* parent)
	: QAbstractItemModel(parent)
	, mRootItem{ new QJsonTreeItem }
{
	mHeaders.append("Key");
	mHeaders.append("Value");
	load(device);
}

QJsonModel::QJsonModel(const QByteArray& json, QObject* parent)
	: QAbstractItemModel(parent)
	, mRootItem{ new QJsonTreeItem }
{
	mHeaders.append("Key");
	mHeaders.append("Value");
	loadJson(json);
}

QJsonModel::~QJsonModel()
{
	delete mRootItem;
}

bool QJsonModel::load(const QString& fileName)
{
	QFile file(fileName);
	bool success = false;
	if (file.open(QIODevice::ReadOnly)) {
		success = load(&file);
		file.close();
	}
	else success = false;

	return success;
}

bool QJsonModel::load(QIODevice* device)
{
	return loadJson(device->readAll());
}

bool QJsonModel::loadJson(const QByteArray& json)
{
	auto const& jdoc = QJsonDocument::fromJson(json);

	if (!jdoc.isNull())
	{
		beginResetModel();
		delete mRootItem;
		if (jdoc.isArray()) {
			mRootItem = QJsonTreeItem::load(QJsonValue(jdoc.array()));
			mRootItem->setType(QJsonValue::Array);

		}
		else {
			mRootItem = QJsonTreeItem::load(QJsonValue(jdoc.object()));
			mRootItem->setType(QJsonValue::Object);
		}
		endResetModel();
		return true;
	}

	qDebug() << Q_FUNC_INFO << "cannot load json";
	return false;
}


QVariant QJsonModel::data(const QModelIndex& index, int role) const
{

	if (!index.isValid())
		return QVariant();


	QJsonTreeItem* item = static_cast<QJsonTreeItem*>(index.internalPointer());


	if (role == Qt::DisplayRole) {

		if (index.column() == 0)
			return QString("%1").arg(item->key());

		if (index.column() == 1)
			return item->value();
	}
	else if (Qt::EditRole == role) {
		if (index.column() == 1) {
			return item->value();
		}
	}

	return QVariant();

}

bool QJsonModel::setData(const QModelIndex& index, const QVariant& value, int role)
{
	int col = index.column();
	if (Qt::EditRole == role) {
		if (col == 1) {
			QJsonTreeItem* item = static_cast<QJsonTreeItem*>(index.internalPointer());
			item->setValue(value);
			emit dataChanged(index, index, { Qt::EditRole });
			return true;
		}
	}

	return false;
}



QVariant QJsonModel::headerData(int section, Qt::Orientation orientation, int role) const
{
	if (role != Qt::DisplayRole)
		return QVariant();

	if (orientation == Qt::Horizontal) {

		return mHeaders.value(section);
	}
	else
		return QVariant();
}

QModelIndex QJsonModel::index(int row, int column, const QModelIndex& parent) const
{
	if (!hasIndex(row, column, parent))
		return QModelIndex();

	QJsonTreeItem* parentItem;

	if (!parent.isValid())
		parentItem = mRootItem;
	else
		parentItem = static_cast<QJsonTreeItem*>(parent.internalPointer());

	QJsonTreeItem* childItem = parentItem->child(row);
	if (childItem)
		return createIndex(row, column, childItem);
	else
		return QModelIndex();
}

QModelIndex QJsonModel::parent(const QModelIndex& index) const
{
	if (!index.isValid())
		return QModelIndex();

	QJsonTreeItem* childItem = static_cast<QJsonTreeItem*>(index.internalPointer());
	QJsonTreeItem* parentItem = childItem->parent();

	if (parentItem == mRootItem)
		return QModelIndex();

	return createIndex(parentItem->row(), 0, parentItem);
}

int QJsonModel::rowCount(const QModelIndex& parent) const
{
	QJsonTreeItem* parentItem;
	if (parent.column() > 0)
		return 0;

	if (!parent.isValid())
		parentItem = mRootItem;
	else
		parentItem = static_cast<QJsonTreeItem*>(parent.internalPointer());

	return parentItem->childCount();
}

int QJsonModel::columnCount(const QModelIndex& parent) const
{
	Q_UNUSED(parent)
		return 2;
}

Qt::ItemFlags QJsonModel::flags(const QModelIndex& index) const
{
	int col = index.column();
	auto item = static_cast<QJsonTreeItem*>(index.internalPointer());

	auto isArray = QJsonValue::Array == item->type();
	auto isObject = QJsonValue::Object == item->type();

	if ((col == 1) && !(isArray || isObject)) {
		return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
	}
	else {
		return QAbstractItemModel::flags(index);
	}
}

QByteArray QJsonModel::json()
{
	auto jsonValue = genJson(mRootItem);
	QByteArray json;
	if (jsonValue.isNull())
	{
		return json;
	}
	if (jsonValue.isArray())
	{
		arrayToJson(jsonValue.toArray(), json, 0, false);
	}
	else
	{
		objectToJson(jsonValue.toObject(), json, 0, false);
	}
	return json;
}

void QJsonModel::objectToJson(QJsonObject jsonObject, QByteArray& json, int indent, bool compact)
{
	json += compact ? "{" : "{\n";
	objectContentToJson(jsonObject, json, indent + (compact ? 0 : 1), compact);
	json += QByteArray(4 * indent, ' ');
	json += compact ? "}" : "}\n";
}
void QJsonModel::arrayToJson(QJsonArray jsonArray, QByteArray& json, int indent, bool compact)
{
	json += compact ? "[" : "[\n";
	arrayContentToJson(jsonArray, json, indent + (compact ? 0 : 1), compact);
	json += QByteArray(4 * indent, ' ');
	json += compact ? "]" : "]\n";
}

void QJsonModel::arrayContentToJson(QJsonArray jsonArray, QByteArray& json, int indent, bool compact)
{
	if (jsonArray.size() <= 0)
	{
		return;
	}
	QByteArray indentString(4 * indent, ' ');
	int i = 0;
	while (1)
	{
		json += indentString;
		valueToJson(jsonArray.at(i), json, indent, compact);
		if (++i == jsonArray.size())
		{
			if (!compact)
				json += '\n';
			break;
		}
		json += compact ? "," : ",\n";
	}
}
void QJsonModel::objectContentToJson(QJsonObject jsonObject, QByteArray& json, int indent, bool compact)
{
	if (jsonObject.size() <= 0)
	{
		return;
	}
	QByteArray indentString(4 * indent, ' ');
	int i = 0;
	while (1)
	{
		QString key = jsonObject.keys().at(i);
		json += indentString;
		json += '"';
		json += escapedString(key);
		json += compact ? "\":" : "\": ";
		valueToJson(jsonObject.value(key), json, indent, compact);
		if (++i == jsonObject.size())
		{
			if (!compact)
				json += '\n';
			break;
		}
		json += compact ? "," : ",\n";
	}
}

void QJsonModel::valueToJson(QJsonValue jsonValue, QByteArray& json, int indent, bool compact)
{
	QJsonValue::Type type = jsonValue.type();
	switch (type)
	{
	case QJsonValue::Bool:
		json += jsonValue.toBool() ? "true" : "false";
		break;
	case QJsonValue::Double:
	{
		const double d = jsonValue.toDouble();
		if (qIsFinite(d))
		{
			json += QByteArray::number(d, 'f', QLocale::FloatingPointShortest);
		}
		else
		{
			json += "null"; // +INF || -INF || NaN (see RFC4627#section2.4)
		}
		break;
	}
	case QJsonValue::String:
		json += '"';
		json += escapedString(jsonValue.toString());
		json += '"';
		break;
	case QJsonValue::Array:
		json += compact ? "[" : "[\n";
		arrayContentToJson(jsonValue.toArray(), json, indent + (compact ? 0 : 1), compact);
		json += QByteArray(4 * indent, ' ');
		json += ']';
		break;
	case QJsonValue::Object:
		json += compact ? "{" : "{\n";
		objectContentToJson(jsonValue.toObject(), json, indent + (compact ? 0 : 1), compact);
		json += QByteArray(4 * indent, ' ');
		json += '}';
		break;
	case QJsonValue::Null:
	default:
		json += "null";
	}
}

QJsonValue  QJsonModel::genJson(QJsonTreeItem* item) const
{
	auto type = item->type();
	int  nchild = item->childCount();

	if (QJsonValue::Object == type) {
		QJsonObject jo;
		for (int i = 0; i < nchild; ++i) {
			auto ch = item->child(i);
			auto key = ch->key();
			jo.insert(key, genJson(ch));
		}
		return  jo;
	}
	else if (QJsonValue::Array == type) {
		QJsonArray arr;
		for (int i = 0; i < nchild; ++i) {
			auto ch = item->child(i);
			arr.append(genJson(ch));
		}
		return arr;
	}
	else {
		QJsonValue va;
		switch (item->value().type()) {
		case QVariant::Bool:
		{
			va = item->value().toBool();
			break;
		}
		default:
			va = item->value().toString();
			break;
		}
		(item->value());
		return va;
	}

}
Summary* QJsonModel::getJsonSummary()
{
    Summary *sum = new Summary();
    sum->setObjectCount(mRootItem->summary->getObjectCount());
    sum->setArrayCount(mRootItem->summary->getArrayCount());
    sum->setStringCount(mRootItem->summary->getStringCount());
    sum->setNumberCount(mRootItem->summary->getNumberCount());
    sum->setNullCount(mRootItem->summary->getNullCount());
    sum->setBooleanCount(mRootItem->summary->getBooleanCount());
	return sum;
}
