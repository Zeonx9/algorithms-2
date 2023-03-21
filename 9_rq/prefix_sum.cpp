//
// Created by musht on 03.03.2023.
//

#include <vector>
#include <unordered_map>
#include <iostream>

// each ith element of res is a sum off all elements prior to ith element of vec
std::vector<int> prefix_of(const std::vector<int> &vec) {
    std::vector<int> res(vec.size() + 1, 0);
    for (int i = 0; i < vec.size(); ++i) {
        res[i + 1] = res[i] + vec[i];
    }
    return res;
}

int sum_of_range(const std::vector<int> &prefix_sum, int l, int r) {
    return prefix_sum[r] - prefix_sum[l];
}

std::pair<int, int> max_len_zero_sum_range(const std::vector<int> &vec) {
    auto prefix = prefix_of(vec);
    std::unordered_map<int, int> map;
    int start = -1, end  = -1;
    for (int i = 0; i < prefix.size(); ++i) {
        auto elem = prefix[i];
        if (map.find(elem) == map.end()) {
            map[elem] = i;
        }
        else if (i - map[elem] > start - end) {
            start = map[elem];
            end = i;
        }
    }
    return {start, end - 1};
}

std::vector<std::vector<int>> prefix_2d_of(const std::vector<std::vector<int>> &mat) {
    auto res = std::vector<std::vector<int>>();
    res.emplace_back(mat[0].size() + 1, 0);
    for (int i = 0; i < mat.size(); ++i) {
        for (int j = 0; j < mat[0].size(); ++j) {
            res[i + 1][j + 1] = mat[i][j] + res[i][j + 1] + res[i + 1][j] - res[i][j];
        }
    }
    return res;
}

int sum_2d_of_range(const std::vector<std::vector<int>> &prefix, int lr, int lc, int rr, int rc) {
    return prefix[rr][rc] - prefix[lr][rc] - prefix[rr][lc] + prefix[lr][lc];
}

int main() {
    std::vector<int> a = {1, 2, 3, -5, 4, 8};
    auto ans = max_len_zero_sum_range(a);
    std::cout << ans.first << " " << ans.second << "\n";
}