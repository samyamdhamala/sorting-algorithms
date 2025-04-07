/****************************************************************************************
* @file main.cpp
*
* @description
* This program benchmarks the performance of six different sorting algorithms
* (Bubble Sort, Selection Sort, Insertion Sort, Merge Sort, Quick Sort, and Shell Sort)
* using large datasets. The user can select a sorting algorithm and a dataset, and the
* program measures the execution time of the chosen algorithm on the selected dataset.
*
* The datasets include:
* - Randomly generated unsorted numbers
* - Sorted datasets (ascending order)
* - Reverse sorted datasets (descending order)
*
* The program provides a menu-driven interface for user interaction, loads the dataset
* from a file, runs the selected sorting algorithm, and displays the execution time
* in milliseconds.
*
* @author: samyam.dhamala
******************************************************************************************/

#include "sorting_algorithms.hpp"
#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;

// Enum for algorithm selection
enum class Algorithm {
    BUBBLE_SORT,
    SELECTION_SORT,
    INSERTION_SORT,
    MERGE_SORT,
    QUICKSORT,
    SHELLSORT,
    INVALID
};

// Enum for dataset type selection
enum class DatasetType {
    RANDOM,
    PRE_SORTED,
    REVERSE_SORTED,
    INVALID
};

// Define dataset options for each type
const vector<string> RANDOM_DATASETS = {
    "dataset_25000.txt",
    "dataset_75000.txt",
    "dataset_120000.txt",
    "dataset_350000.txt",
    "dataset_500000.txt",
};

const vector<string> PRE_SORTED_DATASETS = {
    "sorted_dataset_25000.txt",
    "sorted_dataset_75000.txt",
    "sorted_dataset_120000.txt",
    "sorted_dataset_350000.txt",
    "sorted_dataset_500000.txt",
};

const vector<string> REVERSE_SORTED_DATASETS = {
    "sorted_desc_dataset_25000.txt",
    "sorted_desc_dataset_75000.txt",
    "sorted_desc_dataset_120000.txt",
    "sorted_desc_dataset_350000.txt",
    "sorted_desc_dataset_500000.txt",
};

// Load dataset from file
vector<int> loadDataset(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: Could not open file " << filename << "\n";
        exit(1);
    }

    vector<int> data;
    int num;
    while (file >> num) {
        data.push_back(num);
    }
    return data;
}

// Benchmark a sorting algorithm
void benchmark(void (*sortFunction)(vector<int>&), const string& name, const vector<int>& data, const string& datasetName) {
    vector<int> dataset = data; // Copy the dataset to avoid modifying the original

    // Display "Please be patient" message
    cout << "\n----------------------------------------\n";
    cout << "   Sorting in progress. Please be patient...\n";
    cout << "----------------------------------------\n";

    auto start = chrono::high_resolution_clock::now();
    sortFunction(dataset); // Run the sorting algorithm
    auto end = chrono::high_resolution_clock::now();

    // Clear the "Please be patient" message
    cout << "\r"; // Move cursor to the beginning of the line
    cout << "                                          \r"; // Clear the line

    // Display the benchmark results
    cout << "\n----------------------------------------\n";
    cout << name << " for " << datasetName << " took "
         << chrono::duration<double, milli>(end - start).count()
         << " ms\n";
    cout << "----------------------------------------\n\n";
}

// Display menu and get user's choice for algorithm
Algorithm getAlgorithmChoice() {
    cout << "\n========================================\n";
    cout << "          SELECT A SORTING ALGORITHM\n";
    cout << "========================================\n";
    cout << "1. Bubble Sort\n";
    cout << "2. Selection Sort\n";
    cout << "3. Insertion Sort\n";
    cout << "4. Merge Sort\n";
    cout << "5. Quick Sort\n";
    cout << "6. Shell Sort\n";
    cout << "7. Exit\n";
    cout << "----------------------------------------\n";
    cout << "Enter your choice: ";

    int choice;
    cin >> choice;

    switch (choice) {
        case 1: return Algorithm::BUBBLE_SORT;
        case 2: return Algorithm::SELECTION_SORT;
        case 3: return Algorithm::INSERTION_SORT;
        case 4: return Algorithm::MERGE_SORT;
        case 5: return Algorithm::QUICKSORT;
        case 6: return Algorithm::SHELLSORT;
        case 7: return Algorithm::INVALID; // Exit option
        default: return Algorithm::INVALID;
    }
}

