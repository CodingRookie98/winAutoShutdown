<script setup lang="ts">
import { useTaskStore } from '../stores/taskStore'
import { storeToRefs } from 'pinia'

const store = useTaskStore()
const { tasks } = storeToRefs(store)

function formatDuration(seconds: number) {
  return `${Math.floor(seconds / 60)}m ${seconds % 60}s`
}
</script>

<template>
  <div class="task-list">
    <h3>Scheduled Tasks</h3>
    <div v-if="tasks.length === 0" class="empty-state">No tasks scheduled</div>
    <ul v-else>
      <li v-for="task in tasks" :key="task.id" class="task-item">
        <span class="task-info">
          <strong>{{ task.type }}</strong> - {{ formatDuration(task.remaining) }}
        </span>
        <button @click="store.removeTask(task.id)" class="remove-btn">Cancel</button>
      </li>
    </ul>
  </div>
</template>

<style scoped>
.task-list {
  margin-top: 2rem;
  width: 100%;
  max-width: 400px;
  margin: 0 auto;
}

ul {
  list-style: none;
  padding: 0;
}

.task-item {
  display: flex;
  justify-content: space-between;
  align-items: center;
  padding: 0.5rem;
  border-bottom: 1px solid #ccc;
  background-color: #f9f9f9;
  margin-bottom: 0.5rem;
  border-radius: 4px;
}

.task-info {
  color: #333;
}

.remove-btn {
  background-color: #ff4444;
  color: white;
  border: none;
  padding: 0.25rem 0.5rem;
  cursor: pointer;
  border-radius: 4px;
}

.remove-btn:hover {
  background-color: #cc0000;
}
</style>
