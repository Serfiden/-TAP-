#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int mapSubsequentSums(vector<vector<int> > &sets, int finalSum) {
	vector<vector<int> > partialSumMapping(sets.size(), vector<int>(finalSum));

	for (int i = 0; i < sets[0].size(); i ++) {			// manually filling the first row
		if (sets[0][i] <= finalSum) 
			partialSumMapping[0][sets[0][i]] = sets[0][i];
	}

	// partialSumMap construction

	for (int i = 1; i < partialSumMapping.size(); i ++) {	// each row is equivalent to the partial sums formed with the elements
															// of the i-th set

		for (int currentSubsetIndex = 0; currentSubsetIndex < sets[i].size(); currentSubsetIndex ++ )   // for each element of the i-th set
			for (int possibleSums = 0; possibleSums < finalSum; possibleSums ++) {														// search a valid partial sum to attach the element to
				if(partialSumMapping[i - 1][possibleSums]) {           // we only need to add to already existent partial sums			
					int newPartialSum = possibleSums + 1 + sets[i][currentSubsetIndex];		// new partial sum that has to be validated
					if (newPartialSum <= finalSum) 
						partialSumMapping[i][newPartialSum - 1] = sets[i][currentSubsetIndex];
				}
			}
	}

	// path reconstruction 

	if (partialSumMapping[sets.size() - 1][finalSum - 1] == 0) {
		cout << "Could not find a set with the given sum!";
		return 1;
	}

	int reconstructionSum = finalSum;
	int currentArray = sets.size() - 1;
	vector<int> solution;	

	while (reconstructionSum && currentArray >= 0) {
		solution.push_back(partialSumMapping[currentArray][reconstructionSum - 1]);
		reconstructionSum -= partialSumMapping[currentArray][reconstructionSum - 1];
		currentArray --;
	}

	for (int i = solution.size() - 1; i >= 0; i --)
		cout << solution[i] << " ";
	return 0;
}

int main() {
	ifstream f("subsets.in");

	int numberOfArrays;
	int finalSum;
	int currentChar = 0;
	int currentArrayIndex = 0;

	f >> numberOfArrays;
	f >> finalSum;

	vector<vector<int> > arrays(numberOfArrays);

	for (int i = 0; i < numberOfArrays; i ++) {
		int dummy;
		f >> dummy;
		arrays[i].resize(dummy);
	}
	
	for (int i = 0; i < numberOfArrays; i ++)
		for (int j = 0; j < arrays[i].size(); j ++) 
			f >> arrays[i][j];

	mapSubsequentSums(arrays, finalSum);
}