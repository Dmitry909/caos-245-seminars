#include <cassert>
#include <cstddef>
#include <dlfcn.h>
#include <iostream>

int main() {
    auto lib = dlopen("libm.so.6", RTLD_NOW);
    assert(lib != nullptr);

    auto sin = reinterpret_cast<double (*)(double)>(dlsym(lib, "sin"));
    assert(sin != nullptr);
    std::cout << sin(1) << std::endl;
    dlclose(lib);
}
