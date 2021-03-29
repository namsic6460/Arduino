import sys
import socket
from picamera import PiCamera
import time

HOST = "192.168.0.74"
PORT = 4321

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
print("Socket Created")

camera = PiCamera()

try:
    s.bind((HOST, PORT))
except socket.error:
    print("Bind Failed")
    sys.exit()
    
print("Bind Success")
    
s.listen(1)
(conn, addr) = s.accept()

pngNumber = 0;

while True:
    data = conn.recv(1024).decode('utf-8').strip()
    if data == "1":
        print('Started to capture')
        
        camera.start_preview()
        camera.capture('/home/pi/Pictures/' + str(pngNumber) + ".png")
        pngNumber += 1
        camera.stop_preview()
        
        print('Finished to capture')
    elif data == "0":
        print("Stopping")
        
        conn.close()
        s.close()
        break;