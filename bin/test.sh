#! /usr/bin/env bash
set -e -u
#
job='check_python'
build_type='release'
#
# environment.sh
source bin/environment.sh
#
if [ "$job" == 'debug' ]
then
   file='python/xam/grad_torch.py'
   git checkout $file
   sed -i -e 's|assert \(.*\)() == True|&\n\1()|' $file
   python -m pdb $file
   git checkout $file
elif [ "$job" == 'check_python' ]
then
   python/bin/check_python.py $build_type
elif [ "$job" == 'xam_main' ]
then
   bin/xam_main.py
else
   echo 'temp.sh: job is invalid'
   exit
fi
#
echo 'temp.sh: OK'
exit 0
