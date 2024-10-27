#include <iostream>
#include <fstream>
#include <vector>
#include <utility>

using namespace std;

struct Chord {
    int start;
    int end;
};

struct dependency {
    vector<vector<int>> ij;
    int k;
    dependency() {
        k = -1;
        ij.resize(2, vector<int>(2, -1));
    }
};

vector<int> subset;
void readChords(ifstream& input, vector<int>& chords);
void printMemo(vector<vector<int>>& memo);
void backtrack(vector<vector<dependency>>& dep, vector<int>& subset, int i, int j);
void printSubset(vector<int>& subset, vector<int>& chords);
void quicksort(vector<int>& subset, int low, int high);
int partition(vector<int>& subset, int low, int high);
void swap(int& a, int& b);


void mps(vector<int> chords, vector<vector<int>>& memo, vector<vector<dependency>>& dep, int size) {
    for(int l = 1; l < size; l++) {
        if (l % 1000 == 0) {
            cout << "l = " << l << endl;
        }

        for(int i = 0; i < size - l; i++) {
	    
            int j = i + l;
            int k = chords[j];	// the starting point when the ending point is j

            if(k < i || k > j) {
                memo[i][j] = memo[i][j - 1];
                dep[i][j].ij[0][0] = i;
                dep[i][j].ij[0][1] = j - 1;

            } else if(k > i && k < j) {
                int left = memo[i][k - 1] + memo[k + 1][j - 1] + 1;
                int right = memo[i][j - 1];
                if (left > right) {
                    memo[i][j] = left;
                    dep[i][j].ij[0][0] = i;
                    dep[i][j].ij[0][1] = k - 1;
                    dep[i][j].ij[1][0] = k + 1;
                    dep[i][j].ij[1][1] = j - 1;
                    dep[i][j].k = k;
                } else {
                    memo[i][j] = right;
                    dep[i][j].ij[0][0] = i;
                    dep[i][j].ij[0][1] = j - 1;
                }

            } else if(k == i) {
                memo[i][j] = memo[i + 1][j - 1] + 1;
                dep[i][j].ij[0][0] = i + 1;
                dep[i][j].ij[0][1] = j - 1;
                dep[i][j].k = k;
            } else {
                continue;
            }
        }
    }


}


int main() {

    int n;

    ifstream input("./inputs/10000.in");    
    input >> n;    
    cout << "Number of points: " << n << endl;
    
    vector<int> chords(n);

    readChords(input, chords);

    vector<vector<int>> memo(n, vector<int>(n, -1));
    vector<vector<dependency>> dep(n , vector<dependency>(n)); 
    for(int i = 0; i < n; i++) {
        memo[i][i] = 0;
    }

    mps(chords, memo, dep, n);
    backtrack(dep, subset, 0, n - 1);
    printSubset(subset, chords);
    cout << memo[0][n-1] << endl;
    cout << "Size of subset: " << subset.size() << endl;
    return 0;
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



void readChords(ifstream& input, vector<int>& chords) {
    while (true) {
        int head, tail;
        input >> head;
        // cout << "head: " << head << endl;
        if (head == 0) {
            if (input.peek() == '\n' || input.eof()) {
                break;
            } else {
                input >> tail;
                // cout << "tail: " << tail << endl;
                chords[tail] = head;
                chords[head] = tail;
		        continue;  
            }
        }
        input >> tail;
        chords[tail] = head;
        chords[head] = tail;
        
    }
    //sortSubset(chords);
}



void sortSubset(vector<int>& subset) {
    quicksort(subset, 0, subset.size() - 1);
}


void quicksort(vector<int>& subset, int low, int high) {
    if (low < high) {
        int pi = partition(subset, low, high);
        quicksort(subset, low, pi - 1);
        quicksort(subset, pi + 1, high);
    }
}

int partition(vector<int>& subset, int low, int high) {
    int pivot = subset[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (subset[j] < pivot) {
            i++;
            swap(subset[i], subset[j]);
        }
    }
    swap(subset[i + 1], subset[high]);
    return (i + 1);
}

void swap(int& a, int& b) {
    int t = a;
    a = b;
    b = t;
}


void backtrack(vector<vector<dependency>>& dep, vector<int>& subset, int i, int j) {
    if (i > j) {
        return;
    }
    if (dep[i][j].ij[0][0] == -1 && dep[i][j].ij[1][0] == -1) {
        return;
    }
    if (dep[i][j].ij[1][0] != -1 && dep[i][j].ij[1][1] != -1) {
        subset.push_back(dep[i][j].k); // push the ending point of the chord
        backtrack(dep, subset, dep[i][j].ij[0][0], dep[i][j].ij[0][1]);
        backtrack(dep, subset, dep[i][j].ij[1][0], dep[i][j].ij[1][1]);
    } else if (dep[i][j].ij[0][0] == i + 1 && dep[i][j].ij[0][1] == j - 1) {
        subset.push_back(dep[i][j].k); // push the ending point of the chord
        backtrack(dep, subset, dep[i][j].ij[0][0], dep[i][j].ij[0][1]);
    } else {
        backtrack(dep, subset, dep[i][j].ij[0][0], dep[i][j].ij[0][1]);
    }
}

void printSubset(vector<int>& subset, vector<int>& chords) {
    sortSubset(subset);
    for (int i = 0; i < subset.size(); i++) {
        cout << subset[i] << " " << chords[subset[i]] << endl;
    }
    cout << endl;
}
