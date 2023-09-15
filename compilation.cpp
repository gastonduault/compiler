/* 
TODO 
  - check Noeud A E P I (Analyse Lexical)
  - check plus unaire ou addition
  - Gencode
*/

#include <iostream>
#include <stdbool.h>
#include <string>
#include <string.h>
#include <fstream>
#include <cstring>
#include <typeinfo>
#include <vector>
#include <stdlib.h>

// Type à repérer
enum TokenType
{
  K,        // Constante
  I,        // Identificateur
  SPlus,    // +
  SMoins,   // -
  SDiv,     // /
  SMult,    // *
  Segal,    // =
  ParaO,    // (
  ParaF,    // )
  AccO,     // {
  AccF,     // }
  Pvirgule, // ;
  virgule,  // ,
  EOF_,
  token_int,
  debug
};

enum NoeudType
{
  noeudK,
  noeudI,        // Identificateur
  noeudSPlusUnaire,    // +
  noeudSMoinsUnaire,   // -
  noeudSDiv,     // /
  noeudSMult,    // *
  noeudSegal,    // =
  noeudParaO,    // (
  noeudParaF,    // )
  noeudAccO,     // {
  noeudAccF,     // }
  noeudPvirgule, // ;
  noeudEOF_,
  noeudDebug,
  noeudBlock,
  noeudDrop,
  noeudRef, //Expression
  noeudAffect, //Expression
  noeudSeq, // I
  noeudDecl, // I
  noeudVide, 
};


const char SIGNE_MOINS = '-';
const char SIGNE_PLUS = '+';
const char SIGNE_DIV = '/';
const char SIGNE_MULT = '*';
const char PARA_OUV = '(';
const char PARA_FERM = ')';
const char SIGNE_EGAL = '=';
const char ACC_OUV = '{';
const char ACC_FERM = '}';
const char POINT_VIRGULE = ';';
const char VIRGULE = ',';

const std::string DEBUG = "dbg";

int nbVar = 0;
NoeudType variableLocale;

struct Token{
  TokenType type;
  std::string value;
};

class Symbole
{
public:
  std::string m_nom;
  std::string m_valeur;
  NoeudType m_type;
  int position;
  Symbole(std::string nom, std::string valeur) : m_nom(nom), m_valeur(valeur) {}
  Symbole(std::string nom) : m_nom(nom) {}
  Symbole() {}
};

std::vector<Symbole> Variables;

class Noeud
{
public:
  NoeudType m_type;
  Symbole m_symbole;
  std::string m_valeur;
  std::vector<Noeud> m_sousNoeud;
  // Noeud(Symbole symbole) : m_symbole(symbole) {}
  Noeud(NoeudType type, std::string valeur, std::vector<Noeud> sousNoeud) : m_type(type), m_valeur(valeur), m_sousNoeud(sousNoeud) {}
  Noeud(NoeudType type) : m_type(type) {}
  Noeud(NoeudType type, std::string valeur) : m_type(type), m_valeur(valeur) {}
  Noeud(NoeudType type, std::vector<Noeud> sousNoeud) : m_type(type), m_sousNoeud(sousNoeud) {}
  Noeud() {}

  void ajouterEnfant(Noeud N){
    this->m_sousNoeud.push_back(N);
  }
};

Noeud A();
Noeud E();
Noeud P();

Token tokenCurrent;
Token tokenLast;

std::string line;
int nbToken;

