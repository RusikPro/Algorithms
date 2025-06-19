#include <iostream>
#include <vector>
#include <string>
#include <type_traits>

using namespace std;

// --- User-defined types to explore size/alignment ---

// 1. Empty struct
struct Empty {};

// 2. Single-member structs
struct CharOnly    { char c;            };
struct IntOnly     { int i;             };

// 3. Mixed members (padding in action)
struct MixedA      { char c; int i;     };
struct MixedB      { int i; char c;     };

// 4. Virtual function → adds vptr
struct WithVirtual { virtual void f(){}; };

// 5. Inheritance (no virtual)
struct Base        { int i;             };
struct Derived     : Base { char c;       };

// 6. Virtual inheritance
struct VBase       { int i;             };
struct VI         : virtual VBase { int j; };

// 7. Bit-fields
struct Bitfields   {
    unsigned a : 1;
    unsigned b : 3;
    unsigned c : 4;
};

// 8. Over-aligned type
struct alignas(16) OverAligned { double d[2]; };

// --- Helper to print size and alignment in one go ---

template<typename T>
void printInfo(const string& name) {
    cout << name
        << "\t: sizeof = " << sizeof(T)
        << ", alignof = " << alignof(T)
        << "\n";
}

int main() {
    cout << "=== Fundamental Types ===\n";
    printInfo<bool>("bool");
    printInfo<char>("char");
    printInfo<short>("short");
    printInfo<int>("int");
    printInfo<long>("long");
    printInfo<long long>("long long");
    printInfo<float>("float");
    printInfo<double>("double");
    printInfo<void*>("void* (pointer)");

    cout << "\n=== Enums ===\n";
    enum Color { Red, Green, Blue };
    enum class EColor : uint8_t { Red, Green, Blue };
    printInfo<Color>("Color (unscoped enum)");
    printInfo<EColor>("EColor (enum class : uint8_t)");

    cout << "\n=== Standard Library ===\n";
    printInfo<string>("std::string");
    printInfo<vector<int>>("std::vector<int>");

    cout << "\n=== User-Defined Types ===\n";
    printInfo<Empty>("Empty");
    printInfo<CharOnly>("CharOnly { char }");
    printInfo<IntOnly>("IntOnly  { int }");
    printInfo<MixedA>("MixedA { char; int }");
    printInfo<MixedB>("MixedB { int; char }");
    printInfo<WithVirtual>("WithVirtual (has vptr)");
    printInfo<Base>("Base { int }");
    printInfo<Derived>("Derived : Base + char");
    printInfo<VI>("VI : virtual VBase + int");
    printInfo<Bitfields>("Bitfields {1+3+4 bits}");
    printInfo<OverAligned>("OverAligned (alignas(16))");

    return 0;
}
