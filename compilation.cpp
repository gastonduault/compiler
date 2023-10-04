/*
TODO: lecture de tout le fichier dans un string
TODO: check plus unaire ou addition (pr tous les signes: && == -- || )
TODO: check  fonction
TODO: check while if else (Syntaxique)
TODO: Gencode
  - addition
  - soustraction
  - not
  -multiplication
  -division
  - moins_unaire
  - pointeur_adresse
  - noeud ET
  - noeud return
  - noeud drop
  - noeud declaration
  - noeud ==
  - noeud !=
  - noeud reference
  - noeud affectation
  - continue
  - break
  - target
  - fonction
  - loop
  - appel
TODO: Doit-on faire un main qui appelle compile ?
*/

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#include <fstream>

#include "./Types.cpp"
#include "./Objets/Token.cpp"
#include "./Objets/Operateur.cpp"
#include "./Objets/Symbole.cpp"
#include "./Objets/Noeud.cpp"
#include "./Analyses/AnalyseLexicale.cpp"
#include "./Analyses/AnalyseSyntaxique.cpp"
#include "./Analyses/AnalyseSemantique.cpp"
#include "./GenCode.cpp"


std::string lectureFichier(){
  std::ifstream file("/home/gaston/Documents/Polytech/compilation/Tests/prog1.c");
//  if(file) {
//    auto tailleSize = file.tellg();
//    file.seekg(std::ios::beg);
//    std::string content(file.tellg(), 0);
//    file.read(&content[0], tailleSize);
//    return content;
//  }
  if ( file ) {
    std::string line;
    getline(file,line);
    return line;
  }
  else{
    printf("ERREUR FATALE | erreur lecture fichier");
    exit(1);
  }
}


int main() {
  code = lectureFichier();
  Noeud noeud;
  next();
  while (tokenCurrent.type != tokenEOF_){
    noeud = AnalSyntaxique();
    AnalyseSementique(noeud);
    GenCode(noeud);
  }
  return 0;
}
