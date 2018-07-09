#ifndef Matrix_H
#define Matrix_H

#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "Console.h"

using namespace std;

class Matrix
{
	private:
		vector<vector<string>> matrix;
	public:
		Matrix(string);
		Matrix(string**);
		Matrix(vector<vector<string>>);
		Matrix() {};
		~Matrix() {};

		string getElement(int x, int y) { return matrix[x][y]; }
		int sizeX() { return matrix[0].size(); }
		int sizeY() { return matrix.size(); }
		bool isEmpty() { return matrix.size() ? false : true; }
		void clear() { matrix.erase(matrix.begin(), matrix.end()); }

		void display();
};

#endif
