#include <iostream>
#include <string>
#include <set>
#include <queue>
#include <regex>
#include <curl/curl.h>

// ANSI color codes
#define COLOR_CYAN    "\033[36m"
#define COLOR_GREEN   "\033[32m"
#define COLOR_RESET   "\033[0m"

// Banner
void printBanner() {
    std::cout << COLOR_CYAN;
    std::cout << R"( █████   ███   ███████████████ ███████████       █████████  ███████████    █████████  █████   ███   ██████████      ██████████ 
▒▒███   ▒███  ▒▒███▒▒███▒▒▒▒▒█▒▒███▒▒▒▒▒███     ███▒▒▒▒▒███▒▒███▒▒▒▒▒███  ███▒▒▒▒▒███▒▒███   ▒███  ▒▒███▒▒███      ▒▒███▒▒▒▒▒█▒▒███▒▒▒▒▒███ 
 ▒███   ▒███   ▒███ ▒███  █ ▒  ▒███    ▒███    ███     ▒▒▒  ▒███    ▒███ ▒███    ▒███ ▒███   ▒███   ▒███ ▒███       ▒███  █ ▒  ▒███    ▒███ 
 ▒███   ▒███   ▒███ ▒██████    ▒██████████    ▒███          ▒██████████  ▒███████████ ▒███   ▒███   ▒███ ▒███       ▒██████    ▒██████████  
 ▒▒███  █████  ███  ▒███▒▒█    ▒███▒▒▒▒▒███   ▒███          ▒███▒▒▒▒▒███ ▒███▒▒▒▒▒███ ▒▒███  █████  ███  ▒███       ▒███▒▒█    ▒███▒▒▒▒▒███ 
  ▒▒▒█████▒█████▒   ▒███ ▒   █ ▒███    ▒███   ▒▒███     ███ ▒███    ▒███ ▒███    ▒███  ▒▒▒█████▒█████▒   ▒███      █▒███ ▒   █ ▒███    ▒███ 
    ▒▒███ ▒▒███     ██████████ ███████████     ▒▒█████████  █████   ██████████   █████   ▒▒███ ▒▒███     █████████████████████ █████   █████
     ▒▒▒   ▒▒▒     ▒▒▒▒▒▒▒▒▒▒ ▒▒▒▒▒▒▒▒▒▒▒       ▒▒▒▒▒▒▒▒▒  ▒▒▒▒▒   ▒▒▒▒▒▒▒▒▒▒   ▒▒▒▒▒     ▒▒▒   ▒▒▒     ▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒▒ ▒▒▒▒▒   ▒▒▒▒▒ 
)";
    std::cout << COLOR_RESET;
}

// CURL write callback
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    size_t totalSize = size * nmemb;
    output->append((char*)contents, totalSize);
    return totalSize;
}

// Fetch page content
std::string fetchPage(const std::string& url) {
    CURL* curl = curl_easy_init();
    std::string response;
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 1L);
        CURLcode res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    return response;
}

// Extract URLs from HTML
std::set<std::string> extractUrls(const std::string& html, const std::string& baseUrl) {
    std::set<std::string> urls;
    std::regex urlRegex(R"((href|src)\s*=\s*["']([^"']+)["'])", std::regex::icase);
    auto words_begin = std::sregex_iterator(html.begin(), html.end(), urlRegex);
    auto words_end = std::sregex_iterator();
    for (auto it = words_begin; it != words_end; ++it) {
        std::string url = (*it)[2].str();
        // Only add http/https links
        if (url.find("http://") == 0 || url.find("https://") == 0) {
            urls.insert(url);
        }
        
    }
    return urls;
}

int main() {
    printBanner();

    std::string startUrl;
    std::cout << COLOR_GREEN << "Enter the URL to crawl: " << COLOR_RESET;
    std::getline(std::cin, startUrl);

    std::set<std::string> visited;
    std::queue<std::string> toVisit;
    toVisit.push(startUrl);

    while (!toVisit.empty()) {
        std::string url = toVisit.front();
        toVisit.pop();
        if (visited.count(url)) continue;
        visited.insert(url);

        std::cout << COLOR_GREEN << "Crawling: " << url << COLOR_RESET << std::endl;
        std::string html = fetchPage(url);
        std::set<std::string> urls = extractUrls(html, url);

        for (const auto& foundUrl : urls) {
            if (!visited.count(foundUrl)) {
                std::cout << "  Found: " << foundUrl << std::endl;
                toVisit.push(foundUrl);
            }
        }
    }

    std::cout << COLOR_CYAN << "\nCrawling complete. Total unique URLs found: " << visited.size() << COLOR_RESET << std::endl;
    return 0;
}