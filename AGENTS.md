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

## 5. Branch Management Standards

> 🔒 **CRITICAL RULE**: The `master` branch is **PROTECTED**. Direct commits, modifications, or force pushes to `master` are **STRICTLY PROHIBITED**.

### 🚫 Prohibited Actions
- **DO NOT** run `git push origin master`.
- **DO NOT** commit directly to the `master` branch.
- **DO NOT** edit files directly on `master` (including documentation).
- **DO NOT** use `git merge` to merge into `master` locally and push.

### ✅ Allowed Workflow
The `master` branch is reserved **exclusively** for production-ready code that has passed all tests and reviews.

1.  **Source**: Merges must originate from `dev` (development) or `release/*` branches.
2.  **Mechanism**: Changes must be introduced via **Pull Requests (PRs)** or **Merge Requests (MRs)**.
3.  **Requirements**:
    - Pass CI/CD pipelines (Build & Test).
    - Receive Code Review approval.
    - Pass Quality Gate checks.

### 🚨 Enforcement & Consequences
- **Automatic Rejection**: Push attempts to `master` will be rejected by the remote repository.
- **Rollback**: Any accidental bypass will trigger an automatic rollback.
- **Alerts**: Violations trigger immediate security alerts to the team lead.

### 📝 Example Workflow

**Incorrect (Prohibited):**
```bash
# ❌ NEVER DO THIS
git checkout master
git add .
git commit -m "quick fix"
git push origin master
```

**Correct (Required):**
```bash
# ✅ ALWAYS DO THIS
git checkout -b feature/my-feature
# ... make changes ...
git commit -m "feat: add new feature"
git push origin feature/my-feature
# -> Go to GitHub/GitLab and open a PR to 'dev'
```

## 6. File Operations
- **Renaming/Moving**: ALWAYS use `git mv` for renaming or moving files to preserve version history.
