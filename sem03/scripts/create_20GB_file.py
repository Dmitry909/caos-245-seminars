total_size = 20 * 10**9
one_print = 2 * 10**6
str = 'a' * one_print
for i in range(total_size // one_print):
    print(str, end='')
