#ifndef TOOLS_HPP
#define TOOLS_HPP


#include <string>
#include <vector>
#include <map>
#include <locale>
#include <iostream>
#include <cmath>
#include <tuple>
#include <algorithm>

/**
 * @brief pretreatement
 * To pretreated a given string. Pretreated means remove all of accents ( !!!!! DOIS S'OCCUPER AUSSI D'AUTRE CHOSE !!!!!)
 * @param str to be pretreated
 * @return the pretreated string
 */
std::string pretreatement(std::string& str);
/**
 * @brief removeAccent
 * @param str cette string va être traitee et on va enlever tous les accents
 * @return une chaine sans accents
 */
std::string removeAccent(std::string & str);

/**
 * @brief occurence
 * Allow to search the occurence of each letter on the given string
 * @param str
 * @return a map in the form of :
 * ' A ' : 3
 * means on the fiven string there are 3 A
 */
std::map<char, int> occurence(std::string str);

/**
 * @brief displayMapContent
 * Display the content of the given vectorTuple
 * @param map
 */
void displayMapContent(std::vector<std::tuple<int, std::string, double>> vectorTuple);

/**
 * @brief displayMapContent
 * Display the content of the given vectorTuple
 * @param map
 */
void displayMapContent(std::vector<std::tuple<int, int, std::string>> vectorTuple);

/**
 * @brief displayMap
 * Display the content of the given map <char, int>
 * @param map
 */
void displayMap(std::map<char, int> map);

/**
 * @brief displayMap
 * Display the content of the given map <int, string>
 * @param map
 */
void displayMap(std::map<int, std::string> map);

/**
 * @brief displayMap
 * Display the content of the given vectorMap
 * @param map
 */
void displayMap(std::vector<std::map<char, int>>  vectorMap);

///**
// * @brief findTheKey
// * @param ch
// * @return
// */
//char findTheKey(char ch);

/**
 * @brief isUpper
 * @param ch
 * @return true if the given char is a upper char
 */
bool isUpper(char ch);

/**
 * @brief isLower
 * @param ch
 * @return true if the given char is a lower char
 */
bool isLower(char ch);

/**
 * @brief chisqrt
 * Allow to find the chi sqrt of th egiven str
 * @param input
 * @return
 */
double chisqrt(std::string str);

/**
 * @brief countSpaceNb
 * @param str
 * @return the number of space in the given string
 */
int countSpaceNb(std::string str);

/**
    map of the frequence for each letter in FRENCH
*/
const std::map<char, float> freqFR = {
    {'A', 8.15},
    {'B', 0.97},
    {'C', 3.15},
    {'D', 3.73},
    {'E', 17.39},
    {'F', 1.12},
    {'G', 0.97},
    {'H', 0.85},
    {'I', 7.31},
    {'J', 0.45},
    {'K', 0.02},
    {'L', 5.69},
    {'M', 2.87},
    {'N', 7.12},
    {'O', 5.28},
    {'P', 2.80},
    {'Q', 1.21},
    {'R', 6.64},
    {'S', 8.14},
    {'T', 7.22},
    {'U', 6.38},
    {'V', 1.64},
    {'W', 0.03},
    {'X', 0.41},
    {'Y', 0.28},
    {'Z', 0.15},
};


#endif // TOOLS_HPP
