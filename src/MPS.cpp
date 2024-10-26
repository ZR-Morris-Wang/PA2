#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

using namespace std;

struct Chord {
    int start;
    int end;
    // bool switched = false;
};
void readChords(ifstream& input);
void printMemo(vector<vector<int>>& memo);
void sortSubset(vector<Chord>& subset);
int partition(vector<Chord>& subset, int low, int high);
void quickSort(vector<Chord>& subset, int low, int high);
vector<Chord> chords;


int mps(int i, int j, vector<Chord>& subset, vector<vector<int>>& memo) {
    int maxCount = 0;
    int chordIndex = -1;

    if (i >= j) {
        memo[i][j] = 0;
        return 0;
    }
    
    if (memo[i][j] != -1) {
        return memo[i][j];
    }

    for (int h = 0; h < chords.size(); h++){     
        int k = -1;  
        if (j == chords[h].start){
            k = chords[h].end;
        } else if (j == chords[h].end){
            k = chords[h].start;
        } else {
            continue;
        }

        if (k == i) {
            maxCount = mps(i + 1, j - 1, subset, memo) + 1;
            chordIndex = h;
        } else if (k < i || k > j) {
            maxCount = mps(i, j - 1, subset, memo);
        } else if (k > i && k < j) {
            int left = mps(i, j - 1, subset, memo);
            int right = mps(i, k - 1, subset, memo) + mps(k + 1, j - 1, subset, memo) + 1;
            if (left > right) {
                maxCount = left;
            } else {
                maxCount = right;
                chordIndex = h;
            }
        }
        break;
    }


    memo[i][j] = maxCount;
    // if (chordIndex != -1) {
    //     bool found = false;
    //     for (const Chord& chord : subset) {
    //         if (chord.start == chords[chordIndex].start && chord.end == chords[chordIndex].end) {
    //             // cout << "Found duplicate chord: " << chord.start << " " << chord.end << endl;
    //             found = true;
    //             break;
    //         }
    //     }
    //     if (!found) {
    //         subset.push_back(chords[chordIndex]);
    //     }
    // }
    return maxCount;
}



int main() {

    int n;

    ifstream input("./inputs/60000.in");    
    input >> n;    
    cout << "Number of points: " << n << endl;
    
    readChords(input);
    
    vector<Chord> subset;
    vector<vector<int>> memo(n, vector<int>(n, -1));
    int maxCount = mps(0, n - 1, subset, memo);

    // printMemo(memo);

    cout << maxCount << endl;
    sortSubset(subset);

    cout << subset.size() << endl;

    // for (int i = 0; i < subset.size(); i++) {
    //     cout << subset[i].start << " " << subset[i].end << endl;
    // }

    return 0;
}







void readChords(ifstream& input) {
    while (true) {
        int start, end;
        input >> start;
        // bool switched = false;
        // Check for termination condition
        if (start == 0) {
            if (input.peek() == '\n' || input.eof()) {
                break;  // Terminating condition
            } else {
                input >> end;
                // if (start > end) {
                //     swap(start, end);
                //     switched = true;
                // }
                // // chords.push_back({start, end, switched});
                chords.push_back({start, end});
                continue;  // Continue to read the next chord
            }
        }
        // Read the end value only if the start is not 0
        input >> end;

        // if (start > end) {
        //     swap(start, end);
        //     switched = true;
        // }
        // chords.push_back({start, end, switched});
        chords.push_back({start, end});
        // cout << "Read chord: " << start << " " << end << endl;  // Debugging output
    }
}
void printMemo(vector<vector<int>>& memo) {
    cout << "Memoization Table:" << endl;
    cout << "    ";
    for (int col = 0; col < memo[0].size(); col++) {
        cout << col << " ";
    }
    cout << endl;
    for (int row = 0; row < memo.size(); row++) {
        cout << row << ": ";
        for (int col = 0; col < memo[row].size(); col++) {
            cout << memo[row][col] << " ";
        }
        cout << endl;
    }
}

void quickSort(vector<Chord>& subset, int low, int high) {
    if (low < high) {
        int pi = partition(subset, low, high);
        quickSort(subset, low, pi - 1);
        quickSort(subset, pi + 1, high);
    }
}

int partition(vector<Chord>& subset, int low, int high) {
    Chord pivot = subset[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (subset[j].start < pivot.start) {
            i++;
            swap(subset[i], subset[j]);
        }
    }
    swap(subset[i + 1], subset[high]);
    return i + 1;
}

void sortSubset(vector<Chord>& subset) {
    if (!subset.empty()) {
        quickSort(subset, 0, subset.size() - 1);
    }
}
