#include <vector>
#include <iostream>
#include <algorithm>

using array = std::vector<int>;
using str = std::string;

void print(array &c) {
    for (auto e : c) {
        std::cout << e << " ";
    }
    std::cout << "\n";
}
array input() {
    int n;
    std::cin >> n;
    array a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    return a;
}

//  find the union of sorted int arrays from unique elements
array getUnion(array &a, array &b) {
    int i = 0, j = 0;
    array c;
    while (i < a.size() and j < b.size()) {
        if (a[i] < b[j])
            c.push_back(a[i++]);
        else if (a[i] > b[j])
            c.push_back(b[j++]);
        else {
            c.push_back(a[i]);
            ++i; ++j;
        }
    }
    while (i < a.size())
        c.push_back(a[i++]);
    while (j < b.size())
        c.push_back(b[j++]);
    return c;
}

// find count of most frequent element in the union of two arays
int countFreqInUnion(array &a, array &b) {
    int i = 0, j = 0, max = 0;
    while (i < a.size() and j < b.size()) {
        if (a[i] < b[j])
            ++i;
        else if (b[j] < a[i])
            ++j;

        auto cur = a[i];
        int counter = 0;
        while (i < a.size() and a[i++] == cur)
            ++counter;
        while (j < b.size() and b[j++] == cur)
            ++counter;
        max = std::max(counter, max);
    }
    return max;
}

// find min |a[i] - b[j]|
// sort and work
// or sort union and work
int getMindiff(array &a, array &b) {
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end());
    int i = 1, j = 1, min_diff = 10000000;
    while (i < a.size() and j < b.size()) {
        min_diff = std::min({std::abs(a[i] - b[j - 1]), std::abs(a[i] - b[j]), std::abs(b[j] - a[i - 1]), min_diff});
        ++i;
        ++j;
    }
    return min_diff;
}

// 'a' is sorted array return new sorted array with squared values from 'a'
array getSquared(array &a) {
    array b;
    int s = 0, e = (int) a.size();
    while (s < e) {
        int m = (s + e) / 2;
        if (a[m] == 0) {
            s = m;
            break;
        }
        if (a[m] < 0)
            s = m + 1;
        else
            e = m;
    }
    int i = s, j = s + 1;
    while (i >= 0 and j < a.size()) {
        if (-a[i] < a[j]) {
            b.push_back(a[i] * a[i]);
            i--;
        } else {
            b.push_back(a[j] * a[j]);
            j++;
        }
    }
    while (i >= 0) {
        b.push_back(a[i] * a[i]);
        --i;
    }
    while (j < a.size()) {
        b.push_back(a[j]*a[j]);
        ++j;
    }
    return b;
}

// find maximum of size of subarray sum of which is greater than k;
int getMinSizeOfSubArrWithMaxSum(array &a, int k) {
    int i = 0, j = 1, min_size = (int) a.size(), sum = a[0];
    while (j < a.size()) {
        if (sum < k) {
            sum += a[j];
            ++j;
        } else {
            min_size = std::min(min_size, j - i);
            sum -= a[i];
            ++i;
        }
    }
    return min_size;
}

str getMaxSubstrNoRepeat(str &s) {
    return s;
}

int main() {
    array a = input(), b = getSquared(a);
    print(a);
    print(b);
    return 0;
}