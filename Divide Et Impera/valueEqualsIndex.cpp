#include <iostream>
#include <fstream>

using namespace std;

int searchIndex(int left, int right, int v[]){
	if (left == right){
		return -1;
	}

	int middle = (left + right) / 2;
	if (v[middle] > middle){
		return searchIndex(left, middle, v);
	}

	else if (v[middle] < middle){
		return searchIndex(middle, right, v);
	}

	return middle;
}

int main(){
	ifstream f;
	f.open("date.in");
	int n;

	f >> n;
	int v[n];

	for (int i = 0; i < n; i ++){
		f >> v[i];
	}

	int result = searchIndex(0, n - 1, v);
	if (result) cout << result;
	else cout << "Could not find such an index!";
	return 0;
}