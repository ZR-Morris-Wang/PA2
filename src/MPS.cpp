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

void readChords(ifstream& input, vector<int>& chords);
void printMemo(vector<vector<int>>& memo);
void sortSubset(vector<Chord>& subset);
int partition(vector<Chord>& subset, int low, int high);
void quickSort(vector<Chord>& subset, int low, int high);


void mps(vector<int> chords, vector<vector<int>>& memo, int size) {
    for(int l = 1; l < size; l++) {
    	
        if (l % 1000 == 0) {
            cout << "l = " << l << endl;
        }

        for(int i = 0; i < size - l; i++) {
	    
        int j = i + l;
	    int k = chords[j];	// the starting point when the ending point is j

	    if(k < i || k > j) {
	        memo[i][j] = memo[i][j - 1];
	    } else if(k > i && k < j) {
	    	memo[i][j] = max(memo[i][k - 1] + memo[k + 1][j - 1] + 1, memo[i][j - 1]);
	    } else if(k == i) {
	    	memo[i][j] = memo[i + 1][j - 1] + 1;
	    } else {
	    	continue;
	    }
	}
    }


}


int main() {

    int n;

    ifstream input("./inputs/100000.in");    
    input >> n;    
    cout << "Number of points: " << n << endl;
    
    vector<int> chords(n);

    readChords(input, chords);
    
    // for(int i = 0; i < n; i++) {
    //     cout << chords[i] << " ";
    // }

    vector<vector<int>> memo(n, vector<int>(n, -1));

    for(int i = 0; i < n; i++) {
        memo[i][i] = 0;
    }

    mps(chords, memo, n);


    // printMemo(memo);
    cout << memo[0][n-1] << endl;

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
