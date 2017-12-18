#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

struct dominoListNode{
	int first;
	int second;
	int length;
	int carriedSets;				// here we will store the sets with the same prefix of identical length, since we will only be storing one such set for each prefix
	dominoListNode* prev;
};

int arrayInitialization(vector<dominoListNode*> &dominos, ifstream &file) {
	int piecesNumber;
	file >> piecesNumber;

	for (int i = 0; i < piecesNumber; i ++) {
		dominoListNode* newPiece = new dominoListNode;
		file >> newPiece -> first;
		file >> newPiece -> second;
		newPiece -> prev = NULL;
		newPiece -> length = 1;
		newPiece -> carriedSets = 1;
		dominos.push_back(newPiece);
	}

	return 0;
}

int longestChain(vector<dominoListNode*> &dominos) {
	unordered_map<int, dominoListNode*> dominoChains;

	for (int i = dominos.size() - 1; i >= 0; i --) {
		if (dominoChains.count(dominos[i] -> second) == 0) {   // if there is no existent subset to connect to the current domino piece
			if (!dominoChains.count(dominos[i] -> first) || dominoChains[dominos[i] -> first] -> length == 1) {       // and we won't be replacing a pre-existent subset that has the same prefix
				dominos[i] -> carriedSets += 1;
				dominoChains[dominos[i] -> first] = dominos[i];
			}
		} else {												// if we can attach this domino piece to another pre-existent subset
			dominos[i] -> length += dominoChains[dominos[i] -> second] -> length; // update the potential new substring length

			if (dominoChains.count(dominos[i] -> first)) { // if we have to make a choice between what subset with the given prefix to keep in map
				if (dominoChains[dominos[i] -> first] -> length <= dominos[i] -> length) {			// if we detected a longer subset
					if (dominoChains[dominos[i] -> first] -> length == dominos[i] -> length) {
						dominos[i] -> carriedSets += dominoChains[dominos[i] -> first] -> carriedSets;			// if we consider a different set with the same prefix and equal length
					}
					dominos[i] -> prev = dominoChains[dominos[i] -> second];
					dominoChains[dominos[i] -> first] = dominos[i];
				}
			} else {
				dominos[i] -> carriedSets = dominoChains[dominos[i] -> second] -> carriedSets;		// when we attach a regular existent subset to a new domino piece
				dominos[i] -> prev = dominoChains[dominos[i] -> second];
				dominoChains[dominos[i] -> first] = dominos[i];
			}
		}
	}



	return 0;
}

int main() {
	vector<dominoListNode*> myArray;
	ifstream file("dominos.in");

	arrayInitialization(myArray, file);
	longestChain(myArray);

	int maxIndex;
	int maxSize = 0;

	for (int i = 0; i < myArray.size(); i ++) {
		if (myArray[i] -> length > maxSize) {
			maxSize = myArray[i] -> length;
			maxIndex = i;
		}
	}

	dominoListNode* iterator = myArray[maxIndex];
	while(iterator != NULL) {
		cout << iterator -> first << " " << iterator -> second << endl;
		iterator = iterator -> prev;
	}

	cout << myArray[maxIndex] -> carriedSets;

	return 0;
}

