package main

import (
    "context"
    "fmt"

    pb "awesomeGoStudyV1/demos2/demo2/proto"
    "google.golang.org/grpc"
    "google.golang.org/grpc/credentials/insecure"
)

func main() {
    conn, err := grpc.Dial("127.0.0.1:9090", grpc.WithTransportCredentials(insecure.NewCredentials()))
    if err != nil {
        panic(err)
    }
    defer conn.Close()

    client := pb.NewHelloServiceClient(conn)
    resp, _ := client.SayHello(context.Background(), &pb.HelloRequest{RequestName: "Jacky"})
    fmt.Println("resp:", resp.GetResponseMsg())
}
