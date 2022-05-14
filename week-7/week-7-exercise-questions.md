# Week 7 - Exercise 7: Interview questions

## R.6. What are the uses of the keyword static?

In functions: create a variable which is only accessible in the function but whose value persists across multiple function calls

Otherwise: create a global variable that is not accessible by other files

Correction: Static functions are only accessible inside the module

## R.2 Write the ‘standard’ MIN macro. That is, a macro that takes two arguments and returns the smaller of the two arguments.

`#define MIN(X,Y) ( (X < Y) ? (X) : (Y) )`

Correction: Use smaller than and not smaller and equal than

