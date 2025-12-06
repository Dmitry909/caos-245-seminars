.intel_syntax noprefix
.section .text

.global pref
pref: # void calcPrefixSum(const uint64_t* from, size_t n, uint64_t* to) rdi, rsi, rdx
    add rsi, 0 # ZF
    jz go_away
    mov QWORD PTR [rdx], QWORD PTR [rdi]
    mov rcx, 1 # i

loop:
    cmp rcx, rsi
    jge go_away
    mov rax, QWORD PTR [rdx + 8 * rcx - 8]
    add rax, QWORD PTR [rdi + 8 * rcx]
    mov QWORD PTR [rdx + 8 * rcx], rax
    add rcx, 1
    jmp loop


go_away:
    ret
