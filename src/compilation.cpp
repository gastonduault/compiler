
#include <string>
#include <vector>
#include <fstream>
#include "stdlib.h"
#include <iostream>
#include "./Types.cpp"
#include "./Objets/Token.cpp"
#include "./Objets/Operateur.cpp"
#include "./Objets/Symbole.cpp"
#include "./Objets/Noeud.cpp"
#include "./Analyses/AnalyseLexicale.cpp"
#include "./Analyses/AnalyseSyntaxique.cpp"
#include "./Analyses/AnalyseSemantique.cpp"
#include "./GenCode.cpp"

std::string chemin = "/home/gaston/Bureau/Compilation_Gaston_DUAULT_Vladimir_GUILLEMONT_app4/Compilation_Gaston_DUAULT_Vladimir_GUILLEMONT_App4/src/Tests/prog1.c";

void lectureFichier(){
  std::ifstream file(chemin);
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

  debutAssembleur();
  setListeOperateurs();
  next();
//  debutAssembleur();
  while (tokenCurrent.type != tokenEOF_){
    nbVar = 0;
    Noeud noeud = AnalSyntaxique();
    AnalyseSementique(noeud);
    GenCode(noeud);
  }
  return 0;
}
