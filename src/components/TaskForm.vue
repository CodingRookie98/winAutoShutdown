<script setup lang="ts">
import { ref } from 'vue'
import { useI18n } from 'vue-i18n'
import { useTaskStore } from '../stores/taskStore'
import type { SystemAction } from '../types'

const store = useTaskStore()
const { t } = useI18n()
const action = ref<SystemAction>('shutdown')
const mode = ref<'countdown' | 'specific'>('countdown')

// Countdown inputs
const days = ref(0)
const hours = ref(0)
const minutes = ref(1) // Default to 1 minute
const seconds = ref(0)

// Specific time input
const specificTime = ref('')

// Initialize specificTime with current time + 1 hour for better UX
const now = new Date();
now.setHours(now.getHours() + 1);
now.setMinutes(0);
now.setSeconds(0);
// Format to YYYY-MM-DDTHH:mm for datetime-local input
const isoString = now.toISOString();
specificTime.value = isoString.substring(0, 16); // Remove seconds and milliseconds

async function handleSubmit() {
  if (mode.value === 'countdown') {
    const totalSeconds = 
      (days.value * 86400) + 
      (hours.value * 3600) + 
      (minutes.value * 60) + 
      seconds.value;
      
    if (totalSeconds <= 0) return;
    
    await store.addTask({
      action: action.value,
      duration: totalSeconds
    })
  } else {
    if (!specificTime.value) return;
    const target = new Date(specificTime.value).getTime();
    if (target <= Date.now()) {
        alert(t('taskForm.error.futureTime'));
        return;
    }
    
    await store.addTask({
      action: action.value,
      targetTimestamp: target
    })
  }
}
</script>

<template>
  <form @submit.prevent="handleSubmit" class="task-form">
    <div class="form-group">
        <label>{{ t('taskForm.action') }}</label>
        <div class="select-wrapper">
          <select v-model="action">
            <option value="shutdown">{{ t('actions.shutdown') }}</option>
            <option value="reboot">{{ t('actions.reboot') }}</option>
            <option value="sleep">{{ t('actions.sleep') }}</option>
            <option value="lock">{{ t('actions.lock') }}</option>
          </select>
          <svg class="select-icon" xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="currentColor">
            <path stroke-linecap="round" stroke-linejoin="round" d="M8.25 15L12 18.75 15.75 15m-7.5-6L12 5.25 15.75 9" />
          </svg>
        </div>
    </div>

    <div class="tabs">
        <button type="button" :class="{ active: mode === 'countdown' }" @click="mode = 'countdown'">{{ t('taskForm.countdown') }}</button>
        <button type="button" :class="{ active: mode === 'specific' }" @click="mode = 'specific'">{{ t('taskForm.specificTime') }}</button>
    </div>

    <div v-if="mode === 'countdown'" class="countdown-inputs">
        <div class="time-field">
            <label>{{ t('taskForm.days') }}</label>
            <input type="number" v-model="days" min="0" placeholder="0" />
        </div>
        <div class="time-field">
            <label>{{ t('taskForm.hours') }}</label>
            <input type="number" v-model="hours" min="0" max="23" placeholder="0" />
        </div>
        <div class="time-field">
            <label>{{ t('taskForm.minutes') }}</label>
            <input type="number" v-model="minutes" min="0" max="59" placeholder="0" />
        </div>
        <div class="time-field">
            <label>{{ t('taskForm.seconds') }}</label>
            <input type="number" v-model="seconds" min="0" max="59" placeholder="0" />
        </div>
    </div>

    <div v-else class="specific-input">
        <div class="form-group">
            <label>{{ t('taskForm.targetTime') }}</label>
            <input type="datetime-local" v-model="specificTime" required />
        </div>
    </div>
    
    <button type="submit" class="submit-btn">
      <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="currentColor" class="btn-icon">
        <path stroke-linecap="round" stroke-linejoin="round" d="M12 6v6h4.5m4.5 0a9 9 0 11-18 0 9 9 0 0118 0z" />
      </svg>
      {{ t('taskForm.startTimer') }}
    </button>
  </form>
