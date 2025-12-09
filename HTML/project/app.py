from flask import Flask, request, jsonify, send_from_directory
from flask_cors import CORS
import pandas as pd, threading, socket, os
from flask import send_from_directory, abort


app = Flask(__name__)
CORS(app)

# ① 动态生成的 port.txt
@app.route('/port.txt')
def serve_port():
    return send_from_directory('.', 'port.txt')

# ② 屏蔽 favicon 404（可选，防止控制台刷屏）
@app.route('/favicon.ico')
def favicon():
    abort(204)          # No Content

# ① 托管静态文件（index.html, css, js）
@app.route('/')
def index():
    return send_from_directory('.', 'index.html')

@app.route('/<path:filename>')
def static_files(filename):
    return send_from_directory('.', filename)

# ② 原来的上传接口
@app.route('/upload', methods=['POST'])
def upload_csv():
    file = request.files['file']
    df = pd.read_csv(file.stream)
    return jsonify({
        'rows': len(df),
        'columns': list(df.columns),
        'preview': df.head(3).to_dict(orient='records')
    })

def find_free_port():
    with socket.socket() as s:
        s.bind(('', 0))
        return s.getsockname()[1]

def start_server():
    port = find_free_port()
    with open('port.txt', 'w') as f:
        f.write(str(port))
    print('Flask running on port', port)
    app.run(port=port, debug=False, use_reloader=False)

if __name__ == '__main__':
    threading.Thread(target=start_server, daemon=True).start()
    while True:
        threading.Event().wait(1)
