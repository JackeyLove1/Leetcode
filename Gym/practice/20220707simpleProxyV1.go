package main

import (
	"bufio"
	"log"
	"net"
)

func main() {
	server, err := net.Listen("tcp", "127.0.0.1:1080")
	if err != nil {
		log.Fatal(err.Error())
	}

	for {
		client, err := server.Accept()
		if err != nil {
			log.Fatalf("Accepted failed %s\n", err.Error())
		}

		go process(client)
	}
}

func process(conn net.Conn) {
	defer conn.Close()

	reader := bufio.NewReader(conn)
	for {
		b, err := reader.ReadByte()
		if err != nil {
			break
		}

		_, err = conn.Write([]byte{b})
		if err != nil {
			break
		}

	}
}
