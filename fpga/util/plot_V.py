"""
This script can be used to plot the value function.

To run this script use the following command
make validate
"""
import numpy as np
import pandas as pd
import os

path = os.getcwd()
cpu_folder = "results/seq_cpu/double/final_values"
file_names_cpu = "V_serial-cpu_nk100.txt"

#first iter
# file_names_ref = ["in_kprime.txt", "cpu_kprime.txt", "in_cpu_kcross.txt", "cpu_kcross.txt"] #file names of results 
file_names_ref = ["mat_nk100_nkm4_kcross.txt", "mat_nk200_nkm4_kcross.txt", "mat_nk300_nkm4_kcross.txt", 
                  "mat_nk100_nkm4_kprime.txt",  "mat_nk200_nkm4_kprime.txt", "mat_nk300_nkm4_kprime.txt",
                  "mat_nk100_nkm4_coeffs.txt", "mat_nk200_nkm4_coeffs.txt", "mat_nk300_nkm4_coeffs.txt",
                  "mat_nk100_nkm4_r2bg.txt", "mat_nk200_nkm4_r2bg.txt", "mat_nk300_nkm4_r2bg.txt" ] #file names of results 
file_names_cpu = ["kcross_serial-cpu_nKM4-nk100.txt", "kcross_serial-cpu_nKM4-nk200.txt", "kcross_serial-cpu_nKM4-nk300.txt", 
                  "kpo_serial-cpu_nKM4-nk100.txt", "kpo_serial-cpu_nKM4-nk200.txt", "kpo_serial-cpu_nKM4-nk300.txt",
                  "coeffs_serial-cpu_nKM4-nk100.txt", "coeffs_serial-cpu_nKM4-nk200.txt", "coeffs_serial-cpu_nKM4-nk300.txt",
                  "r2bg_serial-cpu_nKM4-nk100.txt", "r2bg_serial-cpu_nKM4-nk200.txt", "r2bg_serial-cpu_nKM4-nk300.txt" ] #file names of results 
file_names_fpga = ["kcross_fpga_nkM4-nk100_i0_d0_k0.txt", "kcross_fpga_nkM4-nk200_i0_d0_k0.txt", "kcross_fpga_nkM4-nk300_i0_d0_k0.txt", 
                  "kpo_fpga_nkM4-nk100_i0_d0_k0.txt", "kpo_fpga_nkM4-nk200_i0_d0_k0.txt", "kpo_fpga_nkM4-nk300_i0_d0_k0.txt",
                  "coeffs_fpga_nkM4-nk100_i0_d0_k0.txt", "coeffs_fpga_nkM4-nk200_i0_d0_k0.txt", "coeffs_fpga_nkM4-nk300_i0_d0_k0.txt",
                  "r2bg_fpga_nkM4-nk100_i0_d0_k0.txt", "r2bg_fpga_nkM4-nk200_i0_d0_k0.txt", "r2bg_fpga_nkM4-nk300_i0_d0_k0.txt"] #file names of results 

# test_folder = fpga_folder
test_folder = cpu_folder
# file_names_test = file_names_fpga
file_names_test = file_names_cpu
for i in range(len(file_names_ref)):
    sw_file = (os.path.join(path, ref_folder, file_names_ref[i]))
    hw_file = (os.path.join(path, test_folder, file_names_test[i]))

    A = pd.read_csv(sw_file, header=None, delimiter='\n')
    B = pd.read_csv(hw_file, header=None, delimiter='\n')

    equal = np.allclose(A,B,rtol=1e-05, atol=1e-09, equal_nan=False) #absolute(a-b) <= (atol + rtol*absolute(b))
    max_diff = np.max(np.abs(A-B), axis=0)
    avg_diff = np.mean(np.abs(A-B), axis=0)

    if(equal):
        print("\n{} Test Passed".format(file_names_test[i]))
    else:
        print("\n{} Test Failed: Results mismatch".format(file_names_test[i]))

    print("{} Absolute maximum difference is: {}".format(file_names_test[i], max_diff))
    print("{} Mean of the difference is: {}\n".format(file_names_test[i], avg_diff))


test_folder = fpga_folder
# test_folder = cpu_folder
file_names_test = file_names_fpga
# file_names_test = file_names_cpu
for i in range(len(file_names_ref)):
    sw_file = (os.path.join(path, ref_folder, file_names_ref[i]))
    hw_file = (os.path.join(path, test_folder, file_names_test[i]))

    A = pd.read_csv(sw_file, header=None, delimiter='\n')
    B = pd.read_csv(hw_file, header=None, delimiter='\n')

    equal = np.allclose(A,B,rtol=1e-05, atol=1e-09, equal_nan=False) #absolute(a-b) <= (atol + rtol*absolute(b))
    max_diff = np.max(np.abs(A-B), axis=0)
    avg_diff = np.mean(np.abs(A-B), axis=0)

    if(equal):
        print("\n{} Test Passed".format(file_names_test[i]))
    else:
        print("\n{} Test Failed: Results mismatch".format(file_names_test[i]))

    print("{} Absolute maximum difference is: {}".format(file_names_test[i], max_diff))
    print("{} Mean of the difference is: {}\n".format(file_names_test[i], avg_diff))
