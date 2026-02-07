<script setup lang="ts">
import TaskForm from "./components/TaskForm.vue";
import TaskList from "./components/TaskList.vue";
import AboutModal from "./components/AboutModal.vue";
import { onMounted, ref } from "vue";
import { useTheme } from "./composables/useTheme";
import { useI18n } from 'vue-i18n'
import { availableLocales, type Locale } from './i18n'

const { isDark, toggleTheme, initTheme } = useTheme();
const { t, locale } = useI18n()
const showAbout = ref(false);

onMounted(() => {
  initTheme();
});

function toggleLanguage() {
  const newLocale: Locale = locale.value === 'en' ? 'zh-CN' : 'en'
  locale.value = newLocale
}
</script>

<template>
  <main class="container">
    <div class="card">
      <div class="header-row">
        <h1>{{ t('app.title') }}</h1>
        <div class="actions">
          <button class="icon-btn" @click="toggleLanguage" :title="t('language.title')">
            <span class="lang-indicator">{{ locale === 'en' ? 'EN' : '中' }}</span>
          </button>
          <button class="icon-btn" @click="toggleTheme" :title="isDark ? t('theme.switchToLight') : t('theme.switchToDark')">
            <!-- Sun icon -->
            <svg v-if="isDark" xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="currentColor" class="icon">
              <path stroke-linecap="round" stroke-linejoin="round" d="M12 3v2.25m6.364.386l-1.591 1.591M21 12h-2.25m-.386 6.364l-1.591-1.591M12 18.75V21m-4.773-4.227l-1.591 1.591M5.25 12H3m4.227-4.773L5.636 5.636M15.75 12a3.75 3.75 0 11-7.5 0 3.75 3.75 0 017.5 0z" />
            </svg>
            <!-- Moon icon -->
            <svg v-else xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="currentColor" class="icon">
              <path stroke-linecap="round" stroke-linejoin="round" d="M21.752 15.002A9.718 9.718 0 0118 15.75c-5.385 0-9.75-4.365-9.75-9.75 0-1.33.266-2.597.748-3.752A9.753 9.753 0 003 11.25C3 16.635 7.365 21 12.75 21a9.753 9.753 0 009.002-5.998z" />
            </svg>
          </button>
          <button class="icon-btn" @click="showAbout = true" :title="t('about.title')">
            <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="currentColor" class="icon">
              <path stroke-linecap="round" stroke-linejoin="round" d="M9.879 7.519c1.171-1.025 3.071-1.025 4.242 0 1.172 1.025 1.172 2.687 0 3.712-.203.179-.43.326-.67.442-.745.361-1.45.999-1.45 1.827v.75M21 12a9 9 0 11-18 0 9 9 0 0118 0zm-9 5.25h.008v.008H12v-.008z" />
            </svg>
          </button>
        </div>
      </div>
      
      <TaskForm />
      <div class="divider"></div>
      <TaskList />
    </div>

    <AboutModal :is-open="showAbout" @close="showAbout = false" />
  </main>
</template>

<style scoped>
.header-row {
  display: flex;
  justify-content: space-between;
  align-items: center;
  width: 100%;
  margin-bottom: 2rem;
}

h1 {
  font-size: 1.5rem;
  font-weight: 700;
  color: #111827; /* gray-900 */
  margin: 0;
}

.actions {
  display: flex;
  gap: 0.5rem;
}

.icon-btn {
  background: transparent;
  border: none;
  cursor: pointer;
  padding: 0.5rem;
  border-radius: 0.5rem;
  color: #6b7280; /* gray-500 */
  display: flex;
  align-items: center;
  justify-content: center;
  transition: all 0.2s;
  min-width: 2.25rem;
  height: 2.25rem;
}

.icon-btn:hover {
  background-color: #f3f4f6; /* gray-100 */
  color: #1f2937; /* gray-800 */
}

.icon {
  width: 1.25rem;
  height: 1.25rem;
}

.lang-indicator {
  font-size: 0.75rem;
  font-weight: 600;
}

.divider {
  height: 1px;
  background-color: #e5e7eb;
  margin: 2rem 0;
  width: 100%;
}
</style>
<style>
:root {
  font-family: 'Inter', -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, Helvetica, Arial, sans-serif;
  font-size: 16px;
  line-height: 1.5;
  font-weight: 400;

  color: #1f2937; /* gray-800 */
  background-color: #f3f4f6; /* gray-100 */

  font-synthesis: none;
  text-rendering: optimizeLegibility;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
}

body {
  margin: 0;
  min-height: 100vh;
}

.container {
  display: flex;
  justify-content: center;
  align-items: flex-start;
  min-height: 100vh;
  padding-top: 1.5rem;
  padding-bottom: 1.5rem;
}

.card {
  background-color: white;
  border-radius: 1rem;
  box-shadow: 0 4px 6px -1px rgba(0, 0, 0, 0.1), 0 2px 4px -1px rgba(0, 0, 0, 0.06);
  padding: 2rem;
  width: 100%;
  max-width: 460px;
  display: flex;
  flex-direction: column;
  align-items: center;
}

/* Dark mode overrides using class strategy */
:root.dark {
  color: #f9fafb; /* gray-50 */
  background-color: #111827; /* gray-900 */
}

:root.dark .card {
  background-color: #1f2937; /* gray-800 */
  box-shadow: 0 4px 6px -1px rgba(0, 0, 0, 0.5);
}

:root.dark h1 {
  color: #f9fafb;
}

:root.dark .divider {
  background-color: #374151; /* gray-700 */
}

:root.dark .icon-btn {
  color: #9ca3af;
}

:root.dark .icon-btn:hover {
  background-color: #374151;
  color: #f3f4f6;
}
</style>
