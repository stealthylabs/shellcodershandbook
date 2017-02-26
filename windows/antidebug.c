#include <windows.h>
#include <stdio.h>
#if (defined _WIN32 && defined _M_IX86)
#define USE_X86_INLINE
#elif (defined _WIN64 && defined _M_AMD64)
#define USE_X64_CALL
#endif

int main()
{
    int flag = 0;
#ifdef USE_X86_INLINE
    BOOL iswow64 = FALSE;
    __asm {
        mov eax, fs:[0x30] ; Process Environment Block
        mov al, [eax + 0x68]; NtGlobalFlag
        and al, 0x70
        cmp al, 0x70
        je label1
        xor eax, eax
        mov flag, eax
        jmp endlabel1
    label1:
        xor eax, eax
        inc eax
        mov flag, eax
    endlabel1:
    }
    if (IsWow64Process(GetCurrentProcess(), &iswow64) && iswow64) {
        int flag32on64 = 0;
        __asm {
            mov eax, fs:[0x30] ; Process Environment Block
            mov al, [eax + 0x10bc]; NtGlobalFlag in 64-bit PEB
            and al, 0x70
            cmp al, 0x70
            je label2
            xor eax, eax
            mov flag, eax
            jmp endlabel2
        label2:
            xor eax, eax
            inc eax
            mov flag32on64, eax
        endlabel2:
        }
        printf("flag32on64: %d\n", flag32on64);
    }
#endif
#ifdef USE_X64_CALL
    flag = check_ntglobal_flag();
#endif 
    printf("flag: %d\n", flag);
    return 0;
}
