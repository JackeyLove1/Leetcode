<script lang="ts" setup>
import ColumnList, {IColumnList} from './components/ColumnList.vue'
import 'bootstrap/dist/css/bootstrap.min.css'
import GlobalHeader, {UserProps} from './components/GlobalHeader.vue'

const testData: IColumnList[] = [
  {
    id: 1,
    title: 'test1的专栏',
    description: 'no description',
  },
  {
    id: 2,
    title: 'test2的专栏',
    description: 'no description',
  },
  {
    id: 3,
    title: 'test3的专栏',
    description: 'no description',
  }
];

const user : UserProps = {
  isLogin: false,
  name: "Jacky",
}
</script>

<template>
  <div class="container">
    <GlobalHeader :user="user"></GlobalHeader>
    <ColumnList :list="testData"></ColumnList>
  </div>
</template>

<style scoped>

</style>
