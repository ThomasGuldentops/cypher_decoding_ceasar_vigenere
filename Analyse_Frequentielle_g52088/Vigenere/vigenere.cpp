#include "Vigenere/vigenere.hpp"

#include <string>
#include <vector>
#include <map>
#include <locale>
#include <iostream>
#include <cmath>
#include <tuple>
#include <algorithm>

std::string vigenereCipher(std::string str, std::vector<char> k){
    std::string processedString = pretreatement(str);

    std::string cipheredStr;
    std::string tmp;

    int nb_crypt;
    int nb;
    int i = 0;

    for (auto it = processedString.cbegin(); it != processedString.cend(); ++it) {
        //space
        if (*it == 32) {
            tmp = " ";
        }else{
            //si majuscule
            if (isUpper(*it)){
                nb = *it - 65;
                nb_crypt = cipherNumber(nb, k[i] - 65);
                tmp = alphaMaj[nb_crypt];
            }else if(isLower(*it)){
                nb = *it - 97;
                nb_crypt = cipherNumber(nb, k[i] - 97);
                tmp = alphaMin[nb_crypt];
            }else{
                tmp = *it;
            }
             i = (i + 1) % k.size();
        }

        cipheredStr.append(tmp);
    }
    return cipheredStr;

}


std::string vigenereDecipher(std::string str, std::vector<char> k){
    std::string deciphered;
    std::string tmp;

    int nb_crypt;
    int nb;
    int i = 0;
    for (auto it = str.cbegin(); it != str.cend(); ++it) {
        //space
        if (*it == 32) {
            tmp = " ";
        }else{
            //si majuscule
            if (isUpper(*it)){
                nb = *it - 65;
                nb_crypt = decipherNumber(nb, k[i] - 65);
                tmp = alphaMaj[nb_crypt];

            }else if(isLower(*it)){
                nb = *it - 97;
                nb_crypt = decipherNumber(nb, k[i] - 97);
                tmp = alphaMin[nb_crypt];;
            }else{
                tmp = *it;
            }

            i = (i + 1) % k.size();
        }

        deciphered.append(tmp);
    }

    return deciphered;
}

/**
 * @brief decoupageEnSousChaine
 *
 *   int        int           std::string
 *   ID      intervalle       sous-chaine
 * @param str
 * @return
 */
std::vector<std::tuple<int, int, std::string>> cutSubString(std::string str){

    int intervale = 1;
    int id = 1;

    std::string strTreated;
    std::string subString;
    std::vector<std::tuple<int, int, std::string>> allSubStrings;
    char tmpChar;

    for (int j = 0; j < str.length(); ++j) {
        if (str[j] != ' ') {
            //sont en minuscule donc on les passe en majuscule
            if (str[j] >= 97 && str[j] <= 122) {
                strTreated += str[j] - 32;
            }else{
                strTreated += str[j];
            }
        }
    }


    while(intervale <= 10){
        int i = 0;
        while ( i < strTreated.length()) {

            if (i == 0) {
                tmpChar = strTreated[0];
            }else{
                tmpChar = strTreated[i];
            }

            i += intervale;
            subString += tmpChar;
        }
        auto currentSousChaine = std::make_tuple(id, intervale, subString);
        allSubStrings.push_back(currentSousChaine);

        subString.clear();
        intervale++;
        id++;
    }
    return allSubStrings;
}

/**
 * @brief calculateOccurence
 * Allow to count the occurence of the currentTreatedString
 * @param currentOccurence
 * @param currentChar
 * @param i
 * @param currentTreatedString
 * @param tmp
 */
void calculateOccurence(int &currentOccurence, char &currentChar, int &i, std::string &currentTreatedString, std::map<char, int> &tmp)
{
    while(i < currentTreatedString.size()){
        currentChar = currentTreatedString[i];
        currentOccurence = 0;

        for (auto itStr = currentTreatedString.cbegin(); itStr != currentTreatedString.cend(); ++itStr) {
            if(*itStr == currentChar){
                currentOccurence++;
            }
        }

        tmp.insert(std::make_pair(currentChar, currentOccurence));
        i++;
    }
}

void calculateIC(int &intervale, float &closelyICNearFrench, std::map<char, int> &tmp, std::string &currentTreatedString, int &keyLength)
{
    float IC = 0.0;
    auto itTmp = tmp.cbegin();
    for (int i = 0; i < tmp.size(); ++i) {

        IC +=(float) (((float)itTmp->second * (itTmp->second - 1))
                      / (float) (currentTreatedString.size() * (currentTreatedString.size() - 1)));

        itTmp++;
    }



    //if (IC > closelyICNearFrench && (IC > 0.0700 && IC <= 0.0850))
    if (IC > closelyICNearFrench  && (IC <= 0.078)) {
        closelyICNearFrench = IC;
        keyLength = intervale;
    }

}


std::map<int, std::string> cutIntoPart(std::string str, int cut){
    std::map<int, std::string> keyEmplacement;


    std::string tmp;
    int cpt, it;
    cpt = it = 0;

    while(cpt < cut){

        for (it = cpt; it < str.size(); it += cut) {
            tmp += str[it];
        }

        keyEmplacement.insert(std::make_pair(cpt, tmp));

        tmp.clear();
        cpt++;
    }

//    std::cout << "keyEmplacement : \n";
//    displayMap(keyEmplacement);
//    std::cout << std::endl;

    return keyEmplacement;

}

std::vector<char>findVigenereKey(int keyLength, std::vector<std::tuple<int, int, std::string>> allSubString)
{
    std::map<int, std::string> cutted = cutIntoPart(std::get<2>(allSubString[0]), keyLength);

    int key;
    std::vector<char> finalKey;

    std::cout << std::endl;
    for (auto it = cutted.cbegin(); it != cutted.cend(); ++it) {
        key = findShift(it->second);

        std::cout << "L" << it->first << " : " << alphaMaj[key%26] << std::endl;
        finalKey.push_back(alphaMaj[key%26]);
    }
    std::cout << std::endl;
//    // display the key
//    for (int i = 0; i < finalKey.size(); ++i) {
//        std::cout << "finalKey["<< i << "] : " << finalKey[i] << std::endl;
//    }

     return finalKey;
}

std::vector<char> vigenereDecypherWithoutTheKey(std::vector<std::tuple<int, int, std::string>> allSubString){

    std::vector<char> key;
    std::map<char, int> tmp;
    char currentChar;
    int currentOccurence;

    std::string currentTreatedString;

    int intervale = 1;
    int keyLength;

    float closelyICNearFrench = 0.0;

    for (auto it = 0; it < allSubString.size(); ++it) {
        currentTreatedString = std::get<2>(allSubString[it]);

        int i = 0;

        calculateOccurence(currentOccurence, currentChar, i, currentTreatedString, tmp);
        calculateIC(intervale, closelyICNearFrench, tmp, currentTreatedString, keyLength);

        tmp.clear();
        intervale++;
    }

    //std::cout <<"closelyICNearFrench : " <<  closelyICNearFrench <<"  keyLength : " <<  keyLength << std::endl << std::endl;

    key = findVigenereKey(keyLength, allSubString);

    return key;
}
