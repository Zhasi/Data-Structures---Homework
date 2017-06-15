#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <vector>
using namespace std;

struct Node
{
	int data;
	Node* left;
	Node* right;

	Node(int d = 0, Node* l = NULL, Node* r = NULL)
	{
		data = d;
		left = l;
		right = r;
	}
};

class BST
{
	Node* root;
	int size;

public:
	BST();
	~BST();
	int getMin() const;
	int getMax() const;
	int getSize() const;
	bool isEmpty() const;

	void push(int x);
	void popMin();
	void popMax();

	int getLevel(int x);
	int getHeightOfNode(int x);
	int getHeightOfTree();
	int getDepth(int x);
	void getElementsInRow(vector<int>& v, int k);

	bool contains(int x);
	void clear();
	Node*& search(int x);

	void preorder();
	void inorder();

	bool isMirror(Node *root1,Node *root2);
	bool isSymmetric();

private:
	void destroy(Node*& node);
	Node*& findNode(int x);
	int calcHeightOfNode(Node*& node);
	void print_preorder(Node*& node);
	void print_inorder(Node*& node);
	void getElementsInRowFromRoot(vector<int>& v, Node*& node, int k);
};

BST::BST()
{
	root = NULL;
	size = 0;
}

BST::~BST()
{
	destroy(root);
}

void BST::clear()
{
	destroy(root);
}

void BST::destroy(Node*& node)
{
	if (node == NULL)
		return;
	destroy(node->left);
	destroy(node->right);

	delete node;
	node = NULL;
	size--;
}

int BST::getSize() const
{
	return size;
}

bool BST::isEmpty() const
{
	return size == 0;
}

int BST::getMin() const
{
	Node* tmp = root;
	while (tmp->left)
	{
		tmp = tmp->left;
	}
	return tmp->data;
}

int BST::getMax() const
{
	Node* tmp = root;
	while (tmp->right)
	{
		tmp = tmp->right;
	}
	return tmp->data;
}

void BST::push(int x)
{
	if (contains(x))
		return;
	Node* tmp = root;
	Node* parent_tmp = NULL;
	while (tmp)
	{
		parent_tmp = tmp;
		if (x < tmp->data)
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}

	tmp = new Node(x);
	if (size == 0)
		root = tmp;
	else
	{
		if (x <= parent_tmp->data)
			parent_tmp->left = tmp;
		else
			parent_tmp->right = tmp;
	}
	size++;
}

bool BST::isMirror(Node *root1,Node *root2)
{
	if (root1 == NULL && root2 == NULL)
		return true;

	if (root1 && root2)
		return isMirror(root1->left, root2->right) &&
		isMirror(root1->right, root2->left);

	return false;
}

bool BST::isSymmetric()
{
	return isMirror(root, root);
}

Node*& BST::findNode(int x)
{
	Node* tmp = root;
	while (tmp && tmp->data != x)
	{
		if (x < tmp->data)
			tmp = tmp->left;
		else
			tmp = tmp->right;
	}
	return tmp;
}

bool BST::contains(int x)
{
	Node*& node = findNode(x);
	if (node == NULL)
		return 0;
	return 1;
}

Node*& BST::search(int x)
{
	return findNode(x);
}

void BST::popMin()
{
	if (root == NULL)
		return;
	if (size == 1)
	{
		destroy(root);
		return;
	}
	Node* parent = NULL;
	Node* tmp = root;
	while (tmp->left)
	{
		parent = tmp;
		tmp = tmp->left;
	}
	if (parent)
		parent->left = tmp->right;
	else /// in case when root has no left subtree, i.e. root is the minimum element in the tree
		root = tmp->right;

	delete tmp;
	size--;
}

void BST::popMax()
{
	if (root == NULL)
		return;
	if (size == 1)
	{
		destroy(root);
		return;
	}
	Node* parent = NULL;
	Node* tmp = root;
	while (tmp->right)
	{
		parent = tmp;
		tmp = tmp->right;
	}
	if (parent)
		parent->right = tmp->left;
	else /// in case when root has no right subtree, i.e. root is the maximum element in the tree
		root = tmp->left;

	delete tmp;
	size--;
}

int BST::calcHeightOfNode(Node*& node)
{
	if (node == NULL)
	{
		return 0;
	}

	return 1 + max(calcHeightOfNode(node->left),
		calcHeightOfNode(node->right));
}

int BST::getHeightOfNode(int x)
{
	Node* tmp = findNode(x);

	return calcHeightOfNode(tmp) - 1;
}

int BST::getHeightOfTree()
{
	if (root == NULL)
		return -1;
	return getHeightOfNode(root->data);
}


int BST::getLevel(int x)
{
	Node* tmp = root;
	int level = 1;
	while (tmp)
	{
		if (x < tmp->data)
			tmp = tmp->left;
		else if (x > tmp->data)
			tmp = tmp->right;
		else
			return level;
		level++;
	}

	return 0;
}

int BST::getDepth(int x)
{
	return getLevel(x) - 1;
}

void BST::preorder()
{
	print_preorder(root);
	cout << endl;
}

void BST::print_preorder(Node*& node)
{
	if (node == NULL)
		return;

	cout << node->data << " ";
	print_preorder(node->left);
	print_preorder(node->right);
}

void BST::inorder()
{
	print_inorder(root);
	cout << endl;
}

void BST::print_inorder(Node*& node)
{
	if (node == NULL)
		return;

	print_inorder(node->left);
	cout << node->data << " ";
	print_inorder(node->right);
}

void BST::getElementsInRow(vector<int>& v, int k)
{
	getElementsInRowFromRoot(v, root, k);
}

void BST::getElementsInRowFromRoot(vector<int>& v, Node*& node, int k)
{
	if (node == NULL)
		return;
	if (k == 0)
	{
		v.push_back(node->data);
		return;
	}

	getElementsInRowFromRoot(v, node->left, k - 1);
	getElementsInRowFromRoot(v, node->right, k - 1);
}

int main()
{
	BST T;
	T.push(30);
	T.push(20);
	T.push(10);
	T.push(25);
	T.push(45);
	T.push(40);
	T.push(50);

	BST T1;
	T1.push(8);
	T1.push(10);
	T1.push(3);
	T1.push(1);
	T1.push(7);
	T1.push(14);
	T1.push(4);
	T1.push(6);
	T1.push(13);
	
	cout << T.isSymmetric() << endl;
	cout << T1.isSymmetric();
	system("pause");
	return 0;
}
