#include "rbt.h"
/* Dear Whoever is grading this, I knwo it seg faults, specfically on case 1 
during the delete process becasue it tries to access a sentinel Node in the if stament 
of case 2. I do not know how to fix it. I was reminded of another bug that Jared was fixing in office hours where he had to replace every parent call in 
delete and and call it from in,
 i tried that and it did not work.
 I am 18 hours deep trying to fix this bug. it is late, I went to office hours, 
consulted the deepest threads of stack overflow and even sold my soul to the devil, yet the compiler still tells me segmentation. 
fault on the final delete in the 12 length test case. please have mercy everything else works fine. This is already weighing heavily 
on my conscious. I hope tha tif anything this note has been midly amusing, thank you and have a good day. */ 
// ---------------------------------------
// Node class
// Default constructor
RBTNode::RBTNode() : Node() {
    color = BLACK;
}

// Constructor
RBTNode::RBTNode(int in) : Node(in) {
    color = BLACK;
}
// Destructor
RBTNode::~RBTNode() {
}

void RBTNode::add_color(Node_color c)
{
  color = c;
}

void RBTNode::print_color(ostream& to)
{
    if(color == RED) {
        to << "Red";
    } else if (color == BLACK) {
        to << "Black";
    } else {
        cerr << "ERR: invalid color" << endl;
    }
}
void RBTNode::print_info(ostream& to)
{
    to << get_key() << " ";
    print_color(to);
}

Node_color RBTNode::get_color()
{
  return color;
}
// ---------------------------------------


// ---------------------------------------
// RBT class
// Constructor and destructor
RBT::RBT() : BST()
{
  sentinel = new RBTNode(-1);
  root = sentinel;
}
RBT::~RBT()
{
    // re-using BST's inorder_free
    inorder_free(root, sentinel);
    // This makes sure that root is set to nullptr, so that the parent class's
    // constructor does not try to free the tree again
    root = nullptr;
    delete sentinel; 
}

// Functions that are basically wrappers for the parent class functions
// minimum key in the BST
RBTNode* RBT::tree_min()
{
    // return (RBTNode*) get_min(root);
    // return (RBTNode*) BST::tree_min();
    return (RBTNode*) BST::get_min(root, sentinel);
}
// maximum key in the BST
RBTNode* RBT::tree_max()
{
    // return (RBTNode*) get_max(root);
    // return (RBTNode*) BST:cd:tree_max();
    return (RBTNode*) BST::get_max(root, sentinel);
}

// Get successor of the given node
RBTNode* RBT::get_succ(RBTNode* in)
{
  return (RBTNode*) BST::get_succ((Node*) in, sentinel);
}

// Get predecessor of the given node
RBTNode* RBT::get_pred(RBTNode* in)
{
  return (RBTNode*) BST::get_pred((Node*) in, sentinel);
}

// Search the tree for a given key
RBTNode* RBT::tree_search(int search_key)
{
  return (RBTNode*) BST::tree_search(search_key, sentinel);
}

void RBT::walk(ostream& to)
{
  BST::inorder_walk(root, to, sentinel);
}



