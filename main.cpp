#include "ID3.h"
#include "Console.h"

int main()
{
	Matrix macierz("SystemDecyzyjny.txt");
	Tree * drzewo = new Tree();

	ID3::buildTree(drzewo, macierz);

	Console::out("Drzewo:\n");
	Tree::PrintTree(drzewo);

	delete drzewo;
	Console::newLine();
	Console::newLine();

	Console::pause();
    return 0;
}

