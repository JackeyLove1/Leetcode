use std::sync::{Arc, mpsc, Mutex};
use std::thread;
use std::time::Duration;
use tokio::net::TcpListener;

struct Foo {
    a: String,
    b: String,
}

struct Worker {
    id: usize,
    thread: Option<thread::JoinHandle<()>>,
}

impl Worker {
    pub fn new(id: usize, receiver: Arc<Mutex<mpsc::Receiver<Job>>>) -> Worker {
        let thread = thread::spawn(move || {
            let job = receiver.lock().unwrap().recv().unwrap();
            println!("Worker {} got a job; executing", id);
            job();
        });
        return Worker { id: id, thread: Some(thread) };
    }
}

type Job = Box<dyn FnOnce() + Send + 'static>;

pub struct ThreadPool {
    workers: Vec<Worker>,
    sender: mpsc::Sender<Job>,
}

impl ThreadPool {
    pub fn new(size: usize) -> ThreadPool {
        assert!(size > 0);

        let (sender, receiver) = mpsc::channel();

        let mut workers = Vec::with_capacity(size);
        let receiver = Arc::new(Mutex::new(receiver));
        for id in 0..size {
            workers.push(Worker::new(id, Arc::clone(&receiver)));
        }
        return ThreadPool { workers, sender };
    }

    pub fn execute<F>(&self, f: F)
        where F: FnOnce() + Send + 'static,
    {
        let job = Box::new(f);
        self.sender.send(job).unwrap();
    }
}

impl Drop for ThreadPool {
    fn drop(&mut self) {
        for worker in &mut self.workers {
            let Some(thread) = worker.thread.take(){
                thread.join().unwrap();
            }
        }
    }
}

fn main() {
    println!("2022-10-13-2");
    const NTHREADS: i32 = 3;
    const NUMBERS: i32 = 5;
    let mut children = vec![];
    for idx in 0..NTHREADS {
        children.push(thread::spawn(
            move || {
                for num in 0..NUMBERS {
                    println!("thread{} - number{}", idx, num);
                    thread::sleep(Duration::from_millis(1));
                }
            }
        ))
    }

    for child in children {
        child.join().unwrap();
    }

    let v = vec![
        Foo { a: "a0".to_owned(), b: "bo".to_owned() },
        Foo { a: "a1".to_owned(), b: "b1".to_owned() },
    ];
    let (a, b): (Vec<_>, Vec<_>) = v.into_iter().map(|x| { (x.a, x.b) }).unzip();
    println!("a:{:?}, b:{:?}", a, b);

    let counter = Arc::new(Mutex::new(0));
    let mut handles = vec![];
    const COUNTER: i32 = 100;
    for _ in 1..10 {
        let m_counter = Arc::clone(&counter);
        let handle = thread::spawn(move || {
            for _ in 0..COUNTER {
                let mut num = m_counter.lock().unwrap();
                *num += 1;
            }
        });
        handles.push(handle);
    }
    for h in handles {
        h.join().unwrap();
    }
    println!("counter: {}", counter.lock().unwrap());
}