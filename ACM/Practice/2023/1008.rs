use std::fmt::Alignment::Center;

fn main() {
    println!("Hello, world!");

    // tuple
    let tuple = (1, 0.2, "Hello");
    let (a, b, c) = tuple;
    println!("a:{a}, b:{b}, c:{c}");
    let x: (i32, f64, u8) = (500, 6.4, 1);
    let x0 = x.0;
    let x1 = x.1;
    println!("x0:{x0}, x1:{x1}");

    // array
    let _a = [1,2,3,4,5];
    let a : [i32;5] = [1,2,3,4,5];
    for element in a{
        println!("element:{element}")
    }
    for num in (1..4).rev(){
        println!("{num}")
    }

    // String
    let s = String::from("Hello, World!");
    let s_copy = s.clone();
    println!("copy:{s_copy}");
    let mut s2 = String::from("Hell0");
    s2.push_str(", World!");
    println!("s2:{s2}");
    {
        let s3 = &mut s2;
        s3.push_str(" ... ");
        println!("s3:{s3}");
    }
    let slice = &s2[..3];
    println!("slice:{slice}");

    for (i, &item) in s2.as_bytes().iter().enumerate(){
        if item == b' '{
            let sub = &s2[0..i];
            println!("i:{i},  sub:{sub}");
        }
    }

    struct User {
        active: bool,
        username : String,
        email : String,
        sign_in_count : u64,
    };

    let _user1 = User{
        active:true,
        username:String::from("name"),
        email : String::from("email"),
        sign_in_count : 1,
    };

    struct Color(u32, u32, u32);
    let _color = Color(0, 0, 0);

    let rec1 = Rec{
        width : 30,
        height : 50,
    };
    println!("rec1:{:?}", rec1);
    dbg!(&rec1);

    println!("area:{}", rec1.area());
}

#[derive(Debug)]
struct Rec{
    width : u32,
    height : u32,
}

impl Rec {
    fn area(&self) -> u32 {
        return self.width * self.height;
    }

    fn can_hold(&self, other : &Rec)  -> bool {
        return self.height >= other.height && self.width > other.width;
    }
}