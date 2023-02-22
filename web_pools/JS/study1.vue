<script setup>
import { reactive, ref } from 'vue'

// 组件逻辑
// 此处声明一些响应式状态
const counter = reactive({couter:0})
const message = ref("Hello, World!")
const titleClass = ref('title')
</script>

<template>
  <h1>{{message.split('').reverse().join('')}}</h1>
  <p>Counter is:{{counter.couter}}</p>
  <h1 :id="titleClass">Make Me Red</h1>
</template>

<style>
#title{
  color: red;
}
</style>