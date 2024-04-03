console.log("Hello, TypeScript!");
// Define a class
class Person {
    name: string;
    age: number;

    constructor(name: string, age: number) {
        this.name = name;
        this.age = age;
    }

    // Define a method
    sayHello() {
        console.log(`Hello, my name is ${this.name} and I am ${this.age} years old.`);
    }
}

// Create an instance of the class
const person = new Person("John", 25);

// Call the method
person.sayHello();