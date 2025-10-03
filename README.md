# 🕷️ Web Crawler & Spider (C++ & Python)

A collection of lightweight **web crawling tools** written in **C++** and **Python**.  
You can choose between the **C++ web crawler** (fast, compiled) or the **Python spider** (flexible, easy to extend).

---

## ✨ Features
- 🌐 Crawl and extract all internal & external links
- 🔗 Handle relative/absolute URLs
- 💉 Easy to extend for vulnerability testing (SQLi, XSS, etc.)
- 🎨 Colorized terminal output
- ⚡ Both **C++ (performance)** and **Python (flexibility)** versions

---


---

## 🛠️ Installation

### 🔹 C++ Version
Make sure you have:
- C++17 compiler (g++, clang++)
- [libcurl](https://curl.se/libcurl/)

Build:
```bash
cd cpp
g++ -std=c++17 crawl.cpp -o crawler -lcurl

./crawler https://example.com

// For Python Spider You run this command
python spider.py -u https://example.com 


