#/usr/bin/bash

url=http://www.airspayce.com/mikem/bcm2835/bcm2835-1.38.tar.gz
dirname=bcm2835-1.38
tarname=$dirname.tar.gz


cd lib && wget $url && tar -xzf $tarname && rm $tarname 
