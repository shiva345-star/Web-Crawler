# C++ Web Crawler

A simple web crawler written in C++. This tool takes a starting URL and crawls the website, discovering and printing all unique URLs found.

## Features

- Crawls a website starting from a given URL.
- Discovers and displays all unique URLs found on the website.
- Uses the `curl` library for HTTP requests.

## Installation

To use this tool, you need a C++ compiler (like g++) and the `libcurl` development library installed on your system.

### On Debian/Ubuntu:
```bash
sudo apt-get update
sudo apt-get install g++ libcurl4-openssl-dev
```

### On Red Hat/CentOS:
```bash
sudo yum install gcc-c++ libcurl-devel
```

### On macOS (using Homebrew):
```bash
brew install gcc
brew install curl
```

### On Windows:

Installing g++ and libcurl on Windows can be complex. It is recommended to use a package manager like [MSYS2](https://www.msys2.org/) or use the Windows Subsystem for Linux (WSL).

## Compilation

To compile the `crawler.cpp` file, run the following command in your terminal:

```bash
g++ crawler.cpp -o crawler -lcurl
```

This will create an executable file named `crawler` (or `crawler.exe` on Windows).

## Usage

1. Run the compiled executable:
   ```bash
   ./crawler
   ```
2. Enter the URL you want to crawl when prompted.

## Disclaimer

This tool is for educational purposes only. Do not use it on websites without explicit permission from the owner. The author is not responsible for any misuse or damage caused by this tool.
