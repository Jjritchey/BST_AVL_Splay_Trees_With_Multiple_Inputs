
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <queue>

using namespace std;

class BstTree
{
	struct node                                            //struct to holds the nodes that make up the tre
	{
		int post;                                          //holds the interger value of the node
		node* l;                                           //pointer to the left node value
		node* r;                                           //pointer to the right node value
		node* p;                                           //pointer to the parent node
		int h;                                             //holds the height of the node
	};

	node* tree;                                            //will hold the tree

	node* createBstTree(int num, node* n, int &s)                  //function to create a tree
	{
		if (n == NULL)                                     //if the tree is empty, make the number entered the root
		{
			n = new node;
			n->post = num;
			n->l = NULL;
			n->r = NULL;
			n->p = NULL;
			n->h = NULL;
			s++;
		}
		else if (n->post < num)                            //if the number being inserted is greater than the current number assign this new number to the right pointer
		{
			n->r = createBstTree(num, n->r, s);
			n->r->p = n;
			s++;
		}
		else if (n->post == num)                           //if the number eneterd is the same as a current number, it ignores this and returns for the next input
		{
			return n;
		}
		else
		{
			n->l = createBstTree(num, n->l, s);               //if the number being inserted is less than the current number assign this new number to the left pointer 
			n->l->p = n;
			s++;
		}
		return n;
	}

