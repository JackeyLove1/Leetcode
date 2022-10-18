use std::collections::vec_deque::VecDeque;

fn main() {
    println!("2022-10-17-2");
    let v: u8 = 5;
    let boxs: Box<_> = Box::new(v);
    println!("boxs: {:?}", boxs);

    let x = Box::new(100);
    let static_ref:& 'static mut usize = Box::leak(x);
    *static_ref += 1;
    println!("Static_ref: {}", static_ref);

    let mut deq = VecDeque::from([-1, 0, 1]);
    println!("deq: {:?}", deq);

    deq.push_back(2);
    deq.push_back(3);
    deq.push_front(-2);
    println!("deq: {:?}", deq);

    if let Some(v) = deq.get_mut(1){
        *v = 100;
    }
    println!("deq: {:?}", deq);
    deq.swap(0, deq.len() - 1);
    println!("deq: {:?}", deq);

}