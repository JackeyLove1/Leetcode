// go get -u github.com/go-resty/resty/v2

import (
    "fmt"

    "github.com/go-resty/resty/v2"
)


// Create a Resty Client
client := resty.New()

resp, err := client.R().
    EnableTrace().
    Get("https://httpbin.org/get")

// Explore response object
fmt.Println("Response Info:")
fmt.Println("  Error      :", err)
fmt.Println("  Status Code:", resp.StatusCode())
fmt.Println("  Status     :", resp.Status())
fmt.Println("  Proto      :", resp.Proto())
fmt.Println("  Time       :", resp.Time())
fmt.Println("  Received At:", resp.ReceivedAt())
fmt.Println("  Body       :\n", resp)
fmt.Println()

// Create a Resty Client
client := resty.New()

// POST JSON string
// No need to set content type, if you have client level setting
resp, err := client.R().
      SetHeader("Content-Type", "application/json").
      SetBody(`{"username":"testuser", "password":"testpass"}`).
      SetResult(&AuthSuccess{}).    // or SetResult(AuthSuccess{}).
      Post("https://myapp.com/login")

// POST []byte array
// No need to set content type, if you have client level setting
resp, err := client.R().
      SetHeader("Content-Type", "application/json").
      SetBody([]byte(`{"username":"testuser", "password":"testpass"}`)).
      SetResult(&AuthSuccess{}).    // or SetResult(AuthSuccess{}).
      Post("https://myapp.com/login")

// POST Struct, default is JSON content type. No need to set one
resp, err := client.R().
      SetBody(User{Username: "testuser", Password: "testpass"}).
      SetResult(&AuthSuccess{}).    // or SetResult(AuthSuccess{}).
      SetError(&AuthError{}).       // or SetError(AuthError{}).
      Post("https://myapp.com/login")

// POST Map, default is JSON content type. No need to set one
resp, err := client.R().
      SetBody(map[string]interface{}{"username": "testuser", "password": "testpass"}).
      SetResult(&AuthSuccess{}).    // or SetResult(AuthSuccess{}).
      SetError(&AuthError{}).       // or SetError(AuthError{}).
      Post("https://myapp.com/login")

// POST of raw bytes for file upload. For example: upload file to Dropbox
fileBytes, _ := ioutil.ReadFile("/Users/jeeva/mydocument.pdf")

// See we are not setting content-type header, since go-resty automatically detects Content-Type for you
resp, err := client.R().
      SetBody(fileBytes).
      SetContentLength(true).          // Dropbox expects this value
      SetAuthToken("<your-auth-token>").
      SetError(&DropboxError{}).       // or SetError(DropboxError{}).
      Post("https://content.dropboxapi.com/1/files_put/auto/resty/mydocument.pdf") // for upload Dropbox supports PUT too

// Note: resty detects Content-Type for request body/payload if content type header is not set.
//   * For struct and map data type defaults to 'application/json'
//   * Fallback is plain text content type

