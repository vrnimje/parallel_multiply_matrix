#include <hpx/algorithm.hpp>
#include <hpx/execution.hpp>
#include <hpx/hpx_main.hpp>
#include <hpx/iostream.hpp>

#include <cstddef>
#include <iostream>
#include <random>
#include <vector>

std::mt19937 gen;

void print_matrix(const std::vector<int>& X, const std::string& name, const int& r, const int& c) {
    std::cout << "\nMatrix " << name << std::endl;
    for (int i=0; i<r; i++) {
        for (int j=0; j<c; j++) {
            std::cout << X[i * c + j] << " ";
        }
        std::cout << "\n";
    }
}

int main() {
    std::vector<int> A(4 * 5);
    std::vector<int> B(5 * 4);
    std::vector<int> R(4 * 4);

    unsigned int seed = std::random_device{}();
    gen.seed(seed);
    std::cout << "Seed: " << seed << std::endl;

    int const l = 1, r = 100;

    std::uniform_int_distribution<int> distro(l, r);
    auto generator = std::bind(distro, gen);
    hpx::ranges::generate(A, generator);
    hpx::ranges::generate(B, generator);

    hpx::experimental::for_loop(hpx::execution::par, 0, 4, [&](auto i) {
        hpx::experimental::for_loop(0, 4, [&](auto j) {
            R[i * 4 + j] = 0;
            hpx::experimental::for_loop(0, 5, [&](auto k) {
                R[i * 4 + j] += A[i * 5 + k] * B[k * 4 + j];
            });
        });
    });

    print_matrix(A, "A", 4, 5);
    print_matrix(B, "B", 5, 4);
    print_matrix(R, "R", 4, 4);
    
    return 0;
}