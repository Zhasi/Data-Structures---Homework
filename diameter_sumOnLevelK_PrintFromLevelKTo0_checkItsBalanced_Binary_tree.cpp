/**
Terminologies used in Trees:
Root - The top node in a tree.
Parent - The converse notion of a child.
Siblings - Nodes with the same parent.
Descendant - A node reachable by repeated proceeding from parent to child.
Ancestor - A node reachable by repeated proceeding from child to parent.
Leaf - A node with no children.
Internal node - A node with at least one child.
External node - A node with no children.
Degree - Number of sub trees of a node.
Edge - Connection between one node to another.
Path - A sequence of nodes and edges connecting a node with a descendant.
Level - The level of a node is defined by 1 + (the number of connections between the node and the root).
Height of node - The height of a node is the number of edges on the longest downward path between that node and a leaf.
Height of tree - The height of a tree is the height of its root node.
Depth - The depth of a node is the number of edges from the node to the tree's root node.
Forest - A forest is a set of n >= 0 disjoint trees.
**/
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

	//Task1
	int getSumOnLevel(int K);
	int sumLevelsTree(Node* n1, int k1);

	//Task2
	void getElOnLevelK(int k);
	void elLevelK(Node* ac, int k);

	//Task3
	int	balanceState();
	int CheckTreeHeight(Node* r1);
	int IsBalanced(Node* r2);
	int countChildren(Node* cc);

	//Task 4
	int diameter();
	int diameterHelper(Node * tree);
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
//Task1
int BST::getSumOnLevel(int K)
{
	return sumLevelsTree(root, K);
}

int BST::sumLevelsTree(Node* n1, int k1)
{
	Node* tmp = n1;
	if (tmp == NULL)
		return 0;
	if (k1 == 0) 
		return tmp->data;
	return (sumLevelsTree(tmp->left, k1-1) + sumLevelsTree(tmp->right,k1-1));
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

//Task2
void BST::getElOnLevelK(int k)
{
	for (int i = k; i>=0; i--)
	{
		if (i==0)
			cout << root->data << endl;
		else{
			Node *tmp = root;
			if (tmp->left != NULL)
				elLevelK(tmp->left, i);
			if (tmp->right != NULL)
				elLevelK(tmp->right, i);
			cout << endl;
		}
	}
}

void BST::elLevelK(Node* c, int k)
{
		if (k==1)
			cout << c->data << " ";
		else
		{
			if (c->left != NULL)
				elLevelK(c->left, k-1);
			if (c->right != NULL)
				elLevelK(c->right, k-1);
		}
}

//Task3
int BST::balanceState()
{
	Node* tmp = root;
	return IsBalanced(root);
}

int BST::CheckTreeHeight(Node* root)
{
	
	if (root == NULL) return 0; // Height of 0.

	// Check if left is balanaced
	int leftChildHeight = CheckTreeHeight(root->left);
	if (leftChildHeight == -1) return -1; // Not Balanced

	// Check if right is balanced
	int rightChildHeight = CheckTreeHeight(root->right);
	if (rightChildHeight == -1) return -1; // Not Balanced

	// Check if current node is balanced
	int heightDifference = leftChildHeight - rightChildHeight;

	if (abs(heightDifference) > 1)
		return -1; // not balanaced
	else
		return max(leftChildHeight, rightChildHeight) + 1; // Return Height
}

int BST::IsBalanced(Node* root)
{
	if (CheckTreeHeight(root) == -1)
	{
		return 0;
	}
	else
	{
		if (abs(countChildren(root->left) - countChildren(root->right)) <= 1)
			return 2;
		else
			return 1;
	}
}

int BST::countChildren(Node* cc)
{
	Node* tmp = cc;
	if (tmp->left == NULL && tmp->right == NULL)
		return 0;
	if (tmp->right == NULL)
		return countChildren(tmp->left)+1;
	if (tmp->left == NULL)
		return countChildren(tmp->right)+1;
	return countChildren(tmp->left) + countChildren(tmp->right)+2;
}

//Task 4
int BST::diameter()
{
	return diameterHelper(root);
}

int BST::diameterHelper(Node * dh)
{
	/* base case where tree is empty */
	if (dh == NULL)
		return 0;

	/* get the height of left and right sub-trees */
	int lheight = calcHeightOfNode(dh->left);
	int rheight = calcHeightOfNode(dh->right);

	/* get the diameter of left and right sub-trees */
	int ldiameter = diameterHelper(dh->left);
	int rdiameter = diameterHelper(dh->right);

	/* Return max of following three
	1) Diameter of left subtree
	2) Diameter of right subtree
	3) Height of left subtree + height of right subtree + 1 */
	int diameter = max(lheight + rheight + 1, max(ldiameter, rdiameter));
	return diameter;
}
int main()
{
	//Task1
	BST T4, T5;
	T4.push(10);
	T4.push(6);
	T4.push(18);
	T4.push(4);
	T4.push(8);
	T4.push(15);
	T4.push(21);

	T5.push(8);
	T5.push(3);
	T5.push(10);
	T5.push(1);
	T5.push(6);
	T5.push(14);
	T5.push(4);
	T5.push(7);
	T5.push(13);
	
	cout << T4.getSumOnLevel(2) << endl;
	cout << T5.getSumOnLevel(3) << endl;
		
	//Task2
	int depthOfTree = T4.getHeightOfTree();
	int depthOfTree1 = T5.getHeightOfTree();
	T5.getElOnLevelK(depthOfTree1);
	T4.getElOnLevelK(depthOfTree);
	//Task 3
	BST T,T1,T2;
	//ne e balansirano
	T.push(4);
	T.push(5);
	T.push(8);
	T.push(10);
	T.push(13);

	//balansirano
	T1.push(10);
	T1.push(6);
	T1.push(15);
	T1.push(11);
	T1.push(18);
	
	//idealno balansirano
	T2.push(10);
	T2.push(6);
	T2.push(15);
	T2.push(11);
	
	cout << T.balanceState();
	cout << endl;
	cout << T1.balanceState();
	cout << endl;
	cout << T2.balanceState();
	
	//Task 4
	BST T3;
	T3.push(50);
	T3.push(17);
	T3.push(72);
	T3.push(12);
	T3.push(23);
	T3.push(54);
	T3.push(76);
	T3.push(9);
	T3.push(14);
	T3.push(19);
	T3.push(67);
	
	cout << "T3 diameter= " << T3.diameter();
	system("pause");
	return 0;
}

	
	
	
	