//Matthew Penner
//Lab #1
//Part One: mystat.c
//CS333

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <time.h>
#include <string.h>
#include <limits.h>
/*
SOURCES CITED:
https://github.com/Jyotheeswar114/Interactive-User-Defined-Shell/blob/45972fd561ca42273d162c5533dbf0bb7b3c231f/ls.c
https://github.com/samcarljohnson/cpsc275/blob/b318d269f458ffc16c4b8c1617a37e87053757f2/labs/lab12/myls.c
https://www.gnu.org/software/libc/manual/html_node/Testing-File-Type.html
*/
char* show_mode(unsigned long mode)
{
    static char mode_str[11];
    
    switch (mode & S_IFMT) {
      case S_IFBLK:   mode_str[0] = 'b';           break;
      case S_IFCHR:   mode_str[0] = 'c';           break;
      case S_IFDIR:   mode_str[0] = 'd';           break;
      case S_IFIFO:   mode_str[0] = 'p';           break;
      case S_IFLNK:   mode_str[0] = 'l';           break;
      case S_IFREG:   mode_str[0] = '-';           break;
      case S_IFSOCK:  mode_str[0] = 's';           break;
    }
    mode_str[1] = (mode & S_IRUSR) ? 'r' : '-';
    mode_str[2] = (mode & S_IWUSR) ? 'w' : '-';
    mode_str[3] = (mode & S_IXUSR) ? 'x' : '-';
    mode_str[4] = (mode & S_IRGRP) ? 'r' : '-';
    mode_str[5] = (mode & S_IWGRP) ? 'w' : '-';
    mode_str[6] = (mode & S_IXGRP) ? 'x' : '-';
    mode_str[7] = (mode & S_IROTH) ? 'r' : '-';
    mode_str[8] = (mode & S_IWOTH) ? 'w' : '-';
    mode_str[9] = (mode & S_IXOTH) ? 'x' : '-';
    mode_str[10] = '\0';
    
    int count = 0;
    for(int i = 0; i < sizeof(mode_str); ++i)
    {
      if(mode_str[i] ==  '-')
      {
        ++count;
      }
    }
    if(count > 0)
      return mode_str;
    else
      return "lrwxrwxrwx";
}

void display_inode_data(const char *file_path)
{
    struct stat file_stat;
    if(lstat(file_path, &file_stat) == -1)
    {
        perror("lstat");
        exit(EXIT_FAILURE);
    }
    
   
    // Show the name of the file
    printf("File: %s\n", file_path);


    // Display the file type
    printf("File type:                ");
    if(S_ISREG(file_stat.st_mode))
        printf("regular file\n");
    else if(S_ISDIR(file_stat.st_mode))
        printf("directory\n");
    else if(S_ISCHR(file_stat.st_mode))
        printf("character device\n");
    else if(S_ISBLK(file_stat.st_mode))
        printf("block device\n");
    else if(S_ISFIFO(file_stat.st_mode))
        printf("FIFO/pipe\n");
    else if(S_ISLNK(file_stat.st_mode))
    {
        char target_path[PATH_MAX + 1];
        ssize_t len = readlink(file_path, target_path, sizeof(target_path) - 1);

        printf("Symbolic link");
        //Check if symbolic link is dangling
        if(len != -1)
        {
            if(access(target_path, F_OK) == -1)
            {
                printf(" - with dangling destination\t\n");
            }
            else
            {
                printf(" -> %s\n", target_path);
                
            }
        }
    }
    else if(S_ISSOCK(file_stat.st_mode))
        printf("socket\n");
    else
        printf("unknown\n");

    // Display the device ID
    printf("Device ID number:         %lxh/%ldd\n", (long)file_stat.st_dev, (long)file_stat.st_dev);

    // Display the inode value
    printf("I-node number:            %ld\n", (long)file_stat.st_ino);

    // Display the mode
    char* mode_str = show_mode((unsigned long)file_stat.st_mode);
    printf("Mode:\t\t\t%s",  mode_str);
    printf("(%03lo in octal)\n", (unsigned long)(file_stat.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO))); 

    // Show the hard link count
    printf("Link count:               %ld\n", (long)file_stat.st_nlink);

    // Show both the uid and gid for the file
    struct passwd *oid = getpwuid(file_stat.st_uid);
    struct group *gid = getgrgid(file_stat.st_gid);
    
    if(oid != 0)
    {
      printf("Owner Id:                 %s           (UID = %ld)\n", oid->pw_name, (long)file_stat.st_uid); 
    }
    if(gid != 0)
    {
      printf("Group Id:                 %s              (GID = %ld)\n", gid->gr_name, (long)file_stat.st_gid); 
    }
    // Preferred I/O block size, in bytes
    printf("Preferred I/O block size: %ld bytes\n", (long)file_stat.st_blksize);

    // File size, in bytes
    printf("File size:                %lld bytes\n", (long long)file_stat.st_size);

    // Blocks allocated
    printf("Blocks allocated:         %lld\n", (long long)file_stat.st_blocks);

    // Show the 3 time values in local time/date
    char buffer[36];

    // Last access time
    strftime(buffer, 36, "%Y-%m-%d %H:%M:%S %z (%Z) %a", localtime(&file_stat.st_atime));
    printf("Last file access:         %s (local)\n", buffer);
    
    // Last modification time
    strftime(buffer, 36, "%Y-%m-%d %H:%M:%S %z (%Z) %a", localtime(&file_stat.st_mtime));
    printf("Last file modification:   %s (local)\n", buffer);
    
    // Last status change time
    strftime(buffer, 36, "%Y-%m-%d %H:%M:%S %z (%Z) %a", localtime(&file_stat.st_ctime));
    printf("Last status change:       %s (local)\n", buffer);
}


int main(int argc, char *argv[])
{
    if (argc < 2)
    {   
        fprintf(stderr, "Usage: %s <file1> <file2> ... <fileN>\n", argv[0]);
        exit(EXIT_FAILURE);

    }

    for (int i = 1; i < argc; i++)
    {
        display_inode_data(argv[i]);
    }
    return EXIT_SUCCESS;
}
