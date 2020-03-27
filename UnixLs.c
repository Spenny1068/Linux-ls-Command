#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <limits.h>

/* helper functions */
char* format_date(char* str, time_t val);

int main(int argc, char* argv[]) {

    /* check command line arguments */
    if (argc < 2) {
        printf("Usage: %s [-il] [directory]\n", argv[0]);
        return 0;
    }

    int iflag = 0;
    int lflag = 0;
    int option = 0;

    opterr = 0;

    /* get ls options */
    while ((option = getopt(argc, argv, "il:")) != -1) {
        switch (option) {

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

    char fullpath[PATH_MAX + 1];
    char* dir = NULL;
    struct dirent* pDirent = NULL;
    DIR* pDir = NULL;
    struct stat fileStat;
    char mtime[36];

    /* get directory from command-line */
    dir = argv[argc - 1];
    printf ("iflag = %d, lflag = %d, dir = %s\n", iflag, lflag, dir);

    /* open directory */
    pDir = opendir(dir);
    if (pDir == NULL) {
        printf ("Cannot open directory '%s'\n", dir);
        return 0;
    }

    /* iteratively read the directory */
    while ((pDirent = readdir(pDir)) != NULL) {

        /* ignore hidden files */
        if (pDirent->d_name[0] == '.') { continue; }

        /* build full path */
        realpath(dir, fullpath);
        strncat(fullpath, "/", 1);
        strncat(fullpath, pDirent->d_name, sizeof(pDirent->d_name) + 1);

        /* if its a directory, append */
        if (S_ISDIR(fileStat.st_mode)) {
            strncat(fullpath, "/", 1);
        }

        /* get info for this path */
        if (stat(fullpath, &fileStat) == -1) {
            printf("Stat error.\n");
            continue;
        }

        if (iflag == 1) {
            /* file inode */
            printf("%llu  ", fileStat.st_ino);
        }

        if (lflag == 1) {
            /* file permissions */
            printf((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
            printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
            printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
            printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
            printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
            printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
            printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
            printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
            printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
            printf((fileStat.st_mode & S_IXOTH) ? "x  " : "-  ");

            /* number of links */
            printf("%2d  ",fileStat.st_nlink);

            /* user name of file owner */
            printf("%2d  ", fileStat.st_uid);

            /* group name */
            printf("%3d  ", fileStat.st_gid);

            /* date of last modification */
            printf("%17s  ", format_date(mtime, fileStat.st_mtime));

            /* file size */
            printf("%4lld  ",fileStat.st_size);

        }

        /* file name */
        printf("%s", pDirent->d_name);

        /* symbolic link */
        printf("\t%s symbolic\n", (S_ISLNK(fileStat.st_mode)) ? "is" : "is not");
    }
    closedir (pDir);
    return 0;
}

/* mmm dd yyyy hh:mm */
char* format_date(char* str, time_t val) {
    strftime(str, 36, "%b %d %Y %H:%M", localtime(&val));
    return str;
}
