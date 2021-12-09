#include <iostream>
#include <algorithm>
#include <cstring>
#include <ctime>
#include <fstream>
#include <unordered_map>
using namespace std;
const int N = 100100, M = N * 10;
double rand(double l, double r) {
	return (double)rand() / RAND_MAX * (r - l) + l;
}

int main() {
	ofstream out("data.txt");
	unordered_map<long long, int> cnt;
	for (int i = 0; i < M; i++) {
		int x = rand() % N + 1;
		int y = rand() % N + 1;
		long long h = (long long)x * N + y;
		long long rh = (long long)y * N + x;
		while (cnt.count(h) || cnt.count(rh)) {
			x = rand() % N + 1;
			y = rand() % N + 1;
			h = (long long)x * N + y;
			rh = (long long)y * N + x;
		}
		cnt[h] = cnt[rh] = 1;
		double w = rand(N / 10, N);
		out << x << ' ' << y << ' ' << w << endl;
	}

}