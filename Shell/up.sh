#!/bin/sh

	revision=`svn info svn://192.168.0.6/h3_jt/web_server/server/source/latest_server/server | grep "Revision"|awk '{print $2}'`
	date_time=`date +%Y.%m.%d`
	echo "Revision: "$revision
	echo "time: "$date_time
	echo "=============== update ==============="
	echo "please input: \"config\" or \"server \""
	read type

	if [[ $type == "config" ]]
	  then
		config="config_"$date_time.$revision".tar.gz"
		tar zcvf ${config} config
		scp ${config}  root@192.168.0.6:/data/jtweb_dev_s1/server
	fi

	if [[ $type == "server" ]]
	  then
		cd Debug
		server="server_"$date_time.${revision}".tar.gz"
		tar zcvfp ${server} server
		scp ${server}  root@192.168.0.6:/data/jtweb_dev_s1/server
	fi

	if [[ $type == "localserver" ]]; then
	    cd Debug
		server="server_"$date_time.$revision".tar.gz"
		tar zcvfp ${server} server
#		scp ${server} root@
	fi
