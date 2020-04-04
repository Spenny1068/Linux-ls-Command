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

/* global variables */
char fullpath[PATH_MAX + 1];
char mtime[36];
char* tok;
struct stat statbuf;

/* helper functions */
char* format_date(char* str, time_t val);
char* get_user(uid_t uid);
char* get_group(gid_t grpNum);
void l_option();
void i_option();

int main(int argc, char* argv[]) {

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

    /* initialize variables */
    ssize_t nbytes = 0;
    tok = NULL;
    char* buf = malloc(PATH_MAX);
    DIR* pDir = NULL;
    struct dirent* pDirent = NULL;

    /* raw ls - no options provided */
    if (optind == argc) {
        argv[optind] = ".";
        argc++;
    }

    /* for every argument provided */
    for(int index = optind; index < argc; index++) {

        /* open provided file or directory */
        tok = argv[index];
        pDir = opendir(tok);

        /* token is a directory */
        if (pDir != NULL) {

            if (optind != argc - 1) { printf("%s: \n", tok); }

            /* iteratively read the directory */
            while ((pDirent = readdir(pDir)) != NULL) {

                /* ignore hidden files */
                if (pDirent->d_name[0] == '.') { continue; }

                /* build full path */
                realpath(tok, fullpath);
                strncat(fullpath, "/", 1);
                strncat(fullpath, pDirent->d_name, sizeof(pDirent->d_name) + 1);

                /* get info for this path */
                if (lstat(fullpath, &statbuf) == -1) {
                    printf("Stat error: %s\n", fullpath);
                    continue;
                }

                /* -i option */
                if (iflag == 1) { i_option(); }

                /* -l option */
                if (lflag == 1) {

                    l_option();
                    printf("%s ", pDirent->d_name);                         /* file name */

                    /* if its a symbolic link */
                    if (S_ISLNK(statbuf.st_mode)) {

                        nbytes = readlink(fullpath, buf, PATH_MAX);
                        if (nbytes == -1) {  printf("readlink error: %s\n", fullpath); }           
                        printf("-> %.*s\n", (int)nbytes, buf);
                    }
                    else { printf("\n"); }
                }

                /* no -l option */
                else { printf("%s\n", pDirent->d_name); }
            }
            closedir (pDir);
        }

        /* token is a file */
        else if (access(tok, F_OK) != -1) {

            /* get info for this path */
            if (lstat(tok, &statbuf) == -1) {
                printf("Stat error: %s\n", fullpath);
                continue;
            }

            /* i option */
            if (iflag == 1) { i_option(); }

            /* l option */
            if (lflag == 1) { 

                l_option();
                printf("%s", tok);          /* file name */

                /* if its a symbolic link */
                if (S_ISLNK(statbuf.st_mode)) {

                    nbytes = readlink(tok, buf, PATH_MAX);
                    if (nbytes == -1) { printf("readlink error: %s\n", tok); }           
                    printf("-> %.*s\n", (int)nbytes, buf);
                }
                else { printf("\n"); }
            }

            /* no l option */
            else  { printf("%s\n", tok); }
        }

        /* not a file or directory */
        else { printf("%s: %s: no such file or directory", argv[0], tok); }
        printf("\n");
    }

    free(buf);
    return 0;
}

/* mmm dd yyyy hh:mm */
char* format_date(char* str, time_t val) {
    strftime(str, 36, "%b %d %Y %H:%M", localtime(&val));
    return str;
}

/* returns group name from group id */
char* get_group(gid_t grpNum) {
    struct group* grp = getgrgid(grpNum);

    if (grp) { return grp->gr_name; }
    return NULL;
}

/* returns user name from user id */
char* get_user(uid_t uid) {
    struct passwd* pw = getpwuid(uid);

    if (pw) { return pw->pw_name; } 
    return NULL;
}

void l_option() {
    if ((S_ISDIR(statbuf.st_mode))) { printf("d"); } 
    else if (S_ISLNK(statbuf.st_mode)){ printf("l"); }
    else { printf("-"); }
    printf((statbuf.st_mode & S_IRUSR) ? "r" : "-");
    printf((statbuf.st_mode & S_IWUSR) ? "w" : "-");
    printf((statbuf.st_mode & S_IXUSR) ? "x" : "-");
    printf((statbuf.st_mode & S_IRGRP) ? "r" : "-");
    printf((statbuf.st_mode & S_IWGRP) ? "w" : "-");
    printf((statbuf.st_mode & S_IXGRP) ? "x" : "-");
    printf((statbuf.st_mode & S_IROTH) ? "r" : "-");
    printf((statbuf.st_mode & S_IWOTH) ? "w" : "-");
    printf((statbuf.st_mode & S_IXOTH) ? "x  " : "-  ");

    printf("%-3ld  ",statbuf.st_nlink);                       /* number of links */
    printf("%-2s  ", get_user(statbuf.st_uid));               /* user name */
    printf("%-3s  ", get_group(statbuf.st_gid));              /* group name */
    printf("%-8ld  ", statbuf.st_size);                        /* file size */
    printf("%-17s  ", format_date(mtime, statbuf.st_mtime));  /* last mod */
}

void i_option() { printf("%-21lu  ", statbuf.st_ino); }
