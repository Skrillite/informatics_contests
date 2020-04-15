#include <iostream>
#include <string>

using namespace std;

struct Node {
	int data;
	Node* prev_node;

	Node ( int& _data, Node* _prev_node )
		: data      ( _data      )
		, prev_node ( _prev_node ) {}
};

struct Stack {
	void push ( int n );
	void pop   ();
	void back  ();
	void size  ();
	void clear ();
	bool empty ();

	Stack ()
		: last ( nullptr )
		, _size (0) {}
private:
	Node* last;
	size_t _size;
};


int main () {
	string command;
	int arg;
	Stack stack;
	while (command != "exit") {
		cin >> command;
		if (command == "push") {
			cin >> arg;
			stack.push ( arg );
		}
		else if (command == "pop")	stack.pop   ();
		else if (command == "back")	stack.back  ();
		else if (command == "size")	stack.size  ();
		else if (command == "clear")stack.clear ();
	}
	cout << "bye";
}

bool Stack::empty () {
	if (last == nullptr) return true;
	return false;
}

void Stack::push ( int n ) {
	if (!empty ()) {
		last = new Node ( n, last );
	} else {
		last = new Node ( n, nullptr );
	}
	_size++;
	cout << "ok" << endl;
}

void Stack::pop () {
	if (!empty ()) {
		cout << last->data << endl;

		Node* tmp = last;
		last = last->prev_node;
		delete tmp;
		_size--;
	} else
        cout << "error" << endl;
}

void Stack::back () {
	if (!empty ()) {
		cout << last->data << endl;
	} else
        cout << "error" << endl;
}

void Stack::size () {
	cout << _size << endl;
}

void Stack::clear () {
	Node* del;
	while (last != nullptr) {
		del = last;
		last = last->prev_node;
		delete del;
	}

	cout << "ok" << endl;
}