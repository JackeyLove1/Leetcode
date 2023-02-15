// with cancel
func doWork(ctx context.Context) {
	for {
		select {
		case <-ctx.Done():
			fmt.Println("Work done!")
			return
		default:
			fmt.Println("Working...")
		}
	}
}

func main() {
	ctx, cancel := context.WithCancel(context.Background())
	defer cancel() // cancel when we are finished

	go doWork(ctx)

	// Wait for a while before canceling the context
	select {
	case <-ctx.Done():
	case <-time.After(time.Second * 3):
		cancel()
	}
}

// with deadline
ctx := context.Background()
        deadline := time.Now().Add(time.Second * 5)
        ctx, cancel := context.WithDeadline(ctx, deadline)
        defer cancel()
    
        select {
        case <-time.After(time.Second * 10):
            fmt.Println("overslept")
        case <-ctx.Done():
            fmt.Println(ctx.Err())
        }

// read file with timeout 
ctx, cancel := context.WithTimeout(context.Background(), 2*time.Second)
        defer cancel()
    
        data, err := ioutil.ReadFile("example.txt", ctx)
        if err != nil {
            fmt.Println("Error:", err)
            return
        }
    
        fmt.Println(string(data))

// 