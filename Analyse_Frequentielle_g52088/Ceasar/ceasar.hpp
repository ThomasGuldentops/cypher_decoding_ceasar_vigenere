#ifndef CYPHER_HPP
#define CYPHER_HPP

#include "Tools/tools.hpp"

static char alphaMaj[26] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
static char alphaMin[26] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};


/**
 * @brief cipherNumber
 * @param x a number (its place in the alphabet)
 * @param k the shift
 * @return result of mod 26 of sum between x and k
*/
int cipherNumber(int x, int k);

/**
 * @brief decipherNumber
 * @param x a number (its place in the alphabet)
 * @param k the shift
 * @return result of mod 26 of sub between x and k
*/
int decipherNumber(int x, int k);


/**
 * @brief cipher
 * @param str string to be cypher
 * @param k shift
 * @return cyphered word
 */
std::string cipher(std::string str, int k);

/**
 * @brief decipher
 * @param str string to be decypher
 * @param k shift
 * @return decyphered word
 */
std::string decipher(std::string str, int k);

/**
 * @brief bruteShift
 * @param str ciphered sentence
 * @return all of the possibility with their chi for a given crypted string
 */
std::vector<std::tuple<int, std::string, double> > bruteShift(std::string str);

/**
 * @brief findShift
 * search among all of string given in <code> bruteShift</code> method the minimal chi
 * @param input
 * @return
 */
int findShift(std::string input);


#endif // CYPHER_HPP
