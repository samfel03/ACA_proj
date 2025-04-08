#!/bin/bash
mkdir single
mkdir single
cp -R fpga/logs single/logs
cp -R fpga/reports single/reports
mv *.dcp single/
cp *.awsxclbin single/
cp host single/
tar -cf single.zip single