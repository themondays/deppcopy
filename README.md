Deppcopy is yet another native dependency for Node.js, written in C++ for making a full struct copies. This magnificent creation is designed to deliver blazing fast performance, especially when dealing with large data.

Its algorithmic prowess, combined with its native implementation, grants it the ability to conquer even the most formidable of data sets with ease and efficiency. This deppcopy is a tool that is not just fast, but also precise, meticulously copying every detail of the original data structure to a new one.

### Installation
```
npm install deppcopy
```

### Usage

```
const { deppCopy } = require('deppcopy');

console.log(deppCopy)

const test = {
  title: 'Test',
  items: [{id: 1}, {id: 2}]
}

const copy = deppCopy(test);


const title = 'Changed';

test.items.push({id: 4});

copy.items[0].id= 199;

console.log('Original', test);
console.log('Copied', copy);
```

