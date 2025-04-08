#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;
#define real double
#define NPOSLAND 17048 // Number of cells with positive land

int main()
{
  int dim_n = NPOSLAND * NPOSLAND;        // Number of Elements
  size_t SIZE_var = dim_n * sizeof(real); // Number of bytes
  real *trmult_reduced = (real *)malloc(SIZE_var);
  //double fnum[4] = {9.5, -3.4, 1.0, 2.1};
  // Open file
  FILE *fp;
  fp=fopen("/Users/alessandroperi/Dropbox/Projects/CCE-FPGA/CCE-C/C/input/trmult_reduced.bin","rb"); // rb: read binary
  //fp=fopen("/Users/alessandroperi/Dropbox/Projects/CCE-FPGA/CCE-C/testbench/initialize/auxiliary/3-readbinary/numbers.bib","rb"); // rb: read binary
  if (fp == NULL)
  {
    fprintf(stderr, "\n1.1. FAIL: Cannot read the variable %s\n", "trmult_reduced");
    exit(EXIT_FAILURE);
  }
  // Verify size of Array
  printf("Size of array: %lu\n", SIZE_var); // unsigned integral type that measure the number of bytes
  // FREAD: https://study.com/academy/lesson/writing-reading-binary-files-in-c-programming.html
  for(int i=0;i<dim_n;i++){
    fread(&trmult_reduced[i],sizeof(trmult_reduced[0]),1,fp);

  }
  for(int i=0;i<dim_n;i++)
    printf("v[%d]=%.36g\n",i,trmult_reduced[i]);
  // Close file
  fclose(fp);

  // Dellocate
  free(trmult_reduced);
  return 0;
}