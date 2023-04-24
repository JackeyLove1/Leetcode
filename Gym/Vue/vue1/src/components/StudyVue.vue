<script setup lang="ts">
import { reactive, computed } from 'vue';
interface DataProps{
    count : number;
    double : number;
    increase : ()=>void;
};
const data : DataProps = reactive({
    count : 0,
    increase: () => {data.count++;},
    double: computed(() => data.count * 2),
});
</script>

<template>
    <div>
        <h2> {{ data.count }}</h2>
        <h2> {{ data.double }}</h2>
        <button @click="data.increase"> Add </button>
    </div>
</template>