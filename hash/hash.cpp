#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <ctime>


struct Node {
	Node ()
		: data ( NULL )
		, priority ( NULL )
		, left ( nullptr )
		, right ( nullptr )
		, parent ( nullptr ) {};

	Node ( int _data, int _priority, Node* _parent = nullptr,
		Node* _left = nullptr, Node* _right = nullptr )
		: data ( _data )
		, max_val ( _data )
		, priority ( _priority )
		, left ( _left )
		, right ( _right )
		, parent ( _parent ) {}

	friend class Treap;

	int max ( Node* a, Node* b ) {
		if (a == nullptr && b == nullptr) return -1e9 - 1;
		else if (a == nullptr) return b->max_val;
		else if (b == nullptr) return a->max_val;
		else return std::max ( a->max_val, b->max_val );
	}

	void Recalc () {
		if (this != nullptr)
		this->max_val = (std::max ( max ( this->left, this->right )
			, this->data ));
	}

private:
	int data;
	int max_val;
	int priority;
	Node* parent;
	Node* left;
	Node* right;
};

using std::pair;
using std::vector;

struct Treap {

	Treap ()
		: root ( nullptr ) {
		std::srand ( unsigned ( std::time ( 0 ) ) );
	}
	Treap ( int x, int y )
		: root ( new Node ( x, y ) ) {
		std::srand ( unsigned ( std::time ( 0 ) ) );
	}


	void merge ( Node* L, Node* R ) {
		merge ( L, R, this->root );
	}

	void merge ( Node* L, Node* R, Node*& root ) {
		if (L == nullptr) root = R;
		else if (R == nullptr) root = L;

		else if (L->priority > R->priority) {
			root = L;
			merge ( L->right, R, root->right );
		} else {
			root = R;
			merge ( L, R->left, root->left );
		}

		root->Recalc ();
	}

	bool search ( int x ) {
		Node* curr = root;
		while (curr != nullptr) {
			if (curr->data > x) curr = curr->left;
			else if (curr->data < x) curr = curr->right;
			else return true;
		}
		return false;
	}

	//bool search ( int64_t x ) {
		//	Node* R; bool ret(false);

		//	split ( x, root, R );
		//	if (root->max == x) ret = true;
		//	merge ( root, R );
		//	return ret;
	//}

	void split ( int x, Node*& L, Node*& R ) {
		split ( x, L, R, this->root );
	}

	void split ( int x, Node*& L, Node*& R, Node* root ) {
		if (root == nullptr) {
			R = nullptr;
			L = nullptr;
			return;
		}
		if (root->data <= x) {
			L = root;
			split ( x, L->right, R, root->right );

			root->Recalc ();
		} else {
			R = root;
			split ( x, L, R->left, root->left );

			root->Recalc ();
		}
	}

	void erase ( int x ) {
		Node* R, * middle;
		split ( x, root, R );
		split ( x - 1, root, middle);
		merge ( root, R );
	}

	void add ( int x ) {
		Node* R = nullptr
			, * new_element = new Node ( x, std::rand () );

		if (root == nullptr) root = new_element;
		else {
			split ( x, root, R );
			if (root != nullptr && root->max_val == x) return;
			merge ( root, new_element );
			merge ( root, R );
		}
	}

private:
	Node* root;
};

int mul[] = { 2293, 1999, 3527, 3463, 3571, 1553, 2887, 2687, 3469, 3571 };

int hash ( std::string str ) {
	int64_t ret ( 0 );
	for (int i = 0; i < str.size (); i++)
		ret = str[i] + ret * mul[i];
	return ret % static_cast<int>(2e9);
}


int main () {
	char cmd ( 1 );
	std::string str;
	Treap tr;
	std::cin >> cmd;
	while (cmd != '#') {
		std::cin >> str;
		if (cmd == '+')
			tr.add ( hash (str) );
		else if (cmd == '-') {
			tr.erase ( hash (str) );
		}
		else
			std::cout << (tr.search ( hash ( str ) ) ? "YES" : "NO") << std::endl;
		std::cin >> cmd;
	}
}