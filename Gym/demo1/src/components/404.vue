<template>
    <div>
        <el-result
        icon="warning"
        title="404"
        sub-title="您来到了没有知识的荒原"
      >
        <template #extra>
          <el-button type="primary" @click="$router.push('/')">回到首页</el-button>
        </template>
      </el-result>
    </div>
</template>