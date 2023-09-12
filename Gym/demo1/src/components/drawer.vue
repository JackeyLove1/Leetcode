<template>
  <el-drawer v-model="drawerOpen" :title="title" :direction="direction" :before-close="handleClose">
    <el-form :label-position="labelPosition" label-width="100px" :model="formLabelAlign" style="max-width: 460px"
      class="flex flex-col top-0 left-0 right-0">
      <el-form-item label="旧密码">
        <el-input v-model="formLabelAlign.name" />
      </el-form-item>
      <el-form-item label="新密码">
        <el-input v-model="formLabelAlign.region" />
      </el-form-item>
      <el-form-item label="确认密码">
        <el-input v-model="formLabelAlign.type" />
      </el-form-item>
    </el-form>
    <div class="flex flex-row justify-center items-center" space-x-2>
      <el-button type="primary"> 确认 </el-button>
      <el-button> 取消 </el-button>
    </div>
  </el-drawer>
</template>

<script setup lang="ts">
import { ref, reactive } from 'vue'
import { ElMessageBox } from 'element-plus'
const drawerOpen = ref(true)
const title = ref("drawer title")
const direction = ref('rtl')

const labelPosition = ref('right')

const formLabelAlign = reactive({
  name: '',
  region: '',
  type: '',
})

const handleClose = (done: () => void) => {
  ElMessageBox.confirm("确定关闭吗")
    .then(() => {
      done()
      drawerOpen.value = false
    })
    .catch(() => {
      console.log("Error")
    })
}

</script>

<style scoped></style>
