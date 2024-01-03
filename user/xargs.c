#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{

    for (int i = 0; i < argc-1; i++)
    {
        argv[i] = argv[i+1];
    }
    

    char buf[512], *p;

    p = buf;
    while (read(0, p, sizeof(char)))
    {
        
        if (*p == '\n')
        {
            
            p[0] = 0;
            p = buf;
            argv[argc-1] = buf;
            if (fork() == 0)
            {
                exec(argv[0], argv);    
            }else{
                wait(0);
            }
            
        }else 
        {
            p++;
        }
        
    }

    
    // for (int i = 0; i < argc; i++)
    // {
    //     printf("%s\n", argv[i]);        
    // }
    exit(0);
    
}