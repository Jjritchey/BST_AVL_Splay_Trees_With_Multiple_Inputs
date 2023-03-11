#pragma once
#include <vector>
#include <iostream>
#include <stack>
#include <queue>
#include <fstream>
#include <cmath>

using namespace std;

class node
{
public:                           //nodes to be used to make a tree
	int post;
	node* l;
	node* r;
	node* p;
};

