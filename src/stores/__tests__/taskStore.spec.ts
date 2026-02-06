import { setActivePinia, createPinia } from 'pinia'
import { describe, it, expect, beforeEach, afterEach, vi } from 'vitest'
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
    vi.useFakeTimers()
  })

  afterEach(() => {
    vi.useRealTimers()
  })

  it('initializes with empty tasks', () => {
    const store = useTaskStore()
    expect(store.tasks).toEqual([])
  })

  it('adds a task with duration', () => {
    const store = useTaskStore()
    const task = { action: 'shutdown' as const, duration: 60 }
    store.addTask(task)
    expect(store.tasks.length).toBe(1)
    expect(store.tasks[0].action).toBe('shutdown')
    expect(store.tasks[0].duration).toBe(60)
    expect(store.tasks[0].targetTimestamp).toBeDefined()
    // remaining might be 59 or 60 depending on ms precision, usually 60 initially
    expect(store.tasks[0].remaining).toBeGreaterThanOrEqual(59) 
    expect(store.tasks[0].id).toBeDefined()
  })

  it('adds a task with targetTimestamp', () => {
    const store = useTaskStore()
    const now = Date.now()
    const target = now + 60000
    const task = { action: 'reboot' as const, targetTimestamp: target }
    store.addTask(task)
    expect(store.tasks.length).toBe(1)
    expect(store.tasks[0].action).toBe('reboot')
    expect(store.tasks[0].targetTimestamp).toBe(target)
    expect(store.tasks[0].remaining).toBeGreaterThanOrEqual(59)
  })

  it('removes a task', () => {
    const store = useTaskStore()
    store.addTask({ action: 'shutdown' as const, duration: 60 })
    const taskId = store.tasks[0].id
    store.removeTask(taskId)
    expect(store.tasks.length).toBe(0)
  })
})
