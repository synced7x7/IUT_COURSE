// String - Text data
let greeting = "Hello World!";
let single = 'Single quotes work too';
let backticks = `Template literals ${greeting}`; // ES6
let emptyString = "";

// Number - Integers and decimals
let integer = 42;
let decimal = 3.14;
let negative = -15;
let scientific = 1.5e6;    // 1,500,000

// Special numeric values
let infinity = Infinity;
let negativeInfinity = -Infinity;
let notANumber = NaN;      // Result of invalid math operations

// BigInt - For very large integers (> 2^53)
let bigInt = 9007199254740991n;
let hugeNumber = 1234567890123456789012345678901234567890n;

// Boolean - true/false
let isLogged = true;
let hasPermission = false;

// Undefined - Variable declared but not assigned
let undefinedVar;
console.log(undefinedVar); // undefined

// Null - Intentional absence of value
let nullVar = null;

// Symbol - Unique identifier (ES6)
let sym1 = Symbol("id");
let sym2 = Symbol("id");
console.log(sym1 === sym2); // false (unique)




//Non-Primitive (Reference) Types
// Object - Collection of key-value pairs
let person = {
    name: "Alice",
    age: 30,
    isStudent: false,
    greet: function() {
        return `Hello, I'm ${this.name}`;
    }
};

// Array - Ordered list
let fruits = ["apple", "banana", "orange"];
let mixed = [1, "text", true, null];

// Function - Callable object
function add(a, b) {
    return a + b;
}

// Date
let today = new Date();

// Regular Expression
let pattern = /javascript/i;






// When using operators with different types
console.log("5" + 3);      // "53" (string concatenation)
console.log("5" - 3);      // 2 (numeric subtraction)
console.log("5" * "2");    // 10 (numeric multiplication)
console.log("abc" - 1);    // NaN
console.log(true + 1);     // 2 (true becomes 1)
console.log(false + 1);    // 1 (false becomes 0)

// Loose vs Strict Equality
console.log(5 == "5");     // true (loose, converts types)
console.log(5 === "5");    // false (strict, checks type and value)