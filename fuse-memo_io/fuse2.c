#ifndef FUSE_USE_VERSION
	#define FUSE_USE_VERSION 30
#endif
#include <fuse.h>
#include <stdio.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <pwd.h>

char *memo = "/home/song/memo";

int my_getattr(const char *path, struct stat *st){
	
    st -> st_uid = getuid();
    st -> st_gid = getgid();
    st -> st_atime = st -> st_mtime = st -> st_ctime = time(NULL);
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

int my_readdir(const char *path, void *buffer, fuse_fill_dir_t filler, off_t offset, struct fuse_file_info *fInfo){
	filler(buffer, ".", NULL, 0);
	filler(buffer, "..", NULL, 0);
    filler(buffer, "memo", NULL, 0);
	return 0;
}

int my_write(const char *path, const char *buffer, size_t size, off_t offset, struct fuse_file_info *fi){
    FILE *fp = fopen(memo, "a");
    fputs(buffer, fp);
    fclose(fp);
    return size;
}

int fun_open(const char *path, struct fuse_file_info *fi) {
	return 0;
}

/*
int fun_release(const char *path, struct fuse_file_info *fi) {
	return 0;
}

int fun_flush(const char *path, struct fuse_file_info *fi) {
	return 0;
}

int fun_ftruncate(const char *path, off_t offset, struct fuse_file_info *fi) {
	return 0;
}*/

int fun_truncate(const char *path, off_t newsize) {
	return 0;
}

static struct fuse_operations myOperations = {
	.getattr    = my_getattr,
    .readdir    = my_readdir,
    .write      = my_write,
    .open		= fun_open,
    //.flush		= fun_flush,
    .truncate 	= fun_truncate,
	//.release	= fun_release,
	//.ftruncate 	= fun_ftruncate,
};

int main(int argc, char *argv[]){
	return fuse_main(argc, argv, &myOperations, NULL);
}