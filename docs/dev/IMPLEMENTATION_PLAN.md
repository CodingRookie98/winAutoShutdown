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

## 阶段 2: 核心业务逻辑迁移 (Core Logic - Rust)
**目标**: 使用 TDD (Red-Green-Refactor) 在 Rust 端重写电源管理和任务调度逻辑。
**成功标准**:
- [x] **TDD 环境配置**:
    - [x] 确保 `cargo test` 可运行。
    - [x] 引入 `mockall` 用于模拟系统调用。
- [x] **Domain Core (TDD)**:
    - [x] **Red**: 创建 `task_spec.rs`，测试 `Task` 实体创建、校验（如时间不能为过去）及序列化。
    - [x] **Green**: 定义 `Task` 结构体及 `PowerAction` 枚举。
    - [x] **Refactor**: 确保字段类型合适（如使用 `chrono` 处理时间），实现 `Serialize`/`Deserialize`。
- [ ] **PowerManager 模块 (TDD)**:
    - [ ] **Red**: 创建 `power_manager_spec.rs`，定义 `shutdown`, `reboot` 等接口，断言其调用了底层系统命令（通过 Mock）。
    - [ ] **Green**: 实现 `PowerManager` trait 及 Windows 具体实现（使用 `std::process::Command` 或 WinAPI）。
    - [ ] **Refactor**: 提取 `SystemCommandExecutor` trait 以便测试隔离，处理权限错误。
- [ ] **TaskScheduler 模块 (TDD)**:
    - [ ] **Red**: 创建 `scheduler_spec.rs`，测试添加任务、取消任务、任务到期回调触发。
    - [ ] **Green**: 实现内存中的任务队列及定时检查逻辑（Tick Loop）。
    - [ ] **Refactor**: 引入 `tokio` 异步运行时处理并发，确保调度器线程安全（Arc/Mutex）。
- [ ] **SystemTray 状态机 (TDD)**:
    - [ ] **Red**: 测试托盘菜单状态变更（如“运行中”->“暂停”）。
    - [ ] **Green**: 实现托盘菜单状态逻辑。
**测试**: 运行 `cargo test`，核心逻辑覆盖率目标 > 80%。
**状态**: 未开始

## 阶段 3: 前端界面实现 (UI Implementation - Vue)
**目标**: 使用组件测试驱动开发 (Component TDD) 构建 Vue 界面。
**成功标准**:
- [ ] **TDD 环境配置**:
    - [ ] 安装并配置 Vitest, @vue/test-utils, happy-dom。
    - [ ] 配置测试覆盖率报告。
- [ ] **State Management (Pinia TDD)**:
    - [ ] **Red**: 创建 `stores/taskStore.spec.ts`，测试 `addTask`, `removeTask`, `loadTasks` 的状态变更。
    - [ ] **Green**: 实现 `useTaskStore` 及基本 Actions。
    - [ ] **Refactor**: 抽离通用逻辑，优化 Store 结构，确保类型安全。
- [ ] **UI Components (Component TDD)**:
    - [ ] **Atomic Components**:
        - [ ] **Red**: 编写 `BaseButton.spec.ts` (测试点击事件, loading 状态样式)。
        - [ ] **Green**: 实现 `BaseButton.vue`。
    - [ ] **TaskList Module**:
        - [ ] **Red**: 编写 `TaskList.spec.ts`，模拟 Store 数据，验证列表项渲染及删除按钮点击。
        - [ ] **Green**: 实现 `TaskList.vue` 及 `TaskItem.vue`。
    - [ ] **TaskForm Module**:
        - [ ] **Red**: 编写 `TaskForm.spec.ts`，验证表单校验（非空、时间格式）及提交事件。
        - [ ] **Green**: 实现 `TaskForm.vue`。
- [ ] **UI 集成**: 集成 Naive UI，组装 `App.vue`。
**测试**: 运行 `pnpm test`，组件逻辑覆盖率目标 > 80%。
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
