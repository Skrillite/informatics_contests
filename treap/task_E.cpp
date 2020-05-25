#include <iostream>
#include <algorithm>
#include <vector>
#include <stdexcept>
#include <ctime>


struct Node {
	Node ()
		: subtree_size ( NULL )
		, data ( NULL )
		, min_val (NULL)
		, priority ( NULL )
		, left ( nullptr )
		, right ( nullptr )
		, reversed (false) {};

	Node ( int _data, int _priority, Node* _parent = nullptr,
		Node* _left = nullptr, Node* _right = nullptr )
		: subtree_size ( 1 )
		, min_val ( _data )
		, data ( _data )
		, priority ( _priority )
		, left ( _left )
		, right ( _right )
		, reversed (false) {}

	friend struct Treap;

	int min ( Node* a, Node* b ) {
		if (a == nullptr && b == nullptr) return 1e9 + 1;
		else if (a == nullptr) return b->min_val;
		else if (b == nullptr) return a->min_val;
		else return std::min ( a->min_val, b->min_val );
	}

	void Recalc () {
		auto root = this;
		this->subtree_size = ((this->left == nullptr) ? 0 : this->left->subtree_size)
			+ ((this->right == nullptr) ? 0 : this->right->subtree_size)
			+ 1;

		this->min_val = (std::min ( min ( this->left, this->right )
			, this->data ));
	}

private:
	int data;
	int priority;
	int min_val;
	int subtree_size;
	bool reversed;
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

	void push ( Node* root ) {
		if (root == nullptr || !root->reversed) return;

		std::swap ( root->left, root->right );
		root->reversed = false;

		if (root->left != nullptr) root->left->reversed ^= true;
		if (root->right != nullptr) root->right->reversed ^= true;
	}

	void merge ( Node* L, Node* R ) {
		merge ( L, R, this->root );
	}

	void merge ( Node* L, Node* R, Node* &root ) {
		push ( L );
		push ( R );

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

		root->Recalc ();
	}
	

	void split (int idx, Node* &L, Node* &R) {
		split ( idx, L, R, this->root );
	}
	
	void split ( int idx, Node* &L, Node* &R, Node* root) {
		push ( root );

		int sL = root->left != nullptr ? root->left->subtree_size + 1 : 1;
		if (sL <= idx) {
			L = root;
			if (root->right != nullptr)
				split ( idx - sL, root->right, R, root->right );
			else R = nullptr;

			root->Recalc ();

		} else {
			R = root;
			if (root->left != nullptr)
				split ( idx, L, root->left, root->left );
			else L = nullptr;

			root->Recalc ();
		}
	}

	void push_back ( int data ) {
		int priority = std::rand ();
		if (root == nullptr) root = new Node ( data, priority );
		else merge ( root, new Node ( data, priority ), root );
	}

	void push_after ( int idx, int data ) {
		if (root != nullptr) {
			Node* tmp = new Node;
			split ( idx, this->root, tmp );
			merge ( this->root, new Node ( data, std::rand () ) );
			merge ( this->root, tmp );
		} else root = new Node ( data, std::rand () );
	}

	int minOf ( int idxA, int idxB ) {
		idxB -= idxA - 1;
		Node* middle ( new Node ), * right ( new Node );
		split ( idxA - 1, this->root, middle );
		split ( idxB, middle, right, middle );
		int ret = middle->min_val;
		merge ( this->root, middle );
		merge ( this->root, right );
		return ret;
	}

	void reverce (int idxA, int idxB) {
		idxB -= idxA - 1;
		Node* middle ( new Node ), * right ( new Node );
		split ( idxA - 1, this->root, middle );
		split ( idxB, middle, right, middle );
		middle->reversed ^= true;
		merge ( this->root, middle );
		merge ( this->root, right );
	}

	void InorderTraversal () {
		InorderTraversal ( root );
	}

	void InorderTraversal ( Node* root ) {
		push ( root );

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
	int a, b, tmp, cmd;
	Treap tr;
	while (n-- > 0) {
		cin >> tmp;
		tr.push_back ( tmp );
	}
//	tr.InorderTraversal (); cout << endl;
	while (m-- > 0) {
		cin >> cmd >> a >> b;
		switch (cmd) {
			case 1:
			{
				tr.reverce(a, b);
				//tr.InorderTraversal (); cout << endl;
				break;
			}
			case 2:
			{
				cout << tr.minOf ( a, b ) << endl;
				break;
			}
		}
	}
}