#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

typedef struct activity{

	int duration;
	int timeLimit;
	int initialIndex;

	friend istream& operator>> (istream& i, activity& a){
		i >> a.duration;
		i >> a.timeLimit;
		return i;
	}

	friend ostream& operator<< (ostream& o, activity& a){
		o << a.duration << " " << a.timeLimit;
		return o;
	}

} activity;

int cmp(const void *a, const void *b){

	activity *first = (activity*)a;
	activity *second = (activity*)b;
	if(first -> timeLimit == second -> timeLimit)
		return (second -> duration - first -> duration);
	return (first -> timeLimit - second -> timeLimit);
}

int planning(activity activities[], int n){

	qsort(activities, n, sizeof (activity), cmp);

	int finalDelay;
	int currentTime = 0;

	for (int i = 0; i < n; i ++){
		int delay = 0;
		if (currentTime + activities[i].duration - activities[i].timeLimit > 0){
			delay += currentTime + activities[i].duration;
			delay -= activities[i].timeLimit;
		}
			 
		if (delay > finalDelay) finalDelay = delay;
		
		currentTime += activities[i].duration;

		cout << "Activitatea " << activities[i].initialIndex;
		cout << ": Intervalul " << activities[i];
		cout << " cu intarzierea " << delay << endl;
	}

	cout << "Intarzierea totala: " << finalDelay;

}

int main(){

	int n;
	ifstream f;

	f.open("activitati.in");
	f >> n;
	activity activities[n];

	for (int i = 0; i < n; i ++){
		f >> activities[i];
		activities[i].initialIndex = i + 1;
	}

	planning(activities, n);
	return 0;
}