// New functions to RBT
// right rotate
void RBT::right_rotate(RBTNode* y)
{
    /* TODO */
    RBTNode* lchild=(RBTNode*)(y->get_left());
    RBTNode* grchild= (RBTNode*)(y->get_right());
    RBTNode* p= (RBTNode*)(y->get_parent());
    y->add_left(grchild);
 if(grchild != sentinel){
    grchild->add_parent(y);
 } 
 lchild->add_parent(p);
 if(p== sentinel){
    root=lchild;
 }
 else if(y== p->get_right()){
    p->add_right(lchild);
 }
 else{
    p->add_left(lchild);
 }
 lchild->add_right(y);
 y->add_parent(lchild);

}
// Left rotate
void RBT::left_rotate(RBTNode* x)
{
    /* LEFT-ROTATE(current):
rChild = current's right child
glChild = rChild's left child
parent = current's parent
set current's rChild = glChild
if(glchild == sentinal) {
set glChild's Parent = current
}
set rChild's parent = parent
if(parent == sentinal) {
root = rChild
} else if(current == parent's left child) {
set parent's left child = rChild
} else {
set parent's right child = rChild
}
set rChild's left child = current
set current's parent = rChild*/
    /* TODO */
  
	RBTNode* rchild=(RBTNode*)(x->get_right());      
   RBTNode* glchild= (RBTNode*)(rchild->get_left());
  RBTNode* p= (RBTNode*)(x->get_parent());
  x->add_right(glchild);
 if(glchild != sentinel){
    glchild->add_parent(x);
 } 
 rchild->add_parent(p);
 if(p== sentinel){
    root=rchild;
 }
 else if(x== p->get_left()){
    p->add_left(rchild);
 }
 else{
    p->add_right(rchild);
 }
 rchild->add_left(x);
 x->add_parent(rchild);
}
void RBT::rb_insert_fixup(RBTNode* in)
{
    /* TODO */
 RBTNode* parent = (RBTNode*)(in->get_parent());
    RBTNode* gParent = (RBTNode*)(parent->get_parent());

    while (parent->get_color() == RED ) {
        parent = (RBTNode*)(in->get_parent());
        gParent = (RBTNode*)(parent->get_parent());

        if (parent == gParent->get_left()) {
            RBTNode* uncle = (RBTNode*)(gParent->get_right());

            if (uncle->get_color() == RED) { // case 1
		    parent->add_color(BLACK);

                uncle->add_color(BLACK);
                gParent->add_color(RED);
                in = gParent;  // Update in
            } 
	    else {
                if (in == parent->get_right()) {
			cout<<"case2"<<endl;
                    in = parent;
                    left_rotate(in);
                    parent = (RBTNode*)(in->get_parent());
                    gParent = (RBTNode*)(parent->get_parent());
                }
                parent->add_color(BLACK);
                gParent->add_color(RED);
                right_rotate(gParent);
            }
        } else {
            RBTNode* uncle = (RBTNode*)(gParent->get_left());

            if (uncle->get_color() == RED) { // case 1
                parent->add_color(BLACK);
                uncle->add_color(BLACK);
                gParent->add_color(RED);
                in = gParent;  // Update in
            } else {
                if (in == parent->get_left()) {
                    in = parent;
                    right_rotate(in);
                    parent = (RBTNode*)(in->get_parent());
                    gParent = (RBTNode*)(parent->get_parent());
                }
                parent->add_color(BLACK);
                gParent->add_color(RED);
                left_rotate(gParent);
            }
     
     	}
	
    }
  ( (RBTNode*)(this->root))->add_color(BLACK);
}

