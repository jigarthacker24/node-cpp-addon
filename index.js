const addon = require('./build/Release/addon.node');

// Test C API implementation
console.log('=== Testing C API Implementation ===');
console.log('Greet (C API):', addon.greetCAPI('Node.js'));

const calc = addon.calculate(10, 5);
console.log('Calculate (10, 5):', {
    sum: calc.sum,
    difference: calc.difference,
    product: calc.product,
    quotient: calc.quotient
});

// Test C++ Wrapper implementation
console.log('\n=== Testing C++ Wrapper Implementation ===');
console.log('Greet (C++):', addon.greetCPP('Node.js'));
console.log('User Info:', addon.getUserInfo());