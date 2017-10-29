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
			return 1;							// 1 dacă poate fi adăugat
		return 0;							// 0 dacă trebuie ignorat și mers mai departe cu căutarea
	}
	return 2;							//2 dacă trebuie oprită căutarea și trebuie analizat subsetul deja creat
}

int qsortUtility(const void *a, const void *b){				// funcția de sortare folosită de qsort

	interval *first = (interval*)a;
	interval *second = (interval*)b;

	return (first -> left - second -> left);
}

int covering(interval intervals[], int n, interval toCover){

	interval covered;
	covered.left = covered.right = toCover.left;					// interval care stochează acoperirea deja făcută

	qsort(intervals, n, sizeof(interval), qsortUtility);
	
	int i = 0;
	int maxEffectiveLength = 0;
	int indexOfMaxLength = -1;
	int intervalsNumber = 0;

	while(covered.right < toCover.right && i < n){						// parcurg întreg vectorul de intervale 
		while(compatibility(intervals[i], covered) == 1 && i < n){			// cât timp dau doar de intervale compatibile
			if(intervals[i].right -	covered.right > maxEffectiveLength){
				maxEffectiveLength = intervals[i].right - covered.right;
				indexOfMaxLength = i;
			}
			i ++;
		}

		if(compatibility(intervals[i], covered) == 0) i ++;			// dacă am dat de un interval compatibil, dar deja 
																	// cuprins în acoperirea făcută, îl sar

		else if(indexOfMaxLength == -1) return -1;					// în această ramură se ajunge doar dacă, dupa 
																	// adăugarea unui nou interval, nu mai pot găsi
																	// intervale compatibile și nu am terminat acoperirea

		else {

			covered.right = intervals[indexOfMaxLength].right;		// adaug intervalul de lungime utilă maximală la soluție
			maxEffectiveLength = 0;
			intervalsNumber ++;
			indexOfMaxLength = -1;
		}
	}

	if(covered.right < toCover.right) return -1;	// dacă am ieșit din while fără a fi acoperit tot intervalul, semnalez
													// imposibilitatea acoperirii

	if(intervalsNumber == 0) return -1;				// dacă primul interval din sortare este incompatibil, atunci nu există
													// soluție
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