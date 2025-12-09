class CSVProcessor {
    constructor() {
        this.csvData = null;
        this.txtContent = '';
        this.initializeElements();
        this.bindEvents();
    }

    initializeElements() {
        this.dropZone         = document.getElementById('dropZone');
        this.fileInput        = document.getElementById('fileInput');
        this.processBtn       = document.getElementById('processBtn');
        this.viewTxtBtn       = document.getElementById('viewTxtBtn');
        this.downloadBtn      = document.getElementById('downloadBtn');
        this.predictBtn       = document.getElementById('predictBtn');        // ✅
        this.status           = document.getElementById('status');
        this.loading          = document.getElementById('loading');
        this.fileInfo         = document.getElementById('fileInfo');
        this.dataContainer    = document.getElementById('dataContainer');
        this.previewText      = document.getElementById('previewText');
        this.predictResult    = document.getElementById('predictResult');     // ✅
        this.tableContainer   = document.getElementById('tableContainer');
    }

    bindEvents() {
        this.dropZone.addEventListener('dragover',  e => this.handleDragOver(e));
        this.dropZone.addEventListener('dragleave', e => this.handleDragLeave(e));
        this.dropZone.addEventListener('drop',      e => this.handleDrop(e));
        this.dropZone.addEventListener('click',     () => this.fileInput.click());

        this.fileInput.addEventListener('change',  e => this.handleFileSelect(e));

        this.processBtn.addEventListener('click',  () => this.processData());
        this.viewTxtBtn.addEventListener('click',  () => this.viewTxtContent());
        this.downloadBtn.addEventListener('click', () => this.downloadTxtFile());

        this.predictBtn.addEventListener('click',  () => this.uploadCSVToPython()); // ✅

        document.addEventListener('dragover', e => e.preventDefault());
        document.addEventListener('drop',     e => e.preventDefault());
    }

    /* -------------- 原有功能 -------------- */
    handleDragOver(e) {
        e.preventDefault();
        this.dropZone.classList.add('drag-over');
    }
    handleDragLeave(e) {
        e.preventDefault();
        this.dropZone.classList.remove('drag-over');
    }
    handleDrop(e) {
        e.preventDefault();
        this.dropZone.classList.remove('drag-over');
        const files = e.dataTransfer.files;
        if (files.length) this.handleFile(files[0]);
    }
    handleFileSelect(e) {
        const file = e.target.files[0];
        if (file) this.handleFile(file);
    }
    handleFile(file) {
        if (!file.name.toLowerCase().endsWith('.csv')) {
            this.showStatus('请选择 CSV 文件！', 'error');
            return;
        }
        this.showLoading(true);
        this.showStatus('正在读取文件...', 'success');

        const reader = new FileReader();
        reader.onload = e => {
            try {
                this.csvData = e.target.result;
                this.displayFileInfo(file);
                this.showDataPreview();
                this.processBtn.disabled = false;
                this.predictBtn.disabled = false;               // ✅
                this.showStatus('文件读取成功！', 'success');
            } catch (err) {
                this.showStatus('文件读取失败: ' + err.message, 'error');
            } finally {
                this.showLoading(false);
            }
        };
        reader.onerror = () => {
            this.showStatus('文件读取错误！', 'error');
            this.showLoading(false);
        };
        reader.readAsText(file, 'UTF-8');
    }
    displayFileInfo(file) {
        document.getElementById('fileName').textContent     = `文件名: ${file.name}`;
        document.getElementById('fileSize').textContent     = `文件大小: ${this.formatFileSize(file.size)}`;
        const lines = this.csvData.split('\n').filter(l => l.trim());
        document.getElementById('rowCount').textContent     = `行数: ${lines.length}`;
        this.fileInfo.style.display = 'block';
    }
    formatFileSize(bytes) {
        if (!bytes) return '0 Bytes';
        const k = 1024, sizes = ['Bytes','KB','MB','GB'];
        const i = Math.floor(Math.log(bytes) / Math.log(k));
        return parseFloat((bytes / Math.pow(k, i)).toFixed(2)) + ' ' + sizes[i];
    }
    showDataPreview() {
        if (!this.csvData) return;
        const lines = this.csvData.split('\n').filter(l => l.trim()).slice(0, 5);
        let html = '<table class="data-table"><thead><tr>';
        if (lines.length) {
            const headers = this.parseCSVLine(lines[0]);
            headers.forEach(h => html += `<th>${this.escapeHtml(h)}</th>`);
            html += '</tr></thead><tbody>';
            for (let i = 1; i < lines.length; i++) {
                const cells = this.parseCSVLine(lines[i]);
                html += '<tr>';
                cells.forEach(c => html += `<td>${this.escapeHtml(c)}</td>`);
                html += '</tr>';
            }
        }
        html += '</tbody></table>';
        this.tableContainer.innerHTML = html;
        this.dataContainer.style.display = 'block';
    }
    parseCSVLine(line) {
        const res = [], sep = ',', q = '"';
        let cur = '', inQ = false;
        for (let i = 0; i < line.length; i++) {
            const c = line[i], next = line[i + 1];
            if (c === q) {
                if (inQ && next === q) { cur += q; i++; }
                else inQ = !inQ;
            } else if (c === sep && !inQ) {
                res.push(cur); cur = '';
            } else cur += c;
        }
        res.push(cur);
        return res;
    }
    escapeHtml(text) {
        const div = document.createElement('div');
        div.textContent = text;
        return div.innerHTML;
    }
    processData() {
        if (!this.csvData) {
            this.showStatus('请先选择 CSV 文件！', 'error');
            return;
        }
        this.showLoading(true);
        this.showStatus('正在处理数据...', 'success');
        setTimeout(() => {
            try {
                const lines = this.csvData.split('\n').filter(l => l.trim()).slice(0, 5);
                this.txtContent = lines.join('\n');
                localStorage.setItem('csv_data.txt', this.txtContent);
                this.viewTxtBtn.disabled = false;
                this.downloadBtn.disabled = false;
                this.showStatus('数据处理完成！TXT 已生成。', 'success');
                this.viewTxtContent();
            } catch (err) {
                this.showStatus('数据处理失败: ' + err.message, 'error');
            } finally {
                this.showLoading(false);
            }
        }, 1000);
    }
    viewTxtContent() {
        if (!this.txtContent) {
            this.showStatus('请先处理数据！', 'error');
            return;
        }
        this.previewText.textContent = this.txtContent;
        this.previewText.style.display = 'block';
        this.previewText.scrollIntoView({ behavior: 'smooth', block: 'nearest' });
    }
    downloadTxtFile() {
        if (!this.txtContent) {
            this.showStatus('请先处理数据！', 'error');
            return;
        }
        const blob = new Blob([this.txtContent], { type: 'text/plain;charset=utf-8' });
        const url = URL.createObjectURL(blob);
        const a = Object.assign(document.createElement('a'), {
            href: url,
            download: 'csv_data.txt'
        });
        document.body.appendChild(a);
        a.click();
        document.body.removeChild(a);
        URL.revokeObjectURL(url);
        this.showStatus('TXT 文件下载成功！', 'success');
    }
    showStatus(msg, type) {
        this.status.textContent = msg;
        this.status.className = `status ${type}`;
        this.status.style.display = 'block';
        if (type === 'success') {
            setTimeout(() => this.status.style.display = 'none', 3000);
        }
    }
    showLoading(show) {
        this.loading.style.display = show ? 'block' : 'none';
    }

    /* -------------- ✅ 新增：与 PyInstaller 打包的本地 Flask 通信 -------------- */
    async getBackendPort() {
        try {
            const res = await fetch('port.txt');   // PyInstaller 启动后写入
            return (await res.text()).trim();
        } catch {
            return 5000;                           // 默认 fallback
        }
    }
    async uploadCSVToPython() {
        const file = this.fileInput.files[0];
        if (!file) return this.showStatus('请先选择 CSV 文件！', 'error');

        const port = await this.getBackendPort();
        const formData = new FormData();
        formData.append('file', file);

        fetch(`http://localhost:${port}/upload`, {
            method: 'POST',
            body: formData
        })
        .then(res => res.json())
        .then(data => {
            if (data.error) {
                this.showStatus('Python 处理出错: ' + data.error, 'error');
            } else {
                // 把结果漂亮地展示出来
                const result = `行数: ${data.rows}
列名: ${data.columns.join(', ')}

前3行预览:
${JSON.stringify(data.preview, null, 2)}`;
                this.predictResult.textContent = result;
                this.predictResult.style.display = 'block';
                this.predictResult.scrollIntoView({ behavior: 'smooth', block: 'nearest' });
                this.showStatus('Python 返回成功！', 'success');
            }
        })
        .catch(err => {
            this.showStatus('无法连接本地服务，请确保桌面程序已运行！', 'error');
        });
    }
}
