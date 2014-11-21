#!/bin/bash
read -p "Username: " user
read -s -p "Password: " password
echo ""
for i in {01..10}; do
	mkdir $i
	wget --user=$user --password=$password --no-check-certificate "https://biro.inf.u-szeged.hu/Hallg/IB103e/$((${i#0}+1))/$user/feladat.pdf" -O "./$i/feladat.pdf" -o /dev/null
	wget --user=$user --password=$password --no-check-certificate "https://biro.inf.u-szeged.hu/Hallg/IB103e/$((${i#0}+1))/$user/minta.zip" -O "./$i/minta.zip" -o /dev/null
	unzip "./$i/minta.zip" -d "./$i"
done
