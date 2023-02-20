function* generateSeq(){
    yield 1;
    yield 2;
    return 3;
}

let gen = generateSeq();
let one = gen.next();
console.log(JSON.stringify(one))

function* generateSeq2(){
    yield 1;
    yield 2;
    yield 3;
}
let gen2 = generateSeq2();
for (let v of gen2){
    console.log(v)
}

let seq = [0, ...generateSeq2()];
console.log(seq)

let range = {
    from:1,
    to:5,
    [Symbol.iterator](){
        return {
            current: this.from,
            last: this.to,

            next(){
                if (this.current <= this.last){
                    return {done:false, value:this.current++};
                }else{
                    return {done: true};
                }
            }
        }
    }
};

console.log([...range])

let range2 = {
    from:1,
    to:10,
    *[Symbol.iterator](){
        for(let value = this.from; value <= this.to; value++){
            yield value
        }
    }
}
console.log([...range2])

function *generateSeq3(st, ed){
    for(let i = st; i <= ed; i++) yield i;
}

let gen3 = generateSeq3(1, 100);
console.log([...gen3])

function *pseudoRandom(seed){
    let value = seed;
    while (true){
        value = value * 16807 % 2147483647;
        yield value
    }
}

let generator = pseudoRandom(1);
console.log(generator.next().value)
console.log(generator.next().value)
console.log(generator.next().value)

let range3 = {
    from:1,
    to:20,
    async*[Symbol.asyncIterator](){
        for(let value = this.from; value <= this.to; value++){
            await new Promise(resolve => setTimeout(resolve, 100));
            yield value;
        }
    }
};

(async ()=> {
    for await (let v of range3){
        console.log(v)
    }
})()

