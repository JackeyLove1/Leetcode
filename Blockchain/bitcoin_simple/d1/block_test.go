package d1

import (
	"fmt"
	"testing"
)

func TestNewBlock(t *testing.T) {
	bc := NewBlockchain()

	bc.AddBlock("Send 1 BTC to Jacky1")
	bc.AddBlock("Send 2 more BTC to Jacky2")

	for _, block := range bc.blocks {
		fmt.Printf("Prev hash: %x\n", block.PrevBlockHash)
		fmt.Printf("Data: %s\n", block.Data)
		fmt.Printf("Hash: %x\n", block.Hash)
		fmt.Println()
	}
}
