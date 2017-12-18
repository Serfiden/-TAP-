#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int efficientPath(int** values, int n, int m) {
	int paths[n][m];

	paths[n - 1][m - 1] = values[n - 1][m - 1];

	for (int i = n - 2; i >= 0; i --) 
		paths[i][m - 1] = paths[i + 1][m - 1] + values[i][m - 1];

	for (int i = m - 2; i >= 0; i --)
		paths[n - 1][i] = paths[n - 1][i + 1] + values[n - 1][i];

	for (int i = n - 2; i >= 0; i --)
		for (int j = m - 2; j >= 0; j --) {
			int first = paths[i][j + 1];
			int second = paths[i + 1][j];
			paths[i][j] = values[i][j] + max(first, second);
		}

	int i = 0;
	int j = 0;

	while(i < n && j < m) {
			cout << i + 1 << " " << j + 1 << endl;
			if (i == n - 1) j ++;
			else if (j == m - 1) i ++;	
			if (paths[i][j + 1] > paths[i + 1][j]) j ++;
			else i ++;
		}

	cout << n << " " << m;

	return 0;
}

int main() {
	int n, m;
	ifstream f("piese.in");
	f >> n;
	f >> m;

	int **values = new int*[n];
	for (int i = 0; i < n; i ++)
		values[i] = new int[m];

	for (int i = 0; i < n; i ++)
		for (int j = 0; j < m; j ++)
			f >> values[i][j];

	efficientPath(values, n, m);

	return 0;
}