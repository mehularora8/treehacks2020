from flask import Flask, render_template, url_for, request, redirect
from datetime import datetime
import traceback

app = Flask(__name__)

class Trashcan():
	def __init__(self, idn):
		self.id = idn
		self.trash = 0
		self.recycling = 0
		self.compost = 0

cans = {}

@app.route('/', methods = ['POST', 'GET'])
def index():
	
	if request.method == 'GET':
		return render_template('index.html', bins=cans)

	elif request.method == "POST": 
		try:
			idn = request.form['id']
			argument_recycling = request.form["recycling"]
			argument_compost = request.form["compost"]
			argument_trash = request.form["trash"]

			if idn not in cans:
				cans[idn] = Trashcan(idn)
			
			cans[idn].trash = argument_trash
			cans[idn].recycling = argument_recycling
			cans[idn].compost = argument_compost
			return "200"

		except Exception as e:
			traceback.print_exc()
			return str(e)


if __name__ == "__main__":
	app.run(debug = True)
