// http://go-colly.org/docs/best_practices/distributed/

// user-agent
const letterBytes = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"

func RandomString() string {
    b := make([]byte, rand.Intn(10)+10)
    for i := range b {
        b[i] = letterBytes[rand.Intn(len(letterBytes))]
    }
    return string(b)
}

c := colly.NewCollector()

c.OnRequest(func(r *colly.Request) {
    r.Headers.Set("User-Agent", RandomString())
})

// header 
c := colly.NewCollector()
c.WithTransport(&http.Transport{
    Proxy: http.ProxyFromEnvironment,
    DialContext: (&net.Dialer{
        Timeout:   30 * time.Second,          // 超时时间
        KeepAlive: 30 * time.Second,          // keepAlive 超时时间
    }).DialContext,
    MaxIdleConns:          100,               // 最大空闲连接数
    IdleConnTimeout:       90 * time.Second,  // 空闲连接超时
    TLSHandshakeTimeout:   10 * time.Second,  // TLS 握手超时
    ExpectContinueTimeout: 1 * time.Second,  
})

// debuger 
type Debugger interface {
    // Init initializes the backend
    Init() error
    // Event receives a new collector event.
    Event(e *Event)
}

// proxy
if p, err := proxy.RoundRobinProxySwitcher(
	"socks5://127.0.0.1:1337",
	"socks5://127.0.0.1:1338",
	"http://127.0.0.1:8080",
); err == nil {
	c.SetProxyFunc(p)
}

// random proxy
var proxies []*url.URL = []*url.URL{
	&url.URL{Host: "127.0.0.1:8080"},
	&url.URL{Host: "127.0.0.1:8081"},
}

func randomProxySwitcher(_ *http.Request) (*url.URL, error) {
	return proxies[random.Intn(len(proxies))], nil
}
c.SetProxyFunc(randomProxySwitcher)

// 