package main

import (
    "context"
    "errors"
    "net"

    "awesomeGoStudyV1/demos2/demo2/proto"
    "google.golang.org/grpc"
    "google.golang.org/grpc/credentials/insecure"
    "google.golang.org/grpc/metadata"
)

type Server struct {
    service.UnimplementedHelloServiceServer
}

func (s *Server) SayHello(ctx context.Context, req *service.HelloRequest) (*service.HelloResponse, error) {
    md, ok := metadata.FromIncomingContext(ctx)
    if !ok {
        return nil, errors.New("get meta error")
    }
    var appId string
    var appKey string
    if v, ok := md["user"]; ok {
        appId = v[0]
    }
    if v, ok := md["password"]; ok {
        appKey = v[0]
    }
    println(appId)
    println(appKey)
    if appId != "Jacky" || appKey != "123" {
        return nil, errors.New("token error")
    }
    return &service.HelloResponse{
        ResponseMsg: "hello" + req.RequestName,
    }, nil
}

func main() {
    listen, err := net.Listen("tcp", ":9090")
    if err != nil {
        panic(err)
    }
    grpcService := grpc.NewServer(grpc.Creds(insecure.NewCredentials()))
    service.RegisterHelloServiceServer(grpcService, &Server{})
    err = grpcService.Serve(listen)
    if err != nil {
        panic(err)
    }

}
