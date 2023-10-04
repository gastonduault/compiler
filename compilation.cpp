/* 
TODO
  - projet modulaire
  - check Noeud  I (Analyse Lexical) isKeyword(int)
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
  tokenK,        // Constante
  tokenI,        // Identificateur
  tokenPlus,    // +
  tokenMoins,   // -
  tokenDiv,     // /
  tokenMult,    // *
  tokenEgal,    // =
  tokenParaO,    // (
  tokenParaF,    // )
  tokenAccO,     // {
  tokenAccF,     // }
  tokenPvirgule, // ;
  tokenvirgule,  // ,
  tokenEOF_,
  token_int,
  tokendebug
};

enum NoeudType
{
  noeudK,
  noeudI,        // Identificateur
  noeudPlusUnaire,    // +
  noeudMoinsUnaire,   // -
  noeudAddition,
  noeudSoustraction,
  noeudDiv,     // /
  noeudMult,    // *
  noeudEgal,    // =
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
  noeudAppel,
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
const char POINT_tokenVIRGULE = ';';
const char tokenVIRGULE = ',';

const std::string tokenDEBUG = "dbg";

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


class Operateur
{
public:
  TokenType m_cle;
  NoeudType m_token;
  int m_priorite;
  int m_assoDroite;
  Operateur(TokenType cle, NoeudType token, int priorite, int assoDroite) : m_cle(cle), m_token(token), m_priorite(priorite), m_assoDroite(assoDroite) {}
  Operateur(){}
};

std::vector<Operateur> listeOperateurs;


Noeud A(); //Atome
Noeud E(int minPriorite); //Expression
Noeud P(); //Préfixe
Noeud S(); //Suffixe
Noeud I_();

Token tokenCurrent;
Token tokenLast;

std::string line;
int nbToken;

// Fonction d'affichage des tokens
void printAnaLex()
{
  if (tokenLast.type == tokenK)
  {
    std::cout << tokenLast.value << " : constante" << std::endl;
  }
  else if (tokenLast.type == tokenI)
  {
    std::cout << tokenLast.value << " : identificateur" << std::endl;
  }
  else if (tokenLast.type == tokenPlus)
  {
    std::cout << tokenLast.value << " : Signe plus" << std::endl;
  }
  else if (tokenLast.type == tokenMoins)
  {
    std::cout << tokenLast.value << " : Signe moins" << std::endl;
  }
  else if (tokenLast.type == tokenMult)
  {
    std::cout << tokenLast.value << " : Signe mult" << std::endl;
  }
  else if (tokenLast.type == tokenDiv)
  {
    std::cout << tokenLast.value << " : Signe div" << std::endl;
  }
  else if (tokenLast.type == tokenParaO)
  {
    std::cout << tokenLast.value << " : Signe (" << std::endl;
  }
  else if (tokenLast.type == tokenParaF)
  {
    std::cout << tokenLast.value << " : Signe )" << std::endl;
  }
  else if (tokenLast.type == tokenEgal)
  {
    std::cout << tokenLast.value << " : Signe =" << std::endl;
  }
  else if (tokenLast.type == tokenAccO)
  {
    std::cout << tokenLast.value << " : Signe {" << std::endl;
  }
  else if (tokenLast.type == tokenAccF)
  {
    std::cout << tokenLast.value << " : Signe }" << std::endl;
  }
  else if (tokenLast.type == tokenvirgule)
  {
    std::cout << tokenLast.value << " : Signe tokenvirgule" << std::endl;
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
    tokenCurrent.type = tokenEOF_;
  }

  // Le caractère courant est un identificateur
  if (std::isalpha(line[0]) && line.size() > 0)
  {
    tokenCurrent.type = tokenI;
    tokenCurrent.value = line[0];
    line.erase(0, 1);

    // Les caractères qui suivent sont aussi des identificateurs
    while (std::isalpha(line[0]) && line.size() > 0)
    {
      tokenCurrent.value += (line[0]);
      line.erase(0, 1);
    }
    if(tokenCurrent.value.compare(tokenDEBUG) == 0){
      tokenCurrent.type = tokendebug;
    }
  }

  else if (line[0] == POINT_tokenVIRGULE && line.size() > 0)
  {
    tokenCurrent.type = tokenPvirgule;
    tokenCurrent.value = line[0];
    line.erase(0, 1);
  }

  else if (line[0] == tokenVIRGULE && line.size() > 0)
  {
    tokenCurrent.type = tokenvirgule;
    tokenCurrent.value = line[0];
    line.erase(0, 1);
  }

  // Le caractère courant est signe +
  else if (line[0] == SIGNE_PLUS && line.size() > 0)
  {
    tokenCurrent.type = tokenPlus;
    tokenCurrent.value = line[0];
    line.erase(0, 1);
  }

  // Le caractère courant est signe -
  else if (line[0] == SIGNE_MOINS && line.size() > 0)
  {
    tokenCurrent.type = tokenMoins;
    tokenCurrent.value = line[0];
    line.erase(0, 1);
  }

  // Le caractère courant est signe *
  else if (line[0] == SIGNE_MULT && line.size() > 0)
  {
    tokenCurrent.type = tokenMult;
    tokenCurrent.value = line[0];
    line.erase(0, 1);
  }

  // Le caractère courant est signe /
  else if (line[0] == SIGNE_DIV && line.size() > 0)
  {
    tokenCurrent.type = tokenDiv;
    tokenCurrent.value = line[0];
    line.erase(0, 1);
  }

  // Le caractère courant est signe (
  else if (line[0] == PARA_OUV && line.size() > 0)
  {
    tokenCurrent.type = tokenParaO;
    tokenCurrent.value = line[0];
    line.erase(0, 1);
  }

  // Le caractère courant est signe )
  else if (line[0] == PARA_FERM && line.size() > 0)
  {
    tokenCurrent.type = tokenParaF;
    tokenCurrent.value = line[0];
    line.erase(0, 1);
  }

  // Le caractère courant est signe {
  else if (line[0] == ACC_OUV && line.size() > 0)
  {
    tokenCurrent.type = tokenAccO;
    tokenCurrent.value = line[0];
    line.erase(0, 1);
  }

  // Le caratère courant est signe }
  else if (line[0] == ACC_FERM && line.size() > 0)
  {
    tokenCurrent.type = tokenAccF;
    tokenCurrent.value = line[0];
    line.erase(0, 1);
  }

  // Le caractère courant est une constante
  else if (isdigit(line[0]) && line.size() > 0)
  {
    tokenCurrent.type = tokenK;
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
  Noeud n;
  if (check(tokenK))  {
    return Noeud(noeudK, tokenLast.value);
  }
  else if (check(tokenI)) {
    return Noeud(noeudRef, tokenLast.value);
  }
  else if (check(tokenParaO)){
    Noeud n = E(0);
    accept(tokenParaF);
    return n;
  }
  else {
    printf("ERREUR FATALE - %s\n", tokenCurrent.value);
    exit(1);
  }
}

Noeud P() {
  Noeud n;
  if (check(tokenMoins))
  {
    Noeud N = P();
    std::vector<Noeud> v;
    v.push_back(N);
    return Noeud(noeudMoinsUnaire, v);
  } // TODO: else if(check(pointExclam))
    // TODO: else if(check(esperluette))
  else if (check(tokenPlus))
  {
    return P();
  }
  else {
    return S();
  }
}

Noeud S() {
  Noeud n = A();
  if(check(tokenParaO)) {
    Noeud n_ = Noeud(noeudAppel);
    n.m_sousNoeud.push_back(n);
    while(!check(tokenParaF)) {
      n_.m_sousNoeud.push_back(E(0));
      if(check(tokenParaF)) {
        break;
      }
      check(tokenvirgule);
    }
    return n_;
  }
  return n;
}

bool operateursContient(TokenType type){
  for(Operateur operateur : listeOperateurs) {
    if(operateur.m_cle == type) {
      return true;
    }
  }
  return false;
}


Noeud E(int minPriorite) { 
  Noeud n = P();
  while(operateursContient(tokenCurrent.type)){
    Operateur o;
    for (Operateur operateur : listeOperateurs){
      if (operateur.m_cle == tokenCurrent.type){
        o = operateur;
      }
    }
    if(o.m_priorite > minPriorite){
      next();
      Noeud n_ = E(o.m_priorite - o.m_assoDroite);
      n = Noeud(o.m_token);
      n.m_sousNoeud.push_back(n_);
    }
    else {
      break;
    }
  }
  return n;
}


Noeud I_() {
  if (check(tokenPvirgule)){
    return Noeud(noeudVide);
  }
  else if (check(tokenAccO)) {
    Noeud N = Noeud(noeudBlock); 
    while (!check(tokenAccF)){
      N.m_sousNoeud.push_back(I_());
    }
    return N;
  } 
  else if (check(tokendebug)) {  
    Noeud N = E(0);
    accept(tokenPvirgule);
    Noeud n = Noeud(noeudDebug);
    n.m_sousNoeud.push_back(N);
    return n;
  } //TODO: token_return
  // else if (check(I)) {
  //   return Noeud(noeudRef, tokenLast.value);
  // } 
  else if (check(token_int)) {
    Noeud N = Noeud(noeudSeq);
    do {
      accept(tokenI);
      N.ajouterEnfant(Noeud(noeudDecl, tokenLast.value));
    } while (check(tokenvirgule));
    accept(tokenPvirgule);
    return N;
  }
  else if (check(tokenvirgule)) {
    Noeud N = Noeud(noeudSeq);
    do {
      accept(tokenI);
      N.ajouterEnfant(Noeud(noeudDecl, tokenLast.value));
    } while (check(tokenvirgule));
    accept(tokenPvirgule);
    return N;
  }
  //TODO: If
  //TODO: While
  //TODO: break_token
  //TODO: continue_token
  else {
    Noeud N = E(0);
    accept(tokenPvirgule);
    std::vector<Noeud> v;
    v.push_back(N);
    return Noeud(noeudDrop, v);
  }
}

void setListeOperateurs() {
  listeOperateurs.push_back(Operateur(tokenEgal, noeudEgal, 1, 1));
  listeOperateurs.push_back(Operateur(tokenPlus, noeudAddition, 6, 0));
  listeOperateurs.push_back(Operateur(tokenMoins, noeudSoustraction, 6, 0));
  listeOperateurs.push_back(Operateur(tokenMult, noeudMult, 7, 0));
  listeOperateurs.push_back(Operateur(tokenDiv, noeudDiv, 7, 0));
  // modulo %
  // ||
  // &&
  // <
  // >
  // ==
}

Noeud AnalSyn() {
  setListeOperateurs();
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
  line = "123 (465) 123";
  next();
  while (tokenCurrent.type != tokenEOF_){
    GenCode(AnalSyn()); // TODO: Ajouter analyse sémantique
  }
  return 0;
}
