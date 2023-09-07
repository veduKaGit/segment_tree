// given array
//we can do 2 operations => update value at certain index
//                       => find MAX sum in a range


#include<bits/stdc++.h>
using namespace std;

vector<vector<long long int>>tree(400010, vector<long long int>(4, 0));  //tree[i] => {tot_sum, max_sum, max_prefix_sum, max_suffix_sum}

void merge(int i){
    tree[i][0] = tree[2*i+1][0] + tree[2*i+2][0]; //tot_sum
    tree[i][1] = max({tree[2*i+1][1], tree[2*i+2][1], tree[2*i+1][3]+tree[2*i+2][2]}); //max_sum = max({ max_of_left_half, max_of_right_half, max_of_suffix_of_left + max_of_prefix_of_right })
    tree[i][2] = max(tree[2*i+1][2], tree[2*i+1][0]+tree[2*i+2][2]);  //max_prefix_sum = max( max_of_prefix_of_left, total_left_sum + max_of_prefix_of_right )
    tree[i][3] = max(tree[2*i+2][3], tree[2*i+2][0]+tree[2*i+1][3]);   //max_suffix_sum = max( max_of_suffix_of_right , total_right_sum + max_suffix_sum_of_left) 
}

void construct(int i, int l, int r, vector<long long int>&arr){
    if(l>r)  //base case
        return;
    if(l==r){   //base case
        tree[i][0] = arr[l];
        tree[i][1] = max(0LL,arr[l]);
        tree[i][2] = arr[l];
        tree[i][3] = arr[l];
        return;
    }

    int mid = l + (r-l)/2;
    construct(2*i+1, l, mid, arr);
    construct(2*i+2, mid+1, r, arr);

    merge(i);
}

vector<long long int> max_range(int i, int l, int r, int ogl, int ogr){
    if(l>r)  //base case
        return {0, 0, 0, 0};
    if(l>ogr || r<ogl)  //base case
        return {0, 0, 0, 0};
    if(l>=ogl && r<=ogr)  //base case => IMP 
        return tree[i];
    
    int mid = l+(r-l)/2;
    max_range(2*i+1, l, mid, ogl, ogr);
    max_range(2*i+2, mid+1, r, ogl, ogr);

    merge(i);

    return tree[i];
}

void update(int i, int l, int r, int ind, long long val){
    if(l>r)
        return;
    if(ind<l || ind>r)
        return;
    if(l==r){
        tree[i][0] = val;
        tree[i][1] = max(0LL, val);
        tree[i][2] = val;
        tree[i][3] = val;
        return;
    }

    int mid = l+(r-l)/2;
    update(2*i+1, l, mid, ind, val);
    update(2*i+2, mid+1, r, ind, val);

    merge(i);
}

int main(){
    int n, m;
    cin >> n >>m;

    vector<long long int >arr(n);
    vector<vector<long long int>>q(m);

    for(int i=0;i<n;i++){
        int x;
        cin>>x;
        arr[i] = x;
    }

    for(int i=0;i<m;i++){
        long long int  ind, v;
        cin>>ind>>v;
        q[i] = {ind, v};
    }

    construct(0, 0, n-1, arr);
    cout<<max_range(0, 0, n-1, 0, n-1)[1]<<endl;

    for(int i=0;i<m;i++){
        int ind = q[i][0], val = q[i][1];
        
        update(0, 0, n-1, ind, val);
        cout<<max_range(0, 0, n-1, 0, n-1)[1]<<endl;
    }
    
    return 0;
}
