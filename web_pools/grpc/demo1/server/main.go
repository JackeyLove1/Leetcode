package main

import (
    "context"
    "net"

    "awesomeGoStudyV1/demos2/demo2/proto"
    "google.golang.org/grpc"
)

type Server struct {
    service.UnimplementedHelloServiceServer
}

func (s *Server) SayHello(ctx context.Context, req *service.HelloRequest) (*service.HelloResponse, error) {
    return &service.HelloResponse{
        ResponseMsg: "hello" + req.RequestName,
    }, nil
}

func main() {
    listen, err := net.Listen("tcp", ":9090")
    if err != nil {
        panic(err)
    }
    grpcService := grpc.NewServer()
    service.RegisterHelloServiceServer(grpcService, &Server{})
    err = grpcService.Serve(listen)
    if err != nil {
        panic(err)
    }

}
