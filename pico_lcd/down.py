import os
import sys
import time
import serial


com_port  = "COM29"
file_name = "./build/src/pico_lcd"


def open_port(port, baudrate=1200, bytesize=serial.EIGHTBITS, parity=serial.PARITY_NONE, stopbits=serial.STOPBITS_ONE, timeout=None, xonxoff=False, rtscts=False, dsrdtr=False):
    ser = serial.Serial()

    ser.port = port
    ser.baudrate = baudrate
    ser.bytesize = bytesize
    ser.parity = parity
    ser.stopbits = stopbits
    ser.timeout = timeout
    ser.xonxoff = xonxoff
    ser.rtscts = rtscts
    ser.dsrdtr = dsrdtr

    try:      
      ser.open()      
      ser.close()    
    except(OSError, serial.SerialException):
      pass
    return ser


if __name__ == '__main__':

  open_port(com_port)
  print("reset pico")   
  time.sleep(0.5)
  os.system('rp2040load.exe' + " -v -D " + file_name)


  