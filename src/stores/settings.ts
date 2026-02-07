import { defineStore } from 'pinia'
import { ref, watch } from 'vue'
import { i18n } from '../i18n'

export type Theme = 'light' | 'dark' | 'auto'
export type Locale = 'en' | 'zh-CN'

export const useSettingsStore = defineStore('settings', () => {
  const theme = ref<Theme>('auto')
  const locale = ref<Locale>('en')

  // Apply Theme
  function applyTheme(newTheme: Theme) {
    const root = document.documentElement
    const isDark = newTheme === 'dark' || (newTheme === 'auto' && window.matchMedia('(prefers-color-scheme: dark)').matches)
    
    if (isDark) {
      root.classList.add('dark')
    } else {
      root.classList.remove('dark')
    }
  }

  // Apply Locale
  function applyLocale(newLocale: Locale) {
    // @ts-ignore: i18n type complexity
    i18n.global.locale.value = newLocale
  }

  // Watchers to sync state with side effects
  watch(theme, (val) => applyTheme(val), { immediate: true })
  watch(locale, (val) => applyLocale(val), { immediate: true })

  // Listen for system theme changes if in 'auto' mode
  window.matchMedia('(prefers-color-scheme: dark)').addEventListener('change', () => {
    if (theme.value === 'auto') {
      applyTheme('auto')
    }
  })

  return { theme, locale }
}, {
  persist: true
})
