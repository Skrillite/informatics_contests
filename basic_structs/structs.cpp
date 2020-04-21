#include <iostream>
#include <string>

using namespace std;

struct Node {
	int data;
	Node* prev_node;
	Node* next_node;

	Node ( int& _data, Node* _prev_node, Node* _next_node )
		: data ( _data )
		, prev_node ( _prev_node )
		, next_node ( _next_node ) {}
};

struct Dequeue {
	void push_in_the_middle ( int data );
	void push_back ( int data );
	int pop_front ();

	int front ();
	void back ();
	void clear ();
	bool empty ();

	Dequeue ()
		: last ( nullptr )
		, first ( nullptr )
		, middle_position ( nullptr )
		, size ( 0 ) {}

private:
	Node* last;
	Node* first;
	Node* middle_position;
	int size;
};


int main () {
	int n, tmp; cin >> n;
	Dequeue qu;
	for (int i = 0; i < n; i++) {
		char com; cin >> com;
		switch (com) {
			case '+':
			{
				cin >> tmp;
				qu.push_back ( tmp );
				break;
			}
			case '-':
			{
				cout << qu.pop_front () << endl;
				break;
			}
			case '*':
			{
				cin >> tmp;
				qu.push_in_the_middle ( tmp );
				break;
			}
		}
	}
}

bool Dequeue::empty () {
	if (last == nullptr && first == nullptr) return true;
	return false;
}

void Dequeue::push_back ( int data ) {
	if (!empty ()) {
		Node* old = last;
		last = new Node ( data, last, nullptr );
		old->next_node = last;
	} else {
		last = new Node ( data, nullptr, nullptr );
		first = last;
		middle_position = first;
	}
	size++; if (!(size & 1)) middle_position = middle_position->next_node;
	middle_position;
}

void Dequeue::push_in_the_middle ( int data ) {
	if (!empty ()) {
		if (size > 1) {
			middle_position->prev_node = new Node ( data, middle_position->prev_node, middle_position );
			middle_position->prev_node->prev_node->next_node = middle_position->prev_node;
		} else {
			Node* old = last;
			last = new Node ( data, last, nullptr );
			old->next_node = last;
		}
	} else {
		last = new Node ( data, nullptr, nullptr );
		first = last;
		middle_position = first;
	}
	size++; if (size & 1) middle_position = middle_position->prev_node;
	middle_position;
}



int Dequeue::pop_front () {
	int ret = first->data;

	if (first != last) {
		Node* tmp = first;
		first = first->next_node;
		first->prev_node = nullptr;
		delete tmp;
	} else {
		delete first;
		first = nullptr;
		last = nullptr;
	}
	size--; if ((size & 1) && size > 1) middle_position = middle_position->prev_node;
	return ret;
}

int Dequeue::front () {
	return last->data;
}
