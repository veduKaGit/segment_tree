//IMP NOTE: say given array has size = N, then the seg. tree array will have size <= 4*N !!!!
//actually 4N se kam rahega-> 4N is upper bound


// [ss,se] is range of indices in which we do the operation
// si is the index in the seg. tree array
int CST(int ss, int se, int si, int arr[], int tree[])  
{
	if(ss == se){
		tree[si] = arr[ss];
		return arr[ss];
	}

	int mid = (ss + se) / 2;

	tree[si] = CST(ss, mid, 2*si+1, arr, tree) + CST(mid + 1, se, 2*si+2, arr, tree);  //for [ss,mid] -> 2*si+1, and [mid+1,se] -> 2*si+2
	//why are we adding both? -> since in this example, we are considering SUM in the range-> thus total sum = sum of left and right halves
	
	//also notice, since we are assigning value to tree[si], thus some nodes in tree array may NOT be assigned a value(dummy nodes) -> see 02_imp.png
	
	return tree[si]; //return tree[si] -> since in this example, we are considering sum in the range [ss,se]
}	
	
int main() {
	int arr[] = {10, 20, 30, 40}, n= 4;

    	int tree[4 * n];   //see 4*N is assigned as size of seg tree array
	
    	cout << CST(0, n - 1, 0, arr, tree) << endl; //initially si = 0
		
	return 0;
}
