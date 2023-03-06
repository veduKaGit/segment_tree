// basically, we are given an index to update its value(in the main array) -> we need to update the whole segment tree

// Time complexity: O(log N)

//we are considering the same example-> sum in a range of indices -> thats how we have constructed our segment tree




int CST(int ss, int se, int si, int arr[], int tree[])  //seg tree construction
{
	if(ss == se){
		tree[si] = arr[ss];
		return arr[ss];
	}

	int mid = (ss + se) / 2;

	tree[si] = CST(ss, mid, 2 * si + 1, arr, tree) + CST(mid + 1, se, 2 * si + 2, arr, tree);

	return tree[si];
}

// [ss,se] is the range of indices we are considering in the main array
// si is the current index of seg tree array 
// i is the index in main array we want to update -> unchanged during recursion
// diff = (new_val - old_val) -> unchanged during recursion

void updateRec(int ss, int se, int i, int si, int diff, int tree[])
{
    if(i < ss || i > se)   // i is out of range
        return;
        
    tree[si] = tree[si] + diff;  // i lies in range [ss,se] -> so update tree[si] for that particular seg tree node (DONT update tree[i])
    
    if(se > ss)   //condn to check if its NOT leaf node, ie. that seg tree node has children
    {
        int mid = (ss + se) / 2;
        
        updateRec(ss, mid, i, 2*si+1, diff, tree);  //[ss,mid] -> 2*si+1
        updateRec(mid + 1, se, i, 2*si+2, diff, tree);   //[mid+1,se] -> 2*si+2
    }
}

	
int main() {
	int arr[] = {10, 20, 30, 40}, n= 4;

	int tree[4 * n];   //imp-> 4*N size of seg tree always
	
	CST(0, n - 1, 0, arr, tree);
	updateRec(0, 3, 1, 0, 5, tree);
		
	return 0;
}