// Fonction d'affichage des tokens
void printAnaLex()
{
  if (tokenLast.type == K)
  {
    std::cout << tokenLast.value << " : constante" << std::endl;
  }
  else if (tokenLast.type == I)
  {
    std::cout << tokenLast.value << " : identificateur" << std::endl;
  }
  else if (tokenLast.type == SPlus)
  {
    std::cout << tokenLast.value << " : Signe plus" << std::endl;
  }
  else if (tokenLast.type == SMoins)
  {
    std::cout << tokenLast.value << " : Signe moins" << std::endl;
  }
  else if (tokenLast.type == SMult)
  {
    std::cout << tokenLast.value << " : Signe mult" << std::endl;
  }
  else if (tokenLast.type == SDiv)
  {
    std::cout << tokenLast.value << " : Signe div" << std::endl;
  }
  else if (tokenLast.type == ParaO)
  {
    std::cout << tokenLast.value << " : Signe (" << std::endl;
  }
  else if (tokenLast.type == ParaF)
  {
    std::cout << tokenLast.value << " : Signe )" << std::endl;
  }
  else if (tokenLast.type == Segal)
  {
    std::cout << tokenLast.value << " : Signe =" << std::endl;
  }
  else if (tokenLast.type == AccO)
  {
    std::cout << tokenLast.value << " : Signe {" << std::endl;
  }
  else if (tokenLast.type == AccF)
  {
    std::cout << tokenLast.value << " : Signe }" << std::endl;
  }
  else if (tokenLast.type == virgule)
  {
    std::cout << tokenLast.value << " : Signe virgule" << std::endl;
  }
}

// Fonction de parcours de la chaîne de caractère
void next()
{
  // Décalage de current dans last et affichage des tokens avec printAnaLex()
  tokenLast.type = tokenCurrent.type;
  tokenLast.value = tokenCurrent.value;
  printAnaLex();

  // On vérifie si le caractère actuel est un espace, si oui on le supprime
  while (std::isspace(line[0]) && line.size() > 0)
  {
    line.erase(0, 1);
  }

  // On vérifie si on est arrivé à la fin de la ligne
  if ((line.size() == 0))
  {
    tokenCurrent.type = EOF_;
  }

  // Le caractère courant est un identificateur
  if (std::isalpha(line[0]) && line.size() > 0)
  {
    tokenCurrent.type = I;
    tokenCurrent.value = line[0];
    line.erase(0, 1);

    // Les caractères qui suivent sont aussi des identificateurs
    while (std::isalpha(line[0]) && line.size() > 0)
    {
      tokenCurrent.value += (line[0]);
      line.erase(0, 1);
    }
    if(tokenCurrent.value.compare(DEBUG) == 0){
      tokenCurrent.type = debug;
    }
  }

  else if (line[0] == POINT_VIRGULE && line.size() > 0)
  {
    tokenCurrent.type = Pvirgule;
    tokenCurrent.value = line[0];
    line.erase(0, 1);
  }

  else if (line[0] == VIRGULE && line.size() > 0)
  {
    tokenCurrent.type = virgule;
    tokenCurrent.value = line[0];
    line.erase(0, 1);
  }

  // Le caractère courant est signe +
  else if (line[0] == SIGNE_PLUS && line.size() > 0)
  {
    tokenCurrent.type = SPlus;
    tokenCurrent.value = line[0];
    line.erase(0, 1);
  }

  // Le caractère courant est signe -
  else if (line[0] == SIGNE_MOINS && line.size() > 0)
  {
    tokenCurrent.type = SMoins;
    tokenCurrent.value = line[0];
    line.erase(0, 1);
  }

  // Le caractère courant est signe *
  else if (line[0] == SIGNE_MULT && line.size() > 0)
  {
    tokenCurrent.type = SMult;
    tokenCurrent.value = line[0];
    line.erase(0, 1);
  }

  // Le caractère courant est signe /
  else if (line[0] == SIGNE_DIV && line.size() > 0)
  {
    tokenCurrent.type = SDiv;
    tokenCurrent.value = line[0];
    line.erase(0, 1);
  }

  // Le caractère courant est signe (
  else if (line[0] == PARA_OUV && line.size() > 0)
  {
    tokenCurrent.type = ParaO;
    tokenCurrent.value = line[0];
    line.erase(0, 1);
  }

  // Le caractère courant est signe )
  else if (line[0] == PARA_FERM && line.size() > 0)
  {
    tokenCurrent.type = ParaF;
    tokenCurrent.value = line[0];
    line.erase(0, 1);
  }

  // Le caractère courant est signe {
  else if (line[0] == ACC_OUV && line.size() > 0)
  {
    tokenCurrent.type = AccO;
    tokenCurrent.value = line[0];
    line.erase(0, 1);
  }

  // Le caratère courant est signe }
  else if (line[0] == ACC_FERM && line.size() > 0)
  {
    tokenCurrent.type = AccF;
    tokenCurrent.value = line[0];
    line.erase(0, 1);
  }

  // Le caractère courant est une constante
  else if (isdigit(line[0]) && line.size() > 0)
  {
    tokenCurrent.type = K;
    tokenCurrent.value = line[0];
    line.erase(0, 1);

    // Les caractères qui suivent sont aussi des constantes
    while (isdigit(line[0]) && line.size() > 0)
    {
      tokenCurrent.value += (line[0]);
      line.erase(0, 1);
    }
  }
}

