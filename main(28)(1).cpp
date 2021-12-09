#include <iostream>
#include <algorithm>
#include <cstring>
#include <ctime>
#include <fstream>
#include <string>
#include <queue>
#include <vector>
#include <unordered_map>
using namespace std;
const int N = 100100, M = N * 50;
int h[N], e[M], ne[M], idx;
double w[M];
bool st[N];
void add(int a, int b, double c) {
	e[idx] = b, ne[idx] = h[a], w[idx] = c, h[a] = idx++;
}
double dist[N];
void read_data() {
	ifstream in("data.txt");
	string line;
	while (getline(in, line)) {
		int s1 = line.find(' ');
		int s2 = line.find(' ', s1+ 1);
		int x = stoi(line.substr(0, s1));
		int y = stoi(line.substr(s1 + 1, s2 - s1 - 1));
		double d = stof(line.substr(s2 + 1));
		x--, y--;
		add(x, y, d), add(y, x, d);
	}
}
double prim(int start, int end) {
	memset(st, 0, sizeof st);
	for (int i = 0; i < N; i++) {
		dist[i] = 1e18;
	}
	dist[start] = 0;
	priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>>heap;
	heap.push({ 0, start });
	double sum = 0;
	double ans = 1e18;
	while (!heap.empty())
	{
		auto t = heap.top();
		heap.pop();
		int ver = t.second;
		double dst = t.first;
		if (st[ver]) continue;
		st[ver] = true, sum += dst;
		if (ver == end) {
			ans = min(ans, sum);
			break;
		}
		for (int i = h[ver]; i != -1; i = ne[i])
		{
			int j = e[i];
			if (!st[j]) {
				heap.push({ w[i], j });
			}
		}
	}
	return sum;
}
double dijkstra(int start, int end) {
	memset(st, 0, sizeof st);
	for (int i = 0; i < N; i++) {
		dist[i] = 1e18;
	}
	dist[start] = 0;
	priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>>heap;
	heap.push({ 0, start });
	while (heap.size()) {
		auto& t = heap.top();
		heap.pop();
		int x = t.second;
		double d = t.first;
		if (st[x])  continue;
		st[x] = true;
		for (int i = h[x]; ~i; i = ne[i]) {
			int j = e[i];
			if (dist[j] > dist[x] + w[i]) {
				dist[j] = dist[x] + w[i];
				heap.push({ dist[j], j });
			}
		}
	}
	return dist[end];
}
int main() {
	cout << "COP3530_Project3" << endl;
	memset(h, -1, sizeof h);
	read_data();
	string q = "yes";
	while (q == "yes") {
		cout << "Enter the first point:";
		int p1;
		cin >> p1;
		cout << "Enter the second point:";
		int p2;
		cin >> p2;
		p1--, p2--;
		double pr = prim(p1, p2), di = dijkstra(p1, p2);
		cout << "The shortest distance between the two points with Prim's algorithm:" << pr << endl;
		cout << "The shortest distance between the two points with Dijkstra's algorithm:" << di << endl;
		if (fabs(pr - di) < 1e-5) {
			cout << "They are same" << endl;
		}
		else {
			cout << "They are different.";
			if (pr < di)
				cout << "The distance with Prim's algorithm is shorter";
			else
				cout << "The distance with Dijkstra's algorithm is shorter";
			cout << endl;
		}
		cout << "Do you want to test the next point:";
		cin >> q;
	}
	cout << "Thanks for using it.Goodbye!" << endl;
	return 0;
}