# **********************************
. ./M00-Var.sh
# **********************************
WDIR=$(pwd)

echo "Remove C-Files"
cd $WDIR
rm -r $WDIR/AuxiliaryCPP
rm -r $WDIR/C

mkdir $WDIR/AuxiliaryCPP
mkdir $WDIR/C

echo "Copy auxiliary files"
cd $AUXILIARY
git checkout $ACOMMIT_ID
git log --format=%B -n 1 $ACOMMIT_ID
git show -s --format=%ci $ACOMMIT_ID

cp $AUXILIARY/*.cpp $WDIR/AuxiliaryCPP/
cp $AUXILIARY/*.h $WDIR/AuxiliaryCPP/

echo 'C Code Version'
cd $C
git checkout $CCOMMIT_ID
git log --format=%B -n 1 $CCOMMIT_ID
git show -s --format=%ci $CCOMMIT_ID

cp $C/*.cpp $WDIR/C/
cp $C/*.h $WDIR/C/
# *************************************
:<<END
echo 'Generate Sobol Nodes'
cd $WDIR
clang++ /Users/alessandroperi/GoogleDrive/C/ProgrammiLinking/XcodeProjects/SimpleModel/GlobalSearch/sobol_dataset/sobol_dataset/main.cpp -o Sobol

chmod u+x Sobol
./Sobol ${PARMS_TBC} ${N_MODEL} ${SKIP}
mv "/Users/alessandroperi/GoogleDrive/C/ProgrammiLinking/XcodeProjects/SimpleModel/GlobalSearch/sobol_${PARMS_TBC}_${N_MODEL}.txt" $WDIR/

echo "Creating the lb_cmd_file"
cp $WDIR/sobol_${PARMS_TBC}_${N_MODEL}.txt $WDIR/tempofile
awk '{printf("./'$PROJECT'_program %d %s\n", NR, $0";")}' tempofile > sobol_${PARMS_TBC}_${N_MODEL}.txt

rm ./tempofile

tar -czvf sobol_${PARMS_TBC}_${N_MODEL}.tar.gz sobol_${PARMS_TBC}_${N_MODEL}.txt
scp $WDIR/sobol_${PARMS_TBC}_${N_MODEL}.tar.gz $HOST/
rm ./sobol_${PARMS_TBC}_${N_MODEL}.txt
# *************************************
echo "Unzip Sobol"
ssh -T $SERVER <<EOF
cd $HOMED
pwd
echo "Unzip the File"
tar -zxvf sobol_${PARMS_TBC}_${N_MODEL}.tar.gz
rm ./sobol_${PARMS_TBC}_${N_MODEL}.tar.gz
ls
EOF
END
# *************************************
echo "Creating the z Directory"
for((i=1;i<=$JOBS;i++));
do
DIRH='v'$i
echo "$WDIR/$DIRH"
rm -r $WDIR/$DIRH
cp -r $WDIR/Input-DONOTTOUCH/ $WDIR/$DIRH/

cd $WDIR/$DIRH
chmod u+x submitjob.sh
chmod u+x M0_create_executable.sh
chmod u+x M1_create_jobmanagement.sh

# Modify submitjob.h
sed -i '' 's/--nodes=/--nodes='$NODES'/g' submitjob.sh
sed -i '' 's/--ntasks-per-node=/--ntasks-per-node='$CORESPERNODE'/g' submitjob.sh
sed -i '' 's/--time=/--time='$TIME'/g' submitjob.sh
sed -i '' 's/--job-name=/--job-name='$PROJECT'_v'$i'/g' submitjob.sh
#sed -i '' 's/--array=1-5/--array='$ARRAY'/g' submitjob.sh
sed -i '' 's:dirhome=:dirhome='$HOMED':g' submitjob.sh
sed -i '' 's:dirmachine=:dirmachine=/'$DIRH':g' submitjob.sh

# Modify M0_create_executable.sh
sed -i '' 's/_program/'$PROJECT'_program/g' M0_create_executable.sh
sed -i '' 's:dirhome=:dirhome='$HOMED':g' M0_create_executable.sh
sed -i '' 's:dirmachine=:dirmachine=/'$DIRH':g' M0_create_executable.sh
sed -i '' 's/Model6Statistics.cpp/Model6Statistics_cal.cpp/g' M0_create_executable.sh

# Modify M1_create_jobmanagement.sh
sed -i '' 's/N_PARMS_TBC=/N_PARMS_TBC='$PARMS_TBC'/g' M1_create_jobmanagement.sh
sed -i '' 's/N_MODEL=/N_MODEL='$N_MODEL'/g' M1_create_jobmanagement.sh
sed -i '' 's/N_MODEL_PER_LAUNCH=/N_MODEL_PER_LAUNCH='$N_MODEL_PER_LAUNCH'/g' M1_create_jobmanagement.sh
#INDX_MODEL_START=$(($N_INITIAL_MODEL+($i-1)*$N_MODEL_PER_LAUNCH))
INDX_MODEL_START=$N_INITIAL_MODEL #$(($N_INITIAL_MODEL+($i-1)*$N_MODEL_PER_LAUNCH))
echo 'Index Model Start: '$INDX_MODEL_START
sed -i '' 's/INDX_MODEL_START=/INDX_MODEL_START='$INDX_MODEL_START'/g' M1_create_jobmanagement.sh

echo "Initialize all the parameters"
cd $WDIR
cp ../InitialParameters/* $WDIR/$DIRH/
cp $WDIR/C/usr_decl.h $WDIR/$DIRH/usr_decl.h

cd $WDIR/$DIRH/
# Modify usr_decl.h
dirhomemachine2='\/scratch\/summit\/alpe9373\/'$PROJECT'\/'$DIRH'\/'
sed -i '' 's/\/Users\/alessandroperi\/GoogleDrive\/Projects\/'$PROJECT'\/C-Results\//'$dirhomemachine2'/g' usr_decl.h
sed -i '' 's/ESTIMATION_SEARCH_ALGORITHM DEACTIVATED_SEARCH/ESTIMATION_SEARCH_ALGORITHM GLOBAL_SEARCH_SOBOL_LOADBALANCE/g' ./usr_decl.h
#sed -i '' 's/const int NKGRID_SHORT  = 128/const int NKGRID_SHORT  = '$NKGRID'/g' usr_decl.h
#sed -i '' 's/const int NBRGRID_SHORT = 128/const int NBRGRID_SHORT = '$NBRGRID'/g' usr_decl.h

echo "Model Specific Modifications"
# Shift the Interval
:<<END
INIT_ALPHAMIN="0.01"
END_ALPHAMIN="3.00"
INTERVAL_ALPHAMAXMIN="0.1"
DELTAV=$(bc -l <<< "(${END_ALPHAMIN}-${INIT_ALPHAMIN})/(${JOBS}-1)")
ALPHAMIN=$(bc -l <<< "${INIT_ALPHAMIN}+(${i}-1)*${DELTAV}")
ALPHAMAX=$(bc -l <<< "${ALPHAMIN} + ${INTERVAL_ALPHAMAXMIN}")
END
# Set the Last Value
ALPHAMIN="0.01"
DELTAV="0.2"
ALPHAMAX=$(bc -l <<< "${ALPHAMIN}+(${i}-1)*${DELTAV}")
sed -i '' '110s:.*:const double alpha_kss_min = '$ALPHAMIN';:g' usr_decl.h
sed -i '' '111s:.*:const double alpha_kss_max = '$ALPHAMAX';:g' usr_decl.h
ALPHAMIND="0.1"
ALPHAMAXD="1.0"
sed -i '' '112s:.*:const double alpha_debt_min = '$ALPHAMIND';:g' usr_decl.h
sed -i '' '113s:.*:const double alpha_debt_max = '$ALPHAMAXD';:g' usr_decl.h
echo "v${i}: DELTA ${DELTAV} DEBT(ALPHAMIN=${ALPHAMIND} ALPHAMAX=${ALPHAMAXD}) KAPITAL(ALPHAMIN=${ALPHAMIN} ALPHAMAX=${ALPHAMAX})"

:<<END2
echo "Modify the usr_decl.h file"
sed -i '' '218s:.*:    \{'0.699999988079071','0.5','0.8'\},                              //I_ALPHA, 0:g' usr_decl.h
sed -i '' '219s:.*:    \{'0.850000023841858','0.5','0.9'\},                             // I_ALPHA2,           // 1:g' usr_decl.h
sed -i '' '220s:.*:    \{'0.10','0.01','0.45'\},                            //I_DELTA,            // 2  // I_PHI_ADJ, // I_OMEGA_ADJ,:g' usr_decl.h
sed -i '' '221s:.*:    \{'0.602890115905247','0.4','0.8'\},                    //I_CHI0,             // 3 //I_CHI1,I_THETA_A0, I_THETA_A1,:g' usr_decl.h
sed -i '' '223s:.*:    \{'0.443597','0.20','0.50'\},                           //I_THETAUL,          // 4:g' usr_decl.h
sed -i '' '224s:.*:    \{'0.551526','0.35','0.60'\},                            //I_THETAUH,          // 5:g' usr_decl.h
sed -i '' '225s:.*:    \{'0.790216','0.6977','0.80'\},                          //I_PROB_THETAUH,     // 6 //I_EQUISSINCFIX,:g' usr_decl.h
sed -i '' '226s:.*:    \{'1.12','1.05','1.12'\},                           //I_EQUISSINCVAR,     // 7:g' usr_decl.h
sed -i '' '227s:.*:    \{'1.429015','1.35','1.50'\},                           //I_EQUISSINCVAR_R,   // 8:g' usr_decl.h
sed -i '' '228s:.*:    \{'0.461875','0.44','0.60'\},                           //I_PSI,              // 8:g' usr_decl.h
sed -i '' '229s:.*:    \{'0.000000000','0.','0.'\},                                 //I_CHIBKP,           // 9:g' usr_decl.h
sed -i '' '230s:.*:    \{'0.158706','0.10','0.30'\},                             //I_THETABARG,        // 10 \{0.5,0.1,0.75\}:g' usr_decl.h
sed -i '' '231s:.*:    \{'0.000000000','0.','1.'\},                                 //I_LAMBDA_LOSS,      // 11 //I_CHIBARGBANK,I_CHIBARGFIRM,:g' usr_decl.h
sed -i '' '232s:.*:    \{'0.027106','0.','8.'\},                                 //I_C11,              // 12:g' usr_decl.h
sed -i '' '233s:.*:    \{'1.','1.','1.'\},                                 //I_S11CL,            // 13:g' usr_decl.h
sed -i '' '234s:.*:    \{'1.','1.','1.'\},                                 //I_S11CH,            // 14:g' usr_decl.h
sed -i '' '235s:.*:    \{'0.983377','1.','1.'\},                                 //I_S11PL,            // 15:g' usr_decl.h
sed -i '' '236s:.*:    \{'1.','1.','1.'\},                                 //I_S11PH,            // 16:g' usr_decl.h
sed -i '' '237s:.*:    \{'0.303695650374130','0.','0.5'\},                               //I_ENTRYCOST,        // 17//I_ZETA,:g' usr_decl.h
sed -i '' '238s:.*:    \{'0.','0.','0.'\},                                 //I_K0E,              // 18   //I_EQUISSENTFIX,:g' usr_decl.h
sed -i '' '239s:.*:    \{'1.12','1.','1.5'\},                                //I_EQUISSENTVAR,     // 19:g' usr_decl.h
sed -i '' '240s:.*:    \{'0.961499989032745','0.9615','0.9615'\},                     //I_BETA,             // 20:g' usr_decl.h
sed -i '' '241s:.*:    \{'0.039999999105930','0.04','0.04'\},                           //I_RF,               // 21:g' usr_decl.h
sed -i '' '242s:.*:    \{'1.','1.','1.'\},                                 //I_LS,               // 22 //I_DIP_SPREAD,:g' usr_decl.h
sed -i '' '243s:.*:    \{'0.','0.','0.'\},                                 //I_MU_U_LOGX,        // 23:g' usr_decl.h
sed -i '' '244s:.*:    \{'0.21884462','0.01','0.75'\},                           //I_STD_U_LOGX,       // 24:g' usr_decl.h
sed -i '' '245s:.*:    \{'0.6690852','0.75','0.98'\},                           //I_RHO_LOGX,         // 25   //I_PARETOXMIN, I_PARETOKAPPAX,:g' usr_decl.h
sed -i '' '246s:.*:    \{'0.99','0.90','0.999'\},                             //I_PARETOKMIN,       // 26// (kappa -1) k_min^(kappa-1)  x^\{-kappa\}:g' usr_decl.h
sed -i '' '247s:.*:    \{'2.00000062109374999999996','1.85','2.2'\},       //I_PARETOKAPPAK,   Taken from Why Has CEO Pay Increased So Much, Gabaix Landier 2008:g' usr_decl.h
sed -i '' '250s:.*:    \{'0.030697','0.02','0.07'\}                           //I_THETA1,           // 28 //I_THETA2, //I_EXPECTX:g' usr_decl.h

sed -i '' '80s:.*:#define PARAMETERS_TXT    0:g' usr_decl.h
END2
done
rm $WDIR/C/usr_decl.h

# *********************************** COPYING THE FILE TO THE SERVER PHASE
echo 'Remove Files Remotely'
ssh $SERVER << EOF
rm -r $HOMED/AuxiliaryCPP
rm -r $HOMED/C
#rm -r $HOMED/v*
cd $HOMED
echo "DIRECTORY: ${HOMED}"
LISTA=\$(ls -d v*)
LISTAARRAY=(\$LISTA)
for DIRECTORY in "\${LISTAARRAY[@]}"
do
echo "REMOVE DIRECTORY: \${DIRECTORY}"
mkdir empty_dir
rsync -a --delete empty_dir/ \$DIRECTORY/
rm -r empty_dir/
rm -r \$DIRECTORY/
done
EOF
echo 'Copy the Files'
scp -r $WDIR/AuxiliaryCPP $HOST/AuxiliaryCPP
scp -r $WDIR/C $HOST/C
for((i=1;i<=$JOBS;i++));
do
DIRH='v'$i
echo "Copy ${DIRH}"
scp -r $WDIR/$DIRH $HOST/$DIRH
done

echo "Connecting Remotely: Creating Executables and Launching"
ssh $SERVER <<EOF
ssh scompile
#Modifying the malloc
mkdir $HOMED/Results
# https://www.unix.com/shell-programming-and-scripting/148995-variables-inside-ssh-session.html
for((i=1;i<=$JOBS;i++));
do
DIRH='v'\$i
echo aux=\$DIRH
cd $HOMED/\$DIRH
pwd
echo "Compiling the Code"
chmod u+x M0_create_executable.sh
./M0_create_executable.sh
echo "Creating lb_cmd_file"
chmod u+x M1_create_jobmanagement.sh
./M1_create_jobmanagement.sh && _
echo "Launching the job"
chmod u+x submitjob.sh
sbatch $HOMED/\$DIRH/submitjob.sh
done
EOF
