#include <chrono>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <cmath>
#include <cppsim/state.hpp>
#include <cppsim/circuit.hpp>
#include <cppsim/observable.hpp>
#include <cppsim/gate_factory.hpp>
#include <cppsim/gate_merge.hpp>
#include "utils.h"

using std::chrono::high_resolution_clock;
using std::chrono::duration_cast;
using std::chrono::duration;
using std::chrono::microseconds;

void ry(int n) {
    auto t1 = high_resolution_clock::now();
    QuantumState state(n);
    state.set_zero_state();

    for (int i = 0; i < n; i++) {
        gate::to_matrix_gate(gate::RY(i, 1.0))->update_quantum_state(&state);
    }

    auto t2 = high_resolution_clock::now();
    auto us_int = duration_cast<microseconds>(t2 - t1);
    std::cout << FormatWithCommas(us_int.count()) << "\n";

    // const CPPCTYPE* raw_data_cpp = state.data_cpp();
    // for (int i = 0; i < std::min(16, (1 << n)); i++) {
    //     std::cout << raw_data_cpp[i] << std::endl;
    // }
}

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <num-qubits>" << std::endl;;
        return EXIT_FAILURE;
    }

    int n = std::stoi(argv[1]);
    ry(n);

    return EXIT_SUCCESS;
}
