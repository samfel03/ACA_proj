//#include <stdio.h>
//#include <string.h> /* For strcmp() */
//#include <stdlib.h> /* For EXIT_FAILURE, EXIT_SUCCESS */
#include <iostream> // std::cout
#include <cstring>  // append
#include <fstream>
#include <cstdio>
#include <cstdlib>
#include <iomanip>
#define real double
#define INPUTPATH "/Users/alessandroperi/Dropbox/Projects/CCE-FPGA/CCE-C/C/input/"
#define NPOSLAND 17048 // Number of cells with positive land

#define INPUT_INDEXES_ENUM_TXT \
  X(I_H)                            \
  X(I_prod0)                        \
  X(I_pop5_dens)                    \
  X(I_u0)                           \
  X(I_a_norm)                       \
  X(I_trmult_reduced)               \
  X(I_C_vect)                       \
  X(I_emi_no_ff)                    \
  X(I_price_energy0)                \
  X(I_zeta_clean0)                  \
  X(I_zeta_fossil0)                 \
  X(I_forc_noCO2)                   \
  X(I_temp_past)                    \
  X(I_Delta_temp)                   \
  X(I_scaler_temp)                  \
  X(I_theta_amen_scen)              \
  X(I_theta_prod_scen)              \
  X(I_natal_data)

enum Parameters_Indexes
{
#define X(a) a,
  INPUT_INDEXES_ENUM_TXT
#undef X
      N_INPUT // TOTAL NUMBER OF PARAMETERS DISPLAYED
};

char const *const INPUT_NAMES[] = {
#define X(a) #a,
    INPUT_INDEXES_ENUM_TXT
#undef X
    0};

void read_real_1D(real *variable, char *variablename)
{
  FILE *fp;
  char filename[250] = {'\0'};
  memset(filename, '\0', sizeof(filename));
  strcpy(filename, INPUTPATH);
  strcat(filename, variablename);
  strcat(filename, ".txt");
  fprintf(stderr, "Opening the file: %s\n", filename);
  // fprintf(stderr, "Tipo della variabile: %s\n", typeid(variable).name());
  fp = fopen(filename, "r");
  if (fp == NULL)
  {
    fprintf(stderr, "\n1.1. FAIL: Cannot read the variable %s\n", variablename);
    exit(EXIT_FAILURE);
  }
  int i = 0;
  while (fscanf(fp, "%lf", &variable[i]) == 1)
    i = i + 1;
  fprintf(stderr, "Total Number of Elements: %d\n", i);

  fclose(fp);
  fp = NULL;
  return;
}
void printf_real_1D(int dim_1, real *A)
{
  int i_1;
  for (i_1 = 0; i_1 < dim_1; i_1++)
  {
    fprintf(stderr, "%.36lf ", A[i_1]);
  }
}
void fprintf_int_1D(FILE *fp, int dim_1, int *A)
{
  int i_1;
  for (i_1 = 0; i_1 < dim_1; i_1++)
  {
    fprintf(fp, "%d ", A[i_1]);
  }
}
void fprintf1int(FILE *fp, int dim_1, int *A)
{
  int i_1;
  // i1=NK,i2=nBR,i3=NX,i4=NF
  for (i_1 = 0; i_1 < dim_1; i_1++)
  {
    fprintf(fp, "%d ", A[i_1]);
  }
}
int main()
{
  // Preallocate
  real *H = (real *)malloc(NPOSLAND * sizeof(real));

  // ********************************** READ THE VARIABLES FROM INPUT
  char variablename[250] = {'\0'};
  // ---------------------------------------------------------------------------
  memset(variablename, '\0', sizeof(variablename));
  strcpy(variablename, "H");read_real_1D(H, variablename);      // ************* VARIABLE
  printf_real_1D(NPOSLAND, H);printf("\n"); // Print Variable
  
  // Dellocate
  free(H);

  // Variable names
  for (int i_p = 0; i_p < N_INPUT; i_p++)
  {
    printf("%d: %s \n", i_p, INPUT_NAMES[i_p]);
  }

  printf("E poi: %d: %s \n", I_emi_no_ff, INPUT_NAMES[I_emi_no_ff]);

  // std::string variablename("H");//CCE-FPGA/CCE-C/C/input/");
  // std::cout << "variable " << variablename.c_str() <<"\n";
  // std::string filename(INPUTPATH);filename.append(variablename.c_str());filename.append(".txt");
  // std::cout << "variable " << filename <<"\n";
  //  Open File
  // read_1D(H,NPOSLAND,variablename);

  return 0;
}

/*
template <class T>
inline void fscanf7(std::istream &myfile, int dim_1, T *A)
{
  for (int i_1 = 0; i_1 < dim_1; i_1++)
    myfile >> A[i_1];
}
template <class T>
void read_1D(T *variable, int dim, std::string variablename)
{
  // File name
  std::string filename(INPUTPATH);filename.append(variablename);filename.append(".txt");
  // Open File
  std::ifstream infile;infile.open(filename);
if (infile.is_open())
  {
    fscanf7(infile, dim, variable);
  }
  else
  {
    // std::cout << "\nUnable to read the "<< variablename <<"file";
    fprintf(stderr, "\n1.1. FAIL: Cannot read the variable %s\n", variablename);
    exit(EXIT_FAILURE);
  }
  infile.close();
  return;
}
int main()
{
  // Preallocate
  real *H = (real *)malloc(NPOSLAND * sizeof(real));
  std::string variablename("H");//CCE-FPGA/CCE-C/C/input/");
  std::cout << "variable " << variablename.c_str() <<"\n";
  std::string filename(INPUTPATH);filename.append(variablename.c_str());filename.append(".txt");
  std::cout << "variable " << filename <<"\n";
  // Open File
  read_1D(H,NPOSLAND,variablename);
  // Dellocate
  free(H);

  return 0;
}
*/