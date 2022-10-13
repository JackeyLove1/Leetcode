use std::error::Error;
use std::{error, fmt};
use std::collections::HashMap;
use std::fmt::Formatter;

type Result<T> = std::result::Result<T, Box<dyn Error>>;

#[derive(Debug)]
struct EmptyVec;

impl fmt::Display for EmptyVec {
    fn fmt(&self, f: &mut Formatter<'_>) -> fmt::Result {
        return write!(f, "Empty Vector");
    }
}

impl error::Error for EmptyVec {}

fn double_first(vec: Vec<&str>) -> Result<i32> {
    let first = vec.first().ok_or(EmptyVec)?;
    let parsed = first.parse::<i32>()?;
    return Ok(2 * parsed);
}

fn print(result: Result<i32>) {
    match result {
        Ok(n) => println!("The first double is {}", n),
        Err(e) => println!("Error: {}", e),
    }
}

#[allow(dead_code)]
#[derive(Debug)]
enum MathError{
    Error1,
    Error2,
    Error3
}



fn main() {
    println!("2022-10-12");
    let numbers = vec!["42", "93", "18"];
    let empty = vec![];
    let strings = vec!["tofu", "93", "18"];
    print(double_first(numbers));
    print(double_first(empty));
    print(double_first(strings));

    let strings1 = vec!["123", "qwer", "1000"];
    let numbers1: Vec<_> = strings1.clone().into_iter()
        .filter_map(|num| { return num.parse::<i32>().ok(); }).collect();
    println!("numbers1: {:?}", numbers1);

    let mut collected_vec = (1..10).collect::<Vec<i32>>();
    println!("collected_vec: {:?}", collected_vec);

    collected_vec.push(10);
    println!("push 10 {:?}", collected_vec);
    println!("len: {}", collected_vec.len());

    for (idx, num) in collected_vec.iter().enumerate(){
        println!("idx: {}, num: {}", idx, num);
    }

    for num in collected_vec.iter_mut(){
        *num += 100;
    }
    println!("after iter_mut: {:?}", collected_vec);

    let pangram: &'static str = "Hello, World 123 How are you";
    println!("pangram: {}", pangram);

    for w in pangram.split_whitespace().rev(){
        println!("split and reverse is {}", w);
    }

    // for mut ch = pangram.chars().collect::<Vec<char>>();
    let mut chars = pangram.chars().collect::<Vec<char>>();
    chars.sort();
    chars.dedup();
    println!("after duplicate: {:?}", chars);

    let mut str2 = String::new();
    for c in chars{
        str2.push(c);
        str2.push(',');
    }

    let mut hm = HashMap::new();
    hm.insert("1", "a");
    hm.insert("2", "b");

    match hm.get(&"1"){
        Some(&number) => println!("1 is {}", number),
        _ => println!("nothing!"),
    }

    hm.insert("1", "c");

    match hm.get(&"1"){
        Some(&number) => println!("1 is {}", number),
        _ => println!("nothing!"),
    }

    for (key, value) in hm.iter(){
        println!("key:{}, value:{}", key, value);
    }

}