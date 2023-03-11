#include <vector>
#include <iostream>
#include <stack>
#include <queue>
#include <fstream>
#include <cmath>
#include <string>

#include "Node.h"


node * node::createBstTree(int num, node * n)
{
		if (n==NULL)
		{
			n = new node;
			n->post = post;
			n->l = NULL;
			n->r = NULL;
			n->p = NULL;
		}
		else if (n->post < post)
		{
			n->r = createBstTree(num, n->r);
			n->r->p = n;
		}
		else
		{
			n->l = createBstTree(num, n->l);
			n->l->p = n;
		}
	return n;
}
