#include <stdio.h>				
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>	// ENOMEM
#include <unistd.h> 
#include <pwd.h>
char *getUsername() {
	register struct passwd *pw;
  	register uid_t uid;
  	uid = geteuid();
  	pw = getpwuid(uid);
	return pw->pw_name;
}
/*
char *getUsername(){
    register struct passwd *pw;
    register uid_t uid;
    uid = geteuid();
    pw = getpwuid(uid);
    return pw -> pw_name;
}*/

int main( int argc, char *argv[] ) {

    char pathOfBashrc[100];

	sprintf(pathOfBashrc,"/home/");
	sprintf(pathOfBashrc + strlen(pathOfBashrc), "%s", getUsername());
	sprintf(pathOfBashrc + strlen(pathOfBashrc), "/.bashrc");
    printf("\n%s\n", pathOfBashrc);
    return 0;
}