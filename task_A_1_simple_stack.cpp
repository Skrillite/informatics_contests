#include <iostream>
#include <string>

using namespace std;

struct Node {
	int value;
	Node* prev_node;

	Node(int value, Node* prev_node)
		: value(value)
		, prev_node(prev_node) {}
};

struct Stack {
	void push(int n);
	void pop  ();
	void back ();
	void size ();
	void clear();
	bool empty();

	Stack()
		: last(nullptr) {}
private:
	Node* last;
};


int main() {
	string command;
	int arg;
	Stack stack;
	while (command != "exit") {
		cin >> command;
		if (command == "push") {
			cin >> arg;
			stack.push(arg);
		}
		else if (command == "pop"  )	stack.pop  ();
		else if (command == "back" )	stack.back ();
		else if (command == "size" )	stack.size ();
		else if (command == "clear")	stack.clear();
	}
	cout << "bye"; 
}

bool Stack::empty() {
	if (last == nullptr) return true;
	return false;
}

void Stack::push(int n) {
	if (!empty()) {
		last = new Node(n, last);
	} else {
		last = new Node(n, nullptr);
	}
	cout << "ok" << endl;
}

void Stack::pop() {
	if (!empty()) {
		cout << last->value << endl;
		if (last->prev_node != nullptr) {
			Node* tmp = last;
			last = last->prev_node;
			delete tmp;
		}
		else {
			last = nullptr;
		}
	} else cout << "error" << endl;
}

void Stack::back() {
	if (!empty()) {
		cout << last->value << endl;
	} else cout << "error" << endl;
}

void Stack::size() {
	int counter(0);
	Node* now = last;
	while (now != nullptr) {
		counter++;
		now = now->prev_node;
	}
	cout << counter << endl;
}

void Stack::clear() {
	Node* now = last;
	Node* del;
	while (now != nullptr) {
		del = now;
		now = now->prev_node;
		delete del;
	}

	last = nullptr;
	cout << "ok" << endl;
}