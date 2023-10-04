/* 
TODO
  - projet modulaire
  - check Noeud  I (Analyse Lexical) isKeyword(int)
  - check plus unaire ou addition
  - Gencode
*/

#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>

#include "./Types.cpp"
#include "./Objets/Token.cpp"
#include "./Objets/Operateur.cpp"
#include "./Objets/Symbole.cpp"
#include "./Objets/Noeud.cpp"
#include "./Analyses/AnalyseLexicale.cpp"
#include "./Analyses/AnalyseSyntaxique.cpp"



int nbVar = 0;
NoeudType variableLocale;


Symbole declarer  (std::string nom){
  for (int i = Variables.size() - 1; i >= 0; i--){
    if(Variables[i].m_nom.compare(nom) == 0) {
      std::cout << "ERREUR FATALE | declarer()" << std::endl;
      exit(1);
    }if(Variables[i].m_nom.compare("") == 0) {
      break;
    }
  }
  Symbole S = Symbole(nom);
  Variables.push_back(S);
  return S;
}

Symbole chercher(std::string nom) {
  for (int i = Variables.size() - 1; i >= 0; i--){
    if(Variables[i].m_nom.compare(nom) == 0){
      return Variables[i];
    }
  }
  std::cout << "ERREUR FATALE | chercher()" << std::endl;
  exit(1);
}

void begin() {
  Variables.push_back(Symbole(""));
}

void end() {
  for (int i = Variables.size() - 1; i >= 0; i--){
    if (Variables[i].m_nom.compare("") == 0){
      Variables.pop_back();
      break;
    }
    Variables.pop_back();
  }
}

void AnalSem(Noeud N){
  Symbole S;
  switch (N.m_type)
  {
  default:
    for (int i = 0; i <= N.m_sousNoeud.size(); i++)
    {
      AnalSem(N.m_sousNoeud[i]);
    }
    break;
  case noeudBlock:
    begin();
    for (int i = 0; i <= N.m_sousNoeud.size(); i++)
    {
      AnalSem(N.m_sousNoeud[i]);
    }
    end();
    break;
  case noeudDecl:
    S = declarer(N.m_valeur);
    S.position = nbVar;
    nbVar++;
    S.m_type = variableLocale;
    break;
  case noeudRef:
    S = chercher(N.m_valeur);
    N.m_symbole = S;
    break;
  }
}

// Noeud analyseSem(Noeud N)
// {
//   // switch(N.m_type)
//   // {
//   // default:
//   // pour chaque enfant E AnalyseSem(E);

//   // case Noeud_Block:
//   // pour chaque enfant E
//   // Begin()
//   // Pour chaque enfant E
//   // AnalyseSem(E)
//   // End()

//   // case Noeud_Declaration:
//   //  Declare(N.m_valeur)
//   // S.position = nbvar
//   // Nbvar++
//   // S.type = VariableLocale
//   //  case Noeud_Ref:
//   // S = chercher(N.valeur)
//   // N.Symbole = S
//   // }
// }

void GenCode(Noeud N) {
  switch (N.m_type){
    case noeudK :
      std::cout << "push" <<  N.m_valeur << std::endl;
      break;
    // case noeudtokenMoins :
    //   GenCode(N.m_sousNoeud[0]);
    //   GenCode(N.m_sousNoeud[1]);
    //   printf("sub \n");
    //   break;
    // case noeudtokenPlus:
    //   GenCode(N.m_sousNoeud[0]);
    //   GenCode(N.m_sousNoeud[1]);
    //   printf("add \n");
    //   break;
  }
}

int main() {
  line = "123";
  next();
  while (tokenCurrent.type != tokenEOF_){
    GenCode(AnalSyn()); // TODO: Ajouter analyse sémantique
  }
  return 0;
}
