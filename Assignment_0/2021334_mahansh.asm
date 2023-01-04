global main
extern scanf
extern printf

segment .data ;initialised data
    int_format_specifier: db "%d", 0
    string_format_specifier: db "%s", 0
    string_input times 100 db 0

segment .bss ; uninitialised data 
    int_input resb 4

segment .text
    main:
        push rbp ; making the stack frame for main fucntiom
        mov rbp, rsp ; setting base pointer to stack fram
        sub rsp, 16 ; making space for variables in stack

        lea rdi, [int_format_specifier] ; storing formate specifier's address in rdi [ first arguement]
        lea rsi, [int_input] ; storing int's address in rsi register [ second arguement]
        call scanf

        lea rdi, [int_format_specifier] ; storing formate specifier's address in rdi [ first arguement]
        mov edx, [int_input] ; storing int's address in rsi register [ second arguement]
        call printf
        
        lea rdi, [string_format_specifier] ; storing formate specifier's address in rdi [ first arguement]
        lea rsi, [string_input] ; storing string's address in rsi register [ second arguement]
        call scanf

        lea rdi, [string_format_specifier] ; storing formate specifier's address in rdi [ first arguement]
        lea rsi, [string_input] ; storing string's address in rsi register [ second arguement]
        call printf

        add rsp, 16
        mov eax, 0 ; making sure that eax is set to zero since eax is reserved for return values of a function
        leave
        ret