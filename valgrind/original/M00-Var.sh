# **********************************
CCOMMIT_ID='0adc645' #10Parameters-32K-LogB-smallgrid thetau thetah
ACOMMIT_ID='2588745' # DESCRIPTION
PARMS_TBC=10

NKGRID=32
NBRGRID=128

USERNAME='alpe9373'
PROJECT='BPU'
SERVER="${USERNAME}@login.rc.colorado.edu"
HOMED="/scratch/summit/${USERNAME}/${PROJECT}"
SAVED="/projects/${USERNAME}/${PROJECT}"
VALGRIND="/Users/alessandroperi/GoogleDrive/Projects/${PROJECT}/Calibration/Valgrind/"
# **********************************
HOST=$SERVER':'$HOMED
# **********************************
AUXILIARY='/Users/alessandroperi/GoogleDrive/C/Projects/AuxiliaryCPP'
C='/Users/alessandroperi/GoogleDrive/C/Projects/BPUCPP'
# **********************************
JOBS='30'
N_INITIAL_MODEL=1
N_MODEL_PER_LAUNCH=2000
N_MODEL=1000000
SKIP=150
TIME='06:00:00'
NODES='5'
CORESPERNODE='24'
# **********************************
BATCH='P10-K32-0.01-6.00-IVAR0.2-D0.1-1-M2000-LogB'
