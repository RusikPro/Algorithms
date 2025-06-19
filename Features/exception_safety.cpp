#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <stdexcept>

// A simple class holding a vector of ints, with methods demonstrating different guarantees.
class DataHolder {
    std::vector<int> data_;
public:
    DataHolder(std::initializer_list<int> init) : data_(init) {}

    void print(const char* title) const {
        std::cout << title << ":";
        for (int v : data_) std::cout << " " << v;
        std::cout << "\n";
    }

    // 1) No exception-safety guarantee
    // May throw, leave object in an arbitrary, possibly invalid state.
    void noGuarantee(int newValue)
    {
        // Suppose push_back may throw, and we also modify another member before that:
        data_[0] = newValue;         // could be out-of-range -> UB
        data_.push_back(newValue);   // may throw bad_alloc
        // If bad_alloc happens, data_[0] has already been changed.
    }

    // 2) Basic guarantee
    // On exception, object remains in a valid state (no leaks, invariants hold),
    // but may have been modified.
    void basicGuarantee(int newValue)
    {
        // We make changes in-place but ensure vector always remains valid:
        data_.push_back(newValue);    // may throw, but vector stays valid on throw
        // If we need multiple steps, make sure each intermediate step leaves
        // data_ valid.
        // e.g., swapping elements safely:
        if (data_.size() >= 2) {
            std::swap(data_[0], data_[1]);  // no-throw swap of ints
        }
    }

    // 3) Strong (roll-back) guarantee
    // Either completes fully or has no effect on the object.
    void strongGuarantee(int newValue) {
        // Make a copy first:
        std::vector<int> backup = data_;     // may throw; if it does, data_ untouched
        try {
            data_.push_back(newValue);       // may throw
            // … other operations that might throw …
        }
        catch (...) {
            data_ = std::move(backup);       // roll back
            throw;                           // rethrow
        }
    }

    // 4) No-throw (nothrow) guarantee
    // Guarantees never to throw; strongest guarantee.
    void noThrowGuarantee(int newValue) noexcept {
        // Use only operations known not to throw:
        // reserve enough capacity once to avoid reallocation:
        data_.reserve(data_.size() + 1); // may throw, but if we assume reserve succeeded earlier
        data_.push_back(newValue);       // push_back on reserved space does not throw
    }
};

int main() {
    DataHolder d{1,2,3};
    d.print("Original");

    // 1) noGuarantee
    try {
        d.noGuarantee(42);
        d.print("After noGuarantee");
    } catch (...) {
        std::cout << "noGuarantee threw, state may be corrupted\n";
        d.print("State after noGuarantee failure");
    }

    // Reset
    d = DataHolder{1,2,3};

    // 2) basicGuarantee
    try {
        d.basicGuarantee(42);
        d.print("After basicGuarantee");
    } catch (...) {
        std::cout << "basicGuarantee threw, but object still valid\n";
        d.print("State after basicGuarantee failure");
    }

    // Reset
    d = DataHolder{1,2,3};

    // 3) strongGuarantee
    try {
        d.strongGuarantee(42);
        d.print("After strongGuarantee");
    } catch (...) {
        std::cout << "strongGuarantee threw, but rolled back\n";
        d.print("State after strongGuarantee failure");
    }

    // 4) noThrowGuarantee
    d.noThrowGuarantee(42);
    d.print("After noThrowGuarantee");

    return 0;
}
