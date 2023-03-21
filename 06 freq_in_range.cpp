// Leetcode ques=>  Range Frequency Queries

// Design a data structure to find the frequency of a given value in a given subarray.

// Implement the RangeFreqQuery class:
// 1. RangeFreqQuery(int[] arr) Constructs an instance of the class.
// 2. int query(int left, int right, int value) Returns the frequency of 'value' in the subarray arr[left...right]


ANSWER:
2 methods -> simple map
          -> segment tree




// Map method:

class RangeFreqQuery {
public:
    map<int,vector<int>>m;
    
    RangeFreqQuery(vector<int>& arr) {
        for(int i=0;i<arr.size();i++)
            m[arr[i]].push_back(i);
    }
    
    int query(int left, int right, int value) {
        if(m.find(value) == m.end())
            return 0;
        int st = lower_bound(m[value].begin(), m[value].end(), left) - m[value].begin();
        int end = upper_bound(m[value].begin(), m[value].end(), right) - m[value].begin();
        return end-st;
    }
};
