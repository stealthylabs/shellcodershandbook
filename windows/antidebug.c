#include <windows.h>
#include <stdio.h>
#if (defined _WIN32 && defined _M_IX86)
#define USE_X86_INLINE
#elif (defined _WIN64 && defined _M_AMD64)
#define USE_X64_CALL
#endif

#ifdef USE_X64_CALL
extern int x64_get_ntglobal_flag();
extern HANDLE x64_get_process_heap();
#endif

int get_ntglobalflag()
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
        if (flag == 0 && flag32on64 != 0)
            flag = flag32on64;
    }
#endif
#ifdef USE_X64_CALL
    flag = x64_get_ntglobal_flag();
#endif 
    return flag;
}

HANDLE get_process_heap()
{
    HANDLE heap;
#ifdef USE_X86_INLINE
    BOOL iswow64 = FALSE;
    __asm {
        mov eax, fs:[0x30] ; Process Environment Block
        mov eax, [eax + 0x18] ; ProcessHeap pointer 
        mov heap, eax
    }
    /* this doesn't work */
    if (IsWow64Process(GetCurrentProcess(), &iswow64) && iswow64) {
        HANDLE heap32on64;
        __asm {
            mov eax, fs:[0x30] ; Process Environment Block
            mov eax, [eax + 0x1030] ; ProcessHeap pointer
            mov heap32on64, eax
        }
        printf("heap32on64: %p\n", heap32on64);
    }
#endif
#ifdef USE_X64_CALL
    heap = x64_get_process_heap();
#endif
    return heap;
}

int main()
{
    int ntglobalflag = get_ntglobalflag();
    HANDLE heap = get_process_heap();
    printf("NtGlobalFlag: %d\n", ntglobalflag);
    printf("GetProcessHeap(): %p\n", GetProcessHeap());
    printf("ProcessHeap: %p\n", heap);
    
    return 0;
}
