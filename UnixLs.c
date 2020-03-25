#include "list.h"
#include <stdio.h>
#include <sys/stat.h>
#include <dirent.h>

int main(int argc, char* argv[]) {

    /* check command line arguments */
    if (argc < 2) {
        printf("Usage: %s ls\n", argv[0]);
        return 0;
    }

    struct dirent* pDirent = NULL;
    DIR* pDir = NULL;

    pDir = opendir (argv[1]);
    if (pDir == NULL) {
        printf ("Cannot open directory '%s'\n", argv[1]);
        return 1;
    }

    while ((pDirent = readdir(pDir)) != NULL) {
        printf ("[%s]\n", pDirent->d_name);
    }
    closedir (pDir);

    return 0;
}

