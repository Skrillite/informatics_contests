#include <iostream>
#include <string>

using namespace std;

struct Node {
	int data;
	Node* next_node;

	Node(int& _data, Node* _next_node)
		: next_node (_next_node)
		, data		(_data) {}
};

struct Queue {
	void push (int n);
	void pop  ();
	void front();
	void clear();
	void	 size ();
	bool empty();

	Queue()
		: first	(nullptr)
		, last	(nullptr) {}
private:
	Node* first;
	Node* last;
};

int main() {
	string command;
	int arg;
	Queue queue;
	while (command != "exit") {
		cin >> command;
		if (command == "push") {
			cin >> arg;
			queue.push(arg);
		}
		else if (command == "pop")	queue.pop();
		else if (command == "front")queue.front();
		else if (command == "size")	queue.size();
		else if (command == "clear")queue.clear();
	}
	cout << "bye"; 
}

void Queue::push(int data) {
	if (!empty()) {
		first->next_node = new Node(data, nullptr);
		first = first->next_node;
	} else {
		first = new Node(data, nullptr);
		last = first;
	}
	cout << "ok" << endl;
}

void Queue::pop() {
	if (!empty()) {
		front();

		Node* tmp = last;
		last = last->next_node;
		delete tmp;
	}
	else cout << "error" << endl;
}

void Queue::front() {
	if (!empty())
		cout << last->data << endl;
	else 
		cout << "error" << endl;
}

void Queue::clear() {
	Node* del;
	while (last != nullptr) {
		del = last;
		last = last->next_node;
		delete del;
	}
	if (last != nullptr) cout << "fuck you" << endl;
	first = last;
	cout << "ok" << endl;
}

void Queue::size() {
	int counter(0);
	Node* next = last;
	while (next != nullptr) {
		counter++;
		next = next->next_node;
	}
	cout << counter << endl;
}

bool Queue::empty() {
	if (last == nullptr)
		return true;
	return false;
}