function changeColor(color) {
    document.getElementById('d1').style.backgroundColor = color
}

function clickHandler(event) {
    console.log(event);
}

document.getElementById("d1").addEventListener("click", clickHandler)

document.getElementById("")
console.log([1, 2, 3, 4, 5, 6]);

let width = window.innerWidth;
let height = window.innerHeight;
document.write(width + "x" + height);

let benz = {
    brand: "benz",
    type: "car",
    price: 3000,
    showCar: function () {
        document.write(`${this.brand + this.type}, price: ${this.price}<br>`)
    }
}

console.log(benz.brand, benz.type, benz.price)
benz.showCar()

class Car {
    brand;
    type;
    price;

    constructor(brand, type, price) {
        this.brand = brand;
        this.type = type;
        this.price = price;
    }

    showCar() {
        document.write(`${this.brand + this.type}, price: ${this.price}`)
    }
}

let bmw = new Car("bmw", "car", 1000)
bmw.showCar()

let i = 0;
i += 1;
console.log("i:", i)

for (let i = 0; i < 2; i++){
    console.log(i);
}

for (let i = 0; i < 2; i++){
    for (let j = 0; j < 2; j++){
        console.log(i, j);
    }
}

// stack
const stack = []
stack.push("item1");
stack.push("item2");
const item1 = stack.pop();
console.log(item1)

let salaries = {
    "A":10,
    "B":20,
    "C":30,
}

let sum = 0;
for (let k in salaries){
    sum += salaries[k]
}
console.log("sum:", sum)

class Ladder{
    step = 0;
    constructor() {
        this.step = 0;
    }
    up(){
        this.step++;
        return this;
    }
    down(){
        this.step--;
        return this;
    }

    showStep(){
        console.log("step:", this.step);
        return this;
    }
}

let ladder = new Ladder();
ladder.up().up().down().showStep();

