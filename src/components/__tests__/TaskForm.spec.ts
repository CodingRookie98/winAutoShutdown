import { mount } from '@vue/test-utils'
import { describe, it, expect, vi } from 'vitest'
import { createTestingPinia } from '@pinia/testing'
import { useTaskStore } from '../../stores/taskStore'
import TaskForm from '../TaskForm.vue'

// Mock Tauri API
vi.mock('@tauri-apps/api/core', () => ({
  invoke: vi.fn()
}))

describe('TaskForm.vue', () => {
  it('adds a task when form is submitted', async () => {
    const wrapper = mount(TaskForm, {
      global: {
        plugins: [createTestingPinia({
          createSpy: vi.fn,
          stubActions: false // We want to test that the action is called
        })],
      },
    })

    const store = useTaskStore()
    
    const input = wrapper.find('input[type="number"]')
    await input.setValue(120) // 2 minutes
    
    // Select an action (optional, default is shutdown)
    const select = wrapper.find('select')
    await select.setValue('reboot')

    await wrapper.find('form').trigger('submit.prevent')
    
    expect(store.addTask).toHaveBeenCalledTimes(1)
    expect(store.addTask).toHaveBeenCalledWith(expect.objectContaining({
      action: 'reboot',
      duration: 120
    }))
  })
})
