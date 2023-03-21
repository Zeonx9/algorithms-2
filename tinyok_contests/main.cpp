//
// Created by musht on 18.03.2023.
//
#define E


#ifdef A
#include <vector>
#include <iostream>

bool ordered(const std::vector<int> &seq, bool asc) {
    for (int i = 0; i < seq.size() - 1; ++i) {
        if (not ((asc and seq[i + 1] >= seq[i]) or (not asc and seq[i + 1] <= seq[i]))) {
            return false;
        }
    }
    return true;
}
std::string solve(const std::vector<int> &seq) {
    if (ordered(seq, true) or ordered(seq, false)) {
        return "YES";
    }
    return "NO";
}

int main() {
    std::vector<int> heights(4);
    for (int i = 0; i < 4; i++) {
        std::cin >> heights[i];
    }
    std::cout << solve(heights);
}
#endif

#ifdef B
#include <iostream>
#include <cmath>

int solve(double n, double m, double k) {
    return std::ceil(n * k / m);
}

int main() {
    int n, m, k;
    std::cin >> n >> m >> k;
    std::cout << solve(n, m, k);
}
#endif

#ifdef C
#include <unordered_map>
#include <iostream>

int min_pos(const std::unordered_map<char, int> &map) {
    int min_v = map.begin()->second;
    for (auto [k, v] : map) {
        min_v = std::min(min_v, v);
    }
    return min_v;
}

int solve(const std::string &s) {
    std::unordered_map<char, int> pos;
    int min_len = (int) s.size() + 1;
    for (int i = 0; i < s.size(); ++i) {
        pos[s[i]] = i;
        if (pos.size() == 4) {
            min_len = std::min(min_len, i - min_pos(pos) + 1);
        }
    }
    return pos.size() == 4 ? min_len : -1;
}

int main() {
    int n;
    std::string s;
    std::cin >> n >> s;
    std::cout << solve(s);
}
#endif

#ifdef D
#include <vector>
#include <unordered_map>
#include <iostream>

bool check_pair(const std::vector<int> &values, const std::vector<int> &keys, int i, int j) {
    // rather there is a group containing one number that was encountered
    // one time more than other numbers in other group
    // or a group with one number that was encountered exactly once
    return values[i] == 1 and (keys[i] == keys[j] + 1 or keys[i] == 1);
}

bool is_boring(const std::unordered_map<int, int> &groups) {
    if (groups.size() == 2) {
        std::vector<int> values, keys;
        for (auto [k, v] : groups) {
            keys.push_back(k);
            values.push_back(v);
        }
        return check_pair(values, keys, 0, 1) or check_pair(values, keys, 1, 0);
    }
    if (groups.size() == 1 and groups.begin()->first == 1) {
        return true;
    }
    return false;
}

void update_group_counter(std::unordered_map<int, int> &group_counter, int new_count) {
    // increment a group for new value
    if (group_counter.find(new_count) == group_counter.end()) {
        group_counter[new_count] = 1;
    } else {
        group_counter[new_count]++;
    }
    // decrement a group of previous value
    if (new_count > 1) {
        group_counter[new_count - 1]--;
    }
    // delete if group is empty
    if (group_counter.find(new_count - 1) != group_counter.end() and group_counter[new_count - 1] == 0) {
        group_counter.erase(new_count - 1);
    }
}

int solve(const std::vector<int> &a) {
    // counts how many times the number has been encountered in prefix of a
    std::unordered_map<int, int> counter;
    std::unordered_map<int, int> group_counter;
    int l = -1;
    for (int i = 0; i < a.size(); ++i) {
        counter[a[i]] += 1;
        update_group_counter(group_counter, counter[a[i]]);
        if (is_boring(group_counter)) {
            l = i + 1;
        }
    }
    return l;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    std::cout << "start\n";
    std::cout << solve(a);
}
#endif

#ifdef E
#include <vector>
#include <unordered_map>
#include <iostream>
#include <algorithm>

std::vector<int> prefix_of(const std::vector<int> &vec) {
    std::vector<int> res(vec.size() + 1, 0);
    for (int i = 0; i < vec.size(); ++i) {
        res[i + 1] = res[i] + vec[i];
    }
    return res;
}

std::vector<std::pair<int, int>> zero_sum_ranges_in(const std::vector<int> &vec) {
    std::unordered_map<int, int> map;
    std::vector<std::pair<int, int>> res;
    auto prefix = prefix_of(vec);
    for (int i = 0; i < prefix.size(); ++i) {
        auto elem = prefix[i];
        if (map.find(elem) != map.end()) {
            res.emplace_back(map[elem], i);
        }
        map[elem] = i;
    }
    return res;
}

