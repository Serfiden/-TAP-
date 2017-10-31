#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>
#include <functional>

using namespace std;

bool newCompare(int a, int b){
	return(b > a);
}

int customBinarySearch (vector < stack<int> > &set, int valueToPut, int limit){

	/*  În esență, ce caut este o poziție i, astfel încât set[i] > valueToPut &&
	valueToPut > set[i - 1] <=> cel mai mic vf. de stivă, mai mare decât valueToPut */

	int left = 0;
	int right = limit - 1;
	int mid;

	if (valueToPut > set[right].top()) return -1;			// verific dacă elementul verificat 
															// trebuie să fie vârf de stivă nouă

	else if (valueToPut <= set[left].top()) return 0;		// încep căutarea din stânga

	else while (left != right){	

		mid = (left + right) / 2;

		if (valueToPut == set[mid].top()) return mid;	

		else if (valueToPut < set[mid].top())					// verific dacă poziția curentă este bună
			if (valueToPut > set[mid - 1].top()) return mid;
			else right = mid;

		else if (valueToPut > set[mid].top())					 // idem mai sus
			if (valueToPut < set[mid + 1].top()) return mid + 1;
			else left = mid;

		if (valueToPut > set[right].top()) return -1;			// verific din nou capetele selecției

		else if (valueToPut <= set[left].top()) return left;
	}

	return -1;
}


int makeStacks (vector < stack<int> > &initial){

	vector< stack<int> >::iterator it = initial.begin();
	int numberIterator = 0;

	while (it + 1 != initial.end() && it != initial.end()){		// iterez o singură dată prin șirul inițial
		int modified = 0;

		int foundPlace = customBinarySearch(initial, (*(it + 1)).top(), numberIterator + 1); 

		// dacă pot insera elementul curent într-o stivă anterioară

		if (foundPlace >= 0){
			
			int toAdd = (*(it + 1)).top();
			(*(it + 1)).pop();
			initial.erase(it + 1);
			initial[foundPlace].push(toAdd);
			modified = 1;
		} 

		// dacă nu am făcut nicio inserție/ștergere, atunci avansez cu verificarea în vector; altfel, staționez

		if (it + 1 != initial.end() && !modified){
			it ++;
			numberIterator ++;
		} 
	}

	return 0;
}

int sorting(vector <stack <int> > &initial){

	std::priority_queue<int, std::vector<int>, std::greater<int> > myQueue;

	for (int i = 0 ; i < initial.size(); i ++){
		while (!initial[i].empty()){
			myQueue.push(initial[i].top());
			initial[i].pop();
		}
	}

	while (!myQueue.empty()){
		cout << myQueue.top() << " ";
		myQueue.pop();
	}

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

		makeStacks(initialArray);	
		sorting(initialArray);
	}

	
	
	return 0;
}