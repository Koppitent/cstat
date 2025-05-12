#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

int main(int argc, char *argv[]) {
    if(argc < 2) {
        perror("Mindestens 1 Argument angeben!");
    }
    struct stat file_stat;
    for(int i=1; i<argc; i++) {
        if(stat(argv[i], &file_stat)) {
            perror(argv[i]);
        }

        printf("Dateiname:                               %s\n", argv[i]);
        struct passwd *user_info = getpwuid(file_stat.st_uid);
        struct group *group_info = getgrgid(file_stat.st_gid);  

        if (user_info == NULL) {
            printf("Benutzername für UID %d nicht gefunden\n", file_stat.st_uid);
        } else {
            printf("Besitzer der Datei:                      %s\n", user_info->pw_name);
        }

        if (group_info == NULL) {
            printf("Gruppenname für GID %d nicht gefunden\n", file_stat.st_gid);
        } else {
            printf("Gruppeneigentümer der Datei:             %s\n", group_info->gr_name);
        }

        printf("User ID (UID):                           %d\n", file_stat.st_uid);
        printf("Group ID (GID):                          %d\n", file_stat.st_gid);
        printf("File type:                               ");

           switch (file_stat.st_mode & __S_IFMT) {
           case __S_IFBLK:  printf("block device\n");            break;
           case __S_IFCHR:  printf("character device\n");        break;
           case __S_IFDIR:  printf("directory\n");               break;
           case __S_IFIFO:  printf("FIFO/pipe\n");               break;
           case __S_IFLNK:  printf("symlink\n");                 break;
           case __S_IFREG:  printf("regular file\n");            break;
           case __S_IFSOCK: printf("socket\n");                  break;
           default:       printf("unknown?\n");                break;
           }

        printf("Zugriffsbits im Oktalsystem:             %d\n", file_stat.st_mode);
        printf("Zeit des letzten Zugriffs:               %s", ctime(&file_stat.st_atime));
        printf("Zeit der letzten Inode-Anderung:         %s", ctime(&file_stat.st_ctime));
        printf("Zeit der letzten Datei¨anderung:         %s", ctime(&file_stat.st_mtime));
        printf("Zeit der Dateierstellung:                %s\n", "not found");

    }
    return 0;
}