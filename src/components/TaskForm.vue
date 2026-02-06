<script setup lang="ts">
import { ref } from 'vue'
import { useTaskStore } from '../stores/taskStore'

const store = useTaskStore()
const duration = ref(60)
const type = ref<'shutdown' | 'reboot'>('shutdown')

async function handleSubmit() {
  await store.addTask({
    type: type.value,
    duration: duration.value
  })
}
</script>

<template>
  <form @submit.prevent="handleSubmit" class="task-form">
    <div class="form-row">
      <div class="form-group">
        <label>Action</label>
        <div class="select-wrapper">
          <select v-model="type">
            <option value="shutdown">Shutdown</option>
            <option value="reboot">Reboot</option>
          </select>
          <svg class="select-icon" xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="currentColor">
            <path stroke-linecap="round" stroke-linejoin="round" d="M8.25 15L12 18.75 15.75 15m-7.5-6L12 5.25 15.75 9" />
          </svg>
        </div>
      </div>
      
      <div class="form-group">
        <label>Duration (sec)</label>
        <input type="number" v-model="duration" min="1" required placeholder="60" />
      </div>
    </div>
    
    <button type="submit" class="submit-btn">
      <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="currentColor" class="btn-icon">
        <path stroke-linecap="round" stroke-linejoin="round" d="M12 6v6h4.5m4.5 0a9 9 0 11-18 0 9 9 0 0118 0z" />
      </svg>
      Start Timer
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

.form-row {
  display: flex;
  gap: 1rem;
  width: 100%;
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

@media (prefers-color-scheme: dark) {
  label {
    color: #d1d5db; /* gray-300 */
  }

  input, select {
    background-color: #374151; /* gray-700 */
    border-color: #4b5563; /* gray-600 */
    color: white;
  }

  input:focus, select:focus {
    border-color: #60a5fa; /* blue-400 */
    box-shadow: 0 0 0 3px rgba(96, 165, 250, 0.2);
  }
}
</style>