	void printTree(node* n, ofstream& file)                   //function to print out the tree level by level
	{
		if (n == NULL)                                        //if the tree is empty will return with message
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

	int treeHeight(node* n)                                   //function to gather tree height
	{
		if (n == NULL)                                        //if empty return 0
		{
			return 0;
		}
		else                                                  //if not empty, find the hieght of the left and right subtree and return the higher value
		{
			int rheight = treeHeight(n->r);
			int lheight = treeHeight(n->l);

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

	void sortInputFile(string s, node* n, ofstream& file, int& j)
	{
		string tempLine = s.substr(2, s.length());

		stringstream num(tempLine);                                   //turning the string into an int
		int x = 0;
		num >> x;

		switch (s[0])
		{
		case 's':
		case 'S':                                                     //sedns to search function
			cout << "Search: " << x;
			file << "Search: " << x;
			searchTree(x, n, file, j);
			j++;
			break;
		case 'd':
		case 'D':                                                     //sends to delete function
			cout << "Delete: " << x << endl;
			file << "Delete: " << x << endl;
			removeNode(x, n, j);
			j++;
			break;
		case 'i':
		case 'I':                                                     //sends to insert function
			createBstTree(x, n, j);
			cout << "Insert: " << x << endl;
			file << "Insert: " << x << endl;
			j++;
			break;
		}
	}

	node* removeNode(int num, node* n, int& j)                              //fucntion to remove a node from a tree
	{
		node* tmp;                                                  //temp node to hold the value of a node when swapping for a another node
		 
		if (n == NULL)                                              //if tree is empty return back
		{
			return 0;
		}
		if (num < n->post)                                          //if the number being removed is less than the current node move to the left pointer
		{
			n->l = removeNode(num, n->l, j);
			j++;
		}
		else if (num > n->post)                                     //if the number being removed is greater than the current node move to the right pointer
		{
			n->r = removeNode(num, n->r, j);
			j++;
		}
		else                                                        //if the number being removed is found
		{
			if (n->l == NULL)                                       //if the node being removed does not have a left child
			{
				tmp = n->r;
				free(n);
				j++;
				return tmp;
			}
			else if (n->r == NULL)                                 //if the node being removed does not have a right child
			{
				tmp = n->l;
				free(n);
				j++;
				return tmp;
			}
			else                                                   //if the node being removed has 2 childern
			{
				tmp = minNode(n->r);                               //find the minumum node on from the right subtree
				n->post = tmp->post; 
				n->r = removeNode(n->post, n->r, j);
				j++;
			}
		}
		return n;
	}
	 
	node* searchTree(int num, node* n, ofstream& file, int& j)                            //searchs the tree for a value
	{
		if (n == NULL)                                            //if no value is found prints this out and returns
		{
			cout << " - Did not find \n";
			file << " - Did not find \n";
			j++;
			return 0;
		}
		else if (num < n->post)                                  //if the number being searched is less than the current node move to the left pointer node
		{
			return searchTree(num, n->l, file, j);
			j++;
		}
		else if (num > n->post)                                  //if the number being searched is greather than the current node move to the right pointer node
		{
			return searchTree(num, n->r, file, j);
			j++;
		}
		else if (num == n->post)                                 //if the number being searchd is found, prints this out
		{
			cout << " - found at level " << nodeLevel(num) << endl;
			file << " - found at level " << nodeLevel(num) << endl;
			return n;
		}
		return n;
	}

	int nodeLevel(node* n, int num, int lev)                     //function to return a given node's level
	{
		if (n == NULL)                                           //if tree is empty return back
		{
			return 0;
		}

		if (n->post == num)                                      //if node is found, return the level
		{
			return lev;
		}
		if ((n->r == NULL) && (n->l == NULL))                 //if not found return back
		{
			return 0;
		}
		else                                                        //keep searching left and right until the end of the tree
		{
			return nodeLevel(n->r, num, lev + 1) | nodeLevel(n->l, num, lev + 1);
		}

	}

	node* minNode(node* n)                                       //function to find the minium node
	{
		if (n == NULL)                                           //if tree is empty return back
		{
			return 0;
		}
		else if (n->l == NULL)                                   //if the left value is empty then the current node is the smallest node and will return this
		{
			return n;
		}
		else                                                        //will recursivsly keep going left until it find the smallest node
		{
			return minNode(n->l);
		}
	}

	int maxInt(int a, int b)
	{
		return (a > b) ? a : b;
	}

	node* insertAvlNode(int num, node* n, ofstream& file, int& counts)
	{
		if (n == NULL)
		{
			n = new node;
			n->post = num;
			n->l = NULL;
			n->r = NULL;
			n->p = NULL;
			n->h = NULL;
			counts++;
		}
		else if (n->post < num)                            //if the number being inserted is greater than the current number assign this new number to the right pointer
		{
			counts++;
			n->r = insertAvlNode(num, n->r, file, counts);
			n = avlBalance(n, file, counts);
			n->r->p = n;
			
		}
		else if (n->post == num)                           //if the number eneterd is the same as a current number, it ignores this and returns for the next input
		{
			return n;
		}
		else
		{
			counts++;
			n->l = insertAvlNode(num, n->l, file, counts);               //if the number being inserted is less than the current number assign this new number to the left pointer 
			n = avlBalance(n, file, counts);
			n->l->p = n;
		}
		return n;
	}

	node* avlBalance(node* n, ofstream & file, int& counts)
	{
		int bal = nodeBalance(n);

		if (bal > 1)
		{
			if (nodeBalance(n->l) > 0)
			{
				cout << "\n**Rotate Left-Left**\n";
				file << "\n**Rotate Left-Left**\n";
				counts++;
				n = rotateLeft(n);
			}
			else
			{
				cout << "\n**Rotate Left-Right**\n";
				file << "\n**Rotate Left-Right**\n";
				counts++;
				return doubelRotateLeft(n);
			}
		}
		else if (bal < -1)
		{
			if (nodeBalance(n->r) > 0)
			{
				cout << "\n**Rotate right-left**\n";
				file << "\n**Rotate right-left**\n";
				counts++;
				return doubleRotateRight(n);
			}
			else
			{
				cout << "\n**Rotate Right-Right**\n";
			    file << "\n**Rotate Right-Right**\n";
				counts++;
				return rotateRight(n);
			}
		}
		return n;
	}

	node* rotateRight(node* n)
	{
		node* tmp;

		tmp = n->r;
		n->r = tmp->l;
		tmp->l = n;

		return tmp;
	}

	node* rotateLeft(node* n)
	{
		node* tmp;

		tmp = n->l;
		n->l = tmp->r;
		tmp->r = n;

		return tmp;
	}

	node* doubleRotateRight(node* n)
	{
		node* tmp;

		tmp = n->r;
		n->r = rotateLeft(tmp);

		return rotateRight(n);
	}

	node* doubelRotateLeft(node* n)
	{
		node* tmp;

		tmp = n->l;
		n->l = rotateRight(tmp);

		return rotateLeft(n);
	}

	int nodeBalance(node* n)
	{
		if (n == NULL)
		{
			return 0;
		}
		return treeHeight(n->l) - treeHeight(n->r);
	}

	node* removeAvlNode(int num, node* n, ofstream& file, int& counts)                              //fucntion to remove a node from a tree
	{
		node* tmp;                                                  //temp node to hold the value of a node when swapping for a another node

		if (n == NULL)                                              //if tree is empty return back
		{
			return 0;
		}
		if (num < n->post)                                          //if the number being removed is less than the current node move to the left pointer
		{
			n->l = removeAvlNode(num, n->l, file, counts);
			counts++;
		}
		else if (num > n->post)                                     //if the number being removed is greater than the current node move to the right pointer
		{
			n->r = removeAvlNode(num, n->r, file, counts);
			counts++;
		}
		else                                                        //if the number being removed is found
		{
			if (n->l == NULL)                                       //if the node being removed does not have a left child
			{
				tmp = n->r;
				free(n);
				counts++;
				return tmp;
			}
			else if (n->r == NULL)                                 //if the node being removed does not have a right child
			{
				tmp = n->l;
				free(n);
				counts++;
				return tmp;
			}
			else                                                   //if the node being removed has 2 childern
			{
				tmp = minNode(n->r);                               //find the minumum node on from the right subtree
				n->post = tmp->post;
				n->r = removeNode(n->post, n->r, counts);
				avlBalance(n, file, counts);
				counts++;
			}
		}
		return n;
	}

	void sortAvlInputFile(string s, node* n, ofstream& file, int& counts)
	{
		string tempLine = s.substr(2, s.length());

		stringstream num(tempLine);                                   //turning the string into an int
		int x = 0;
		num >> x;

		switch (s[0])
		{
		case 's':
		case 'S':                                                     //sedns to search function
			cout << "Search: " << x;
			file << "Search: " << x;
			searchTree(x, n, file, counts);
			break;
		case 'd':
		case 'D':                                                     //sends to delete function
			cout << "Delete: " << x << endl;
			file << "Delete: " << x << endl;
			removeAvlNode(x, n, file, counts);
			break;
		case 'i':
		case 'I':                                                     //sends to insert function
			cout << "Insert: " << x << endl;
			file << "Insert: " << x << endl;
			insertAvlNode(x, file, counts);
			break;
		}
	}

	node* insertSplayNode(int num, node* n, ofstream& file, string &s, int& counts)
	{
		{
			if (n == NULL)                                    //if no node exists, it will create one.
			{
				n = new node;
				n->post = num;
				n->l = NULL;
				n->r = NULL;
				n->p = NULL;
				n->h = NULL;
				counts++;
			}
			else if (n->post < num)                            //if the number being inserted is greater than the current number assign this new number to the right pointer
			{
				counts++;
				n->r = insertSplayNode(num, n->r, file, s, counts);
				n = splayBalance(n, num, file, s, counts);
				
			}
			else if (n->post == num)                           //if the number eneterd is the same as a current number, it ignores this and returns for the next input
			{
				return n;
			}
			else
			{
				counts++;
				n->l = insertSplayNode(num, n->l, file, s, counts);      //if the number being inserted is less than the current number assign this new number to the left pointer 
				n = splayBalance(n, num, file, s, counts);
			}
			return n;
		}
	}

	node* splayBalance(node* n, int num, ofstream& file, string &s, int& counts)
	{
		node check;                                          //new node that will act as a placeholder for new root values
		check.r = NULL;
		check.l = NULL;
		node* lcheck = &check;
		node* rcheck = &check;

		if (n == NULL)                                         //if node is empty, this will return the node.
		{
			return n;
		}
		 
		while (true)                                           //loop for splaying
		{
			if (n->post > num)                                 //if the node is greater than the number (checking left sub tree)
			{
				if (n->l == NULL)                              //if left node is empty, then current node will be root
				{
					break;
				}
				if (n->l->post > num)                          //if left node is less than number 
				{
					s += "l";
					n = rotateLeft(n);                         //rotate the current node 
					if (n->l == NULL)                          //if the new left node is empty break out of the loop
					{
						break;
					}
				}
				s += "l";
				rcheck->l = n;                                 //assigning the current node to be the left node and assigning
				rcheck = rcheck->l;                            //rcheck to be the old node. Will continue until num node is root
				n = n->l;
				rcheck->l = NULL;
			}
			else if(n->post < num)                             //if the current node is less than the number (checking right sub tree)
			{
				if (n->r == NULL)                              //if the node is empty, current node will be new root
				{
					break;
				}
				if (n->r->post < num)                          //if number is greater than the right node then rotate
				{
					s += "r";
					n = rotateRight(n);                        //rotate right
					if (n->r == NULL)                          //if the new right node is empty break out, otherwise continue
					{
						break;     
					}
				}
				s += "r";
				lcheck->r = n;                                 //assigning the current node to be the right node and assining
				lcheck = lcheck->r;                            //lcheck as the old node, will continue until num node is root
				n = n->r; 
				lcheck->r = NULL;
			}
			else                                           
			{
				break;                                         //if the current node and number are equal this will break the loop
			}
			counts++;
		}
		lcheck->r = n->l;                                      //assigning the subtrees onto the new root
		rcheck->l = n->r;
		n->l = check.r;
		n->r = check.l;
		counts++;
		return n;
	}

	void sortSplayInputFile(string s, node* n, ofstream& file, string& so, int& counts)
	{
		string tempLine = s.substr(2, s.length());

		stringstream num(tempLine);                                   //turning the string into an int
		int x = 0;
		num >> x;

		switch (s[0])
		{
		case 's':
		case 'S':                                                     //sedns to search function
			cout << "Search: " << x;
			file << "Search: " << x;
			searchSplayTree(x, file, so, counts);
			counts++;
			break;
		case 'd':
		case 'D':                                                     //sends to delete function
			cout << "Delete: " << x << endl;
			file << "Delete: " << x << endl;
			removeSplayNode(x, file, so, counts);
			counts++;
			break;
		case 'i':
		case 'I':                                                     //sends to insert function
			cout << "Insert: " << x << endl;
			file << "Insert: " << x << endl;
			insertSplayNode(x, file, so, counts);
			counts++;
			break;
		}
	}

	node* searchSplayTree(int num, node* n, ofstream& file, string& s, int& counts)
	{
		if (n == NULL)                                            //if no value is found prints this out and returns
		{
			cout << " Tree is empty \n";
			file << " Tree is empty \n";
			return 0;
		}
		else if (num < n->post)                                  //if the number being searched is less than the current node move to the left pointer node
		{
			if (n->l == NULL)
			{
				counts++;
				splayBalance(num, file, s, counts);
				return n;
			}
			counts++;
			return searchSplayTree(num, n->l, file, s, counts);
		}
		else if (num > n->post)                                  //if the number being searched is greather than the current node move to the right pointer node
		{
			if (n->r == NULL)
			{
				counts++;
				splayBalance(num, file, s, counts);
				return n;
			}
			counts++;
			return searchSplayTree(num, n->r, file, s, counts);
		}
		else if (num == n->post)                                 //if the number being searchd is found, prints this out
		{
			counts++;
			cout << " - found at level " << nodeLevel(num) << endl;
			file << " - found at level " << nodeLevel(num) << endl;
			splayBalance(num, file, s, counts);
			return n;
		}
		return n;
	}

	node* removeSplayNode(int num, node* n, ofstream& file, string& s, int & counts)
	{
		node* tmp;                        //using a temp node struct to hold the value of the current node

		if (n == NULL)                    //if the node is empty
		{
			return n;
		}
		counts++;
		n = splayBalance(n, num, file, s, counts);   //splay the node to the top before rmoving then assign the new root

		if (n->l == NULL)                 //if the left node is empty use the right node as the new root
		{
			tmp = n;
			n = n->r;
			counts++;
		}
		else                              //if the left node is not empty use this node as the new root
		{
			counts++;
			tmp = n;
			n = splayBalance(n->l, num, file, s, counts);
			n->r = tmp->r;
		}

		return n;
	}


public:
	BstTree()                                                      //constructor to make an empty tree
	{
		tree = NULL;
	}

	void createBstTree(int num, int& s)                                    //fucntion to make a tree 
	{
		tree = createBstTree(num, tree, s);
	}

	void printTree(ofstream& file)                                 //function to print a tree
	{
		printTree(tree, file);
	}

	int treeHeight()                                               //function to gather the tree's height
	{
		return treeHeight(tree);
	}

	void sortInputFile(string s, ofstream& file, int& j)                  //function to sort the second input file for which action it will need to preform
	{
		sortInputFile(s, tree, file, j);

	}

	void sortAvlInputFile(string s, ofstream& file, int& counts)                  //function to sort the second input file for which action it will need to preform
	{
		sortAvlInputFile(s, tree, file, counts);
	}

	void sortSplayInputFile(string s, ofstream& file, string& so, int& counts)
	{
		sortSplayInputFile(s, tree, file, so, counts);
	}

	void removeNode(int num, int & j)                                     //function to delete a node from a  tree
	{
		removeNode(num, tree, j);
	}

	void searchTree(int num, ofstream& file, int& j)                     //fucntion to search a tree for a node
	{
		searchTree(num, tree, file, j);
	}

	void removeSplayNode(int num, ofstream& file, string& s, int& counts)
	{
		tree = removeSplayNode(num, tree, file, s, counts);
	}

	void searchSplayTree(int num, ofstream& file, string& s, int& counts)
	{
		tree = searchSplayTree(num, tree, file, s, counts);
	}

	int nodeLevel(int num)                                       //fucntion to return a node's level
	{
		return nodeLevel(tree, num, 1);
		
	}
	void avlBalance(ofstream& file, int& counts)
	{
		tree = avlBalance(tree, file, counts);
	}

	void splayBalance(int num, ofstream& file, string &s, int& counts)
	{
		tree = splayBalance(tree, num, file, s, counts);
	}

	void insertAvlNode(int num, ofstream& file, int& counts)
	{
		tree = insertAvlNode(num, tree, file, counts);
	}

	void insertSplayNode(int num, ofstream& file, string& s, int& counts)
	{
		tree = insertSplayNode(num, tree, file, s, counts);
	}
	
};


