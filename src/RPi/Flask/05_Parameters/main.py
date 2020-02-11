#-*-coding:utf-8-*-

# Parameters
from flask import Flask, render_template, request

app = Flask(__name__)


@app.route("/")
def index():
    return render_template("index.html")


# Get 방식 요청시 파라메터 추출
@app.route("/result1")
def result1():
    a1 = request.args.get("a1")
    a2 = request.args.get("a2")
    a3 = request.args.get("a3")
    # 존재하지 않는 파라메터
    a4 = request.args.get("a4")     # 'None'으로 처리됨
    # 존재하지 않는 파라메터인 경우 기본값 셋팅
    a5 = request.args.get("a5", 1000)
    # 파라메터는 모두 문자열!
    # 타입을 지정하면 형변환해서 반환한다.
    a6 = request.args.get("a6", 0, int)     # 첫번째 파라메터명, 두번째 기본값, 세번째 타입형

    # 파라메터 값의 타입 표시
    print(f'a1 : {type(a1)}')
    print(f'a6 : {type(a6)}')

    return render_template("result1.html", a1=a1, a2=a2, a3=a3, a4=a4, a5=a5, a6=a6)


# POST 방식
@app.route("/result2", methods=['post'])
def result2():
    a1 = request.form['a1']
    a2 = request.form['a2']
    # a3 = request.form['a3']
    # return render_template("result1.html", a1=a1, a2=a2, a3=a3)
    return render_template("result1.html", a1=a1, a2=a2)


# GET/POST 방식
@app.route("/result3", methods=['get', 'post'])
def result3():
    a1 = request.values.get('a1')
    a2 = request.values.get('a2')
    a3 = request.values.get('a3', 300)
    a4 = request.values.get('a4', 0, int)

    print(f'a4 : {type(a4)}')

    return render_template("result1.html", a1=a1, a2=a2, a4=a4)


app.run(host='0.0.0.0', port=1500, debug=True)