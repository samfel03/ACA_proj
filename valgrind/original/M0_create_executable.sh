#!/bin/bash

module purge
echo "Compiling the code"

module load gcc
module load gsl
module load valgrind

dirhome=/scratch/summit/alpe9373/BPU
dirmachine=/z1
diraux='/AuxiliaryCPP'
dircode='/C'

cd $dirhome$dirmachine

g++ -std=c++11 -g -I /curc/sw/gsl/2.4/gcc/6.1.0/include/gsl/ -I /curc/sw/gsl/2.4/gcc/6.1.0/include/ -I $dirhome$dirmachine/ -I $dirhome$dircode/ -I $dirhome$diraux/ $dirhome$diraux/AR1.cpp $dirhome$diraux/Checks1.cpp $dirhome$diraux/CustomAR1.cpp $dirhome$diraux/Distributions.cpp $dirhome$diraux/Distributions.h $dirhome$diraux/dynalloc.cpp $dirhome$diraux/Efx_GaussLegendre.cpp $dirhome$diraux/Efx_quad.cpp $dirhome$diraux/Efx.cpp $dirhome$diraux/Efx2.cpp $dirhome$diraux/EfxCh7.cpp $dirhome$diraux/Firms.h $dirhome$diraux/Gauss_Legendre_2pts.cpp $dirhome$diraux/Gauss_Legendre_10pts.cpp $dirhome$diraux/GaussLegendre_NodesWeights.h $dirhome$diraux/libdynalloc.h  $dirhome$diraux/linear_interpolation2.cpp $dirhome$diraux/linearalgebra_fun.cpp $dirhome$diraux/linearalgebra_fun.h $dirhome$diraux/local_search.cpp $dirhome$diraux/local_search.h $dirhome$diraux/Model1SobolNodes.cpp $dirhome$diraux/Nodes.cpp $dirhome$diraux/Nodes.h $dirhome$diraux/normalization_shock.cpp $dirhome$diraux/numerical_approximations.h $dirhome$diraux/ProjectFunctions.h $dirhome$diraux/Quadrature.cpp $dirhome$diraux/Tauchen1986.cpp $dirhome$diraux/TauchenHussey1991.cpp $dirhome$diraux/UncertaintyFunctions.h $dirhome$diraux/utils.cpp $dirhome$diraux/utils.h $dirhome$diraux/vec_partialsorting.cpp $dirhome$dircode/Firms0Incumbents.cpp $dirhome$dircode/Firms1EndEntrants.cpp $dirhome$dircode/Firms2InvDist_FixPoint.cpp $dirhome$dircode/local_search_usr_decl.cpp $dirhome$dircode/main.cpp $dirhome$dircode/Model.cpp $dirhome$dircode/Model1Parameters.cpp $dirhome$dircode/Model2Uncertainty.cpp $dirhome$dircode/Model4GridsEndStates.cpp $dirhome$dircode/Model5Equilibrium.cpp $dirhome$dircode/Model6Statistics.cpp $dirhome$dircode/Model7StoreResults.cpp $dirhome$dircode/ModelSpecific.cpp $dirhome$dirmachine/usr_decl.h -L /curc/sw/gsl/2.4/gcc/6.1.0/lib/ -L /curc/sw/gcc/6.1.0/lib64/ -lgsl -lgslcblas -o BPU_program -lm

chmod u+x ./BPU_program
