# winAutoShutdown Project Guidelines for AI Agents

## 1. Build and Environment
This is a C++20 project using Qt 6/5 and CMake. It is primarily developed for Windows.

### Build Commands
- **Configure**: `cmake -B build -G "Ninja" -DCMAKE_BUILD_TYPE=Debug`
- **Build All**: `cmake --build build`
- **Clean**: `cmake --build build --target clean`
- **Install/Deploy**:
  - `cmake --build build --target install_all_targets`
  - `cmake --build build --target qt_deploy_release` (Release mode only, for Windows deployment)

### Running the Application
- **Debug**: `bin/Debug/winAutoShutdown.exe`
- **Release**: `bin/Release/winAutoShutdown.exe`
- **Working Directory**: The application expects `settings.ini` and `translations/` to be available relative to the executable or in the current working directory.

### Linting and Formatting
- **Format Check/Apply**: Use `clang-format` based on the `.clang-format` file.
  - Apply to file: `clang-format -i path/to/file.cpp`
- **Static Analysis**: Use `lsp_diagnostics` to check for errors before submitting code.

### Testing & TDD (Mandatory)
- **TDD Requirement**: **Test-Driven Development is NOT optional.**
  1. **Red**: Write a failing test first.
  2. **Green**: Implement just enough to pass.
  3. **Refactor**: Improve code quality under test protection.
- **Frameworks**: GTest or Qt Test. Located in `tests/`.
- **No Tests = No Code**: Do not write implementation code without a corresponding test.

---

## 2. Code Style and Conventions

### General Rules
- **Standard**: C++20 (`set(CMAKE_CXX_STANDARD 20)`).
- **Style Base**: LLVM (configured via `.clang-format`).
- **Indentation**: 4 spaces, no tabs.
- **Braces**: Attached to the statement (e.g., `if (cond) {`).
- **Line Length**: Prefer no hard limit, but keep it readable (around 100-120 chars).

### Naming Conventions
- **Files**: `camelCase.cpp` / `camelCase.h` (e.g., `mainWindow.cpp`).
- **Classes**: `PascalCase` (e.g., `MainWindow`, `OptionWidget`).
- **Methods/Functions**:
  - Prefer `camelCase` for methods (e.g., `init()`, `signalsProcess()`) to align with Qt conventions.
  - Use `PascalCase` for some standalone functions or public API-like methods if appropriate (e.g., `RestartApp()`).
  - Qt slots: `on_<objectName>_<signalName>` (e.g., `on_btnAddTask_clicked()`).
- **Member Variables**: `snake_case_` with a trailing underscore (e.g., `optionWidget_`, `trayIcon_`).
- **Local Variables**: `snake_case` (e.g., `language_file_name`, `message_box`).
- **Enums**: `PascalCase` for the enum class name, `snake_case` or `PascalCase` for members (e.g., `Language::zh_CN`).
- **Namespaces**: `snake_case` (e.g., `work`, `operation`).

### Code Organization and Imports
- **Include Order**:
  1. Related header (for .cpp files).
  2. Standard library headers (`<vector>`, `<memory>`).
  3. Qt headers (`<QMainWindow>`, `<QTranslator>`).
  4. Project headers (`"worker.h"`, `"mainWindow.h"`).
- **Header Guards**: Use `#ifndef PROJECT_PATH_FILE_H_` style (e.g., `WINAUTOSHUTDOWN_SRC_MAINWINDOW_H_`) or simple `#ifndef FILENAME_H`.
- **Namespaces**: Use `QT_BEGIN_NAMESPACE` and `QT_END_NAMESPACE` for Qt-related declarations in headers to support various Qt configurations.

### Error Handling
- Use `QMessageBox` for user-facing errors in UI code.
- Check return values for critical operations (e.g., `translator.load()`).
- Prefer `std::make_unique` or `std::make_shared` for memory management.

---

## 3. Architecture & Structure

### Directory Structure
- `src/`: Root of source code.
- `src/ui/`: UI-related classes (MainWindow, Dialogs, Widgets).
- `src/components/work/`: Core logic for task scheduling and execution.
- `src/res/`: Resource files (icons, images, markdown files).
- `translations/`: Qt translation sources (`.ts`).
- `bin/`: Build artifacts.

### Key Patterns
- **Signals and Slots**: Always use the function pointer based `connect()` syntax.
- **signalsProcess()**: Convention in UI classes to group all signal-slot connections.
- **Worker Pattern**: Scheduling is handled in `Worker` class which runs a background thread (`Working()`) to execute `Work` items at specific times.

---

## 4. UI & Localization

### Qt UI Files
- Use `.ui` files for layout whenever possible.
- UI elements are accessed via the `ui` pointer (e.g., `ui->btnAddTask`).

### Localization
- Always wrap user-visible strings in `tr()`.
- Localization files are managed in the `translations/` directory.
- When adding new strings, run `lupdate` (part of Qt) to update `.ts` files, or remind the developer to do so.

## 5. AI Interaction Rules
- **Strictly Follow TDD**: Always write tests *before* implementation.
- **Do not** delete existing Doxygen-style comments or file headers.
- **Always** ensure `lsp_diagnostics` are clean after modifications.
- **Be proactive** in updating translation files (`.ts`) if you add new `tr()` strings.
- Follow the existing pattern of using `signalsProcess()` for connecting signals and slots in UI classes.
- When creating new UI components, remember to add them to the appropriate `CMakeLists.txt`.
