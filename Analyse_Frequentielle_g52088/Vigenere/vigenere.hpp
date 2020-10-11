#ifndef VIGENERE_HPP
#define VIGENERE_HPP


#include "Ceasar/ceasar.hpp"

/**
 * @brief vigenereCipher
 * Allow to cipher the given string following the vigenere cipher
 * @param str
 * @param k the key
 * @return the str Cipher
 */
std::string vigenereCipher(std::string str, std::vector<char> k);

/**
 * @brief vigenereDecipher
 * Allow to decipher the given string following the vigenerede cipher
 * @param str
 * @param k the key
 * @return the str Decipher
 */
std::string vigenereDecipher(std::string str, std::vector<char> k);

/**
 * @brief cutSubString
 * @param str
 * @return
 */
std::vector<std::tuple<int, int, std::string>> cutSubString(std::string str);

/**
 * @brief occurenceInSubString
 * @param allSubString
 */
std::vector<char> vigenereDecypherWithoutTheKey(std::vector<std::tuple<int, int, std::string>> allSubString);


#endif // VIGENERE_HPP