int solve(const std::vector<int> &a) {
    auto zero_sums = zero_sum_ranges_in(a);
    // create vector sorted by first coordinates
    std::vector<std::pair<int, int>> l_zero_sums = zero_sums;
    std::sort(l_zero_sums.begin(), l_zero_sums.end());

    int res = 0;
    int prev_r = (int) a.size();
    auto l_border = l_zero_sums.rbegin();

    for (auto it = zero_sums.rbegin(); it < zero_sums.rend(); ++it) {
        while (l_border->second > it->second) {
            l_border++;
        }
        res += (prev_r - it->second + 1) * (l_border->first + 1);
        prev_r = it->second - 1;
    }
    return res;
}

int main() {
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i];
    }
    std::cout << solve(a);
}
#endif

#ifdef F

class Solver {
    std::vector<std::pair<int, int>> a;
    int s;
    std::vector<int> path;
    int answer = -1;

    void count_median() {
        std::vector<int> path_copy = path;
        std::sort(path_copy.begin(), path_copy.end());
        answer = std::max(answer, path_copy[path_copy.size() / 2]);
    }

    void dfs(int sum, int level) {
        if (level == a.size()) {
            count_median();
            return;
        }
        for (int i = a[level].second; i >= a[level].first; --i) {
            if (sum + i > s) {
                continue;
            }

            path.push_back(i);
            dfs(sum + i, level + 1);
            path.pop_back();
        }
    }

public:

    Solver(std::vector<std::pair<int, int>> &a_, int s_) : a(std::move(a_)), s(s_) {}

    int solve() {
        dfs(0, 0);
        return answer;
    }
};

int main() {
    int n, s;
    std::cin >> n >> s;
    std::vector<std::pair<int, int>> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i].first >> a[i].second;
    }
    Solver solver = Solver(a, s);
    std::cout << solver.solve();
}
#endif

#ifdef H
#include <vector>
#include <algorithm>
#include <iostream>

class Solver {
    std::vector<std::pair<int, int>> a;
    constexpr static auto comp = [](const std::pair<int, int> &p1, const std::pair<int, int> &p2) {
        return p1.second < p2.second;
    };
    int n, s;
    int min_med, max_med;
    int init_less_sum = 0, init_less_count = 0;
    int init_greater_sum = 0, init_greater_count = 0;

    bool check_median(int median) {
        int count_less = init_less_count, sum_less = init_less_sum;
        int count_greater = init_greater_count, sum_greater = init_greater_sum;
        std::vector<std::pair<int, int>> middle;
        for (auto [l, r] : a) {
            if (r < median) {
                count_less++;
                sum_less += l;
            }
            else if (l > median) {
                count_greater++;
                sum_greater += l;
            }
            else {
                middle.emplace_back(l, r);
            }
        }
        if ((n / 2 < count_less) or (n / 2 >= count_less + middle.size())) {
            return false;
        }
        int k = n / 2 - count_less;
        for (int i = 0; i < k; i++) {
            sum_less += middle[i].first;
        }
        return sum_less + median * (middle.size() - k) + sum_greater <= s;
    }

public:

    Solver(std::vector<std::pair<int, int>> &a_, int s_) : a(std::move(a_)), s(s_) {
        std::vector<std::pair<int, int>> a_copy = a;

        std::sort(a.begin(), a.end());
        std::sort(a_copy.begin(), a_copy.end(), comp);

        n = (int) a.size();
        max_med = a_copy[n / 2].second;
        min_med = a[n / 2].first;

        std::vector<std::pair<int, int>> new_a;
        for (auto [l, r] : a) {
            if (r < min_med) {
                init_less_count++;
                init_less_sum += l;
            }
            else if (l > max_med) {
                init_greater_count++;
                init_greater_sum += l;
            }
            else {
                new_a.emplace_back(l, r);
            }
        }
        a = std::move(new_a);
//        std::cout << "[" << min_med << "; " << max_med << "] left("
//                << init_less_count << ", " << init_less_sum << ") right("
//                << init_greater_count << ", " << init_greater_sum << ")\n";
    }

    int solve() {
        for (int i = max_med; i >= min_med; i--) {
            if (check_median(i)) {
                return i;
            }
        }
        return -1;
    }
};

int main() {
    int n, s;
    std::cin >> n >> s;
    std::vector<std::pair<int, int>> a(n);
    for (int i = 0; i < n; ++i) {
        std::cin >> a[i].first >> a[i].second;
    }
    Solver solver = Solver(a, s);
    std::cout << solver.solve();
}
#endif


