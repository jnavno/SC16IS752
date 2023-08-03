#include <stdio.h>

//using namespace std;

int main() {
  long crystal_freq = 1843200; // 3072000Hz (3,072MHz) --- 11059200Hz (11,0592MHz) --- 1843200Hz (1,8432MHz)
  long prescaler = 1;
  long baudrate = 115200;
  long divisor1 = crystal_freq/prescaler;
  long divisor2 = baudrate*16;
  double divisorf = (double)divisor1/(double)divisor2;
  long divisor = divisorf + 0.999;
  printf("divisor1=%ld divisor2=%ld divisor=%ld divisorf=%f\n",
    divisor1, divisor2, divisor, divisorf);

  long actual_baudrate =(divisor1/divisor)/16;
  printf("actual_baudrate=%ld\n", actual_baudrate);
 return (0);
}