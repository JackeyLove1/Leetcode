#[derive(Debug)]
struct Rec {
    width: f64,
    length: f64,
}

impl Rec {
    pub fn new(w: f64, l: f64) -> Self {
        return Rec {
            width: w,
            length: l,
        };
    }

    pub fn width(&self) -> f64 {
        return self.width;
    }

    fn area(&self) -> f64 {
        return std::f64::consts::PI * self.width * self.length;
    }
}
#[derive(Debug)]
struct Point {
    x: i32,
    y: i32,
}

impl Point {
    fn move_to(&mut self, x: i32, y: i32) {
        self.x = x;
        self.y = y;
    }
}

fn add<T: std::ops::Add<Output=T>>(a: T, b: T) -> T {
    return a + b;
}

fn two_sum(nums: &Vec<i32>, target: i32) -> Vec<i32> {
    use std::collections::HashMap;
    // let mp: HashMap<_, _> = nums.into_iter().collect();
    let mut mp: HashMap<i32, i32> = HashMap::with_capacity(nums.len());
    for (idx, &num) in nums.iter().enumerate() {
        if let Some(&i) = mp.get(&(target - num)) {
            return vec![i as i32, idx as i32];
        }
        mp.insert(num, idx as i32);
    }
    return vec![];
}

fn two_sum2(nums: &Vec<i32>, target: i32) -> Vec<i32> {
    let len = nums.len();
    for i in 0..len {
        for j in i + 1..len {
            if nums[i] + nums[j] == target {
                return vec![i as i32, j as i32];
            }
        }
    }
    return vec![];
}

fn longest<'a>(x: &'a str, y: &'a str) -> &'a str {
    return if x.len() > y.len() {
        x
    } else {
        y
    };
}

fn main() {
    let r1 = Rec {
        width: 1.2,
        length: 3.5,
    };
    println!("area of r is {}", r1.area());
    println!("width is {}", r1.width());

    println!("add i8: {}", add(2i8, 3i8));
    println!("add i32: {}", add(20, 30));
    println!("add f64: {}", add(1.23, 1.23));

    let nums1: Vec<i32> = vec![2, 7, 11, 15];
    let target1: i32 = 9;
    println!("two sum: {:?}", two_sum(&nums1, target1));
    println!("two sum2: {:?}", two_sum2(&nums1, target1));
    println!("nums1.capacity is {}", nums1.capacity());
    let x = String::from("Hello");
    let y = "World!";
    println!("longest is {:?}", longest(x.as_str(), y));
    let string1 = String::from("long string is long");
    {
        let string2 = String::from("xyz");
        let result = longest(string1.as_str(), string2.as_str());
        println!("The longest string is {}", result);
    }

    let mut p = Point { x: 0, y: 0 };
    let r = &mut p;
    let rr: &Point = &*r;

    println!("{:?}", rr);
    r.move_to(10, 10);
    println!("{:?}", r);

    let s1:Box<str> = "Hello there!".into();
    println!("s1 is {}", s1);
}