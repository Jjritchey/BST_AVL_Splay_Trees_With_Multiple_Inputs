#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>


using namespace std;

class avl
{
	struct node                                            //struct to holds the nodes that make up the tre
	{
		int post;                                          //holds the interger value of the node
		node* l;                                           //pointer to the left node value
		node* r;                                           //pointer to the right node value
	};

	node* tree;

	node* insertAvlNode(int num, node* tree)
	{
		if (tree == NULL)
		{
			cout << "Working\n\n";
			tree = new node;
			tree->post = num;
			tree->l = NULL;
			tree->r = NULL;
			
		}
		else if (num < tree->post)
		{
			tree->l = insertAvlNode(num, tree->l);
			tree = avlBalance(tree, num);
		}
		else if (num > tree->post)
		{
			tree->r = insertAvlNode(num, tree->r);
			tree = avlBalance(tree, num);
		}
		else
		{
			return tree;
		}
		return tree;
	}

	node* avlBalance(node* tree, int num)
	{
		int bal = nodeBalance(tree);

		if (bal > 1)
		{
			if (nodeBalance(tree->l) > 0)
			{
				tree = rotateLeft(tree);
				cout << "**" << tree->post << "**" << endl;
			}
			else
			{
				return doubelRotateLeft(tree);
			}
		}
		else if (bal < -1)
		{
			if (nodeBalance(tree->r) > 0)
			{
				return doubleRotateRight(tree);
			}
			else
			{
				return rotateRight(tree);

			}
		}
		return tree;
	}

	node* rotateRight(node* tree)
	{
		node* tmp;

		tmp = tree->r;
		tree->r = tmp->l;
		tmp->l = tree;

		return tmp;
	}

	node* rotateLeft(node* tree)
	{
		cout << "\n**rotate left**\n" << endl;
		node* tmp;

		tmp = tree->l;
		tree->l = tmp->r;
		tmp->r = tree;

		return tmp;
	}

	node* doubleRotateRight(node* tree)
	{
		node* tmp;
		tmp = tree->r;
		tree->r = rotateLeft(tmp);
		return rotateRight(tree);
	}

	node* doubelRotateLeft(node* tree)
	{
		node* tmp;
		tmp = tree->l;
		tree->l = rotateRight(tmp);
		return rotateLeft(tree);
	}

	int nodeBalance(node* tree)
	{
		if (tree == NULL)
		{
			return 0;
		}
		return treeHeight(tree->l) - treeHeight(tree->r);
	}

	int treeHeight(node* tree)                                   //function to gather tree height
	{
		if (tree == NULL)                                        //if empty return 0
		{
			return 0;
		}
		else                                                     //if not empty, find the hieght of the left and right subtree and return the higher value
		{
			int rheight = treeHeight(tree->r);
			int lheight = treeHeight(tree->l);

			if (rheight > lheight)
			{
				return (rheight + 1);
			}
			else
			{
				return (lheight + 1);
			}
		}
	}

	void printAVLTree(node* tree, ofstream& file)                   //function to print out the tree level by level
	{
		if (tree == NULL)                                        //if the tree is empty will return with message
		{
			cout << "Tree is empty";
			file << "Tree is empty";
			return;
		}

		queue<node*> que;                                        //makes a queue of node pointers
		que.push(tree);                                          //adds the nodes of the tree into the queue

		while (que.empty() == false)
		{
			int numNodes = que.size();                           //gathers the amount of nodes

			while (numNodes > 0)                                 //While there are still nodes in the queue loop will keep moving
			{
				node* node = que.front();                        //accessing the first node in the queue
				cout << node->post;                              //prints out the node
				file << node->post;
				que.pop();                                       //removes this node from the queue

				if (node->l != NULL)                             //checks if the left and right pointer have values
				{                                                //adds them to the queue if they do
					que.push(node->l);
				}
				if (node->r != NULL)
				{
					que.push(node->r);
				}

				cout << " ";
				file << " ";
				--numNodes;                                      //subtracting one from the number of nodes in the queue counter
			}
			cout << endl;                                        //going to next line after each print
			file << endl;
		}
	}

public:
	avl()
	{
		tree = NULL;
	}
	void avlBalance(int num)
	{
		avlBalance(tree, num);
	}

	void insertAvlNode(int num)
	{
		insertAvlNode(num, tree);
	}

	void printTree(ofstream& file)                                 //function to print a tree
	{
		printAVLTree(tree, file);
	}

	int treeHeight()                                               //function to gather the tree's height
	{
		return treeHeight(tree);
	}



};