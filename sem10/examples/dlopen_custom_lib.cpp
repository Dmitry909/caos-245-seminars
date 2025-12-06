#include <cassert>
#include <cstddef>
#include <cstdint>
#include <dlfcn.h>
#include <iostream>

int main() {
    void *lib = dlopen("./local.so", RTLD_NOW);
    if (lib == nullptr) {
        std::cout << "Failed to open local.so" << std::endl;
        return 1;
    }

    uint64_t* value = reinterpret_cast<uint64_t*>(dlsym(lib, "value"));
    assert(value != nullptr);

    auto write_value = reinterpret_cast<void (*)(uint64_t)>(dlsym(lib, "write_value"));
    assert(write_value != nullptr);

    std::cout << "Value is " << *value << std::endl;
    write_value(123);
    std::cout << "Value is " << *value << std::endl;

    dlclose(lib);
}
