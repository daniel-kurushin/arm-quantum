from flask import Flask,request,make_response

app = Flask(__name__)
com = ''
command = ''

status = 0

@app.route('/connect', methods=['POST','GET'])
def get_com():
	if request.method == 'POST':
		global com
		com = request.form['com']
	if request.method == 'GET':
		print(com)
		return com
		com = ''
	return ("")

@app.route('/status', methods=['POST','GET'])
def set_status():
	if request.method == 'POST':
		global status
		status = request.form['status']
	if request.method == 'GET':
		return status
	return("")

@app.route('/command', methods=['POST','GET'])
def get_command():
	if request.method == 'POST':
		global command
		command = request.form('command')
	elif request.method == 'GET':
		if command != '':
			return command
			command = ''

app.run(debug=True)