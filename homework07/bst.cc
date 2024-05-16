#include "bst.h"

// ---------------------------------------
// Node class
// Default constructor
Node::Node() {
// TODO: Implement this
parent=nullptr;
left=nullptr;
right=nullptr;

}
// Constructor
Node::Node(int in) {
// TODO: Implement this

key=in;
parent=nullptr;
left=nullptr;
right=nullptr;
}
// Destructor
Node::~Node() {
// TODO: Implement this
    
}

// Add parent i
void Node::add_parent(Node* in) {
// TODO: Implement this
parent= in;
}
// Add to left of current node
void Node::add_left(Node* in) {
// TODO: Implement this
left= in;
}
// Add to right of current node
void Node::add_right(Node* in) {
// TODO: Implement this
right= in;
}

// Get key
int Node::get_key()
{
	
    return key;
// TODO: Implement this
}
// Get parent node
Node* Node::get_parent()
{
// TODO: Implement this
return parent;
}
// Get left node
Node* Node::get_left()
{
// TODO: Implement this
return  left;
}
// Get right node
Node* Node::get_right()
{
// TODO: Implement this
return right;
}
// Print the key to ostream to
// Do not change this
void Node::print_info(ostream& to)
{
    to << key << endl;
}
// ---------------------------------------


// ---------------------------------------
// BST class
// Walk the subtree from the given node
void BST::inorder_walk(Node* in, ostream& to)
{
// TODO: Implement this
/* INORDER-TREE-WALK(x)
if x != NIL then
    INORDER-TREE-WALK(left[x])
    print key[x]
    INORDER-TREE-WALK(right[x])
INORDER-TREE-WALK(root)*/

if (in != nullptr) {
		inorder_walk(in->get_left(), to);
		in->print_info(to);
		inorder_walk(in->get_right(), to);
	}

}
// Constructor
BST::BST()
{
    // TODO: Implement this
      root=nullptr;
}
// Destructor
BST::~BST()
{
// TODO: Implement this
	while (root != nullptr) {
		delete_node(root);
	}
}
// Insert a node to the subtree
void BST::insert_node(Node* in)
{

// TODO: Implement this
	  Node* z = in;
    Node* y = nullptr;
    Node* x = root; // Assuming 'root' is a member variable of your Bst class

    while (x != nullptr) {
        y = x;
        if (z->get_key() < x->get_key()) {
            x = x->get_left();
        } else {
            x = x->get_right();
        }
    }

    z->add_parent(y);

    if (y == nullptr) {
        root = z;
    } else if (z->get_key() < y->get_key()) {
        y->add_left(z);
    } else {
        y->add_right(z);
    }

   
}

// Delete a node to the subtree
void BST::delete_node(Node* out)
{
// TODO: Implement this

if (out->get_left() == nullptr) {
		transplant(out, out->get_right());
	}
	// The node to delete doesn't have a right child
	else if (out->get_right() == nullptr) {
		transplant(out, out->get_left());
	}
	// The node has two children
	else {
		// Get the successor
		Node *y = get_succ(out);
		// The successor's parent isn't the node we're deleting
		if (y->get_parent() != out) {
			transplant(y, y->get_right());
			// Add a right child and parent to y
			y->add_right(out->get_right());
			y->get_right()->add_parent(y);
		}
		transplant(out, y);
		// Add a left child and parent to y
		y->add_left(out->get_left());
		y->get_left()->add_parent(y);
	}
	delete out;
}
// minimum key in the BST
Node* BST::tree_min()
{
// TODO: Implement this

// Start at the root and go  to the left-most node
	Node *min = root;
	while (min->get_left() != nullptr) {
		min = min->get_left();
	}
	return min;
}
// maximum key in the BST
Node* BST::tree_max()
{
// TODO: Implement this
Node *max = root;
	while (max->get_right() != nullptr) {
		max = max->get_right();
	}
	return max;
}
// Get the minimum node from the subtree of given node
Node* BST::get_min(Node* in)
{
// TODO: Implement this

while( in->get_left() != nullptr) {
		in = in->get_left();
	}
	return in;
}
// Get the maximum node from the subtree of given node
Node* BST::get_max(Node* in)
{
// TODO: Implement this
while (in->get_right() != nullptr) {
		in = in->get_right();
	}
	return in;
}
// Get successor of the given node
Node* BST::get_succ(Node* in)
// TODO: Implement this
{
	// If in has a right subtree, return the min from there
    if (in->get_right() != nullptr) {
        return get_min(in->get_right());
    }

    // Otherwise, go up the tree until you find the successor
    Node* y = in->get_parent();
    while (y != nullptr and in == y->get_right()) {
        in = y;
        y = y->get_parent();
    }

    // Check if there is no successor (input node is the maximum node in the tree)
    if (y == nullptr) {
        return nullptr;
    }

    return y;
}
// Get predecessor of the given node
Node* BST::get_pred(Node* in)
{
// TODO: Implement this
 

// If in has a left subtree, return the max from there
    if (in->get_left() != nullptr) {
        return get_max(in->get_left());
    }

    // Otherwise, go up the tree until you find the predecessor
    Node* y = in->get_parent();
    while (y != nullptr and in == y->get_left()) {
        in = y;
        y = y->get_parent();
    }

    // Check if there is no predecessor (input node is the minimum node in the tree)
    if (y == nullptr) {
        return nullptr;
    }

    return y;
}


// Walk the BST from min to max
void BST::walk(ostream& to)
{
// TODO: Implement this

inorder_walk(root, to);
}
// Search the tree for a given key
Node* BST::tree_search(int search_key)
{
// TODO: Implement this
/*REE-SEARCH(x, k)
while x != NIL and k != key[x]
    if k < key[x] then
        x <- left[x]
    else
        x <- right[x]
    return x

*/
Node *x=root;
while(x!= nullptr and search_key!=x-> get_key()){
    if (search_key < x -> get_key()){
        x= x->get_left();

    }
    else{
        x= x->get_right();
    }
}
return x;
}
void BST::transplant(Node *u, Node *v) {
	// u's parent is null (we are at the root)
	if (u->get_parent() == nullptr) {
		root = v;
	}
	// u is the left child of it's parent
	else if (u == u->get_parent()->get_left()) {
		u->get_parent()->add_left(v);
	}
	// u is the right child of it's parent
	else {
		u->get_parent()->add_right(v);
	}

	// v is an actual node so we have to replace it's parent with u's
	if (v != nullptr) {
		v->add_parent(u->get_parent());
	}
}
// ---------------------------------------

