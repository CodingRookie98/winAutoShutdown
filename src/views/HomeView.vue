<template>
  <div class="home-view">
    <TaskForm />
    <div class="divider"></div>
    <TaskList />
  </div>
</template>

<script setup lang="ts">
import TaskForm from "../components/TaskForm.vue";
import TaskList from "../components/TaskList.vue";
</script>

<style scoped>
.home-view {
  width: 100%;
  display: flex;
  flex-direction: column;
}

.divider {
  height: 1px;
  background-color: #e5e7eb;
  margin: 2rem 0;
  width: 100%;
}
:root.dark .divider {
  background-color: #374151;
}
</style>
