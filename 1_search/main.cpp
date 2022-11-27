#define B

#ifdef B
#include <iostream>

// creates a sorted 2d array and returns it;
int ** generate(int n, int  m) {
    int ** arr = new int *[n];
    for (int i = 0; i < n; ++i) {
        arr[i] = new int[m];
    }

    arr[0][0] = 0;
    for (int j = 1; j < m; ++j) {
        arr[0][j] = arr[0][j - 1] + rand() % 10 + 1;
    }
    for (int i = 1; i < n; ++i) {
        arr[i][0] = arr[i - 1][0] + rand() % 10 + 1;
    }
    for (int i = 1; i < n; ++i)
        for (int j = 1; j < m; ++j) {
            int e = std::max(arr[i][j - 1], arr[i - 1][j]);
            arr[i][j] = e + rand() % 10 + 1;
        }

    return arr;
}

// frees allocated memory
void del(int **a, int n) {
    for (int i = 0; i < n; ++i) {
        delete[] a[i];
    }
    delete[] a;
}

// prints the 2d aray to console
void print(int **a, int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j)
            std::cout << a[i][j] << " ";
        std::cout << "\n";
    }

}

// tells if there is such element 'key' in matrix 'a' with o(n + m) complexity
bool findLin(int key, int **a, int n, int m) {
    int i = 0, j = m - 1, k = 0, l = n - 1;;
    while (i < n and j >= 0 and k < m and l >= 0) {
        if (a[i][j] == key or a[l][k] == key)
            return true;
        if (key < a[i][j])
            --j;
        else
            ++i;
        if (key < a[l][k])
            --l;
        else
            ++k;
    }
    return false;
}

// tells if there is such element 'key' in matrix 'a' with O(n * log m) complexity
bool findBin(int key, int **a, int n, int m) {
    if (n < m) {
        for (int i = 0; i < n; ++i) {
            int s = 0, e = m;
            while (s < e) {
                int d = (s + e) / 2;
                if (a[i][d] == key)
                    return true;

                if (key < a[i][d])
                    e = d;
                else
                    s = d + 1;
            }
        }
        return false;
    } else {
        for (int i = 0; i < m; ++i) {
            int s = 0, e = n;
            while (s < e) {
                int d = (s + e) / 2;
                if (a[d][i] == key)
                    return true;

                if (key < a[d][i])
                    e = d;
                else
                    s = d + 1;
            }
        }
        return false;
    }

}

#include <chrono>
#include <fstream>

// measures the time of executing
long long test_time(int** arr, int n, int m, bool (*func)(int, int **, int, int)) {
    auto t1 = std::chrono::high_resolution_clock::now();
    for (int j = 0; j < 100; ++j) {
        int f = rand() % (arr[n - 1][m - 1] + 1);
        func(f, arr, n, m);
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
}

#define max1 6

void saveData(std::ofstream &file, long long data[max1][max1], int n) {
    std::string sep = ",\t";
    file << "0" << sep;
    for (int i = 0, m = 1; i < n; ++i, m *= 10) {
        file << m << sep;
    }
    file << "\n";
    for (int i = 0, m = 1; i < n; ++i, m *= 10) {
        file << m << sep;
        for (int j = 0; j < n; ++j) {
            file << data[i][j] << sep;
        }
        file << "\n";
    }
}

int main() {
    srand(time(nullptr));

    for (int i = 0, n = 100000, m = 10; i < 5; ++i, n /= 10, m *= 10) {
        int **arr = generate(n, m);
        std::cout << n << " x " << m << ": "
                  << (double) test_time(arr, n, m, findLin) / 1000.0 << ", "
                  << (double) test_time(arr, n, m, findBin) / 1000.0<< "\n";
        del(arr, n);
    }
}
#endif