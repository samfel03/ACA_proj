// ConsoleApplication1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <math.h>
#include <string.h>
extern "C" {
#include "rt_nonfinite.h"
#include "rtwtypes.h"
#include "svd.h"
}
#include <stddef.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <math.h>
#include <string.h>

typedef double real;

#define INPUTPATH "C:\\Users\\Joongsan\\source\\repos\\AleP83\\CCE-C\\testbench\\estim_model\\auxiliary\\3-rcond\\"
#define PRINTPATH "C:\\Users\\Joongsan\\source\\repos\\AleP83\\CCE-C\\testbench\\estim_model\\auxiliary\\3-rcond\\"
#define MATRIX_SIZE 8
#define TEST_CNT 10
#define DIMENSION(size) size*size
#define ELEMENT(row,column,size) row+column*size

/* Function Definitions */
void call_pinv(const double X[64], double Y[64])
{
    int br;
    int i;
    int ib;
    int ic;
    int j;
    int vcol;
    boolean_T p;
    /* RCOND  */
    p = true;
    for (br = 0; br < 64; br++) {
        Y[br] = 0.0;
        if ((!p) || (rtIsInf(X[br]) || rtIsNaN(X[br]))) {
            p = false;
        }
    }
    if (!p) {
        for (i = 0; i < 64; i++) {
            Y[i] = rtNaN;
        }
    }
    else {
        double U[64];
        double V[64];
        double s[8];
        double absx;
        int r;
        svd(X, U, s, V);
        absx = fabs(s[0]);
        if ((!rtIsInf(absx)) && (!rtIsNaN(absx))) {
            if (absx <= 2.2250738585072014E-308) {
                absx = 4.94065645841247E-324;
            }
            else {
                frexp(absx, &vcol);
                absx = ldexp(1.0, vcol - 53);
            }
        }
        else {
            absx = rtNaN;
        }
        absx *= 8.0;
        r = -1;
        br = 0;
        while ((br < 8) && (s[br] > absx)) {
            r++;
            br++;
        }
        if (r + 1 > 0) {
            vcol = 1;
            for (j = 0; j <= r; j++) {
                absx = 1.0 / s[j];
                i = vcol + 7;
                for (br = vcol; br <= i; br++) {
                    V[br - 1] *= absx;
                }
                vcol += 8;
            }
            for (vcol = 0; vcol <= 56; vcol += 8) {
                i = vcol + 1;
                j = vcol + 8;
                if (i <= j) {
                    memset(&Y[i + -1], 0, ((j - i) + 1) * sizeof(double));
                }
            }
            br = 0;
            for (vcol = 0; vcol <= 56; vcol += 8) {
                int ar;
                ar = -1;
                br++;
                i = br + (r << 3);
                for (ib = br; ib <= i; ib += 8) {
                    int i1;
                    j = vcol + 1;
                    i1 = vcol + 8;
                    for (ic = j; ic <= i1; ic++) {
                        Y[ic - 1] += U[ib - 1] * V[(ar + ic) - vcol];
                    }
                    ar += 8;
                }
            }
        }
    }
}



