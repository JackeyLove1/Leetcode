#![allow(dead_code)]

struct Point {
    x: f64,
    y: f64,
}

impl Point {
    fn origin() -> Point {
        return Point { x: 0.0, y: 0.0 };
    }

    fn new(x: f64, y: f64) -> Point {
        return Point { x, y };
    }
}

struct Rectangle {
    p1: Point,
    p2: Point,
}

impl Rectangle {
    fn area(&self) -> f64 {
        let Point { x: x1, y: y1 } = self.p1;
        let Point { x: x2, y: y2 } = self.p2;
        return ((x1 - x2) * (y1 - y2)).abs();
    }

    fn translate(&mut self, x: f64, y: f64) {
        self.p1.x += x;
        self.p1.y += y;
        self.p2.x += x;
        self.p2.y += y;
    }
}

struct Pair(Box<i32>, Box<i32>);

impl Pair {
    fn destroy(self) {
        let Pair(first, second) = self;
        println!("Destroying Pair({} {})", first, second);
    }
}

fn main() {
    println!("2022-10-09");

    let names1 = vec!["A", "B", "C"];
    for name in names1.iter() {
        match *name {
            "C" => println!("C1"),
            _ => println!("Hello1 {}", name),
        }

        match name {
            &"C" => println!("C2"),
            _ => println!("Hello2 {}", name),
        }
    }
    println!("names1 : {:?}", names1);

    let names1 = vec!["A", "B", "C"];
    for name in names1.into_iter() {
        match name {
            "C" => println!("C"),
            _ => println!("Hello {}", name),
        }
    }
    // names1 is borrowed!
    let mut names1 = vec!["A", "B", "C"];
    for name in names1.iter_mut() {
        match name {
            &mut "C" => println!("C"),
            _ => println!("Hello {}", name),
        }
    }
    println!("names1 : {:?}", names1);

    let x = &4;
    match x {
        &val => println!("x is {:?}", val),
        // _ => println!("Nothing!"),
    };
    let ref y = 4;
    match y {
        &val => println!("y is {:?}", val),
        // _ => println!("nothing!"),
    }

    let age = 15;
    match age {
        0 => println!("I haven't celebrated my first birthday yet"),
        n @ 1..=12 => println!("I'm a child of age {:?}", n),
        n @ 13..=19 => println!("I'm a teen of age {:?}", n),
        // Nothing bound. Return the result.
        n => println!("I'm an old person of age {:?}", n),
    }

    let number: Option<i32> = Some(100);
    if let Some(i) = number {
        println!("number is {}", i);
    } else {
        println!("number is nothing");
    }

    let mut op = Some(0);
    while let Some(i) = op {
        if i > 9 {
            println!("Greater than 9, quit!");
            op = None;
        } else {
            println!("i is {}", i);
            op = Some(i + 1);
        }
    }

    let rectangle = Rectangle {
        p1: Point::origin(),
        p2: Point::new(3.0, 4.0),
    };
    println!("Rectangle area: {}", rectangle.area());
}