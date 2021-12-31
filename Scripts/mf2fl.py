# Exact file list main for source insight from make file based build system
# Usage:
#     Step1: use command make -j4 >> make.txt to collect the build process
#     Step2: use makefiletofl.bat >> fl.txt to generate the file list to fl.txt
#     Step3: Form source insight, add files from fl.txt
import getopt, sys
import argparse
import glob
import os

inputfile = open('make.txt')  # Open file
my_text = inputfile.readlines()
inargs = []
save_next = False
include_dir = set()
source_files = set()

for line in my_text:
    array = line.split()
    
    inargs.clear()
    for item in array:
        if save_next == True:
            inargs.append(item)
            save_next = False
            continue
            
        if item[0:2] == "-I": # Keep arg with -I option
            inargs.append(item)
            
        if item[0:2] == "-c":   # Keep arg with -c option 
            inargs.append(item)            
            
        if item == "-c": # Keep next arg if full match -c
            save_next = True  
            
        if item == "-I": # Keep next arg if full match -I
            save_next = True              
            
    try:
        opts, args = getopt.getopt(inargs, 'I:c:')
        for o, a in opts:
            if o == "-I":
                include_dir.add(a)
            elif o in ("-c"):
                source_files.add(a)
    except:
        a=100           

# Print header file, add .h file under include_dir
for item in include_dir:
    files = glob.glob(os.getcwd() + item + "/*.h")
    for file in files:
        print(file)  
 
# Print source file 
for item in source_files:
    print (os.getcwd() + "/" + eval(item))     
