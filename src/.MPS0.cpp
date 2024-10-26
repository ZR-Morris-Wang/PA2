#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Chord {
    int start, end;
};

vector<vector<int>> dp;
vector<vector<vector<int>>> solution;
vector<Chord> chords;

int findMaxPlanarSubset(int i, int j) {
    if (i >= j) return 0;
    if (dp[i][j] != -1) return dp[i][j];

    dp[i][j] = findMaxPlanarSubset(i, j - 1);
    solution[i][j] = solution[i][j - 1];

    for (int k = 0; k < chords.size(); ++k) {
        if (chords[k].start == i && chords[k].end == j) {
            int temp = findMaxPlanarSubset(i + 1, j - 1) + 1;
            if (dp[i][j] < temp) {
                dp[i][j] = temp;
                solution[i][j] = solution[i + 1][j - 1];
                solution[i][j].push_back(k);
            }
        }
    }

    return dp[i][j];
}

int main() {
    ifstream input("inputs/12.in");

    // Read the number of points on the circle
    int n;
    input >> n;
    cout << "Number of points: " << n << endl;  // Debugging output
while (true) {
        int start, end;

        // Read the start value
        input >> start;

        // Check for termination condition
        if (start == 0) {
            // If the start is 0, we need to break, but we need to ensure there's no following number
            if (input.peek() == '\n' || input.eof()) {
                break;  // Terminating condition
            } else {
                // If there is another value, continue to read the end of the chord
                input >> end;
                chords.push_back({start, end});
                cout << "Read chord: " << start << " " << end << endl;  // Debugging output
                continue;  // Continue to read the next chord
            }
        }

        // Read the end value only if the start is not 0
        input >> end;

        // Debugging output to verify the chords being read
        cout << "Read chord: " << start << " " << end << endl;

        chords.push_back({start, end});
    }

    // Display the list of chords read
    cout << "Chords read: " << endl;
    for (const auto &chord : chords) {
        cout << chord.start << " " << chord.end << endl;
    }

    int m = chords.size();
    dp.assign(m + 1, vector<int>(m + 1, -1));
    solution.assign(m + 1, vector<vector<int>>(m + 1));

    int maxSubset = findMaxPlanarSubset(0, m - 1);

    cout << "Number of chords in maximum planar subset: " << maxSubset << endl;
    cout << "Chords in maximum planar subset:" << endl;
    for (int idx : solution[0][m - 1]) {
        cout << chords[idx].start << " " << chords[idx].end << endl;
    }

   return 0;
}

