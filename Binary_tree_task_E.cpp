#include <iostream>

using namespace std;

struct Node {
	Node* left_node;
	Node* right_node;
	int data;

	Node ( int _data, Node* left, Node* right )
		: left_node ( left )
		, right_node ( right )
		, data ( _data ) {}
};

struct BTree {
	void add ( int data );
	int size ();
	void inorderTraversal ();

	BTree ()
		: root ( new Node ( NULL, nullptr, nullptr ) )
		, _size ( 0 ) {}
private:
	void inorderTraversal ( Node* node );

	Node* root;
	int _size;
};

int main () {
	int input (1);
	BTree btr;
	cin >> input;
	while (input != 0) {
		btr.add ( input );
		cin >> input;
	}
	btr.inorderTraversal ();
}

void BTree::add ( int data ) {
	Node* act_node = root;

	if (_size == 0) {
		root->data = data;
		_size++;
	}
	else {
		while (true) {
			if (act_node->data > data) {
				if (act_node->left_node != nullptr)
					act_node = act_node->left_node;
				else {
					act_node->left_node = new Node ( data, nullptr, nullptr );
					_size++;
					break;
				}
			}
			else if (act_node->data < data) {
				if (act_node->right_node != nullptr)
					act_node = act_node->right_node;
				else {
					act_node->right_node = new Node ( data, nullptr, nullptr );
					_size++;
					break;
				}
			}
			else break;
		}
	}
}

void BTree::inorderTraversal () {
	if (root->data != NULL) {
		if (root->left_node == nullptr && root->right_node == nullptr) {
			cout << root->data << ' ';
		} else {
			inorderTraversal ( root->left_node );
			inorderTraversal ( root->right_node );
		}
	}
}

void BTree::inorderTraversal (Node* node) {
	if (node != nullptr) {
		if (node->left_node == nullptr && node->right_node == nullptr) {
			cout << node->data << ' ';
		} else {
			inorderTraversal ( node->left_node );
			inorderTraversal ( node->right_node );
		}
	}
}

int BTree::size () {
	return _size;
}