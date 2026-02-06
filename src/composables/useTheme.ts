import { ref, watchEffect } from 'vue'

const isDark = ref(false)

// Initialize theme from system preference or local storage
const initTheme = () => {
  const storedTheme = localStorage.getItem('theme')
  if (storedTheme) {
    isDark.value = storedTheme === 'dark'
  } else {
    isDark.value = window.matchMedia('(prefers-color-scheme: dark)').matches
  }
}

// Watch for changes and update DOM
watchEffect(() => {
  const root = document.documentElement
  if (isDark.value) {
    root.classList.add('dark')
    try { localStorage.setItem('theme', 'dark') } catch (e) { /* ignore */ }
  } else {
    root.classList.remove('dark')
    try { localStorage.setItem('theme', 'light') } catch (e) { /* ignore */ }
  }
})

export function useTheme() {
  const toggleTheme = () => {
    isDark.value = !isDark.value
  }

  return {
    isDark,
    toggleTheme,
    initTheme
  }
}
