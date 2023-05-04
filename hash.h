#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <string>

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
    { // see how const std::string changes it
        // Add your code here
        int strSize = k.length();
        unsigned long long w[5] = {0,0,0,0,0};
        for(int i{0}; i<strSize/6+1; i++){
          for(int j{5}; j>=0; j--){
            if(strSize>(6*i)+j){
            w[4-i] += letterDigitToNumber(k[strSize-i*6-j-1]); 
            if(j!=0 && (strSize > (6*i)+j+1)){
              w[4-i] *= 36;
            }
            }else{
              continue;
            }
            
          }
        }
        
      unsigned long long h = 0;
      for(int i{4}; i>=0; i--){
        h += (w[i] * rValues[i]);
      }
      return h;
    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
      char letterFixed = letter;
      if(letter >= 65 && letter <= 90){
        letterFixed -= 65;
      } else if(letter >= 97 && letter <= 122){
        letterFixed -= 97;
      }else if(letter >=48 && letter <= 57){
        letterFixed-=22;
      }
      return letterFixed;
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
