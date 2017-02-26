_TEXT SEGMENT

PUBLIC check_ntglobal_flag

check_ntglobal_flag PROC

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
check_ntglobal_flag ENDP

_TEXT ENDS

END

