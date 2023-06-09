#define FUSE_USE_VERSION 30

#include <fuse.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <time.h>

static int myGetattr(const char *path, struct stat *st){
    st -> st_uid = getuid();
    st -> st_gid = getgid();
    st -> st_atime = time(NULL);
    st -> st_mtime = time(NULL);
    st -> st_ctime = time(NULL);
    if(strcmp(path, "/") == 0){
        st -> st_mode = S_IFDIR | 0755;
        st -> st_nlink = 2;
    } else{
        st -> st_mode = S_IFREG | 0644;
        st -> st_nlink = 1;
        st -> st_size = 1024;
    }
    return 0;
}

static int myRead(const char *path, char *buffer, size_t size, off_t offset, struct fuse_file_info *fInfo){
    char file1Text[] = "This is File[1]!\n";
    char file2Text[] = "This is File[2]\n";
    char *selectedText = NULL;

    if(strcmp(path, "file[1]") == 0){
        selectedText = file1Text;
    } else if(strcmp(path, "file[2]") == 0){
        selectedText = file2Text;
    } else{
        return -1;
    }
    memcpy(buffer, selectedText + offset, size);
    return strlen(selectedText) - offset;
}

static int myReaddir(const char *path, void *buffer, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fInfo){
    filler(buffer, ".", NULL, 0);
    filler(buffer, "..", NULL, 0);

    if(strcmp(path, "/") == 0){
        filler(buffer, "file1", NULL, 0);
        filler(buffer, "file2", NULL, 0);
    }
    return 0;
}

static struct fuse_operations myFileOperation = {
    .getattr = myGetattr,
    .readdir = myReaddir,
    .read = myRead,
};

int main(int argc, char *argv[]){
    return fuse_main(argc, argv, &myFileOperation, NULL);
}