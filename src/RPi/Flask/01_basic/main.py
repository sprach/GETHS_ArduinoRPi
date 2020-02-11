#-*-coding:utf-8-*-

from flask import Flask             #Flask 패키지 불러오기
app = Flask(__name__)               #Flask 모듈 불러오기

# Flask 객체를 생성한다.
app = Flask(__name__)


@app.route('/')
def index():
    return '안녕하세요'


@app.route('/hello')
def test1():
    return 'Hello World'


@app.route('/html')
def test2():
    return '''
            <html>
                <head>
                </head>
                <body>
                    <h1>Hello World</h1>
                </body>
            </html>
           '''


# 서버 가동. 기본 포트는 5000
# app.run()
# app.run(host='192.168.0.33')
# app.run(host='0.0.0.0')
# app.run(host='0.0.0.0', port=3000)
# debug=True 인 경우 코드가 수정되는 경우 재시동
app.run(host='0.0.0.0', port=3000, debug=True)
