#!/bin/bash
#SBATCH --account=ucb70_summit1

# Set the QoS (debug = 1 hr; normal = 24 h; long = 7 d)
#SBATCH --qos=normal

#Set the partition (shas, sgpu, sknl, smem)
#SBATCH --partition=shas

# set the number of nodes
#SBATCH --nodes=1

# set the number of tasks (cores) per node (up to 24 on each shas node)
#SBATCH --ntasks-per-node=24

# set max wallclock time (hh:mm:ss)
#SBATCH --time=00:10:00

#Set the job name
#SBATCH --job-name=t1_f1node
#SBATCH --output=t1_1node.%j.out

#Set the mail settings
#SBATCH --mail-type=ALL
#SBATCH --mail-user=peri.alessandro@gmail.com

module purge
echo "Starting the Valgrind"

module load gcc
module load gsl
module load valgrind

dirhome=/scratch/summit/alpe9373/BPU
dirmachine=/z1

cd $dirhome$dirmachine/

INDX_MODEL_START=1
N_MODEL_PER_LAUNCH=3
INDX_MODEL_END=$(($INDX_MODEL_START+$N_MODEL_PER_LAUNCH-1))
echo "Index Model Start: $INDX_MODEL_START Index Model End: $INDX_MODEL_END"
for ((i=$INDX_MODEL_START;i<=$INDX_MODEL_END;i++));
do
echo $i
FILE='lb_cmd_file'
PARAMETERS=$(awk NR==$i $FILE)
valgrind --log-file="${dirhome}${dirmachine}/Output" --track-origins=yes --leak-check=full --show-leak-kinds=all ./BPU_program $i $PARAMETERS
#valgrind --track-origins=yes --leak-check=full --show-leak-kinds=all ./BPU_program $i $PARAMETERS
done

