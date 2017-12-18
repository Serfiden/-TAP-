#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <exception>
#include <vector>

using namespace std;

int threeWayMinimum(int a, int b, int c) {
	int partial = min(a, b);
	return min(partial, c);
}

/* DISCLAIMER: the homework required me to display every single step taken by the LevenshteinDistance procedure, which obviously
required a ton of verifications and whatnot. I am fully aware of how awful of a coding practice this is and how bad a ~150 lines
procedure looks, but I didn't have much of an option if I wanted to get full marks for this. */

/*
int displayPath(string &source, string &destination, int n, int m, int **a, int insertCost, int deleteCost, int substituteCost) {
	int i = n;
	int j = m;

	vector<string> operations;

	while(i > 0 || j > 0) {

		string newOperation;

		if (i == 0 && j != 0) {
			newOperation += "stergem ";
			newOperation += (char)source[j - 1];
			newOperation += '\n';
			j --;
		} else if (j == 0 && i != 0) {
			newOperation += "inseram ";
			newOperation += (char)destination[i - 1];
			newOperation += '\n';
			i --;
		} else if (a[i - 1][j - 1] == a[i - 1][j] && a[i - 1][j - 1] < a[i][j - 1]) {
			if (substituteCost <= insertCost) {
				if (a[i - 1][j - 1] == a[i][j]) {
					newOperation += "pastram ";
						newOperation += (char)source[j - 1];
					newOperation += '\n';
					i --;
					j --;
				} else {
					newOperation += "inlocuim ";
					newOperation += (char)source[j - 1];
					newOperation += " cu ";
					newOperation += (char)destination[i - 1];
					newOperation += '\n';
					i --;
					j --;
				}
			} else {
				newOperation += "inseram ";
				newOperation += (char)destination[i - 1];
				newOperation += '\n';
				i --;
			}
		} else if (a[i - 1][j - 1] == a[i][j - 1] && a[i - 1][j - 1] < a[i - 1][j]) {
			if (substituteCost <= deleteCost) {
				if (a[i - 1][j - 1] == a[i][j]) {
					newOperation += "pastram ";
					newOperation += (char)source[j - 1];
					newOperation += '\n';
					i --;
					j --;
				} else {
					newOperation += "inlocuim ";
					newOperation += (char)source[j - 1];
					newOperation += " cu ";
					newOperation += (char)destination[i - 1];
					newOperation += '\n';
					i --;
					j --;
				}
			} else {
				newOperation += "stergem ";
				newOperation += (char)source[i - 1];
				newOperation += '\n';
				j --;
			}
		} else if (a[i - 1][j] == a[i][j - 1] && a[i - 1][j] < a[i - 1][j - 1]) {
			if (insertCost <= deleteCost) {
				newOperation += "inseram ";
				newOperation += (char)destination[i - 1];
				newOperation += '\n';
				i --;
			} else {
				newOperation += "stergem ";
				newOperation += (char)source[i - 1];
				newOperation += '\n';
				j --;
			}
		} else if (a[i - 1][j] == a[i][j - 1] && a[i - 1][j] == a[i - 1][j - 1]) {
			if (substituteCost <= insertCost && substituteCost <= deleteCost) {
				if (a[i - 1][j - 1] == a[i][j]) {
					newOperation += "pastram ";
					newOperation += (char)source[j - 1];
					newOperation += '\n';
					i --;
					j --;
				} else {
					newOperation += "inlocuim ";
					newOperation += (char)source[j - 1];
					newOperation += " cu ";
					newOperation += (char)destination[i - 1];
					newOperation += '\n';
					i --;
					j --;
				}
			} else if (insertCost <= substituteCost && insertCost <= deleteCost) {
				newOperation += "inseram ";
				newOperation += (char)destination[i - 1];
				newOperation += '\n';
				i --;
			} else if (deleteCost <= substituteCost && deleteCost <= insertCost) {
				newOperation += "stergem ";
				newOperation += (char)source[i - 1];
				newOperation += '\n';
				j --;
			}
		} else if (a[i - 1][j - 1] < a[i - 1][j] && a[i - 1][j - 1] < a[i][j - 1]) {
			if (a[i - 1][j - 1] == a[i][j]) {
				newOperation += "pastram ";
				newOperation += (char)source[j - 1];
				newOperation += '\n';
				i --;
				j --;
			} else {
				newOperation += "inlocuim ";
				newOperation += (char)source[j - 1];
				newOperation += " cu ";
				newOperation += (char)destination[i - 1];
				newOperation += '\n';
				i --;
				j --;
			}
		} else if (a[i - 1][j] < a[i - 1][j - 1] && a[i - 1][j] < a[i][j - 1]) {
			newOperation += "inseram ";
			newOperation += (char)destination[i - 1];
			newOperation += '\n';
			i --;
		} else if (a[i][j - 1] < a[i - 1][j - 1] && a[i][j - 1] < a[i - 1][j]) {
			newOperation += "stergem ";
			newOperation += (char)source[i - 1];
			newOperation += '\n';
			j --;
		}

		operations.push_back(newOperation);
	}

	for (int i = operations.size() - 1; i >= 0; i --) 
		cout << operations[i];
}
*/

/*This procedure essentially computes the Levenshtein distance between the source and each prefix of the destination
The homework task assumes that the operations have different costs (given as input) so each computation will require some 
additional verifications.
*/

int LevenshteinDistance(string &source, string &destination, int insertCost, int deleteCost, int substituteCost) {
	int sourceLength = source.length();
	int destinationLength = destination.length();

	int **distanceMatrix = new int*[destinationLength + 1];
	for (int i = 0; i <= destinationLength; i ++) 
		distanceMatrix[i] = new int[sourceLength + 1];

	distanceMatrix[0][0] = 0;

	for (int i = 1; i <= sourceLength; i ++)
		distanceMatrix[0][i] = deleteCost * i;

	for (int i = 1; i <= destinationLength; i ++)
		distanceMatrix[i][0] = insertCost * i;

	for (int i = 1; i <= destinationLength; i ++)
		for (int j = 1; j <= sourceLength; j ++) {
			bool substitute;
			if (destination[i - 1] == source[j - 1])
				substitute = 0;
			else substitute = 1;

			int forInsertion = distanceMatrix[i][j - 1] + insertCost;
			int forDelete = distanceMatrix[i - 1][j] + deleteCost;
			int forSubstitution = distanceMatrix[i - 1][j - 1];
			if (substitute) forSubstitution += substituteCost;

			distanceMatrix[i][j] = threeWayMinimum(forInsertion, forDelete, forSubstitution);
		}

	cout << distanceMatrix[destinationLength][sourceLength] << endl;

//	displayPath(source, destination, destinationLength, sourceLength, distanceMatrix, insertCost, deleteCost, substituteCost);

	return distanceMatrix[destinationLength][sourceLength];

}

int main() {
	ifstream f("levenstein.in");
	string source, destination;
	int insertCost, deleteCost, substituteCost;

	f >> source;
	f >> destination;
	f >> insertCost;
	f >> deleteCost;
	f >> substituteCost;

	LevenshteinDistance(source, destination, insertCost, deleteCost, substituteCost);


}