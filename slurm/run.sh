#!/usr/bin/env bash

#SBATCH --job-name="testmulti"
# #SBATCH --account="HerrComp" # not used
#SBATCH --mail-type=ALL
#SBATCH --mail-user=wfoquendop@unal.edu.co
#SBATCH --time=01:00:00
#SBATCH --nodes=3
#SBATCH --ntasks-per-node=6
#SBATCH --cpus-per-task=1
#SBATCH --partition=12threads

srun -p 12threads -n 4 -c 4  stress -t 20 -c 4
