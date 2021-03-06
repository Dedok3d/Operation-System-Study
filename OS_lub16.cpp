#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
static struct termios stored_settings;

void set_keypress(void)
{
  struct termios new_settings;

  tcgetattr(0,&stored_settings);

  new_settings = stored_settings;
  /*
     Отключение канонического режима и вывода на экран
     и установка буфера ввода размером в 1 байт
  */
  new_settings.c_lflag &= (~ICANON & ~ECHO);
  new_settings.c_cc[VTIME] = 0;
  new_settings.c_cc[VMIN] = 1;

  tcsetattr(0,TCSANOW,&new_settings);
  return;
}

void reset_keypress(void)
{
  tcsetattr(0,TCSANOW,&stored_settings);
  return;
}

int main(void)
{
  set_keypress();
   char n;
  printf("You're an idiot?  ");

     // putchar здесь вызывается для того, чтобы проверить работоспособность
     n = putchar(getchar());
  printf(" \n");
  if((n!='y') && (n!='n')){
     printf("No correct symbol!\n");
     reset_keypress();
     return 0;
  }
     printf("Oh, really?\n");
  reset_keypress();
  return 0;
}