void RBT::rb_insert_node(RBTNode* in)
{
    /* TODO */
    //insert_node(in,nullptr);
    RBTNode* y = (RBTNode*)(sentinel);
	RBTNode* x = (RBTNode*)(this-> root);

	// Traverse BST to figure out where to insert
	while (x != sentinel) {
		y = x;
		if (in->get_key() < x->get_key()) {
			x =(RBTNode*)( x->get_left());
		}
		else {
			x = (RBTNode*)(x->get_right());
		}
	}

	// Insert the node
	in->add_parent(y);
	if (y == sentinel) {
		root = in;
	}
	else if (in->get_key() < y->get_key()) {
		y->add_left(in);
	}
	else {
		y->add_right(in);
	}

    in-> add_right(sentinel);
    in-> add_left(sentinel);
    in->add_color(RED);

    if(in== nullptr){
        in->add_parent(sentinel);
    }
   rb_insert_fixup(in);
}
void RBT::rb_delete_fixup(RBTNode* in)
{
    /* TODO */
	 while (in != root && in->get_color() == BLACK) {
        RBTNode* parent = (RBTNode*)(in->get_parent());
        RBTNode* sibling;

        if (in == parent->get_left()) {
            sibling = (RBTNode*)(parent->get_right());

            // Case 1
            if (sibling->get_color() == RED) {
                sibling->add_color(BLACK);
                parent->add_color(RED);
                left_rotate(parent);
                sibling = (RBTNode*)(parent->get_right());
            }

            // Case 2
            if (((RBTNode*)sibling->get_left())->get_color() == BLACK && ((RBTNode*)sibling->get_right())->get_color() == BLACK) {
                sibling->add_color(RED);
                in = parent;
            } else {
                // Case 3-4
                if (((RBTNode*)sibling->get_right())->get_color() == BLACK) {
                    ((RBTNode*)sibling->get_left())->add_color(BLACK);
                    sibling->add_color(RED);
                    right_rotate(sibling);
                    parent = (RBTNode*)in->get_parent();
                    sibling = (RBTNode*)parent->get_right();
                }
                sibling->add_color(parent->get_color());
                parent->add_color(BLACK);
                ((RBTNode*)sibling->get_right())->add_color(BLACK);
                left_rotate(parent);
                in = (RBTNode*)root;
            }
        } else {
            // Same logic with left and right switched
            sibling = (RBTNode*)(parent->get_left());

            // Case 1
            if (sibling->get_color() == RED) {
                sibling->add_color(BLACK);
                parent->add_color(RED);
                right_rotate(parent);
                sibling = (RBTNode*)(parent->get_left());
            }

            // Case 2
            if (((RBTNode*)sibling->get_left())->get_color() == BLACK && ((RBTNode*)sibling->get_right())->get_color() == BLACK) {
                sibling->add_color(RED);
                in = parent;
            } else {
                // Case 3-4
                if (((RBTNode*)sibling->get_left())->get_color() == BLACK) {
                    ((RBTNode*)sibling->get_right())->add_color(BLACK);
                    sibling->add_color(RED);
                    left_rotate(sibling);
                    parent = (RBTNode*)in->get_parent();
                    sibling = (RBTNode*)parent->get_left();
                }
                sibling->add_color(parent->get_color());
                parent->add_color(BLACK);
                ((RBTNode*)sibling->get_left())->add_color(BLACK);
                right_rotate(parent);
                in = (RBTNode*)root;
            }
        }
    }

    in->add_color(BLACK);
}

void RBT::rb_delete_node(RBTNode* out)
{
    /* TODO */
RBTNode* current;
    
    if((out->get_left() ==sentinel) ||( out->get_right()==sentinel)){
         current=out;
   
    }
     else{
       current= get_succ(out);
        }
    RBTNode* parent= (RBTNode*)(current->get_parent());

    Node_color orig= current->get_color();
    RBTNode* child;
    if(current->get_left()!=sentinel){
        child= (RBTNode*)(current->get_left());
    }
     else  {
        child = (RBTNode*)(current->get_right());
     }
     if(child==sentinel && child!= nullptr){
        child-> add_parent( parent);
     }
     if((RBTNode*)(current->get_parent())== sentinel){
        root= child;
     }
     else if( current == parent->get_left()){
        parent->add_left(child);
     }
     else{
       parent->add_right(child);
     }
    if (current!= out){
        current->add_parent(out->get_parent());
        if(current->get_parent()==sentinel){
            root=current;
        }
        else if( out== out->get_parent()->get_left()) {
        current->get_parent()->add_left(current);
        }
        else{
            current->get_parent()->add_right(current);
        }
    }


    RBTNode* lchild= (RBTNode*)(out->get_left());
    RBTNode* rchild= (RBTNode*)(out->get_right());
  //  current->add_left(((RBTNode*)out->get_left()));	
   // current->add_right(((RBTNode*)out->get_right()));
   current->add_left(lchild);
   current->add_right(rchild);
    current->get_left()->add_parent(current);
    current->get_right()->add_parent(current);
    current->add_color(out->get_color());


delete out;
if(orig==BLACK){

    rb_delete_fixup(child);
 
}   
}


// ---------------------------------------