double call_rcond(const double X[64])
{
    double A[64];
    double x[8];
    double Y;
    double normA;
    double s;
    int b_j;
    int i;
    int iy;
    int j;
    int jA;
    boolean_T exitg1;
    /* RCOND  */
    memcpy(&A[0], &X[0], 64U * sizeof(double));
    Y = 0.0;
    normA = 0.0;
    j = 0;
    exitg1 = false;
    while ((!exitg1) && (j < 8)) {
        s = 0.0;
        for (i = 0; i < 8; i++) {
            s += fabs(X[i + (j << 3)]);
        }
        if (rtIsNaN(s)) {
            normA = rtNaN;
            exitg1 = true;
        }
        else {
            if (s > normA) {
                normA = s;
            }
            j++;
        }
    }
    if (!(normA == 0.0)) {
        double smax;
        int b_i;
        int iter;
        int jjA;
        int jp1j;
        int kase;
        for (j = 0; j < 7; j++) {
            int b_tmp;
            iter = 6 - j;
            b_tmp = j * 9;
            jp1j = b_tmp + 2;
            jjA = 8 - j;
            iy = 0;
            smax = fabs(A[b_tmp]);
            for (jA = 2; jA <= jjA; jA++) {
                s = fabs(A[(b_tmp + jA) - 1]);
                if (s > smax) {
                    iy = jA - 1;
                    smax = s;
                }
            }
            if (A[b_tmp + iy] != 0.0) {
                if (iy != 0) {
                    iy += j;
                    for (jA = 0; jA < 8; jA++) {
                        jjA = jA << 3;
                        kase = j + jjA;
                        s = A[kase];
                        jjA += iy;
                        A[kase] = A[jjA];
                        A[jjA] = s;
                    }
                }
                b_i = (b_tmp - j) + 8;
                for (i = jp1j; i <= b_i; i++) {
                    A[i - 1] /= A[b_tmp];
                }
            }
            jA = b_tmp;
            for (b_j = 0; b_j <= iter; b_j++) {
                s = A[(b_tmp + (b_j << 3)) + 8];
                if (s != 0.0) {
                    b_i = jA + 10;
                    jjA = (jA - j) + 16;
                    for (iy = b_i; iy <= jjA; iy++) {
                        A[iy - 1] += A[((b_tmp + iy) - jA) - 9] * -s;
                    }
                }
                jA += 8;
            }
        }
        jA = 7;
        int exitg2;
        do {
            exitg2 = 0;
            if (jA + 1 > 0) {
                if (A[jA + (jA << 3)] == 0.0) {
                    exitg2 = 1;
                }
                else {
                    jA--;
                }
            }
            else {
                double ainvnm;
                ainvnm = 0.0;
                iter = 2;
                kase = 1;
                jp1j = 1;
                j = 0;
                for (i = 0; i < 8; i++) {
                    x[i] = 0.125;
                }
                while (kase != 0) {
                    if (kase == 1) {
                        for (b_j = 0; b_j < 8; b_j++) {
                            jjA = b_j + (b_j << 3);
                            b_i = 6 - b_j;
                            for (i = 0; i <= b_i; i++) {
                                iy = (b_j + i) + 1;
                                x[iy] -= x[b_j] * A[(jjA + i) + 1];
                            }
                        }
                        for (b_j = 7; b_j >= 0; b_j--) {
                            jjA = b_j + (b_j << 3);
                            x[b_j] /= A[jjA];
                            for (i = 0; i < b_j; i++) {
                                iy = (b_j - i) - 1;
                                x[iy] -= x[b_j] * A[(jjA - i) - 1];
                            }
                        }
                    }
                    else {
                        for (b_j = 0; b_j < 8; b_j++) {
                            jA = b_j << 3;
                            s = x[b_j];
                            for (i = 0; i < b_j; i++) {
                                s -= A[jA + i] * x[i];
                            }
                            x[b_j] = s / A[jA + b_j];
                        }
                        for (b_j = 7; b_j >= 0; b_j--) {
                            jA = b_j << 3;
                            s = x[b_j];
                            b_i = b_j + 2;
                            for (i = 8; i >= b_i; i--) {
                                s -= A[(jA + i) - 1] * x[i - 1];
                            }
                            x[b_j] = s;
                        }
                    }
                    if (jp1j == 1) {
                        ainvnm = 0.0;
                        for (jA = 0; jA < 8; jA++) {
                            ainvnm += fabs(x[jA]);
                        }
                        if ((!rtIsInf(ainvnm)) && (!rtIsNaN(ainvnm))) {
                            for (jA = 0; jA < 8; jA++) {
                                s = x[jA];
                                smax = fabs(s);
                                if (smax > 2.2250738585072014E-308) {
                                    s /= smax;
                                    x[jA] = s;
                                }
                                else {
                                    x[jA] = 1.0;
                                }
                            }
                            kase = 2;
                            jp1j = 2;
                        }
                        else {
                            kase = 0;
                        }
                    }
                    else if (jp1j == 2) {
                        j = 0;
                        smax = fabs(x[0]);
                        for (jA = 0; jA < 7; jA++) {
                            s = fabs(x[jA + 1]);
                            if (!(s <= smax)) {
                                j = jA + 1;
                                smax = s;
                            }
                        }
                        iter = 2;
                        memset(&x[0], 0, 8U * sizeof(double));
                        x[j] = 1.0;
                        kase = 1;
                        jp1j = 3;
                    }
                    else if (jp1j == 3) {
                        ainvnm = 0.0;
                        for (jA = 0; jA < 8; jA++) {
                            ainvnm += fabs(x[jA]);
                        }
                        if (ainvnm <= x[0]) {
                            s = 1.0;
                            for (jA = 0; jA < 8; jA++) {
                                x[jA] = s * ((((double)jA + 1.0) - 1.0) / 7.0 + 1.0);
                                s = -s;
                            }
                            kase = 1;
                            jp1j = 5;
                        }
                        else {
                            for (jA = 0; jA < 8; jA++) {
                                s = x[jA];
                                smax = fabs(s);
                                if (smax > 2.2250738585072014E-308) {
                                    s /= smax;
                                    x[jA] = s;
                                }
                                else {
                                    x[jA] = 1.0;
                                }
                            }
                            kase = 2;
                            jp1j = 4;
                        }
                    }
                    else if (jp1j == 4) {
                        jjA = j;
                        j = 0;
                        smax = fabs(x[0]);
                        for (jA = 0; jA < 7; jA++) {
                            s = fabs(x[jA + 1]);
                            if (!(s <= smax)) {
                                j = jA + 1;
                                smax = s;
                            }
                        }
                        if ((fabs(x[jjA]) != fabs(x[j])) && (iter <= 5)) {
                            iter++;
                            memset(&x[0], 0, 8U * sizeof(double));
                            x[j] = 1.0;
                            kase = 1;
                            jp1j = 3;
                        }
                        else {
                            s = 1.0;
                            for (jA = 0; jA < 8; jA++) {
                                x[jA] = s * ((((double)jA + 1.0) - 1.0) / 7.0 + 1.0);
                                s = -s;
                            }
                            kase = 1;
                            jp1j = 5;
                        }
                    }
                    else if (jp1j == 5) {
                        s = 0.0;
                        for (jA = 0; jA < 8; jA++) {
                            s += fabs(x[jA]);
                        }
                        s = 2.0 * s / 3.0 / 8.0;
                        if (s > ainvnm) {
                            ainvnm = s;
                        }
                        kase = 0;
                    }
                }
                if (ainvnm != 0.0) {
                    Y = 1.0 / ainvnm / normA;
                }
                if (rtIsNaN(Y)) {
                    boolean_T p;
                    p = false;
                    for (jA = 0; jA < 64; jA++) {
                        if (p || rtIsNaN(A[jA])) {
                            p = true;
                        }
                    }
                    if (!p) {
                        Y = 0.0;
                    }
                }
                exitg2 = 1;
            }
        } while (exitg2 == 0);
    }
    return Y;
}

