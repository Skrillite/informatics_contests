#include <iostream>
#include <string>
//
using namespace std;

struct Node {
    char data;
    Node* prev_node;

    Node ( char& _data, Node* _prev_node )
        : data ( _data )
        , prev_node ( _prev_node ) {}
};

struct Stack {
    void push ( char n );
    void pop ();
    char back ();
    void size ();
    void clear ();
    bool empty ();

    Stack ()
        : last ( nullptr ) {}
private:
    Node* last;
};


int main () {
    string input;
    Stack stack;
    getline ( cin, input );

    const char o1 ( '(' ), o2 ( '[' ), o3 ( '{' );
    const char c1 ( ')' ), c2 ( ']' ), c3 ( '}' );

    for (auto& i : input) {
        if (i == o1 || i == o2 || i == o3)
            stack.push ( i );
        else {
            switch (i) {
                case c1:
                {
                    if (stack.back () == o1) {
                        stack.pop ();
                    } else {
                        cout << "no";
                        return 0;
                    }
                    break;
                }
                case (c2):
                {
                    if (stack.back () == o2) {
                        stack.pop ();
                    } else {
                        cout << "no";
                        return 0;
                    }
                    break;
                }
                case (c3):
                {
                    if (stack.back () == o3) {
                        stack.pop ();
                    } else {
                        cout << "no";
                        return 0;
                    }
                    break;
                }
            }
        }
    }
    if (stack.empty ())
        cout << "yes";
    else cout << "no";
}

    bool Stack::empty () {
        if (last == nullptr) return true;
        return false;
    }

    void Stack::push ( char n ) {
        if (!empty ()) {
            last = new Node ( n, last );
        } else {
            last = new Node ( n, nullptr );
        }
    }

    void Stack::pop () {
        if (!empty ()) {

            Node* tmp = last;
            last = last->prev_node;
            delete tmp;
        } else
            cout << "error" << endl;
    }

    char Stack::back () {
        if (!empty ()) {
            return last->data;
        } else
            cout << "no";
        exit ( 0 );
    }
