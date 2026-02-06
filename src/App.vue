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
    <h1>WinAutoShutdown</h1>
    <TaskForm />
    <TaskList />
  </main>
</template>

<style scoped>
</style>
<style>
:root {
  font-family: Inter, Avenir, Helvetica, Arial, sans-serif;
  font-size: 16px;
  line-height: 24px;
  font-weight: 400;

  color: #0f0f0f;
  background-color: #f6f6f6;

  font-synthesis: none;
  text-rendering: optimizeLegibility;
  -webkit-font-smoothing: antialiased;
  -moz-osx-font-smoothing: grayscale;
  -webkit-text-size-adjust: 100%;
}

.container {
  margin: 0;
  padding-top: 5vh;
  display: flex;
  flex-direction: column;
  justify-content: flex-start;
  text-align: center;
  min-height: 100vh;
}

h1 {
  text-align: center;
  margin-bottom: 2rem;
}

@media (prefers-color-scheme: dark) {
  :root {
    color: #f6f6f6;
    background-color: #2f2f2f;
  }
}

input,
button,
select {
  border-radius: 8px;
  border: 1px solid transparent;
  padding: 0.6em 1.2em;
  font-size: 1em;
  font-weight: 500;
  font-family: inherit;
  color: #0f0f0f;
  background-color: #ffffff;
  transition: border-color 0.25s;
  box-shadow: 0 2px 2px rgba(0, 0, 0, 0.2);
}

button {
  cursor: pointer;
}

button:hover {
  border-color: #396cd8;
}
button:active {
  border-color: #396cd8;
  background-color: #e8e8e8;
}

input,
button,
select {
  outline: none;
}
</style>