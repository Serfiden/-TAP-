#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <algorithm>
#include <math.h>
#include <cmath>

using namespace std;

struct point{
	double x;
	double y;
};

double pseudoDistance(point first, point second) {
	double paramA = pow((first.x - second.x), 2);
	double paramB = pow((first.y - second.y), 2);
	return sqrt(paramA + paramB);
}

bool sortingUtilityAbscissa(point first, point second) {
	return (first.x <= second.x);
}

bool sortingUtilityOrdinate(point first, point second) {
	return (first.y <= second.y);
}

double mergeDistances(std::vector<point> &pointsArray, int leftBound, int rightBound, double &partialMinimum) {
	std::vector<point> sortedArray;
	std::vector<point> potentialPoints;

	int median = (leftBound + rightBound) / 2;
	point middlePoint = pointsArray[median];

	int leftSubsetIndex = leftBound;
	int rightSubsetIndex = median + 1;
	while (leftSubsetIndex <= median && rightSubsetIndex <= rightBound) {
		
		if (pointsArray[leftSubsetIndex].y < pointsArray[rightSubsetIndex].y) {
			
			if (abs(middlePoint.x - pointsArray[leftSubsetIndex].x))
				potentialPoints.push_back(pointsArray[leftSubsetIndex]);

			sortedArray.push_back(pointsArray[leftSubsetIndex]);
			leftSubsetIndex ++;

		} else {
			
			if (abs(middlePoint.x - pointsArray[rightSubsetIndex].x))
				potentialPoints.push_back(pointsArray[rightSubsetIndex]);

			sortedArray.push_back(pointsArray[rightSubsetIndex]);
			rightSubsetIndex ++;
		}
	}

	if (leftSubsetIndex <= median) {
		while (leftSubsetIndex <= median) {
			if (abs(middlePoint.x - pointsArray[leftSubsetIndex].x))
				potentialPoints.push_back(pointsArray[leftSubsetIndex]);

			sortedArray.push_back(pointsArray[leftSubsetIndex]);
			leftSubsetIndex ++;
		}
	} else if (rightSubsetIndex <= rightBound) {
		if (abs(middlePoint.x - pointsArray[rightSubsetIndex].x))
				potentialPoints.push_back(pointsArray[rightSubsetIndex]);

			sortedArray.push_back(pointsArray[rightSubsetIndex]);
			rightSubsetIndex ++;
	}

	for (int i = leftBound; i <= rightBound; i ++) pointsArray[i] = sortedArray[i - leftBound];

	for (int i = 0; i < potentialPoints.size() - 1; i ++) 
		for (int j = i + 1; j < potentialPoints.size() && j < 8 - i; j ++) {
			double potentialMinimalDistance = pseudoDistance(potentialPoints[i], potentialPoints[j]);
			if (potentialMinimalDistance && potentialMinimalDistance < partialMinimum) 
				partialMinimum = potentialMinimalDistance;
		}

}

double minimalDistance(std::vector<point> &pointsArray, int leftBound, int rightBound) {
	if (rightBound - leftBound == 1) {
		return pseudoDistance(pointsArray[leftBound], pointsArray[rightBound]);
	
	} else if (rightBound - leftBound == 2) {
		std::vector<double> discreteAux(3);
		discreteAux[0] = pseudoDistance(pointsArray[leftBound], pointsArray[leftBound + 1]);
		discreteAux[1] = pseudoDistance(pointsArray[leftBound + 1], pointsArray[rightBound]);
		discreteAux[2] = pseudoDistance(pointsArray[rightBound], pointsArray[leftBound]);

		std::sort(discreteAux.begin(), discreteAux.end());
		return discreteAux[2];
	
	} else {
		int median = (leftBound + rightBound) / 2;
		
		double partialMinimalDistance = min(minimalDistance(pointsArray, leftBound, median),
									minimalDistance(pointsArray, median + 1, rightBound)); 
		
		mergeDistances(pointsArray, leftBound, rightBound, partialMinimalDistance);

		return partialMinimalDistance;
	}
}

int main() {
	std::vector<point> pointsArray;
	int pointsNumber;
	ifstream f;
	ofstream o;

	f.open("puncte.in");
	o.open("cmap.out");

	f >> pointsNumber;
	for (int i = 0; i < pointsNumber; i ++) {
		point newPoint;
		f >> newPoint.x;
		f >> newPoint.y;
		pointsArray.push_back(newPoint);
	}

	cout.setf(std::ios::fixed, std::ios::floatfield);
	cout.precision(6);

	sort(pointsArray.begin(), pointsArray.end(), sortingUtilityAbscissa);
	
	cout << minimalDistance(pointsArray, 0, pointsArray.size() - 1);

	f.close();
	o.close();
	return 0;
}