#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>

using namespace std;

struct Chord {
    int start, end;
};

// Memoization cache for maximum planar subset size
unordered_map<string, int> memo;

// Function to create a unique key for memoization
string createKey(int i, int j) {
    return to_string(i) + "," + to_string(j);
}

// Function to find the maximum planar subset using recursion and memoization
int findMaxPlanarSubset(const vector<Chord>& chords, int i, int j) {
    // Base case
    if (i >= j) return 0;

    string key = createKey(i, j);
    if (memo.find(key) != memo.end()) return memo[key];

    // Exclude the last chord
    int maxSubset = findMaxPlanarSubset(chords, i, j - 1);

    // Include the last chord if it is a valid pair
    for (const auto& chord : chords) {
        if (chord.start == i && chord.end == j) {
            int temp = 1 + findMaxPlanarSubset(chords, i + 1, j - 1);
            maxSubset = max(maxSubset, temp);
        }
    }

    // Store the result in the memoization cache
    memo[key] = maxSubset;
    return maxSubset;
}

int main() {
    ifstream input("./inputs/12.in");

    // Read the number of points on the circle
    int n;
    input >> n;
    cout << "Number of points: " << n << endl;  // Debugging output

    vector<Chord> chords;
    
    while (true) {
        int start, end;
        input >> start;

        // Check for termination condition
        if (start == 0) {
            if (input.peek() == '\n' || input.eof()) {
                break;  // Terminating condition
            } else {
                input >> end;
                chords.push_back({start, end});
                cout << "Read chord: " << start << " " << end << endl;  // Debugging output
                continue;  // Continue to read the next chord
            }
        }

        // Read the end value only if the start is not 0
        input >> end;
        chords.push_back({start, end});
        cout << "Read chord: " << start << " " << end << endl;  // Debugging output
    }

    // Display the list of chords read
    cout << "Chords read: " << endl;
    for (const auto& chord : chords) {
        cout << chord.start << " " << chord.end << endl;
    }

    // Call the recursive function to find the maximum planar subset
    int maxSubset = findMaxPlanarSubset(chords, 0, n - 1);

    cout << "Number of chords in maximum planar subset: " << maxSubset << endl;

    return 0;
}

