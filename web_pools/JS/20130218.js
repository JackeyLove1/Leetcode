let p1 = new Promise(function (resolve, reject) {
    resolve(1);
    setTimeout(()=> resolve(2), 100);
});

let prices = {
    banana: 1,
    orange: 2,
    meat: 4
}

let doublePrices = Object.fromEntries(
    Object.entries(prices).map(entry => [entry[0], entry[1] * 2])
)

console.log(doublePrices)

let user = {
    name: "John",
    age: 100
}

for (let value of Object.values(user)){
    console.log(value)
}

for (let key of Object.keys(user)){
    console.log(key)
}

let salaries = {
    "John": 100,
    "Pete": 300,
    "Mary": 250
};
let sumSalaries = (salaries) => {
    let sum = 0;
    for (let value of Object.values(salaries)){
        sum += value
    }
    return sum
}
console.log(sumSalaries(salaries)); // 650

user = {
    name: 'John',
    age: 30
};
let count = (user) => {
    let cnt = 0;
    for (let _ of Object.keys(user)){
        cnt += 1
    }
    return cnt
}
console.log(count(user));

let [a, b, c] = "abc"
console.log(a)
console.log(b)
console.log(c)

let [one, two, three] = new Set([1,2,3,4])
console.log(one)
console.log(two)
console.log(three)

user = {
    name: "John",
    age: 30
};

for (let [key, value] of Object.entries(user)){
    console.log(`${key}:${value}`)
}

user = new Map()
user.set("name", "Jacky")
user.set("age", "30")
for (let [k, v] of user){
    console.log(`${k}:${v}`)
}

let [name1, name2, ...rest] = ["Julius", "Caesar", "Consul", "of the Roman Republic"];
console.log(name1)
console.log(name2)
console.log(rest.length)
console.log(rest)

user = {
    name: "John",
    years: 30
};

let {name, years:age, isAdmin = false} = user
console.log(name)
console.log(age)
console.log(isAdmin)

salaries = {
    "John": 100,
    "Pete": 300,
    "Mary": 250
};

let topSalary = (salaries_) => {
    if (salaries_.length === 0) return null;
    let maxName , maxSalary = 0;
    for (let [name, salary] of Object.entries(salaries_)){
        if (salary >= maxSalary){
            maxName = name
            maxSalary = salary
        }
    }
    return maxName;
}

console.log(topSalary({}))
console.log(topSalary(salaries))

let now = new Date()
console.log(now)

let start = new Date()
for (let i = 0; i < 100000000; i++){
    let dosomething = i * i * i;
}
let end = new Date();
console.log(`the loop cost ${end - start}ms`)

let student = {
    name: 'John',
    age: 30,
    isAdmin: false,
    courses: ['html', 'css', 'js'],
    spouse: null
};
let json = JSON.stringify(student)
console.log(json)
console.log(JSON.stringify(student, null, 2))

user = {
    name: "John Smith",
    age: 35
};
json = JSON.stringify(user, null, 2)
let user2 = JSON.parse(json)
console.log(json)
console.log(user2)

function pow(x, n){
    return (n === 1) ? x : (x * pow(x, n- 1));
}
console.log(pow(2, 50))

let sum = (x) => {
    return (x === 1) ? 1 : (x + sum(x-1))
}
console.log(sum(100))

let fib = (x) => {
    let a = 1, b = 1;
    for (let i = 3; i <= x; i++){
        let c = a + b;
        a = b;
        b = c;
    }
    return b;
}
console.log(fib(3));
console.log(fib(77));

function sumAll(...args){
    let sum = 0;
    for (let arg of args) sum += arg;
    return sum;
}

console.log(sumAll(1,2,3,4,5,6,7,8,9,10));

console.log(Math.max(1,4,5,2,-1,-100,23,1000))

let arr1 = [1, -2, 3, 4];
let arr2 = [8, 3, -8, 1];
console.log(Math.min(...arr1, 1000, ...arr2, -10000, 2000));
/*
function sayHi(){
    console.log("Hello")
}
setTimeout(sayHi, 100)

let timeId = setTimeout(()=>console.log("never happens"), 100)
clearTimeout(timeId)

timeId = setInterval(()=>console.log("tick"), 200)
setTimeout(()=>{clearInterval(timeId); console.log("stop");}, 1000);
*/
let printNumbers = (from, to) => {
    let now = from;
    let timeout = 10;
    let timeId = setInterval(function (){
        console.log(now);
        if (now === to){
            clearInterval(timeId)
        }
        now++;
    }, timeout)
    // setTimeout(clearInterval(timeId), (to - from) * timeId);
}
printNumbers(1, 5);

printNumbers = (from, to) => {
    let now = from;
    let timeout = 10;
    let timeId = setInterval(function (){
        console.log(now);
        if (now === from){
            setTimeout(() => clearInterval(timeId), (to - from + 2) * timeId);
        }
        now++;
    }, timeout);
}
printNumbers(1, 5);

/*
let worker = {
    someMethod(){
        return 1;
    },
    slow(x){
        console.log("Call with:", x);
        return x * this.someMethod();
    }
}

function cachingDecorator(func){
    let cache = new Map();
    return function (x){
      if (cache.has(x)){
          return cache.get(x);
      }
      let result = func.call(x);
      cache.set(x, result);
      return result;
    };
}

worker.slow = cachingDecorator(worker.slow)
worker.slow(2);
worker.slow(2);
 */

user = {
    firstName: "John"
};

function func(){
    console.log(this.firstName)
}

let funcUser = func.bind(user)
funcUser();
