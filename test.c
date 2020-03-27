#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>
#include <stdio.h>

int main(int argc, char* argv[]) {

    /* open directory */
    pDir = opendir();
    if (pDir == NULL) {
        printf ("Cannot open directory '%s'\n", dir);
        return 0;
    }

    while ((pDirent = readdir(pDir)) != NULL) {

        /* get info for this path */
        if (stat(, &fileStat) == -1) {
            printf("Stat error.\n");
            return 0;
        }

        /* ignore hidden files */
        /* if (pDirent->d_name[0] == '.') { continue; } */

        /* regular file */
        if (S_ISREG(fileStat.st_mode)) {

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
        }

        /* directory */
        else if (S_ISDIR(fileStat.st_mode)) {
                /* printf("directory\n"); */
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
