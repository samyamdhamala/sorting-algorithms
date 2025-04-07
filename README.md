# 📊 Sorting Algorithms: Empirical Performance Analysis

This project evaluates the time efficiency of six classic sorting algorithms using C++. It includes custom dataset generation, benchmarking, and comparative analysis across various input types (unsorted, sorted, and reverse-sorted). The analysis is based on real-time measurements and theoretical complexity.

## 📁 Project Structure

///sorting-algorithms/ ├── dataset-generator/ │ ├── data_generator.cpp │ └── datasets/ ├── sorting-program/ │ ├── main.cpp │ ├── sorting_algorithms.cpp │ ├── sorting_algorithms.hpp │ └── datasets/ └── README.md///

## ⚙️ Implemented Algorithms

- Bubble Sort
- Selection Sort
- Insertion Sort
- Merge Sort
- Quick Sort
- Shell Sort

Each algorithm was tested on datasets of:
- 25,000 to 500,000 elements
- Random, sorted, and reverse-sorted order

## 🧪 Dataset Generation

- Uses `mt19937` for generating unique integers between 0–4,000,000.
- Files include:
  - `dataset_25000.txt`
  - `sorted_dataset_25000.txt`
  - `sorted_desc_dataset_25000.txt`

## 📈 Sample Runtime (Unsorted Data)

| Dataset Size | Bubble Sort | Merge Sort | Quick Sort |
|--------------|-------------|------------|------------|
| 25,000       | 8,349 ms    | 35 ms      | 11 ms      |
| 120,000      | 195,879 ms  | 181 ms     | 58 ms      |
| 500,000      | 3.49M ms    | 786 ms     | 287 ms     |


## 🏁 How to Run

### Dataset Generator
```bash
cd dataset-generator
g++ data_generator.cpp -o generator
./generator

cd sorting-program
g++ main.cpp sorting_algorithms.cpp -o sorter
./sorter

## 🔧 Technologies Used

- C++
- STL (Vectors, I/O)
- `<chrono>` for benchmarking
- `<random>` for dataset generation

## 📚 Academic Context

📘 **Course**: CSCI-6620: Data Structures and Algorithms  
👨‍🏫 **Instructor**: Dr. Adrian Rusu  
👨‍💻 **Author**: Samyam Dhamala

## 📜 License

This project is licensed under the [MIT License](LICENSE).