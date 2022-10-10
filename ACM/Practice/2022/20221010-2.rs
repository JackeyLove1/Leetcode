use std::fmt::Debug;

struct C1(i32, i32);

trait Contains<A, B> {
    fn contains(&self, _: &A, _: &B) -> bool;
    fn first(&self) -> i32;
    fn last(&self) -> i32;
}

impl Contains<i32, i32> for C1 {
    fn contains(&self, a: &i32, b: &i32) -> bool {
        return (a == &self.0) && (b == &self.1);
    }
    fn first(&self) -> i32 {
        return self.0;
    }
    fn last(&self) -> i32 {
        return self.1;
    }
}

fn difference<A, B, C>(container: &C) -> i32
    where C: Contains<A, B> {
    return container.last() - container.first();
}

trait Container {
    type A;
    type B;
    fn contains(&self, _: &Self::A, _: &Self::B) -> bool;
    fn first(&self) -> Self::A;
    fn last(&self) -> Self::B;
}

/*
impl Container for C1 {
    type A = i32;
    type B = i32;
    fn contains(&self, a: &Self::A, b: &Self::B) -> bool {
        return (self.0 == a) && (self.1 == b);
    }
    fn first(&self) -> Self::A {
        return self.0;
    }
    fn last(&self) -> Self::B {
        return self.1;
    }
}
*/
#[allow(dead_code)]
#[derive(Debug)]
struct Person {
    name: String,
    age: Box<u8>,
}

#[allow(dead_code)]
fn print_one<'a>(x: &'a i32) {
    println!("x is {}", x);
}

#[allow(dead_code)]
fn add_one<'a>(x: &'a mut i32) {
    *x += 1;
}

#[allow(dead_code)]
fn print_multi<'a, 'b>(x: &'a i32, y: &'b i32) {
    println!("x is {}, y is {}", x, y);
}

#[allow(dead_code)]
fn pass_x<'a, 'b>(x: &'a i32, _y: &'b i32) -> &'a i32 {
    return x;
}

struct Owner(i32);

impl Owner {
    fn add_one(&mut self) {
        self.0 = self.0 + 1;
    }
    fn print(&self) {
        println!("value is {}", self.0);
    }
}

#[derive(Debug)]
struct Ref<'a, T: 'a>(&'a T);

fn print<T>(t: T)
    where T: Debug {
    println!("t is {:?}", t);
}

fn print_ref<'a, T>(t: &'a T)
    where T: Debug + 'a {
    println!("t is {:?}", t);
}

trait Animal {
    fn noise(&self) -> &'static str;
}

struct Sheep {}

struct Cow {}

const SHEEP: &'static str = "sheep";
const COW: &'static str = "cow";

impl Animal for Sheep {
    fn noise(&self) -> &'static str {
        return SHEEP;
    }
}

impl Animal for Cow {
    fn noise(&self) -> &'static str {
        return COW;
    }
}

fn random_animal(num: f64) -> Box<dyn Animal> {
    return if num < 0.5 {
        Box::new(Sheep {})
    } else {
        Box::new(Cow {})
    };
}

fn main() {
    println!("2022-10-10");
    let number_1 = 3;
    let number_2 = 10;

    let container = C1(number_1, number_2);

    println!("Does container contain {} and {}: {}",
             &number_1, &number_2,
             container.contains(&number_1, &number_2));
    println!("First number: {}", container.first());
    println!("Last number: {}", container.last());

    println!("The difference is: {}", difference(&container));

    let per = Person {
        name: String::from("Hello"),
        age: Box::new(20),
    };
    println!("per is {:?}", per);
    let mut v = vec![1, 2, 3];
    let x = &mut v;
    x.push(4);
    let y = &mut v;
    y.push(5);
    println!("v: {:?}", v);

    let mut owner = Owner(100);
    owner.add_one();
    owner.print();

    let x = 7;
    let ref_x = Ref(&x);
    print_ref(&ref_x);
    print(x);

    let rand = 0.123;
    let animal = random_animal(rand);
    println!("animal is {}", animal.noise());

}