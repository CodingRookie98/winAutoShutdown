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
**目标**: 在 Rust 端重写电源管理和任务调度逻辑，并建立自动化测试。
**成功标准**:
- [ ] 实现 `PowerAction` 模块 (使用 `windows-rs` 或系统命令实现关机、重启等)。
- [ ] 实现 `TaskScheduler` 模块 (替代原 `Worker` 类，支持定时触发)。
- [ ] 为上述模块编写 Rust 单元测试 (`cargo test`)。
- [ ] 实现系统托盘 (System Tray) 的后端逻辑。
**测试**: 运行 `cargo test` 通过所有逻辑测试；手动测试托盘图标显示。
**状态**: 未开始

## 阶段 3: 前端界面实现 (UI Implementation - Vue)
**目标**: 使用 Vue + Naive UI (或类似组件库) 复刻现有界面。
**成功标准**:
- [ ] 集成 UI 组件库 (推荐 Naive UI 或 Element Plus)。
- [ ] 实现 **主窗口** (任务列表展示、控制按钮)。
- [ ] 实现 **添加任务对话框** (选择时间、操作类型)。
- [ ] 实现 **设置页面** (开机自启、语言切换)。
- [ ] 前端状态管理 (使用 Pinia) 与 Rust 后端状态同步。
**测试**: 界面交互流畅，数据能够正确传递给后端。
**状态**: 未开始

## 阶段 4: 系统集成与完善 (Integration & Polish)
**目标**: 完成前后端对接，实现配置持久化和国际化。
**成功标准**:
- [ ] 对接所有 Rust Commands (添加任务、停止任务、立即执行)。
- [ ] 实现配置持久化 (`settings.ini` 或 JSON，使用 `tauri-plugin-store`)。
- [ ] 实现国际化 (i18n)，迁移现有的 `zh_CN` / `en_US` 翻译。
- [ ] 实现开机自启功能 (`tauri-plugin-autostart`)。
- [ ] 完善错误处理和用户提示。
**测试**: 完整的功能验收测试，模拟真实用户场景。
**状态**: 未开始

## 阶段 5: 打包与交付 (Packaging & Delivery)
**目标**: 生成最终的可执行文件，并清理旧代码。
**成功标准**:
- [ ] 配置 Tauri 构建参数 (图标、元数据)。
- [ ] 成功构建 Release 版本 (`.exe` / `.msi`)。
- [ ] (可选) 设置 GitHub Actions 自动构建。
- [ ] 归档旧的 C++ 源码到 `legacy/` 目录或删除。
**测试**: 在干净的 Windows 虚拟机中安装并运行，验证所有功能。
**状态**: 未开始
