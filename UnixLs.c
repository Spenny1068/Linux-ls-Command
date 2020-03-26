#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>
#include <stdio.h>

/* helper functions */
char* format_date(char* str, time_t val);

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
    struct stat fileStat;
    char mtime[36];

    /* get directory */
    dir = argv[argc - 1];
    printf ("iflag = %d, lflag = %d, dir = %s\n", iflag, lflag, dir);

    /* open directory */
    pDir = opendir(dir);
    if (pDir == NULL) {
        printf ("Cannot open directory '%s'\n", dir);
        return 0;
    }

    while ((pDirent = readdir(pDir)) != NULL) {

        /* ignore hidden files */
        if (pDirent->d_name[0] == '.') { continue; }

        /* get file info */
        if (stat(pDirent->d_name, &fileStat) < 0) {
            printf("stat error\n");
            return 0;
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
            printf("%d  ",fileStat.st_nlink);

            /* user name of file owner */
            printf("%d  ", fileStat.st_uid);

            /* group name */
            printf("%d  ", fileStat.st_gid);

            /* date of last modification */
            printf("%s  ", format_date(mtime, fileStat.st_mtime));

            /* file size */
            printf("%lld  ",fileStat.st_size);
        }

        /* file name */
        printf("%s  ", pDirent->d_name);

        /* symbolic link */
        printf("\t%s a symbolic link\n", (S_ISLNK(fileStat.st_mode)) ? "is" : "is not");
    }

    closedir (pDir);
    return 0;
}

/* mmm dd yyyy hh:mm */
char* format_date(char* str, time_t val) {
    strftime(str, 36, "%b %d %Y %H:%M", localtime(&val));
    return str;
}
