# Implementation Plan: Settings Page & UI Refactoring

## Phase 1: Dependencies & Routing Setup
**Goal:** Establish a proper SPA (Single Page Application) structure using `vue-router`.

- [ ] **Install `vue-router`**: Add the router package to the project.
- [ ] **Setup Router**:
    - Create `src/router/index.ts`.
    - Define routes:
        - `/`: `HomeView` (Existing functionality).
        - `/settings`: `SettingsView` (New page).
- [ ] **Create View Components**:
    - Extract existing `App.vue` content into `src/views/HomeView.vue`.
    - Create a placeholder `src/views/SettingsView.vue`.
- [ ] **Update `App.vue`**: Replace direct component usage with `<router-view>` and implement a persistent layout (if needed, or keep layout in views).

## Phase 2: Store Implementation (Preferences)
**Goal:** Centralize user preferences (Theme, Language) for easier management across pages.

- [ ] **Create `useSettingsStore`**:
    - Manage `theme` state ('light' | 'dark').
    - Manage `locale` state ('en' | 'zh-CN').
    - Use `pinia-plugin-persistedstate` to save settings automatically.
- [ ] **Refactor `useTheme`**: Deprecate or integrate existing `useTheme` logic into the new store to avoid duplication.

## Phase 3: Settings Page UI
**Goal:** Create a user-friendly settings interface.

- [ ] **Design `SettingsView.vue`**:
    - **Header**: "Settings" title with a "Back" button (to Home).
    - **Section 1: General**:
        - Language Selector (Dropdown or Segmented Control).
    - **Section 2: Appearance**:
        - Theme Mode (Light / Dark / System - optional).
    - **Section 3: About**:
        - Version info (from `package.json` or Tauri config).
        - GitHub link.
        - Author info.

## Phase 4: Main Header Updates
**Goal:** Clean up the main view and link to settings.

- [ ] **Update `HomeView` Header**:
    - Keep **Theme Toggle** (as requested: "one button for theme").
    - **Remove** direct Language Toggle (move to Settings).
    - **Remove** About Button (content moved to Settings > About section).
    - **Add Settings Button**: A gear icon button that navigates to `/settings`.

## Phase 5: Verification
**Goal:** Ensure all requirements are met and no regressions.

- [ ] **Test Routing**: Navigation between Home and Settings works smoothly.
- [ ] **Test Persistence**: Refreshing the app retains the chosen language and theme.
- [ ] **Test Functionality**:
    - Theme toggles correctly from both Home button and Settings page.
    - Language changes immediately reflect across the app.
- [ ] **Lint & Build**: Ensure code quality standards.
