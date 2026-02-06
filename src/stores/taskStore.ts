import { defineStore } from 'pinia'
import { ref } from 'vue'
import { invoke } from '@tauri-apps/api/core'
import type { Task, SystemAction } from '../types'

export const useTaskStore = defineStore('task', () => {
  const tasks = ref<Task[]>([])
  const timerId = ref<number | null>(null)

  async function executeAction(action: SystemAction) {
    try {
      console.log(`Executing action: ${action}`);
      await invoke('execute_system_action', { action })
    } catch (e) {
      console.error('Failed to execute action:', e)
    }
  }

  async function addTask(input: { action: SystemAction, duration?: number, targetTimestamp?: number }) {
    if (timerId.value) {
      clearInterval(timerId.value)
      timerId.value = null
    }
    // Clear existing tasks to ensure only one runs
    tasks.value = []
    
    // TODO: Re-enable backend timer when it supports actions
    // await invoke('cancel_timer')

    let target = input.targetTimestamp;
    if (!target && input.duration) {
        target = Date.now() + input.duration * 1000;
    }
    
    if (!target) {
        console.error("Invalid task input: missing duration or targetTimestamp");
        return;
    }

    const task: Task = {
      id: crypto.randomUUID(),
      createdAt: Date.now(),
      action: input.action,
      targetTimestamp: target,
      duration: input.duration,
      remaining: Math.max(0, Math.floor((target - Date.now()) / 1000))
    }
    tasks.value.push(task)
    
    // await invoke('start_shutdown_timer', { seconds: task.duration })

    timerId.value = window.setInterval(async () => {
      const currentTask = tasks.value.find(t => t.id === task.id)
      if (!currentTask) {
          if (timerId.value) { clearInterval(timerId.value); timerId.value = null; }
          return;
      }
      
      const now = Date.now();
      if (currentTask.targetTimestamp > now) {
        currentTask.remaining = Math.floor((currentTask.targetTimestamp - now) / 1000);
      } else {
        // Expired
        if (timerId.value) {
           clearInterval(timerId.value)
           timerId.value = null
        }
        await executeAction(currentTask.action)
        removeTask(currentTask.id)
      }
    }, 1000)
  }

  async function removeTask(id: string) {
    tasks.value = tasks.value.filter(t => t.id !== id)
    // await invoke('cancel_timer')
    if (tasks.value.length === 0 && timerId.value) {
       clearInterval(timerId.value)
       timerId.value = null
    }
  }

  return { tasks, addTask, removeTask }
}, {
  persist: true
})
