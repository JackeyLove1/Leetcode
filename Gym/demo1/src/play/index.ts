import { ElNotification, ElMessageBox } from 'element-plus'
import nprogress from 'nprogress'

export function toast(message: string, type = "success", dangerouslyUseHTMLString = false) {
    ElNotification({
        message,
        type,
        dangerouslyUseHTMLString,
        duration: 3000
    })
}

// 显示全屏loading
export function showFullLoading() {
    nprogress.start()
}

// 隐藏全屏loading
export function hideFullLoading() {
    nprogress.done()
}

export function showModal(content = "content", type = "warning", title = "title") {
    return ElMessageBox.confirm(
        content,
        title,
        {
            confirmButtonText: '确认',
            cancelButtonText: '取消',
            type,
        }
    )
}