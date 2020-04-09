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
	void push_front ( int data );
	void push_back  ( int data );
	void pop_front  ();
	void pop_back   ();

	void front ();
	void back  ();
	void size  ();
	void clear ();
	bool empty ();

	Dequeue ()
		: last  ( nullptr )
		, first ( nullptr ) {}
private:
	Node* last;
	Node* first;
};


int main () {
	string command;
	int arg;
	Dequeue deq;
	while (command != "exit") {
		cin >> command;
		if (command == "push_front") {
			cin >> arg;
			deq.push_front ( arg );
		} else if (command == "push_back") {
			cin >> arg;
			deq.push_back ( arg );
		}

		else if (command == "pop_front") deq.pop_front ();
		else if (command == "pop_back")  deq.pop_back  ();
		else if (command == "front") deq.front ();
		else if (command == "back")	 deq.back  ();
		else if (command == "size")  deq.size  ();
		else if (command == "clear") deq.clear ();
	}
	cout << "bye";
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
	}
	cout << "ok" << endl;
}

void Dequeue::push_front ( int data ) {
	if (!empty ()) {
		Node* old = first;
		first = new Node ( data, nullptr, first );
		old->prev_node = first;
	} else {
		last = new Node ( data, nullptr, nullptr );
		first = last;
	}
	cout << "ok" << endl;
}

void Dequeue::pop_back () {
	if (!empty ()) {
		cout << last->data << endl;

		if (first != last) {
			Node* tmp = last;
			last = last->prev_node;
			last->next_node = nullptr;
			delete tmp;
		} else {
			delete last;
			first = nullptr;
			last = nullptr;
		}
	} else 
		cout << "error" << endl;
}

void Dequeue::pop_front () {
	if (!empty ()) {
		cout << first->data << endl;

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
	} else
		cout << "error" << endl;
}

void Dequeue::front () {
	if (!empty ())
		cout << first->data << endl;
	else
		cout << "error" << endl;
}

void Dequeue::back () {
	if (!empty ())
		cout << last->data << endl;
	else
		cout << "error" << endl;
}

void Dequeue::size () {
	int counter ( 0 );
	Node* now = last;
	while (now != nullptr) {
		counter++;
		now = now->prev_node;
	}
	cout << counter << endl;
}

void Dequeue::clear () {
	Node* del;
	while (last != nullptr) {
		del = last;
		last = last->prev_node;
		delete del;
	}

	first = nullptr;

	cout << "ok" << endl;
}