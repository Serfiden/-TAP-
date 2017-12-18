#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

using namespace std;

struct show {
	int start;
	int finish;
	int profit;

	bool operator==(const show& toCompare) {
		if (start == toCompare.start)
			if (finish == toCompare.finish)
				return 1;
		return 0;
	}
};

void displayMatrix(vector<vector<int> > &matrix) {
	for (int i = 0; i < matrix.size(); i ++) {
		for (int j = 0; j < matrix[i].size(); j ++) 
			cout << matrix[i][j] << " ";
		cout << endl;
	}
}

bool showCompatibility(show &a, show &b) {
	if (a.finish < b.start) return 1;
	return 0;
}

int showsBinarySearch(vector<show> &array, show lookFor, int leftLimit) {
	int left = leftLimit;
	int right = array.size() - 1;

	if (array[left] == lookFor) return left;

	else if (array[right] == lookFor) return right;

	else while (left < right) {
		int middle = (left + right) / 2;
	
		if (array[middle] == lookFor) return middle;

		else if (array[middle].finish < lookFor.finish) left = middle;

		else right = middle; 
	}

	return -1;
}

int modifiedBinarySearch(vector<show> &array, int lookFor) {
	int left = 1;
	int right = array.size();

	if (lookFor > array[right].finish) return right;
	
	else if (lookFor < array[left - 1].finish) return -1;
	
	else while (left < right) {
		int middle = (left + right) / 2;

		if (array[middle].finish < lookFor && lookFor < array[middle + 1].finish) return middle;
		
		else if (array[middle - 1].finish < lookFor && lookFor < array[middle].finish) return middle - 1;

		else if (array[left - 1].finish < lookFor && lookFor < array[left].finish) return left;
		
		else if (array[right - 2].finish < lookFor && lookFor < array[right - 1].finish) return right - 1;
		
		else if (array[middle].finish < lookFor) left = middle;

		else if (lookFor < array[middle].finish) right = middle; 
	}

	return -1;
}

int compareUtility(const void* a, const void* b) {
	show* first = (show*)a;
	show* second = (show*)b;
	return (first -> finish - second -> finish);
}

int showScheduling(vector<show> &shows) {

	/* First we will use the scheduleMapping matrix to store road lengths. We will start
	computing such lengths starting with the final row. If a given cell, of index [i][j]
	has the value x, it means that the best partial schedule that starts with the activity
	shows[j] and is followed by shows[i] has the "length" x */

	vector<vector<int> > scheduleMapping(shows.size(), vector<int>(shows.size() + 1));

	/* The vector bestPartialRoads is an extension of the 'shows' array. If this array 
	stores the show A at the index i, it means that the best schedule that contains 
	the show shows[i] also contains the show A, as the following show (basically using this
	array to rebuild the solution, once the matrix is fully computed)*/

	vector<show> bestPartialRoads(shows.size());

	// The first column will store the initial profit of each show 

	for (int i = 0; i < shows.size(); i ++)
		scheduleMapping[i][0] = shows[i].profit;

	// Start computing lengths

	for (int i = scheduleMapping.size() - 1; i >= 0; i --) {			// start the computation with the final matrix row

		int start = modifiedBinarySearch(shows, shows[i].start);		// the shows array will be sorted when this occurs, so the binary search		
																				// will work as intended
		for (int j = 1; j <= start + 1; j ++) {
			if (showCompatibility(shows[j - 1], shows[i])) {			
				scheduleMapping[i][j] = scheduleMapping[i][0] + shows[j - 1].profit;
				if (scheduleMapping[i][j] > scheduleMapping[j - 1][0]) {		// if we just computed a schedule that has a higher profit
					scheduleMapping[j - 1][0] = scheduleMapping[i][j];
					bestPartialRoads[j - 1] = shows[i];
				}
			}
		}
	}

	// Rebuilding solution 

	int maxProfit = 0;
	int maxProfitIndex;

	for (int i = 0; i < shows.size(); i ++) {
		if (scheduleMapping[i][0] > maxProfit) {
			maxProfit = scheduleMapping[i][0]; 
			maxProfitIndex = i;
		}
	}

	displayMatrix(scheduleMapping);

	cout << maxProfit << endl;

	while (maxProfit) {
		maxProfit -= shows[maxProfitIndex].profit;
		cout << shows[maxProfitIndex].start << " " << shows[maxProfitIndex].finish << endl;
		maxProfitIndex = showsBinarySearch(shows, bestPartialRoads[maxProfitIndex], maxProfitIndex + 1);
	}

}

int main() {
	ifstream f("shows.in");
	int n;
	f >> n;

	show showsArray[n];

	for (int i = 0; i < n; i ++) {
		f >> showsArray[i].start;
		f >> showsArray[i].finish;	
		f >> showsArray[i].profit;
	}

	qsort(showsArray, n, sizeof(show), compareUtility);	

	vector<show> shows(n);
	for (int i = 0; i < n; i ++) 
		shows[i] = showsArray[i];

	showScheduling(shows);

	return 0;
}