	
#include <stdio.h>				
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>	
#include <unistd.h> 
#include <pwd.h>	


int main() {

   char *str1 = "abcdef";
   char *str2 = "abc";
   char *str3 = "abce";
   if(strncmp(str1, str2, 3) == 0){
      printf("first correct\n");
   }
   if(strncmp(str1, str3, 4) == 0){
      printf("second correct\n");
   }
	return 0;
}