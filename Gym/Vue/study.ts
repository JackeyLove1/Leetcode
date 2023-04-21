import { th } from "element-plus/es/locale";

let promise = new Promise(function (resolve, reject) {
    setTimeout(() => { resolve("done!"), 1000 });
})

promise.then(
    result => console.log(result),
    error => console.log(error)
);

// let p2 = new Promise(function (resolve, reject) {
//     setTimeout(() => reject(new Error("Whoops")), 100);
// });
// p2.then(
//     result => console.log(result),
//     error => console.error(error)
// )


let p3 = new Promise(function (resolve, reject) {
    setTimeout(() => resolve(1), 1000);
});

p3.then(function (result) {
    console.log(result); // 1
});

interface ILength{
    length : number;
}

function echoWithLength<T extends ILength> (arg : T) : number {
    console.log("arg:", arg,"type:", typeof arg,  "len:", arg.length);
    return arg.length;
}

const str1 = echoWithLength('a');
const nums = echoWithLength([1,2]);
const dir = echoWithLength({length:3});

class Queue<T>{
    private data : T[] = [];
    public push(item: T){
        this.data.push(item);
    }
    public pop(){
        this.data.shift();
    }
}

const queue = new Queue();
for (let i = 0; i < 10; i++) {
    queue.push(i);
}
console.log(queue.pop());

type IOperator = 'plus' | 'minus';
interface ICalculator {
    (operator: IOperator, numbers : number[]) => number;
    plus: (numbers: number[]) => number;
    minus: (numbers: number[]) => number;
}

declare const calculator: ICalculator;