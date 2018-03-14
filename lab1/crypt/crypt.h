#pragma once
#include <iostream>
#include <functional>
#include <fstream>
#include <string>

int Crypt(const std::string & inFileName, const std::string & outFileName, const std::function<char(char)> & fn);

std::function<char(char)> GetCryptFunction(const uint8_t & key);
std::function<char(char)> GetDecryptFunction(const uint8_t & key);

uint8_t BitPermutation(char byte);
uint8_t BitPermutationBack(const uint8_t & byte);