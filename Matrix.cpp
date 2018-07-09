#include "Matrix.h"

Matrix::Matrix(string fileName)
{
	ifstream dataFile;
	dataFile.open(fileName, ifstream::in);

	if (dataFile.is_open())
	{
		vector < string > Row;
		string line;
		string item;
		while (!dataFile.eof())
		{
			getline(dataFile, line);

			istringstream iss(line);

			while (iss >> item)
			{
				if (item.length())
				{
					Row.push_back(item);
				}
			}

			if (line.length())
			{
				matrix.push_back(Row);
				Row.erase(Row.begin(), Row.end());
			}
		}
		dataFile.close();
	}
	else
	{
		Console::displayError("Nie uda³o siê otworzyæ pliku :<\n");
		Console::displayError("Utworzono pust¹ macierz...\n");
	}

}

Matrix::Matrix(vector<vector<string>> tempMatrix)
{
	for (int i = 0; i < tempMatrix.size(); i++)
	{
		matrix.push_back(tempMatrix[i]);
	}
}

void Matrix::display()
{
	for (int i = 0; i <sizeY(); i++)
	{
		for (int j = 0; j < sizeX(); j++)
		{
			Console::out((" " + matrix[i][j]).c_str());
		}
		Console::newLine();
	}
}