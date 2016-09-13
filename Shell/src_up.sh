#!/bin/sh

	revision=` svn info svn://192.168.0.6/h3_jt/web_planning/%E7%89%88%E7%BD%B2%E6%9C%8D%E9%85%8D%E7%BD%AE/%E9%80%9A%E7%94%A8%E9%85%8D%E7%BD%AE | grep "Revision"|awk '{print $2}'`
	date_time=`date +%Y.%m.%d`
	version=\"`date +%Y%m%d`$revision\"
	echo "Revision: "$revision
	echo "time: "$date_time
	echo "version:$version"
	echo "=============== update ==============="
	echo "please input: \"config\" or \"server \""
	read type

	if [[ $type == "config" ]]
	  then
#	  	sed -i "2s/\([^[:blank:]]\+\) \(*\)/\1 $vesion/"  config/version/version.json
		config="config_"$date_time.$revision".tar.gz"
		tar zcvf ${config} config
#		scp -P 28004 ${config}  root@:/data/hhweb_dev_s105/server 
		scp -P 28004 ${config} root@183.60.108.112:/data/hzsh_test_t888a/server

	fi

	if [[ $type == "server" ]]
	  then
		cd Debug
		server="server_"$date_time.${revision}".tar.gz"
		tar zcvfp ${server} server
#		scp ${server}  root@172.16.1.233:/data/hhweb_dev_s105/server
		scp -P 28004 ${server} root@183.60.108.112:/data/hzsh_test_t888a/server
	fi
