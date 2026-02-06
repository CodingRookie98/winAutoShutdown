# 重构计划: winAutoShutdown (Rust + Tauri + Vue)

**目标**: 将现有的 C++ Qt 项目重构为 Rust + Tauri + Vue 架构，以提升开发体验、测试效率和界面现代化程度。

## 阶段 1: 基础设施搭建 (Infrastructure & Hello World)
**目标**: 建立 Tauri 项目骨架，确保开发环境就绪，并跑通最小链路。
**成功标准**:
- [x] Tauri + Vue (Vite) 项目初始化成功 (使用 pnpm)。
- [x] 能够成功编译并运行 Debug 版本。
- [x] 实现前端 (Vue) 调用 Rust 后端 (Command) 打印 "Hello World"。
- [x] 配置好项目目录结构 (`src-tauri` 用于 Rust, `src` 用于 Vue)。
**测试**: 运行 `pnpm tauri dev` 成功启动应用窗口。
**状态**: 已完成

## 阶段 2: 核心业务逻辑迁移 (Lightweight Rust)
**目标**: 实现一个极简、可靠的 Rust 后端，仅负责“系统控制”和“防冻结计时”，复杂业务逻辑移交前端。
**成功标准**:
- [x] **TDD 环境配置**:
    - [x] 确保 `cargo test` 可运行。
    - [x] 引入 `mockall` 用于模拟系统调用。
- [x] **SystemControl 模块 (TDD)**:
    - [x] **Red**: 创建 `system_control_spec.rs`，定义 `shutdown`, `reboot` 接口，Mock 系统命令执行。
    - [x] **Green**: 实现 `SystemControl` trait 及 Windows `shutdown /s /t 0` 调用。
    - [x] **Refactor**: 处理命令执行错误，确保在非 Windows 环境下能编译通过（Stub）。
- [x] **TimerService 模块 (TDD)**:
    - [x] **Red**: 创建 `timer_spec.rs`，测试定时器回调触发。
    - [x] **Green**: 使用 `std::thread` 或 `tokio` 实现一个简单的倒计时器，支持 `start(duration)` 和 `cancel()`。
    - [x] **Refactor**: 确保计时器在后台线程运行，不会阻塞主线程。
- [x] **Tauri Commands**:
    - [x] 暴露 `start_shutdown_timer(seconds: u64)`。
    - [x] 暴露 `cancel_timer()`。
    - [x] 暴露 `execute_shutdown_now()`。
**测试**: 运行 `cargo test`，确保计时准确，命令构建正确。
**状态**: 已完成

## 阶段 3: 前端界面与业务逻辑 (Vue + Pinia)
**目标**: 使用 Vue 实现所有用户交互、任务管理、配置持久化。
**成功标准**:
- [ ] **TDD 环境配置**:
    - [ ] 安装 Vitest, @vue/test-utils, Pinia。
- [ ] **Task Store (Pinia TDD)**:
    - [ ] **Red**: 测试任务的添加、删除、倒计时计算逻辑。
    - [ ] **Green**: 实现 `useTaskStore`，包含 `tasks` 数组和 `startTask` action。
    - [ ] **Integration**: 在 `startTask` 中调用 Rust 的 `start_shutdown_timer`。
- [ ] **UI Components**:
    - [ ] 任务列表、添加任务表单、倒计时展示。
- [ ] **持久化**:
    - [ ] 使用 `pinia-plugin-persistedstate` 或 `localStorage` 保存任务配置。
**状态**: 未开始

## 阶段 4: 系统集成与完善 (Integration & Polish)
**目标**: 完成前后端对接，确保端到端流程符合预期。
**成功标准**:
- [ ] **IPC 契约测试**:
    - [ ] **Red**: 编写测试验证 Rust Command `invoke` 接口的输入输出格式。
    - [ ] **Green**: 实现 Rust Command (`#[tauri::command]`) 并对接 `TaskScheduler`。
    - [ ] **Refactor**: 统一错误处理格式 (Result -> Serialized Error)。
- [ ] **持久化 (Persistence TDD)**:
    - [ ] **Red**: 在 Rust 端编写 `store_spec.rs`，测试任务列表的 JSON 序列化与文件读写（Mock 文件 IO）。
    - [ ] **Green**: 实现基于文件的存储库 (Repository Pattern)。
    - [ ] **Refactor**: 集成 `tauri-plugin-store` 或自定义存储层，确保异常处理健壮。
- [ ] **E2E 冒烟测试**:
    - [ ] 手动或自动化验证：启动 -> 添加任务 -> 验证倒计时 -> 触发关机（模拟）。
- [ ] **辅助功能**:
    - [ ] 国际化 (i18n) 支持。
    - [ ] 开机自启配置。
**测试**: `cargo test` (后端) + `pnpm test` (前端) + 手动验收。
**状态**: 未开始

## 阶段 5: 打包与交付 (Packaging & Delivery)
**目标**: 生成最终可执行文件，清理项目。
**成功标准**:
- [ ] **构建配置验证**:
    - [ ] 检查 `tauri.conf.json` 中的 bundle 配置 (icon, identifier)。
- [ ] **Release 构建**:
    - [ ] 运行 `pnpm tauri build` 成功生成 `.exe`/`.msi`。
- [ ] **安装测试**:
    - [ ] 在全新环境中运行安装包，验证安装路径与快捷方式。
- [ ] **项目清理**:
    - [ ] 移除 `legacy/` 目录。
    - [ ] 归档文档。
**状态**: 未开始
