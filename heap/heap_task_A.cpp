#include <iostream>
#include <vector>

using namespace std;

struct Heap {
	Heap () = delete;
	Heap ( int _size )
		: arr ( new int[_size] )
		, size ( 0 ) {}

	Heap ( int _size, istream& stream )
		: arr ( new int[_size] )
		, size ( _size ) {

		int counter ( 0 );
		while (counter < size) 
			stream >> arr[counter++];
	}

	int& operator[] ( int idx ) {
		return arr[idx];
	}

	void add ( int data ) {
		arr[size] = data; size++;
		swift_up ( size - 1 );
	}

	int swift_up ( int i ) {

		int parent = (i - 1) / 2;

		while (arr[i] > arr[parent]) {
			int tmp = arr[i];
			arr[i] = arr[parent];
			arr[parent] = tmp;

			i = parent;
			parent = (i - 1) / 2;
		}

		return i;
	}

	void show () {
		int counter = 0;
		while (counter < size)
			cout << arr[counter++] << ' ';
	}

private:
	int* arr;
	int size;
};

int main () {
	int n, tmp; cin >> n;
	Heap hp ( n, cin );

	int m; cin >> m;
	int idx, val;
	while (m-- > 0) {
		cin >> idx >> val;

		hp[--idx] += val;
		cout << hp.swift_up ( idx ) + 1 << endl;
	}

	hp.show ();
}