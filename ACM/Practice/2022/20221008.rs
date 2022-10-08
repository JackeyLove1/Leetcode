#![allow(dead_code)]

use std::fmt;
use std::fmt::{format, Formatter};
use tokio::count;
use crate::LinkedList::{Cons, Nil};

#[derive(Debug)]
struct A {
    num: i32,
}

#[derive(Debug)]
struct Point2D {
    x: i32,
    y: i32,
}

impl fmt::Display for Point2D {
    fn fmt(&self, f: &mut Formatter<'_>) -> fmt::Result {
        return write!(f, "x: {}, y: {}", self.x, self.y);
    }
}

#[derive(Debug)]
struct List(Vec<i32>);

impl fmt::Display for List {
    fn fmt(&self, f: &mut Formatter<'_>) -> fmt::Result {
        let vec = &self.0;
        write!(f, "[")?;
        for (idx, num) in vec.iter().enumerate() {
            if idx != 0 { write!(f, " , ")?; }
            write!(f, "{}:{}", idx, num)?;
        }
        return write!(f, "]");
    }
}

#[derive(Debug)]
struct Matrix(f32, f32, f32, f32);

impl fmt::Display for Matrix {
    fn fmt(&self, f: &mut Formatter<'_>) -> fmt::Result {
        write!(f, "({}, {})\n", self.0, self.1)?;
        return write!(f, "({}, {})", self.2, self.3);
    }
}


enum LinkedList {
    Cons(u32, Box<LinkedList>),
    Nil,
}

impl LinkedList {
    fn new() -> LinkedList {
        return Nil;
    }
    fn prepend(self, elem: u32) -> LinkedList {
        return Cons(elem, Box::new(self));
    }
    fn len(&self) -> u32 {
        match *self {
            Nil => 0,
            Cons(_, ref tail) => 1 + tail.len(),
        }
    }

    fn stringify(&self) -> String {
        match *self {
            Nil => format!("Nil"),
            Cons(head, ref tail) => format!("{} {}", head, tail.stringify()),
        }
    }
}

const LENGTH: u32 = 1000;

fn main() {
    let a = A { num: 1 };
    println!("a is {:?}", a);
    let p1 = Point2D { x: 1, y: 2 };
    println!("p1 is {}", p1);
    println!("debug: p1 is {:?}", p1);
    let l1 = List(vec![0, 1, 2, 3, 4, 5]);
    println!("debug List1: {:?}", l1);
    println!("display List1: {}", l1);
    let m1 = Matrix(1 as f32, 2 as f32, 3 as f32, 4 as f32);
    println!("{}", m1);
    println!("m1 is {:?}", m1);
    let xs: [i32; 5] = [1, 2, 3, 4, 5];
    let _ys: [i32; 500] = [0; 500];
    for i in 0..xs.len() + 1 {
        match xs.get(i) {
            Some(xval) => println!("position {}, val {}", i, xval),
            None => println!("position {} is None", i),
        }
    }
    let mut list = LinkedList::new();
    list = list.prepend(1);
    list = list.prepend(2);
    list = list.prepend(3);
    println!("list has length: {}", list.len());
    println!("{}", list.stringify());
    println!("const length {}", LENGTH);

    let a_binding;
    {
        let x = 2;

        // Initialize the binding
        a_binding = x * x;
    }
    println!("a binding: {}", a_binding);
    let x = 1u8;
    let y = 2u32;
    let z = 3f32;
    // Unsuffixed literals, their types depend on how they are used
    let i = 1;
    let f = 1.0;
    // `size_of_val` returns the size of a variable in bytes
    println!("size of `x` in bytes: {}", std::mem::size_of_val(&x));
    println!("size of `y` in bytes: {}", std::mem::size_of_val(&y));
    println!("size of `z` in bytes: {}", std::mem::size_of_val(&z));
    println!("size of `i` in bytes: {}", std::mem::size_of_val(&i));
    println!("size of `f` in bytes: {}", std::mem::size_of_val(&f));

    let x1: i32 = "123".parse().unwrap();
    println!("x1 is {}", x1);
    let x2: i32 = "-123".parse().unwrap();
    println!("x2 is {}", x2);

    'outer: loop {
        println!("Enter outer loop!");
        'inner: loop {
            println!("Enter inner loop!");
            break 'outer;
        }
        println!("go on outer loop");
    }
    println!("Exited outer loop!");

    let mut cnt = 1;
    let result = loop {
        cnt += 1;
        if cnt == 100 {
            break cnt * 123;
        }
    };
    assert_eq!(result, 12300);
    println!("result is {}", result);
    let number = 10;
    match number {
        1 => println!("1"),
        2 | 3 | 4 => println!("2 or 3 or 4"),
        5..=10 => println!("[5, 10]"),
        _ => println!("others"),
    }
}