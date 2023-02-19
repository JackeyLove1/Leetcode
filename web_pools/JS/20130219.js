let user = {
    firstName: "John",
    sayHi() {
        console.log(`Hello, ${this.firstName}!`);
    }
};

let group = {
    title: "Our Group",
    students: ["John", "Pete", "Alice"],
    showList() {
        this.students.forEach(student => console.log(student));
    }
};

group.showList()

function defer(f, ms){
    return function () {
        setTimeout(()=>f.apply(this, arguments), ms);
    }
}

function sayHi(name){
    console.log("Hello,", name)
}

let deferSayHi = defer(sayHi, 100);
deferSayHi("Jacky")

let obj = {
    name:"jacky",
    get prodName(){
        return this.name
    },
    set prodName(setName){
        this.name = setName
    },
}
console.log(obj.prodName)

Function.prototype.defer = function (ms){
    setTimeout(this, ms);
}
function f(){
    console.log("Hello")
}
f.defer(100);

Function.prototype.defer = function (ms){
    let f = this;
    return function (...args){
        setTimeout(() => f.apply(this, args), ms);
    }
}

f = (a, b) => {console.log(`${a}+${b}=${a+b}`)}
f.defer(20)(1, 2)

class User{
    constructor(name) {
        this.name = name;
    }
    get name(){
        return this._name;
    }

    set name(setName){
        this._name = setName
    }

    onClick = () =>{
        console.log("user name:", this.name)
    }
}

user = new User("Jacky")
setTimeout(user.onClick, 100)


class Animal {
    constructor(name) {
        this.name = name;
    }
}
class Rabbit extends Animal {
    constructor(name) {
        super(name);
        this.created = Date.now();
    }
}
let rabbit = new Rabbit("White Rabbit");
console.log(rabbit.name);
console.log(rabbit.created)

class Article{
    constructor(title, date) {
        this.title = title
        this.date = Date.now()
    }
    toString(){
        return `title:${this.title}, date:${this.date}`
    }
    static compare(articleA, articleB){
        return articleA.date < articleB.date
    }
}

let articles = [
    new Article("HTML", new Date(2019, 1, 1)),
    new Article("CSS", new Date(2019, 0, 1)),
    new Article("JavaScript", new Date(2019, 11, 1))
];
articles.sort(Article.compare)
articles.forEach(article => {
    console.log(article)
})

let arr = [1,2,3]
console.log(arr instanceof Array)

function delay(ms){
    return new Promise(resolve => setTimeout(resolve, ms));
}
delay(300).then(()=>console.log("runs after 3s"))

let p = new Promise(function (resolve, reject){
    setTimeout(()=>resolve(1), 100);
}).then(function (result){
    console.log(result);
    return result * 2;
}).then(function (result){
    console.log(result);
    return result * 2;
}).then(function (result){
    console.log(result);
    return result * 2;
})
p;

let urls = [
    'https://api.github.com/users/iliakan',
    'https://api.github.com/users/remy',
    'https://api.github.com/users/jeresig'
];

let requests = urls.map(url => fetch(urls))
Promise.all(requests).then(
    responses => responses.forEach(response => console.log(`${response.url}:${response.status}`))
)

Promise.race([
        new Promise((resolve, reject) => setTimeout(() => resolve(123), 100)),
        new Promise((resolve, reject) => setTimeout(() => reject(new Error("Whoops!")), 200)),
        new Promise((resolve, reject) => setTimeout(() => resolve(321), 300))]
).then(console.log)

Promise.any([
    new Promise((resolve, reject) => setTimeout(() => resolve(123), 1000)),
    new Promise((resolve, reject) => setTimeout(() => reject(new Error("Whoops!")), 200)),
    new Promise((resolve, reject) => setTimeout(() => resolve(321), 100))]
).then(console.log)

Promise.resolve()
    .then(()=>{console.log("print1")})
    .then(()=>{console.log("print2")})

async function f1(){
    return "f1"
}
f1().then(console.log)

async function f2(){
    let promise = new Promise(
        (resolve, reject) => {
            setTimeout(()=> resolve("done!"), 300);
        }
    );
    let result = await promise;
    console.log("result:", result)
}
f2();

async function f3(){
    let p = Promise.resolve("f3");
    let res = await p;
    console.log("res:", res);
}
f3().then(()=>{console.log("f3 done")});

async function loadJson(url){
    let res = await fetch(url)
    if (res.status === 200){
        let json = await res.json()
        return json
    }else{
        throw new Error(res.status)
    }
}
/*
loadJson('https://javascript.info/no-such-user.json')
    .catch(console.log); // Error: 404
*/
async function wait(){
    await new Promise(resolve => {setTimeout(resolve, 1000)});
    return "f4"
}

function f4(){
    wait().then(result => {console.log(result)});
}
f4();