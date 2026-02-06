<script setup lang="ts">
import { useTaskStore } from '../stores/taskStore'
import { storeToRefs } from 'pinia'

const store = useTaskStore()
const { tasks } = storeToRefs(store)

function formatDuration(seconds: number) {
  const d = Math.floor(seconds / 86400);
  const h = Math.floor((seconds % 86400) / 3600);
  const m = Math.floor((seconds % 3600) / 60);
  const s = seconds % 60;
  
  const pad = (num: number) => num.toString().padStart(2, '0');
  
  if (d > 0) {
      return `${d}d ${pad(h)}:${pad(m)}:${pad(s)}`;
  }
  return `${pad(h)}:${pad(m)}:${pad(s)}`;
}

function getTaskIcon(action: string) {
    switch (action) {
        case 'reboot':
            return 'M16.023 9.348h4.992v-.001M2.985 19.644v-4.992m0 0h4.992m-4.993 0l3.181 3.183a8.25 8.25 0 0013.803-3.7M4.031 9.865a8.25 8.25 0 0113.803-3.7l3.181 3.182m0-4.991v4.99';
        case 'sleep':
            return 'M21.752 15.002A9.718 9.718 0 0118 15.75c-5.385 0-9.75-4.365-9.75-9.75 0-1.33.266-2.597.748-3.752A9.753 9.753 0 003 11.25C3 16.635 7.365 21 12.75 21a9.753 9.753 0 009.002-5.998z';
        case 'lock':
            return 'M16.5 10.5V6.75a4.5 4.5 0 10-9 0v3.75m-.75 11.25h10.5a2.25 2.25 0 002.25-2.25v-6.75a2.25 2.25 0 00-2.25-2.25H6.75a2.25 2.25 0 00-2.25 2.25v6.75a2.25 2.25 0 002.25 2.25z';
        default: // shutdown
            return 'M5.636 5.636a9 9 0 1012.728 0M12 3v9';
    }
}
</script>

<template>
  <div class="task-list">
    <h3>Scheduled Tasks</h3>
    <div v-if="tasks.length === 0" class="empty-state">
      <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="currentColor" class="empty-icon">
        <path stroke-linecap="round" stroke-linejoin="round" d="M12 6v6h4.5m4.5 0a9 9 0 11-18 0 9 9 0 0118 0z" />
      </svg>
      <p>No active timers</p>
    </div>
    <ul v-else class="list-container">
      <li v-for="task in tasks" :key="task.id" class="task-item">
        <div class="task-content">
            <div class="task-icon-wrapper" :class="task.action">
                <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="currentColor" class="task-icon">
                    <path stroke-linecap="round" stroke-linejoin="round" :d="getTaskIcon(task.action)" />
                </svg>
            </div>
            <div class="task-details">
                <span class="task-type">{{ task.action }}</span>
                <span class="task-time">{{ formatDuration(task.remaining) }}</span>
            </div>
        </div>
        <button @click="store.removeTask(task.id)" class="remove-btn" title="Cancel Task">
            <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="currentColor" class="btn-icon">
                <path stroke-linecap="round" stroke-linejoin="round" d="M6 18L18 6M6 6l12 12" />
            </svg>
        </button>
      </li>
    </ul>
  </div>
</template>

<style scoped>
.task-list {
  width: 100%;
}

h3 {
  font-size: 1.1rem;
  font-weight: 600;
  color: #374151; /* gray-700 */
  margin-top: 0;
  margin-bottom: 1rem;
}

.empty-state {
    display: flex;
    flex-direction: column;
    align-items: center;
    justify-content: center;
    padding: 3rem 1rem;
    color: #9ca3af; /* gray-400 */
    border: 2px dashed #e5e7eb; /* gray-200 */
    border-radius: 0.75rem;
}

.empty-icon {
    width: 3rem;
    height: 3rem;
    margin-bottom: 0.5rem;
    opacity: 0.5;
}

