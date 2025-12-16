#include<iostream>
#include<string>
#include<fstream>
#include<vector>
using namespace std;

template <typename T>
void outputVec(const vector<T>& vec) {
	for (int32_t i = 0; i < vec.size(); ++i) {
		cout << vec[i] << endl;
	}
}

bool checkSimilarity(string stroke) {
	if (!stroke.empty()) {
		for (int32_t i = 0; i < stroke.size(); ++i) {
			if (stroke[i] >= 'A' && stroke[i] <= 'Z') {
				stroke[i] = stroke[i] - 'A' + 'a'; 
			}
		}
		char firstSymbol = stroke[0];
		for (int32_t i = 0; i < stroke.size(); ++i) {
			if (stroke[i] != firstSymbol) {
				return false;
			}
		}
		return true;
	}
	else return false;
}

void ensureFileOpen(ifstream& file, const string& filename) {
	if (!file.is_open()) {
		throw runtime_error("Error: cannot open input file " + filename);
	}
	else cout << "Your input file  was succesfully opened" << endl;
}

void ensureFileOpen(ofstream& file, const string& filename) {
	if (!file.is_open()) {
		throw runtime_error("Error: cannot open output file " + filename);
	}
	else cout << "Your output file  was succesfully opened" << endl;
}

int main() {
	try {
		vector<string> strokeVec;
		vector<int32_t> sizeVec;
		vector<int32_t> maxSizePosVec;
		ifstream inpFile("input.txt");
		ensureFileOpen(inpFile, "input.txt");
		string stroke;

		while (getline(inpFile, stroke)) {
			if (!stroke.empty()) {
				strokeVec.push_back(stroke);
			}
		}
		cout << "We read " << strokeVec.size() << " strings from your file" << endl;
		if (strokeVec.empty()) {
			throw "Your string is empty. There is nothing to output.";
		}
		int32_t maxStrokeSize = 0;
		for (int32_t i = 0; i < strokeVec.size(); ++i) {
			if (strokeVec[i].size() > maxStrokeSize) {
				maxStrokeSize = strokeVec[i].size();
			}
		}


		for (int32_t i = 0; i < strokeVec.size(); ++i) {
			sizeVec.push_back(strokeVec[i].size());

		}

		for (int32_t i = 0; i < sizeVec.size(); ++i) {
			if (sizeVec[i] == maxStrokeSize) {
				maxSizePosVec.push_back(i);
			}
		}

		ofstream outFile("output.txt");
		ensureFileOpen(outFile, "output.txt");
		bool wroteSth = false;
		for (int32_t i = 0; i < maxSizePosVec.size(); ++i) {
			if (i < 10) {
				if (checkSimilarity(strokeVec[maxSizePosVec[i]])) {
					outFile << strokeVec[maxSizePosVec[i]] << endl;
					wroteSth = true;
				}
			}
		}
		if (wroteSth == false) {
			throw "There are no suitable strings";
		}
		cout << "We output needed strings in your file" << endl;
	}
	catch (const char* msg) {
		cout << "Exception caught:" << msg << endl;
	}
	
	return 0;
}