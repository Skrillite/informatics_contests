#include <iostream>
#include <cmath>
#include <algorithm>

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
	bool balanceChecker ();

	BTree ()
		: root ( new Node ( NULL, nullptr, nullptr ) )
		, _size ( 0 ) {}
private:
	pair<bool, int> balanceChecker ( Node* node );

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
	if (btr.balanceChecker ()) cout << "YES";
	else cout << "NO";
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

bool BTree::balanceChecker () {
	pair<bool, int> left ( balanceChecker ( root->left_node ) )
		, right ( balanceChecker ( root->right_node ) );
	return (left.first && right.first && abs ( left.second - right.second ) < 2);
}

pair<bool, int> BTree::balanceChecker ( Node* node ) {
	if (node == nullptr) 
		return make_pair ( 1, 0 );
	else {
		auto left = balanceChecker ( node->left_node ); 
		left.second++;
		auto right = balanceChecker ( node->right_node );
		right.second++;
		auto ret = make_pair ( (left.first && right.first && abs ( left.second - right.second ) < 2)
			, max ( left.second, right.second ) );
		return ret;
	}
}

int BTree::size () {
	return _size;
}