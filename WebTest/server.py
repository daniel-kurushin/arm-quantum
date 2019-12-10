from flask import Flask,request,make_response
#import ProgaVadima

app = Flask(__name__)
com = '/dev/ttyUSB0'
command = ''
type_command = ''

lib = ['подать', 'возьми', 'брось', 'положи']

@app.route('/connect', methods=['POST','GET'])
def get_com():
	if request.method == 'POST':
		global com
		com = request.form['com']
	if request.method == 'GET':
		print(com)
		return com
	return ("")

@app.route('/command', methods=['POST','GET'])
def get_command():
	if request.method == 'POST':
		global command
		command = request.form['command']
		print (command)
		return("")
	elif request.method == 'GET':
		return command

app.run(debug=True)