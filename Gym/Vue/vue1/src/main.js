import { createApp } from 'vue'
import { createPinia } from 'pinia';
import './style.css'
import App from './App.vue'

const pinia = createPinia();
app.use(pinia);

createApp(App).mount('#app')
