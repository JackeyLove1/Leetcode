#![allow(dead_code)]

use std::num::ParseIntError;

#[derive(Debug, Copy, Clone)]
struct PhoneNumber {
    area_code: Option<u8>,
    number: u32,
}

#[derive(Copy, Clone)]
struct Job {
    phone_number: Option<PhoneNumber>,
}

#[derive(Copy, Clone)]
struct Person {
    job: Option<Job>,
}

impl Person {
    fn work_phone_area_code(&self) -> Option<u8> {
        return self.job?.phone_number?.area_code;
    }
}

#[derive(Debug)]
enum Number { One, Two, Three }

#[derive(Debug)]
enum Day { Monday, Tuesday, Wednesday }

fn have_nums(num: Number) -> Option<Number> {
    match num {
        Number::One => None,
        _ => Some(num),
    }
}

fn multiply(first: &str, second: &str) -> Result<i32, ParseIntError> {
    let num1 = first.parse::<i32>()?;
    let num2 = second.parse::<i32>()?;
    return Ok(num1 * num2);
}

fn print_multiply(result: Result<i32, ParseIntError>) {
    match result {
        Ok(t) => println!("result is {}", t),
        Err(e) => println!("Err is {}", e),
    }
}

fn double_first(vec: Vec<&str>) -> Result<Option<i32>, ParseIntError> {
    let opt = vec.first().map(|first| {
        first.parse::<i32>().map(|n| 2 * n)
    });

    opt.map_or(Ok(None), |r| r.map(Some))
}

fn main() {
    println!("2022-10-11");

    let p = Person {
        job: Some(Job {
            phone_number: Some(PhoneNumber {
                number: 12345,
                area_code: Some(10),
            }),
        }),
    };
    println!("area_code is {}", p.work_phone_area_code().unwrap());

    print_multiply(multiply("10", "2"));
    print_multiply(multiply("t", "123"));

    let numbers = vec!["42", "93", "18"];
    let empty = vec![];
    let strings = vec!["tofu", "93", "18"];

    println!("The first doubled is {:?}", double_first(numbers));
    println!("The first doubled is {:?}", double_first(empty));
    println!("The first doubled is {:?}", double_first(strings));
}