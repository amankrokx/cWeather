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

void showWeather(string w) {
  std::vector<std::string>   a;

  std::stringstream  dataa(w);

  std::string line;
  while(std::getline(dataa,line,',')) {
    a.push_back(line); // Note: You may get a couple of blank lines
  }

  cout << "Weather : " << a[0] << endl;
  cout << "Description : " << a[1] << endl;
  // cout << "  " << a[2] << endl;
  cout << "Temperature : " << a[3] << endl;
  cout << "Feels Like : " << a[4] << endl;
  cout << "Pressure : " << a[5] << " Bar" << endl;
  cout << "Humidity : " << a[6] << endl;
  cout << "Wind Speed : " << a[7] << " Kmph" << endl;
  cout << "Wind Direction : " << a[8] << endl;
  cout << "At : " << a[9] << endl;
  
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
  data.close();
  string res = http(url);
  showWeather(res);
  string userinp;
  cout << "Enter your location : ";
  getline(cin, userinp);
  userinp = "curl -o data.txt http://krokxweather.herokuapp.com/?address=" + url_encode(userinp);
  res = http(userinp);
  showWeather(res);
  return 0;
}