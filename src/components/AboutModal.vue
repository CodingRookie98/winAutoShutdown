<script setup lang="ts">
import { openUrl } from '@tauri-apps/plugin-opener';

defineProps<{
  isOpen: boolean
}>()

defineEmits<{
  (e: 'close'): void
}>()

async function openLink(url: string) {
  try {
    await openUrl(url);
  } catch (error) {
    console.error('Failed to open link:', error);
  }
}
</script>

<template>
  <div v-if="isOpen" class="modal-overlay" @click="$emit('close')">
    <div class="modal-content" @click.stop>
      <div class="modal-header">
        <h2>About</h2>
        <button class="close-btn" @click="$emit('close')">
          <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="currentColor" class="icon">
            <path stroke-linecap="round" stroke-linejoin="round" d="M6 18L18 6M6 6l12 12" />
          </svg>
        </button>
      </div>
      
      <div class="modal-body">
        <div class="logo-area">
          <svg xmlns="http://www.w3.org/2000/svg" fill="none" viewBox="0 0 24 24" stroke-width="1.5" stroke="currentColor" class="app-logo">
            <path stroke-linecap="round" stroke-linejoin="round" d="M5.636 5.636a9 9 0 1012.728 0M12 3v9" />
          </svg>
          <h3>WinAutoShutdown</h3>
          <span class="version">v1.2.0</span>
        </div>
        
        <p class="description">
          A modern, lightweight utility for scheduling system power actions on Windows.
          Built with Tauri, Rust, and Vue 3.
        </p>
        
        <div class="links">
          <a href="#" @click.prevent="openLink('https://github.com/CodingRookie98/winAutoShutdown')">GitHub Repository</a>
          <span class="separator">|</span>
          <a href="#" @click.prevent="openLink('https://github.com/CodingRookie98')">Author</a>
        </div>
        
        <div class="footer">
          &copy; {{ new Date().getFullYear() }} WinAutoShutdown Team
        </div>
      </div>
    </div>
  </div>
</template>

<style scoped>
.modal-overlay {
  position: fixed;
  top: 0;
  left: 0;
  width: 100%;
  height: 100%;
  background-color: rgba(0, 0, 0, 0.5);
  display: flex;
  align-items: center;
  justify-content: center;
  z-index: 100;
  backdrop-filter: blur(2px);
}

.modal-content {
  background-color: white;
  border-radius: 1rem;
  width: 90%;
  max-width: 400px;
  box-shadow: 0 20px 25px -5px rgba(0, 0, 0, 0.1), 0 10px 10px -5px rgba(0, 0, 0, 0.04);
  overflow: hidden;
  animation: modal-pop 0.2s ease-out;
}

@keyframes modal-pop {
  from { opacity: 0; transform: scale(0.95); }
  to { opacity: 1; transform: scale(1); }
}

.modal-header {
  display: flex;
  justify-content: space-between;
  align-items: center;
  padding: 1rem 1.5rem;
  border-bottom: 1px solid #e5e7eb;
}

h2 {
  margin: 0;
  font-size: 1.25rem;
  font-weight: 600;
  color: #111827;
}

.close-btn {
  background: transparent;
  border: none;
  cursor: pointer;
  padding: 0.5rem;
  border-radius: 0.375rem;
  color: #6b7280;
  display: flex;
  align-items: center;
  justify-content: center;
  transition: all 0.2s;
}

.close-btn:hover {
  background-color: #f3f4f6;
  color: #1f2937;
}

.icon {
  width: 1.25rem;
  height: 1.25rem;
}

.modal-body {
  padding: 2rem 1.5rem;
  display: flex;
  flex-direction: column;
  align-items: center;
  text-align: center;
}

.logo-area {
  display: flex;
  flex-direction: column;
  align-items: center;
  margin-bottom: 1.5rem;
}

.app-logo {
  width: 4rem;
  height: 4rem;
  color: #3b82f6;
  margin-bottom: 1rem;
}

h3 {
  margin: 0;
  font-size: 1.5rem;
  font-weight: 700;
  color: #111827;
}

.version {
  font-size: 0.875rem;
  color: #6b7280;
  margin-top: 0.25rem;
  background-color: #f3f4f6;
  padding: 0.125rem 0.5rem;
  border-radius: 9999px;
}

.description {
  color: #4b5563;
  margin-bottom: 1.5rem;
  line-height: 1.5;
}

.links a {
  color: #3b82f6;
  text-decoration: none;
  font-weight: 500;
}

.links a:hover {
  text-decoration: underline;
}

.separator {
  margin: 0 0.5rem;
  color: #9ca3af;
}

.footer {
  margin-top: 2rem;
  font-size: 0.75rem;
  color: #9ca3af;
}
</style>

<style>
/* Dark mode support */
:root.dark .modal-content {
  background-color: #1f2937;
  border: 1px solid #374151;
  color: #f3f4f6;
}

:root.dark .modal-header {
  border-bottom-color: #374151;
}

:root.dark .modal-content h2, :root.dark .modal-content h3 {
  color: #f9fafb;
}

:root.dark .close-btn {
  color: #9ca3af;
}

:root.dark .close-btn:hover {
  background-color: #374151;
  color: #f3f4f6;
}

:root.dark .description {
  color: #d1d5db;
}

:root.dark .version {
  background-color: #374151;
  color: #9ca3af;
}

:root.dark .links a {
  color: #60a5fa; /* blue-400 */
}

:root.dark .links a:hover {
  color: #93c5fd; /* blue-300 */
}
</style>
