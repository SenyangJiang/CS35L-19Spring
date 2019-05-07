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
	fprintf(stderr, "ERROR: from has duplicate bytes\n");
	exit(1);
      }
    }
  }
  const char* to = argv[2];
  // if from and to are not of the same length
  // exit with error 
  if(lenFrom != strlen(to)){
    fprintf(stderr, "ERROR: from and to are not of the same length\n");
    exit(1);
  }
  
  int c;
  while(read(STDIN_FILENO, &c, 1) > 0){
    for(int i = 0; i < lenFrom; i++){
      if(from[i] == c){
	c = to[i];
	break;
      }
    }
    write(STDOUT_FILENO, &c, 1);
  }

  return 0;
}
