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
set +u
if [ "$EDITOR" == '' ]
then
   echo 'bin/git_commit.sh: EDITOR is not defined.'
   exit 1
fi
set -u
# -----------------------------------------------------------------------------
list=$(git status --porcelain | sed -n -e '/^?? /p' | sed -e 's|^?? ||')
for file in $list
do
   res=''
   while [ "$res" != 'delete' ] && [ "$res" != 'add' ] [ "$res" != 'abort' ]
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
$branch: 1. General comments about this git commit go here.
2. If you delete all the lines in this file, this commit will abort.
3. All the files below will be included in this commit. 
4. Delete the lines below if you do not want them in the commit message.
EOF
git status --porcelain >> git_commit.log
$EDITOR git_commit.log
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

