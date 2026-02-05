# winAutoShutdown Project Guidelines for AI Agents (Rust + Tauri + Vue)

## 1. Build and Environment
This is a Rust + Tauri + Vue project.

### Build Commands
- **Dev**: `pnpm tauri dev`
- **Build**: `pnpm tauri build`
- **Frontend Only**: `pnpm dev` / `pnpm build`
- **Backend Only**: `cd src-tauri && cargo build`

### Package Management
- Use **pnpm**.

## 2. Code Style
- **Rust**: Follow `cargo fmt` and Clippy.
- **Vue/TS**: Follow ESLint/Prettier (standard Vue 3 style).
- **Naming**: `snake_case` for Rust, `camelCase` for TS/JS.

## 3. Architecture
- `src/`: Vue frontend.
- `src-tauri/`: Rust backend.
- `legacy/`: Old C++ implementation (Reference only).

## 4. Testing & TDD (Mandatory)
- **TDD Requirement**: **Test-Driven Development is NOT optional.**
  1. **Red**: Write a failing test first.
  2. **Green**: Implement just enough to pass.
  3. **Refactor**: Improve code quality under test protection.
- **Frameworks**:
  - **Rust**: Built-in `cargo test`.
  - **Frontend**: Vitest (To be setup).
- **No Tests = No Code**: Do not write implementation code without a corresponding test.
