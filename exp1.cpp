#include <iostream>

// Fragile function example
int fragileFunction(int x, int y) {
    int result = x * y;
    return result;
}

int main() {
    int a = 5;
    int b = 10;
    int result = fragileFunction(a, b);

    std::cout << "Result: " << result << std::endl;
    return 0;
}

