#include <iostream>
#include <string>

int hashTableSize = 1e5;
int mul[] = { 2293, 1999, 3527, 3463, 3571, 1553, 2887, 2687, 3469, 3571 };

struct Node {
	Node () {};
	Node ( std::string data, Node* node = nullptr )
		: data ( data )
		, nextNode ( node ) {}

	std::string data;
	Node* nextNode;
};

struct HashTable {
	HashTable ()
		: Table ( new Node* [hashTableSize] { nullptr } ) {}

	int hashFunction ( std::string str ) {
		size_t ret ( 1 );
		for (int i = 0; i < str.size (); i++)
			ret = str[i] + ret * mul[i];
		return ret % hashTableSize;
	}

	void insert ( const std::string& str ) {
		auto hash = hashFunction ( str );
		if (Table[hash] != nullptr) {
			auto curr = Table[hash];
			while (curr->nextNode != nullptr) curr = curr->nextNode;
			curr->nextNode = new Node ( str );
		} else Table[hash] = new Node ( str );
	}

	void erase ( const std::string& str ) {
		auto hash = hashFunction ( str );
		if (Table[hash] != nullptr && Table[hash]->data != str) {
			auto curr = Table[hash];
			while (curr->nextNode != nullptr || curr->data != str) 
				curr = curr->nextNode;
			if (curr->data != str) return;
		}
			delete Table[hash];
			Table[hash] = nullptr;
	}

	bool check ( const std::string& str ) {
		auto hash = hashFunction ( str );
		if (Table[hash] == nullptr) return false;
		else if (Table[hash]->data != str) {
			auto curr = Table[hash];
			while (curr->nextNode != nullptr || curr->data != str) curr = curr->nextNode;
			if (curr->data != str) return false;
		}
		return true;
	}
	
private:
	Node** Table;
};


int main () {
	using namespace std;
	char cmd ( 1 );
	string str;
	HashTable hs;
	cin >> cmd;
	while (cmd != '#') {
		cin >> str;
		if (cmd == '+')
			hs.insert ( str );
		else if (cmd == '-') {
			hs.erase ( str );
		}
		else
			cout << (hs.check ( str ) ? "YES" : "NO") << endl;
		cin >> cmd;
	}
}