#include <iostream>
#include <string>

using namespace std;

struct Node {
	string data;
	Node* next_node;

	Node ( string& _data, Node* _next_node )
		: next_node ( _next_node )
		, data ( _data ) {
		  data.reserve ( 50 );
	}
};

struct Queue {
	void push ( string n );
	void show ();
	bool empty ();

	Queue ( int cls )
		: first ( nullptr )
		, last ( nullptr )
		, class_number ( cls ) {}
private:
	Node* first;
	Node* last;
	int class_number;
};

int main () {
	Queue cl9 ( 9 ), cl10 ( 10 ), cl11 ( 11 );
	string str; int tmp;
	while (cin >> tmp >> str) {
		switch (tmp) {
			case 9:
			{
				cl9.push ( str );
				break;
			}
			case 10:
			{
				cl10.push ( str );
				break;
			}
			case 11:
			{
				cl11.push ( str );
				break;
			}
		}
	}

	cl9.show ();
	cl10.show ();
	cl11.show ();
}

void Queue::push ( string data ) {
	if (!empty ()) {
		first->next_node = new Node ( data, nullptr );
		first = first->next_node;
	} else {
		first = new Node ( data, nullptr );
		last = first;
	}
}

void Queue::show () {
	Node* next = last;
	while (next != nullptr) {
		cout << class_number << ' ' << next->data << endl;
		next = next->next_node;
	}
}


bool Queue::empty () {
	if (last == nullptr)
		return true;
	return false;
}