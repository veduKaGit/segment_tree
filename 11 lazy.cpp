



#define MAX 1000

int tree[MAX] = {0}; // To store segment tree
int lazy[MAX] = {0}; // To store pending updates

/* si -> index of current node in segment tree
	ss and se -> Starting and ending indexes of elements for which current nodes stores sum.
	us and ue -> starting and ending indexes of update query
	diff -> which we need to add in the range us to ue */
void updateRangeUtil(int si, int ss, int se, int us, int ue, int diff)
{
	if (lazy[si] != 0)   //pending lazy updates  => make sure that pending updates are done before making new updates
	{  
		tree[si] += (se-ss+1)*lazy[si];  //update the sum in range 
	
		if (ss != se)  //check if leaf node => if yes, we cannot go further
		{
			// We can postpone updating children we don't need their new values now.
			lazy[si*2 + 1] += lazy[si];
			lazy[si*2 + 2] += lazy[si];
		}
	
		lazy[si] = 0;  //remove lazy for curent node
	}

	if (ss>se || ss>ue || se<us)     //DOUBT_1
		return ;
	
	if (ss>=us && se<=ue)   // Current segment is fully in range
	{
		tree[si] += (se-ss+1)*diff;
	
		if (ss != se)
		{
			lazy[si*2 + 1] += diff;
			lazy[si*2 + 2] += diff;
		}

		//  lazy[si] = 0;  //DOUBT_2
		
		return;
	}

	int mid = (ss+se)/2;
	updateRangeUtil(si*2+1, ss, mid, us, ue, diff);
	updateRangeUtil(si*2+2, mid+1, se, us, ue, diff);
	
	tree[si] = tree[si*2+1] + tree[si*2+2];
}



/* 	si --> Index of current node in the segment tree.
	ss & se --> Starting and ending indexes of the segment represented by current node
	qs & qe --> Starting and ending indexes of query range 
 */
int getSumUtil(int ss, int se, int qs, int qe, int si)
{
	if (lazy[si] != 0)
	{
		tree[si] += (se-ss+1)*lazy[si];

		if (ss != se)
		{
			lazy[si*2+1] += lazy[si];
			lazy[si*2+2] += lazy[si];
		}

		lazy[si] = 0;
	}

	// Out of range
	if (ss>se || ss>qe || se<qs)
		return 0;

	// At this point we are sure that pending lazy updates
	// are done for current node. So we can return value
	// (same as it was for query in our previous post)

	// If this segment lies in range
	if (ss>=qs && se<=qe)
		return tree[si];

	// If a part of this segment overlaps with the given
	// range
	int mid = (ss + se)/2;
	return getSumUtil(ss, mid, qs, qe, 2*si+1) + getSumUtil(mid+1, se, qs, qe, 2*si+2);
}


// constructs Segment Tree for array[ss..se]. si is index of current node in segment tree 
void constructSTUtil(int arr[], int ss, int se, int si)
{
	// out of range as ss can never be greater than se
	if (ss > se)
		return ;

	if (ss == se)
	{
		tree[si] = arr[ss];
		return;
	}

	int mid = (ss + se)/2;
	constructSTUtil(arr, ss, mid, si*2+1);
	constructSTUtil(arr, mid+1, se, si*2+2);

	tree[si] = tree[si*2 + 1] + tree[si*2 + 2];
}

