#include "ID3.h"

int ID3::getAttributeIndex(Matrix matrix, string attribute)
{
	int index;

	for (int i = 0; i < matrix.sizeX(); i++)
	{
		if (matrix.getElement(0, i) == attribute)
		{
			index = i;
			break;
		}
	}
	return index;
}

vector<string> ID3::getAttributes(Matrix matrix)
{
	vector<string> attribute;
	for (int i = 0; i < matrix.sizeX() - 1; i++)//pobiera liste atrybutów
	{
		attribute.push_back(matrix.getElement(0, i));
	}
	return attribute;
}

vector<string> ID3::getAttributeValues(Matrix matrix, string attribute)
{
	return getAttributesValues(matrix)[attribute]; //pobiera możliwości dla podanego atrybutu
}

map<string, vector<string>> ID3::getAttributesValues(Matrix matrix)
{
	map<string, vector<string>> attributesValues;
	vector < string > attributeValues;

	for (int i = 0; i < matrix.sizeX(); i++)
	{
		for (int j = 0; j < matrix.sizeY(); j++)
		{
			attributeValues.push_back(matrix.getElement(j,i));//pobiera wszystkie wartości dla danego atrybutu
		}
		sort(attributeValues.begin(), attributeValues.end());
		attributeValues.erase(unique(attributeValues.begin(), attributeValues.end()), attributeValues.end());//Usuwa powtórzenia
		attributesValues[matrix.getElement(0, i)] = attributeValues;
		attributeValues.erase(attributeValues.begin(), attributeValues.end());
	}
	return attributesValues;
}

map<string, vector<string>> ID3::getAttributeValuesScores(Matrix matrix, string attribute)
{
	int index = getAttributeIndex(matrix, attribute);
	map<string, vector<string>> attributeValuesScores;
	vector<string> attributeValues = getAttributesValues(matrix)[attribute];

	//tworzy listę rezultatów dla wartości atrybutów
	for (int i = 0; i < attributeValues.size(); i++)
	{
		vector<string> row;
		for (int j = 0; j < matrix.sizeY(); j++)
		{
			if (matrix.getElement(j, index) == attributeValues[i])
			{
				row.push_back(matrix.getElement(j, matrix.sizeX() - 1));
			}
		}
		attributeValuesScores[attributeValues[i]] = row;
	}
	return attributeValuesScores;
}

//Zwraca listę wszystkich rezultatów
vector<string> ID3::getScores(Matrix matrix)
{
	vector<string> scores;

	for (int i = 0; i < matrix.sizeY(); i++)
	{
		string item = matrix.getElement(i, matrix.sizeX() - 1);
		scores.push_back(item);
	}
	return scores;
}

//Zwraca listę możliwych rezultatów
vector<string> ID3::getUniqueScores(vector<string> scores)
{
	sort(scores.begin(), scores.end());
	scores.erase(unique(scores.begin(), scores.end()), scores.end());
	return scores;
}

//Zwraca rezultat który wystąpił większą ilość razy
string ID3::getFrequentScore(vector<string> scores)
{
	vector<string> uniqueScores = getUniqueScores(scores);
	vector<int> count(uniqueScores.size(), 0);

	for (int i = 0; i < scores.size(); i++)
	{
		for (int j = 0; j < uniqueScores.size(); j++)
		{
			if (scores[i] == uniqueScores[j])
			{
				count[j]++;
			}
		}
	}

	int maxIndex = 0;

	for (int i = 0; i < uniqueScores.size(); i++)
	{
		if (count[i] > count[maxIndex])
		{
			maxIndex = i;
		}
	}

	return uniqueScores[maxIndex];
}

double ID3::computeEntropy(vector<string> scores)
{
	vector<string> scoreRange = getUniqueScores(scores);

	if (scoreRange.size() == 0)
	{
		return 0;
	}
	else
	{
		vector<int> count(scoreRange.size(), 0);

		//Zlicza ilość wystąpienia danego rezultatu
		for (int i = 0; i < scores.size(); i++)
		{
			for (int j = 0; j < scoreRange.size(); j++)
			{
				if (scores[i] == scoreRange[j])
				{
					count[j]++;
				}
			}
		}

		double entropy = 0, tempEntropy;

		for (int i = 0; i < scoreRange.size(); i++)
		{
			if (count[i] == 0)
			{
				tempEntropy = 0;
			}
			else {
				tempEntropy = -((double)count[i] / (double)(scores.size())) * log(((double)count[i] / (double)(scores.size()))) / log(2);
			}
			entropy += tempEntropy;
		}

		return entropy;
	}
}

double ID3::computeGain(Matrix matrix, string attribute) {
	vector<string> scores = getScores(matrix);
	map<string, vector<string>> valuesScores = getAttributeValuesScores(matrix, attribute);
	vector < string > attributeValues = getAttributeValues(matrix, attribute);
	vector < string > tempScores;

	double entropy = 0, originalEntropy, tempEntropy;

	originalEntropy = computeEntropy(scores);//Entropy(S)

	for (int i = 0; i < attributeValues.size(); i++)//zlicza zysk informacyjny wszytkich wartosci atrybutu
	{
		tempScores = valuesScores[attributeValues[i]];
		tempEntropy = computeEntropy(tempScores)*(double)tempScores.size() / (double)scores.size();//spodziewana wartoscia entropii po podziale S przy pomocy atrybutu A
		entropy +=  tempEntropy;
	}
	return originalEntropy - entropy; //Gain(S, A)
}

Tree * ID3::buildTree(Tree * tree, Matrix matrix)
{
	if (matrix.isEmpty())
	{
		Console::displayError("Macierz jest pusta!\n");
		return nullptr;
	}

	vector<string> scores = getScores(matrix);
	vector < string > uniqueScores = getUniqueScores(scores);

	if (uniqueScores.size() == 1)
	{
		tree->Node = uniqueScores[0];
		return tree;
	}
	else if (matrix.sizeX() == 3)
	{
		string frequentScore = getFrequentScore(scores);
		tree->Node = frequentScore;
		return tree;
	}

	double maxGain = NULL, tempGain;
	string maxAttribute;

	vector<string> attributes = getAttributes(matrix);

	for (int i = 1; i < attributes.size(); i++)//Zaczynamy od jedynki żeby pominąć atrybut dzień, który nic nie wnosi
	{
		tempGain = computeGain(matrix, attributes[i]);
		if (maxGain == NULL || tempGain > maxGain)//Wybiera atrybut z największym zyskiem
		{
			maxGain = tempGain;
			maxAttribute = attributes[i];
		}
	}

	vector<string> values = getAttributeValues(matrix, maxAttribute);

	for (int i = 0; i < values.size(); i++)
	{
		Matrix newMatrix = getDecisionSubsystem(matrix, maxAttribute, values[i]); 

		Tree * newTree = new Tree();
		newTree->Branch = values[i];

		buildTree(newTree, newMatrix);

		tree->Child.push_back(newTree);
	}

	return tree;
}

Matrix ID3::getDecisionSubsystem(Matrix matrix, string attribute, string value)
{
	vector<vector<string>> temp;
	int index = getAttributeIndex(matrix, attribute);

	for (int i = 0; i < matrix.sizeY(); i++)//Tworzy podsystem decyzyjny
	{
		vector<string> row;

		for (int j = 0; j < matrix.sizeX(); j++)
		{
			if ((matrix.getElement(0, j) != attribute) && (matrix.getElement(i, index) == value))
			{
				row.push_back(matrix.getElement(i, j));
			}
		}
		if (row.size() != 0)
		{
			temp.push_back(row);
		}
	}

	return Matrix(temp);
}