#include <iostream>
#include <string>

using namespace std;

struct Node {
	int data;
	Node* prev_node;

	Node ( int& _data, Node* _prev_node )
		: data ( _data )
		, prev_node ( _prev_node ) {}
};

struct Stack {
	void push ( int n );
	bool empty ();
	int pop    ();
	int back   ();

	Stack ()
		: last ( nullptr ) {}
private:
	Node* last;
};


int main () {
	Stack stack;
	char new_val;
	int a, b;
	while (cin >> new_val) {
		if (new_val >= '0' && new_val <= '9') {
			stack.push ( new_val - '0' );
		} else {
			b = stack.pop ();
			a = stack.pop ();

			switch (new_val) {
				case '+': 
				{
					stack.push ( a + b );
					break;
				}
				case '-':
				{
					stack.push ( a - b );
					break;
				}
				case '*':
				{
					stack.push ( a * b );
					break;
				}
			}
		}
	}
	cout << stack.back ();
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
}

int Stack::pop () {
	int ret = last->data;

	Node* tmp = last;
	last = last->prev_node;
	delete tmp;
	return ret;
}

int Stack::back () {
	return last->data;
}
