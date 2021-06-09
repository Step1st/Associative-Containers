#include <iostream>
#include <map>
#include <string>
#include <regex>
#include <algorithm>
#include <sstream>
#include <fstream>
#include <ostream>
#include <vector>

using std::vector;
using std::string;
using std::cout;
using std::cin;
using std::endl;
using std::less;
using std::make_pair;

typedef std::multimap<std::string, int> MapText;
typedef std::multimap<string, int> MapUrl;

void core(string& path);

void getText(MapText& textMap, MapUrl& urls, string& path);
void printWords(MapText& textMap, vector<string>& keys);
void XRefTable(MapText& textMap, vector<string>& keys);
void printURLs(MapUrl& urls);

void tolower(string& str);

int main(int argc, char* argv[]) {

    if (argc == 2) {
        string input;
        input = argv[1];
        std::replace( input.begin(), input.end(), '\\', '/');
        core(input);
        return 0;
    }
    else if(argc == 1){
        string input;
        cout << "Enter file location: ";
        std::getline(std::cin, input);
        std::replace( input.begin(), input.end(), '\\', '/');
        core(input);
        system("pause");
        return 0;
    }
    else{
        cout << "Error! too many arguments given!" << endl;
        return 1;
    }

}

void core(string& path)
{
    MapText textMap;
    MapUrl urls;
    vector<string> keys;

    cout << "Reading text..." << endl;
    getText(textMap, urls, path);
    cout << "Counting words..." << endl;
    printWords(textMap, keys);
    cout << "Generating cross reference table..." << endl;
    XRefTable(textMap, keys);
    cout << "Getting URLs..." << endl;
    printURLs(urls);
    cout << "Finished" << endl;
}

void getText(MapText& textMap, MapUrl& urls, string& path) {
    std::regex url("(((http|https)://)?www\\.)?[a-zA-Z0-9@:%._\\+~#?&/=]{2,256}\\.[a-z]{2,6}\\b([-a-zA-Z0-9@:%._\\+~#?&/=]*)");
    string templine, word;
    std::stringstream text;
    std::stringstream line;
    std::fstream input;
    int k = 1;

    input.open(path);

    if (input.fail())
    {
        cout << "Failed to open file" << endl;
        system("pause");
        exit(2);
    }

    text << input.rdbuf();
    input.close();

    while (text) {
        if (!text.eof()) {
            std::getline(text, templine);
            line << templine;
            while (!line.eof())
            {
                line >> word;
                if(regex_match(word, url)) {
                    urls.insert(make_pair(word,k));
                }
                else{
                    word.erase(std::remove_if (word.begin(), word.end(), ispunct), word.end());
                    tolower(word);
                    textMap.insert(make_pair(word,k));
                }
            }
            k++;
            line.clear();
        }

        else break;
    }
    text.clear();
}

void printWords(MapText& textMap, vector<string>& keys){
    std::ofstream output("WordCount.txt");
    std::stringstream endBuffer;
    endBuffer << "Word:               Count:" << endl;
    endBuffer << "--------------------------------------------" << endl;
    for (auto it = textMap.begin(); it != textMap.end(); ) {
        std::string key = it->first;

        int i = textMap.count(key);
        if (i > 1) {
            keys.push_back(key);
            endBuffer << key << string(20 - key.length(), ' ') << i << endl;
        }

        do {
            ++it;
        } while (it != textMap.end() && key == it->first);
    }
    keys.shrink_to_fit();
    output << endBuffer.str();
    output.close();
}

void XRefTable(MapText& textMap, vector<string>& keys){
    std::ofstream output("CrossRefTable.txt");
    std::stringstream endBuffer;
    endBuffer << "Word:               In lines:" << endl;
    endBuffer << "--------------------------------------------" << endl;
    for (auto & key : keys)
    {
        auto adr = textMap.equal_range(key);
        endBuffer << key << string(20 - key.length(), ' ');
        for (auto it=adr.first; it!=adr.second; ++it)
            endBuffer << it->second << ' ';
        endBuffer << endl;
    }
    output << endBuffer.str();
    output.close();
}

void printURLs(MapUrl& urls){
    std::ofstream output("URLs.txt");
    std::stringstream endBuffer;
    endBuffer << "URLs:" << endl;
    endBuffer << "--------------------------------------------" << endl;
    for (auto & url : urls) {
        endBuffer << url.first << endl;
    }
    output << endBuffer.str();
    output.close();
}

void tolower(string& str){
    std::transform(str.begin(), str.end(), str.begin(),
                   [](unsigned char c){ return std::tolower(c); });
}
