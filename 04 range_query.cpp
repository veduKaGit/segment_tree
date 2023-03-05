//in this file, we see how to find the sum, provided a range


int CST(int ss, int se, int si, int arr[], int tree[])  //normal seg tree construction
{
	if(ss == se){
		tree[si] = arr[ss];
		return arr[ss];
	}

	int mid = (ss + se) / 2;

	tree[si] = CST(ss, mid, 2 * si + 1, arr, tree) + CST(mid + 1, se, 2 * si + 2, arr, tree);

	return tree[si];
}


// [qs,qe] range mei sum is required
// [ss,se] is the range under consideration
// si is the current index in the seg. tree array
int getSumRec(int qs, int qe, int ss, int se, int si, int tree[])  
{
	if(se < qs || ss > qe) //NO overlap bw the intervals [ss,se] and [qs,qe]
		return 0;
  
	if(qs <= ss &&  qe >= se)  //[ss,se] lies completely INSIDE
		return tree[si];

	int mid = (ss + se) / 2;

	return getSumRec(qs, qe, ss, mid, 2*si+1, tree) + getSumRec(qs, qe, mid + 1, se, 2*si+2, tree);  //[ss,mid] is left half, and [mid+1, se] is right half
}
	

int main() {
	int arr[] = {10, 20, 30, 40}, n= 4;

    int tree[4 * n];
    CST(0, n - 1, 0, arr, tree);
     
    cout << getSumRec(0, 2, 0, 3, 0, tree); 
		
	return 0;
}
