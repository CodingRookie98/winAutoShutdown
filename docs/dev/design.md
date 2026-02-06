# WinAutoShutdown Design Document

## 1. 系统概述 (System Overview)
WinAutoShutdown 旨在为 Windows 用户提供轻量级、可靠的自动化电源管理工具。
- **核心目标**: 提供直观的定时关机、重启、休眠、睡眠功能。
- **约束条件**:
  - 仅支持 Windows 10/11。
  - 基于 Tauri v2 框架。
  - 后端使用 Rust，前端使用 Vue 3 + TypeScript。

## 2. 架构设计 (Architecture)

### 2.1 整体架构
采用典型的 C/S 架构变体，前端作为 UI 交互层，后端作为系统服务层。

- **Frontend (Vue 3)**: 负责用户交互、任务配置、倒计时显示、持久化配置管理。
- **Backend (Rust)**: 负责执行特权系统调用（关机/重启）、高精度计时保底（可选）、托盘管理。
- **IPC Bridge**: 使用 Tauri Commands 进行指令传递，Events 进行状态同步。

### 2.2 前后端职责边界
为了保持后端轻量（符合 Core Memory 01KGREFKY4Z9534V87FAC9A6A7），我们将大部分业务逻辑放在前端。

| 模块 | 职责 | 备注 |
| :--- | :--- | :--- |
| **Frontend** | 任务调度逻辑 (Scheduler) | 负责计算何时触发，维护倒计时状态 |
| **Frontend** | 任务队列管理 | 增删改查任务 |
| **Frontend** | 配置持久化 | 保存用户设置 |
| **Backend** | 系统控制 (SystemControl) | 仅执行最终的 API 调用 (ExitWindowsEx) |
| **Backend** | 计时服务 (TimerService) | **可选**。仅在系统即将休眠或前端可能被冻结时作为保底。目前优先前端计时。 |

## 3. 核心模块设计 (Core Modules)

### 3.1 系统控制 (SystemControl)
负责调用 Windows 底层 API 执行电源操作。

- **技术选型**: 使用 `windows-rs` crate 直接调用 Win32 API。
- **理由**:
  - 相比复用 `legacy` C++ 代码，Rust 重写无需引入 C++ 构建链，维护更简单。
  - `windows-rs` 提供了类型安全的封装，比手写 FFI 更安全。
  - 逻辑简单（提权 + 调用 API），迁移成本极低。

- **核心 API 映射**:
  - 关机: `ExitWindowsEx(EWX_SHUTDOWN | EWX_FORCE, 0)`
  - 重启: `ExitWindowsEx(EWX_REBOOT | EWX_FORCE, 0)`
  - 锁定: `LockWorkStation()`
  - 睡眠/休眠: `SetSuspendState(...)`

- **权限管理**:
  - 必须在执行前请求 `SE_SHUTDOWN_NAME` 权限 (LookupPrivilegeValue + AdjustTokenPrivileges)。

### 3.2 任务调度 (Task Scheduling)
支持两种触发模式：
1.  **倒计时 (Countdown)**: "X [天/小时/分钟/秒] 后关机"，支持灵活的时间单位组合。
2.  **指定时间 (Specific Time)**: "在 YYYY-MM-DD HH:mm:ss 关机"，支持完整的日期时间选择。

- **实现方案**:
  - 前端统一将所有任务转换为 "目标时间戳 (Target Timestamp)"。
  - 使用 `setInterval` (1s) 检查当前时间是否超过目标时间戳。
  - **防冻结机制**: 如果前端被挂起，唤醒后通过比对时间戳发现已过期，应立即触发或询问用户（取决于策略）。

## 4. 数据持久化 (Persistence)
- **方案**: 前端 `pinia-plugin-persistedstate` (localStorage)。
- **内容**:
  - 待执行的任务列表。
  - 全局设置（如：是否开机自启）。

## 5. IPC 接口设计 (IPC Interfaces)

### Commands (Frontend -> Backend)
```rust
// 执行立即操作
fn execute_system_action(action: SystemAction) -> Result<(), String>;

// 注册后端保底计时器 (可选，若前端计时不可靠)
fn start_shutdown_timer(seconds: u64);
fn cancel_timer();
```

### Events (Backend -> Frontend)
- `timer-tick`: 后端倒计时推送 (若使用后端计时)。

## 6. UI/UX 设计原则 (UI/UX Guidelines)
- 现代化、简洁风格。
- 暗色模式支持。
- 关键操作（关机）需有明显的确认或撤销机制。
