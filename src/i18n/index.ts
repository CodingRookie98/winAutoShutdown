import { createI18n } from 'vue-i18n'
import en from './locales/en.json'
import zhCN from './locales/zh-CN.json'

export type Locale = 'en' | 'zh-CN'

export const i18n = createI18n({
  legacy: false,
  locale: 'en',
  fallbackLocale: 'en',
  messages: {
    en,
    'zh-CN': zhCN
  }
})

export const availableLocales = [
  { code: 'en', name: 'English' },
  { code: 'zh-CN', name: '简体中文' }
] as const
