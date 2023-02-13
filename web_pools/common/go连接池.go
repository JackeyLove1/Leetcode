package main

import (
    "fmt"
    "net"
    "sync"
    "time"
)

// connection pool
type ConnectionPool struct {
    pool     chan net.Conn
    maxSize  int
    created  int
    mu       sync.Mutex
    dialFunc func() (net.Conn, error) // created method
    timeout  time.Duration
}

func NewConnectionPool(maxSize int, dialFunc func() (net.Conn, error), timeout time.Duration) (*ConnectionPool, error) {
    pool := &ConnectionPool{
        pool:     make(chan net.Conn, maxSize),
        maxSize:  maxSize,
        created:  0,
        mu:       sync.Mutex{},
        dialFunc: dialFunc,
        timeout:  timeout,
    }
    for i := 0; i < maxSize; i++ {
        conn, err := dialFunc()
        if err != nil {
            return nil, fmt.Errorf("failed to create connection %d, %s", i, err)
        }
        pool.pool <- conn
        pool.created++
    }
    return pool, nil
}

func (pool *ConnectionPool) Get() (net.Conn, error) {
    select {
    case conn := <-pool.pool:
        return conn, nil
    default:
    }
    pool.mu.Lock()
    defer pool.mu.Unlock()

    if pool.created < pool.maxSize {
        conn, err := pool.dialFunc()
        if err != nil {
            return nil, err
        }
        pool.created++
        return conn, nil
    }
    for {
        select {
        case conn := <-pool.pool:
            return conn, nil
        case <-time.After(time.Second):
            return nil, fmt.Errorf("timeout")
        }
    }
}

func (pool *ConnectionPool) Put(conn net.Conn) {
    select {
    case pool.pool <- conn:
    default:
        conn.Close()
    }
}
