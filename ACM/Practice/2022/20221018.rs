use std::collections::{HashMap, LinkedList, BTreeMap, HashSet, BTreeSet, BinaryHeap};
use std::collections::vec_deque::VecDeque;
use std::ops::Bound::Included;

extern crate rand;

use rand::Rng;

fn main() {
    println!("2022-10-19");
    let mut buf = VecDeque::with_capacity(15);
    buf.extend(1..10);
    println!("buf: {:?}", buf);
    buf.shrink_to_fit();
    println!("buf size: {}", buf.len());

    buf.truncate(1);
    println!("buf: {:?}", buf);

    for num in 2..10 {
        buf.push_back(num);
    }
    let c: Vec<_> = buf.iter().collect();
    println!("c is {:?}", c);

    for num in buf.iter_mut() {
        *num = *num * 10;
    }
    println!("buf is {:?}", buf);

    assert!(!buf.is_empty());

    let mut deque: VecDeque<_> = (1..20).into_iter().collect();
    let mut range: VecDeque<_> = deque.range(2..).copied().collect();
    println!("range is {:?}", range);

    range.clear();
    println!("range len: {}", range.len());

    let mut rng = rand::thread_rng();
    for _ in 0..10 {
        let rnum = rng.gen_range(0..50);
        println!("deque contains {} is {}", rnum, deque.contains(&rnum));
    }

    let _df = deque.front();
    let _db = deque.back();
    deque.pop_front();
    deque.pop_back();
    deque.insert(0, 100);
    let df = deque.front().unwrap();
    assert_eq!(*df, 100);

    let mut buf2 = (90..100).into_iter().collect::<VecDeque<_>>();
    deque.append(&mut buf2);
    println!("deque is {:?}", deque);

    let l = LinkedList::from([1, 2, 3, 4, 5]);
    println!("list is {:?}", l);

    let mut hmap = HashMap::new();
    hmap.insert("1".to_string(), "world".to_string());
    println!("hmap: {:?}", hmap);

    let mut smap = HashMap::from([
        ("Mercury", 0.4),
        ("Venus", 0.7),
        ("Earth", 1.0),
        ("Mars", 1.5),
    ]);
    for (k, v) in smap.iter() {
        println!("k: {}, v: {}", k, v);
    }

    println!("keys: {:?}", smap.keys());
    println!("values: {:?}", smap.values());

    for (_, v) in smap.iter_mut() {
        *v = *v * 10 as f64;
    }
    println!("smap: {:?}", smap);

    let mp: HashMap<_, _> = (0..10).map(|x| (x, x * x)).collect();
    println!("mp: {:?}", mp);

    let mut odd = mp.keys().copied().filter(|x| x % 2 == 1).collect::<Vec<_>>();
    odd.sort();
    println!("odd: {:?}", odd);

    let mut bmap = BTreeMap::from([
        ("Mercury", 0.4),
        ("Venus", 0.7),
        ("Earth", 1.0),
        ("Mars", 1.5),
    ]);

    println!("bmap: {:?}", bmap);
    bmap.insert("Jacky", 2 as f64);

    let found = ["Mercury", "Jacky", "123", "others"];
    for ks in &found{
        match bmap.get(ks){
            Some(v) => println!("{ks} : {v}"),
            None => println!("{ks} is not existed")
        }
    }

    let mut hs = HashSet::new();
    for ks in &found{
        hs.insert(ks.clone());
    }
    println!("hs: {:?}", hs);
    hs.clear();

    let mut bs = BTreeSet::new();
    for ks in &found{
        bs.insert(ks.clone());
    }
    println!("bs: {:?}", bs);

    let mut nums:BTreeSet<_> = (0..10).collect();
    for &num in nums.range((Included(&4), Included(&9))){
        println!("{num}");
    }
    nums.clear();

    let mut heap = BinaryHeap::new();
    heap.append(&mut (0..5).collect::<BinaryHeap<_>>());
    println!("heap: {:?}", heap);
    assert_eq!(*heap.peek().unwrap(), 4);

    while !heap.is_empty() {
        if let Some(num) = heap.pop(){
            println!("{num} pop from heap");
        }
    }
}