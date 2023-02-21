package main

import (
    "context"
    "fmt"

    pb "awesomeGoStudyV1/demos2/demo2/proto"
    "google.golang.org/grpc"
    "google.golang.org/grpc/credentials/insecure"
)

/*
type PerRPCCredentials interface {
    GetRequestMetadata(ctx context.Context, uri ...string) (map[string]string, error)
    RequireTransportSecurity() bool
}
*/

type ClientTokenAuth struct {
    User     string
    PassWord string
}

func (c *ClientTokenAuth) GetRequestMetadata(ctx context.Context, uri ...string) (map[string]string, error) {
    return map[string]string{
        "user":     c.User,
        "password": c.PassWord,
    }, nil
}

func (c *ClientTokenAuth) RequireTransportSecurity() bool {
    return false
}
func main() {

    c := ClientTokenAuth{
        User:     "Jacky",
        PassWord: "123",
    }
    var opts []grpc.DialOption
    opts = append(opts, grpc.WithTransportCredentials(insecure.NewCredentials()))
    opts = append(opts, grpc.WithPerRPCCredentials(&c))

    conn, err := grpc.Dial("127.0.0.1:9090", opts...)
    if err != nil {
        panic(err)
    }
    defer conn.Close()

    client := pb.NewHelloServiceClient(conn)
    resp, _ := client.SayHello(context.Background(), &pb.HelloRequest{RequestName: "Jacky"})
    fmt.Println("resp:", resp.GetResponseMsg())
}
