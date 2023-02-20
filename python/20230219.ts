const hello: string = "Hello, World";
console.log(hello);

const object:{
    a:number,
    b:string,
    c:boolean,
} = {
    a:1,
    b:"1",
    c:true,
}
console.log(object)

class Site{
    name():void{
        console.log("Site");
    }
}

const obj = new Site();
obj.name();

const number = 20;
if (number % 2 == 0){
    console.log("odd number")
}

const num1 = 5;
let fab = 1;
for (let i = 1; i <= num1; i++){
    fab *= i;
}
console.log("fab:", fab);

let chars1:any = "abc";
for (let index in chars1){
    console.log(chars1[index]);
}

let l1 = [1,2,3];
l1.forEach((val, idx, array) =>{
   console.log("val:", val," idx:", idx);
});

function buildName(first:string, last?:string){
    if (last){
        return first + " " + last;
    }else{
        return first;
    }
}

let res1 = buildName("Jakcy");
console.log(res1);
let res2 = buildName("Jacky", "Fan");
console.log(res2);

function buildName2(first:string, ...restOfName:string[]){
    return first + " " + restOfName.join(" ");
}

let res3 = buildName2("Jacky", "fan", "1", "2", "3");
console.log(res3);

function addNumbers(...nums:number[]){
    let sum = 0;
    for (let i = 0; i < nums.length; i++){
        sum += nums[i];
    }
    console.log("sum:", sum);
}
addNumbers(1,2,3,4,5);
addNumbers(1,2,3,4,5,6,7,8,9,10);

let func = (x:any) => {
    if (typeof x == 'number'){
        console.log("x is number");
    }else if (typeof x == "string"){
        console.log("x is string");
    }else {
        console.log("x is unkown")
    }
}
func(12);
func("12");
func(()=>{});

const sites:string[] = new Array("1", "2", "3", "4", "5");
for (let i = 0; i < sites.length; i++){
    console.log(sites[i]);
}

const alpha = ["a", "b", "c"];
const num= [1,2,3];
let alphaNum = alpha.concat(num.toString());
console.log(alphaNum)

const arrays = new Array(1,2,3,4,5);
let passed = arrays.every((num)=>{
    return num >5;
});
console.log("the val:", passed);

let passed2 = arrays.filter((num, idx, arr) => {
    return num > 3;
});
console.log("the val:", passed2);

let passed3 = arrays.forEach((val)=>{console.log(val)})
passed3;

let myMap = new Map([
    ["k1","v1"],
    ["k2","v2"],
])
console.log(myMap);
myMap.set("k3", "v3");
console.log(myMap);
console.log(myMap.has("k3"));
console.log(myMap.has("k4"));

for (let k of myMap.keys()){
    console.log(k);
}
for (let v of myMap.values()){
    console.log(v);
}
for (let entry of myMap.entries()){
    console.log(`${entry[0]}:${entry[1]}`)
}
for (let [k,v] of myMap.entries()){
    console.log(`${k}:${v}`)
}

let myTulpes = [1, 2, "hello", "world"];
console.log(myTulpes.length);
myTulpes.push(3);
myTulpes.pop();
console.log(myTulpes);

let val:string | number;
val = 1;
console.log(val);
val = "1";
console.log(val);

function disp(name:string|string[]) {
    if (typeof name == "string"){
        console.log(name);
    }else{
        for (let i = 0; i < name.length; i++){
            console.log(name[i]);
        }
    }
}
disp(["1", "2", "3", "4", "5"]);

interface IPerson{
    firstName: string,
    secondName:string,
    sayHi:()=>string,
}

let customer:IPerson = {
    firstName:"Jacky",
    secondName:"Fan",
    sayHi:():string => {return "Hello, World!";}
}
console.log(customer.firstName);
console.log(customer.secondName);
console.log(customer.sayHi());

class Car{
    engine:string;
    constructor(engine:string) {
        this.engine = engine;
    }
    disp():void{
        console.log(this.engine)
    }
}

let car = new Car("engine1");
car.disp();

class StaticMem{
    static num:number;
    static disp():void{
        console.log("num:", num)
    }
}
StaticMem.num = 12;
StaticMem.disp();

interface IPoint{
    x:number,
    y:number,
}
function addPoints(p1:IPoint, p2:IPoint):IPoint {
    return {x:p1.x+p2.x, y:p1.y+p2.y};
}

let newP = addPoints({x:1,y:2}, {x:3,y:4});
console.log(newP);

