import { mount } from '@vue/test-utils'
import { describe, it, expect, vi } from 'vitest'
import { createTestingPinia } from '@pinia/testing'
import App from '../../App.vue'
import TaskForm from '../../components/TaskForm.vue'
import TaskList from '../../components/TaskList.vue'

// Mock Tauri API
vi.mock('@tauri-apps/api/core', () => ({
  invoke: vi.fn()
}))

describe('App.vue', () => {
  it('renders TaskForm and TaskList', () => {
    const wrapper = mount(App, {
      global: {
        plugins: [createTestingPinia({
          createSpy: vi.fn,
        })],
      },
    })

    expect(wrapper.findComponent(TaskForm).exists()).toBe(true)
    expect(wrapper.findComponent(TaskList).exists()).toBe(true)
    expect(wrapper.text()).toContain('WinAutoShutdown')
  })
})
