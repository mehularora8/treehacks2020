from flask import Flask, render_template, url_for, request, redirect
from flask_sqlalchemy import SQLAlchemy
from datetime import datetime

app = Flask(__name__)
app.config['SQLALCHEMY_DATABASE_URI'] = 'sqlite:///trashcan.db'
db = SQLAlchemy(app)


class trashcan(db.Model):
	dustbin_id = db.Column(db.String(10), primary_key = True, unique = True)
	trash = db.Column(db.Integer, nullable = True)
	compost = db.Column(db.Integer, nullable = True)
	recycling = db.Column(db.Integer, nullable = True)
	def __repr__(self):
		return str(self.__dict__)


@app.route('/', methods = ['POST', 'GET'])
def index():
	
	if request.method == 'POST':
		dustbin_id = request.get.args('id')
		target_dustbin = trashcan.query.get(id)
		target_dustbin.trash = request.get.args('trash')
		target_dustbin.compost = request.get.args('compost')
		target_dustbin.recycling = request.get.args('recycling')

		try:
			db.session.commit()
			return redirect('/')
		except:
			return "Internal Failure"
		
	else: 
		bins = trashcan.query.all()
		return render_template('index.html', bins = bins)


if __name__ == "__main__":
	app.run(debug = True)
