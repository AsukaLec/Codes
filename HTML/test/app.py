from flask import Flask, request, jsonify
import pandas as pd
import io

app = Flask(__name__)

@app.route('/')                 # 返回下面这份 HTML
def index():
    return open('E:\code for vs code\HTML\index.html', encoding='utf-8').read()

@app.route('/preview', methods=['POST'])
def preview():
    file = request.files.get('file')
    if not file or file.filename == '':
        return jsonify(success=False, error='未选择文件')
    try:
        df = pd.read_csv(io.BytesIO(file.read()))
        return jsonify(success=True, preview=df.head(5).to_string())
    except Exception as e:
        return jsonify(success=False, error=str(e))

if __name__ == '__main__':
    app.run(debug=True)
