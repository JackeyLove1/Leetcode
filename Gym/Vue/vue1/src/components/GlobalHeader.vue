<script lang="ts">
import { defineComponent, PropType } from 'vue';
import DropDown from './DropDown.vue';
export interface UserProps {
    isLogin: boolean;
    name?: string;
    id?: number;
};

export default defineComponent({
    name: "GlobalHeader",
    props: {
        user: {
            type: Object as PropType<UserProps>,
            required: true,
        }
    }
})
</script>

<template>
    <nav class="navbar navbar-dark bg-primary justify-content-between mb-4 px-4">
        <div class="container-fluid">
            <a class="navbar-brand" href="#">Jacky's Web</a>
            <ul v-if="!user.isLogin" class="list-inline mb-0">
                <li class="list-inline-item"><a href="#" class="btn btn-outline-light my-2">Login</a></li>
                <li class="list-inline-item"><a href="#" class="btn btn-outline-light my-2">Register</a></li>
            </ul>
            <ul v-else class="list-inline mb-0">
                <li class="list-inline-item"><a href="#" class="btn btn-outline-light my-2">Hello!</a></li>
            </ul>
        </div>
    </nav>
</template>

<style scoped></style>