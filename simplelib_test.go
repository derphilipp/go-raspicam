package simplelib_test

import (
	"github.com/zacg/simplelib"
	"io/ioutil"
	"testing"
)

func TestFoo(t *testing.T) {
	c := simplelib.NewSimpleclass()
	result := c.Dostuff()
	if result != 424 {
		t.Error("not 424 pixels!")
	}
}
