#include <iostream>
#include <vector>
#include <algorithm>
#include <omp.h>

using namespace std;

const int BIN_COUNT = 3;
const int MAX_VALUE = 100;

int getBinIndex(int value) {
    int range = MAX_VALUE / BIN_COUNT;
    return value / range;
}

int main() {
    vector<int> data = {42, 15, 88, 32, 67, 23, 75, 11, 98, 54};
    
    vector<vector<int>> bins(BIN_COUNT);

    #pragma omp parallel
    {
        vector<vector<int>> private_bins(BIN_COUNT);
        
        #pragma omp for
        for (size_t i = 0; i < data.size(); ++i) {
            int binIndex = getBinIndex(data[i]);
            if (binIndex >= BIN_COUNT) binIndex = BIN_COUNT - 1;
            private_bins[binIndex].push_back(data[i]);
        }

        #pragma omp critical
        for (int i = 0; i < BIN_COUNT; ++i) {
            bins[i].insert(bins[i].end(), 
                          private_bins[i].begin(), 
                          private_bins[i].end());
        }
    }

    #pragma omp parallel for
    for (int i = 0; i < BIN_COUNT; ++i) {
        sort(bins[i].begin(), bins[i].end());
    }

    vector<int> sortedData;
    for (const auto& bin : bins) {
        sortedData.insert(sortedData.end(), bin.begin(), bin.end());
    }

    cout << "Sorted Data: ";
    for (int num : sortedData) {
        cout << num << " ";
    }
    cout << endl;

    return 0;
}

