import { defineStore } from 'pinia'
import { ref } from 'vue'
import { invoke } from '@tauri-apps/api/core'
import type { Task } from '../types'

export const useTaskStore = defineStore('task', () => {
  const tasks = ref<Task[]>([])
  const timerId = ref<number | null>(null)

  async function addTask(input: Omit<Task, 'id' | 'createdAt' | 'remaining'>) {
    if (timerId.value) {
      clearInterval(timerId.value)
      timerId.value = null
    }

    const task: Task = {
      id: crypto.randomUUID(),
      createdAt: Date.now(),
      remaining: input.duration,
      ...input
    }
    tasks.value.push(task)
    await invoke('start_shutdown_timer', { seconds: task.duration })

    timerId.value = window.setInterval(() => {
      const currentTask = tasks.value.find(t => t.id === task.id)
      if (currentTask && currentTask.remaining > 0) {
        currentTask.remaining--
      } else {
        if (timerId.value) {
           clearInterval(timerId.value)
           timerId.value = null
        }
      }
    }, 1000)
  }

  async function removeTask(id: string) {
    tasks.value = tasks.value.filter(t => t.id !== id)
    await invoke('cancel_timer')
    if (tasks.value.length === 0 && timerId.value) {
       clearInterval(timerId.value)
       timerId.value = null
    }
  }

  return { tasks, addTask, removeTask }
}, {
  persist: true
})
