
#include <vector>
#include <iostream>

using array = std::vector<int>;

int missedNumberSum(array &a) {
    unsigned long long  s = 0;
    for (auto e : a)
        s += e;
    auto n = a.size();
    return (int) ((n + 1) * n / 2 - s);
}
int missedNumberBool(array &a) {
    std::vector<bool> check(a.size() + 1, false);
    for (auto e : a)
        check[e] = true;
    for (int i = 0; i < check.size(); ++i)
        if (not check[i])
            return i;
    return 0;
}

int missedNumberReplace(array &a) {
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] == i)
            continue;
        auto m = a[i];
        while (m < a.size() and a[m] != m) {
            auto k = a[m];
            a[m] = m;
            m = k;
        }
    }
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] != i)
            return i;
    }
    return (int) a.size();
}

int main() {
    array a{3, 2, 1, 0};
    std::cout << missedNumberSum(a) << "\n";
    std::cout << missedNumberBool(a) << "\n";
    std::cout << missedNumberReplace(a) << "\n";
}
