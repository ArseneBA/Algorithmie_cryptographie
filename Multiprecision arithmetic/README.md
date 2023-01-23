# Multiprecision arithmetic

Implement multiprecision arithmetic. A word is considered to be 64bits. We will represent our numbers as tables of words.

For the addition of two words, we will use the intrsics Guide of Intel (https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html).

## Functions

- **nus_mul :** We have to take care of memory management. Because each time that we call :  nus_mul_llu or nus_add, we allocate a new nus. As a result for the temp of type nus we have to clear it at the end of each loop for. (It will be reallocated at each use of nus_mul_llu).
    We have the same phenomenon happing for the res (c) nus, to prevent memory leakage, we will use a variable storing the adress of the res structure used to store the data from a loop to another one.
  