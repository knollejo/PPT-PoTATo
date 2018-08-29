#!/bin/bash
cd $1
source /cvmfs/cms.cern.ch/cmsset_default.sh
eval `scramv1 runtime -sh`
./run $2 $3 $4 $5 $6 $7 $8 2>&1
