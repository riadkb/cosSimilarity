#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <sstream>
#include <cmath>

using namespace std;

// Function to tokenize a string into words and numbers
vector<string> tokenize(const string& text) {
    vector<string> tokens;
    string token;
    istringstream iss(text);

    while (iss >> token) {
        tokens.push_back(token);
    }

    return tokens;
}

// Function to calculate the cosine similarity between two documents
double cosineSimilarity(const map<string, int>& tf1, const map<string, int>& tf2) {
    double dotProduct = 0.0;
    double magnitude1 = 0.0;
    double magnitude2 = 0.0;

    for (const auto& term : tf1) {
        if (tf2.count(term.first)) {
            dotProduct += term.second * tf2.at(term.first);
        }
        magnitude1 += term.second * term.second;
    }

    for (const auto& term : tf2) {
        magnitude2 += term.second * term.second;
    }

    magnitude1 = sqrt(magnitude1);
    magnitude2 = sqrt(magnitude2);

    if (magnitude1 == 0 || magnitude2 == 0) {
        return 0.0;  // To avoid division by zero
    }

    return dotProduct / (magnitude1 * magnitude2);
}

int main() {
    string file1, file2;

    cout << "Enter the path to the first text file: ";
    cin >> file1;

    cout << "Enter the path to the second text file: ";
    cin >> file2;

    ifstream input1(file1);
    ifstream input2(file2);

    if (!input1.is_open() || !input2.is_open()) {
        cout << "Failed to open one or both files." << endl;
        return 1;
    }

    string text1((istreambuf_iterator<char>(input1)), (istreambuf_iterator<char>()));
    string text2((istreambuf_iterator<char>(input2)), (istreambuf_iterator<char>()));

    vector<string> tokens1 = tokenize(text1);
    vector<string> tokens2 = tokenize(text2);

    map<string, int> tf1, tf2;

    for (const string& token : tokens1) {
        tf1[token]++;
    }

    for (const string& token : tokens2) {
        tf2[token]++;
    }

    double similarity = cosineSimilarity(tf1, tf2);

    cout << "Cosine Similarity = " << similarity*100 << ' '<<'%' << endl;

    return 0;
}
