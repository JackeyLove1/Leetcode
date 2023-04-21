let promise = new Promise(function (resolve, reject) {
    setTimeout(() => { resolve("done!"), 1000 });
})

promise.then(
    result => console.log(result),
    error => console.log(error)
);

let p2 = new Promise(function (resolve, reject) {
    setTimeout(() => reject(new Error("Whoops")), 100);
});
p2.then(
    result => console.log(result),
    error => console.error(error)
)

let p3 = new Promise(function (resolve, reject) {
    setTimeout(() => resolve(1), 1000);
});

p3.then(function (result) {
    console.log(result); // 1
});

