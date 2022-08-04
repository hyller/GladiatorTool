#!/usr/bin/env python3
# coding: utf8

import serial
import sys
import time
import json
import matplotlib.pyplot as plt
import usb.core
import csv

'''
This util start a sniffer, then calculate the received packets
'''


def Stop(ser, dev):
    for i in range(100):
        ser.write(b'collect 10000 0 1 1\n')
        time.sleep(0.001)
    for i in range(1000):
        try:
            dev.read(0x81, 512, 1)
        except:
            ser.write(b'stop')
        ser.write(b'stop')


def Capture(port, seconds=5):
    ser = serial.Serial(port, 921600, timeout=0.1)  # Timeout 0.1s
    dev = usb.core.find(idVendor=0x1cbe, idProduct=0x00ab)
    dev.set_configuration()

    # Config sensor and device
    ser.write(b'wreg 0x00 0x0020\n')
    time.sleep(0.1)
    ser.write(b'wreg 0x01 0x01c0\n')
    time.sleep(0.1)

    # Read bulk data
    recvs = b''
    ser.write(b'collect 100 224 0 1\n')
    start = time.time()
    print(f'start time {start}')
    while True:
        recvs += dev.read(0x81, 512*128, 100)
        stop = time.time()
        delta = stop - start
        if(delta > seconds):
            print(f'stop time {stop}')
            print(f'delta time {delta}')
            break

    Stop(ser, dev)

    cnt = divmod(len(recvs), 4)
    print(f"receive total cnt {cnt}")

    return recvs


def Parse(recvs):
    # Parse received bytes
    # 0    :1      :2-3
    # Frame:Address:Data
    x_value = []
    y_value = []
    z_value = []
    for index in range(len(recvs)):
        if recvs[index] == 0:
            index += 1
            address = recvs[index]
            data = recvs[index+1]*256+recvs[index+2]

            # Convert to mT
            if(data >= 0x7FFF):
                data = data - 0x10000
            if(data > 32767):
                data = -data/-32768
            else:
                data = data/32767
            data = data * 150

            # Fill to xyz
            if address == 9:
                x_value.append(data)
                index += 3
            elif address == 10:
                y_value.append(data)
                index += 3
            elif address == 11:
                z_value.append(data)
                index += 3

    print(f"receive x cnt {len(x_value)}")
    print(f"receive y cnt {len(y_value)}")
    print(f"receive z cnt {len(z_value)}")

    return x_value, y_value, z_value


def Draw(values):
    plt.plot(values)
    plt.axis([0, len(values), min(0, min(values)), max(0, max(values))])
    plt.xlabel("Count")
    plt.ylabel("mT")
    plt.show()


def StoreValues(x, y, z, filename):
    with open(filename, 'w+') as wf:
        wf.write(f'count x_axis y_axis z_axis\n')
        for index in range(min(len(x), len(y), len(z))):
            wf.write(f'{index} {x[index]} {y[index]} {z[index]}\n')

        wf.close()


def LoadValueFromFile(filename):
    value = []
    with open(filename) as csvfile:
        spamreader = csv.reader(csvfile)
        index = 0
        for row in spamreader:
            if index == 0:
                index = 1
            else:
                value.append(float(row[1]))

        csvfile.close()

    return value


if __name__ == '__main__':
    if len(sys.argv) == 4:
        recvs = Capture(sys.argv[1], int(sys.argv[2]))
        x_values, y_values, z_values = Parse(recvs)
        StoreValues(x_values, y_values, z_values, sys.argv[3])
    elif len(sys.argv) == 5:
        x_values = LoadValueFromFile(sys.argv[1])
        y_values = LoadValueFromFile(sys.argv[2])
        z_values = LoadValueFromFile(sys.argv[3])
        StoreValues(x_values, y_values, z_values, sys.argv[4])
        # Draw(x_values)
    else:
        print('Usage: wd_acc port_name time file_name')
