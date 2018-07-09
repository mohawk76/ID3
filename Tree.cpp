#include "Tree.h"

Tree::Tree()
{
	Node = "";
	Branch = "";
}

Tree::~Tree()
{
	if (this->Child.size() > 0)
		memoryFree(this);
}

//Wyœwietla drzewo, zmienna Depth odpowiada za iloœæ tabulacji
void Tree::PrintTree(Tree * tree, int Depth)
{
	for (int i = 0; i < Depth; i++)
		Console::out("\t");

	if (!tree->Branch.empty())
	{
		Console::out(tree->Branch.c_str(), Console::GREEN);
		Console::newLine();

		for (int i = 0; i < Depth + 1; i++)
			if (!tree->Node.empty())
				Console::out("\t");
	}
	
	Console::out(tree->Node.c_str(), Console::GREEN);

	if(!tree->Node.empty())
		Console::newLine();

	for (int i = 0; i < tree->Child.size(); i++)
	{
		PrintTree(tree->Child[i], Depth + 1);
	}
}

//Rekurencyjnie czyœci przydzielon¹ pamiêæ(przynajmniej mam tak¹ nadziejê xD)
void Tree::memoryFree(Tree* tree)
{
	while (tree->Child.size() > 0)
	{
		memoryFree(tree->Child[0]);
		delete tree->Child[0];
		tree->Child.erase(tree->Child.begin());
	}
}