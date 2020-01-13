#include<iostream>
#include<vector>
#include<algorithm>
#include<vector>
#include<math.h>
#include<time.h>
#include<string>
using namespace std;

void showVector(vector<int> v) {
	for (int i = 0; i < v.size(); i++) {
		cout << v[i] << " ";
	}
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


vector<string> map{
	"################...#",
	"#.........##...#.#.#",
	"....#.....##.#.#.#.#",
	".##...###.##.#.#.#.#",
	".#.#.#..#.##.#.#.#.#",
	".#.#S#..#.##.#.#.#.#",
	"...###..#....#.#.#.#",
	"#.......######.#.#.#",
	"##.........#.#...#.#",
	"###..........#####.#",
	"###................#",
	"####.##.##....##...#",
	"####.#...#.....#####",
	"###..#.###...#.#....",
	"###..#.#T#.#####....",
	"##...#...#.........."
};
/*
vector<string> map{
    "S#..T",
    ".#.##",
    ".....",
    ".##.#",
    ".#..."
};
*/
//vector<string> map;

vector<vector<int>> graph(400);

vector<int> optimalway;
bool foundway = false;
int optimallength = int(pow(10, 5));



void buildGraph(int coord, vector<int> way) {
    way.push_back(coord);
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
	for(int i = 0; i < 4; i++){
        auto found = find(way.begin(), way.end(), endings[i]);
        //Если не нашли
        if (found == way.end()){
            auto found = find(graph[coord].begin(), graph[coord].end(), endings[i]);
            if (found == graph[coord].end()){
                graph[coord].push_back(endings[i]);
                buildGraph(endings[i], way);
            }
        }
	}


}

vector<int> color(400);
//color 0 means empty
//color 1 means green
//color 2 means black

vector<int> lengths(400);

vector<int> q;

void bfs(int vertex){
    int length = 0;
    q.push_back(vertex);
    color[vertex] = 1;
    lengths[vertex] = 0;
    while (q.size() != 0){
        vertex = q[0];

        for(int i = 0; i < graph[vertex].size(); i++){
            if(color[graph[vertex][i]] == 0){
                //cout << "Vertex " << graph[vertex][i] << " is empty!" << endl;
                q.push_back(graph[vertex][i]);
                color[graph[vertex][i]] = 1;
                lengths[graph[vertex][i]] = lengths[q[0]] + 1;
            }

        }
        length++;
        color[vertex] = 2;
        q.erase(q.begin());
        //cout << "Очередь: ";
        //showVector(q);
        //cout << endl;
    }

}


int main() {
	//setlocale(LC_ALL, "Russian");
/*
	int x, y;
	cin >> x >> y;
	for (int i = 0; i < x; i++) {
		string str;
		cin >> str;
		map.push_back(str);
	}*/
    for (int i = 0; i < color.size(); i++) color[i] = 0;
	//for (int i = 0; i < map.size(); i++) cout << map[i] << endl;

	int emptycounter = 0;
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			if (map[i][j] == '.') emptycounter++;
		}
	}
	//cout << "Empty cells: " << emptycounter << endl;


	vector<int> way;

	int starti, startj;
    int stopi, stopj;
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
	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[0].size(); j++) {
			if (map[i][j] == 'T') {
				stopi = i;
				stopj = j;
				i = map.size();
				break;
			}
		}
	}

	int startcoord = starti * map[0].size() + startj;
    int stopcoord = stopi * map[0].size() + stopj;
	buildGraph(startcoord, way);

	//cout << "Graph was built!\n";
	//cout << "Printing the graph:\n";
    /*
	for(int i = 0; i < graph.size(); i++){
        if(graph[i].size() > 0){
            cout << i << ": ";
            showVector(graph[i]);
            cout << "\n";
        }

	}*/
    bfs(startcoord);

    if (lengths[stopcoord] > 0)cout << lengths[stopcoord] << endl;
    else cout << -1;
	//cout << "Minimal length way: " << optimallength << endl;

	//cout << "Optimal way: ";
	//showVector(optimalway);
	return 0;
}
