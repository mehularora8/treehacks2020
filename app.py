from flask import Flask, render_template, url_for, request, redirect
from flask_sqlalchemy import SQLAlchemy
from datetime import datetime

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///trashcan.db'
db = SQLAlchemy(app)


class trashcan(db.Model):
	dustbin_id = db.Column(db.Integer, primary_key = True, unique = True)
	trash = db.Column(db.Integer, nullable = True)
	compost = db.Column(db.Integer, nullable = True)
	recycling = db.Column(db.Integer, nullable = True)
	def __repr__(self):
		return str(self.__dict__)


@app.route('/', methods = ['POST', 'GET'])
def index():
	
	if request.method == 'POST':
		dustbin_id = request.args.get('id')

		if target_dustbin is None:
			return render_template('index.html', bins = bins)
		
		argument_recycling = request.args.get('recycling')
		argument_compost = request.args.get('compost')
		argument_trash = request.args.get('trash')

		target_dustbin = trashcan.query.get(dustbin_id)

		

		target_dustbin.trash = argument_trash
		target_dustbin.compost = argument_compost
		target_dustbin.recycling = argument_recycling
		
		try:
			db.session.commit()
			bins = trashcan.query.all()
			return render_template('index.html', bins = bins)

		except:
			return "Internal Failure"

		
	else: 
		bins = trashcan.query.all()
		return render_template('index.html', bins = bins)


if __name__ == "__main__":
	app.run(debug = True)
