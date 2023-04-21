console.log(Number.POSITIVE_INFINITY)
console.log(Number.NEGATIVE_INFINITY)
console.log(Number.MAX_VALUE)

class Animal{
    Name: string
}

function func1<T>(m:T) : T{
    return m
}

console.log(func1<string>("Hello, World!"))
console.log(func1("hello2"))
console.log(func1(123))
console.log(typeof func1)

class A<T, U> {
    attr1: T;
    attr2: U;
    constructor(a: T, b: U) {
        this.attr1 = a;
        this.attr2 = b;
    }
    show(m: T, n: U) : T{
        return m;
    }
}

let a = new A<string, number>("123", 123);
console.log(a)

interface A2<T> {
    attr: T
}

let b: A2<number> = {attr: 123};
console.log(b)

let arr:  Array<number> = [1,2,3,4];
console.log(arr)

type myNumber = number;
type myString = number | string;
type myText = "Zero" | "One" | "Two";
type Pair<T, U> = [T, U];

namespace ns{
    let ns_a = 1;
    export let ns_b = 2;
}
console.log(ns.ns_b)

function func2(a:string, b?:string) : string{
    return b ? a + b : a;
}
console.log(func2("Hello"))
console.log(func2("Hello", " World"))

class Dog{
    public name: string;
    constructor(name_ : string) {
        this.name = name_;
    }

    static isDog<T>(d:T) : boolean{
        console.log("d type is", typeof d)
        return d instanceof Dog
    }
}

let dog = new Dog("Doge")
console.log(dog.name)
console.log(Dog.isDog("123"))
console.log(Dog.isDog(dog))