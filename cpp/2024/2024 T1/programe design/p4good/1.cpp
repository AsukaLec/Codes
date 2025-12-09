#include <iostream>
#include <vector>

class Joseph {
public:
    Joseph(int n, int m, int k) : n(n), m(m), start(k) {}

    std::vector<int> simulate() {
        std::vector<int> people(n);
        for (int i = 0; i < n; i++) {
            people[i] = i + 1;
        }

        int current = start - 1;
        while (n > 0) {
            current = (current + m - 1) % n;
            std::cout << people[current] << " ";
            people.erase(people.begin() + current);
            n--;
        }
        std::cout << std::endl;
        return people;
    }

private:
    int n;
    int m;
    int start;
};
int main() {
    int n, m, k;
    std::cin >> n >> m >> k;
    Joseph obj(n, m, k);
    obj.simulate();
    return 0;
}