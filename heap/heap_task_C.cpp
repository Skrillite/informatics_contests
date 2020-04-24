#include <iostream>

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
			swap ( arr[i], arr[parent] );

			i = parent;
			parent = (i - 1) / 2;
		}

		return i;
	}

	int swift_down ( int i ) {
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
		return swift_down (0);
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

	int max;
	while (--n > 0) {
		int max = hp[0];
		cout << hp.pop () + 1 << ' ' << max << endl;
	}
}