<script lang="ts">
import {defineComponent, ref} from 'vue';
export default defineComponent({
    name: 'DropdownItem',
    props: {
        disabled: {
            type: Boolean,
            default: false,
        },
    }
});
</script>

<template>
    <li class="dropdown-option" :class="{'is-disabled' : disabled}">
        <slot></slot>
    </li>
</template>

<style scoped>
.dropdown-option.is-disabled * {
    color: #6c757d;
    pointer-events: none;
    background-color: transparent;
}
</style>