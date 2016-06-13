package main

import (
	"C"
	"fmt"
	"github.com/derphilipp/go-raspicam"
	"io/ioutil"
	"unsafe"
)

func main() {
	c := simplelib.NewSimpleclass()
	result := c.GetImage()
	length := c.GetImageLength()
	brightPixels := c.GetBrightPixels()
	slice := (*[1 << 30]byte)(unsafe.Pointer(result))[:length:length]
	fmt.Println("5")

	ioutil.WriteFile("dat1.png", slice, 0644)
	fmt.Println("Bright pixels:")
	fmt.Println(brightPixels)
	fmt.Println("File length:")
	fmt.Println(length)
}