</template>

<style scoped>
.task-form {
  display: flex;
  flex-direction: column;
  gap: 1.5rem;
  width: 100%;
}

.tabs {
    display: flex;
    background-color: #f3f4f6; /* gray-100 */
    padding: 0.25rem;
    border-radius: 0.5rem;
}

.tabs button {
    flex: 1;
    padding: 0.5rem;
    border: none;
    background: transparent;
    border-radius: 0.375rem;
    font-size: 0.875rem;
    font-weight: 500;
    color: #6b7280; /* gray-500 */
    cursor: pointer;
    transition: all 0.2s;
}

.tabs button.active {
    background-color: white;
    color: #111827; /* gray-900 */
    box-shadow: 0 1px 2px 0 rgba(0, 0, 0, 0.05);
}

.countdown-inputs {
    display: flex;
    gap: 0.5rem;
}

.time-field {
    display: flex;
    flex-direction: column;
    gap: 0.25rem;
    flex: 1;
}

.time-field label {
    font-size: 0.75rem;
    color: #6b7280; /* gray-500 */
    text-align: center;
}

.time-field input {
    text-align: center;
    padding: 0.5rem;
}

.form-group {
  display: flex;
  flex-direction: column;
  gap: 0.5rem;
  flex: 1;
}

label {
  font-size: 0.875rem;
  font-weight: 500;
  color: #374151; /* gray-700 */
}

input, select {
  width: 100%;
  padding: 0.75rem 1rem;
  border-radius: 0.5rem;
  border: 1px solid #d1d5db; /* gray-300 */
  background-color: #fff;
  font-size: 0.95rem;
  color: #111827; /* gray-900 */
  transition: all 0.2s;
  appearance: none;
  box-sizing: border-box;
}

input:focus, select:focus {
  outline: none;
  border-color: #3b82f6; /* blue-500 */
  box-shadow: 0 0 0 3px rgba(59, 130, 246, 0.1);
}

.select-wrapper {
  position: relative;
}

.select-icon {
  position: absolute;
  right: 0.75rem;
  top: 50%;
  transform: translateY(-50%);
  width: 1rem;
  height: 1rem;
  color: #6b7280; /* gray-500 */
  pointer-events: none;
}

.submit-btn {
  display: flex;
  align-items: center;
  justify-content: center;
  gap: 0.5rem;
  background-color: #3b82f6; /* blue-500 */
  color: white;
  border: none;
  padding: 0.875rem;
  border-radius: 0.5rem;
  font-weight: 600;
  font-size: 1rem;
  cursor: pointer;
  transition: background-color 0.2s;
  width: 100%;
  margin-top: 0.5rem;
}

.submit-btn:hover {
  background-color: #2563eb; /* blue-600 */
}

.submit-btn:active {
  background-color: #1d4ed8; /* blue-700 */
  transform: translateY(1px);
}

.btn-icon {
    width: 1.25rem;
    height: 1.25rem;
  }
</style>

<style>
  :root.dark .task-form label {
    color: #d1d5db; /* gray-300 */
  }

  :root.dark .task-form input, :root.dark .task-form select {
    background-color: #374151; /* gray-700 */
    border-color: #4b5563; /* gray-600 */
    color: white;
  }

  :root.dark .task-form input:focus, :root.dark .task-form select:focus {
    border-color: #60a5fa; /* blue-400 */
    box-shadow: 0 0 0 3px rgba(96, 165, 250, 0.2);
  }

  :root.dark .task-form .tabs {
      background-color: #374151; /* gray-700 */
  }

  :root.dark .task-form .tabs button {
      color: #9ca3af; /* gray-400 */
  }

  :root.dark .task-form .tabs button.active {
      background-color: #1f2937; /* gray-800 */
      color: #f3f4f6; /* gray-100 */
  }
  
  :root.dark .task-form .time-field label {
      color: #9ca3af; /* gray-400 */
  }
</style>
