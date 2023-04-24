<script lang="ts">
import { defineComponent, PropType } from 'vue';

export interface IColumnList{
    id:number,
    title:string,
    avatar:string,
    description: string,
}

export default defineComponent({
   name: "ColumnList",
    props: {
        list:{
            type: Array as PropType<IColumnList[]>,
            required: true,
        }
    }
});

</script>

<template>
    <ul>
        <li v-for=" column in list" :key="column.id">
            <img :src="column.avatar" alt="avatar"/>
            <div>{{ column.title }}</div>
            <div>{{ column.description }}</div>
            <a href="#">Enter the Column</a>
        </li>
    </ul>
</template>

<style scoped>
</style>