import { defineConfig } from 'vite'
import vue from '@vitejs/plugin-vue'
import WindiCSS from 'vite-plugin-windicss'
import path from "path"

// https://vitejs.dev/config/
export default defineConfig({
  plugins: [vue(), WindiCSS(),],
  resolve:{
    alias:{
      "@":path.resolve(__dirname, "src")
    }
  },
  server:{
    host: "0.0.0.0",
    port: 8866,
    proxy:{
      '/api': {
        target: 'http://ceshi13.dishait.cn',
        changeOrigin: true,
        rewrite: (path) => path.replace(/^\/api/, '')
      },
    },
},
})