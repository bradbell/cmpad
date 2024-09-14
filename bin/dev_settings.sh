# ---------------------------------------------------------------------------
# SPDX-License-Identifier: EPL-2.0 OR GPL-2.0-or-later
# SPDX-FileCopyrightText: Bradley M. Bell <bradbell@seanet.com>
# SPDX-FileContributor: 2003-24 Bradley M. Bell
# ---------------------------------------------------------------------------
#
# source bin/dev_settings.sh
# Sets the development tool variables listed below to settings for this system.
#
# Directories
# If an file name below is a directory it specifies all the 
# files in the directory.
#
# spdx_license_id
# Each file, except those specified by no_copyright_list, should have a line
# that ends with the following text:
spdx_license_id='EPL-2.0 OR GPL-2.0-or-later'
#
# no_copyright_list
# These files do not have the spdx license id in them.
# BEGIN_SORT_THIS_LINE_PLUS_2
no_copyright_list='
   .gitignore
   .readthedocs.yaml
   readme.md
   xam_main.csv
'
# END_SORT_THIS_LINE_MINUS_2
#
# invisible_and_tab_ok
invisible_and_tab_ok='
'
#
# check_commit
# These files may have automatic changes that should not be commited.
# Including them in this list gives one this option to abort their changes.
check_commit='
   xam_main.csv
'
