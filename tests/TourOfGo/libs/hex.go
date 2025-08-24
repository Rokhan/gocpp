package main

import (
	"encoding/hex"
	"fmt"
)

func main() {
	src := []byte("Hello")
	dst := make([]byte, hex.EncodedLen(len(src)))
	hex.Encode(dst, src)
	fmt.Printf("%s\n", dst)

	decoded := make([]byte, hex.DecodedLen(len(dst)))
	_, err := hex.Decode(decoded, dst)
	if err != nil {
		fmt.Println(err)
	}
	fmt.Printf("%s\n", decoded)

	dump := hex.Dump(src)
	fmt.Println(dump)

	s := "48656c6c6f"
	data, err := hex.DecodeString(s)
	if err != nil {
		panic(err)
	}
	fmt.Printf("%s\n", data)

	str := hex.EncodeToString(src)
	fmt.Println(str)
}
