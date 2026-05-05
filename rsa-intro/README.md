<div align="center">
  <br>
  <img src="https://img.shields.io/badge/RSA-Cryptography-6c5ce7?style=for-the-badge" alt="RSA">
  <img src="https://img.shields.io/badge/Status-Completed-00cec9?style=for-the-badge" alt="Status">
  <br><br>
  <h1 align="center">🔐 RSA 算法交互式科普网站</h1>
  <p align="center">
    一个精美、交互式的单页网站，深入浅出地介绍 RSA 非对称加密算法的原理与流程
  </p>
  <br>
</div>

---

## ✨ 特性

- **粒子动画背景** — 动态 Canvas 粒子系统，鼠标移动可牵引粒子
- **响应式设计** — 适配桌面与移动设备
- **四步流程卡片** — 密钥生成 → 加密 → 解密 → 数字签名
- **数学原理板块** — 大整数分解、欧拉定理、模逆元、模幂运算
- **通信模型图** — Alice ↔ Bob ↔ Eve 的加密通信示意
- **交互式 Demo** — 可切换素数位数，实时进行 RSA 加解密计算
- **安全性分析** — 密钥长度、填充方案、量子威胁等

## 🚀 快速开始

直接打开 `index.html` 即可在浏览器中运行，无需任何构建工具或依赖。

```bash
# 使用浏览器打开
open index.html        # macOS
xdg-open index.html    # Linux
start index.html       # Windows
```

## 📖 内容概览

| 章节 | 内容 |
|------|------|
| **Hero** | RSA 简介与核心概念 |
| **工作流程** | 密钥生成、加密、解密、签名四步骤详解 |
| **数学原理** | 背后的数论基础与公式 |
| **通信模型** | 公钥/私钥在通信中的角色示意 |
| **交互演示** | 可调节密钥强度的 RSA 加解密模拟器 |
| **安全性分析** | RSA 的安全假设与未来挑战 |

## 🧪 交互 Demo 说明

Demo 使用教学用小素数（非安全）来演示 RSA 加解密过程：

1. 通过滑块选择素数位数（2~5 位）
2. 程序自动生成对应的 p、q、n、e、d
3. 输入明文数字，点击按钮即可查看加密与解密结果
4. 展示从明文 → 密文 → 解密的完整链路

> ⚠️ 此 Demo 仅用于教学演示，实际 RSA 应使用 ≥2048 位的密钥并配合 OAEP 填充。

## 🛠 技术栈

- **纯原生 HTML/CSS/JavaScript** — 零依赖
- **Canvas API** — 粒子动画与鼠标交互
- **Intersection Observer** — 滚动渐入动画
- **CSS 变量 + Flexbox/Grid** — 现代布局与主题

## 📄 许可

本项目仅供教育用途。
