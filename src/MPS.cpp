#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int mps(int i, int j, vector<int>& chords, vector<vector<int>>& memo);
void readChords(ifstream& input, vector<int>& chords, vector<int>& start);
void printSubset(vector<int>& subset, vector<int>& chords, ofstream& output);
void quicksort(vector<int>& subset, int low, int high);
void sortSubset(vector<int>& subset);
int partition(vector<int>& subset, int low, int high);
void swap(int& a, int& b);
void traverseOptimal(int i, int j, vector<vector<int>>& memo, vector<int>& ans, vector<int>& chords, vector<int>& reversed);

int main(int argc, char* argv []) {

    int n;

    ifstream input;
    ofstream output;
    input.open(argv[1]);
    output.open(argv[2]);

    input >> n;    

    vector<int> chords(n);
    vector<int> start(n, 0);
    readChords(input, chords, start);
    input.close();

    vector<vector<int>> memo(n, vector<int>(n, -1));
    for(int i = 0; i < n; i++) {
        memo[i][i] = 0;
    }

    mps(0, n - 1, chords, memo);

    vector<int> ans;
    traverseOptimal(0, n - 1, memo, ans, chords, start);
    sortSubset(ans);

    output << ans.size() << endl;
    printSubset(ans, chords, output);
    return 0;
}

int mps(int i, int j, vector<int>& chords, vector<vector<int>>& memo) {
    if (memo[i][j] != -1) {
        return memo[i][j];
    }

    if(j <= i){
        memo[i][j] = 0;
        return 0;
    }

    if(chords[j] < i || chords[j] > j) {
        memo[i][j] = mps(i, j - 1, chords, memo);
    } else if(chords[j] > i && chords[j] < j) {
        int left = mps(i, chords[j] - 1, chords, memo) + mps(chords[j] + 1, j - 1, chords, memo) + 1;
        int right = mps(i, j - 1, chords, memo);
        if (left >= right) {
            memo[i][j] = left;
        } else {
            memo[i][j] = right;
        }
    } else if(chords[j] == i) {
        memo[i][j] = mps(i + 1, j - 1, chords, memo) + 1;
    } else {
        cout << "else case " << endl;
        memo[i][j] = 0;
    }

    memo[i][j] = memo[i][j];   
    return memo[i][j];
}

void readChords(ifstream& input, vector<int>& chords, vector<int>& start) {
    int head, tail;
    while (true) {
        input >> head;
        if (head == 0) {
            if (input.peek() == '\n' || input.eof()) {
                break;
            } else {
                input >> tail;
                chords[tail] = head;
                chords[head] = tail;
		        continue;  
            }
        }
        input >> tail;
        chords[tail] = head;
        chords[head] = tail;
        start[head] = 1;
        
    }
}

void printSubset(vector<int>& subset, vector<int>& chords, ofstream& output) {
    sortSubset(subset);
    for (int i = 0; i < subset.size(); i++) {
        output << subset[i] << " " << chords[subset[i]] << endl;
    }
    output << endl;
}

void quicksort(vector<int>& subset, int low, int high) {
    if (low < high) {
        int pi = partition(subset, low, high);
        quicksort(subset, low, pi - 1);
        quicksort(subset, pi + 1, high);
    }
}

void sortSubset(vector<int>& subset) {
    quicksort(subset, 0, subset.size() - 1);
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


void traverseOptimal(int i, int j, vector<vector<int>>& memo, vector<int>& ans, vector<int>& chords, vector<int>& start) {
    if(memo[i][j] <= 0) {
        return;
    }

    if(chords[j] < i || chords[j] > j) {
        memo[i][j] = mps(i, j - 1, chords, memo);
        traverseOptimal(i, j - 1, memo, ans, chords, start);
    } else if(chords[j] > i && chords[j] < j) {
        int left = mps(i, chords[j] - 1, chords, memo) + mps(chords[j] + 1, j - 1, chords, memo) + 1;
        int right = mps(i, j - 1, chords, memo);
        if (left >= right) {
            memo[i][j] = left;
            ans.push_back((start[j]) ? j : chords[j]);
            traverseOptimal(i, chords[j] - 1, memo, ans, chords, start);
            traverseOptimal(chords[j] + 1, j - 1, memo, ans, chords, start);
        } else {
            memo[i][j] = right;
            traverseOptimal(i, j - 1, memo, ans, chords, start);
        }
    } else if(chords[j] == i) {
        memo[i][j] = mps(i + 1, j - 1, chords, memo) + 1;
        ans.push_back((start[j]) ? j : chords[j]);
        traverseOptimal(i + 1, j - 1, memo, ans, chords, start);
    } else {
        cout << "else case " << endl;
        memo[i][j] = 0;
    }
}



void swap(int& a, int& b) {
    int t = a;
    a = b;
    b = t;
}