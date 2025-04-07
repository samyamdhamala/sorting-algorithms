/****************************************************************************************
* @file dataset_generator.cpp
*
* @description
* This program generates unique random datasets of specified sizes and saves them
* as text files. The numbers are generated using a uniform distribution and stored
* in an unordered set to ensure uniqueness.
*
* Additionally, the program includes commented-out functionality to:
* - Sort the datasets in ascending order before saving.
* - Sort the datasets in descending order before saving.
*
* @author: samyam.dhamala
******************************************************************************************/

#include <iostream>
#include <fstream>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <random>

using namespace std;

/**
 * @brief Generates a dataset with unique random numbers and saves it to a file.
 * @param size The number of unique numbers to generate.
 * @param filename The name of the output file.
 */
void generateUniqueDataset(int size, const string& filename) {
    unordered_set<int> uniqueNumbers;
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> dist(0, 4000000);

    while (uniqueNumbers.size() < size) {
        uniqueNumbers.insert(dist(gen));
    }

    vector<int> dataset(uniqueNumbers.begin(), uniqueNumbers.end());

    // Uncomment one of the sorting methods if needed

    // Sort in ascending order
    // sort(dataset.begin(), dataset.end());

    // Sort in descending order
    // sort(dataset.rbegin(), dataset.rend());

    ofstream file(filename);
    for (int num : dataset) {
        file << num << "\n";
    }

    cout << "Dataset " << filename << " created with " << size << " unique numbers.\n";
}

int main() {
    generateUniqueDataset(25000, "datasets/dataset_25000.txt");
    generateUniqueDataset(75000, "datasets/dataset_75000.txt");
    generateUniqueDataset(120000, "datasets/dataset_120000.txt");
    generateUniqueDataset(350000, "datasets/dataset_350000.txt");
    generateUniqueDataset(500000, "datasets/dataset_500000.txt");

    return 0;
}
