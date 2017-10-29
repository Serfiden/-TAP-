#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

typedef struct {

	int left;
	int right;

}	interval;

int compatibility(interval toTest, interval refference){

	if(toTest.left <= refference.right){
		if(toTest.right > refference.right)
			return 1;
		return 0;
	}
	return 2;
}

int qsortUtility(const void *a, const void *b){

	interval *first = (interval*)a;
	interval *second = (interval*)b;

	return (first -> left - second -> left);
}

int covering(interval intervals[], int n, interval toCover){

	interval covered;
	covered.left = covered.right = toCover.left;

	qsort(intervals, n, sizeof(interval), qsortUtility);
	
	int i = 0;
	int maxEffectiveLength = 0;
	int indexOfMaxLength = -1;
	int intervalsNumber = 0;

	while(covered.right < toCover.right && i < n){
		while(compatibility(intervals[i], covered) == 1 && i < n){
			if(intervals[i].right -	covered.right > maxEffectiveLength){
				maxEffectiveLength = intervals[i].right - covered.right;
				indexOfMaxLength = i;
			}
			i ++;
		}

		if(compatibility(intervals[i], covered) == 0) i ++;

		else if(indexOfMaxLength == -1) return -1;

		else {

			covered.right = intervals[indexOfMaxLength].right;
			maxEffectiveLength = 0;
			intervalsNumber ++;
			indexOfMaxLength = -1;
		}
	}

	if(covered.right < toCover.right) return -1;

	if(intervalsNumber == 0) return -1;
	return intervalsNumber;
}

int main(){

	int n;
	ifstream f;
	ofstream g;
	f.open("acoperire.in");
	g.open("acoperire.out");

	interval refference;
	f >> refference.left;
	f >> refference.right;

	f >> n;

	interval intervals[n];

	for(int i = 0; i < n; i ++){
		f >> intervals[i].left;
		f >> intervals[i].right;
	}

	int x = covering(intervals, n, refference);
	cout << x;
	g << x;

	return 0;
}