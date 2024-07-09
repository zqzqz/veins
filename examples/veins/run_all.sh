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

### scheme Options ###
# Scheme2 Scheme3 Scheme2_Pi Scheme3_Pi

### numCpuCores Options ###
# 1 2 3 4 ...

### map Options ###
# intersection_500 intersection_1000 intersection_1500 intersection_max
# beijing_200 beijing_500 beijing_1000 beijing_1500 beijing_2000
# paris_100 paris_300 paris_500 paris_700 paris_1000

schemes="Scheme3" 
numCpuCores="1 2 3 4"
maps="intersection_500 intersection_1000 intersection_1500 intersection_max"

config="omnetpp.ini"
logfile="simulation.log"
recordlog="record.log"
cp ${config} ${config}.bk

for map in $maps
do
	for scheme in $schemes
	do
		for numCpuCore in $numCpuCores
		do
			echo "Experiment ${scheme} ${map} ${numCpuCore}"
			sed -i "s/maps\/intersection_500/maps\/${map}/g" ${config}
			sed -i "s/rsu\[\*\]\.appl\.numCpuCores = 1/rsu[*].appl.numCpuCores = ${numCpuCore}/g" ${config}
			# customize RSU position
			if [[ $map == intersection_* ]]; then
				sed -i "s/\.mobility\.x = 225/\.mobility\.x = 225/g" ${config}
				sed -i "s/\.mobility\.y = 225/\.mobility\.y = 225/g" ${config}
				sed -i "s/rsu_x = 225/rsu_x = 225/g" ${config}
				sed -i "s/rsu_y = 225/rsu_y = 225/g" ${config}
			fi
			if [[ $map == beijing_* ]]; then
				sed -i "s/\.mobility\.x = 225/\.mobility\.x = 940/g" ${config}
				sed -i "s/\.mobility\.y = 225/\.mobility\.y = 870/g" ${config}
				sed -i "s/rsu_x = 225/rsu_x = 940/g" ${config}
				sed -i "s/rsu_y = 225/rsu_y = 870/g" ${config}
			fi
			if [[ $map == paris_* ]]; then
				sed -i "s/\.mobility\.x = 225/\.mobility\.x = 670/g" ${config}
				sed -i "s/\.mobility\.y = 225/\.mobility\.y = 570/g" ${config}
				sed -i "s/rsu_x = 225/rsu_x = 670/g" ${config}
				sed -i "s/rsu_y = 225/rsu_y = 570/g" ${config}
			fi
			opp_run -r 0 -m -u Cmdenv -c "${scheme}" -n .:../../src/veins --image-path=../../images -l ../../src/veins ${config}
			sed -i -n "/\[WARN\]/p" ${logfile}
			echo "Succeeded transactions: " >> ${recordlog}
			cat ${logfile} | grep -c "succeed" >> ${recordlog}
			echo "Failed transactions: " >> ${recordlog}
			cat ${logfile} | grep -c "fail"  >> ${recordlog} || echo "All succeed!"  >> ${recordlog}
			mv ${logfile} ${data_dir}/dsrc_${scheme}_${map}_${numCpuCore}.log
			cp ${config}.bk ${config}
		done
	done
done

rm ${config}.bk