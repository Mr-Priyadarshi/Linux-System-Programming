#include <iostream>
#include <cstdlib>
#include <cstdio>
#include <cstring>

// Global variable
int global_var = 42;

// Static variable
static int static_var = 7;

int main() {
    // Local variable
    int local_var = 14;

    // Dynamic memory allocation
    int* dynamic_array = static_cast<int*>(std::malloc(5 * sizeof(int)));

    if (dynamic_array == nullptr) {
        std::cerr << "Memory allocation failed" << std::endl;
        return EXIT_FAILURE;
    }

    for (int i = 0; i < 5; i++) {
        dynamic_array[i] = i * 2;
    }

    std::cout << "Global variable: " << global_var << std::endl;
    std::cout << "Static variable: " << static_var << std::endl;
    std::cout << "Local variable: " << local_var << std::endl;
    std::cout << "Dynamic array: ";

    for (int i = 0; i < 5; i++) {
        std::cout << dynamic_array[i] << " ";
    }

    std::cout << std::endl;

    // Free dynamically allocated memory
    std::free(dynamic_array);

    return EXIT_SUCCESS;
}
