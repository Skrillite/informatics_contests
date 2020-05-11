#include <iostream>
#include <algorithm>
#include <vector>
#include <ctime>


struct Node {
	Node ()
		: data ( NULL )
		, priority ( NULL )
		, left ( nullptr )
		, right ( nullptr )
		, parent ( nullptr ) {};

	Node ( int _data, int _priority,  Node* _parent = nullptr,
		Node* _left = nullptr, Node* _right = nullptr )
		: data ( _data )
		, priority ( _priority )
		, left ( _left )
		, right ( _right )
		, parent ( _parent ) {}

	friend class Treap;

	int data;
	int priority;
	Node* parent;
	Node* left;
	Node* right;
};

using std::pair;
using std::vector;

struct Treap {

	Treap ()
		: root ( nullptr ) {}
	Treap ( int x, int y )
		: root ( new Node ( x, y ) ) {}
	Treap ( vector <pair<int, int>> x )
		: root ( new Node () ) {
		std::srand ( unsigned ( std::time ( 0 ) ) );

		sort ( x.begin (), x.end () );
		root->data = x[0].first;
		root->priority = x[0].second;


		Node* last_node = root;
		for (int i = 1, size = x.size (); i < size; i++) {
			auto curr = last_node;
			while (curr->parent != nullptr) {
				if (curr->priority < x[i].second) {
					curr->right = new Node ( x[i].first, x[i].second, curr, curr->right );
					if (curr->right->left != nullptr)
						curr->right->left->parent = curr->right;
					last_node = curr->right;
					break;
				} else {
					curr = curr->parent;
				}
			}
			if (curr->parent == nullptr) {
				if (curr->priority < x[i].second) {
					curr->right = new Node ( x[i].first, x[i].second, curr, curr->right );
					if (curr->right->left != nullptr)
						curr->right->left->parent = curr->right;
					last_node = curr->right;
				} else {
					root = new Node ( x[i].first, x[i].second, nullptr, root );
					root->left->parent = root;
					last_node = root;
				}
			}
		}
	}

	void merge ( Node* L, Node* R ) {
		merge ( L, R, this->root );
	}

	void merge ( Node* L, Node* R, Node* &root ) {
		if (L == nullptr) root = R;
		else if (R == nullptr) root = L;

		else if (L->priority > R->priority) {
			root = L;
			merge ( L->right, R, root->right );
		} else {
			root = R;
			merge ( L, R->left, root->left );
		}
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

	void split (int x, Node* &L, Node* &R) {
		split ( x, L, R, this->root );
	}
	 
	void split ( int x, Node* &L, Node* &R, Node* root) {
		if (root == nullptr) {
			R = nullptr;
			L = nullptr;
			return;
		}
		if (root->data < x) {
			L = root;
			split ( x, L->right, R, root->right );
		} else {
			R = root;
			split ( x, L, R->left, root->left );
		}
	}

	int next ( int x ) {
 		auto curr = root;
		int min = root->data >= x ? root->data : static_cast<int>(1e9 + 1);
		while (curr != nullptr) {
			if (curr->data < min && curr->data >= x) min = curr->data;
			if (curr->data > x) curr = curr->left;
			else if (curr->data == x) {
				min = x;
				break;
			} else curr = curr->right;
		}
		return min == 1e9 + 1 ? -1 : min;
	}

	void add ( int x ) {
		if (search ( x )) return;
		int y = std::rand ();
		if (root == nullptr) root = new Node ( x, y );
		else add ( x, y );
	}

	Node* add ( int x, int y ) {
		Node  *L = nullptr
			, *R = nullptr
			, *el = new Node ( x, y );

		split ( x, L, R );
		merge ( L, el, L );
		merge ( L, R );
		return el;
	}

private:
	Node* root;
};


int main () {
	using namespace std;

	int n, el, lastr; cin >> n;
	char cm; bool flag = false;
	Treap tr;
	for (int i = 0; i < n; i++) {
		cin >> cm;
		switch (cm) {
			case '?':
			{
				cin >> el;
				lastr = tr.next (el);
				cout << lastr << endl;
				flag = true;
				break;
			}
			case '+':
			{
				cin >> el;
				if (flag) tr.add ( (el + lastr) % static_cast<int>(1e9) );
				else tr.add ( el );
				flag = false;
				break;
			}
		}
	}
}