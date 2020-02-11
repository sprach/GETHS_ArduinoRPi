#-*-coding:utf-8-*-

# GET, POST 요청 테스트
from flask import Flask, render_template, request

app = Flask(__name__)


@app.route("/")
def index():
    return render_template("index.html")


# 받아 들일 요청 방식 설정.
# methods 를 생략하면 'get'만, 'post'는 지정을 해 주어야 한다.
@app.route("/second", methods=['get', 'post'])
def second():
    return request.method


app.run(host='0.0.0.0', debug=True, port=2000)
