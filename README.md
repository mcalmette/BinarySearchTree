# BinarySearchTree


## Class Setup
```
cmake CMakeLists.txt
make
```
To use the test file:
```
./bstTest
```

To use the performance test:
```
./bstPerf rand-50k.txt
```

## About this project
Binary Search tree with key-value nodes - uses a mix of iterations and recursion through helper inorder/preorder copies to do the following functions:
- add
- remove
- find
- range find
- keys (returns all keys by reference)
- sort (ascending order)
- size


The test file is used as a way to ensure that each function works with different test cases.  The performance file is used to find the speed and number of calls for each function. This can be used with a randomly generated key-value pairs that ranges from 10k pairs to 50k pairs.

Note: Need to have Cmake installed

# 50k items Performance - Test Results
=============

  Add Calls...: 50000
  
  Add Time....: 81311 microseconds
  
  Add Average.: 1.62622 microseconds


  Remove Calls...: 2000
  
  Remove Time....: 1155 microseconds
  
  Remove Average.: 0.5775 microseconds


  Find Calls...: 2000
  
  Find Time....: 945 microseconds
  
  Find Average.: 0.4725 microseconds


  Range Calls...: 1
  
  Range Time....: 4191 microseconds
  
  Range Average.: 4191 microseconds

  Sort Calls...: 1
  
  Sort Time....: 6065 microseconds
  
  Sort Average.: 6065 microseconds
  
  Tree Height: 1006
