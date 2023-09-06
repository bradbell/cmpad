#! /usr/bin/env bash
set -e -u
if [ $# != 0 ]
then
   echo 'check_python.sh does not expect any arguments'
   exit 1
fi
if [ "$0" != 'bin/check_python.sh' ]
then
   echo 'bin/check_python.sh: must execute from its parent directory'
   exit 1
fi
# ---------------------------------------------------------------------------
#
PYTHONPATH="$(pwd)/python:$PYTHONPATH"
pytest python/xam/*.py
#
echo 'check_python.sh: OK'
exit 0
