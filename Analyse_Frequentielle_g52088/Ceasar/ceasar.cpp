#include "Ceasar/ceasar.hpp"


#include <string>
#include <vector>
#include <map>
#include <locale>
#include <iostream>
#include <cmath>
#include <tuple>
#include <algorithm>


int cipherNumber(int x, int k){
    return (x + k) % 26;
}

int decipherNumber(int x, int k){
    return ((x - k) + 26) % 26;
}


std::string cipher(std::string str, int k){
    std::string treatedString = pretreatement(str);

    std::string cypheredStr;
    std::string tmp;

    int nb;
    int nb_crypt;
    for (auto it = treatedString.cbegin(); it != treatedString.cend(); ++it) {

        //space
        if (*it == 32) {
            tmp = " ";
        }else{

            if (isUpper(*it)){
                nb = *it - 65;
                nb_crypt = cipherNumber(nb, k);
                tmp = alphaMaj[nb_crypt];

            }else if(isLower(*it)){
                nb = *it - 97;
                nb_crypt = cipherNumber(nb, k);
                tmp = alphaMin[nb_crypt];
            }else{
                tmp = *it;
            }

        }
        cypheredStr.append(tmp);
    }
    return cypheredStr;
}

std::string decipher(std::string str, int k){
    std::string decipheredStr;
    std::string tmp;


    int nb;
    int nb_crypt;
    for (auto it = str.cbegin(); it != str.cend(); ++it) {

        //space
        if (*it == 32) {
            tmp = " ";
        }else{

            if (isUpper(*it)){
                nb = *it - 65;
                nb_crypt = decipherNumber(nb, k);
                tmp = alphaMaj[nb_crypt];

            }else if(isLower(*it)){
                nb = *it - 97;
                nb_crypt = decipherNumber(nb, k);
                tmp = alphaMin[nb_crypt];
            }else{
                tmp = *it;
            }

        }
        decipheredStr.append(tmp);
    }

    return decipheredStr;
}


int findShift(std::string input){

    std::vector<std::tuple<int, std::string, double>> brute = bruteShift(input);

    //displayMapContent(brute);

    int shift = 1;
    double chi = std::get<2>(brute[0]);

    for (unsigned i = 0; i < brute.size(); ++i) {

        if (std::get<2>(brute[i]) <= chi) {
            chi = std::get<2>(brute[i]);
            shift = std::get<0>(brute[i]);
        }

    }
    return shift;
}

std::vector<std::tuple<int, std::string, double>> bruteShift(std::string str){

    std::vector<std::tuple<int, std::string, double>> bruteTable;

    for(int i = 1; i <= 26; i++){

        std::string shifted = decipher(str, i);

        auto tmp = std::make_tuple(i, shifted, chisqrt(shifted));

        bruteTable.push_back(tmp);
    }

    return bruteTable;
}



