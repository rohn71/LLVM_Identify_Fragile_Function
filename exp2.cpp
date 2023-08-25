#include <iostream>
#include <cstring>

// A fragile function that causes a buffer overflow
void fragileBufferOverflow() {
    char buffer[5];
    strcpy(buffer, "Hello, World!");
    std::cout << "Buffer: " << buffer << std::endl;
}

// A fragile function that causes a memory leak
void fragileMemoryLeak() {
    int* data = new int[100];
    // Oops, forgot to delete the allocated memory!
}

// A fragile function that exhibits undefined behavior
void fragileUndefinedBehavior() {
    int* ptr = nullptr;
    *ptr = 42; // Dereferencing a null pointer, leading to undefined behavior
}

// A fragile function that may cause a division by zero
int fragileDivisionByZero(int x, int y) {
    return x / y; // Potential division by zero
}

// A fragile function that returns a reference to a local variable
int& fragileReturnReferenceToLocal() {
    int value = 42;
    return value; // Returning a reference to a local variable
}

int main() {
    std::cout << "Fragile Function Examples" << std::endl;

    fragileBufferOverflow();

    fragileMemoryLeak();

    fragileUndefinedBehavior();

    int result = fragileDivisionByZero(10, 0); // Potential division by zero

    int& ref = fragileReturnReferenceToLocal(); // Reference to a local variable, leads to undefined behavior

    return 0;
}

