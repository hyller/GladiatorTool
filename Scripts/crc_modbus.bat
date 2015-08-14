@echo off
setlocal

rem calculate modbus crc, example:
rem crc_modbus 0207
rem 41 12
rem 41 is low byte, 12 is high byte
rem CRC Byte Sequence defined in Modbus is:
rem Addr Func Data_Count Data Data Data Data CRC_Lo(41) CRC_Hi(12)

reveng -m modbus -S -c %1

endlocal
@echo on