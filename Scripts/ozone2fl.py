# Paser Ozone output to file list
# 1. In Ozone, File/Export/Code Profile/Include Source Path
# 2. python ozone2fl.py file

import sys
import pandas as pd


def parse(in_file):
    frame = pd.read_csv(in_file)
    files = list(set(frame['File']))
    sr = pd.Series(files)
    sr.to_csv('source_insight_file_list.txt', header=False, index=False)


if __name__ == '__main__':
    parse(sys.argv[1])
