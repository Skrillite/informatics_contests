#include <iostream>
#include <algorithm>
#include <tuple>
#include <vector>


struct Node {
	Node () {};
	Node ( int _data, int _priority, int _num = NULL, Node* _parent = nullptr,
		Node* _left = nullptr, Node* _right = nullptr )
		: data ( _data )
		, num ( _num )
		, priority ( _priority )
		, left ( _left )
		, right ( _right )
		, parent ( _parent ) {}

	friend class Treap;

	int num;
	int data;
	int priority;
	Node* parent;
	Node* left;
	Node* right;
};

using std::get;
using std::tuple;
using std::vector;

struct Treap {

	Treap ( int x, int y )
		: root ( new Node ( x, y ) ) {}
	Treap ( vector<tuple<int, int, int>> x) 
		: root ( new Node () ) {
		vector<Node*> res(x.size(), 0);
		sort ( x.begin (), x.end (), []( tuple<int, int, int> lhs, tuple<int, int, int> rhs ) { 
			return (get<0> ( lhs ) < get<0> ( rhs )); });
		root->data = get<0> ( x[0] );
		root->priority = get<1> ( x[0] );
		root->num = get<2> ( x[0] );
		res[root->num] = root;

		Node* last_node = root;
		for (int i = 1, size = x.size(); i < size; i++) {
			auto curr = last_node;
			while (curr->parent != nullptr) {
				if (curr->priority < get<1>(x[i])) {
					curr->right = new Node ( get<0> ( x[i] ), get<1> ( x[i] ), get<2> ( x[i] ), curr, curr->right );
					if (curr->right->left != nullptr)
						curr->right->left->parent = curr->right;
					last_node = curr->right;
					break;
				} else {
					curr = curr->parent;
				}
			}
			if (curr->parent == nullptr) {
				if (curr->priority < get<1> ( x[i] )) {
					curr->right = new Node ( get<0> ( x[i] ), get<1> ( x[i] ), get<2> ( x[i] ), curr, curr->right );
					if (curr->right->left != nullptr)
						curr->right->left->parent = curr->right;
					last_node = curr->right;
				} else {
					root = new Node ( get<0> ( x[i] ), get<1> ( x[i] ), get<2> ( x[i] ), nullptr, root );
					root->left->parent = root;
					last_node = root;
				}
			}
			res[last_node->num] = last_node;
		}
		std::cout << "YES" << std::endl;
		for (auto curr : res)
			std::cout << ((curr->parent == nullptr) ? 0 : curr->parent->num + 1) << ' '
			<< ((curr->left == nullptr) ? 0 : curr->left->num + 1) << ' '
			<< ((curr->right == nullptr) ? 0 : curr->right->num + 1) << ' ' << std::endl;
	}

	void show ( int x ) const {
		Node* curr = root;

		while (curr->data != x) {
			if (curr->data > x) curr = curr->left;
			else curr = curr->right;
		}
		std::cout << ((curr->parent == nullptr) ? 0 : curr->parent->num + 1) << ' '
			<< ((curr->left == nullptr) ? 0 : curr->left->num + 1) << ' '
			<< ((curr->right == nullptr) ? 0 : curr->right->num + 1) << ' ' << std::endl;
	}

	void inorderTraversal () {
		inorderTraversal ( this->root );
	}

	void inorderTraversal (Node* curr) const {
		if (curr != nullptr) {
			inorderTraversal ( curr->left );
			std::cout << ((curr->parent == nullptr) ? 0 : curr->parent->num + 1) << ' '
				<< ((curr->left == nullptr) ? 0 : curr->left->num + 1) << ' '
				<< ((curr->right == nullptr) ? 0 : curr->right->num + 1) << ' ' << std::endl;
			inorderTraversal ( curr->right );
		}
	}

	void merge ( Node* L, Node* R ) {
		merge ( L, R, this->root );
	}

	void merge ( Node* L, Node* R, Node* root ) {
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

	void split (int x, Node* L, Node* R) {
		split ( x, L, R, this->root );
	}

	void split ( int x, Node* L, Node* R, Node* root) {
		if (root == nullptr) return;
		if (root->data < x) {
			L = root;
			split ( x, L->right, R, root->right );
		} else {
			R = root;
			split ( x, L, R->left, root->left );
		}
	}

	Node* add ( int x, int y ) {
		Node  *L = nullptr
			, *R = nullptr
			, *el = new Node ( x, y );

		split ( x, L, R );
		merge ( L, el );
		merge ( this->root, R );
		return el;
	}

private:
	Node* root;
};


int main () {
	using namespace std;

	int n; cin >> n;
	vector<tuple<int, int, int>> vec;
	vec.reserve ( n );
	int x, y;
	for (int i = 0; i < n; i++) {
		cin >> x >> y;
		vec.push_back ( make_tuple ( x, y, i ) );
	}
	Treap tr ( vec );
}