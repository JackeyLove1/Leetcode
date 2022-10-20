use log::{debug, info, warn};
use rand::Rng;
use rayon::prelude::*;
use rusqlite::{Connection, Result};
use rusqlite::NO_PARAMS;

#[derive(Debug, Clone, Eq, Ord, PartialEq, PartialOrd)]
struct Person {
    name: String,
    age: u32,
}

impl Person {
    pub fn new(name: String, age: u32) -> Self {
        return Person {
            name,
            age,
        };
    }
}

#[derive(Debug, PartialEq, PartialOrd, Copy, Clone)]
struct Man {
    age: u8,
}

fn main() -> Result<()> {
    println!("2022-10-20");
    let mut rng = rand::thread_rng();
    println!("Random f64: {}", rng.gen::<f64>());
    println!("Random range u32 (0 - 10): {:?}", rng.gen_range(0..10));

    let mut v1 = vec![1, 5, 10, 2, 15];
    v1.sort();
    println!("v1: {:?}", v1);

    let mut v2 = vec![1.1, 1.15, 5.5, 1.123, 2.0];
    v2.sort_by(|a, b| a.partial_cmp(b).unwrap());
    println!("v2: {:?}", v2);

    let people = vec![
        Person::new("Zoe".to_string(), 25),
        Person::new("Al".to_string(), 60),
        Person::new("John".to_string(), 1),
    ];
    let mut p1 = people.clone();
    p1.sort();
    println!("people: {:?}", p1);

    let mut p2 = people.clone();
    p2.sort_by(|a, b| {
        return if a.age == b.age {
            a.name.cmp(&b.name)
        } else {
            a.age.cmp(&b.age)
        };
    });
    println!("p2: {:?}", p2);

    let mut arr = [0, 7, 9, 11];
    arr.par_iter_mut().for_each(|p| *p = 100);
    println!("{:?}", arr);

    let mut vec = vec![2, 4, 6, 8, 10];
    assert!(vec.par_iter().any(|n| (*n % 2 == 0)));
    assert!(vec.par_iter().all(|n| (*n % 2 == 0)));

    vec.push(11);
    assert!(vec.par_iter().any(|n| { *n % 2 == 0 }));

    let v = vec![6, 2, 1, 9, 3, 8, 11];
    let f1 = v.par_iter().find_any(|&&x| { return x == 9; });
    println!("{:?}", f1.unwrap());
    if let Some(f2) = v.par_iter().find_first(|&&x| { return x < 2; }) {
        println!("first number < 2 is {}", *f2);
    }

    let v: Vec<Man> = vec![Man { age: 23 }, Man { age: 19 }, Man { age: 42 }, Man { age: 17 }, Man { age: 17 }, Man { age: 31 }, Man { age: 30 }];
    let num_over30 = v.par_iter().filter(|&&man| { return man.age > 30; });
    println!("{:?}", num_over30);

    let sum_over30 = v.par_iter().map(|&man| { man.age }).filter(|&age| { age > 30 }).reduce(|| 0, |a, b| { return a + b; });
    println!("sum_over30: {:?}", sum_over30);

    let over30: u8 = v.par_iter().map(|&man| { man.age }).filter(|&age| { age > 30 }).sum();
    println!("over30: {:?}", over30);

    let conn = Connection::open("cats.db")?;

    conn.execute(
        "create table if not exists cat_colors (
             id integer primary key,
             name text not null unique
         )",
        NO_PARAMS,
    )?;
    conn.execute(
        "create table if not exists cats (
             id integer primary key,
             name text not null,
             color_id integer not null references cat_colors(id)
         )",
        NO_PARAMS,
    )?;

    warn!("[bar] warn!");
    info!("[bar] info");
    debug!("[bar] debug");
    Ok(())
}
