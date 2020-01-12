#include<iostream>
#include<vector>
#include<algorithm>
#include<vector>
#include<math.h>
#include<time.h>
#include<Windows.h>
#include<string>
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

/*
vector<string> map{
	"################...#",
	"#.........##...#.#.#",
	"....#.....##.#.#.#.#",
	".##...###.##.#.#.#.#",
	".#.#.#..#.##.#.#.#.#",
	".#.#S#..#.##.#.#.#.#",
	"...###..#T...#.#.#.#",
	"#.......######.#.#.#",
	"##.........#.#...#.#",
	"###..........#####.#",
	"###................#",
	"####.##.##....##...#",
	"####.#...#.....#####",
	"###..#.###...#.#....",
	"###..#.#.#.#####....",
	"##...#...#.........."
};*/

vector<string> map;

vector<int> optimalway;
int optimallength = int(pow(10, 5));

void buildGraph(int coord, vector<int> way) {
	way.push_back(coord);

	//cout << "Current coord: " << coord;
	//cout << "\tWay: ";
	//showVector(way);


	vector<int> possible(4);
	/*
	0 - top
	1 - bot
	2 - left
	3 - right
	*/
	int currenti, currentj;
	currenti = coord / map[0].size();
	currentj = coord % map[0].size();

	if (map[currenti][currentj] == 'T') {
		if (way.size() < optimallength) {
			optimalway = way;
			optimallength = way.size();
		}
		return;
	}
	//Searching top
	for (int i = currenti - 1; i >= 0; i--) {
		if (map[i][currentj] != '#') {
			possible[0]++;
		}
		else break;
	}

	//Searching bot
	for (int i = currenti + 1; i < map.size(); i++) {
		if (map[i][currentj] != '#') {
			possible[1]++;
		}
		else break;
	}

	//Searching left
	for (int i = currentj - 1; i >= 0; i--) {
		if (map[currenti][i] != '#') {
			possible[2]++;
		}
		else break;
	}
	
	//Searching right
	for (int i = currentj + 1; i < map[0].size(); i++) {
		if (map[currenti][i] != '#') {
			possible[3]++;
		}
		else break;
	}

	vector<int> endings(4);
	int finishi, finishj;
	
	//Top:
	finishi = currenti - ceil(double(possible[0]) / 2.0);
	finishj = currentj;
	endings[0] = finishi * map[0].size() + finishj;

	//Bot:
	finishi = currenti + ceil(double(possible[1]) / 2.0);
	finishj = currentj;
	endings[1] = finishi * map[0].size() + finishj;

	//Left:
	finishi = currenti;
	finishj = currentj - ceil(double(possible[2]) / 2.0);
	endings[2] = finishi * map[0].size() + finishj;
	
	//Right:
	finishi = currenti;
	finishj = currentj + ceil(double(possible[3]) / 2.0);
	endings[3] = finishi * map[0].size() + finishj;
	
	//cout << "\t\tEndings: ";
	//showVector(endings);
	//cout << endl;

	for (int i = 0; i < 4; i++) {
		auto found = find(way.begin(), way.end(), endings[i]);
		if (found == way.end()) {	//если не нашли
			buildGraph(endings[i], way);
		}
	}

}



int main() {
	//setlocale(LC_ALL, "Russian");

	int x, y;
	cin >> x >> y;
	for (int i = 0; i < x; i++) {
		string str;
		cin >> str;
		map.push_back(str);
	}

	//for (int i = 0; i < map.size(); i++) cout << map[i] << endl;

	int emptycounter = 0;
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			if (map[i][j] == '.') emptycounter++;
		}
	}
	//cout << "Empty cells: " << emptycounter << endl;

	vector<vector<int>> v(map.size() * map[0].size());
	vector<int> way;

	int starti, startj;

	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[0].size(); j++) {
			if (map[i][j] == 'S') {
				starti = i;
				startj = j;
				i = map.size();
				break;
			}
		}
	}

	int startcoord = starti * map[0].size() + startj;

	buildGraph(startcoord, way);

	int minlenway = int(pow(10, 5));
	

	//cout << "Minimal length way: " << optimallength << endl;
	cout << optimallength - 1;
	//cout << "Optimal way: ";
	//showVector(optimalway);
	return 228;
}