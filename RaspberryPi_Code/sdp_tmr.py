import serial
import sys
import time
import smbus
ser = serial.Serial(port='/dev/ttyS0', baudrate=9600, timeout=None)  # open ser
print(ser.name) # check which port was really used
while(1):
        bus = smbus.SMBus(1) # Read Temperature
        config = [0x00, 0x00]
        bus.write_i2c_block_data(0x18, 0x01, config)
        bus.write_byte_data(0x18, 0x08, 0x03)
        time.sleep(0.5)
        data = bus.read_i2c_block_data(0x18, 0x05, 2)
        ctemp = ((data[0] & 0x1F) * 256) + data[1]
        if ctemp > 4095 :
                ctemp -= 8192
        ctemp = ctemp * 0.0625
        stemp = format(ctemp, '.4f')
        stemp = stemp.zfill(8)
        temp = stemp.encode('utf-8') # Convert temp to string
        t = time.time() # get current epoch time
        currtime = format(t, '.2f')
        ctime = currtime.encode('utf-8')
        col = "," # write time and temp to serial port
        ser.write("z".encode('utf-8'))
        ser.write(currtime)
        ser.write(col.encode('utf-8'))
        ser.write(temp)
        ser.write("\n\r".encode('utf-8'))

ser.close()             # close port

