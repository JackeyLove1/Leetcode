package d1

type Blockchain struct {
	blocks []*Block
}

func (bc *Blockchain) AddBlock(data string) {
	prevBlock := bc.blocks[len(bc.blocks)-1]
	newBlock := NewBlock(data, prevBlock.Hash)
	bc.blocks = append(bc.blocks, newBlock)
}

func NewGenesisBlock() *Block {
	return NewBlock("Gensis Block", []byte{})
}

func NewBlockchain() *Blockchain {
	return &Blockchain{
		blocks: []*Block{NewGenesisBlock()}}
}
