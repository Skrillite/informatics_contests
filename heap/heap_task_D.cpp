#include <iostream>

using namespace std;

struct Heap {
	Heap () = delete;
	Heap ( int _size )
		: arr ( new int[_size] )
		, arr_size ( _size )
		, size ( 0 ) {}

	Heap ( int _size, istream& stream )
		: arr ( new int[_size] )
		, arr_size ( _size )
		, size ( _size ) {

		int counter ( 0 );
		while (counter < size)
			stream >> arr[counter++];
	}

	int& operator[] ( int idx ) {
		return arr[idx];
	}

	int add ( int data ) {

		if (size < arr_size) {
			arr[size] = data; size++;
			return swift_up ( size - 1 );
		} else return -2;
	}

	int swift_up ( int i ) {

		int parent = (i - 1) / 2;

		while (arr[i] > arr[parent]) {
			swap ( arr[i], arr[parent] );

			i = parent;
			parent = (i - 1) / 2;
		}

		return i;
	}

	int swift_down ( int i ) {
		if (size < 1) return -1;
		int largestChild = i
			, leftChild
			, rightChild;

		while (true) {
			leftChild = 2 * i + 1;
			rightChild = 2 * i + 2;

			if (leftChild < size && arr[leftChild] > arr[largestChild])	largestChild = leftChild;
			if (rightChild < size && arr[rightChild] > arr[largestChild]) largestChild = rightChild;

			if (largestChild == i)	return i;

			swap ( arr[largestChild], arr[i] );
			i = largestChild;
		}
	}

	int pop () {
		arr[0] = arr[size - 1]; size--;
		return swift_down ( 0 );
	}

	int get_max () const {
		if (size > 0) return arr[0];
		else return -1e9 - 1;
	}

	void show () const {
		int counter = 0;
		while (counter < size)
			cout << arr[counter++] << ' ';
	}

private:
	const int arr_size;
	int* arr;
	int size;
};

int main () {
	int n, m, tmp; cin >> n >> m;
	Heap hp ( n );


	while (m-- > 0) {
		cin >> tmp;
		switch (tmp) {
			case 1:
			{
				int max = hp.get_max ();
				if (max != -1e9 -1) {
					cout << hp.pop () + 1 << ' ' << max << endl;
				} else
					cout << -1 << endl;
				break;
			}
			case 2:
			{
				cin >> tmp;
				cout << hp.add ( tmp ) + 1 << endl;
				break;
			}
		}
	}
	hp.show ();
}