package main

import (
	"io"
	"log"
	"sync"
	"testing"

	"google.golang.org/protobuf/encoding/protowire"

	"tencent.com/mmkv"
)

var testBytes = []byte("test")

func init() {
	mmkv.InitializeMMKVWithLogLevel("/tmp/mmkv", 2)
	log.SetOutput(io.Discard)
}

// func TestMMKVGORead(t *testing.T) {
// 	m, err := mmkvgo.NewManager("/tmp/mmkv")
// 	if err != nil {
// 		t.Fatal(err)
// 	}
// 	v, err := m.OpenVault("")
// 	if err != nil {
// 		t.Fatal(err)
// 	}

// 	byt, err := v.GetBytes("test")
// 	if err != nil {
// 		t.Fatal(err)
// 	}
// 	fmt.Println(string(byt))
// }

func BenchmarkMMKVRead(b *testing.B) {
	kv := mmkv.DefaultMMKVWithMode(mmkv.MMKV_SINGLE_PROCESS)
	kv.SetBytes(testBytes, "test")

	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		kv.GetBytesBuffer("test")
	}
}

func BenchmarkMMKVWrite(b *testing.B) {
	kv := mmkv.DefaultMMKVWithMode(mmkv.MMKV_SINGLE_PROCESS)
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		kv.SetBytes(testBytes, "test")
	}
}

func BenchmarkMMKVMultiRead(b *testing.B) {
	kv := mmkv.DefaultMMKVWithMode(mmkv.MMKV_MULTI_PROCESS)
	kv.SetBytes(testBytes, "test")
	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		kv.GetBytesBuffer("test")
	}
}

func BenchmarkMMKVMultiWrite(b *testing.B) {
	kv := mmkv.DefaultMMKVWithMode(mmkv.MMKV_MULTI_PROCESS)

	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		kv.SetBytes(testBytes, "test")
	}
}

func BenchmarkMapRead(b *testing.B) {
	m := sync.Map{}

	v := protowire.AppendBytes(nil, testBytes)
	m.Store("test", v)

	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		v, _ := m.Load("test")
		protowire.ConsumeBytes(v.([]byte))
	}
}

func BenchmarkMapWrite(b *testing.B) {
	m := sync.Map{}

	b.ResetTimer()
	for i := 0; i < b.N; i++ {
		v := protowire.AppendBytes(nil, testBytes)
		m.Store("test", v)
	}
}
