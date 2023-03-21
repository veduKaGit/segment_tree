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





// segment tree:

class RangeFreqQuery {
public:
    int n;
    vector<map<int, int>>seg;

    void construct(int l, int r, int i, vector<int>&arr){
        if(l==r){
            map<int,int>m;
            m[arr[l]]++;
            seg[i] = m;
            return;
        }

        int mid = (l+r)/2;

        construct(l, mid, 2*i+1, arr);
        construct(mid+1, r, 2*i+2, arr);

        map<int,int>m;
        m = seg[2*i+1];

        for(auto x: seg[2*i+2]){
            if(m.find(x.first) == m.end())
                m[x.first] = x.second;
            else
                m[x.first] += x.second;
        }

        seg[i] = m;
    }

    int freq(int l, int r, int i, int ql, int qr, int val){
        if(l>qr || r<ql)
            return 0;
        
        if(l>=ql && r<=qr)
            return seg[i][val];

        int mid = (l+r)/2;

        int left_half = freq(l, mid, 2*i+1, ql, qr, val);
        int right_half = freq(mid+1, r, 2*i+2, ql, qr, val);

        return left_half+right_half;
    }

    RangeFreqQuery(vector<int>& arr) {
        n = arr.size();
        map<int,int>m;
        seg = vector<map<int,int>>(4*n+1,m);
        construct(0, n-1, 0, arr);
    }
    
    int query(int left, int right, int value) {
        return freq(0, n-1, 0, left, right, value);
    }
};
