#![allow(dead_code)]

use std::{cmp, sync, thread, time};
use std::fmt::{Display, Formatter};
use std::ops::{Add, Mul};
use std::time::Duration;
use sync::mpsc::{Sender, Receiver};
use sync::mpsc;

async fn do_something() {
    println!("Hello, World!");
}

pub fn is_sorted<T>(arr: &[T]) -> bool
    where T: cmp::PartialOrd,
{
    if arr.is_empty() || arr.len() == 1 {
        return true;
    }
    let n = arr.len();
    for i in 1..n {
        if arr[i - 1] > arr[i] {
            return false;
        }
    }
    return true;
}

pub fn bubble_sort<T: Ord>(arr: &mut [T]) {
    if arr.is_empty() {
        return;
    }
    let n = arr.len();
    for i in 0..n {
        for j in i..n {
            if arr[i] > arr[j] {
                arr.swap(i, j);
            }
        }
    }
}

pub fn sleep_sort(arr: &Vec<u32>) -> Vec<u32> {
    if arr.is_empty() {
        return vec![];
    }
    let (sender, receiver) = mpsc::channel::<u32>();
    for &num in arr {
        let tx = sender.clone();
        thread::spawn(move || {
            thread::sleep(Duration::from_millis((num * 20) as u64));
            tx.send(num).unwrap();
        });
    }

    let mut sorted_vec = Vec::with_capacity(arr.len());
    for _ in 0..arr.len() {
        sorted_vec.push(receiver.recv().unwrap());
    }
    return sorted_vec;
}

pub fn check_anagram(s: &str, t: &str) -> bool {
    let mut s = s.to_ascii_lowercase().chars().collect::<Vec<_>>();
    let mut t = t.to_ascii_lowercase().chars().collect::<Vec<_>>();
    s.sort();
    t.sort();
    return s.eq(&t);
}

#[derive(Clone, Copy)]
struct Complex {
    real: i32,
    imag: i32,
}

impl Complex {
    fn new(real: i32, imag: i32) -> Self {
        return Complex {
            real,
            imag,
        };
    }
}

impl Mul for Complex {
    type Output = Complex;
    fn mul(self, rhs: Self) -> Self::Output {
        return Complex {
            real: self.real * rhs.real - self.imag * rhs.imag,
            imag: self.real * rhs.imag + self.imag * rhs.real,
        };
    }
}

impl Add for Complex {
    type Output = Complex;
    fn add(self, rhs: Self) -> Self::Output {
        return Complex {
            real: self.real + rhs.real,
            imag: self.imag + rhs.imag,
        };
    }
}

impl Display for Complex {
    fn fmt(&self, f: &mut Formatter<'_>) -> std::fmt::Result {
        write!(f, "({} + {}i)", self.real, self.imag)
    }
}

fn main() {
    // do_something();
    println!("2022-10-14");

    let v = vec![6, 5, 4, 1, 2, 3, 1, 3, 0, 5, 9, 7];

    let mut v1 = v.clone();
    bubble_sort(&mut v1);
    assert!(is_sorted(&v1));
    println!("after bubble sorting, v1 is {:?}", v1);

    let v2 = v.clone();
    let v3 = sleep_sort(&v2);
    assert!(is_sorted(&v3));
    println!("after sleep sorting, v3 is {:?}", v3);

    assert!(check_anagram("cat", "tac"));
    assert!(!check_anagram("casdas", "asfvsfaf"));

    let c1 = Complex::new(1, 2);
    let c2 = Complex::new(2, 3);
    let c3 = c1 + c2;
    println!("{} + {} = {}", c1, c2, c3);
    let c4 = c1 * c2;
    println!("{} * {} = {}", c1, c2, c4);
}