/*
TODO: lecture de tout le fichier dans un string
TODO: check plus unaire ou addition (pr tous les signes: && == -- || )
TODO: check  fonction
TODO: check while if else (Syntaxique)
TODO: Gencode
  - addition
  - soustraction
  - not
  - multiplication
  - division
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


void lectureFichier(){
  std::ifstream file("/home/gaston/Documents/Polytech/compilation/Tests/prog1.c");
  std::string res = "";
  if(file.is_open()) {
    while(file.good()) {
      file >> res;
      code.append(res);
    }
  }
  else{
    printf("ERREUR FATALE | erreur lecture fichier");
    exit(1);
  }
}


int main() {
  lectureFichier();

  setListeOperateurs();
  Noeud noeud;
  next();

  while (tokenCurrent.type != tokenEOF_){
    nbVar = 0;
    noeud = AnalSyntaxique();
    AnalyseSementique(noeud);
    GenCode(noeud);
  }
  return 0;
}
