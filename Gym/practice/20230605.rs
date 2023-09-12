use std::io;

#[derive(Debug)]
struct Person<'a> {
    name: &'a str,
    age: u8,
}

fn main() {
    println!("Hello, world!");
    let person = Person { name: "Jacky", age: 10 };
    println!("{:#?}", person);
    // let mut guess = String::new();
    // io::stdin().read_line(&mut guess).expect("Failed to read line");
    // println!("Your guess name:{guess}")
    let x = 5;
    let y = 10;
    println!("x = {x}, y = {y}");

    use std::cmp::Ordering;
    let num1 = 10;
    let num2 = 10;
    match num1.cmp(&num2) {
        Ordering::Less => println!("Less"),
        Ordering::Equal => println!("Equal"),
        Ordering::Greater => println!("Greater"),
    };

    let num3 = "3";
    let guess1: u32 = num3.trim().parse().expect("failed to parse guess to a value");
    println!("guess:{guess1}");
    let guess2: u32 = match num3.trim().parse() {
        Ok(num) => num,
        Err(_) => 0,
    };
    println!("guess2:{guess2}");

    const DAY_SECONDS: u32 = 60 * 60 * 24;
    println!("DAY_SECONDS:{DAY_SECONDS}");

    let tuple1: (i32, f64) = (1, 2.0);
    let tup = (500, 6.4, 1);
    let (x, y, z) = tup;
    println!("The value of y is: {y}");

    let condition = true;
    let num4 = if condition { 1 } else { 0 };
    println! {"num4:{num4}"}

    let mut num5 = 3;
    while num5 > 0 {
        println!("num5:{num5}");
        num5 -= 1;
    }

    let a = [10, 20, 30, 40, 50];
    for num in a {
        println!("num:{num}");
    }

    for num in (1..3).rev() {
        println!("num:{num}")
    }

    let mut s1 = String::from("Hello, ");
    s1.push_str("World!");
    let s2 = s1.clone();
    println!("s1:{s1}, s2:{s2}");

    for (idx, &item) in s2.as_bytes().iter().enumerate() {
        println!("item:{item}");
        if item == b' ' {
            println!("idx:{idx}");
        }
    }
    let sz = s2.len();
    println!("len:{sz}");

    struct User {
        active: bool,
        username: String,
        email: String,
        sign_in: u64,
    }
    let user1 = User {
        active: true,
        username: String::from("Hello"),
        email: String::from("World"),
        sign_in: 1,
    };

    enum IPAddr {
        V4(u8, u8, u8, u8),
        V6(String),
    };

    use std::collections::HashMap;
    let mut source = HashMap::new();
    source.insert(String::from("Hello"), 1);
    let key = String::from("Hello");
    let value = source.get(&key).copied().unwrap_or(0);
    println!("value:{value}");
    for (k, v) in &source{
        println!("k:{k}, v:{v}");
    }

    let text = "hello world wonderful world";
    for word in text.split_whitespace(){
        let count = source.entry(word.to_string()).or_insert(0);
        *count += 1;
    }
    println!("{:?}", source)
}