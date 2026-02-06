import { mount } from '@vue/test-utils'
import { describe, it, expect, vi } from 'vitest'
import { createTestingPinia } from '@pinia/testing'
import { useTaskStore } from '../../stores/taskStore'
import TaskList from '../TaskList.vue'

// Mock Tauri API
vi.mock('@tauri-apps/api/core', () => ({
  invoke: vi.fn()
}))

describe('TaskList.vue', () => {
  it('renders tasks from store', () => {
    const wrapper = mount(TaskList, {
      global: {
        plugins: [createTestingPinia({
          createSpy: vi.fn,
          initialState: {
            task: {
              tasks: [
                { id: '1', type: 'shutdown', duration: 60, remaining: 60, createdAt: 1000 },
                { id: '2', type: 'reboot', duration: 120, remaining: 120, createdAt: 2000 }
              ]
            }
          }
        })],
      },
    })

    const items = wrapper.findAll('.task-item')
    expect(items).toHaveLength(2)
    expect(items[0].text()).toContain('shutdown')
    expect(items[1].text()).toContain('reboot')
  })

  it('removes task when button is clicked', async () => {
    const wrapper = mount(TaskList, {
        global: {
          plugins: [createTestingPinia({
            createSpy: vi.fn,
            initialState: {
              task: {
                tasks: [
                  { id: '1', type: 'shutdown', duration: 60, remaining: 60, createdAt: 1000 }
                ]
              }
            },
            stubActions: false
          })],
        },
      })
  
      const store = useTaskStore()
      await wrapper.find('.remove-btn').trigger('click')
      
      expect(store.removeTask).toHaveBeenCalledWith('1')
  })
})
