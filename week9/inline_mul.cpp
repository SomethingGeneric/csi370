#include <iostream>

// Matt C 11/12/25
// CSI 370 w/ Brian Hall
// Assignment 9.1 Inline ASM multiply/divide helper

int main() {
    float first = 0.0f;
    float second = 0.0f;

    std::cout << "Enter two floating point numbers: ";
    std::cin >> first >> second;

    if (!std::cin) {
        std::cerr << "Invalid input.\n";
        return 1;
    }

    float product = 0.0f;
    float half = 0.0f;
    float scaled = 0.0f;
    const float two = 2.0f;

    asm volatile(
        "movss %1, %%xmm0\n\t"   // xmm0 = first
        "movss %2, %%xmm1\n\t"   // xmm1 = second
        "mulss %%xmm1, %%xmm0\n\t" // xmm0 *= xmm1
        "movss %%xmm0, %0\n\t"   // product = xmm0
        : "=m"(product)
        : "m"(first), "m"(second)
        : "xmm0", "xmm1"
    );

    asm volatile(
        "movss %1, %%xmm0\n\t"   // xmm0 = product
        "divss %2, %%xmm0\n\t"   // xmm0 /= 2.0f
        "movss %%xmm0, %0\n\t"   // half = xmm0
        : "=m"(half)
        : "m"(product), "m"(two)
        : "xmm0"
    );

    asm volatile(
        "movss %1, %%xmm0\n\t"    // xmm0 = half
        "movss %2, %%xmm1\n\t"    // xmm1 = first
        "mulss %%xmm1, %%xmm0\n\t" // xmm0 *= first
        "movss %%xmm0, %0\n\t"    // scaled = xmm0
        : "=m"(scaled)
        : "m"(half), "m"(first)
        : "xmm0", "xmm1"
    );

    std::cout << "Input A: " << first << '\n';
    std::cout << "Input B: " << second << '\n';
    std::cout << "Product (A * B): " << product << '\n';
    std::cout << "Half of product: " << half << '\n';
    std::cout << "Half * Input A: " << scaled << '\n';

    return 0;
}
