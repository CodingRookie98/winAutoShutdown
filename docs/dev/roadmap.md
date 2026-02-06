# 实施路线图: WinAutoShutdown (Rust + Tauri + Vue)

> **基准文档**: [DESIGN.md](./DESIGN.md)
> **状态**: 阶段 1-3 已完成，准备进入阶段 4。

## 阶段 1: 基础设施搭建 (Infrastructure) [✅ 已完成]
**目标**: 建立 Tauri 项目骨架，确保开发环境就绪。
- [x] Tauri + Vue (Vite) 项目初始化。
- [x] 调试环境配置 (Rust Backend + Vue Frontend)。
- [x] Hello World 链路打通。

## 阶段 2: 核心业务逻辑迁移 (Lightweight Rust) [✅ 已完成]
**目标**: 实现 Rust 后端基础架构。
- [x] TDD 环境配置 (cargo test + mockall)。
- [x] SystemControl Trait 定义与 Mock 实现。
- [x] TimerService 基础实现 (简单的后台线程计时)。
- [x] Tauri Commands 暴露 (start_timer, cancel_timer)。

## 阶段 3: 前端界面与业务逻辑 (Vue + Pinia) [✅ 已完成]
**目标**: 实现前端基础交互与状态管理。
- [x] Vitest + Pinia 环境配置。
- [x] TaskStore 实现 (任务增删、倒计时逻辑)。
- [x] 基础 UI 组件 (TaskForm, TaskList)。
- [x] 数据持久化 (pinia-plugin-persistedstate)。

---

## 阶段 4: 系统集成与功能增强 (System Integration & Enhancement) [✅ 已完成]
**目标**: 基于 `design.md` 实现真实的 Windows 系统调用，并升级前端以支持高精度时间选择。
**当前状态**: ✅ 已完成

### 4.1 后端: SystemControl 真实实现 (windows-rs) [✅ 已完成]
> 参考 design.md 第 3.1 节
- [x] **依赖配置**:
    - [x] 在 `Cargo.toml` 中添加 `windows` crate (features: Win32_Security, Shutdown, Power)。
- [x] **权限管理 (Privilege)**:
    - [x] 实现 `enable_shutdown_privilege` (LookupPrivilegeValue + AdjustTokenPrivileges)。
- [x] **API 封装 (Unsafe Wrapper)**:
    - [x] 实现 `shutdown()` -> `ExitWindowsEx(EWX_SHUTDOWN)`.
    - [x] 实现 `reboot()` -> `ExitWindowsEx(EWX_REBOOT)`.
    - [x] 实现 `sleep()` / `hibernate()` -> `SetSuspendState`.
    - [x] 实现 `lock()` -> `LockWorkStation`.
- [x] **Command 接入**:
    - [x] 替换 `lib.rs` 中的 Mock 实现，接入真实逻辑。

### 4.2 前端: 调度器与 UI 升级 (UI/UX Upgrade) [✅ 已完成]
> 参考 design.md 第 3.2 节
- [x] **UI 组件重构 (TaskForm.vue)**:
    - [x] **倒计时模式**: 替换单一输入框，实现 [天/时/分/秒] 组合输入组件。
    - [x] **指定时间模式**: 引入日期时间选择器 (Native `datetime-local` 或组件库)，支持 `YYYY-MM-DD HH:mm:ss`。
- [x] **逻辑升级 (TaskStore)**:
    - [x] 统一使用 "目标时间戳 (Target Timestamp)" 作为内部存储格式。
    - [x] 优化倒计时显示逻辑 (格式化为 DD:HH:MM:SS)。
    - [x] 处理跨天/跨月的时间计算。

### 4.3 集成测试与验证 (Integration Verification) [✅ 已完成]
- [x] **IPC 联调**:
    - [x] 验证前端 Action 正确触发后端 Command。
    - [x] 验证后端错误 (如权限不足) 能正确反馈给前端。
- [x] **真实场景测试**:
    - [x] 虚拟机/真机测试关机、重启功能。
    - [x] 验证睡眠唤醒后的倒计时准确性。

## 阶段 5: 打包与交付 (Packaging & Delivery) [✅ 已完成]
**目标**: 生成最终可发布版本。
**当前状态**: ✅ 已完成

- [x] **功能增强 (Enhancements)**:
    - [x] 深色/浅色模式切换。
    - [x] 关于页面 (About Page)。
- [x] **应用配置**:
    - [x] 配置应用图标 (Icons)。
    - [x] 设置应用元数据 (Identifier, Version, ProductName)。
- [x] **构建发布**:
    - [x] 运行 `pnpm tauri build`。
    - [x] 验证生成的 `.exe` / `.msi` 安装包文件名是否正确。
- [x] **清理与归档**:
    - [x] 移除 `legacy/` 代码。
    - [x] 完善最终用户文档。
