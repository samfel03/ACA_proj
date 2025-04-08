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
sed -i '' 's:/Users/alessandroperi/Dropbox/Projects/CCE-FPGA/CCE-C/C/input/:/scratch/summit/alpe9373/CCE-C/input/:g'  main.cpp
sed -i '' 's:/Users/alessandroperi/Dropbox/Projects/CCE-FPGA/CCE-C/C/output/:/scratch/summit/alpe9373/CCE-C/output/:g'  main.cpp

scp $WDIR/main.cpp $HOST/auxiliary/main.cpp
