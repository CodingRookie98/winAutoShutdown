import { createApp } from "vue";
import { createPinia } from "pinia";
import piniaPluginPersistedstate from 'pinia-plugin-persistedstate'
import { i18n } from './i18n'
import App from "./App.vue";

const app = createApp(App);

app.config.errorHandler = (err, _instance, info) => {
    console.error("Global Error:", err, info);
    alert(`Error: ${err}`);
};

const pinia = createPinia()
pinia.use(piniaPluginPersistedstate)

app.use(pinia);
app.use(i18n);
app.mount("#app");