void write_binary(const real* X_var, const char* variablename, int dim_n)
{
	FILE* fp;
	char filename[250] = { '\0' };
	memset(filename, '\0', sizeof(filename));
	strcpy(filename, PRINTPATH);
	strcat(filename, variablename);
	strcat(filename, ".bin");
	fprintf(stderr, "Opening the file: %s\n", filename);

	// Open the file
	fp = fopen(filename, "wb"); // // wb: write binary
	if (fp == NULL)
	{
		fprintf(stderr, "\n1.1. FAIL: Cannot write the variable %s\n", variablename);
		exit(EXIT_FAILURE);
	}
	// Write binary
	fwrite(X_var, sizeof(X_var[0]), dim_n, fp);

	fclose(fp);
	fp = NULL;
	return;
}

void read_binary(real* X_var, const char* variablename, int dim_n)
{
	FILE* fp;
	char filename[250] = { '\0' };
	memset(filename, '\0', sizeof(filename));
	strcpy(filename, INPUTPATH);
	strcat(filename, variablename);
	strcat(filename, ".bin");
	fprintf(stderr, "Opening the file: %s\n", filename);

	// Open the file
	fp = fopen(filename, "rb"); // // rb: read binary
	if (fp == NULL)
	{
		fprintf(stderr, "\n1.1. FAIL: Cannot read the variable %s\n", variablename);
		exit(EXIT_FAILURE);
	}
	// Variable size
	size_t SIZE_var = dim_n * sizeof(X_var[0]); // Number of bytes
	fprintf(stderr, "\nVariable %s is of size: %lu bytes\n", variablename, SIZE_var);

	// Read binary
	for (int i = 0; i < dim_n; i++)
	{
		fread(&X_var[i], sizeof(X_var[0]), 1, fp);
	}

	fclose(fp);
	fp = NULL;
	return;
}


void transpose(real* matrix,const unsigned int size)
{
	real temp;
	for (unsigned int row = 1; row < size; row++)
	{
		for (unsigned int column = 0; column < row; column++)
		{
			temp = matrix[ELEMENT(row, column, size)];
			matrix[ELEMENT(row, column, size)] = matrix[ELEMENT(column,row,size)];
			matrix[ELEMENT(column, row, size)] = temp;
		}
	}

	return;
}

int main()
{
	//Test rcond
    real matrix[DIMENSION(MATRIX_SIZE)];
	char input_file[]= "RINPUT ";
	char output_file[] = "ROUTPUT ";
	double compare_value;
	for (unsigned char i=0; i < TEST_CNT; i++)
	{
		input_file[6] = i + '0';
		output_file[7] = i + '0';
		read_binary(matrix, input_file, DIMENSION(MATRIX_SIZE));
		std::cout << "GOT FILE\n";
		transpose(matrix, MATRIX_SIZE);
		std::cout << "TRANSPOSED MATRIX\n";
		compare_value = call_rcond(matrix);
		write_binary(&compare_value, output_file, 1);
	}
    std::cout << "PART 1 FINISHED SUCCESSFULLY\n";


	//Test pinv
    real output[DIMENSION(MATRIX_SIZE)];

	input_file[0]= output_file[0] = 'P';
    for (unsigned char i = 0; i < TEST_CNT; i++)
    {
        input_file[6] = i + '0';
        output_file[7] = i + '0';
        read_binary(matrix, input_file, DIMENSION(MATRIX_SIZE));
        transpose(matrix, MATRIX_SIZE);
        call_pinv(matrix, output);
        std::cout << char(i + '0');
        write_binary(output, output_file, DIMENSION(MATRIX_SIZE));
    }
    std::cout << "PART 2 FINISHED SUCCESSFULLY\n";

}

