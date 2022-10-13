use std::collections::HashSet;
use std::sync::mpsc::{Sender, Receiver};
use std::rc::Rc;
use std::sync::{Arc, mpsc};
use std::thread;
use std::fs::File;
use std::io::prelude::*;
use std::path::Path;

pub fn add(a: i32, b: i32) -> i32 {
    return a + b;
}

#[cfg(test)]
mod tests {
    use super::*;

    #[test]
    fn test_add_1() {
        assert_eq!(add(1, 2), 3 as i32);
    }

    #[test]
    fn test_add_2() {
        assert!(add(1, 2) == (3 as i32));
    }
}

fn main() {
    println!("2022-10-13");
    let mut a: HashSet<i32> = vec![1, 2, 3, 4].into_iter().collect();
    let mut b: HashSet<i32> = (2..5).into_iter().collect();

    assert!(a.insert(5));
    assert!(a.contains(&5));

    let f = b.insert(4);
    println!("b insert 4 is {}", f);

    let v1 = a.union(&b).collect::<Vec<_>>();
    println!("v1 is {:?}", v1);

    let v1 = a.difference(&b).collect::<Vec<_>>();
    println!("v1 is {:?}", v1);

    let v1 = a.intersection(&b).collect::<Vec<_>>();
    println!("v1 is {:?}", v1);

    let rc_example = "Rc Example".to_string();
    {
        let rc_a = Rc::new(rc_example);
        println!("rc_a count is {}", Rc::strong_count(&rc_a));
        {
            let rc_b = Rc::clone(&rc_a);
            println!("clone b, rc_b count is {}", Rc::strong_count(&rc_b));
            println!("clone b, rc_a count is {}", Rc::strong_count(&rc_a));
            assert!(rc_a.eq(&rc_b))
        }
    }

    let apple = Arc::new("this is an apple");
    let mut children = vec![];
    for _ in 1..10 {
        let apple = Arc::clone(&apple);
        children.push(thread::spawn(move || {
            println!("{:?}", apple);
            println!("apple rc is {}", Arc::strong_count(&apple));
        }));
    }
    for child in children {
        let _ = child.join();
    }

    const NTHREADS: i32 = 3;
    let (tx, rx): (Sender<i32>, Receiver<i32>) = mpsc::channel();
    for id in 0..NTHREADS {
        let thread_tx = tx.clone();
        thread::spawn(move || {
            thread_tx.send(id).unwrap();
            println!("thread{} finished", id);
        });
    }

    let mut ids: Vec<_> = Vec::with_capacity(NTHREADS as usize);
    for _ in 0..NTHREADS {
        ids.push(rx.recv());
    }
    println!("{:?}", ids);

    let path = Path::new("hello.txt");
    let display = path.display();

    let mut file = match File::open(&path) {
        Ok(file) => file,
        Err(e) => panic!("open file {} error: {:?}", display, e),
    };

    let mut s = String::new();
    match file.read_to_string(&mut s) {
        Err(e) => println!("couldn't read {}, e:{:?}", display, e),
        Ok(_) => println!("read succeed, string is {:?}", s),
    }
}