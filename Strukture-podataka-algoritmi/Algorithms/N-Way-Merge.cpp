#include <iostream>
#include <vector>
using namespace std;

vector<int> Two_Way_Merge(vector<int> A, vector<int> B) {

	vector<int> resultList;

	int i = 0, j = 0;	// counters for traversing the lists A and B
	
	// the while loop exits as soon as one of the two lists ends
	while (i < A.size() && j < B.size()) {
		if (A[i] <= B[j]) {
			resultList.push_back(A[i]);
			i++;
		}
		else {
			resultList.push_back(B[j]);
			j++;
		}
	}

	// after the while loop is finished, the rest of the other list, if it exists, is blindly copied into the result list
	while (i < A.size()) {
		resultList.push_back(A[i]);
		i++;
	}

	while (j < B.size()) {
		resultList.push_back(B[j]);
		j++;
	}

	return resultList;
}


// left and right are indices of our current function call that tell us to which array the first and last pointer "point to"
vector<int> N_Way_Merge(vector<vector<int>> arrays, int left, int right) {
	// base case which tells us that both indices 'left' and 'right' point to the same array(vector) in the arrays vector
	if (left == right)
		return arrays[left];

	// mid point is calculated so that the array of arrays can be split up into two (un)equal parts
	int mid = (left + right) / 2;

	// We can think of this as a binary tree
	//
	// N_Way_Merge is called recursively up until the most left child is accessed
	// When the most left leaf is accessed, left = right, which means that the base case is fulfilled, hence making the leftArray the most left leaf
	// After that the other recursive call is being called up until the most left node's sibling is accessed (so that would be the right node)
	// Then, the same way leftArray is determined, the right node fulfills the base case left = right and it becomes rightArray
	// After the two recursive call, we end up calling the Two_Way_Merge, which constructs a resultArray from these two and it is stored in their parent, so it essentially backtracks up the tree
	// This process is repeated until we get another "same-rank" array (in terms of binary tree rank/height) which we then also "Two_Way_Merge" up, all until we are left with one singular array that contains all elements from all arrays that N_Way_Merge was called on

	vector<int> leftArray = N_Way_Merge(arrays, left, mid);
	vector<int> rightArray = N_Way_Merge(arrays, mid + 1, right);

	return Two_Way_Merge(leftArray, rightArray);
}


int main() {
	
	vector<vector<int>> Arrays = {
		{1,2,3,4,5},
		{2,3,11,16,18},
		{-5,-2,0,15,100},
		{1,1,1,1,1},
		{-200,0,1,86,88}
	};

	vector<int> result = N_Way_Merge(Arrays, 0, Arrays.size() - 1);
	for (int i = 0; i < result.size(); i++) {
		cout << result[i] << " ";
	}
	cout << endl;

	return 0;
}