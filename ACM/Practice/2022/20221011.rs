extern crate core;

use std::ops;

struct Foo;

struct Bar;

#[derive(Debug)]
struct FooBar;

#[derive(Debug)]
struct BarFoo;

impl ops::Add<Bar> for Foo {
    type Output = FooBar;
    fn add(self, _rhs: Bar) -> Self::Output {
        println!("Foo.add(Bar) was called");
        return FooBar;
    }
}

impl ops::Add<Foo> for Bar {
    type Output = BarFoo;
    fn add(self, _rhs: Foo) -> Self::Output {
        println!("Bar.add(Foo) was called!");
        return BarFoo;
    }
}

struct DropSub {}

impl Drop for DropSub {
    fn drop(&mut self) {
        println!("Drop Dropsub");
    }
}

#[allow(dead_code)]
struct DropObj {
    name: &'static str,
    sub: DropSub,
}

impl Drop for DropObj {
    fn drop(&mut self) {
        println!(">Dropping {}", self.name);
    }
}

#[derive(Debug)]
struct Fib {
    curr: u32,
    next: u32,
}

impl Iterator for Fib {
    type Item = u32;
    fn next(&mut self) -> Option<Self::Item> {
        let new_next = self.curr + self.next;
        self.curr = self.next;
        self.next = new_next;
        return Some(self.curr);
    }
}

fn fib() -> Fib {
    return Fib { curr: 1, next: 1 };
}

#[derive(Clone, Debug)]
struct Pair;

#[derive(Clone, Debug)]
struct PB(Box<i32>, Box<i32>);

macro_rules! say_hello {
    () => {
        println!("Hello!");
    };
}

#[allow(dead_code)]
fn call_panic() {
    panic!("panic!");
}

fn animal_match(animal: Option<&str>) {
    match animal {
        Some("snake") => println!("Snake SSSS "),
        Some(others) => println!("Others animal {}", others),
        None => println!("Nothing"),
    }
}

fn animal_unwarp(animal: Option<&str>) {
    let inside = animal.unwrap();
    return if inside == "snake" {
        println!("Snake SSSS ")
    } else {
        println!("Others animal {}s", inside)
    }
}

fn main() {
    println!("2022-10-11");
    println!("Foo + Bar = {:?}", Foo + Bar);
    println!("Bar + Foo = {:?}", Bar + Foo);

    {
        let _a = DropObj { name: "a", sub: DropSub {} };
        {
            let _b = DropObj { name: "b", sub: DropSub {} };
        }
    }
    println!("The first four terms of the Fibonacci sequence are: ");
    for i in fib().take(4) {
        println!("> {}", i);
    }

    let p1 = Pair;
    let _p2 = p1.clone();
    println!("p1 is {:?}", p1);

    let pb1 = PB(Box::new(1), Box::new(2));
    let pb2 = pb1.clone();
    std::mem::drop(pb1);
    println!("pb2 is {:?}", pb2);

    say_hello!();

    let food = Some("chicken");
    let snake = Some("snake");
    let void = None;

    animal_match(food);
    animal_match(snake);
    animal_match(void);

    let bird = Some("robin");
    let _nothing = None;

    animal_unwarp(bird);
    // will panic if unwarp None
    // animal_unwarp(nothing); 
    
    
}