.list-container {
  list-style: none;
  padding: 0;
  margin: 0;
  display: flex;
  flex-direction: column;
  gap: 0.75rem;
}

.task-item {
  display: flex;
  justify-content: space-between;
  align-items: center;
  padding: 1rem;
  border: 1px solid #e5e7eb; /* gray-200 */
  background-color: #f9fafb; /* gray-50 */
  border-radius: 0.75rem;
  transition: all 0.2s;
}

.task-item:hover {
    border-color: #d1d5db; /* gray-300 */
    box-shadow: 0 2px 4px rgba(0,0,0,0.05);
}

.task-content {
    display: flex;
    align-items: center;
    gap: 1rem;
}

.task-icon-wrapper {
    display: flex;
    align-items: center;
    justify-content: center;
    width: 2.5rem;
    height: 2.5rem;
    border-radius: 0.5rem;
    background-color: #e5e7eb;
}

.task-icon-wrapper.shutdown {
    background-color: #fee2e2; /* red-100 */
    color: #ef4444; /* red-500 */
}

.task-icon-wrapper.reboot {
    background-color: #dbeafe; /* blue-100 */
    color: #3b82f6; /* blue-500 */
}

.task-icon-wrapper.sleep {
    background-color: #fef3c7; /* amber-100 */
    color: #d97706; /* amber-500 */
}

.task-icon-wrapper.lock {
    background-color: #e0e7ff; /* indigo-100 */
    color: #4f46e5; /* indigo-500 */
}

.task-icon {
    width: 1.5rem;
    height: 1.5rem;
}

.task-details {
    display: flex;
    flex-direction: column;
}

.task-type {
    font-size: 0.875rem;
    font-weight: 600;
    text-transform: capitalize;
    color: #111827; /* gray-900 */
}

.task-time {
    font-family: ui-monospace, SFMono-Regular, Menlo, Monaco, Consolas, monospace;
    font-size: 0.875rem;
    color: #6b7280; /* gray-500 */
}

.remove-btn {
  display: flex;
  align-items: center;
  justify-content: center;
  background-color: transparent;
  color: #9ca3af; /* gray-400 */
  border: none;
  padding: 0.5rem;
  cursor: pointer;
  border-radius: 0.5rem;
  transition: all 0.2s;
}

.remove-btn:hover {
  background-color: #fee2e2; /* red-100 */
  color: #ef4444; /* red-500 */
}

.btn-icon {
      width: 1.25rem;
      height: 1.25rem;
  }
</style>

<style>
  :root.dark .task-list h3 {
      color: #d1d5db; /* gray-300 */
    }
  
    :root.dark .task-list .empty-state {
        border-color: #374151; /* gray-700 */
        color: #6b7280; /* gray-500 */
    }
  
    :root.dark .task-list .task-item {
        background-color: #1f2937; /* gray-800 */
        border-color: #374151; /* gray-700 */
    }
    
    :root.dark .task-list .task-item:hover {
        border-color: #4b5563; /* gray-600 */
    }
  
    :root.dark .task-list .task-type {
        color: #f3f4f6; /* gray-100 */
    }
  
    :root.dark .task-list .task-time {
        color: #9ca3af; /* gray-400 */
    }
    
    :root.dark .task-list .task-icon-wrapper.shutdown {
        background-color: #7f1d1d; /* red-900 */
        color: #f87171; /* red-400 */
    }
    
    :root.dark .task-list .task-icon-wrapper.reboot {
        background-color: #1e3a8a; /* blue-900 */
        color: #60a5fa; /* blue-400 */
    }
  
    :root.dark .task-list .task-icon-wrapper.sleep {
        background-color: #78350f; /* amber-900 */
        color: #fbbf24; /* amber-400 */
    }
  
    :root.dark .task-list .task-icon-wrapper.lock {
        background-color: #312e81; /* indigo-900 */
        color: #818cf8; /* indigo-400 */
    }
    
    :root.dark .task-list .remove-btn:hover {
        background-color: #7f1d1d; /* red-900 */
    }
</style>
