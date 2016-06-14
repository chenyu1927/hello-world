#!/bin/sh

SVN_DIR=/data/svn/webgame_svn
SVN_BAKDIR=/svnbak/dump
DATE=$(date +%Y%m%d)
VER=$(svnlook youngest $SVN_DIR)
LOG=/tmp/fullsvn.log
/usr/bin/svnadmin dump $SVN DIR > $SVN_BAKDIR/full $DATE 2>$LOG
if [ $? -eq 0]; then
	echo $VER > /tmp/version
	else
	echo "fullsvn bak is failed" >> $LOG
fi

