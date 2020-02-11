#-*-coding:utf-8-*-

from flask import Flask
from flask import render_template

app = Flask(__name__)


@app.route("/")
def index():
    html_txt = render_template('index.html')
    return html_txt


@app.route("/jinja1")
def html_jinja1():
    html_txt = render_template('jinja1.html')
    return html_txt


@app.route("/jinja2")
def html_jinja2():
    # 전달한 데이터
    str1 = '문자열'
    int1 = 100
    double1 = 11.11
    boolean1 = True
    list1 = [10, 20, 30]
    dict1 = {'b1':100, 'b2':200}

    html_txt = render_template('jinja2.html', a1=str1, a2=int1, a3=double1, a4=boolean1, a5=list1, a6=dict1)
    return html_txt


@app.route("/jinja3")
def html_jinja3():
    html_txt = render_template('jinja3.html', a1=100, a2=[10, 20, 30])
    return html_txt


app.run(host='0.0.0.0', port=1500, debug=True)
