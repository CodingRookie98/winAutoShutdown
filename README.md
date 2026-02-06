# WinAutoShutdown (Rust + Tauri + Vue)

一个现代化的 Windows 自动关机/任务计划工具，构建于 Rust 和 Tauri 之上，提供轻量、安全且美观的用户体验。

![License](https://img.shields.io/badge/license-MIT-blue.svg)
![Version](https://img.shields.io/badge/version-1.2.0-green.svg)

## ✨ 特性

- 🚀 **高性能**: 基于 Rust 后端，资源占用极低。
- 🎨 **现代化 UI**: 使用 Vue 3 构建，支持深色模式 (Dark Mode)。
- 🛡️ **安全**: 需要管理员权限执行系统操作，操作透明。
- ⏰ **多任务支持**: 支持定时关机、重启、睡眠、锁定等多种任务。
- 🔄 **任务管理**: 可随时取消或查看待执行任务。

## 🛠️ 技术栈

- **Frontend**: Vue 3, TypeScript, Vite
- **Backend**: Rust, Tauri, Windows API
- **State Management**: Pinia
- **Testing**: Vitest (Frontend), Cargo Test (Backend)

## 📦 安装与运行

### 前置要求

- Node.js (v18+)
- pnpm
- Rust (最新稳定版)
- Visual Studio C++ Build Tools (Windows)

### 开发环境启动

```bash
# 安装依赖
pnpm install

# 启动开发服务器 (同时启动前端和后端)
pnpm tauri dev
```

### 构建生产版本

```bash
# 构建 Windows 安装包 (.msi, .exe)
pnpm tauri build
```

## 🧪 测试

本项目遵循 TDD (测试驱动开发) 原则。

```bash
# 运行前端测试
pnpm test

# 运行后端测试
cd src-tauri && cargo test
```

## 📂 项目结构

```
winAutoShutdown/
├── src/                # Vue 前端源码
│   ├── components/     # UI 组件
│   ├── composables/    # 组合式逻辑 (Hooks)
│   ├── stores/         # Pinia 状态管理
│   └── ...
├── src-tauri/          # Rust 后端源码
│   ├── src/
│   │   ├── core/       # 核心业务逻辑 (Timer, SystemControl)
│   │   └── ...
│   └── ...
├── docs/               # 项目文档
└── ...
```

## 🤝 贡献

欢迎提交 Issue 和 Pull Request！请确保遵循以下规范：

1.  **Commit Message**: 使用 Conventional Commits 规范 (e.g., `feat: add timer`, `fix: dark mode`).
2.  **Branching**: 不要在 `master` 分支直接提交，请使用 `dev` 或 `feature/*` 分支。
3.  **Code Style**: 保持代码整洁，运行 `cargo fmt` 和 ESLint。

## 📄 许可证

MIT License