// Function to get dataset type choice from the user
DatasetType getDatasetTypeChoice() {
    cout << "\n========================================\n";
    cout << "           SELECT DATASET TYPE\n";
    cout << "========================================\n";
    cout << "1. Unsorted Datasets\n";
    cout << "2. Pre-Sorted Datasets\n";
    cout << "3. Reverse Sorted Datasets\n";
    cout << "4. Exit\n";
    cout << "----------------------------------------\n";
    cout << "Enter your choice: ";

    int choice;
    cin >> choice;

    switch (choice) {
        case 1: return DatasetType::RANDOM;
        case 2: return DatasetType::PRE_SORTED;
        case 3: return DatasetType::REVERSE_SORTED;
        case 4: return DatasetType::INVALID; // Exit option
        default: return DatasetType::INVALID;
    }
}

// Modify the getDatasetChoice function to filter based on dataset type
string getDatasetChoice(DatasetType type) {
    vector<string> selectedDatasets;

    // Select the appropriate dataset list based on the dataset type
    switch (type) {
        case DatasetType::RANDOM:
            selectedDatasets = RANDOM_DATASETS;
            break;
        case DatasetType::PRE_SORTED:
            selectedDatasets = PRE_SORTED_DATASETS;
            break;
        case DatasetType::REVERSE_SORTED:
            selectedDatasets = REVERSE_SORTED_DATASETS;
            break;
        default:
            return "exit"; // If invalid choice, return exit
    }

    cout << "\n========================================\n";
    cout << "           SELECT A DATASET\n";
    cout << "========================================\n";
    for (size_t i = 0; i < selectedDatasets.size(); i++) {
        cout << (i + 1) << ". " << selectedDatasets[i] << "\n";
    }
    cout << (selectedDatasets.size() + 1) << ". Exit\n";
    cout << "----------------------------------------\n";
    cout << "Enter your choice: ";

    int choice;
    cin >> choice;

    if (choice >= 1 && choice <= selectedDatasets.size()) {
        return selectedDatasets[choice - 1];
    } else {
        return "exit"; // Exit if the user chooses an invalid option or the exit option
    }
}

int main() {
    cout << "\n========================================\n";
    cout << "     SORTING ALGORITHM BENCHMARK TEST\n";
    cout << "========================================\n";

    DatasetType type = DatasetType::INVALID;

    // Ask the user to select the dataset type at the beginning
    while (type == DatasetType::INVALID) {
        type = getDatasetTypeChoice();
        if (type == DatasetType::INVALID) {
            cout << "\nExiting the program. Goodbye!\n";
            cout << "========================================\n";
            return 0; // Exit the program if invalid option
        }
    }

    // Now keep selecting datasets in the chosen dataset type until exit
    while (true) {
        // Get dataset choice based on selected type
        string filename = getDatasetChoice(type);

        if (filename == "exit") {
            cout << "\nExiting the program. Goodbye!\n";
            cout << "========================================\n";
            break; // Exit the program
        }

        // Load dataset
        vector<int> data;
        try {
            data = loadDataset("datasets/" + filename);
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << "\n";
            continue; // Skip to the next iteration if the file cannot be loaded
        }

        // Get algorithm choice from user
        Algorithm choice = getAlgorithmChoice();

        // Exit if the user chooses to
        if (choice == Algorithm::INVALID) {
            cout << "\nExiting the program. Goodbye!\n";
            cout << "========================================\n";
            break;
        }

        // Benchmark the selected algorithm
        switch (choice) {
            case Algorithm::BUBBLE_SORT:
                benchmark(bubbleSort, "Bubble Sort", data, filename);
                break;
            case Algorithm::SELECTION_SORT:
                benchmark(selectionSort, "Selection Sort", data, filename);
                break;
            case Algorithm::INSERTION_SORT:
                benchmark(insertionSort, "Insertion Sort", data, filename);
                break;
            case Algorithm::MERGE_SORT:
                benchmark([](vector<int>& d) { mergeSort(d, 0, d.size() - 1); }, "Merge Sort", data, filename);
                break;
            case Algorithm::QUICKSORT:
                benchmark([](vector<int>& d) { quickSort(d, 0, d.size() - 1); }, "Quick Sort", data, filename);
                break;
            case Algorithm::SHELLSORT:
                benchmark(shellSort, "Shell Sort", data, filename);
                break;
            default:
                cout << "\nInvalid choice. Please try again.\n";
                break;
        }
    }

    return 0;
}
