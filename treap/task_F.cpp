#include <iostream>
#include <algorithm>
#include <vector>
#include <stdexcept>
#include <ctime>


struct Node {
	Node ()
		: subtree_size ( NULL )
		, data ( NULL )
		, sum  (NULL)
		, priority ( NULL )
		, left ( nullptr )
		, right ( nullptr )
		, reversed (false) {};

	Node ( int _data, int _priority, Node* _parent = nullptr,
		Node* _left = nullptr, Node* _right = nullptr )
		: subtree_size ( 1 )
		, sum ( _data )
		, data ( _data )
		, priority ( _priority )
		, left ( _left )
		, right ( _right )
		, reversed (false) {}

	friend struct Treap;

	void Recalc () {
		auto root = this;
		this->subtree_size = ((this->left == nullptr) ? 0 : this->left->subtree_size)
			+ ((this->right == nullptr) ? 0 : this->right->subtree_size)
			+ 1;

		this->sum = ((this->left == nullptr) ? 0 : this->left->sum)
			+ ((this->right == nullptr) ? 0 : this->right->sum) + this->data;
	}

private:
	int data;
	int priority;
	int64_t sum;
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

		root->Recalc ();
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

	int sumof ( int idxA, int idxB ) {
		idxB -= idxA - 1;
		Node* middle ( new Node ), * right ( new Node );
		split ( idxA - 1, this->root, middle );
		split ( idxB, middle, right, middle );
		int64_t ret = middle->sum;
		merge ( this->root, middle );
		merge ( this->root, right );
		return ret;
	}

	int64_t sumof ( int idxA, int idxB, Treap& tr_odd ) {
		int oddidxA, oddidxB, paiidxA, paiidxB;

		bool idxA_odd = idxA & 1;
		bool idxB_odd = idxB & 1;


		oddidxA = (idxA + !idxA_odd) / 2;
		oddidxB = (idxB - !idxB_odd) / 2 + 1;
		paiidxA = (idxA + idxA_odd) / 2 - 1;
		paiidxB = (idxB - idxB_odd) / 2;

		oddidxB -= oddidxA;
		paiidxB -= paiidxA;

		Node* middle_pai ( new Node ), * right_pai ( new Node )
			, * middle_odd ( new Node ), * right_odd ( new Node );

		if (this->root != nullptr) split ( paiidxA, this->root, middle_pai );
		if (middle_pai != nullptr) split ( paiidxB, middle_pai, right_pai, middle_pai );
		if (tr_odd.root != nullptr) split ( oddidxA, tr_odd.root, middle_odd, tr_odd.root );
		if (middle_odd != nullptr) split ( oddidxB, middle_odd, right_odd, middle_odd );

		int64_t ret = ((middle_odd == nullptr) ? 0 : middle_odd->sum)
			+ ((middle_pai == nullptr) ? 0 : middle_pai->sum);

		merge ( this->root, middle_pai );
		merge ( this->root, right_pai );
		merge ( tr_odd.root, middle_odd, tr_odd.root );
		merge ( tr_odd.root, right_odd, tr_odd.root );

		return ret;
	}

	void swapper ( int idxA, int idxB, Treap& tr_odd ) {

		int oddidxA, oddidxB, paiidxA, paiidxB;
		bool idx_odd = idxA & 1;

		oddidxA = (idxA + !idx_odd) / 2;
		oddidxB = (idxB - idx_odd) / 2 + 1;
		paiidxA = (idxA + idx_odd) / 2 - 1;
		paiidxB = (idxB - !idx_odd) / 2;

		oddidxB -= oddidxA;
		paiidxB -= paiidxA;

		Node* middle_pai ( new Node ), * right_pai ( new Node )
			, * middle_odd ( new Node ), * right_odd ( new Node );

		if (this->root != nullptr) split ( paiidxA, this->root, middle_pai );
		if (middle_pai != nullptr) split ( paiidxB, middle_pai, right_pai, middle_pai );
		if (tr_odd.root != nullptr) split ( oddidxA, tr_odd.root, middle_odd, tr_odd.root );
		if (middle_odd != nullptr) split ( oddidxB, middle_odd, right_odd, middle_odd );

		merge ( this->root, middle_odd );
		merge ( this->root, right_pai );
		merge ( tr_odd.root, middle_pai, tr_odd.root );
		merge ( tr_odd.root, right_odd, tr_odd.root );
	}

	void InorderTraversal () {
		InorderTraversal ( root );
	}

	void InorderTraversal ( Node* root ) {

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

	int n, m, counter(1);
	cin >> n >> m;
	while (n != 0) {
		cout << "Swapper " << counter << ':' << endl;
		int a, b, tmp, cmd;
		Treap tr_pai;
		Treap tr_odd;
		for (int i = 0; i < n; i++) {
			cin >> tmp;
			if (i & 1) tr_pai.push_back ( tmp );
			else tr_odd.push_back ( tmp );
		}

		while (m-- > 0) {
			cin >> cmd >> a >> b;
			switch (cmd) {
				case 1:
				{
					tr_pai.swapper ( a, b, tr_odd);
					break;
				}
				case 2:
				{
					cout << tr_pai.sumof ( a, b, tr_odd ) << endl;
					break;
				}
			}
		}
		cout << "\n";
		counter++;
		cin >> n >> m;
	}
}