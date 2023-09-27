#! /usr/bin/env bash
# ---------------------------------------------------------------------------
# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2023 Bradley M. Bell
# ---------------------------------------------------------------------------
set -e -u
# -----------------------------------------------------------------------------
# bash function that echos and executes a command
echo_eval() {
	echo $*
	eval $*
}
# -----------------------------------------------------------------------------
#
if [ $# != 0 ]
then
   echo 'usage: bin/git_commit.sh: does not expect arugments'
   exit 1
fi
if [ "$0" != 'bin/git_commit.sh' ]
then
   echo 'bin/git_commit.sh: must execute this script from its parent directory'
   exit 1
fi
if [ ! -e './.git' ]
then
   echo 'bin/git_commit.sh: cannot find ./.git'
   exit 1
fi
# -----------------------------------------------------------------------------
# EDITOR
set +u
if [ "$EDITOR" == '' ]
then
   echo 'bin/git_commit.sh: EDITOR is not defined.'
   exit 1
fi
set -u
# -----------------------------------------------------------------------------
# xam_main.csv
for lang in 'cpp' 'python'
do
   csv_file="$lang/xam_main.csv"
   pattern=$( echo "$csv_file" | sed -e 's|/|[/]|g' )
   if git status --porcelain | grep "$pattern" > /dev/null
   then
      res=''
      while [ "$res" != 'yes' ] && [ "$res" != 'no' ]
      do
         read -p "revert to old $csv_file [yes/no] ?" res
      done
      if [ "$res" == 'yes' ]
      then
         echo "removing change to $csv_file"
         git reset "$csv_file"   > /dev/null
         git checkout "$csv_file" > /dev/null
      fi
   fi
done
# -----------------------------------------------------------------------------
# new files
list=$(git status --porcelain | sed -n -e '/^?? /p' | sed -e 's|^?? ||')
for file in $list
do
   res=''
   while [ "$res" != 'delete' ] && [ "$res" != 'add' ] && [ "$res" != 'abort' ]
   do
      read -p "$file is uknown to git, [delete/add/abort] ?" res
   done
   if [ "$res" == 'delete' ]
   then
      echo_eval rm $file
   elif [ "$res" == 'abort' ]
   then
      echo 'bin/git_commit.sh: aborting'
      exit 1
   fi
done
# -----------------------------------------------------------------------------
# git_commit.log
branch=$(git branch --show-current)
cat << EOF > git_commit.log
$branch: Comments about this commit go in this file.
If you delete all the lines in this file, this commit will abort.
Below is a list of the files that will be changed by this commit:
EOF
git status --porcelain >> git_commit.log
$EDITOR git_commit.log
#
if grep 'If you delete all the lines in this file,' git_commit.log > /dev/null
then
   echo 'Aborting because you left documentation lines in commit log'
   exit 1
fi
if grep 'Below is a list of the files that will' git_commit.log > /dev/null
then
   echo 'Aborting because you left documentation lines in commit log'
   exit 1
fi
# -----------------------------------------------------------------------------
#
# git add
echo_eval git add --all
#
#
# git commit
git commit --file=git_commit.log
#
echo 'bin/git_commit.sh: OK'
exit 0
