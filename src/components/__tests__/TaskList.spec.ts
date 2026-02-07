import { mount } from '@vue/test-utils'
import { describe, it, expect, vi } from 'vitest'
import { createTestingPinia } from '@pinia/testing'
import { createTestI18n } from '../../i18n/test-utils'
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
        plugins: [
          createTestingPinia({
            createSpy: vi.fn,
            initialState: {
              task: {
                tasks: [
                  { id: '1', action: 'shutdown', duration: 60, remaining: 60, createdAt: 1000 },
                  { id: '2', action: 'reboot', duration: 120, remaining: 120, createdAt: 2000 }
                ]
              }
            }
          }),
          createTestI18n()
        ],
      },
    })

    const items = wrapper.findAll('.task-item')
    expect(items).toHaveLength(2)
    expect(items[0].text()).toContain('Shutdown')
    expect(items[1].text()).toContain('Reboot')
  })

  it('removes task when button is clicked', async () => {
    const wrapper = mount(TaskList, {
        global: {
          plugins: [
            createTestingPinia({
              createSpy: vi.fn,
              initialState: {
                task: {
                  tasks: [
                    { id: '1', action: 'shutdown', duration: 60, remaining: 60, createdAt: 1000 }
                  ]
                }
              },
              stubActions: false
            }),
            createTestI18n()
          ],
        },
      })
  
      const store = useTaskStore()
      await wrapper.find('.remove-btn').trigger('click')
      
      expect(store.removeTask).toHaveBeenCalledWith('1')
  })
})
