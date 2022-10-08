enum LinkedList {
    Cons(u32, Box<LinkedList>),
    Nil,
}

impl LinkedList {
    fn new() -> LinkedList {
        return Nil;
    }
    fn prepend(self, elem: u32) -> LinkedList {
        return Cons(elem, Box::new(self));
    }
    fn len(&self) -> u32 {
        match *self {
            Nil => 0,
            Cons(_, ref tail) => 1 + tail.len(),
        }
    }

    fn stringify(&self) -> String {
        match *self {
            Nil => format!("Nil"),
            Cons(head, ref tail) => format!("{} {}", head, tail.stringify()),
        }
    }
}