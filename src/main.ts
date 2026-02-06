import { createApp } from "vue";
import { createPinia } from "pinia";
import App from "./App.vue";

const app = createApp(App);

app.config.errorHandler = (err, _instance, info) => {
    console.error("Global Error:", err, info);
    alert(`Error: ${err}`);
};

app.use(createPinia());
app.mount("#app");
