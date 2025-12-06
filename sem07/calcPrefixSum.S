.intel_syntax noprefix
.section .note.GNU-stack
.section .text

.global calcPrefixSum
# calcPrefixSum(const uint64_t* arr, size_t n, uint64_t* prefix_sum)
calcPrefixSum: # rdi = arr, rsi = n, rdx = prefix_sum
    test rsi, rsi
    jz Ret
    mov rax, 0 # rax - индекс в массиве
    mov rcx, QWORD PTR [rdi] # rcx = текущая префиксная сумма, поддерживаем ее и кладем в prefix_sum
    mov QWORD PTR [rdx], rcx # положили первый элемент в prefix_sum
Loop:
    add rax, 1
    cmp rax, rsi
    je Ret # i==n => return
    add rcx, QWORD PTR [rdi + rax * 8]
    mov QWORD PTR [rdx + rax * 8], rcx
    jmp Loop
Ret:
    ret
