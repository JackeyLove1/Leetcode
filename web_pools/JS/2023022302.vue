<script setup>
import {computed, reactive, ref, watch} from 'vue'
import ChildComp from "@/ChildComp.vue";

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
  {id:id++, text:'Learn HTML', done: true},
  {id:id++, text: "Learn JS", done: false},
  {id:id++, text:"Learn Vue", done: false},
])
function addTodo(){
  todos.value.push({id: id++, text: newTodo.value, done: false});
  newTodo.value = ''
}
function removeTodo(todo){
  todos.value = todos.value.filter((t)=>t!==todo);
}

const hideCompleted = ref(false)
const filteredTodos = computed(()=>{
  return todos.value = hideCompleted ?
      todos.value.filter((t) => (!t.done)) : todos.value;
});

const todoId = ref(1);
const todoData = ref(null)
async function fetchData(){
  todoData.value = null;
  const res = await fetch(
      `https://jsonplaceholder.typicode.com/todos/${todoId.value}`
  )
  todoData.value = await res.json();
}
fetchData();
watch(todoId, fetchData)

const greeting = ref("Hello, World");

const childMsg = ref('No Child msg yet');


</script>

<template>
  <ChildComp />
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
    <li v-for="todo in filteredTodos" :key="todo.id">
    <input type="checkbox" v-model="todo.done">
      <span :class="{done:todo.done}">{{todo.text}}}</span>
      <button @click="removeTodo(todo)">X</button>
    </li>
  </ul>
  <button @click="hideCompleted = !hideCompleted">
    {{ hideCompleted ? 'Show all' : 'Hide completed' }}
  </button>

  <p>Todo id:{{todoId}}}</p>
  <button @click="todoId++"> Fetch next todo </button>
  <p v-if="!todoData">Loading...</p>
  <p v-else>{{todoData}}}</p>

  <ChildComp :msg="greeting" @resp="(msg)=>childMsg = msg"/>
  <h2> {{childMsg}}</h2>
</template>

<style>
#title{
  color: red;
}
</style>