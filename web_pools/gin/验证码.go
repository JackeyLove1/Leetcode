// https://www.topgoer.com/gin%E6%A1%86%E6%9E%B6/%E5%85%B6%E4%BB%96/gin%E9%AA%8C%E8%AF%81%E7%A0%81.html
// github.com/dchest/captcha

/*
web端是怎么实现验证码的功能呢？

提供一个路由，先在session里写入键值对（k->v），把值写在图片上，然后生成图片，显示在浏览器上面
前端将图片中的内容发送给后后端，后端根据session中的k取得v，比对校验。如果通过继续下一步的逻辑，失败给出错误提示
API接口验证码实现方式类似，可以把键值对存储在起来，验证的时候把键值对传输过来一起校验。这里我只给出了web端的方法，爱动手的小伙伴可以自己尝试一下。
*/
package main

import (
    "bytes"
    "github.com/dchest/captcha"
    "github.com/gin-contrib/sessions"
    "github.com/gin-contrib/sessions/cookie"
    "github.com/gin-gonic/gin"
    "net/http"
    "time"
)

// 中间件，处理session
func Session(keyPairs string) gin.HandlerFunc {
    store := SessionConfig()
    return sessions.Sessions(keyPairs, store)
}
func SessionConfig() sessions.Store {
    sessionMaxAge := 3600
    sessionSecret := "topgoer"
    var store sessions.Store
    store = cookie.NewStore([]byte(sessionSecret))
    store.Options(sessions.Options{
        MaxAge: sessionMaxAge, //seconds
        Path:   "/",
    })
    return store
}

func Captcha(c *gin.Context, length ...int) {
    l := captcha.DefaultLen
    w, h := 107, 36
    if len(length) == 1 {
        l = length[0]
    }
    if len(length) == 2 {
        w = length[1]
    }
    if len(length) == 3 {
        h = length[2]
    }
    captchaId := captcha.NewLen(l)
    session := sessions.Default(c)
    session.Set("captcha", captchaId)
    _ = session.Save()
    _ = Serve(c.Writer, c.Request, captchaId, ".png", "zh", false, w, h)
}
func CaptchaVerify(c *gin.Context, code string) bool {
    session := sessions.Default(c)
    if captchaId := session.Get("captcha"); captchaId != nil {
        session.Delete("captcha")
        _ = session.Save()
        if captcha.VerifyString(captchaId.(string), code) {
            return true
        } else {
            return false
        }
    } else {
        return false
    }
}
func Serve(w http.ResponseWriter, r *http.Request, id, ext, lang string, download bool, width, height int) error {
    w.Header().Set("Cache-Control", "no-cache, no-store, must-revalidate")
    w.Header().Set("Pragma", "no-cache")
    w.Header().Set("Expires", "0")

    var content bytes.Buffer
    switch ext {
    case ".png":
        w.Header().Set("Content-Type", "image/png")
        _ = captcha.WriteImage(&content, id, width, height)
    case ".wav":
        w.Header().Set("Content-Type", "audio/x-wav")
        _ = captcha.WriteAudio(&content, id, lang)
    default:
        return captcha.ErrNotFound
    }

    if download {
        w.Header().Set("Content-Type", "application/octet-stream")
    }
    http.ServeContent(w, r, id+ext, time.Time{}, bytes.NewReader(content.Bytes()))
    return nil
}

func main() {
    router := gin.Default()
    router.LoadHTMLGlob("./*.html")
    router.Use(Session("topgoer"))
    router.GET("/captcha", func(c *gin.Context) {
        Captcha(c, 4)
    })
    router.GET("/", func(c *gin.Context) {
        c.HTML(http.StatusOK, "index.html", nil)
    })
    router.GET("/captcha/verify/:value", func(c *gin.Context) {
        value := c.Param("value")
        if CaptchaVerify(c, value) {
            c.JSON(http.StatusOK, gin.H{"status": 0, "msg": "success"})
        } else {
            c.JSON(http.StatusOK, gin.H{"status": 1, "msg": "failed"})
        }
    })
    router.Run(":8080")
}