# **********************************
. ./M00-Var.sh
# **********************************
WDIR=$(pwd)
echo $WDIR

echo "Remove C-Files"
cd $WDIR
rm -r $WDIR/common
rm -r $WDIR/cpu
mkdir $WDIR/common
mkdir $WDIR/cpu

echo "Copy C-Files in local valgrind folder"
cp $C/common/*.cpp $WDIR/common/
cp $C/common/*.h $WDIR/common/
cp $C/cpu/*.cpp $WDIR/cpu/
cp $C/cpu/*.h $WDIR/cpu/

echo 'Remove Files Remotely'
ssh $SERVER << EOF
rm -r $HOMED/common
rm -r $HOMED/cpu
EOF

echo 'Modify the Files'
cd $WDIR/common/
sed -i '' 's:/Users/alessandroperi/Dropbox/Projects/CCE-FPGA/CCE-C/C/input/:/scratch/summit/alpe9373/CCE-C/input/:g'  definitions.h

echo 'Copy Files remotely'
cd $WDIR
scp -r $WDIR/common/ $HOST/common/
scp -r $WDIR/cpu $HOST/cpu
#scp -r /Users/alessandroperi/Dropbox/Projects/CCE-FPGA/CCE-C/C/input/  alpe9373@login.rc.colorado.edu:/scratch/summit/alpe9373/CCE-C/


:<<END
ssh $SERVER << EOF
ssh scompile
module load gcc
module load gsl
module load valgrind
g++ -D_SERIAL_CPU_MODE  -I./cpu  -Wall -O3 -g -std=c++11 -lpthread -lstdc++ -L/usr/local/lib -lm common/init.cpp common/app.cpp -o app
valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all ./app
EOF
END