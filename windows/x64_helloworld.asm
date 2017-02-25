_DATA SEGMENT

msg db "Hello World!", 0
caption db "Hello 64-bit", 0

_DATA ENDS

_TEXT SEGMENT

EXTERN MessageBoxA: PROC
EXTERN GetForegroundWindow: PROC

PUBLIC hello_world_x64

hello_world_x64 PROC

push rbp ; save frame pointer
mov rbp, rsp ; fix stack pointer
sub rsp, 8 * (4 + 2) ; allocate shadow register area + 2 QWORDs for stack alignment

call GetForegroundWindow
mov rcx, rax
mov rdx, offset msg
mov r8, offset caption
mov r9, 0; MB_OK
and rsp, not 8; align stack to 16 bytes prior to call
call MessageBoxA

mov rsp, rbp ; restore stack pointer
pop rbp ; restore frame pointer
ret ; return to caller
hello_world_x64 ENDP

_TEXT ENDS

END

