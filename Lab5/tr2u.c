#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, const char *argv[]){
  const char* from = argv[1];
  // if from has duplicate bytes
  // exit with error
  int lenFrom = strlen(from);
  for(int i = 0; i < lenFrom; i++){
    for(int j = i+1; j < lenFrom; j++){
      if(from[i] == from[j]){
	fprintf(stderr, "from has duplicate bytes");
	exit(1);
      }
    }
  }
  const char* to = argv[2];
  // if from and to are not of the same length
  // exit with error 
  if(lenFrom != strlen(to)){
    fprintf(stderr, "from and to are not of the same length");
    exit(1);
  }
  
  int c;
  while(read(0, &c, 1) > 0){
    for(int i = 0; from[i] != '\0'; i++){
      if(from[i] == c){
	c = to[i];
	break;
      }
    }
    write(1, &c, 1);
  }

  return 0;
}
