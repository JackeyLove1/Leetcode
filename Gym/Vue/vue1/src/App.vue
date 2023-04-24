<script lang="ts" setup>
import ColumnList, {IColumnList} from './components/ColumnList.vue'
import 'bootstrap/dist/css/bootstrap.min.css'

const testData: IColumnList[] = [
  {
    id: 1,
    title: 'test1的专栏',
    description: '这是的test1专栏，有一段非常有意思的简介，可以更新一下欧',
    avatar: 'http://vue-maker.oss-cn-hangzhou.aliyuncs.com/vue-marker/5ee22dd58b3c4520912b9470.jpg?x-oss-process=image/resize,m_pad,h_100,w_100'
  },
  {
    id: 2,
    title: 'test2的专栏',
    description: '这是的test2专栏，有一段非常有意思的简介，可以更新一下欧',
    avatar: 'http://vue-maker.oss-cn-hangzhou.aliyuncs.com/vue-marker/5ee22dd58b3c4520912b9470.jpg?x-oss-process=image/resize,m_pad,h_100,w_100'
  }
]
</script>

<template>
  <div class="container">
    <h2> Jacky's Web</h2>
    <ColumnList :list="testData"></ColumnList>
  </div>
</template>

<style scoped>

</style>
