package limit

import (
    "net/http"

    "chatgpt-demo/chat"
    "github.com/gin-gonic/gin"
)

func RateLimiter(maxConcurrent uint) gin.HandlerFunc {
    sem := make(chan struct{}, maxConcurrent)
    release := func() { <-sem }
    return func(c *gin.Context) {
        select {
        case sem <- struct{}{}:
            release()
            c.Next()
        default:
            c.JSON(http.StatusOK, gin.H{
                "message": chat.HandleError(chat.OverMaxConcurrency),
            })
        }
    }
}
