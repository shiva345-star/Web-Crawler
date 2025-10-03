import requests, time, subprocess
from bs4 import BeautifulSoup
from urllib.parse import urljoin, urlparse
from colorama import Fore, init

init(autoreset=True)

visited = set()
banner = """
                                   █████████     ███████████     █████    ██████████      ██████████    ███████████  
                                  ███▒▒▒▒▒███   ▒▒███▒▒▒▒▒███   ▒▒███    ▒▒███▒▒▒▒███    ▒▒███▒▒▒▒▒█   ▒▒███▒▒▒▒▒███ 
                                 ▒███    ▒▒▒     ▒███    ▒███    ▒███     ▒███   ▒▒███    ▒███  █ ▒     ▒███    ▒███ 
                                 ▒▒█████████     ▒██████████     ▒███     ▒███    ▒███    ▒██████       ▒██████████  
                                  ▒▒▒▒▒▒▒▒███    ▒███▒▒▒▒▒▒      ▒███     ▒███    ▒███    ▒███▒▒█       ▒███▒▒▒▒▒███ 
                                  ███    ▒███    ▒███            ▒███     ▒███    ███     ▒███ ▒   █    ▒███    ▒███ 
                                 ▒▒█████████     █████           █████    ██████████      ██████████    █████   █████
                                  ▒▒▒▒▒▒▒▒▒     ▒▒▒▒▒           ▒▒▒▒▒    ▒▒▒▒▒▒▒▒▒▒      ▒▒▒▒▒▒▒▒▒▒    ▒▒▒▒▒   ▒▒▒▒▒ 

                                                                                           created by Dark X Devil                                                                                                               
"""                                                              
print(f"{Fore.LIGHTMAGENTA_EX}{banner}")

def spider(url, domain, max_depth=3, depth=0):
    if depth > max_depth or url in visited:
        return

    try:
        print(Fore.CYAN + f"[+] Crawling: {url}")
        response = requests.get(url, timeout=5)
    except Exception as e:
        print(Fore.RED + f"[!] Failed to fetch {url} | {e}")
        return

    visited.add(url)
    soup = BeautifulSoup(response.text, "html.parser")

    for link in soup.find_all("a", href=True):
        new_url = urljoin(url, link["href"])
        if urlparse(new_url).netloc == domain:
            if new_url not in visited:
                print(Fore.GREEN + f"[+] Found Link: {new_url}")
                spider(new_url, domain, max_depth, depth + 1)


def run_command(command):
    try:
        result = subprocess.run(command, capture_output=True, text=True)
        return result.stdout
    except Exception as e:
        return f"[!] Error running {command}: {e}"

def main():

    target = input(Fore.CYAN + "Enter Target URL: ").strip()
    domain = urlparse(target).netloc

    print(Fore.MAGENTA + f"\n[+] Starting crawl on: {target}\n")
    spider(target, domain, max_depth=2)

    print(Fore.YELLOW + f"\n[+] Crawling done! {len(visited)} URLs found.\n")

   
if __name__ == "__main__":
    main()
