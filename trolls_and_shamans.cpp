#include <iostream>
#include <string>

using namespace std;

struct Node {
	int data;
	Node* next_node;

	Node ( int& _data, Node* _next_node )
		: next_node ( _next_node )
		, data ( _data ) {}
};

struct Queue {
	void push ( int n );
	void push_in_the_middle ( int n );
	int pop ();
	bool empty ();

	Node* middle;

	Queue ()
		: first ( nullptr )
		, last ( nullptr )
		, middle (nullptr)
		, size ( 0 ) {}
private:
	Node* first;
	Node* last;
	size_t size;
};

int main () {
	int n, tmp; cin >> n;
	Queue qu;
	for (int i = 0; i < n; i++) {
		char com; cin >> com;
		switch (com) {
			case '+':
			{
				cin >> tmp;
				qu.push ( tmp );
				break;
			}
			case '-':
			{
				cout << qu.pop () << endl;
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

void Queue::push ( int data ) {
	if (!empty ()) {
		first->next_node = new Node ( data, nullptr );
		first = first->next_node;

		size++;
		if (size & 1) middle = middle->next_node;
	} else {
		first = new Node ( data, nullptr );
		last = first;
		middle = first;
		size++;
	}

}

void Queue::push_in_the_middle ( int data ) {
	if (!empty ()) {
		if (size == 1) {
			last->next_node = new Node ( data, nullptr );
			first = last->next_node;
			size++;
		} else {
				middle->next_node = new Node ( data, middle->next_node );
				size++;
				if (size & 1) middle = middle->next_node;
		}
	} else {
		first = new Node ( data, nullptr );
		last = first;
		middle = first;
		size++;
	}

}

int Queue::pop () {
	if (!empty ()) {
		Node* tmp = last;
		last = last->next_node;
		int ret = tmp->data;
		size--;
		if (size & 1) middle = middle->next_node;
		delete tmp;
		return ret;
	} else cout << "error" << endl;
}

bool Queue::empty () {
	return last == nullptr;
}