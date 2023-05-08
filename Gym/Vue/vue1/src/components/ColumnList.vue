<script lang="ts">
import { defineComponent, PropType, computed } from 'vue';
import DropDown from './DropDown.vue';
export interface IColumnList {
    id: number,
    title: string,
    avatar?: string,
    description: string,
}

export default defineComponent({
    name: "ColumnList",
    props: {
        list: {
            type: Array as PropType<IColumnList[]>,
            required: true,
        }
    },
    setup(props){
        const columnList = computed(() => {
            return props.list.map(column => {
                if (!column.avatar){
                    column.avatar = require('@/assets/avatar.jpg');
                }
                return column;
            })
        });
        return {
            columnList
        };
    }
});

</script>

<template>
    <ul>
        <div class="row">
            <li v-for=" column in list" :key="column.id" class="col-4 mb-4">
                <div class="card h-100 shadow-sm">
                    <img :src="column?.avatar" :alt="column.title" class="card-img-top rounded-circle border border-light w-25 my-3" />
                    <div class="card-body text-center">
                        <h5 class="card-title">{{ column.title }}</h5>
                        <p class="card-text text-left">{{ column.description }}</p>
                        <a href="#" class="btn btn-primary">Enter the Column</a>
                    </div>
                </div>
            </li>

        </div>
    </ul>
</template>

<style scoped></style>