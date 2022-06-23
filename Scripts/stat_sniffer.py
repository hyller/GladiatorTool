#!/usr/bin/env python3
# coding: utf8

import serial
import sys

''' 
This util start a sniffer, then calculate the received packets

Send commands: (Baud reate 115200)
    Start sniffer: 11~26
    Stop sniffer: 0xBB

Recevie packet frame format
    | Bytes | 2     | 1           | 6    | Len-2   | 1    | 1    |
    | ----- | ----- | ----------- | ---- | ------- | ---- | ---- |
    | Value | AD 13 | Payload Len | Time | Payload | RSSI | LQI  |
'''


def StatSniffer(port, channel=11, seconds=5):
    ser = serial.Serial(port, 115200, timeout=1)  # Timeout 1s
    ser.write(b'\xBB')  # Stop first
    ser.write(channel.to_bytes(1, 'little'))

    total_packet_cnt = 0
    for i in range(seconds):
        magic_low = False
        second_packet_cnt = 0
        recvs = ser.read(115200)  # The number can be big enough to let it timeout
        # print(f"recv_bytes={len(recvs)}")

        for recv in recvs:
            if recv == 0x13 and magic_low == True:  # Magic number match
                second_packet_cnt += 1  # Increase second_packet_cnt number

            if recv == 0xAD:  # Magic number low match
                magic_low = True
            else:
                magic_low = False

        print(f"second_packet_cnt={second_packet_cnt}")
        total_packet_cnt += second_packet_cnt

    ser.write(b'\xBB')  # Stop
    ser.close()
    return total_packet_cnt // seconds


def StatSnifferChannels(port, ch_list, seconds=5):
    ch_pcks_dict = {}
    for channel in ch_list:
        print(f"Scan channel: {channel}")
        avg_packet = StatSniffer(port, channel, seconds)
        print(f"avg_second_packet_cnt={avg_packet}\n")
        ch_pcks_dict[channel] = avg_packet

    print(f"channel\tpackets")
    for ch, pck in ch_pcks_dict.items():
        print(f"{ch}\t{pck}")


if __name__ == '__main__':
    if len(sys.argv) >= 4:
        channel = int(sys.argv[2])
        if channel >= 11 and channel <= 26:
            ch_list = [channel]
            avg_packet = StatSnifferChannels(sys.argv[1], ch_list, int(sys.argv[3]))
        elif channel == 0:  # Scann all channel
            ch_list = range(11, 26+1)
            StatSnifferChannels(sys.argv[1], ch_list, int(sys.argv[3]))
        elif channel == 1:  # Scan HA prefer channel
            ch_list = [11, 15, 20, 25, 26]
            StatSnifferChannels(sys.argv[1], ch_list, int(sys.argv[3]))
        else:
            print(f"\nWrong channel number!!!\n")
    else:
        print('Usage: stat_sniffer port_name channel time')
        exit()
