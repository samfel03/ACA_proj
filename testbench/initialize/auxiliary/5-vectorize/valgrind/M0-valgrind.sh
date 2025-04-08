# **********************************
PROJECT='CCE-C'
USERNAME='alpe9373'
SERVER="${USERNAME}@login.rc.colorado.edu"
HOMED="/scratch/summit/${USERNAME}/${PROJECT}"
SAVED="/projects/${USERNAME}/${PROJECT}"
VALGRIND="/Users/alessandroperi/Dropbox/Projects/CCE-FPGA/${PROJECT}/valgrind/"
HOST=$SERVER':'$HOMED
# **********************************

WDIR=$(pwd)
echo $WDIR
cp ../main.cpp ./main.cpp
sed -i '' 's:/Users/alessandroperi/Dropbox/Projects/CCE-FPGA/CCE-C/testbench/initialize/auxiliary/5-vectorize/:/scratch/summit/alpe9373/CCE-C/auxiliary/:g'  main.cpp
scp $WDIR/main.cpp $HOST/auxiliary/main.cpp
scp ../A.bin $HOST/auxiliary
