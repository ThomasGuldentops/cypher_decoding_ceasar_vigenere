#include "Vigenere/vigenere.hpp"

#include <fstream>


std::string toUpper(std::string str);
void displayHeader(std::string str);

int main(int argc, char *argv[])
{
    /*
     * Aspect du programme & utilisation
     *
     * ./[nomProgramme] TypeCryptage Decrypter/Crypter Clef Chaine/Fichier
     *
     *
     * --------------------
     *  Ceasar :
     *
     * ---- crypter
     * ./[nomProgramme] c c 6 ../Fichiers/aCrypter.txt
     *
     *
     * ---- Decrypter :
     *
     *  -- avec la clef
     *./[nomProgramme] c d 6 ../Fichiers/ceasarCrypted.txt
     *
     *  -- sans la clef
     *./[nomProgramme] c d 0 ../Fichiers/ceasarCrypted.txt
     *
     *
     * --------------------
     * Vigenere :
     *
     * ---- crypter
     * ./[nomProgramme] v c KEY ../Fichiers/aCrypter.txt
     *
     * ---- Decrypter :
     *
     * -- avec la clef
     * ./[nomProgramme] v d KEY ../Fichiers/vigenereCrypted.txt
     *
     *  -- sans la clef
     * ./[nomProgramme] v d 0 ../Fichiers/vigenereCrypted.txt
     *
     *
     */

    if (argc == 1) {
        std::cout << "Vous n'avez pas entrez d'arguments ! " << std::endl;
        return 1;
    }else{
        if (*argv[1] == 'c') {
            std::string cipherType;
            std::string operation;
            int ceasarKey;
            std::string fileWay;

            cipherType = "ceasar";
            displayHeader("ceasar");

            if(argv[4] != " "){
                fileWay = argv[4];
            }

            std::cout << "fileWay : " << fileWay << std::endl;
            //cryptage cesar
            if (*argv[2] == 'c') {
                //std::string currentFile = fileWay;
                std::ifstream aCrypter(fileWay, std::ios::in);

                if(aCrypter){
                    std::cout << "\n------ Vous avez choisi de crypter le fichier  \n" << fileWay << std::endl;

                    operation = "cryptage.";
                    //vérifie si on a entré une clé
                    if(argv[3] != 0){
                        ceasarKey = atoi(argv[3]);
                        //std::cout << "Clee choisie : " << ceasarKey << std::endl;
                    }

                    //mettre le contenu du fichier dans un string
                    std::string toCipher;
                    std::string line;

                    while(std::getline(aCrypter, line)){
                        toCipher += line;
                    }


                    //std::cout << "affichage de la phrase a crypter :  \n" << toCipher << std::endl;

                    //maintenant faut crypter le texte et le mettre dans un fichier qu'on va créer appellé ceasarCrypted.txt

                    std::string ceasarCiphered = cipher(toCipher, ceasarKey);
                    std::ofstream ceasarCrypted;
                    std::cout << "Phrase ciphered : " << ceasarCiphered << std::endl;
                    ceasarCrypted.open("../Fichiers/ceasarCrypted.txt", std::ios::out);

                    if (ceasarCrypted) {
                        ceasarCrypted << ceasarCiphered;
                        ceasarCrypted.close();
                    }else{
                        std::cout << "Erreur d'ecriture du fichier \n"  << std::endl;
                        return 1;
                    }


                    std::cout << "Le contenu du fichier a crypte est dans ceasarCrypted.txt" << std::endl;

                    aCrypter.close();

                }else{
                    std::cout << "Erreur d'ouverture du fichier \n"  << std::endl;
                    return 1;
                }

            }else if(*argv[2] == 'd'){
                //decrypter avec cesar
                std::ifstream aDecrypter(fileWay, std::ios::in);
                std::cout << "\n------ Vous avez choisi de decrypter le fichier  \n" << fileWay << std::endl;
                operation = "decryptage.";


                if(aDecrypter){
                    std::string toDecipher;
                    std::string line;

                    while(std::getline(aDecrypter, line)){
                        toDecipher += line;
                    }

                    std::ofstream ceasarDecrypted;
                    ceasarDecrypted.open("../Fichiers/ceasarDecrypted.txt", std::ios::out);

                    if(ceasarDecrypted){
                        //vérifie si on a entré une clé
                        if(*argv[3] != '0'){
                            ceasarKey = atoi(argv[3]);
                            std::cout << "Clee entree : " << ceasarKey << std::endl;

                            std::string ceasarDecipher = decipher(toDecipher, ceasarKey);
                            ceasarDecrypted << ceasarDecipher;
                            // std::cout << "Mot decrypter : " << toDecipher << std::endl << std::endl;

                        }else{

                            int key = findShift(toDecipher);
                            std::cout << "\n\n------ Resultat de la recherche de la clef\nLa clef qui a ete trouvee est : " << key << std::endl << std::endl;

                            std::string decipheredWithoutShift = decipher(toDecipher, key);
                            ceasarDecrypted << decipheredWithoutShift;
                            ceasarDecrypted.close();
                            /* std::cout << "Mot decrypter : " << decipheredWithoutShift << std::endl;*/

                        }
                    }else{
                        std::cout << "Erreur d'ecriture du fichier \n"  << std::endl;
                        return 1;
                    }


                    aDecrypter.close();
                }else{
                    std::cout << "Erreur d'ouverture du fichier \n"  << std::endl;
                    return 1;
                }

            }
        } else if(*argv[1] == 'v'){
            std::string keyInString;
            std::string fileWay;
            std::vector<char> keyVigenere;

            displayHeader("vigenere");

            if(argv[4] != " "){
                fileWay = argv[4];
            }

            if (*argv[2] == 'c') {

                std::ifstream aCrypter(fileWay, std::ios::in);

                if (aCrypter) {
                    std::cout << "\n------ Vous avez choisi de crypter le fichier  \n" << fileWay << std::endl;
                    if(*argv[3] != '0'){
                        keyInString = argv[3];

                        //assembler la clef
                        for (auto i = 0; i < keyInString.size(); ++i) {
                            keyVigenere.push_back((keyInString[i]));
                        }

                        //afficher la clef
                        std::string displayKey;
                        for (int i = 0; i < keyVigenere.size(); ++i) {
                            displayKey += keyVigenere[i];
                        }

                        std::cout << "Clee entree : " << displayKey << std::endl;


                        std::string toCipher;
                        std::string line;

                        while(std::getline(aCrypter, line)){
                            toCipher += line;
                        }

                        std::string vigenereCiphered = vigenereCipher(toCipher, keyVigenere);
                        std::ofstream vigenereCrypted;
                        vigenereCrypted.open("../Fichiers/vigenereCrypted.txt", std::ios::out);

                        if (vigenereCrypted) {
                            vigenereCrypted << vigenereCiphered;
                            vigenereCrypted.close();
                        }else{
                            std::cout << "Erreur d'ecriture du fichier \n"  << std::endl;
                            return 1;
                        }

                        std::cout << "Le contenu du fichier a crypte est dans vigenereCrypted.txt" << std::endl;

                        aCrypter.close();
                    }
                }else{
                    std::cout << "Erreur d'ouverture du fichier \n"  << std::endl;
                    return 1;
                }

                //decrypter avec vigenere
            }else if(*argv[2] == 'd'){

                std::cout << "\n------ Vous avez choisi de decrypter le fichier  \n" << fileWay << std::endl;

                std::ifstream aDecrypter(fileWay, std::ios::in);

                if (aDecrypter) {
                    std::string toDecipher;
                    std::string line;

                    while(std::getline(aDecrypter, line)){
                        toDecipher += line;
                    }

                    std::ofstream vigenereDecrypted;
                    vigenereDecrypted.open("../Fichiers/vigenereDecrypted.txt", std::ios::out);

                    if (vigenereDecrypted) {

                        //avec la clef
                        if(*argv[3] != '0'){
                            keyInString = argv[3];

                            //assembler la clef
                            for (auto i = 0; i < keyInString.size(); ++i) {
                                keyVigenere.push_back((keyInString[i]));
                            }

                            //afficher la clef
                            std::string displayKey;
                            for (int i = 0; i < keyVigenere.size(); ++i) {
                                displayKey += keyVigenere[i];
                            }
                            std::cout << "Clee entree : " << displayKey << std::endl;

                            std::string vigenereDecypher = vigenereDecipher(toDecipher, keyVigenere);
                            vigenereDecrypted << vigenereDecypher;
                            vigenereDecrypted.close();

                        }else if(*argv[3] == '0'){ //on donne pas la clef

                            std::vector<std::tuple<int, int, std::string>> decoupe = cutSubString(toDecipher);
                            keyVigenere = vigenereDecypherWithoutTheKey(decoupe);
                            std::string decipheredVigenereWithoutKey = vigenereDecipher(toDecipher, keyVigenere);

                            vigenereDecrypted << decipheredVigenereWithoutKey;
                            vigenereDecrypted.close();
                        }
                        std::cout << "Le contenu du fichier decrypte est dans vigenereDecrypted.txt" << std::endl;

                    }else{
                        std::cout << "Erreur d'ecriture du fichier \n"  << std::endl;
                        return 1;
                    }

                    aDecrypter.close();
                }else{
                    std::cout << "Erreur d'ouverture du fichier \n"  << std::endl;
                    return 1;
                }
            }
        }
    }
    return 0;
}



std::string toUpper(std::string str){
    std::string upper;

    for (int i = 0; i < str.length(); ++i) {
        upper += std::toupper(str[i]);
    }
    return upper;
}

void displayHeader(std::string str){
    std::cout<<
                "+ ======================================== +\n"
                "|  Vous avez choisis le cryptage : " + toUpper(str)+ "  |\n"
                                                                      "+ ======================================== +"
             << std::endl << std::endl;
}

