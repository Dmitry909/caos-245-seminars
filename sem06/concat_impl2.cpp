# 0 "examples/build_2_cpp/concat_impl.cpp"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/usr/include/stdc-predef.h" 1 3 4
# 0 "<command-line>" 2
# 1 "examples/build_2_cpp/concat_impl.cpp"
# 1 "examples/build_2_cpp/headers.h" 1
char* concat(const char* a, const char* b, char* buf);
# 2 "examples/build_2_cpp/concat_impl.cpp" 2

char* concat(const char* a, const char* b, char* buf) {
    char* result = buf;

    while (*a) {
        *buf = *a;
        ++a;
        ++buf;
    }
    while (*b) {
        *buf = *b;
        ++b;
        ++buf;
    }
    *buf = 0;

    return result;
}
