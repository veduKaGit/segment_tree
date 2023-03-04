used for FIXED size arrays

supports 2 types of operations:
1. range query....do something in a range...in O(log N) time
2. update a value.... O(log N)

Preprocessing time O(N)
Preprocessing space O(N)

  
  
Example:
given an array-> do 2 operations-> 1. find sum on range on index, and 2. update value at an index

Naive sol:
find sum in O(N)
update in O(1)
  
Prefix sum approach:
find sum in O(1)
update in O(N) => because we need to update whole prefix array


BEST sol=> segment tree
