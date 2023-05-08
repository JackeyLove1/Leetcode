<script lang="ts">
import { ref, defineComponent } from 'vue';
import DropdownItem from './DropdownItem.vue';
export default defineComponent({
    name: "DropDown",
    props: {
        title: {
            type: String,
            required: true,
        },
    },
    setup() {
        const isOpen = ref(false);
        const toggleOpen = () => {
            isOpen.value = !isOpen.value;
        };
        return {
            isOpen,
            toggleOpen
        };
    },
    components: { DropdownItem }
})
</script>

<template>
    <button class="btn btn-secondary dropdown-toggle" type="button" data-bs-toggle="dropdown" aria-expanded="false" @click.prevent="toggleOpen">
        {{ title }}
    </button>
    <ul class="dropdown-menu">
        <DropdownItem><a class="dropdown-item" href="#">新建文章</a></DropdownItem>
        <DropdownItem><a class="dropdown-item" href="#">编辑资料</a></DropdownItem>
    </ul>
</template>

<style scoped></style>