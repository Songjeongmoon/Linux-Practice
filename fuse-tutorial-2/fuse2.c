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

    filler(buffer, "new_file", NULL, 0);
	printf("\n%s\n", path);
	return 0;
}

int my_read(const char *path, char *buffer, size_t size, off_t offset, struct fuse_file_info *fInfo){
    
    printf("\npath = %s\nbuffer = %s\nsize = %d\noffset = %d\n", path, buffer, (int)size, (int)offset);
    return 0;
}

int my_write(const char *path, const char *buffer, size_t size, off_t offset, struct fuse_file_info *fi){
    char *line;
    char *path2 = "/home/song/project/exam/Linux-Practice/fuse-tutorial-2/asd/new_file";
    char *str;
    size_t len = 0;
    printf("buffer = %s\n", buffer);
    printf("size = %d\n", (int)size);
    FILE *file = fopen(path2, "w");
    FILE *file2 = fopen(path2, "r");
    fprintf(file, "%s", buffer);
    fflush(file);
    fgets(str, 10, file2);
    printf("%s", str);
    fclose(file);
    fclose(file2);
    return size;
}

int fun_release(const char *path, struct fuse_file_info *fi) {
    printf("release path = %s\n", path);
	printf("Release Function\n");
	return 0;
}



int fun_flush(const char *path, struct fuse_file_info *fi) { 
    printf("flush path = %s\n", path);
	printf("Flush Function\n");
	return 0;
}



int fun_open(const char *path, struct fuse_file_info *fi) {
	
	if ( strcmp(path, "/new_file") == 0 ) 
		printf("has Been opened successfully\n");
	else
		return -ENOENT;

	return 0;
}

int fun_truncate(const char *path, off_t newsize)
{
    printf("truncate path = %s\n", path);
    printf("truncate newsize = %d\n", (int)newsize);
	return 0;
}

int fun_ftruncate(const char *path, off_t offset, struct fuse_file_info *fi)
{
    printf("ftruncate path = %s\n", path);
    printf("ftruncate offset = %d\n", (int)offset);
	return 0;
}


static struct fuse_operations myOperations = {
	.getattr = my_getattr,
    .readdir = my_readdir,
    .read = my_read,
    .write = my_write,
    .open		= fun_open,
    .flush		= fun_flush,
    .truncate 	= fun_truncate,
	.release	= fun_release,
	.ftruncate 	= fun_ftruncate,
};

int main(int argc, char *argv[]){
	return fuse_main(argc, argv, &myOperations, NULL);
}