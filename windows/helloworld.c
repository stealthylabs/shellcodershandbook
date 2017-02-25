#include <windows.h>

#ifdef _WIN64
void hello_world_x64();
#endif

int main()
{
    //MessageBoxA(GetForegroundWindow(), msg, caption, MB_OK);
#if (defined _WIN32 && defined _M_IX86)
    const char *caption = "Hello 32-bit";
    const char *msg = "Hello World!";
    __asm {
        push MB_OK
        push caption
        push msg
        call GetForegroundWindow
        push eax
        call MessageBoxA
    }
#elif (defined _WIN64 && defined _M_AMD64)
    hello_world_x64();
#else
    #error "Unsupported on non-x86 architectures"
#endif
    return 0;
}
