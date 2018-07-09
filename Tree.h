#pragma once
#ifndef TREE_H
#define TREE_H

#include <string>
#include <vector>

#include "Console.h"

using namespace std;

struct Tree
{	
		string Node;
		string Branch;
		vector<Tree*> Child;
		Tree();
		~Tree();
		static void PrintTree(Tree*, int Depth = -1);
		static void memoryFree(Tree*);
};

#endif
