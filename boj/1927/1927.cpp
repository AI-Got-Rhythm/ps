#define LOCAL // need to delete in online judge
// https://www.acmicpc.net/problem/1927
//------------------------------------------------------------------------------
// #include <bits/stdc++.h>
#include <iostream>
using namespace std;
template <typename T, typename... Args>
void log(const T& first, const Args&... rest);
void end();
// #define C_MIN (-(1e8 + 7))
// #define C_MAX (1e8 + 7)
#define C_MAX (1234567891)
#define C_MIN (-1234567891)
/**
 *------------------------------------------------------------------------------
 *                      /$$             /$$     /$$
 *                     | $$            | $$    |__/
 *   /$$$$$$$  /$$$$$$ | $$ /$$   /$$ /$$$$$$   /$$  /$$$$$$  /$$$$$$$
 *  /$$_____/ /$$__  $$| $$| $$  | $$|_  $$_/  | $$ /$$__  $$| $$__  $$
 * |  $$$$$$ | $$  \ $$| $$| $$  | $$  | $$    | $$| $$  \ $$| $$  \ $$
 *  \____  $$| $$  | $$| $$| $$  | $$  | $$ /$$| $$| $$  | $$| $$  | $$
 *  /$$$$$$$/|  $$$$$$/| $$|  $$$$$$/  |  $$$$/| $$|  $$$$$$/| $$  | $$
 * |_______/  \______/ |__/ \______/    \___/  |__/ \______/ |__/  |__/
 *------------------------------------------------------------------------------
 */

#include <vector>
template <typename T, typename Compare = std::less<T>>
class pq {
    vector<T> base;
    Compare cmp;

    void downheap(size_t i)
    {
        size_t best = i;
        size_t l = i * 2 + 1;
        size_t r = i * 2 + 2;

        if (l < base.size() && cmp(base[l], base[best]))
            best = l;

        if (r < base.size() && cmp(base[r], base[best]))
            best = r;

        if (best != i) {
            swap(base[best], base[i]);
            downheap(best);
        }
    }

    void upheap()
    {
        size_t idx = base.size() - 1;

        while (idx > 0) {
            size_t p = (idx - 1) / 2;
            if (!cmp(base[idx], base[p]))
                break;
            swap(base[idx], base[p]);
            idx = p;
        }
    }

public:
    void push(int i)
    {
        base.push_back(i);
        upheap();
    }

    void print() const
    {
        int size = 1;
        int count = 0;
        for (size_t i = 1; i <= base.size(); ++i) {
            cout << base[i - 1] << " ";
            count++;

            if (count == size) {
                cout << "\n";
                size = (size << 1);
                count = 0;
            }
        }
    }

    int top()
    {
        int r = base[0];

        swap(base[0], base[base.size() - 1]);
        base.pop_back();
        downheap(0);

        return r;
    }

    bool empty()
    {
        return base.empty();
    }
};

void solution()
{
    int n;
    cin >> n;

    pq<int, less<>> pq;

    while (n--) {
        int in;
        cin >> in;

        if (in == 0) {
            if (pq.empty()) {
                cout << 0 << "\n";
            } else {
                cout << pq.top() << "\n";
            }
        } else {
            pq.push(in);
        }
    }
}

/**
 *------------------------------------------------------------------------------
 *  /$$        /$$$$$$  /$$$$$$$$ /$$      /$$
 * | $$       /$$__  $$|__  $$__/| $$$    /$$$
 * | $$      | $$  \__/   | $$   | $$$$  /$$$$
 * | $$      | $$ /$$$$   | $$   | $$ $$/$$ $$
 * | $$      | $$|_  $$   | $$   | $$  $$$| $$
 * | $$      | $$  \ $$   | $$   | $$\  $ | $$
 * | $$$$$$$$|  $$$$$$/   | $$   | $$ \/  | $$
 * |________/ \______/    |__/   |__/     |__/
 *------------------------------------------------------------------------------
 */
// for local test
void end()
{
#ifdef LOCAL
    cout << ' ';
#else
    cout << '\n';
#endif
}

#ifndef LOCAL
// for online test
int main()
{
    ios_base ::sync_with_stdio(false);
    cin.tie(nullptr);
    // cout.tie(nullptr);
    solution();
}

template <typename T, typename... Args>
void log(const T& first, const Args&... rest)
{
}

#else

#include <unistd.h>

int redirect_to_tty()
{
    int original_stdout_fd = dup(fileno(stdout));

    fclose(stdout);

    if (freopen("/dev/tty", "w", stdout) == NULL) {
        cerr << "tty 장치 파일 열기 오류" << endl;
        return -1;
    }

    return original_stdout_fd;
}

void restore_stdout(int original_stdout_fd)
{
    dup2(original_stdout_fd, fileno(stdout));
}

void log_()
{
}

template <typename T, typename... Args>
void log_(const T& first, const Args&... rest)
{
    cout << first << " ";

    if (sizeof...(rest) > 0) {
        log_(rest...);
    } else {
        cout << "\n";
    }
}

template <typename T, typename... Args>
void log(const T& first, const Args&... rest)
{
    int original_stdout_fd = redirect_to_tty();

    if (original_stdout_fd != -1) {
        log_(first, rest...);
        restore_stdout(original_stdout_fd);
    }
}

// for local test
void _run_test(const int problem_number, const int test_number)
{
    string test = string(to_string(problem_number) + "/test-input-" + to_string(test_number) + ".txt");

    if (freopen(test.c_str(), "r", stdin) == NULL) {
        cout << "file open error" << endl;
        cerr << strerror(errno) << endl;
    }

    string my_answer = string(to_string(problem_number) + "/my-output-" + to_string(test_number) + ".txt");

    if (freopen(my_answer.c_str(), "w", stdout) == NULL) {
        cout << "file open error" << endl;
        cerr << strerror(errno) << endl;
    }

    log("test case - ", test_number);
    solution();
    cout << '\n';
}

int main(int argc, char* argv[])
{
    ios_base ::sync_with_stdio(false);
    cin.tie(nullptr);
    // cout.tie(nullptr);

    int problem_number = 0;
    int test_size = 0;
    int test_target = 0;

    if (argc == 3) {
        problem_number = stoi(argv[1]);
        test_size = stoi(argv[2]);
    } else if (argc == 4) {
        problem_number = stoi(argv[1]);
        test_size = stoi(argv[2]);
        test_target = stoi(argv[3]);
    } else {
        return -1;
    }

    if (test_target == 0) {
        for (int i = 1; i <= test_size; i++) {
            _run_test(problem_number, i);
        }
    } else {
        _run_test(problem_number, test_target);
    }

    return 0;
}
#endif
