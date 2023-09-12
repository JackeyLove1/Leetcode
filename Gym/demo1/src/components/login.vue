<template>
  <el-row class="min-h-screen w-auto bg-indigo-500">
    <el-col :lg="16" :md="12" class="flex justify-center items-center">
      <div class="text-left">
       <div class="font-bold text-5xl text-light-50 mb-4">欢迎登陆</div>
       <div class="text-sm text-gray-200">致力于打造世界领先的人工智能平台</div> 
      </div>
    </el-col>
    <el-col :lg="8" :md="12" class="bg-light-50 flex justify-center items-center flex-col space-y-4">
      <h2 class="text-black font-bold text-3xl ">AI 助手</h2>
      <div class="justify-center items-center flex space-x-2">
        <span class="h-[1px] w-16 bg-gray-200"></span>
        <span> 账号密码登陆</span>
        <span class="h-[1px] w-16 bg-gray-200"></span>
      </div>
      <el-form ref="formRef" :model="form" class="w-[250px]">
                <el-form-item prop="username">
                    <el-input v-model="form.username" placeholder="请输入用户名">
                        <template #prefix>
                            <el-icon><user /></el-icon>
                        </template>
                    </el-input>
                </el-form-item>
                <el-form-item prop="password">
                    <el-input type="password" v-model="form.password" placeholder="请输入密码" show-password>
                        <template #prefix>
                            <el-icon><lock /></el-icon>
                        </template>
                    </el-input>
                </el-form-item>
                <el-form-item>
                    <el-button round color="#626aef" class="w-[250px]" type="primary" @click="onSubmit" :loading="loading">登 录</el-button>
                </el-form-item>
        </el-form>
    </el-col>
  </el-row>
</template>

<script setup lang="ts">
import {ref, reactive} from "vue"
const form = reactive({
  username: "",
  password: ""
})

const formRef = ref(null)
const loading = ref(false)
const onSubmit = () => {
  return true;
}
</script>