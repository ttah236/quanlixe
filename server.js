/**
 * Node.js Server cho Hệ Thống Quản Lý Phương Tiện
 * Sử dụng thuần thư viện chuẩn của Node.js (http, fs, path) - KHÔNG CẦN CÀI ĐẶT THÊM PACKAGE NGOÀI!
 * Chạy lệnh: `node server.js` hoặc `npm start`
 */
const http = require('http');
const fs = require('fs');
const path = require('path');

const PORT = process.env.PORT || 3000;
const PUBLIC_DIR = __dirname;
const VEHICLES_FILE = path.join(__dirname, 'vehicles.txt');
const OUTPUT_FILE = path.join(__dirname, 'output.txt');

// Load OOP Models
const Vehicle = require('./js/models/Vehicle');
const Car = require('./js/models/Car');
const Truck = require('./js/models/Truck');
const VehicleManager = require('./js/controllers/VehicleManager');

const MIME_TYPES = {
  '.html': 'text/html; charset=UTF-8',
  '.css': 'text/css; charset=UTF-8',
  '.js': 'application/javascript; charset=UTF-8',
  '.json': 'application/json; charset=UTF-8',
  '.txt': 'text/plain; charset=UTF-8',
  '.svg': 'image/svg+xml',
  '.ico': 'image/x-icon'
};

// Helper đọc body request JSON
function getRequestBody(req) {
  return new Promise((resolve, reject) => {
    let body = '';
    req.on('data', chunk => body += chunk);
    req.on('end', () => {
      try {
        resolve(body ? JSON.parse(body) : {});
      } catch (e) {
        resolve(body);
      }
    });
    req.on('error', reject);
  });
}

const server = http.createServer(async (req, res) => {
  const parsedUrl = new URL(req.url, `http://${req.headers.host}`);
  const pathname = parsedUrl.pathname;

  // CORS headers
  res.setHeader('Access-Control-Allow-Origin', '*');
  res.setHeader('Access-Control-Allow-Methods', 'GET, POST, OPTIONS');
  res.setHeader('Access-Control-Allow-Headers', 'Content-Type');

  if (req.method === 'OPTIONS') {
    res.writeHead(204);
    res.end();
    return;
  }

  // -------------------------------------------------------------
  // REST API ENDPOINTS
  // -------------------------------------------------------------
  if (pathname === '/api/vehicles' && req.method === 'GET') {
    try {
      const manager = new VehicleManager();
      if (fs.existsSync(VEHICLES_FILE)) {
        const text = fs.readFileSync(VEHICLES_FILE, 'utf8');
        manager.loadFromTxt(text);
      }
      res.writeHead(200, { 'Content-Type': 'application/json; charset=UTF-8' });
      res.end(JSON.stringify({
        success: true,
        count: manager.count,
        totalTax: manager.calculateTotalTaxLiability(),
        vehicles: manager.vehicles.map(v => v.display())
      }));
    } catch (err) {
      res.writeHead(500, { 'Content-Type': 'application/json' });
      res.end(JSON.stringify({ success: false, error: err.message }));
    }
    return;
  }

  if (pathname === '/api/save' && req.method === 'POST') {
    try {
      const body = await getRequestBody(req);
      if (typeof body.data === 'string') {
        fs.writeFileSync(VEHICLES_FILE, body.data, 'utf8');
        res.writeHead(200, { 'Content-Type': 'application/json' });
        res.end(JSON.stringify({ success: true, message: 'Đã lưu dữ liệu vào vehicles.txt' }));
      } else {
        res.writeHead(400, { 'Content-Type': 'application/json' });
        res.end(JSON.stringify({ success: false, message: 'Dữ liệu không hợp lệ!' }));
      }
    } catch (err) {
      res.writeHead(500, { 'Content-Type': 'application/json' });
      res.end(JSON.stringify({ success: false, error: err.message }));
    }
    return;
  }

  if (pathname === '/api/export-report' && req.method === 'GET') {
    try {
      const manager = new VehicleManager();
      if (fs.existsSync(VEHICLES_FILE)) {
        const text = fs.readFileSync(VEHICLES_FILE, 'utf8');
        manager.loadFromTxt(text);
      }
      const report = manager.exportResultsToFileString();
      fs.writeFileSync(OUTPUT_FILE, report, 'utf8');

      res.writeHead(200, { 'Content-Type': 'application/json; charset=UTF-8' });
      res.end(JSON.stringify({
        success: true,
        message: 'Đã xuất báo cáo ra output.txt',
        report: report
      }));
    } catch (err) {
      res.writeHead(500, { 'Content-Type': 'application/json' });
      res.end(JSON.stringify({ success: false, error: err.message }));
    }
    return;
  }

  // -------------------------------------------------------------
  // PHỤC VỤ STATIC FILES (HTML, CSS, JS, TXT)
  // -------------------------------------------------------------
  let reqPath = pathname === '/' ? '/index.html' : pathname;
  let safePath = path.normalize(path.join(PUBLIC_DIR, reqPath));

  if (!safePath.startsWith(PUBLIC_DIR)) {
    res.writeHead(403);
    res.end('403 Forbidden');
    return;
  }

  fs.stat(safePath, (err, stats) => {
    if (err || !stats.isFile()) {
      res.writeHead(404, { 'Content-Type': 'text/plain; charset=UTF-8' });
      res.end('404 Not Found');
      return;
    }

    const ext = path.extname(safePath).toLowerCase();
    const contentType = MIME_TYPES[ext] || 'application/octet-stream';

    res.writeHead(200, { 'Content-Type': contentType });
    fs.createReadStream(safePath).pipe(res);
  });
});

server.listen(PORT, () => {
  console.log(`\n=============================================================`);
  console.log(`   🚗 HỆ THỐNG QUẢN LÝ PHƯƠNG TIỆN (VEHICLE MANAGEMENT) 🚗   `);
  console.log(`=============================================================`);
  console.log(` Server đang chạy tại: http://localhost:${PORT}`);
  console.log(` File dữ liệu gốc:      ${VEHICLES_FILE}`);
  console.log(` File báo cáo kết quả:  ${OUTPUT_FILE}`);
  console.log(` Nhấn Ctrl + C để dừng server.\n`);
});
