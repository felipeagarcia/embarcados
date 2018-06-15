#include <stdio.h>
#include <stdlib.h>
#define COL_NUM 2
#define ROW_NUM 3

float data[3][COL_NUM] = {{1,2},{3,4},{5,6}};


int main(){
  int i,j;
  for(i=0;i<ROW_NUM;i++){
    for(j=0;j<COL_NUM;j++){
      printf("[%f]",data[i][j]);
    }
    printf("\n");
  }

  return 0;
}
