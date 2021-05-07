#-*- coding:utf-8 -*-

import bluetooth
import RPi.GPIO as GPIO
import time
from flask import Flask, request, render_template

TRIG_PIN = 16
ECHO_PIN = 20
RED_PIN = 18
GREEN_PIN = 23
BLUE_PIN = 24
BUZZER_PIN = 25

client_socket = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
client_socket.connect(("FC:A8:9A:00:20:5C", 1))
print("Bluetooth connected")

app = Flask(__name__)

@app.route("/")
def helloWorld():
	return "Hello World"

def ledOn(pin):
	GPIO.output(pin, GPIO.HIGH)
	return "ok";

def ledOff(pin):
	GPIO.output(pin, GPIO.LOW)
	return "ok";
	
#@app.route("/led/<state>")
@app.route("/led")
def led():
	r = request.args.get("r")
	g = request.args.get("g")
	b = request.args.get("b")
	
	if r == None and g == None and b == None:
		return render_template("led.html")
	else:		
		if r != None:
			if r == "on":
				ledOn(RED_PIN)
			elif r == "off":
				ledOff(RED_PIN)
		
		if g != None:
			if g == "on":
				ledOn(GREEN_PIN)
			elif g == "off":
				ledOff(GREEN_PIN)
			
		if b != None:
			if b == "on":
				ledOn(BLUE_PIN)
			elif b == "off":
				ledOff(BLUE_PIN)
				
		return "ok"
	
@app.route("/html/name/<name>")
def nameHtml(name):
	return render_template("name.html", name=name)

@app.route("/html/form", methods=["GET"])
def formHtml():
	return render_template("form.html")
	
@app.route("/html/form", methods=["POST"])
def formTest():
	value = request.form["test"]
	print(value)
	return value
	
@app.route("/init")
def init():
	GPIO.setmode(GPIO.BCM)
	GPIO.setwarnings(False)
	
	GPIO.setup(TRIG_PIN, GPIO.OUT)
	GPIO.setup(ECHO_PIN, GPIO.IN)
	GPIO.output(TRIG_PIN, GPIO.LOW)
    
	GPIO.setup(RED_PIN, GPIO.OUT)
	GPIO.output(RED_PIN, GPIO.LOW)
	GPIO.setup(GREEN_PIN, GPIO.OUT)
	GPIO.output(GREEN_PIN, GPIO.LOW)
	GPIO.setup(BLUE_PIN, GPIO.OUT)
	GPIO.output(BLUE_PIN, GPIO.LOW)
	
	GPIO.setup(BUZZER_PIN, GPIO.OUT)
	GPIO.output(BUZZER_PIN, GPIO.LOW)
	
	return "Success"
	
@app.route("/clean-up")
def cleanUp():
	GPIO.output(RED_PIN, GPIO.LOW)
	GPIO.output(GREEN_PIN, GPIO.LOW)
	GPIO.output(BLUE_PIN, GPIO.LOW)
	GPIO.output(BUZZER_PIN, GPIO.LOW)
	GPIO.cleanup()
	return "Success"
	
@app.route("/distance")
def distance():
	distance = getDistance()
	
	if distance < 10:
		GPIO.output(BUZZER_PIN, GPIO.HIGH)
	else:
		GPIO.output(BUZZER_PIN, GPIO.LOW)
	
	return render_template("distance.html", distance=str(distance))
	
@app.route("/humi-temp")
def humiTemp():
	return render_template("humiTemp.html")
	
@app.route("/getHumiTemp")
def boundHumiTemp():
	[humi, temp] = getHumiTemp()
	return humi + "," + temp
	
def getDistance():
	GPIO.output(TRIG_PIN, GPIO.LOW)
	time.sleep(0.5)
	GPIO.output(TRIG_PIN, GPIO.HIGH)
	time.sleep(0.00001)
	GPIO.output(TRIG_PIN, GPIO.LOW)
    
	while GPIO.input(ECHO_PIN) == GPIO.LOW:
		pulseBegin = time.time()
	while GPIO.input(ECHO_PIN) == GPIO.HIGH:
		pulseEnd = time.time()
		
	duration = float(pulseEnd - pulseBegin)
	distance = (340 * (duration / 2)) * 100
	
	return distance
	
def getHumiTemp():
	client_socket.send("-")
	
	isHumi = True
	humi = ""
	
	string = ""
	
	while True:
		data = client_socket.recv(1).decode("utf-8").strip()
		
		if data == "-":
			if isHumi:
				isHumi = False
				humi = string
				string = ""
			else:
				return [humi, string]
		else:
			string += data
	
	
if __name__ == "__main__":
	try:
		app.run(host="0.0.0.0")
	except KeyboardInterrupt:
		client_socket.close()
