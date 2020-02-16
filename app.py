from flask import Flask, render_template, url_for, request, redirect
from datetime import datetime
import traceback

app = Flask(__name__)

class Trashcan():
	def __init__(self, id):
		self.id = id
		self.trash = 0
		self.recycling = 0
		self.compost = 0

cans = {}

@app.route('/', methods = ['POST', 'GET'])
def index():
	
	if request.method == 'GET':
		return render_template('index.html', bins = cans)

	elif request.method == "POST": 
		try:
			dustbin_id = request.form['id']
			argument_recycling = request.form["recycling"]
			argument_compost = request.form["compost"]
			argument_trash = request.form["trash"]

			if id not in cans:
				cans[id] = Trashcan(id)
			
			cans[id].trash = argument_trash
			cans[id].recycling = argument_recycling
			cans[id].compost = argument_compost

		except Exception as e:
			traceback.print_exc()
			return str(e)


if __name__ == "__main__":
	app.run(debug = True)
