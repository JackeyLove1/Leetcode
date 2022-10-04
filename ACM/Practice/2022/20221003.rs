use num::complex::Complex;

fn greet_world() {
    let southern_germany = "Grüß Gott!";
    let chinese = "世界，你好";
    let english = "World, hello";
    let regions = [southern_germany, chinese, english];
    for region in regions.iter() {
        println!("{}", &region);
    }
}

fn add(a: i32, b: i32) -> i32 {
    return a + b;
}

fn main() {
    greet_world();
    let x = 100;
    let x = x + 1;
    println!("x is {}", x);
    {
        let x = x * 2;
        println!("x is {}", x);
    }
    println!("x is {}", x);
    let guess: i32 = "123".parse().expect("is not a number!");
    println!("guess is {}", guess);
    // assert_eq!(0.1 + 0.2, 0.3);
    let y = (-4.0_f32).sqrt();
    if y.is_nan() {
        println!("y is {}", y);
    }
    let a = Complex { re: 2.1, im: -1.2 };
    let b = Complex::new(11.1, 22.2);
    let result = a + b;
    println!("{} + {}i", result.re, result.im);
    let x = '中';
    println!("size of x is {}", std::mem::size_of_val(&x));
    let a = 12;
    let b = 34;
    println!("{} + {} = {}", a, b, add(a, b));
    let y = {
        let x = 1;
        x + 1
    };
    println!("y is {}", y);
    let mut s = String::from("Hello, World");
    s.push_str("!");
    println!("{}", s);
    let s2 = s;
    println!("s2 is {}", s2);
    let s3 = "Hello, World3333";
    let s4 = s3;
    println!("s3: {}, s4: {}", s3, s4);
    let s5 = s3.clone();
    let s6 = s2.clone();
    println!("s5: {}, s6: {}", s5, s6);
    println!("sizeof s5 is {}", std::mem::size_of_val(&s5));
    println!("sizeof s6 is {}", std::mem::size_of_val(&s6));

    let my_name = "Pascal";
    greet(my_name);

    let mut s7 = String::from("Jacky");
    s7.push_str("123");
    let len = s7.len();
    println!("s7 len is {}", len);

    let string_append = String::from("hello ");
    let string_rust = String::from("rust");
    // &string_rust会自动解引用为&str
    let mut result = string_append + &string_rust;
    result = result + "!";
    result += "!!!";
    println!("连接字符串 + -> {}", result);

    let r = Rec {
        weight: 20,
        height: 30,
    };
    dbg!(&r);

    // 编译器自动推导出one的类型
    let one = [1, 2, 3];
    // 显式类型标注
    let two: [u8; 3] = [1, 2, 3];
    let blank1 = [0; 3];
    let blank2: [u8; 3] = [0; 3];

    // arrays是一个二维数组，其中每一个元素都是一个数组，元素类型是[u8; 3]
    let arrays: [[u8; 3]; 4] = [one, two, blank1, blank2];

    // 借用arrays的元素用作循环中
    for a in &arrays {
        println!("{:?}:", a);
        for n in a.iter() {
            print! {"\t{} + 10 = {}\n", n, n + 10};
        }

        let mut sum = 0;
        for i in 0..a.len() {
            sum += a[i];
        }
        println!("\t({:?} = {})", a, sum);
    }

    let a = [1, 2, 3, 4, 5];
    for (idx, num) in a.iter().enumerate() {
        println!("idx: {}, num: {}", idx, num);
    }
}


fn greet(name: &str) -> () {
    println!("name is {}", name);
}

#[derive(Debug)]
struct Rec {
    weight: i32,
    height: i32,
}

enum Coin{
    One,
    Two,
    Three,
}

fn value_in(coin : Coin) -> u8{
    match coin {
        Coin::One =>{
            return 0;
        },
        Coin::Two =>{
            return 1;
        },
        Coin::Three => {
            return 2;
        },
    }
}