#include "Tools/tools.hpp"

#include <string>
#include <vector>
#include <map>
#include <locale>
#include <iostream>
#include <cmath>
#include <tuple>
#include <algorithm>

std::string removeAccent(std::string & str){

    std::string withAccent = "æèéêëàáâãäåìíîïòóôõöùúûüÆÈÉÊËÀÁÂÃÄÅÌÍÎÏÒÓÔÕÖÙÚÛÜ";
    std::string withoutAccent = "eeeeeaaaaaaiiiiooooouuuuEEEEEAAAAAAIIIIOOOOOUUUU";

    for (auto it = str.begin(); it != str.end(); it++) {

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)

        // Quand j'écris É ça devient Ã‰ donc si le caractère courant est Ã(-61), je l'enlève. Il reste ‰ qui deviendra E.
        if (*it == withAccent.at(0)) {
            str.erase(it, it+1);
        }

        size_t i = 0;
        while (i < withAccent.size()) {
            if (*it == withAccent[i+1]) {
                *it = withoutAccent[i/2];
                break;
            }
            i += 2;
        }
#else
        size_t i = 0;
        while (i < withAccent.size()) {
            if (*it == withAccent[i]) {
                *it = withoutAccent[i];
                break;
            }
            i++;
        }
#endif
    }
    return str;
}


int countSpaceNb(std::string str){
    int cpt = 0;
    for (auto it = str.cbegin(); it < str.cend(); ++it) {
        if (*it == 32) {
            cpt++;
        }
    }
    return cpt;
}

std::string pretreatement(std::string& str){
    std::string tmp;

    str = removeAccent(str);


//    //enlever les caracteres speciaux
//    for (auto it = str.cbegin(); it != str.cend(); ++it) {
//        if ((isUpper(*it)) || (isLower(*it)) || *it == 32) {
//            tmp += *it;
//        }
//    }

//     str = tmp;

//     std::cout << "string traitee (1): " << str << std::endl;
//     tmp.clear();

     //tout mettre en maj
    for (auto it = str.cbegin(); it != str.cend(); ++it) {
        if(*it == 32){
            tmp += *it;
        }else if (isLower(*it)) {
            tmp += (*it - 32);
        }else{
            tmp += *it;
        }
    }

    str = tmp;
    std::cout << "string traitee (2): " << str << std::endl;
    return str;
}


std::map<char, int> occurence(std::string str){
    std::map<char, int> occurenceOfLetters;

    unsigned i, cpt;
    char currentLetter;

    i = 0;

    while(i < str.size()){
        currentLetter = str[i];
            cpt = 0;

            for (auto it = str.cbegin(); it < str.cend(); ++it) {
                if(*it == currentLetter){
                    cpt++;
                }
            }
            occurenceOfLetters.insert(std::make_pair(currentLetter, cpt));

        i++;
    }
    return occurenceOfLetters;
}

void displayMapContent(std::vector<std::tuple<int, std::string, double>> vectorTuple){
    std::cout << std::endl << std::endl;
    for (unsigned i = 0; i < vectorTuple.size(); ++i) {
        std::cout << std::get<0>(vectorTuple[i])<< " " << std::get<1>(vectorTuple[i]) << " : " << std::get<2>(vectorTuple[i]) << std::endl;
    }
}


void displayMapContent(std::vector<std::tuple<int, int, std::string>> vectorTuple){
    std::cout << "ID\tintervalle\t      sous-chaine" << std::endl;
    for (unsigned it = 0; it < vectorTuple.size(); ++it) {
        std::cout << std::get<0>(vectorTuple[it])<< "\t    " << std::get<1>(vectorTuple[it]) << "\t\t : " << std::get<2>(vectorTuple[it]) << std::endl;
    }
}

void displayMap(std::map<int, std::string> map){
    for(auto it = map.cbegin(); it != map.cend(); ++it)
    {
        std::cout << it->first << " : " << it->second << "\n";
    }
}


double chisqrt(std::string str){
    std::map<char, int> mapOcc = occurence(str);

    int cptNumberSpace = countSpaceNb(str);
    unsigned inputLength = str.size() - cptNumberSpace;
    double chi;

    for (auto it = mapOcc.cbegin(); it != mapOcc.cend(); ++it){

        char c = it->first;

        auto itFR = freqFR.cbegin();
        while (itFR != freqFR.cend() && c != itFR->first){
            ++itFR;
        }

        double expNb = (((itFR->second)*inputLength)/100);
        double result = (std::pow((expNb - it->second), 2)/it->second);
        chi += result;
    }
    return chi;
}


void displayMap(std::map<char, int> map){
    for(auto it = map.cbegin(); it != map.cend(); ++it)
    {
        std::cout << it->first << " : " << it->second << "\n";
    }
}


void displayMap(std::vector<std::map<char, int>>  vectorMap){
    for(auto iti = vectorMap.begin(); iti != vectorMap.end(); iti++){

        for(auto itj = iti->begin(); itj != iti->end(); ++itj){
            std::cout << itj->first << " : " << itj->second << std::endl;
        }

    }
}

bool isUpper(char ch){
    return ch >= 65 && ch <= 90;
}

bool isLower(char ch){
    return ch >= 97 && ch <= 122;
}
