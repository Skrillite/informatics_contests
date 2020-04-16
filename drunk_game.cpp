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
	int pop ();
	int front ();
	bool empty ();

	Queue ()
		: first ( nullptr )
		, last ( nullptr ) {}
private:
	Node* first;
	Node* last;
};

int main () {
	string str_player;
	Queue player1;
	Queue player2;

	int tmp;
	for (int i = 0; i < 5; i++) {
		cin >> tmp;
		player1.push ( tmp );
	}
	for (int i = 0; i < 5; i++) {
		cin >> tmp;
		player2.push ( tmp );
	}

	for (int i = 0; i < 1e6; i++) {
		if (player1.empty ()) {
			cout << "second" << ' ' << i;
			return 0;
		}
		if (player2.empty ()) {
			cout << "first" << ' ' << i;
			return 0;
		}
		if (player1.front () == 0 && player2.front () == 9 ||
			(player1.front () > player2.front () &&
				(player1.front () != 9 || player2.front () != 0))) {

			player1.push ( player1.pop () );
			player1.push ( player2.pop () );
		} else {
			player2.push ( player1.pop () );
			player2.push ( player2.pop () );
		}
	}
	cout << "botva";
}

void Queue::push ( int data ) {
	if (!empty ()) {
		first->next_node = new Node ( data, nullptr );
		first = first->next_node;
	} else {
		first = new Node ( data, nullptr );
		last = first;
	}
}

int Queue::pop () {
	auto ret = last->data;

	Node* tmp = last;
	last = last->next_node;
	delete tmp;
	return ret;
}

int Queue::front () {
	return last->data;
}


bool Queue::empty () {
	if (last == nullptr)
		return true;
	return false;
}