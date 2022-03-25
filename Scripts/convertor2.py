# 1. Extract crash address form reset information in internal log
# 2. According the crash address to find the crash function by search IAR map file
# 3. Output the crash address and function name to file
# NOTE: map file should in UTF-8 format
import csv
import os
import sys
import os.path

code_list = []
code_list_index = 0


def read_output_log(inputfile, outputfile):
    lastTimeStampRaw = 0
    with open(outputfile, 'w+') as wf:
        with open(inputfile, 'r') as rf:
            csv_reader = csv.DictReader(rf)
            for row in csv_reader:
                timeStampRaw = int(row['Timestamp'])
                if(timeStampRaw == 0):
                    timeStampRaw = lastTimeStampRaw
                lastTimeStampRaw = timeStampRaw

                timeStamp_hour = timeStampRaw//(1000*60*60)  # hours
                timeStamp_min = (timeStampRaw//(1000*60)) % 60  # min
                timeStamp_sec = (timeStampRaw//(1000)) % 60  # second
                timeStamp_ms = timeStampRaw % (1000)  # milli second

                if(row['Event ID'] == '0x70'):
                    reason = int(row['Parameter 2'], 16)
                    wf.write('\n\n')
                    wf.write('PWR:'+'resetReason-'+row['Parameter 2'])
                    if reason & 0x0001 == 1:
                        wf.write('-POWERON')
                    if reason & 0x0004 == 0x0004:
                        wf.write('-AVDDBOD')
                    if reason & 0x0008 == 0x0008:
                        wf.write('-DVDDBOD')
                    if reason & 0x0010 == 0x0010:
                        wf.write('-DECBOD')
                    if reason & 0x0100 == 0x0100:
                        wf.write('-EXTRST')
                    if reason & 0x0200 == 0x0200:
                        wf.write('-LOCKUPRST')
                    if reason & 0x0400 == 0x0400:
                        wf.write('-SYSREQRST')
                    if reason & 0x0800 == 0x0800:
                        wf.write('-WDOGRST')
                    if reason & 0x10000 == 0x10000:
                        wf.write('-EM4RST')
                    wf.write('|' + 'resetCnt-' + row['Parameter 3'] + '\n')
                elif(row['Event ID'] == '0x71'):
                    addr = int(row['Parameter 3'], 16)*65536 + int(row['Parameter 2'], 16)
                    funct_name = find_function(addr)
                    wf.write('PWR:'+'CRASH__PC-'+row['Parameter 3'] + "'" + row['Parameter 2'] + "--->" + funct_name + '\n')
                elif(row['Event ID'] == '0x72'):
                    addr = int(row['Parameter 3'], 16)*65536 + int(row['Parameter 2'], 16)
                    funct_name = find_function(addr)
                    wf.write('PWR:'+'RETURN[0]-'+row['Parameter 3'] + "'" + row['Parameter 2'] + "--->" + funct_name + '\n')
                elif(row['Event ID'] == '0x73'):
                    addr = int(row['Parameter 3'], 16)*65536 + int(row['Parameter 2'], 16)
                    funct_name = find_function(addr)
                    wf.write('PWR:'+'RETURN[1]-'+row['Parameter 3'] + "'" + row['Parameter 2'] + "--->" + funct_name + '\n')
                elif(row['Event ID'] == '0x74'):
                    addr = int(row['Parameter 3'], 16)*65536 + int(row['Parameter 2'], 16)
                    funct_name = find_function(addr)
                    wf.write('PWR:'+'RETURN[2]-'+row['Parameter 3'] + "'" + row['Parameter 2'] + "--->" + funct_name + '\n')
                elif(row['Event ID'] == '0x75'):
                    addr = int(row['Parameter 3'], 16)*65536 + int(row['Parameter 2'], 16)
                    funct_name = find_function(addr)
                    wf.write('PWR:'+'RETURN[3]-'+row['Parameter 3'] + "'" + row['Parameter 2'] + "--->" + funct_name + '\n')
                elif(row['Event ID'] == '0x76'):
                    addr = int(row['Parameter 3'], 16)*65536 + int(row['Parameter 2'], 16)
                    funct_name = find_function(addr)
                    wf.write('PWR:'+'RETURN[4]-'+row['Parameter 3'] + "'" + row['Parameter 2'] + "--->" + funct_name + '\n')
                elif(row['Event ID'] == '0x77'):
                    addr = int(row['Parameter 3'], 16)*65536 + int(row['Parameter 2'], 16)
                    funct_name = find_function(addr)
                    wf.write('PWR:'+'RETURN[5]-'+row['Parameter 3'] + "'" + row['Parameter 2'] + "--->" + funct_name + '\n')

        rf.close()
    wf.close()


def extract_code_from_map_file(inputfile):
    ret_funct_line_whole = ""
    code_list_index = 0
    with open(inputfile, 'r') as rf:
        lines = rf.readlines()

        entry_list_flag = False
        for line in lines:
            if "*** ENTRY LIST" in line:  # Start at line: *** ENTRY LIST
                entry_list_flag = True
                continue

            if "[1] = " in line and entry_list_flag == True:  # End at line: [1] =
                entry_list_flag = False
                break

            if entry_list_flag == True:
                if "Code " in line:  # Find the line include Code
                    if line[0] == " ":  # Function name is in previous line
                        funct_name = pre_line.strip()
                        ret_funct_line_whole = funct_name + "    " + line.strip()
                    else:  # All is in one line
                        funct_name = line.split()[0]
                        ret_funct_line_whole = line.strip()
                    code_list.append(ret_funct_line_whole)
            pre_line = line

        rf.close()


def find_function(addr):
    for line in code_list:  # sample line: zdoSimpleCommand           0x3'0a77    0x1a  Code  Gb  zdo-cli.o [66]
        funct_name = line.split()[0]
        funct_addr = int(line.split()[1].replace("'", ""), 16)  # Address maybe like this: 0x3'0d89
        try:
            funct_size = int(line.split()[2], 16)
        except:
            funct_size = 0

        if addr >= funct_addr and addr < (funct_addr + funct_size):
            return line

    return ""


if __name__ == '__main__':
    if len(sys.argv) == 4:
        extract_code_from_map_file(sys.argv[2])
        read_output_log(sys.argv[1], sys.argv[3])
    else:
        print('please give the target csv input file, map file, and output file name')
        exit()
