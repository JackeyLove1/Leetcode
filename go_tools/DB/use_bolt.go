package main

import (
	"fmt"
	"log"

	"github.com/boltdb/bolt"
)

func check(err error) {
	if err != nil {
		log.Fatal(err)
	}
}

func main() {
	db, err := bolt.Open("my.db", 0600, nil)
	if err != nil {
		log.Panic(err)
	}

	defer db.Close()

	err = db.Update(func(tx *bolt.Tx) error {
		b := tx.Bucket([]byte("MyBucket"))
		if b == nil {
			// create buckets
			_, err := tx.CreateBucket([]byte("MyBucket"))
			check(err)
		}
		return nil
	})
	check(err)

	// write
	err = db.Update(func(tx *bolt.Tx) error {
		b := tx.Bucket([]byte("MyBucket"))
		if b != nil {
			err = b.Put([]byte("answer"), []byte("0x0000"))
			err = b.Put([]byte("answer2"), []byte("0x0001"))
			err = b.Put([]byte("answer3"), []byte("0x0002"))
			check(err)
		}
		return nil
	})
	check(err)

	// read
	db.View(func(tx *bolt.Tx) error {
		b := tx.Bucket([]byte("MyBucket"))
		v := b.Get([]byte("answer"))
		fmt.Printf("The answer is: %s\n", v)
		return nil
	})
}
