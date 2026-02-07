<script setup lang="ts">
import { useSettingsStore } from "./stores/settings";
import { useI18n } from 'vue-i18n'
import { useRouter, useRoute } from 'vue-router'

const { t } = useI18n()
const router = useRouter()
const route = useRoute()

// Initialize settings store to apply theme
useSettingsStore()

function goSettings() {
  router.push('/settings')
}

function goBack() {
  router.back()
}
</script>

<template>
  <main class="container">
    <div class="card">
      <div class="header-row">
        <h1>{{ t('app.title') }}</h1>
        <div class="actions">
          <button v-if="route.path === '/'" class="icon-btn" @click="goSettings" :title="t('settings.title')">
            <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="currentColor" class="icon">
              <path stroke-linecap="round" stroke-linejoin="round" d="M9.594 3.94c.09-.542.56-.94 1.11-.94h2.593c.55 0 1.02.398 1.11.94l.213 1.281c.063.374.313.686.645.87.074.04.147.083.22.127.324.196.72.257 1.075.124l1.217-.456a1.125 1.125 0 011.37.49l1.296 2.247a1.125 1.125 0 01-.26 1.431l-1.003.827c-.293.24-.438.613-.431.992a6.759 6.759 0 010 .255c-.007.378.138.75.43.99l1.005.828c.424.35.534.954.26 1.43l-1.298 2.247a1.125 1.125 0 01-1.369.491l-1.217-.456c-.355-.133-.75-.072-1.076.124a6.57 6.57 0 01-.22.128c-.331.183-.581.495-.644.869l-.213 1.28c-.09.543-.56.941-1.11.941h-2.594c-.55 0-1.02-.398-1.11-.94l-.213-1.281c-.062-.374-.312-.686-.644-.87a6.52 6.52 0 01-.22-.127c-.325-.196-.72-.257-1.076-.124l-1.217.456a1.125 1.125 0 01-1.369-.49l-1.297-2.247a1.125 1.125 0 01.26-1.431l1.004-.827c.292-.24.437-.613.43-.992a6.932 6.932 0 010-.255c.007-.378-.138-.75-.43-.99l-1.004-.828a1.125 1.125 0 01-.26-1.43l1.297-2.247a1.125 1.125 0 011.37-.491l1.216.456c.356.133.751.072 1.076-.124.072-.044.146-.087.22-.128.332-.183.582-.495.644-.869l.214-1.281z" />
              <path stroke-linecap="round" stroke-linejoin="round" d="M15 12a3 3 0 11-6 0 3 3 0 016 0z" />
            </svg>
          </button>
          <button v-else-if="route.path === '/settings'" class="icon-btn" @click="goBack" :title="t('common.back')">
            <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="currentColor" class="icon">
              <path stroke-linecap="round" stroke-linejoin="round" d="M10.5 19.5L3 12m0 0l7.5-7.5M3 12h18" />
            </svg>
          </button>
        </div>
      </div>

      <router-view v-slot="{ Component }">
        <transition name="fade" mode="out-in">
          <component :is="Component" />
        </transition>
      </router-view>
    </div>
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

/* Transition styles */
.fade-enter-active,
.fade-leave-active {
  transition: opacity 0.2s ease;
}

.fade-enter-from,
.fade-leave-to {
  opacity: 0;
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

:root.dark .icon-btn {
  color: #9ca3af;
}

:root.dark .icon-btn:hover {
  background-color: #374151;
  color: #f3f4f6;
}
</style>
