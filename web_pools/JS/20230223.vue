<script setup>
import { reactive, ref } from 'vue'

// 组件逻辑
// 此处声明一些响应式状态
const counter = reactive({couter:0});
const message = ref("Hello, World!");
const titleClass = ref('title');
const counter2 = ref(0);
function increment (){
  counter2.value++;
}

const text1 = ref('');
function onInput(e){
  text1.value = e.target.value;
}

const awesome = ref(true)
function toggle(){
  awesome.value = !awesome.value;
}

let id=0;
const newTodo = ref('');
const todos = ref([
  {id:id++, text:'Learn HTML'},
  {id:id++, text: "Learn JS"},
  {id:id++, text:"Learn Vue"},
])
function addTodo(){
  todos.value.push({id: id++, text: newTodo.value});
  newTodo.value = ''
}
function removeTodo(todo){
  todos.value = todos.value.filter((t)=>t!==todo);
}
</script>

<template>
  <h1>{{message.split('').reverse().join('')}}</h1>
  <p>Counter is:{{counter.couter}}</p>
  <h1 :id="titleClass">Make Me Red</h1>
  <button @click="increment">counter is : {{counter2}}</button>
  <input :value="text1" @input="onInput" placeholder="Type Here"> <h2> {{text1}}</h2>
  <button @click="toggle">toggle</button>
  <h1 v-if="awesome">Vue is awesome!</h1>
  <h1 v-else>Oh no 😢</h1>

  <form @submit.prevent="addTodo">
    <input v-model="newTodo">
    <button>Add Todo</button>
  </form>
  <ul>
    <li v-for="todo in todos" :key="todo.id">
    {{todo.text}}
      <button @click="removeTodo(todo)">X</button>
    </li>
  </ul>
</template>

<style>
#title{
  color: red;
}
</style>