#include "bst.h"

// ---------------------------------------
// Node class
// Default constructor
Node::Node() {
	this->key = 0;
	this->parent=nullptr;
	this->left = nullptr;
	this->right = nullptr;
}
// Constructor
Node::Node(int in) {
	this->key = in;
	this->parent=nullptr;
	this->left = nullptr;
	this->right = nullptr;
}
// Destructor
Node::~Node() {

}

// Add parent 
void Node::add_parent(Node* in) {
	this->parent = in;
}
// Add to left of current node
void Node::add_left(Node* in) {
	this->left = in;
}
// Add to right of current node
void Node::add_right(Node* in) {
	this->right = in;
}

// Get key
int Node::get_key()
{
	return this->key;
}
// Get parent node
Node* Node::get_parent()
{
	return this->parent;
}
// Get left node
Node* Node::get_left()
{
	return this->left;
}
// Get right node
Node* Node::get_right()
{
	return this->right;
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
	if (in!=nullptr) {
		if (in->get_left()!=nullptr) {
			inorder_walk(in->get_left(), to);
		}
		in->print_info(to);
		if (in->get_right()!=nullptr) {
			inorder_walk(in->get_right(), to);
		}
	}
}
void freedom(Node* source) {
	if (source!=nullptr) {
		if (source->get_left() != nullptr) {
			freedom(source->get_left());
		}
		if (source->get_right() != nullptr) {
			freedom(source->get_right());
		}
		delete source;
	}
}
// Constructor
BST::BST()
{
	root = nullptr;
}
// Destructor
BST::~BST()
{
	freedom(root);
}
// Insert a node to the subtree
void BST::insert_node(Node* in)
{
	Node* holder = nullptr;
	Node* location = this->root;
	int l_or_r = 0;
	while (location!=nullptr) {
			holder = location;
			if (in->get_key()<location->get_key()) {
				location = location->get_left();
				l_or_r = 0;
			}
			else {
				location = location->get_right();
				l_or_r = 1;
			}
		}	
	in->add_parent(holder);
	if (holder == nullptr) {
		this->root = in;
	}
	else if (l_or_r==1) {
		holder->add_right(in);
	}
	else {
		holder->add_left(in);
	}
}
// Delete a node to the subtree
void BST::delete_node(Node* out)
{
	// if no children
	if ((out->get_right() == nullptr) && (out->get_left() == nullptr)) {
		if (out->get_parent()->get_right() == out) {
			out->get_parent()->add_right(nullptr);
		}
		else {
			out->get_parent()->add_left(nullptr);
		}
		delete out;
	}
	// if one child
	else if ((out->get_right() == nullptr) || (out->get_left() == nullptr)) {
		// if only child is left
		if (out->get_parent() == nullptr) {
			if (out->get_right() == nullptr) {
				out->get_left()->add_parent(nullptr);
				this->root = out->get_left();
			}
			else {
				out->get_right()->add_parent(nullptr);
				this->root = out->get_right();
			}
			delete out;
		}
		else {
		Node * child;
		Node * parent = out->get_parent();
		if (out->get_right() == nullptr) {
			child = out->get_left();
			child->add_parent(parent);
		}
		// if only child is right
		else {
			child = out->get_right();
			child->add_parent(parent);
		}
		if (parent->get_left() == out) {
			parent->add_left(child);
		}
		else {
			parent->add_right(child);
		}
		delete out;
		}
	}
	// if two children
	else {
		if (out->get_parent() == nullptr) {
			Node * max = get_max(out->get_left());
			out->get_right()->add_parent(max);
			max->add_right(out->get_right());
			out->get_left()->add_parent(nullptr);
			this->root = out->get_left();
			delete out;
		}
		else {
		Node * parent = out->get_parent();
		Node * left = out->get_left();
		Node * right = out->get_right();
		if (parent->get_right() == out) {
			Node * new_parent = get_max(left);
			right->add_parent(new_parent);
			new_parent->add_right(right);
			left->add_parent(parent);
			parent->add_right(left);
			delete out;
		}
		else {
			Node * new_parent = get_min(out->get_right());
			left->add_parent(new_parent);
			new_parent->add_left(left);
			right->add_parent(parent);
			parent->add_left(right);
			delete out;
		}
		}
	}

}
// minimum key in the BST
Node* BST::tree_min()
{
	return get_min(root);
}
// maximum key in the BST
Node* BST::tree_max()
{
	return get_max(root);
}
// Get the minimum node from the subtree of given node
Node* BST::get_min(Node* in)
{
	Node* tmp = in;
	while (tmp->get_left()){
		tmp = tmp->get_left();
	}
	return tmp;

}
// Get the maximum node from the subtree of given node
Node* BST::get_max(Node* in)
{
	Node* tmp = in;
	while (tmp->get_right()){
		tmp = tmp->get_right();
	}
	return tmp;
}
// Get successor of the given node
Node* BST::get_succ(Node* in)
{
	Node* tmp = in;
	if (tmp == tree_max()){
		return nullptr;
	}
	if (tmp->get_right() != nullptr) {
		return get_min(tmp->get_right());
	}
	Node* new_tmp = tmp->get_parent();
	while (new_tmp != nullptr && tmp==new_tmp->get_right()){
		tmp = new_tmp;
		new_tmp = new_tmp->get_parent();
	}
	return new_tmp;
}
// Get predecessor of the given node
Node* BST::get_pred(Node* in)
{
	Node* tmp = in;
	if (tmp == tree_min()){
		return nullptr;
	}
	if (tmp->get_left() != nullptr) {
		return get_max(tmp->get_left());
	}
	Node* new_tmp = tmp->get_parent();
	while (new_tmp != nullptr && tmp==new_tmp->get_left()){
		tmp = new_tmp;
		new_tmp = new_tmp->get_parent();
	}
	return new_tmp;
}
// Walk the BST from min to max
void BST::walk(ostream& to)
{
	inorder_walk(root, to);

}
// Search the tree for a given key
Node* BST::tree_search(int search_key)
{
	Node* tmp = root;
	while (tmp!=nullptr && tmp->get_key()!=search_key){
		if (search_key < tmp->get_key()){
			tmp = tmp->get_left();
		}
		else{
			tmp = tmp->get_right();
		}
	}
	return tmp;
}
// ---------------------------------------
