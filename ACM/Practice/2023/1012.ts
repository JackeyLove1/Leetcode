let fs: (a: any, b: any) => any = (a, b) => a;
// or more precisely
let fst: <T, U>(a: T, b: U) => T = (a, b) => a;

console.log("Hello, World!")

declare function mapIt<T, U>(f: (t: T) => U, ts: T[]): U[];

interface Person {
    name: string
    age: number
    isProgrammer: boolean

    eat(name: string): string

    speak: (name: string) => string
}

let person: Person = {
    name: "ylx",
    age: 100,
    isProgrammer: true,
    eat: function (name: string) {
        return `eat ${name}`
    },
    speak: (name: string) => `speak ${name}`
}

const add = (a: number, b: number, c ?: number | string): number => {
    console.log(c)
    return a + b
}

console.log(add(1, 2, "hello"))

class PersonClass {
    readonly name: string;
    private isCool: boolean;
    protected email ?: string;
    public age: number;

    constructor(n: string, c: boolean, a: number) {
        this.name = n
        this.isCool = c
        this.age = a
    }

    sayHello() {
        return `Hi, I am ${this.name}, my age is ${this.age}`
    }
}

const p1 = new PersonClass("Jacky", false, 100)
console.log(p1.sayHello())

interface HasFormatter {
    format(): string
}

class PersonFormat implements HasFormatter {
    constructor(public username: string, protected password: string) {
    }

    format(): string {
        return this.username.toLocaleLowerCase()
    }
}

let pf1 = new PersonFormat("Jacky", "admin123")
console.log(pf1.format())

interface Animal {
    name: string
}

interface Cat extends Animal {
    honey: boolean
}

const cat: Cat = {
    name: "Cat",
    honey: true,
}

