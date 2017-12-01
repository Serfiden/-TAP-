#include <iostream>
#include <limits.h>
#include <algorithm>
#include <fstream>
#include <vector>

using namespace std;

typedef struct{
	float left;
	float right;
} pairs;

int evaluatePair(pairs a, pairs b) {
	if (a.left < b.right && a.right > b.left) return 0;
	else if (a.left > b.right) return -1;
	return 1;
}	

float findMedianArrays(std::vector<int> &firstArray, std::vector<int> &secondArray){
	int totalLength = firstArray.size() + secondArray.size();

	int lowerBound = 0;
	int higherBound = firstArray.size();
	while (lowerBound <= higherBound) {
		int firstPartitionPoint = (lowerBound + higherBound) / 2;
		int secondPartitionPoint = (totalLength + 1) / 2 - firstPartitionPoint;

		pairs firstMedianPair, secondMedianPair;
	
		firstMedianPair.left = (firstPartitionPoint == 0) ? INT_MIN : firstArray[firstPartitionPoint - 1];
		firstMedianPair.right = (firstPartitionPoint == firstArray.size()) ? INT_MAX : firstArray[firstPartitionPoint];

		secondMedianPair.left = (secondPartitionPoint == 0) ? INT_MIN : secondArray[secondPartitionPoint - 1];
		secondMedianPair.right = (secondPartitionPoint == secondArray.size()) ? INT_MAX : secondArray[secondPartitionPoint];

		if (!evaluatePair(firstMedianPair, secondMedianPair)) {
			if (totalLength % 2 == 0) {
				return (max(firstMedianPair.left, secondMedianPair.left) + min(firstMedianPair.right, secondMedianPair.right)) / 2;
			} else return max(firstMedianPair.left, secondMedianPair.left);
		
		} else if (evaluatePair(firstMedianPair, secondMedianPair) == -1) {
			higherBound = firstPartitionPoint - 1;
		
		} else lowerBound = firstPartitionPoint + 1;
	}
}	

int main() {
	ifstream f;
	f.open("medianArrays.in");
	
	int n, m;
	f >> n;
	std::vector<int> v(n);

	for (int i = 0; i < n; i ++) f >> v[i];

	f >> m;
	std::vector<int> u(m);
	for (int i = 0; i < m; i ++) f >> u[i];

	cout << findMedianArrays(v, u);
}