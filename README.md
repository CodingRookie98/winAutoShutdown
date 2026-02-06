# WinAutoShutdown (Rust + Tauri + Vue)

> **English** | [中文](./docs/README_zh-CN.md)

A modern Windows auto-shutdown/task scheduling tool built on Rust and Tauri, providing a lightweight, secure, and beautiful user experience.

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Version](https://img.shields.io/badge/version-1.2.0-green.svg)

## ✨ Features

- 🚀 **High Performance**: Low resource usage powered by Rust backend.
- 🎨 **Modern UI**: Built with Vue 3, supports Dark Mode.
- 🛡️ **Secure**: Requires admin privileges for system operations, transparent execution.
- ⏰ **Multi-task Support**: Supports Shutdown, Reboot, Sleep, Lock, and more.
- 🔄 **Task Management**: View or cancel pending tasks at any time.

## 🛠️ Tech Stack

- **Frontend**: Vue 3, TypeScript, Vite
- **Backend**: Rust, Tauri, Windows API
- **State Management**: Pinia
- **Testing**: Vitest (Frontend), Cargo Test (Backend)

## 📦 Installation & Run

### Prerequisites

- Node.js (v18+)
- pnpm
- Rust (Latest Stable)
- Visual Studio C++ Build Tools (Windows)

### Development

```bash
# Install dependencies
pnpm install

# Start dev server (Frontend + Backend)
pnpm tauri dev
```

### Build for Production

```bash
# Build Windows installer (.msi, .exe)
pnpm tauri build
```

## 🧪 Testing

This project follows TDD (Test-Driven Development) principles.

```bash
# Run frontend tests
pnpm test

# Run backend tests
cd src-tauri && cargo test
```

## 📂 Project Structure

```
winAutoShutdown/
├── src/                # Vue Frontend Source
│   ├── components/     # UI Components
│   ├── composables/    # Composable Logic (Hooks)
│   ├── stores/         # Pinia Stores
│   └── ...
├── src-tauri/          # Rust Backend Source
│   ├── src/
│   │   ├── core/       # Core Business Logic (Timer, SystemControl)
│   │   └── ...
│   └── ...
├── docs/               # Documentation
└── ...
```

## 🤝 Contribution

Issues and Pull Requests are welcome! Please follow these guidelines:

1.  **Commit Message**: Use Conventional Commits (e.g., `feat: add timer`, `fix: dark mode`).
2.  **Branching**: Do not commit directly to `master`. Use `dev` or `feature/*` branches.
3.  **Code Style**: Keep code clean, run `cargo fmt` and ESLint.

## 📄 License

MIT License
