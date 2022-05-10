var a = 1
console.log(a)

function countDown(n) {
    while (n-- > 0) {
        console.log(n)
    }
}

countDown(3)

function isEven(n) {
    var msg = n + " is " + ((n % 2 === 0) ? "Even" : "Odd")
    console.log(msg)
}

for (var i = 0; i < 2; ++i) {
    isEven(i)
}

console.log(Math.exp(2))
console.log(typeof NaN)
console.log(parseInt("123"))

let hello = "Hello, World!";
console.log(hello)

const s = "Hello"
console.log(s[1])
console.log(s.length)

let obj = {
    'foo': 'Hello',
    'bar': 'World'
};

console.log(obj['foo'])
console.log(obj.foo)

console.log(Object.keys(obj))
delete obj.foo
console.log(Object.keys(obj))
console.log("foo" in obj)

obj = {a: 1, b: 2, c: 3};
for (var k in obj) {
    console.log("Key is ", k)
    console.log("value is ", obj[k])
}

let print = function (x) {
    console.log(x)
}

print(123)
print("1234")

let add = function (a, b) {
    console.log(a + b)
}

add(1, 2)
add("1", "2")
add(1, "2")
console.log(add.name)

obj = {p: 1};

function f1(o) {
    o.p = 2
}

f1(obj)
console.log(obj.p)

let arr = [
    {a: 1},
    [1, 2, 3],
    function () {
        return true;
    }
];

for (i in arr) {
    console.log(typeof arr[i])
}

console.log(arr)
arr = []
console.log(arr)

let colors = ['red', 'green', 'blue'];
colors.forEach(function (color){
    console.log(color)
})