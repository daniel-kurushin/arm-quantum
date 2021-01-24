from flask import Flask,request,make_response
import os
#import ProgaVadima

app = Flask(__name__)
com = '/dev/ttyUSB0'
command = ''
coord = '0 0 0'  

lib = ['подать', 'возьми', 'брось', 'положи']

@app.route('/connect', methods=['POST','GET'])
def get_com():
	if request.method == 'POST':
		global com
		com = request.form['com']
		print(com)
	if request.method == 'GET':
		print(com)
		return com
	return ("")

@app.route('/command', methods=['POST','GET'])
def get_command():
	if request.method == 'POST':
		global command
		command = request.form['command']
		return("")
	elif request.method == 'GET':
		return command

@app.route('/coord',methods=['POST','GET'])
def send_coord():
	if request.method == 'POST':
		global coord
		print(coord)
		coord = request.form["x"] + ' ' + request.form["y"] + ' ' + request.form["z"]
		return("")
	elif request.method == 'GET':
		return coord

@app.route('/visual', methods=['POST'])
def start_blender():
	if request.method == 'POST':
		print("got")
		os.startfile(r'C:/Program Files (x86)/Google/Chrome/Application/chrome.exe')
		return("")

app.run(debug=True)