<script setup lang="ts">
import TaskForm from "./components/TaskForm.vue";
import TaskList from "./components/TaskList.vue";
import { onMounted } from "vue";

onMounted(() => {
  console.log("App mounted successfully");
});
</script>

<template>
  <main class="container">
    <div class="card">
      <h1>WinAutoShutdown</h1>
      <TaskForm />
      <div class="divider"></div>
      <TaskList />
    </div>
  </main>
</template>

<style scoped>
.divider {
  height: 1px;
  background-color: #e5e7eb;
  margin: 2rem 0;
  width: 100%;
}
</style>
<style>
:root {
  font-family: 'Inter', -apple-system, BlinkMacSystemFont, "Segoe UI", Roboto, Helvetica, Arial, sans-serif;
  font-size: 16px;
  line-height: 1.5;
  font-weight: 400;

  color: #1f2937; /* gray-800 */
  background-color: #f3f4f6; /* gray-100 */

  font-synthesis: none;
  text-rendering: optimizeLegibility;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
}

body {
  margin: 0;
  min-height: 100vh;
}

.container {
  display: flex;
  justify-content: center;
  align-items: flex-start;
  min-height: 100vh;
  padding-top: 4rem;
  padding-bottom: 2rem;
}

.card {
  background-color: white;
  border-radius: 1rem;
  box-shadow: 0 4px 6px -1px rgba(0, 0, 0, 0.1), 0 2px 4px -1px rgba(0, 0, 0, 0.06);
  padding: 2.5rem;
  width: 100%;
  max-width: 480px;
  display: flex;
  flex-direction: column;
  align-items: center;
}

h1 {
  font-size: 1.5rem;
  font-weight: 700;
  color: #111827; /* gray-900 */
  margin-top: 0;
  margin-bottom: 2rem;
  text-align: center;
}

@media (prefers-color-scheme: dark) {
  :root {
    color: #f9fafb; /* gray-50 */
    background-color: #111827; /* gray-900 */
  }
  
  .card {
    background-color: #1f2937; /* gray-800 */
    box-shadow: 0 4px 6px -1px rgba(0, 0, 0, 0.5);
  }

  h1 {
    color: #f9fafb;
  }

  .divider {
    background-color: #374151; /* gray-700 */
  }
}
</style>