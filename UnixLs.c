#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <stdio.h>

int main(int argc, char* argv[]) {

    /* check command line arguments */
    if (argc < 3) {
        printf("Usage: %s [-il] [directory]\n", argv[0]);
        return 0;
    }

    int iflag = 0;
    int lflag = 0;
    int c;

    opterr = 0;

    /* get ls options */
    while ((c = getopt (argc, argv, "il:")) != -1) {
        switch (c) {

        case 'l':
            lflag = 1;
            break;

        case 'i':
            iflag = 1;
            break;

        /* unknown option */
        case '?':
            if (isprint (optopt)) { printf ("Unknown option `-%c'.\n", optopt); }
            else { printf ("Unknown option character `\\x%x'.\n", optopt); }
            return 1;
        }
    }

    char* dir = NULL;
    struct dirent* pDirent = NULL;
    DIR* pDir = NULL;

    /* get directory */
    dir = argv[argc - 1];
    printf ("iflag = %d, lflag = %d, dir = %s\n", iflag, lflag, dir);

    pDir = opendir (dir);
    if (pDir == NULL) {
        printf ("Cannot open directory '%s'\n", dir);
        return 0;
    }

    while ((pDirent = readdir(pDir)) != NULL) {
        printf ("[%s]\n", pDirent->d_name);
    }
    closedir (pDir);

    return 0;
}

