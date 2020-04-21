#include <iostream>

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
	int pop ();
	int back ();
	bool empty ();
	bool search ( int n );

	Stack ()
		: last ( nullptr ) {}
private:
	Node* last;
};


int main () {
	int n, k, tmp; cin >> n;
	auto stacks = new Stack[n];
	for (int i = 0; i < n; i++) {
		cin >> k;
		bool flag = false;
		while (k-- > 0) {
			cin >> tmp;
			if (tmp - 1 != i || flag) {
				stacks[i].push ( tmp );
				flag = true;
			}
		}
	}

	if (n == 1) {
		if (stacks[0].empty ()) return 0;
		else {
			cout << 0 << endl;
			return 0;
		}
	} else if (n == 2) {

		if ((!stacks[0].empty () && !stacks[1].empty ()) || stacks[0].search(1)|| stacks[1].search(2)) {
			cout << 0;
			return 0;
		} 
	}

	for (int i = 1; i < n; i++) {
		while (!stacks[i].empty()) {
			tmp = stacks[i].pop ();
			if (stacks[tmp - 1].empty()) {
				cout << i + 1 << ' ' << tmp << endl;
			} else {
				cout << i + 1 << ' ' << 1 << endl;
				stacks[0].push ( tmp );
			}
		}
	}

	k = 0;
	while (!stacks[0].empty ()) {
		tmp = stacks[0].pop ();
		if (tmp == 1) {
			cout << 1 << ' ' << n << endl;
			stacks[n - 1].push ( tmp );
		} else if (tmp == n) {
			cout << 1 << ' ' << n << endl;
			if (!stacks[n - 1].empty ()) stacks[n - 1].push ( tmp );
		} else {
			cout << 1 << ' ' << tmp << endl;
		}
	}

	while (!stacks[n - 1].empty ()) {
		tmp = stacks[n - 1].pop();
		if (tmp == 1) cout << n << ' ' << 1 << endl;
		else {
			stacks[n - 2].push ( tmp );
			cout << n << ' ' << n - 1 << endl;
		}
	}

	while (!stacks[n - 2].empty ()) {
		stacks[n - 2].pop ();
		cout << n - 1 << ' ' << n << endl;
	}
}

bool Stack::empty () {
	return last == nullptr;
}

void Stack::push ( int n ) {
	if (!empty ()) {
		last = new Node ( n, last );
	} else {
		last = new Node ( n, nullptr );
	}
}

int Stack::pop () {
	if (!empty ()) {
		auto ret = last->data;

		Node* tmp = last;
		last = last->prev_node;
		delete tmp;
		return ret;
	} else cerr << "error";
}

int Stack::back () {
	if (!empty ()) {
		return last->data;
	} return 0;
}

bool Stack::search ( int val ) {
	Node* act = last;
	while (act != nullptr) {
		if (act->data == val) return true;
		act = act->prev_node;
	}
	return false;
}
