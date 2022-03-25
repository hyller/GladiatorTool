import csv
import os
import sys


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

                wf.write("line:%4d | %02d:%02d:%02d.%03d" % (int(row['Index']), timeStamp_hour, timeStamp_min, timeStamp_sec, timeStamp_ms) + '|')
                if(row['Event ID'] == '0x50'):
                    rawParameter = int(row['Parameter 3'].split('x')[1], 16)
                    networkState = rawParameter/256
                    leaveReason = rawParameter % 256
                    wf.write('SDK:'+'state-'+row['Parameter 1'] + '|' + 'Gateway_IEEE-' + row['Parameter 2'] + '|' + "networkState-%d" % networkState + '|' + "leaveReason-%x" % leaveReason + '\n')
                elif(row['Event ID'] == '0x51'):
                    wf.write('SDK:'+'LastLeaveReason-' + row['Parameter 1'] + 'leave_API_called_type-' + row['Parameter 2']+'\n')
                elif(row['Event ID'] == '0x52'):
                    wf.write('SDK:'+'EMBER_COUNTER_ALLOCATE_PACKET_BUFFER_FAILURE-' + row['Parameter 2']+'\n')
                elif(row['Event ID'] == '0x53'):
                    wf.write('SDK:'+'EMBER_COUNTER_TYPE_NWK_RETRY_OVERFLOW-' + row['Parameter 2']+'\n')
                elif(row['Event ID'] == '0x54'):
                    wf.write('SDK:'+'EMBER_COUNTER_PHY_CCA_FAIL_COUNT-' + row['Parameter 2']+'\n')
                elif(row['Event ID'] == '0x60'):
                    pinglost = int(row['Parameter 2'].split('x')[1], 16)
                    if(row['Parameter 1'] == '0x0'):
                        wf.write('APP:'+'ZIGBEE_COMMU_STATE_INIT')
                    if(row['Parameter 1'] == '0x1'):
                        wf.write('APP:'+'ZIGBEE_COMMU_STATE_STEERING')
                    if(row['Parameter 1'] == '0x2'):
                        wf.write('APP:'+'ZIGBEE_COMMU_STATE_NORMAL')
                    if(row['Parameter 1'] == '0x3'):
                        wf.write('APP:'+'ZIGBEE_COMMU_STATE_FAIL')
                    if(row['Parameter 1'] == '0x4'):
                        wf.write('APP:'+'ZIGBEE_COMMU_STATE_LOSS')
                    wf.write('|'+'pinglost-' + str(pinglost) + '|' + 'channel-' + row['Parameter 3'] + '\n')
                elif(row['Event ID'] == '0x61'):  # disable print LED state
                    if(row['Parameter 1'] == '0x0'):
                        wf.write('LED:'+'PRODUCT_STATE_ERROR')
                    if(row['Parameter 1'] == '0x1'):
                        wf.write('LED:'+'PRODUCT_STATE_OK')
                    if(row['Parameter 1'] == '0x2'):
                        wf.write('LED:'+'PRODUCT_STATE_INIT')
                    if(row['Parameter 1'] == '0x3'):
                        wf.write('LED:'+'PRODUCT_STATE_ZIGB_STEERING')
                    if(row['Parameter 1'] == '0x4'):
                        wf.write('LED:'+'PRODUCT_STATE_ZIGB_COMMU_NORMAL')
                    if(row['Parameter 1'] == '0x5'):
                        wf.write('LED:'+'PRODUCT_STATE_ZIGB_COMMU_FAIL')
                    if(row['Parameter 1'] == '0x6'):
                        wf.write('LED:'+'PRODUCT_STATE_ZIGB_COMMU_LOSS')
                    if(row['Parameter 1'] == '0x7'):
                        wf.write('LED:'+'PRODUCT_STATE_ZIGB_IDENTIFY')
                    if(row['Parameter 1'] == '0x8'):
                        wf.write('LED:'+'PRODUCT_STATE_POWER_LOSS')
                    wf.write('\n')
                elif(row['Event ID'] == '0x70'):
                    reason = int(row['Parameter 2'], 16)
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
                    wf.write('PWR:'+'CRASH_INFO_PC_low-'+row['Parameter 2'] + '|' + 'CRASH_INFO_PC_high-' + row['Parameter 3'] + '\n')
                elif(row['Event ID'] == '0x72'):
                    wf.write('PWR:'+'RETURN[0]_low-'+row['Parameter 2'] + '|' + 'RETURN[0]_high-' + row['Parameter 3'] + '\n')
                elif(row['Event ID'] == '0x73'):
                    wf.write('PWR:'+'RETURN[1]_low-'+row['Parameter 2'] + '|' + 'RETURN[1]_high-' + row['Parameter 3'] + '\n')
                elif(row['Event ID'] == '0x74'):
                    wf.write('PWR:'+'RETURN[2]_low-'+row['Parameter 2'] + '|' + 'RETURN[2]_high-' + row['Parameter 3'] + '\n')
                elif(row['Event ID'] == '0x75'):
                    wf.write('PWR:'+'RETURN[3]_low-'+row['Parameter 2'] + '|' + 'RETURN[3]_high-' + row['Parameter 3'] + '\n')
                elif(row['Event ID'] == '0x76'):
                    wf.write('PWR:'+'RETURN[4]_low-'+row['Parameter 2'] + '|' + 'RETURN[4]_high-' + row['Parameter 3'] + '\n')
                elif(row['Event ID'] == '0x77'):
                    wf.write('PWR:'+'RETURN[5]_low-'+row['Parameter 2'] + '|' + 'RETURN[5]_high-' + row['Parameter 3'] + '\n')
                elif(row['Event ID'] == '0x0'):  # internal counter log
                    wf.write('E_LOG_APS_SEND'+'|' + 'status-'+row['Parameter 1'] + '|' + 'apsFrame->sequence-' + row['Parameter 2'] + '|' + 'diff_tm-' + row['Parameter 3'] + '\n')
                elif(row['Event ID'] == '0x1'):
                    wf.write('E_LOG_APS_COUNTER'+'|' + 'emberCounters_EMBER_COUNTER_APS_DATA_TX_UNICAST_SUCCESS-' + row['Parameter 2'] + '|' + 'emberCounters_EMBER_COUNTER_APS_DATA_TX_UNICAST_FAILED-' + row['Parameter 3'] + '\n')
                elif(row['Event ID'] == '0x2'):
                    wf.write('E_LOG_MAC_COUNTER'+'|' + 'emberCounters_EMBER_COUNTER_MAC_TX_UNICAST_SUCCESS-' + row['Parameter 2'] + '|' + 'emberCounters_EMBER_COUNTER_MAC_TX_UNICAST_FAILED-' + row['Parameter 3'] + '\n')
                elif(row['Event ID'] == '0x3'):
                    wf.write('E_LOG_FAILURE_COUNTER'+'|' + 'emberCounters_EMBER_COUNTER_ALLOCATE_PACKET_BUFFER_FAILURE-' + row['Parameter 2'] + '|' + 'emberCounters_EMBER_COUNTER_PHY_CCA_FAIL_COUNT-' + row['Parameter 3'] + '\n')
                elif(row['Event ID'] == '0x4'):
                    wf.write('E_LOG_POLL_COUNTER'+'|' + 'last_poll_status-' + row['Parameter 1'] + '|' + 'poll_send_counter-' + row['Parameter 2'] + '|'+'poll_complete_counter-' + row['Parameter 3'] + '\n')
                elif(row['Event ID'] == '0x5'):
                    wf.write('E_LOG_LED_CHANGE_REASON'+'|' + 'E_LED_CHANGE_BY_GW/E_LED_CHANGE_BY_DIAG/E_LED_CHANGE_BY_COMM' + row['Parameter 1'] + '|' + ' last_state' + row['Parameter 2'] + '\n')
                elif(row['Event ID'] == '0x6'):
                    wf.write('E_LOG_LED_STATE'+'|' + 'led_currState_LED_COLOR_RED' + row['Parameter 2'] + '|' + ' led_currState_LED_COLOR_GREEN' + row['Parameter 3'] + '\n')
                elif(row['Event ID'] == '0x7'):
                    wf.write('E_LOG_PACKET_BUFFER'+'|' + 'BUFFER_TOTAL_COUNT-' + row['Parameter 2'] + '|' + ' BUFFER_FREE_COUNT-' + row['Parameter 3'] + '\n')
                elif(row['Event ID'] == '0x40'):  # TCB Info
                    wf.write('Total CPU Usage'+'|' + row['Parameter 3'] + '\n')
                elif(row['Event ID'] == '0x20'):
                    wf.write('DI/DO Task      '+'|'+'CPU Usage:' + row['Parameter 1']+'|' + 'CtxSwCtr: '+row['Parameter 2']+'|'+row['Parameter 3']+'\n')
                elif(row['Event ID'] == '0x21'):
                    wf.write('DATAMGR Task    '+'|'+'CPU Usage:' + row['Parameter 1']+'|' + 'CtxSwCtr: '+row['Parameter 2']+'|'+row['Parameter 3']+'\n')
                elif(row['Event ID'] == '0x22'):
                    wf.write('DIAG Task       '+'|'+'CPU Usage:' + row['Parameter 1']+'|' + 'CtxSwCtr: '+row['Parameter 2']+'|'+row['Parameter 3']+'\n')
                elif(row['Event ID'] == '0x23'):
                    wf.write('COMMU Task      '+'|'+'CPU Usage:' + row['Parameter 1']+'|' + 'CtxSwCtr: '+row['Parameter 2']+'|'+row['Parameter 3']+'\n')
                elif(row['Event ID'] == '0x24'):
                    wf.write('BUTTON Task     '+'|'+'CPU Usage:' + row['Parameter 1']+'|' + 'CtxSwCtr: '+row['Parameter 2']+'|'+row['Parameter 3']+'\n')
                elif(row['Event ID'] == '0x25'):
                    wf.write('LED Task        '+'|'+'CPU Usage:' + row['Parameter 1']+'|' + 'CtxSwCtr: '+row['Parameter 2']+'|'+row['Parameter 3']+'\n')
                elif(row['Event ID'] == '0x26'):
                    wf.write('ZigBee Task     '+'|'+'CPU Usage:' + row['Parameter 1']+'|' + 'CtxSwCtr: '+row['Parameter 2']+'|'+row['Parameter 3']+'\n')
                elif(row['Event ID'] == '0x27'):
                    wf.write('APP Task        '+'|'+'CPU Usage:' + row['Parameter 1']+'|' + 'CtxSwCtr: '+row['Parameter 2']+'|'+row['Parameter 3']+'\n')
                elif(row['Event ID'] == '0x30'):  # stk info
                    wf.write('DI/DO Task      '+'|'+'Task State:' + row['Parameter 1']+'|' + 'CPUUsageMax: '+row['Parameter 2']+'|'+'StkUsedPercentage'+row['Parameter 3']+'\n')
                elif(row['Event ID'] == '0x31'):
                    wf.write('DATAMGR Task    '+'|'+'Task State:' + row['Parameter 1']+'|' + 'CPUUsageMax: '+row['Parameter 2']+'|'+'StkUsedPercentage'+row['Parameter 3']+'\n')
                elif(row['Event ID'] == '0x32'):
                    wf.write('DIAG Task       '+'|'+'Task State:' + row['Parameter 1']+'|' + 'CPUUsageMax: '+row['Parameter 2']+'|'+'StkUsedPercentage'+row['Parameter 3']+'\n')
                elif(row['Event ID'] == '0x33'):
                    wf.write('COMMU Task      '+'|'+'Task State:' + row['Parameter 1']+'|' + 'CPUUsageMax: '+row['Parameter 2']+'|'+'StkUsedPercentage'+row['Parameter 3']+'\n')
                elif(row['Event ID'] == '0x34'):
                    wf.write('BUTTON Task     '+'|'+'Task State:' + row['Parameter 1']+'|' + 'CPUUsageMax: '+row['Parameter 2']+'|'+'StkUsedPercentage'+row['Parameter 3']+'\n')
                elif(row['Event ID'] == '0x35'):
                    wf.write('LED Task        '+'|'+'Task State:' + row['Parameter 1']+'|' + 'CPUUsageMax: '+row['Parameter 2']+'|'+'StkUsedPercentage'+row['Parameter 3']+'\n')
                elif(row['Event ID'] == '0x36'):
                    wf.write('ZigBee Task     '+'|'+'Task State:' + row['Parameter 1']+'|' + 'CPUUsageMax: '+row['Parameter 2']+'|'+'StkUsedPercentage'+row['Parameter 3']+'\n')
                elif(row['Event ID'] == '0x37'):
                    wf.write('APP Task        '+'|'+'Task State:' + row['Parameter 1']+'|' + 'CPUUsageMax: '+row['Parameter 2']+'|'+'StkUsedPercentage'+row['Parameter 3']+'\n')
                elif(row['Event ID'] == '0x80'):
                    wf.write('POWERDOWN       '+'|'+row['Parameter 1']+'|' + row['Parameter 2']+'|'+row['Parameter 3']+'\n')
                elif(row['Event ID'] == '0x81'):
                    wf.write('HB_LED          '+'|'+row['Parameter 1']+'|' + row['Parameter 2']+'|'+row['Parameter 3']+'\n')
                elif(row['Event ID'] == '0x82'):
                    wf.write('HB_ZIGBEE       '+'|'+row['Parameter 1']+'|' + row['Parameter 2']+'|'+row['Parameter 3']+'\n')
                elif(row['Event ID'] == '0x83'):
                    wf.write('HB_DI           '+'|'+row['Parameter 1']+'|' + row['Parameter 2']+'|'+row['Parameter 3']+'\n')
                elif(row['Event ID'] == '0x84'):
                    wf.write('HB_DO           '+'|'+row['Parameter 1']+'|' + row['Parameter 2']+'|'+row['Parameter 3']+'\n')
                elif(row['Event ID'] == '0x85'):
                    wf.write('HB_DIAG         '+'|'+row['Parameter 1']+'|' + row['Parameter 2']+'|'+row['Parameter 3']+'\n')
                elif(row['Event ID'] == '0x86'):
                    wf.write('HB_COMMU        '+'|'+row['Parameter 1']+'|' + row['Parameter 2']+'|'+row['Parameter 3']+'\n')
                elif(row['Event ID'] == '0x87'):
                    wf.write('HB_BTN          '+'|'+row['Parameter 1']+'|' + row['Parameter 2']+'|'+row['Parameter 3']+'\n')
                else:
                    wf.write('\n')
        rf.close()
    wf.close()


if __name__ == '__main__':
    if len(sys.argv) == 3:
        read_output_log(sys.argv[1], sys.argv[2])
    else:
        print('please give the target csv input file, and output file name')
        exit()
