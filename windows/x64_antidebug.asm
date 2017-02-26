_TEXT SEGMENT

PUBLIC x64_get_ntglobal_flag, x64_get_process_heap

x64_get_ntglobal_flag PROC

push rbp ; save frame pointer
mov rbp, rsp ; fix stack pointer
sub rsp, 8 * 2 ; allocate 2 QWORDs for stack alignment

mov rax, gs:[60h] ; Process Environment Block
mov al, [rax + 0BCh] ; NtGlobalFlag
and al, 70h
cmp al, 70h
je LABEL2
LABEL1:
xor rax, rax
jmp LABEL3
LABEL2:
mov rax, 1h
LABEL3:
mov rsp, rbp ; restore stack pointer
pop rbp ; restore frame pointer
ret ; return to caller
x64_get_ntglobal_flag ENDP


x64_get_process_heap PROC
push rbp
mov rbp, rsp
sub rsp, 8 * 2
mov rax, gs:[60h]
mov rax, [rax + 30h]
mov rsp, rbp
pop rbp
ret
x64_get_process_heap ENDP

_TEXT ENDS

END

