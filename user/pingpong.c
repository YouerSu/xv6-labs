#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int ping[2], pong[2];
  pipe(ping);
  pipe(pong);
  if (fork() == 0)
  {
    //replace default IO with pipe
    close(1);
    dup(ping[0]);
    
    close(ping[0]);
    close(ping[1]);
    close(pong[0]);

    char c = ' ';

    read(1, &c, 1);
    fprintf(0 ,"%d: received ping\n", getpid());
    write(pong[1], &c, 1);
    close(pong[1]);
    
  } else
  {
    
    close(1);
    dup(pong[0]);

    close(ping[0]);
    
    close(pong[0]);
    close(pong[1]);

    

    char c = 'a';
    write(ping[1], &c, 1);
    close(ping[1]);

    read(1, &c, 1);
    char* s = "%d: received pong\n";
    fprintf(0 ,s ,getpid());
  }
  
    exit(0);

  
}