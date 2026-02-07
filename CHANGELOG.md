# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.1.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

## [1.3.0] - 2026-02-07

### Added
- **Settings Page**: Dedicated settings view with persistent configuration.
- **SPA Routing**: Implemented `vue-router` for seamless navigation between Home and Settings.
- **Hibernate Support**: Added support for Windows Hibernate power state.
- **Author Info**: Updated author details with GitHub profile link.

### Changed
- **UI Refactoring**: 
  - Extracted Home logic to `HomeView`.
  - Moved Settings logic (Theme, Language) to `SettingsView`.
  - Replaced modal-based About section with a dedicated page.
  - Improved header navigation with dynamic Settings/Back buttons.
- **State Management**: Migrated manual `localStorage` logic to Pinia store (`useSettingsStore`) with auto-persistence.
- **Dependencies**: Added `vue-router`.

## [1.2.0] - 2026-02-07

### Added
- Multi-language support (English and Simplified Chinese)
- Language switcher in the header
- Internationalization for all UI components

### Changed
- Moved README_zh-CN.md to docs directory
- Refactored application using Rust + Tauri + Vue

### Removed
- Deleted temp_init directory

**Full Changelog**: https://github.com/Gangster-new/winAutoShutdown/compare/v1.1.0...v1.2.0
