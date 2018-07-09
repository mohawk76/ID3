#ifndef ID3_H
#define ID3_H

#include <vector>
#include <string>
#include <map>
#include <cmath>
#include <algorithm>

#include "Matrix.h"
#include "Tree.h"

using namespace std;

namespace ID3 {
		vector<string> getAttributes(Matrix);
		map<string, vector<string>> getAttributesValues(Matrix);
		vector<string> getAttributeValues(Matrix, string);
		map<string, vector<string>> getAttributeValuesScores(Matrix, string);
		int getAttributeIndex(Matrix, string);

		vector <string> getScores(Matrix);
		vector <string> getUniqueScores(vector<string>);
		string getFrequentScore(vector<string>);

		double computeEntropy(vector<string>);
		double computeGain(Matrix, string);

		Matrix getDecisionSubsystem(Matrix, string, string);

		Tree * buildTree(Tree *, Matrix);
}

#endif