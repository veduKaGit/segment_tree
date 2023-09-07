#include<bits/stdc++.h>
using namespace std;

vector<int>tree(400010);

void construct(int i, int l, int r, vector<int>&arr){
    if(l>r) 
        return;
    if(l==r){
        tree[i] = arr[l];
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
        tree[i] = 1 - tree[i];
        arr[l] = 1 - arr[l]; //toggle
        return;
    }

    int mid = l+(r-l)/2;
    update(2*i+1, l, mid, ind, arr);
    update(2*i+2, mid+1, r, ind, arr);

    tree[i] = tree[2*i+1] + tree[2*i+2];
}

int k_th(int node ,int kth, int st, int sp){

        if(st == sp) return st ;

        int lft = (node << 1) +1;
        int rght = lft + 1;
        int mid = st + ((sp-st)>>1) ;

        if(tree[lft] >= kth){
            return k_th(lft,kth,st,mid) ;
        }
        else{
            return k_th(rght,kth-tree[lft],mid+1,sp) ;
        }

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
            cout<< k_th(0,y+1, 0, n-1) <<endl;
        }
   
    }

    return 0;
}
