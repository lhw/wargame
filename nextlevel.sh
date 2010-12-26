#!/bin/sh
if [ $(/usr/bin/id -g) -ne $(/usr/bin/id -g -r) ]; then
	/usr/bin/groups $(/usr/bin/id -u -n -r) | /bin/grep -q $(/usr/bin/id -g -n)
	if [ $? -eq 0 ]; then
		echo "you already submitted this level ;)"
	else
		echo "congratz, you made it :)"
		/usr/sbin/usermod -a -G $(/usr/bin/id -g -n) $(/usr/bin/id -u -r -n)
		echo $(/bin/date +'%s ')$(/usr/bin/id -u -r -n)$(/bin/echo -en " -> ")$(/usr/bin/id -g -n) >> /var/log/stats
	fi
fi
