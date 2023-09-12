<template>
    <h1> {{ msg }}</h1>
    <el-button @click="handleLogout">Logout</el-button>
    <el-button @click="handleDrawer"> drawer </el-button>
</template>

<script setup lang="ts">
import {ref} from "vue"
import {showModal, toast} from "@/play"
import {useRouter} from "vue-router"
const msg = ref<string>("Hello, World")
const router = useRouter()
function handleLogout() {
    showModal("是否退出登陆", "warning", "提醒").then(() => {
        router.push('/login')
        toast("退出成功！")
    })
}
const drawer = ref(false)
const handleDrawer = () => {
    drawer.value = !drawer.value
}

</script>

