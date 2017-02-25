#include <windows.h>

int main()
{
    const char *caption = "Hello";
    const char *msg = "Hello World!";
    //MessageBoxA(GetForegroundWindow(), msg, caption, MB_OK);
#if (defined _WIN32 && defined _M_IX86)
    __asm {
        push MB_OK
        push caption
        push msg
        call GetForegroundWindow
        push eax
        call MessageBoxA
    }
#elif (defined _WIN64 && define _M_AMD64)

#else
    #error "Unsupported on non-x86 architectures"
#endif
    return 0;
}
