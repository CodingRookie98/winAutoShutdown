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
  it('adds a task in countdown mode', async () => {
    const wrapper = mount(TaskForm, {
      global: {
        plugins: [createTestingPinia({
          createSpy: vi.fn,
          stubActions: false
        })],
      },
    })

    const store = useTaskStore()
    
    // Default is countdown mode
    // Find inputs
    const inputs = wrapper.findAll('input[type="number"]')
    // 0: Days, 1: Hours, 2: Mins, 3: Secs
    await inputs[2].setValue(2) // 2 minutes
    await inputs[3].setValue(30) // 30 seconds
    
    // Select an action
    const select = wrapper.find('select')
    await select.setValue('reboot')

    await wrapper.find('form').trigger('submit.prevent')
    
    const expectedDuration = (2 * 60) + 30
    
    expect(store.addTask).toHaveBeenCalledTimes(1)
    expect(store.addTask).toHaveBeenCalledWith(expect.objectContaining({
      action: 'reboot',
      duration: expectedDuration
    }))
  })

  it('adds a task in specific time mode', async () => {
    // Mock window.alert
    window.alert = vi.fn()

    const wrapper = mount(TaskForm, {
      global: {
        plugins: [createTestingPinia({
          createSpy: vi.fn,
          stubActions: false
        })],
      },
    })

    const store = useTaskStore()
    
    // Switch to specific time mode
    const buttons = wrapper.findAll('.tabs button')
    await buttons[1].trigger('click') // Click "Specific Time"
    
    // Set time to 24 hours in the future to avoid timezone issues in test environment
    const future = new Date()
    future.setDate(future.getDate() + 1)
    
    // Format to YYYY-MM-DDTHH:mm
    const year = future.getFullYear()
    const month = String(future.getMonth() + 1).padStart(2, '0')
    const day = String(future.getDate()).padStart(2, '0')
    const hours = String(future.getHours()).padStart(2, '0')
    const minutes = String(future.getMinutes()).padStart(2, '0')
    const isoString = `${year}-${month}-${day}T${hours}:${minutes}`
    
    const input = wrapper.find('input[type="datetime-local"]')
    await input.setValue(isoString)
    
    await wrapper.find('form').trigger('submit.prevent')
    
    expect(window.alert).not.toHaveBeenCalled()
    
    // targetTimestamp will be based on the input string, which is parsed as local time by the browser/test env
    // We just check if it's called with a targetTimestamp
    expect(store.addTask).toHaveBeenCalledTimes(1)
    expect(store.addTask).toHaveBeenCalledWith(expect.objectContaining({
      action: 'shutdown', // Default
    }))
    
    // Verify targetTimestamp property exists
    // The spy function is a bit complex in Pinia testing with vitest
    // We can just verify it was called with an object that has targetTimestamp
    expect(store.addTask).toHaveBeenCalledWith(
        expect.objectContaining({
            targetTimestamp: expect.any(Number)
        })
    )
  })
})
