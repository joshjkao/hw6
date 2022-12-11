#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
  HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
  MyStringHash(bool debug = true)
  {
    if(false == debug){
      generateRValues();
    }
  }
  // hash function entry point (i.e. this is h(k))
  HASH_INDEX_T operator()(const std::string& k) const
  {
      // Add your code here
    unsigned long long w[5] = {0,0,0,0,0};
    std::string sub;
    unsigned int i = 0;
    if (k.size() != 0) i = k.size()-1;
    int a = 4;
    while (i >= 0) {
      if (i >= 5) {
        sub = k.substr(i-5, 6);
      }
      else {
        sub = k.substr(0,i+1);
      }
      // std::cout << sub << std::endl;
      unsigned long long num = 0;
      for (unsigned int j = 0; j < sub.size(); j++) {
        num = num * 36 + letterDigitToNumber(sub[j]);
      }
      w[a--] = num;
      // std::cout << num << std::endl;
      if (i > 5) {
        i -= 6;
      }
      else {
        break;
      }
    }
    size_t res = 0;
    for (unsigned int k = 0; k < 5; k++) {
      // std::cout << "w" << i << "=" << w[i] << std::endl;
      res += rValues[k] * w[k];
    }
    return res;

  }

  // A likely helper function is to convert a-z,0-9 to an integral value 0-35
  HASH_INDEX_T letterDigitToNumber(char letter) const
  {
      // Add code here or delete this helper function if you do not want it
    if (letter >= 97 && letter <= 122) {
      return int(letter) - 97;
    }
    else if (letter >= 65 && letter <= 90) {
      return int(letter) - 65;
    }
    else {
      return int(letter) - 22;
    }
  }

  // Code to generate the random R values
  void generateRValues()
  {
    // obtain a seed from the system clock:
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::mt19937 generator (seed);  // mt19937 is a standard random number generator

    // Simply call generator() [it has an operator()] to get another random number
    for(int i{ 0 }; i < 5; ++i)
    {
      rValues[i] = generator();
    }
  }
};

#endif