bool check(TokenType type)
{
  if (tokenCurrent.type == type)
  {
    next();
    return true;
  }
  return false;
}

void accept(TokenType T)
{
  if (!check(T))
  {
    std::cout << "ERREUR FATALE" << std::endl;
    exit(1);
  }
}

Noeud A(){
  if (check(K))
  {
    return Noeud(noeudK, tokenLast.value);
  }
  else if (check(I))
  {
    std::cout << "ERREUR FATALE" << std::endl;
    exit(0);
  }
  else if (check(ParaO)){
    E();
    accept(ParaF);
    return Noeud(noeudParaO);
  }
}

Noeud P() {
  if (check(SMoins))
  {
    Noeud N = P();
    std::vector<Noeud> v;
    v.push_back(N);
    return Noeud(noeudSMoinsUnaire, v);
  } // TODO else if(check(pointExclam))
  else if (check(SPlus))
  {
    Noeud N = P();
    std::vector<Noeud> v;
    v.push_back(N);
    return Noeud(noeudSPlusUnaire, v);
  }
  else
  {
    Noeud N = A();
    return N;
  }
}

Noeud E() {
  return P();
}



Noeud I_() {
  if (check(Pvirgule)){
    return Noeud(noeudVide);
  }
  else if (check(AccO)) {
    Noeud N = Noeud(noeudBlock); 
    while (!check(AccF)){
      N.m_sousNoeud.push_back(I_());
    }
    return N;
  } 
  else if (check(debug)) {  
    Noeud N = E();
    accept(Pvirgule);
    std::vector<Noeud> v;
    v.push_back(N);
    return Noeud(noeudDebug, v);
  } 
  else if (check(I)) {
    return Noeud(noeudRef, tokenLast.value);
  } 
  else if (check(token_int)) {
    Noeud N = Noeud(noeudSeq);
    do {
      accept(I);
      N.ajouterEnfant(Noeud(noeudDecl, tokenLast.value));
    } while (check(virgule));
    accept(Pvirgule);
    return N;
  } else {
    Noeud N = E();
    std::vector<Noeud> v;
    v.push_back(N);
    accept(Pvirgule);
    return Noeud(noeudDrop, v);
  }
}

Noeud AnalSyn() {
  return I_();
}

Symbole declarer  (std::string nom){
  for (int i = Variables.size() - 1; i >= 0; i--){
    if(Variables[i].m_nom.compare(nom) == 0) {
      std::cout << "ERREUR FATALE" << std::endl;
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
  std::cout << "ERREUR FATALE" << std::endl;
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
      printf("push", N.m_valeur);
      break;
    // case noeudSMoins :
    //   GenCode(N.m_sousNoeud[0]);
    //   GenCode(N.m_sousNoeud[1]);
    //   printf("sub \n");
    //   break;
    // case noeudSPlus:
    //   GenCode(N.m_sousNoeud[0]);
    //   GenCode(N.m_sousNoeud[1]);
    //   printf("add \n");
    //   break;
  }
}

int main() {
  line = "123 (465)";
  next();
  while (tokenCurrent.type != EOF_){
    GenCode(AnalSyn()); // TODO: Ajouter analyse sémantique
  }
  return 0;
}
