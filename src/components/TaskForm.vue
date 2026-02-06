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
    <div class="form-group">
      <label>Action:</label>
      <select v-model="type">
        <option value="shutdown">Shutdown</option>
        <option value="reboot">Reboot</option>
      </select>
    </div>
    
    <div class="form-group">
      <label>Duration (seconds):</label>
      <input type="number" v-model="duration" min="1" required />
    </div>
    
    <button type="submit">Start Timer</button>
  </form>
</template>

<style scoped>
.task-form {
  display: flex;
  flex-direction: column;
  gap: 1rem;
  max-width: 300px;
  margin: 0 auto;
}

.form-group {
  display: flex;
  flex-direction: column;
  align-items: flex-start;
}
</style>
