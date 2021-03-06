#include <iostream>
#include <cmath>

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

		for (int i = size / 2; i >= 0; i--)
			swift_down ( i );
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

		while (arr[i] > arr[(i - 1) / 2]) {
			swap ( arr[i], arr[(i - 1) / 2] );

			i = (i - 1) / 2;
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

	int erase ( int idx ) {
		if (idx < size && idx > -1) {
			int ret = arr[idx];
			arr[idx] = arr[size - 1]; size--;
			swift_down ( idx );
			swift_up ( idx );
			return ret;
		} else return -1e9 - 1;
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
		cout << endl;
	}

	void sort () {
		int tmp;
		while (size > 0) {
			tmp = get_max ();
			pop (); 
			show ();
			arr[size] = tmp;
		}

		for (int i = 0; i < arr_size; i++) {
			cout << arr[i] << ' ';
		}
	}

private:
	const int arr_size;
	int* arr;
	int size;
};

int main () {
	int n; cin >> n;
	Heap hp ( n, cin );
	hp.show ();
	hp.sort ();
}