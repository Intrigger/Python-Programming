#define _CRT_DISABLE_PERFCRIT_LOCKS
#include<iostream>
#include<vector>
#include<algorithm>
#include<vector>
#include<time.h>
#include<Windows.h>
using namespace std;

void showVector(vector<int> v) {
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
	}
}

int algo1(int l, int r, int a) {
	int len = r - l;
	if (len + 1 >= a) {
		int greatv = len + 1 - a;
		int smallv = len + 1 - (len - (len % a));
		int n = ((greatv- smallv) / a) + 1;
		int res = n * (smallv + greatv) / 2;
		return res;
	}
	else {
		return 0;
	}
}

int algo2(int l, int r, int a) {
	int x = r - l - a + 1;
	int x1 = x / a;
	int x2 = x % a;
	int s = ((1 + x1) / 2) * x1;
	int res = s * a;
	res += (x2) * ((r - l) / a);
	return res;
}

int gcd(int a, int b, int& x, int& y) {
	if (a == 0) {
		x = 0; y = 1;
		return b;
	}
	int x1, y1;
	int d = gcd(b % a, a, x1, y1);
	x = y1 - (b / a) * x1;
	y = x1;
	return d;
}

int algo(int a, int b) {
	int x = 0;
	while ((x * a) % b != 1) {
		x += 1;
	}
	return x;
}

struct interval {
	int left;
	int right;
	int length;
	int number;
};

bool sort_left(interval s1, interval s2) {
	return s1.left < s2.left;
}

int main() {
	srand(time(0));
	setlocale(LC_ALL, "Russian");
	
	int n;
	cin >> n;

	vector<vector<int>> v(n, vector<int>(n, 0));

	int op = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			v[i][j] = rand() % 10;
		}
	}

	for (int i = n - 1; i >= 0; i--) {
		int c = i;
		for (int j = n - 1; (j >= 0) and (c < n); j--) {
			if (c == n - 1) {
				if (j != n - 1) {
					v[c][j] += v[c][j + 1];
				}
				c += 1;
				continue;
			}
			if (j == n - 1) {
				if (c != n - 1) {
					v[c][j] += v[c + 1][j];
				}
				c += 1;
				continue;
			}
			v[c][j] += max(v[c + 1][j], v[c][j + 1]);
			c += 1;
			op++;
		}
	}

	for (int j = n - 2; (j >= 0); j--) {
		int c = j;
		for (int i = 0; (i < n) and (c >= 0); i++) {
			v[i][c] += max(v[i + 1][c], v[i][c + 1]);
			c -= 1;
			op++;
		}
	}

	cout << "Max way sum: " << v[0][0];
	cout << "\nOperations: " << op;
	return 0;
}