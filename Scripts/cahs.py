#!/usr/bin/env python3
# coding: utf8

import serial
import sys
import time
import crcmod


''' 
This util simulate changan host

Send commands: (Baud reate 38400)

Recevie packet frame format
    | Bytes | Len   | cmd  | tx pks | rx pks  | crc    |
    | ----- | ----- | ---- | ------ | ------- | ------ |
    | Value | 0B    | 01   | 4Bytes | 4Bytes  | 2Bytes |
    
Send packet frame format
    | Bytes | Len   | cmd  | rx pks  | crc    |
    | ----- | ----- | ---- | ------- | ------ |
    | Value | 07    | 01   | 4Bytes  | 2Bytes |    
'''


def SimulateChangAnHost(port):
    ser = serial.Serial(port, 38400)
    modbus_crc = crcmod.predefined.mkCrcFun("crc-ccitt-false")

    host_recv_packets = 0
    while True:
        ser.reset_input_buffer()
        recvs = ser.read(12)
        efr32_send_packets = recvs[2] + recvs[3] * 256 + recvs[4] * 256 * 256 + recvs[5] * 256 * 256 * 256
        efr32_recv_packets = recvs[6] + recvs[7] * 256 + recvs[8] * 256 * 256 + recvs[9] * 256 * 256 * 256
        if host_recv_packets > efr32_send_packets:
            host_recv_packets = 1
        else:
            host_recv_packets += 1
        print(f"efr32_send={efr32_send_packets}, host_recv={host_recv_packets}, efr32_recv={efr32_recv_packets}")
        send_bytes = bytes()
        send_bytes += b'\x07'
        send_bytes += b'\x02'
        send_bytes += host_recv_packets.to_bytes(4, 'little')
        send_bytes += modbus_crc(send_bytes).to_bytes(2, 'little')
        # print(send_bytes)
        ser.write(send_bytes)
        time.sleep(0.1)


if __name__ == '__main__':
    if len(sys.argv) >= 2:
        SimulateChangAnHost(sys.argv[1])
    else:
        print('Usage: cahs port_name')
        exit()
