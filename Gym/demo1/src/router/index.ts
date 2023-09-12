import {
    createRouter,
    createWebHashHistory
} from 'vue-router'

import Home from "@/components/Home.vue"
// import Chat from "@/components/chat.vue"
import Login from '@/components/login.vue'
import NotFound from "@/components/404.vue"
import Drawer from "@/components/drawer.vue"
const routes = [
    {
        path: "/",
        component: Home,
    },
    {
        path: "/login",
        component: Login
    },
    {
        path: "/drawer",
        component: Drawer
    },
    {
        path: '/:pathMatch(.*)*',
        component: NotFound,
    }
]

export const router = createRouter({
    history: createWebHashHistory(),
    routes
})

export default router
