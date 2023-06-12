'''
This tool will generate source insight 4 project file list
from build output file (*.dep)，then we can import the
file list in the source insight 4 project.
'''
import os
import sys
import xml.etree.ElementTree as ET
from datetime import datetime

def parse(sourcefile, targetname):
    # 1: .dep file and targetname given by input
    # 2: parse the seleted dep file
    parsefile = open(sourcefile, 'r')
    si4filelist = []

    tree = ET.ElementTree(file=parsefile)
    for tag in tree.findall('configuration'):
        if targetname == tag.find('name').text:
            output_tag = tag.find('outputs')

            for elem in output_tag.findall('file'):
                if elem.text.startswith('$PROJ_DIR$'):
                    if elem.text.endswith('.c') or elem.text.endswith('.cpp') or elem.text.endswith('.s') or elem.text.endswith('.h') or elem.text.endswith('.hpp'):
                        si4filelist.append(os.path.abspath(elem.text.replace('$PROJ_DIR$', os.getcwd()))+'\n')
            break

    # 3: save the lists
    outputfile = open(targetname + '.si4project_filelist.txt', 'w')
    outputfile.write('; Source Insight Project File List\n')
    outputfile.write('; Project Name: '+os.path.splitext(sourcefile)[0]+'\n')
    outputfile.write('; Generated by si4project_filelist.py at '+datetime.now().strftime('%Y/%m/%d %H:%M:%S')+'\n')
    outputfile.write('; Version=4.00.xxxx\n')
    outputfile.write(';\n')
    outputfile.write('; Each line should contain either a file name, a wildcard, or a sub-directory name.\n')
    outputfile.write('; File paths are relative to the project source root directory.\n')
    outputfile.write(';\n')
    outputfile.writelines(si4filelist)
    outputfile.close()


if __name__ == '__main__':
    if len(sys.argv) > 2:
        sourcefile = sys.argv[1]
        targetname = sys.argv[2]
        parse(sourcefile, targetname)
    else:
        print('Usage: iar2fl dep_name target_name')
