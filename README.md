
# Json-Visualizer

JSON Explorer / Json-Visualizer is a desktop application written in modern C++ and Qt that helps you inspect, validate and explore JSON documents in a tree view. It's designed for fast parsing (uses simdjson) and provides utilities such as JSON validation, JSON -> XML/CSV/Base64 conversion, minify/pretty-print and JSONPath querying via jsoncons.

This repository contains the full application source (Qt project) and bundled JSON libraries used by the project.

## Key features

- Parse and validate JSON quickly using simdjson (embedded in the repo).
- Display JSON as an editable tree using a Qt model/view (QTreeView backed by `QJsonModel`).
- Query JSON using JSONPath expressions (via jsoncons/jsonpath).
- Generate a summary (counts of objects/arrays/strings/numbers/nulls/booleans, MD5 hash, parsing time, data size).
- Convert JSON to XML, CSV or Base64 (menu actions exist in UI).
- Open/Edit/Save local .json files, browse filesystem and view containing folder.

## Screenshots

See `docs/screenshots/` for project screenshots used in the original README.

## High-level architecture

- `MainWindow.*` — Qt UI and main application logic. Connects UI events to worker methods, updates the tree view and summary dialog.
- `qjsonmodel.*` — A QAbstractItemModel implementation (QJsonModel) and supporting QJsonTreeItem that turns a QJsonDocument into a tree model suitable for `QTreeView`.
- `JsonWorker.*` — Helper class that performs parsing (simdjson), tree-generation and JSONPath queries (jsoncons jsonpath). Also measures parsing time.
- `simdjson.*` — Vendored simdjson implementation (fast C++ JSON parser). Used to validate/parse JSON quickly.
- `jsoncons/` and `jsoncons_ext/` — bundled jsoncons library used for JSONPath queries and conversions.
- `Summary.*` — A small dialog that presents counts (object/array/string/number/null/boolean), MD5 hash, parsing time and data size.
- `File.*` — Simple file operations (open, read, write, browse). UI resources and icons are in `icons/` and `MainWindow.qrc`.

## Important files

- `JsonVisualizer.pro` - Qt project file (qmake). Open this with Qt Creator.
- `main.cpp` - standard Qt application entry point.
- `MainWindow.ui` - UI layout used by `MainWindow`.
- `qjsonmodel.cpp/h` - model and tree item implementations.
- `JsonWorker.cpp/h` - parse/validate/query helpers.
- `simdjson.cpp/h` - embedded simdjson library code.
- `jsoncons/` - bundled jsoncons library (JSONPath support).

## Build (Windows / Qt)

Prerequisites
- Qt 5.x or Qt 6.x (Qt Widgets module). Qt Creator recommended.
- A C++ compiler supported by Qt (MSVC or MinGW).

Quick steps (recommended: use Qt Creator):

1. Open `JsonVisualizer.pro` with Qt Creator.
2. Configure kit (select MSVC or MinGW kit) and click "Configure Project".
3. Build and run from Qt Creator (F5 / Run).

Command-line build (example with Qt's qmake + mingw make in PowerShell):

> Note: these commands are optional examples — using Qt Creator will be easier.

```powershell
# from repository root
& qmake JsonVisualizer.pro
# then (depending on kit) use mingw32-make or nmake
# mingw:
mingw32-make
# msbuild/nmake for MSVC (kit dependent)
```

The repo includes `simdjson` and `jsoncons` sources; no external install should be required for a local build.

## Run / Usage

1. Start the application.
2. Use File -> Browse or the toolbar to open a `.json` file.
3. The left pane is the raw JSON editor; the right pane is a tree view generated from the JSON. Edits to the text area trigger re-parse and refresh of the tree view (if valid JSON).
4. Enter JSONPath expressions in the top text box to filter the JSON (placeholder: "Type your JsonPath query here"). Query results (if any) are displayed in the tree view.
5. Use View -> Summary to open the summary dialog (object/array/string/number/null/boolean counts, MD5, parsing time, size).

Notes:
- The UI contains menu actions for conversions (XML/CSV/Base64) and minify. Some actions may be stubs depending on the current code state — examine `MainWindow` to see which slots are implemented.

## Module notes & implementation details

- MainWindow
	- `MainWindow::on_plainTextEdit_textChanged()` updates the internal JSON string, recomputes MD5 hash, validates JSON via `JsonWorker::IsValid`, and calls `DrawTreeView` if valid.
	- File operations are delegated to `File` helper. Summary dialog is obtained from `QJsonModel::getJsonSummary()`.

- QJsonModel / QJsonTreeItem
	- Builds an in-memory tree representation from a `QJsonDocument` and exposes it as a `QAbstractItemModel` for `QTreeView`.
	- Supports editing of leaf values and reserializing to JSON via `QJsonModel::json()`.

- JsonWorker
	- `IsValid(QString&)` uses `simdjson::dom::parser` to parse and returns whether parsing succeeded; also records parsing time.
	- `GenerateTreeView` hands the raw JSON bytes to `QJsonModel::loadJson()`.
	- `QueryJson` uses `jsoncons::json` and `jsoncons::jsonpath::json_query` to run JSONPath queries; catches errors and returns an empty QString on failure.

- Summary
	- Tracks counts and other metadata and displays them in a modal dialog.

## Troubleshooting & tips

- Large documents: simdjson is fast but the UI may still struggle with very large JSON trees. Consider increasing memory or using streaming.
- If you get `CAPACITY` or other simdjson errors, the file may be larger than the parser's practical limits — consider splitting the document.
- If JSONPath queries return empty, validate the JSON and verify the query syntax; UI placeholder indicates JSONPath support (see jsoncons docs).

## Suggested next steps / improvements

- Add unit tests for `QJsonModel` round-trip JSON -> model -> JSON.
- Add CI (GitHub Actions) that runs a quick build matrix (Windows + Linux) and runs basic tests.
- Improve error reporting for JSONPath queries (show parse errors to user instead of silently returning empty string).
- Add streaming view for very large JSON files.

## License
See repository root or ask project owner — the repo does not contain an explicit LICENSE file in the workspace snapshot. Add a license file if you plan to publish.

---

If you'd like, I can now:

- add a `docs/USAGE.md` with step-by-step screenshots and example JSONPath queries, or
- add small developer docs for each module in `docs/` and update source headers with short doxygen-style comments.

Tell me which follow-up you'd prefer and I'll proceed (I'll update the todo list and work on that next).
