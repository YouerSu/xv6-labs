#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void 
primes(int  p[2])
{
    close(1);
    dup(p[0]);
    close(p[0]);
    close(p[1]);

    int p_number = 2;
    int pass_number = -1;
    short pipe_exist = 0;
    
    char* to_print = "prime %d\n";

    fprintf(0, to_print, p_number);

    while (pass_number < 35)
    {
        read(1, &pass_number, sizeof(pass_number));
        if (pass_number > 0 && (pass_number % p_number) != 0)
        {
            if (pipe_exist == 1)
            {
                write(0, &pass_number, sizeof(pass_number));
            }else{
                int pass[2];
                pipe(pass);
                if (fork() == 0)
                {
                    close(1);
                    dup(pass[0]);
                    close(pass[0]);
                    close(pass[1]);
                    p_number = pass_number;
                    
                    fprintf(0, to_print, p_number);
                } else {
                    pipe_exist = 1;

                    close(0);
                    dup(pass[1]);
                    close(pass[0]);
                    close(pass[1]);
                    // continue;
                }
                
            }
            
        }
    }
    
    if (pipe_exist == 1)
    {
        write(0, &pass_number, sizeof(pass_number));
    }
}

int
main(int argc, char *argv[])
{
    int p[2];
    pipe(p);

    if (fork() == 0)
    {
        primes(p);
        
    }else{
        close(0);
        dup(p[1]);
        close(p[0]);
        close(p[1]);
        int i;
        for (i = 2; i <= 35; ++i)
        {

            write(0, &i, sizeof(i));

        }
    }

    wait(0);
    exit(0);
}