#include <iostream>
#include <cctype>
#include <vector>
#include <iomanip>
#include <fstream>
#include <string>
#include <algorithm>
#include <stdio.h>

using namespace std;

string http(string url) {
  system(url.c_str());//Executing script
  system("clear");//Clearing previous logs so that the result can be seen neatly
  string res;
  ifstream file("data.txt");//Retrieving response from data.txt
  getline(file, res);
  file.close();
  return res;
}

string url_encode(const string &value) {
    ostringstream escaped;
    escaped.fill('0');
    escaped << hex;

    for (string::const_iterator i = value.begin(), n = value.end(); i != n; ++i) {
        string::value_type c = (*i);

        // Keep alphanumeric and other accepted characters intact
        if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
            escaped << c;
            continue;
        }

        // Any other characters are percent-encoded
        escaped << uppercase;
        escaped << '%' << setw(2) << int((unsigned char) c);
        escaped << nouppercase;
    }

    return escaped.str();
}

int main() {
  ifstream data("coord.txt");//Retrieving response from data.txt
  string lat;
  string lon;
  string addr;
  string url = "curl -o data.txt http://krokxweather.herokuapp.com/";
  getline(data, lat);
  if (lat.length() > 0) {
    getline(data, lon);
    getline(data, addr);
    url += "?lat=" + lat + "&lon=" + lon;
  }
  string res = http(url);
  std::vector<std::string>   arst;

  std::stringstream  dataa(res);

  std::string line;
  while(std::getline(dataa,line,',')) {
    arst.push_back(line); // Note: You may get a couple of blank lines
                            // When multiple underscores are beside each other.
    cout << line << endl;
  }
  cout << res << "\nDone\n";//Voila
  string userinp;
  cout << "Enter your location : ";
  getline(cin, userinp);
  userinp = "curl -o data.txt http://krokxweather.herokuapp.com/?address=" + url_encode(userinp);
  res = http(userinp);
  cout << res << endl;
  return 0;
}