#-*-coding:utf-8-*-

from flask import Flask, render_template, request

app = Flask(__name__)


@app.route("/")
def index():
    return render_template("index.html")


@app.route("/test1")
def test1():
    return 'test1'


# 주소/test1/sub1
@app.route("/test1/sub1")
def test1_sub1():
    return 'test1 sub1'


# 주소/test1/sub2
@app.route("/test1/sub2")
def test1_sub2():
    return 'test1 sub2'


# 주소/test2
@app.route("/test2")
def test2():
    return 'test2'


# 주소/test2/값1
@app.route("/test2/<data1>")
def test2_data1(data1):
    return f'test2_data1 : {data1}'

# 주소/test2/값1/값2
@app.route("/test2/<data1>/<data2>")
def test2_data1_data2(data1, data2):
    return f'test2_data1 : {data1}, test2_data1_data2 : {data2}'

# 요청 주소의 형태가 다른 경우
@app.route("/test3")
@app.route("/test4")
def test3_4():
    return "test3 test4"

# 주소, 주소/값1, 주소/값1/값2
# - 함수의 인자를 넘길 때 파라메터의 갯수가 달라서 없는 변수를 만날 때 오류 발생한다.
#   그래서 함수에 기본값을 별도로 지정해 주어야 한다.
@app.route("/test5", defaults={'data1':1, 'data2':2})
@app.route("/test5/<data1>", defaults={'data2':2})
@app.route("/test5/<data1>/<data2>")
def test5(data1, data2):
    return f'test5 : {data1}, {data2}'


app.run(host="0.0.0.0", port=3000, debug=True)
