#include <stdlib.h>

#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char** argv) {
  ifstream infile;
  infile.open("CodingCPlusPlus", std::ios::in);
  if (infile.is_open()) {
    cout << "CodingCPlusPlus is exist, we should delete it" << std::endl;
    if (system("rm -rf ./CodingCPlusPlus") == 0) {
      cout << "delete CodingCPlusPlus success" << endl;
    } else {
      cout << "delete CodingCPlusPlus failed, just return" << endl;
    }
  } else {
    cout << "CodingCPlusPlus is not exist" << std::endl;
  }
  int result = system("unzip text.zip");
  if (result != 0) {
    cout << "unzip text.zip failed" << endl;
  } else {
    cout << "unzip text.zip success" << endl;
    if(system("mv CodingCPlusPlus ./update/") == 0) {
        cout << "update success" << endl;
    }else{
        cout << "update failure" << endl;
    }
  }
}