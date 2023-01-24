#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>


using namespace std;

struct flight{
public:
    string s;
    int num;
};

struct fio{
public:
    string name;
    string surname;
    string patronym;
};

struct key : public flight, public fio{
    int day;
    int month;
    int year;
};

void bubbleSort(vector<key> &arr, int n) {
    key temp;
    bool swapped;
    for (int i = 0; i < n-1; i++) {
        swapped = false;
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j].s < arr[j+1].s) {
                //swap(arr[j], arr[j+1]);
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                swapped = true;
            } else if (arr[j].s == arr[j+1].s) {
                if (arr[j].num < arr[j+1].num) {
                    //swap(arr[j], arr[j+1]);
                    temp = arr[j];
                    arr[j] = arr[j+1];
                    arr[j+1] = temp;
                    swapped = true;
                } else if (arr[j].num == arr[j+1].num) {
                    if (arr[j].name > arr[j+1].name) {
                        //swap(arr[j], arr[j+1]);
                        temp = arr[j];
                        arr[j] = arr[j+1];
                        arr[j+1] = temp;
                        swapped = true;
                    } else if (arr[j].name == arr[j+1].name) {
                        if (arr[j].surname > arr[j+1].surname) {
                            //swap(arr[j], arr[j+1]);
                            temp = arr[j];
                            arr[j] = arr[j+1];
                            arr[j+1] = temp;
                            swapped = true;
                        } else if (arr[j].surname == arr[j+1].surname) {
                            if (arr[j].patronym > arr[j+1].patronym) {
                                //swap(arr[j], arr[j+1]);
                                temp = arr[j];
                                arr[j] = arr[j+1];
                                arr[j+1] = temp;
                                swapped = true;
                            }
                        }
                    }
                }
            }
        }
        if (!swapped) {
            break;
        }
    }
}

void merge(vector<key> &arr, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
    vector<key> L, R;
    for (i = 0; i < n1; i++) {
        L.push_back(arr[l + i]);
    }
    for (j = 0; j < n2; j++) {
        R.push_back(arr[m + 1 + j]);
    }
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i].s < R[j].s) {
            arr[k] = L[i];
            i++;
        } else if (L[i].s == R[j].s) {
            if (L[i].num < R[j].num) {
                arr[k] = L[i];
                i++;
            } else if (L[i].num == R[j].num) {
                if (L[i].name < R[j].name) {
                    arr[k] = L[i];
                    i++;
                } else if (L[i].name == R[j].name) {
                    if (L[i].surname < R[j].surname) {
                        arr[k] = L[i];
                        i++;
                    } else if (L[i].surname == R[j].surname) {
                        if (L[i].patronym < R[j].patronym) {
                            arr[k] = L[i];
                            i++;
                        } else {
                            arr[k] = R[j];
                            j++;
                        }
                    } else {
                        arr[k] = R[j];
                        j++;
                    }
                } else {
                    arr[k] = R[j];
                    j++;
                }
            } else {
                arr[k] = R[j];
                j++;
            }
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}


void mergeSort(vector<key> &arr, int l, int r, int count) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m, count);
        mergeSort(arr, m + 1, r, count);
        merge(arr, l, m, r);
    }
}

long readKeysFromFile(const string& fileName, vector<key>& keys) {
    ifstream file(fileName);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << fileName << endl;
        return 0;
    }
    string line;
    getline(file, line);
    istringstream iss(line);
    long fileLen;
    iss >> fileLen;
    while (getline(file, line)) {
        istringstream iss(line);
        key k;
        iss >> k.s >> k.num >> k.name >> k.surname >> k.patronym >> k.day >> k.month >> k.year;
        keys.push_back(k);
    }
    file.close();
    return fileLen;
}

void writeKeysToFile(const string& fileName, const vector<key>& keys, auto duration) {
    ofstream file(fileName);
    if (!file.is_open()) {
        cerr << "Failed to open file: " << fileName << endl;
        return;
    }
    file << "Duration of sort: " << duration.count() << " milliseconds" << endl;
    for (const auto& key : keys) {
        file << key.s << " " << key.num << " " << key.name << " " << key.surname << " " << key.patronym << " " << key.day << " " << key.month << " " << key.year << endl;
    }
    file.close();
}

int main() {

    vector <key> keys;
    vector <key> keys2;
    long len1 = readKeysFromFile(R"(C:\files\danil\in1000.txt)", keys);
    long len2 = readKeysFromFile(R"(C:\files\danil\in1000.txt)", keys2);
    cout << len1 << endl;
    cout << len2 << endl;
    auto start = chrono::high_resolution_clock::now();
    bubbleSort(keys, len1); // Sort the vector of keys
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration<double, milli>(stop - start);
    cout << "Bubble Sorting: " << duration.count() << " milliseconds" << endl;
    writeKeysToFile(R"(C:\files\danil\sortedBubble.txt)", keys, duration);

    auto start1 = chrono::high_resolution_clock::now();
    mergeSort(keys2, 0, keys2.size() - 1, len2); // Sort the vector of keys
    auto stop1 = chrono::high_resolution_clock::now();
    auto duration1 = chrono::duration<double, milli>(stop1 - start1);
    cout << "Merge Sorting: " << duration1.count() << " milliseconds" << endl;
    writeKeysToFile(R"(C:\files\danil\sortedMerge.txt)", keys, duration1);

    return 0;
}
