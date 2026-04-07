// 1. Function Declaration Call
function sayHello() {
    console.log("Hello World!");
}
sayHello(); // Parentheses () are required to call

// 2. Function Expression Call
const greetUser = function() {
    console.log("Welcome!");
};
greetUser();

// 3. Arrow Function Call
const showMessage = (name) => {
    console.log(`Message from ${name}`);
};
showMessage("Farzana");

// 4. Method Call (function as object property)
const person = {
    name: "John",
    sayName: function() {
        console.log("My name is " + this.name);
    }
};
person.sayName(); // Method call

// 5. Constructor Call (with 'new')
function Person(name, age) {
    this.name = name;
    this.age = age;
    this.introduce = function() {
        return `I'm ${this.name}, ${this.age} years old`;
    };
}

const john = new Person("John", 30);
console.log(john.introduce()); // "I'm John, 30 years old"

// 6. Chaining Function Calls
const calculator = {
    value: 0,
    add(num) {
        this.value += num;
        return this; // Return object for chaining
    },
    multiply(num) {
        this.value *= num;
        return this;
    },
    getValue() {
        return this.value;
    }
};

// Method chaining
const result = calculator.add(5).multiply(2).add(10).getValue();
console.log(result); // 20


// 7. Memoization: an optimization technique that speeds up function calls by caching the results of expensive function executions. If the same inputs are provided to a memoized function again, it returns the cached result instead of re-calculating it, thus improving performance. 
function memoize(fn) {
    const cache = {};
    return function(...args) { //...args allows the function to accept any number of arguments and automatically collects them into an array called args
        const key = JSON.stringify(args);
        if (cache[key]) {
            console.log("Returning cached result");
            return cache[key];
        }
        const result = fn(...args);
        cache[key] = result;
        return result;
    };
}

const expensiveCalc = memoize(function(n) {
    console.log("Calculating...");
    return n * n;
});

console.log(expensiveCalc(5)); // Calculating... 25
console.log(expensiveCalc(5)); // Returning cached result 25