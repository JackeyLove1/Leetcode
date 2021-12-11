package go_pool

import "errors"

var (
	ErrPoolClosed = errors.New("Pool has been closed!")
	ErrInvalidWorker = errors.New("Get the Invalid goWorker")
	ErrInvalidCapacity = errors.New("Capacity can't be zero")
)
