#!/bin/bash

cleanup() {
	local exit_status=$?
	if [[ $exit_status != 0 ]]; then
		if [[ -f ${config}.bk ]]; then
			mv ${config}.bk ${config}
		fi
	fi
}

trap cleanup EXIT

set -e

data_dir=${1}
if [[ -z "$data_dir" ]]; then
	echo "Input the path to save results as the first parameter.\n"
	exit
fi

if [[ ! -d ${data_dir} ]]; then
	mkdir -p ${data_dir}
fi
# Schem2 Scheme3
schemes="Scheme2_Pi Scheme3_Pi" 
# 1 2 3 4
numCpuCores="1 2 3 4"
# intersection_500 intersection_1000 intersection_1500 intersection_max
# beijing_200 beijing_500 beijing_1000 beijing_1500 beijing_2000
# paris_100 paris_300 paris_500 paris_700 paris_1000
maps="intersection_500 intersection_1000 intersection_1500 intersection_max"
# PerceptionApp AuctionApp
apps="GeneralApp"

config="omnetpp.ini"
logfile="simulation.log"
cp ${config} ${config}.bk

for map in $maps
do
	for scheme in $schemes
	do
		for app in $apps
		do
			for numCpuCore in $numCpuCores
			do
				echo "Experiment ${scheme} ${map} ${app} ${numCpuCore}"
				sed -i "s/maps\/intersection/maps\/${map}/g" ${config}
				sed -i "s/rsu\[\*\]\.appl\.numCpuCores = 1/rsu[*].appl.numCpuCores = ${numCpuCore}/g" ${config}
				opp_run -r 0 -m -u Cmdenv -c "${scheme}_${app}" -n .:../../src/veins --image-path=../../images -l ../../src/veins ${config}
				sed -i -n "/\[WARN\]/p" ${logfile}
				echo "Succeeded transactions: "
				cat ${logfile} | grep -c "succeed"
				echo "Failed transactions: "
				cat ${logfile} | grep -c "fail" || echo "All succeed!"
				mv ${logfile} ${data_dir}/dsrc_${scheme}_${map}_${app}_${numCpuCore}.log
				cp ${config}.bk ${config}
			done
		done
	done
done

rm ${config}.bk
