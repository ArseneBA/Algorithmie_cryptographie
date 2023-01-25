# Multiprecision arithmetic

Implement multiprecision arithmetic. A word is considered to be 64bits. We will represent our numbers as tables of words.

For the addition of two words, we will use the intrsics Guide of Intel (https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html).

Prbs : each time a multiplication or a division is made, a new variable is created.

## Functions

- **nus_mul :** We have to take care of memory management. Because each time that we call :  nus_mul_llu or nus_add, we allocate a new nus. As a result for the temp of type nus we have to clear it at the end of each loop for. (It will be reallocated at each use of nus_mul_llu).
    We have the same phenomenon happing for the res (c) nus, to prevent memory leakage, we will use a variable storing the adress of the res structure used to store the data from a loop to another one.

- **nus_mul_mod :** We use the Montgomery multiplication algorithm.
  Use of algorithm d'euclide étendu and bezo coefficient.
  Nombre de solinas : 2^192-2^64-1

# Note
During this project, I learned that quit logically, it is not possible to use unsigned int in a for (without adding another limit) because number reached are never negatives since it is unsigned.
