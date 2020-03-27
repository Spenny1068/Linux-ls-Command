#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <time.h>       /* local time */
#include <stdio.h>
#include <string.h>
#include <limits.h>     /* PATH_MAX */
#include <grp.h>
#include <pwd.h>

/* helper functions */
char* format_date(char* str, time_t val);
char* get_user(uid_t uid);
char* get_group(gid_t grpNum);

int main(int argc, char* argv[]) {

    /* check command line arguments */
    if (argc < 2) {
        printf("Usage: %s [-il] [directory]\n", argv[0]);
        return 1;
    }

    int iflag = 0;
    int lflag = 0;
    int option = 0;

    /* options */
    while ((option = getopt(argc, argv, "ilp:")) != -1) {
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
    struct dirent* pDirent = NULL;
    struct stat statbuf;
    char mtime[36];

    /* get directory from command-line */
    char* dir = argv[argc - 1];
    printf ("iflag = %d, lflag = %d, dir = %s\n", iflag, lflag, dir);

    /* open directory */
    DIR* pDir = opendir(dir);
    if (pDir == NULL) {
        printf ("Failed to  open directory '%s'\n", dir);
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
        if (S_ISDIR(statbuf.st_mode)) { strncat(fullpath, "/", 1); }

        /* get info for this path */
        if (stat(fullpath, &statbuf) == -1) {
            printf("Stat error: %s\n", fullpath);
            continue;
        }

        /* -i option */
        if (iflag == 1) { printf("%9llu  ", statbuf.st_ino); }

        /* -l option */
        if (lflag == 1) {

            printf((S_ISDIR(statbuf.st_mode)) ? "d" : "-");         /* permissions */
            printf((statbuf.st_mode & S_IRUSR) ? "r" : "-");
            printf((statbuf.st_mode & S_IWUSR) ? "w" : "-");
            printf((statbuf.st_mode & S_IXUSR) ? "x" : "-");
            printf((statbuf.st_mode & S_IRGRP) ? "r" : "-");
            printf((statbuf.st_mode & S_IWGRP) ? "w" : "-");
            printf((statbuf.st_mode & S_IXGRP) ? "x" : "-");
            printf((statbuf.st_mode & S_IROTH) ? "r" : "-");
            printf((statbuf.st_mode & S_IWOTH) ? "w" : "-");
            printf((statbuf.st_mode & S_IXOTH) ? "x  " : "-  ");

            printf("%2d  ",statbuf.st_nlink);                       /* number of links */
            printf("%2s  ", get_user(statbuf.st_uid));              /* user name */
            printf("%3s  ", get_group(statbuf.st_gid));             /* group name */
            printf("%4lld  ",statbuf.st_size);                      /* file size */
            printf("%17s  ", format_date(mtime, statbuf.st_mtime)); /* last mod */
        }

        printf("%s\n", pDirent->d_name);                            /* file name */

        /* symbolic link */
        /* printf("\t%s symbolic\n", (S_ISLNK(statbuf.st_mode)) ? "is" : "is not"); */
    }

    closedir (pDir);
    return 0;
}

/* mmm dd yyyy hh:mm */
char* format_date(char* str, time_t val) {
    strftime(str, 36, "%b %d %Y %H:%M", localtime(&val));
    return str;
}

char* get_group(gid_t grpNum) {
    struct group* grp = getgrgid(grpNum);

    if (grp) { return grp->gr_name; }
    return NULL;
}

char* get_user(uid_t uid) {
    struct passwd* pw = getpwuid(uid);

    if (pw) { return pw->pw_name; } 
    return NULL;
}
