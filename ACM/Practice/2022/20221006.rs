struct HasDrop1;

struct HasDrop2;

impl Drop for HasDrop1 {
    fn drop(&mut self) {
        println!("Dropping HasDrop1!");
    }
}

impl Drop for HasDrop2 {
    fn drop(&mut self) {
        println!("Dropping HasDrop2!");
    }
}

struct HasTwoDrops {
    one: HasDrop1,
    two: HasDrop2,
}

impl Drop for HasTwoDrops {
    fn drop(&mut self) {
        println!("Dropping HasTwoDrops!");
    }
}

struct Foo;

fn foo(x: &str) -> String {
    let a = "Hello, ".to_string() + x;
    return a;
}

impl Drop for Foo {
    fn drop(&mut self) {
        println!("Dropping Foo!")
    }
}

use std::thread;
use std::time::Duration;

fn main() {
    let b = foo("world");
    println!("{}", b);

    let a = Box::new(3);
    println!("a = {}", a); // a = 3

    let b = *a + 1;
    println!("b = {}", b);

    let a = vec![Box::new(1), Box::new(2)];
    for (idx, boxs) in a.iter().enumerate() {
        println!("i is {:?}", **boxs);
    }
    {
        let _x = HasTwoDrops {
            two: HasDrop2,
            one: HasDrop1,
        };
        let _foo = Foo;
        println!("Running!");
    }
    use std::cell::RefCell;
    let s = RefCell::new(String::from("hello, world"));
    let s1 = s.borrow();
    let s2 = s.borrow();

    println!("s1:{}, s2:{}", s1, s2);

    thread::spawn(|| {
        for i in 1..10 {
            println!("hi number {} from the spawned thread!", i);
            thread::sleep(Duration::from_millis(1));
        }
    });

    for i in 1..5 {
        println!("hi number {} from the main thread!", i);
        thread::sleep(Duration::from_millis(1));
    }
}