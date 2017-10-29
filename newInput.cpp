#include <iostream>
#include <fstream>
#include <stack>
#include <vector>

using namespace std;

int displayStack (stack<int> subset){

	stack<int> reversed;

	while(!subset.empty()){
		int head = subset.top();
		subset.pop();
		reversed.push(head);
	}

	while(!reversed.empty()){
		cout << reversed.top() << " ";
		reversed.pop();
	}

	cout << endl;

	return 0;
}

int customBinarySearch (vector < stack<int> > &set, int valueToPut, int limit){

	int left = 0;
	int right = limit - 1;
	int mid;

	if (valueToPut > set[right].top()) return -1;

	else if (valueToPut <= set[left].top()) return 0;

	else while (left != right){	

		mid = (left + right) / 2;

		if (valueToPut == set[mid].top()) return mid;

		else if (valueToPut < set[mid].top())
			if (valueToPut > set[mid - 1].top()) return mid;
			else right = mid;

		else if (valueToPut > set[mid].top())
			if (valueToPut < set[mid + 1].top()) return mid + 1;
			else left = mid;

		if (valueToPut > set[right].top()) return -1;

		else if (valueToPut <= set[left].top()) return left;
	}

	return -1;
}


int minNumberSubsets (vector < stack<int> > &initial){

	vector< stack<int> >::iterator it = initial.begin();
	int numberIterator = 0;

	while (it + 1 != initial.end() && it != initial.end()){
		int modified = 0;

		int foundPlace = customBinarySearch(initial, (*(it + 1)).top(), numberIterator + 1);

		if (foundPlace >= 0){
			
			int toAdd = (*(it + 1)).top();
			(*(it + 1)).pop();
			initial.erase(it + 1);
			initial[foundPlace].push(toAdd);
			modified = 1;
		} 

		if (it + 1 != initial.end() && !modified){
			it ++;
			numberIterator ++;
		} 
	}

	return 0;
}

int main (int argc, char* argv[]){

	int n;
	ifstream f;

	for (int j = 1; j < argc; j ++){

		f.open(argv[j]);

		f >> n;

		vector< stack<int> > initialArray;

		for (int i = 0; i < n; i ++) { 
			stack<int> newNumber;
			int x;
			f >> x;
			newNumber.push(x);
			initialArray.push_back(newNumber);
		}

		minNumberSubsets(initialArray);	
	
		for (int i = 0; i < initialArray.size(); i ++) {
			displayStack(initialArray[i]);
		}

		f.close();

		cout << endl << endl;

	}

	return 0;
	
}