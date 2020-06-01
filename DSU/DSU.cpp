#include <iostream>
#include <set>
#include <tuple>
#include <ctime>


struct DSU {

	DSU ( size_t size )
		: p ( new int[size] )
		, v ( new int[size] ) {
		std::srand ( unsigned ( std::time ( 0 ) ) );
	};

	void makeSet ( int el ) {
		p[el] = el;
	}

	int find ( int el ) {
		if (p[el] != el) return p[el] = find ( p[el] );
		return el;
	}

	bool unite ( int x, int y, int weight = 0 ) {
		x = find ( x );
		y = find ( y );

		if (x == y) return false;
		if (std::rand () & 1) std::swap ( x, y );
		p[x] = y;
		v[y] = v[x] + v[y] + weight;
		return true;
	}

	int weight ( int x ) {
		return v[find ( x )];
	}

private:
	int* p;
	int* v;
};

int main () {
	using namespace std;

	int n, m;
	cin >> n >> m;

	DSU dsu ( n );
	set <tuple <int, int, int>> st;
	int x, y, w;
	for (int i = 0; i < m; i++) {
		cin >> x >> y >> w;
		x--;
		y--;
		st.emplace ( w, x, y );
	}

	int64_t k ( 0 );

	for (int i = 0; i < n - 1;) {
		tie ( w, x, y ) = *st.begin ();
		st.erase ( st.begin () );
		if (dsu.unite ( x, y )) {
			k += w;
			i++;
		}
	}


	//using namespace std;
	//int n, m, counter ( 0 ); cin >> n >> m;

	//DSU dsu ( n );
	//for (int i = 0; i < n; i++)
	//	dsu.makeSet ( i );
	//int a, b;
	//while (m-- > 0) {
	//	cin >> a >> b;
	//	if (dsu.unite ( a, b )) n--;
	//	counter++;
	//}
	//cout << counter;

}