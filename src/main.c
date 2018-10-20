#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>


void print_help(char** argv){

    printf("\nUse this binary to search what pkg provides a binary\n");
    printf("\ni.e.:\n");
    printf("\n    %s /usr/bin/ls\n\n",argv[0]);

}

int main (int argc, char** argv){

    const char *fname = "/etc/dnf.conf";
    if( access( fname, F_OK ) != -1 ) {
        if (argc>=2){
        char *const parmlist[] = {"/usr/bin/dnf-3", "--releasever=clear",\
            "--config=/etc/dnf.conf","provides",argv[1],NULL};
        execv("/usr/bin/dnf-3",parmlist);
        } else{
            print_help(argv);
            return -1;
        }
    } else {
        perror("dnf.does not exist in /etc/, please copy there");
        return -1;
    }


    return 0;

}

