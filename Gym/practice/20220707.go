package main

import (
	"bufio"
	"fmt"
	"log"
	"math/rand"
	"os"
	"strconv"
	"strings"
	"time"
)

func main() {
	fmt.Println("Hello, World!")
	rand.Seed(time.Now().UnixNano())
	const maxNumber = 100
	randNumber := rand.Intn(maxNumber)
	for {
		reader := bufio.NewReader(os.Stdin)
		inputs, err := reader.ReadString('\n')
		if err != nil {
			log.Fatal(err.Error())
		}
		inputs = strings.TrimSuffix(inputs, "\n")
		inputsNumber, err := strconv.Atoi(inputs)
		if err != nil {
			log.Fatal(err.Error())
		}
		if inputsNumber < randNumber {
			fmt.Println("Success!")
			break
		} else {
			fmt.Println("Failed!")
		}
	}
}
