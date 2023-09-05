//2 types of queries:
//type 1=> {1 i v} => means set the element with index i to v
//type 2=> {2 l r} => calculate the minimum AND number of elements equal to minimum of elements with indices from l to (r−1)

//For each operation of the second type print two integers: the minimum on a segment, and the number of elements equal to minimum.



#include<bits/stdc++.h>
using namespace std;

vector<vector<int>>tree(400010, vector<int>(2, INT_MAX)); //tree[i] => {min_val, cnt_of_min_val}

void construct(int i, int l, int r, vector<int>&arr){
    if(l>r)  //base case
        return;
    if(l==r){  //base case
        tree[i][0] = arr[l];
        tree[i][1] = 1;
        return;
    }

    //recursion
    int mid = l+(r-l)/2;
    construct(2*i+1, l, mid, arr);
    construct(2*i+2, mid+1, r, arr);

    //merge the 2 child nodes in seg tree -> to form a parent node
    if(tree[2*i+1][0] < tree[2*i+2][0]){  
        tree[i][0] = tree[2*i+1][0];
        tree[i][1] = tree[2*i+1][1];
    }else if(tree[2*i+1][0] > tree[2*i+2][0]){
        tree[i][0] = tree[2*i+2][0];
        tree[i][1] = tree[2*i+2][1];
    }else{
        tree[i][0] = tree[2*i+2][0];
        tree[i][1] = tree[2*i+2][1] + tree[2*i+1][1];
    }
}

void update(int i, int l, int r, int val, int ind, vector<int>&arr){
    if(l>r)  //base case
        return;
    if(ind<l || ind>r)  //base case
        return;
    if(l==r){  //base case
        arr[l] = val;
        tree[i][0] = val;
        tree[i][1] = 1;
        return;
    }

    //recursion
    int mid = l+(r-l)/2;
    update(2*i+1, l, mid, val, ind, arr);
    update(2*i+2, mid+1, r, val, ind, arr);

    //merge the 2 child nodes in seg tree -> to form a parent node
    if(tree[2*i+1][0] < tree[2*i+2][0]){
        tree[i][0] = tree[2*i+1][0];
        tree[i][1] = tree[2*i+1][1];
    }else if(tree[2*i+1][0] > tree[2*i+2][0]){
        tree[i][0] = tree[2*i+2][0];
        tree[i][1] = tree[2*i+2][1];
    }else{
        tree[i][0] = tree[2*i+2][0];
        tree[i][1] = tree[2*i+2][1] + tree[2*i+1][1];
    }
}

vector<int> range(int i, int l, int r, int ogl, int ogr){  //val, cnt
    if(l>r)  //base case
        return {INT_MAX, 0};
    if(r<ogl || l>ogr)  //base case
        return {INT_MAX, 0};
    if(l>=ogl && r<=ogr){  //base case  => IMP => if all lies inside the range
        return tree[i];
    }
    
    //recursion
    int mid = l+(r-l)/2, min_val = INT_MAX, cnt = 0;
    vector<int>a = range(2*i+1, l, mid, ogl, ogr);
    vector<int>b = range(2*i+2, mid+1, r, ogl, ogr);

    //merge the 2 child nodes in seg tree -> to form a parent node
    if(a[0] < b[0]){
        min_val = a[0];
        cnt = a[1];
    }else if(a[0] > b[0]){
        min_val = b[0];
        cnt = b[1];
    }else{
        min_val = a[0];
        cnt = a[1]+b[1];
    }

    return {min_val, cnt};
}


int main() {
    int n, m;
    cin >> n >>m;
    vector<int>arr(n);
    vector<vector<int>>q(m);

    for(int i=0;i<n;i++){
        int x;
        cin>>x;
        arr[i] = x;
    }

    for(int i=0;i<m;i++){
        int a, b, c;
        cin>>a>>b>>c;
        q[i] = {a, b, c};
    }

    construct(0, 0, n-1, arr);   //construct the seg tree with initial array

    for(int i=0;i<m;i++){
        int a = q[i][0], b = q[i][1], c = q[i][2];
        if(a==1){ //update
            update(0, 0, n-1, c, b, arr);
        }else{  //range
            vector<int>temp = range(0, 0, n-1, b, c-1);
            cout<<temp[0]<<" "<<temp[1]<<endl;
        }
    }
    
    return 0;
}

