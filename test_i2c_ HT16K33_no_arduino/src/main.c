#include <avr/io.h>
#include <util/delay.h>
#include <USI_TWI_Master.h>

#define set(x) |= (1<<x)
#define clr(x) &=~(1<<x) 
#define inv(x) ^=(1<<x)


void setupAttiny() {
}

void loopAttiny() {
  for(;;) {
  }
}

int main() {
  setupAttiny();
  loopAttiny();
}
