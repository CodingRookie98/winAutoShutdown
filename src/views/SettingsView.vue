<template>
  <div class="settings-view">
    <!-- Language Section -->
    <section class="section">
      <h2>{{ t('settings.language') }}</h2>
      <div class="options">
        <button 
          :class="{ active: settings.locale === 'en' }" 
          @click="settings.locale = 'en'"
        >
          English
        </button>
        <button 
          :class="{ active: settings.locale === 'zh-CN' }" 
          @click="settings.locale = 'zh-CN'"
        >
          简体中文
        </button>
      </div>
    </section>

    <!-- Theme Section -->
    <section class="section">
      <h2>{{ t('settings.theme') }}</h2>
      <div class="options">
        <button :class="{ active: settings.theme === 'light' }" @click="settings.theme = 'light'">
          {{ t('theme.light') }}
        </button>
        <button :class="{ active: settings.theme === 'dark' }" @click="settings.theme = 'dark'">
          {{ t('theme.dark') }}
        </button>
        <button :class="{ active: settings.theme === 'auto' }" @click="settings.theme = 'auto'">
          {{ t('theme.auto') }}
        </button>
      </div>
    </section>

    <div class="divider"></div>

    <!-- About Section -->
    <section class="about-section">
      <h3>{{ t('about.title') }}</h3>
      <p class="description">{{ t('about.description') }}</p>
      
      <div class="info-row">
        <span class="label">{{ t('about.author') }}:</span>
        <a href="https://github.com/CodingRookie98" target="_blank" class="value link">CodingRookie98</a>
      </div>
      
      <div class="info-row">
        <span class="label">Version:</span>
        <span class="value">1.2.0</span>
      </div>

      <a href="https://github.com/CodingRookie98/winAutoShutdown" target="_blank" class="github-link">
        {{ t('about.github') }}
        <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="currentColor" class="icon">
          <path stroke-linecap="round" stroke-linejoin="round" d="M13.5 6H5.25A2.25 2.25 0 003 8.25v10.5A2.25 2.25 0 005.25 21h10.5A2.25 2.25 0 0018 18.75V10.5m-10.5 6L21 3m0 0h-5.25M21 3v5.25" />
        </svg>
      </a>

      <p class="copyright">{{ t('about.copyright', { year: new Date().getFullYear() }) }}</p>
    </section>
  </div>
</template>

<script setup lang="ts">
import { useSettingsStore } from '../stores/settings'
import { useI18n } from 'vue-i18n'

const settings = useSettingsStore()
const { t } = useI18n()
</script>

<style scoped>
.settings-view {
  width: 100%;
  display: flex;
  flex-direction: column;
  gap: 1.5rem;
}

.section h2 {
  font-size: 1rem;
  font-weight: 600;
  margin-bottom: 0.75rem;
  color: #374151; /* gray-700 */
}

.options {
  display: flex;
  background-color: #f3f4f6; /* gray-100 */
  padding: 0.25rem;
  border-radius: 0.5rem;
}

.options button {
  flex: 1;
  padding: 0.5rem;
  border: none;
  background: transparent;
  border-radius: 0.375rem;
  font-size: 0.875rem;
  font-weight: 500;
  color: #6b7280; /* gray-500 */
  cursor: pointer;
  transition: all 0.2s;
}

.options button.active {
  background-color: white;
  color: #111827; /* gray-900 */
  box-shadow: 0 1px 2px 0 rgba(0, 0, 0, 0.05);
}

.divider {
  height: 1px;
  background-color: #e5e7eb;
  width: 100%;
}

.about-section {
  text-align: center;
  display: flex;
  flex-direction: column;
  align-items: center;
  gap: 0.75rem;
}

.about-section h3 {
  font-size: 1.125rem;
  font-weight: 600;
  margin: 0;
  color: #111827; /* gray-900 */
}

.description {
  font-size: 0.875rem;
  color: #6b7280; /* gray-500 */
  line-height: 1.4;
  margin: 0;
}

.info-row {
  display: flex;
  gap: 0.5rem;
  font-size: 0.875rem;
}

.label {
  color: #6b7280; /* gray-500 */
}

.value {
  color: #111827; /* gray-900 */
  font-weight: 500;
}

.link {
  color: #3b82f6; /* blue-500 */
  text-decoration: none;
  cursor: pointer;
}

.link:hover {
  text-decoration: underline;
}

.github-link {
  display: inline-flex;
  align-items: center;
  gap: 0.25rem;
  color: #3b82f6; /* blue-500 */
  text-decoration: none;
  font-size: 0.875rem;
  font-weight: 500;
  margin-top: 0.5rem;
}

.github-link:hover {
  text-decoration: underline;
}

.icon {
  width: 1rem;
  height: 1rem;
}

.copyright {
  font-size: 0.75rem;
  color: #9ca3af; /* gray-400 */
  margin-top: 1rem;
}

/* Dark mode */
:root.dark .section h2,
:root.dark .about-section h3,
:root.dark .value {
  color: #f3f4f6; /* gray-100 */
}

:root.dark .options {
  background-color: #374151; /* gray-700 */
}

:root.dark .options button {
  color: #9ca3af; /* gray-400 */
}

:root.dark .options button.active {
  background-color: #1f2937; /* gray-800 */
  color: #f3f4f6; /* gray-100 */
}

:root.dark .divider {
  background-color: #374151; /* gray-700 */
}

:root.dark .description,
:root.dark .label,
:root.dark .copyright {
  color: #9ca3af; /* gray-400 */
}
</style>
