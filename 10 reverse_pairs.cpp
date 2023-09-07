// Given array of size n => numbers are from 1 to n
// 1 <= n <= 10^5

// Find for each i, the number of j, such that j<i and arr[j]>arr[i]
// Print n numbers, the i-th number is equal to the number of j such that j<i and arr[j] > arr[i]

// 3 METHODS TO SOLVE:

// 1. Ordered set -> traverse from left to right
//                -> for each arr[i] -> we have stored numbers on its left (ie. arr[j] for j<i) in the ordered_set
//                -> for each arr[i] -> we can find number of elements STRICTLY smaller than (arr[i] + 1), lets call it 'X'
//                -> so, for index i, the number of pairs = ( i - X )
//                -> do this for all indices

// 2. Merge Sort -> left half is sorted, right half is sorted
//               -> iterate over right half -> find number of elements in left half that are greater than right[i] (use lower/upper bound) 
//               -> add them to the answer
//               -> merge left and right halves
//               -> repeat

// 3. Segment Tree -> explained below


#include<bits/stdc++.h>
using namespace std;

vector<int>tree(400040);  

void update(int i, int l, int r, int ind){   
    if(ind<l || ind>r || l>r)
        return;
    if(l==r){
        tree[i]++;   //increment tree[i] => tree[i] is count of numbers present in range l to r
        return;
    }

    int mid = l+(r-l)/2;
    update(2*i+1, l, mid, ind);
    update(2*i+2, mid+1, r, ind);

    tree[i] = tree[2*i+1] + tree[2*i+2];
}

int range(int i, int l, int r, int ogl, int ogr){
    if(l>ogr || r<ogl || l>r)
        return 0;
    if(l==r)
        return tree[i];
    if(l>=ogl && r<=ogr)
        return tree[i];

    int mid = l+(r-l)/2;
    return range(2*i+1, l, mid, ogl, ogr) + range(2*i+2, mid+1, r, ogl, ogr);
}

int main(){
    int n;
    cin>>n;

    vector<int>arr(n);

    for(int i=0;i<n;i++){
        int x;
        cin>>x;
        arr[i] = x;
    }
    
    for(int i=0; i<n; i++){
        cout<< range(0, 0, 100000, arr[i]+1, 100001) <<" ";  //for index i (before using update function) -> we are printing count of elements in range (arr[i]+1 to 10^5)
        update(0, 0, 100000, arr[i]);
    }

    return 0;
}

