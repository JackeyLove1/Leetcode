#![allow(dead_code)]

use std::fmt::{Debug, Display};

fn apply<F>(f: F)
    where F: FnOnce() {
    f();
}

mod my_mod {
    fn private_func() {
        println!("my_mod private function");
    }

    pub fn public_func() {
        println!("my_mod public function");
    }

    pub mod sub {
        pub fn sub_func() {
            println!("my_mod::sub::sub_func");
        }
    }
}

struct Empty;

trait DoubleDrop<T> {
    fn double_drop(self, _: T);
}

impl<T, U> DoubleDrop<T> for U {
    fn double_drop(self, _: T) {
        println!("double drop");
    }
}

#[derive(Debug)]
struct Rectangle {
    length: f64,
    height: f64,
}

#[allow(dead_code)]
struct Triangle {
    length: f64,
    height: f64,
}

trait HasArea {
    fn area(&self) -> f64;
}

impl HasArea for Rectangle {
    fn area(&self) -> f64 {
        return self.length * self.height;
    }
}

fn print_area<T: HasArea>(t: &T) {
    println!("area is {}", t.area());
}

fn print_debug<T: Debug>(t: &T) {
    println!("{:?}", t);
}

fn compare_print<T: Display + Debug>(t: &T) {
    println!("Display: {}", t);
    println!("Debug: {:?}", t);
}

trait PrintInOption {
    fn print_in_option(self);
}

impl<T> PrintInOption for T
    where Option<T>: Debug {
    fn print_in_option(self) {
        println!("{:?}", Some(self));
    }
}

fn main() {
    println!("2022-10-09-2");
    let haystack = vec![1, 2, 3];
    let contains = move |needle| haystack.contains(needle);
    println!("{}", contains(&1));
    println!("{}", contains(&4));

    let color = String::from("Hello");
    let print = || { println!("`color`:{}", color); };
    print();
    let _reborrow = &color;
    print();

    let _color_moved = color;
    let mut count = 0;
    let mut inc = || {
        count += 1;
        println!("count is {}", count);
    };
    inc();
    inc();
    let _count_borrowed = &mut count;
    let movable = Box::new(3);
    let consume = || {
        println!("`movable`:{:?}", movable);
        std::mem::drop(movable);
    };
    consume();

    let x = 123;
    let print = || println!("{}", x);
    apply(print);

    let vec1 = vec![1, 2, 3];
    let vec2 = vec![4, 5, 6];
    println!("2 in vec1:{}", vec1.iter().any(|&x| { return x == 2; }));
    println!("2 in vec2:{}", vec2.into_iter().any(|x| { return x == 2; }));

    let vec1 = vec![1, 2, 3];
    let vec2 = vec![4, 5, 6];
    println!("2 in vec1:{:?}", vec1.iter().find(|&&x| { return x == 2; }));
    println!("2 in vec2:{:?}", vec2.into_iter().find(|&x| { return x == 2; }));

    let upper = 1000;
    let mut acc = 0;
    loop {
        let acc_squared = acc * acc;
        if acc_squared >= upper {
            break;
        }
        acc += 1;
    }
    println!("acc is {}", acc);

    my_mod::public_func();
    my_mod::sub::sub_func();

    let empty = Empty;
    let a = 1;
    empty.double_drop(a);

    let rectangle = Rectangle { length: 3.0, height: 4.0 };
    let _triangle = Triangle { length: 3.0, height: 4.0 };

    print_debug(&rectangle);
    println!("Area: {}", rectangle.area());
    print_area(&rectangle);
    let s1 = "Hello, World";
    compare_print(&s1);

    let v = vec![1,2,3,4,5];
    v.print_in_option();

}