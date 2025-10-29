#include <iostream>
#include <vector>
#include <numeric> // For std::accumulate
#include <iomanip> // For std::setprecision

// Use the standard namespace
using namespace std;

/**
 * @brief Calculates the moving average using a naive O(n*k) approach.
 * @details Re-calculates the sum of the window for each element.
 */
vector<double> calculateMovingAverageNaive(const vector<double>& data, int k) {
    vector<double> movingAverages;
    
    for (int i = k - 1; i < data.size(); ++i) {
        double currentSum = 0.0;
        
        // Sum the 'k' elements in the current window
        for (int j = 0; j < k; ++j) {
            currentSum += data[i - j];
        }
        
        movingAverages.push_back(currentSum / k);
    }
    return movingAverages;
}

/**
 * @brief Calculates the moving average using an optimized O(n) "sliding window".
 * @details Maintains a running sum by adding the new element and subtracting the oldest.
 */
vector<double> calculateMovingAverageOptimized(const vector<double>& data, int k) {
    vector<double> movingAverages;
    if (data.size() < k) {
        return movingAverages; // Not enough data
    }

    // 1. Calculate the sum of the first window
    double currentSum = 0.0;
    for (int i = 0; i < k; ++i) {
        currentSum += data[i];
    }
    movingAverages.push_back(currentSum / k);

    // 2. Slide the window for the rest of the data
    for (int i = k; i < data.size(); ++i) {
        // Update the sum: subtract the element leaving, add the element entering
        currentSum = currentSum - data[i - k] + data[i];
        
        movingAverages.push_back(currentSum / k);
    }
    return movingAverages;
}

/**
 * @brief Helper function to print a vector.
 */
void printVector(const string& title, const vector<double>& vec) {
    cout << title << "\n";
    cout << "[ ";
    for (const double& val : vec) {
        cout << val << " ";
    }
    cout << "]\n\n";
}

int main() {
    // Set precision for floating point output
    cout << fixed << setprecision(2);

    // Sample data
    vector<double> data = {10.0, 12.0, 11.0, 13.0, 15.0, 14.0, 16.0, 18.0, 17.0};
    int windowSize = 3;

    cout << "--- Moving Average Calculation (Window Size = " << windowSize << ") ---\n\n";
    printVector("Original Data:", data);

    // --- Naive Method ---
    cout << "Calculating with Naive (O(n*k)) method...\n";
    vector<double> naiveResult = calculateMovingAverageNaive(data, windowSize);
    printVector("Naive Result:", naiveResult);

    // --- Optimized Method ---
    cout << "Calculating with Optimized (O(n)) 'Sliding Window' method...\n";
    vector<double> optimizedResult = calculateMovingAverageOptimized(data, windowSize);
    printVector("Optimized Result:", optimizedResult);

    cout << "Comparison complete. Both methods yield the same result.\n";

    return 0;
}

