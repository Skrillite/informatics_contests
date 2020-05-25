#include <iostream>
#include <algorithm>
#include <vector>
#include <stdexcept>
#include <ctime>


struct Node {
	Node ()
		: subtree_size ( NULL )
		, data ( NULL )
		, priority ( NULL )
		, left ( nullptr )
		, right ( nullptr )
		, parent ( nullptr ) {};

	Node ( int _data, int _priority, Node* _parent = nullptr,
		Node* _left = nullptr, Node* _right = nullptr )
		: subtree_size ( 1 )
		, data ( _data )
		, priority ( _priority )
		, left ( _left )
		, right ( _right )
		, parent ( _parent ) {}

	friend struct Treap;

private:
	int data;
	int priority;
	int subtree_size;
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
		if (L == nullptr) {
			root = R;
			return;
		} else if (R == nullptr) {
			root = L;
			return;
		}

		else if (L->priority > R->priority) {
			root = L;
			merge ( L->right, R, root->right );
		} else {
			root = R;
			merge ( L, R->left, root->left );
		}

			root->subtree_size = ((root->left == nullptr) ? 0 : root->left->subtree_size)
				+ ((root->right == nullptr) ? 0 : root->right->subtree_size)
				+ 1;
	}
	

	void split (int idx, Node* &L, Node* &R) {
		split ( idx, L, R, this->root );
	}
	
	void split ( int idx, Node* &L, Node* &R, Node* root) {
		int sL = root->left != nullptr ? root->left->subtree_size + 1 : 1;
		if (sL <= idx) {
			L = root;
			if (root->right != nullptr)
				split ( idx - sL, root->right, R, root->right );
			else R = nullptr;

			root->subtree_size = (root->left == nullptr ? 0 : root->left->subtree_size)
				+ (root->right == nullptr ? 0 : root->right->subtree_size)
				+ 1;

		} else {
			R = root;
			if (root->left != nullptr)
				split ( idx, L, root->left, root->left );
			else L = nullptr;

			root->subtree_size = (root->left == nullptr ? 0 : root->left->subtree_size)
				+ (root->right == nullptr ? 0 : root->right->subtree_size)
				+ 1;
		}
	}

	void push_back ( int data ) {
		int priority = std::rand ();
		if (root == nullptr) root = new Node ( data, priority );
		else merge ( root, new Node ( data, priority ), root );
	}

	void InorderTraversal () const {
		if (root != nullptr) {
			InorderTraversal ( root->left );
			std::cout << root->data << ' ';
			InorderTraversal ( root->right );
		}
	}

	void InorderTraversal ( Node* root ) const {
		if (root != nullptr) {
			InorderTraversal ( root->left );
			std::cout << root->data << ' ';
			InorderTraversal ( root->right );
		}
	}

	void move ( int begin, int end ) {
		end -= begin - 1;
		Treap middle, right;
		split ( begin - 1, this->root, middle.root );
		middle.split ( end, middle.root, right.root, middle.root );
		merge ( this->root, right.root );
		merge ( middle.root, this->root );
	}

	int& operator[] ( int idx ) {
		auto curr = root;
		while (curr->left != nullptr && curr->left->subtree_size != idx)
			if (curr->left->subtree_size > idx) curr = curr->left;
			else {
				curr = curr->right;
				idx -= curr->subtree_size;
			}
		if (curr == nullptr)
			if (curr->left == nullptr) return curr->data;
			else throw std::out_of_range ( "no item with that index" );
	}

private:
	Node* root;
};



int main () {
	using namespace std;

	int n, m; cin >> n >> m;
	Treap tr;
	for (int i = 1; i <= n; i++)
		tr.push_back ( i );
	int begin, end;
	for (int i = 0; i < m; i++) {
		cin >> begin >> end;
		tr.move ( begin, end );
		cout << endl;
	}
    tr.InorderTraversal ();
}