import { mount } from '@vue/test-utils'
import { describe, it, expect, vi } from 'vitest'
import { createTestingPinia } from '@pinia/testing'
import { createTestI18n } from '../../i18n/test-utils'
import App from '../../App.vue'
import TaskForm from '../../components/TaskForm.vue'
import TaskList from '../../components/TaskList.vue'

// Mock Tauri API
vi.mock('@tauri-apps/api/core', () => ({
  invoke: vi.fn()
}))

// Mock vue-router
vi.mock('vue-router', () => ({
    useRouter: () => ({
        push: vi.fn(),
        back: vi.fn()
    }),
    useRoute: () => ({
        path: '/'
    })
}))

describe('App.vue', () => {
  it('renders TaskForm and TaskList', async () => {
    // Mock localStorage and matchMedia
    const localStorageMock = {
        getItem: vi.fn(() => null),
        setItem: vi.fn(),
        clear: vi.fn(),
        removeItem: vi.fn(),
        key: vi.fn(),
        length: 0
    };

    vi.stubGlobal('localStorage', localStorageMock);

    vi.stubGlobal('matchMedia', vi.fn().mockImplementation(query => ({
        matches: false,
        media: query,
        onchange: null,
        addListener: vi.fn(), // deprecated
        removeListener: vi.fn(), // deprecated
        addEventListener: vi.fn(),
        removeEventListener: vi.fn(),
        dispatchEvent: vi.fn(),
    })));

    const wrapper = mount(App, {
      global: {
        plugins: [
          createTestingPinia({
            createSpy: vi.fn,
          }),
          createTestI18n()
        ],
      },
    })

    expect(wrapper.findComponent(TaskForm).exists()).toBe(true)
    expect(wrapper.findComponent(TaskList).exists()).toBe(true)
    expect(wrapper.text()).toContain('WinAutoShutdown')
  })
})
