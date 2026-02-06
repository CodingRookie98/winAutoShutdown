import { setActivePinia, createPinia } from 'pinia'
import { describe, it, expect, beforeEach, vi } from 'vitest'
import { useTaskStore } from '../taskStore'
import { invoke } from '@tauri-apps/api/core'

// Mock Tauri API
vi.mock('@tauri-apps/api/core', () => ({
  invoke: vi.fn()
}))

describe('Task Store', () => {
  beforeEach(() => {
    setActivePinia(createPinia())
    vi.mocked(invoke).mockClear()
  })

  it('initializes with empty tasks', () => {
    const store = useTaskStore()
    expect(store.tasks).toEqual([])
  })

  it('adds a task', () => {
    const store = useTaskStore()
    const task = { action: 'shutdown' as const, duration: 60 }
    store.addTask(task)
    expect(store.tasks.length).toBe(1)
    expect(store.tasks[0].action).toBe('shutdown')
    expect(store.tasks[0].duration).toBe(60)
    expect(store.tasks[0].remaining).toBe(60)
    expect(store.tasks[0].id).toBeDefined()
  })

  // We temporarily disabled backend timer start in frontend
  // it('calls backend to start timer when adding task', async () => {
  //   const store = useTaskStore()
  //   const task = { action: 'shutdown' as const, duration: 60 }
  //   store.addTask(task)
  //   
  //   expect(invoke).toHaveBeenCalledWith('start_shutdown_timer', { seconds: 60 })
  // })

  it('removes a task', () => {
    const store = useTaskStore()
    store.addTask({ action: 'shutdown' as const, duration: 60 })
    const taskId = store.tasks[0].id
    store.removeTask(taskId)
    expect(store.tasks.length).toBe(0)
  })

  // We temporarily disabled backend timer cancellation
  // it('calls backend to cancel timer when removing task', async () => {
  //   const store = useTaskStore()
  //   store.addTask({ action: 'shutdown' as const, duration: 60 })
  //   const taskId = store.tasks[0].id
  //   
  //   vi.mocked(invoke).mockClear()
  //   
  //   store.removeTask(taskId)
  //   expect(invoke).toHaveBeenCalledWith('cancel_timer')
  // })
})
