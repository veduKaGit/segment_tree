// 2 types of operations:
// -> 1 i : change the element with index i to the opposite (basically toggle if no. is present or not)
// -> 2 k : find the k-th one (ones are numbered from 0, it is guaranteed that there are enough ones in the array).

// For each operation of type (2 k), print the index of the corresponding one (all indices in this problem are from 0).


#include<bits/stdc++.h>
using namespace std;

vector<int>tree(400010);

void construct(int i, int l, int r, vector<int>&arr){   //tree[i] contains the count of numbers present in range l to r
    if(l>r) 
        return;
    if(l==r){
        tree[i] = arr[l];   //arr[l] is either 1 or 0
        return;
    }

    int mid = l + (r-l)/2;
    construct(2*i+1, l, mid, arr);
    construct(2*i+2, mid+1, r, arr);

    tree[i] = tree[2*i+1] + tree[2*i+2];
}

void update(int i, int l, int r, int ind, vector<int>&arr){
    if(ind<l || ind>r)
        return;
    if(l==r){
        tree[i] = 1 - tree[i]; //toggle
        arr[l] = 1 - arr[l]; //toggle
        return;
    }

    int mid = l+(r-l)/2;
    update(2*i+1, l, mid, ind, arr);
    update(2*i+2, mid+1, r, ind, arr);

    tree[i] = tree[2*i+1] + tree[2*i+2];
}

int k_th(int i ,int l, int r, int k){
    if(l == r) 
        return l;

    int mid = l+(r-l)/2;

    if(tree[2*i+1] >= k)  //if MORE (or equal) than k numbers are present in left half
        return k_th(2*i+1, l, mid, k) ;
    else  //if LESS than k numbers are present in left half
        return k_th(2*i+2, mid+1, r, k-tree[2*i+1]);
}

int main(){
    int n, m;
    cin>>n>>m;

    vector<int>arr(n);
    vector<vector<int>>q;

    for(int i=0;i<n;i++){
        int x;
        cin>>x;
        arr[i] = x;
    }

    for(int i=0;i<m;i++){
        int a, b;
        cin>>a>>b;
        q.push_back({a,b});
    }

    construct(0, 0, n-1, arr);  //construct segment tree
    
    for(int i=0;i<m;i++){
        int x = q[i][0], y = q[i][1];
        if(x==1){  //update
            update(0, 0, n-1, y, arr);
        }else{   //find kth one
            cout<< k_th(0, 0, n-1, y+1) <<endl;
        }
   
    }

    return 0;
}
