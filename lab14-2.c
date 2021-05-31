#include <signal.h>
#include <stdio.h>

void my_handler(int nsig) {
  if(nsig == SIGINT)
    printf("CTRL + С is pressed");
  else if(nsig == SIGQUIT)
    printf("CTRL + 4 is pressed");
}

int main(void) {
  (void)signal(SIGINT, my_handler);
  (void)signal(SIGQUIT, my_handler);

  while(1);
  return 0;
}
