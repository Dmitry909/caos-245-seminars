#include <iostream>
#include <cstdint>

uint64_t SumAsm(uint64_t* p, size_t n) {
    // a - rax
    // b - rbx
    // c - rcx
    // d - rdx
    // D - rdi
    // S - rsi
    /*
    int rcx = 0;//i
    int rdx = 0;//res
    begin
    if(i >=n) {
    jmp end
    }
    rdx += p[i]
    i++
    jmp begin
    end
    */
    uint64_t res = 0;
    asm volatile(R"(
        .intel_syntax noprefix
        mov rcx, 0
        mov rdx, 0
        begin:
            cmp rcx, rbx
            je end
            add rdx, [rax + 8 * rcx]
            add rcx, 1
            jmp begin
        end:
        .att_syntax
        )"
        :
        "=&d"(res)
        :
        "a"(p),
        "b"(n)
        :"rcx");
    return res;
}

int main() {
    uint64_t a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    std::cout << SumAsm(a, 10) << std::endl;
}
