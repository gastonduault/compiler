#include <string>


// Type à repérer
enum TokenType
{
    tokenK,        // Constante       V
    tokenI,        // Identificateur  V
    tokenPlus,    // +              V
    tokenMoins,   // -              V
    tokenEtoile,    // *
    tokenSlash,    //
    tokenEgal,    // =
    tokenParaO,    // (
    tokenParaF,    // )
    tokenAccO,     // {
    tokenAccF,     // }
    tokenCrochO,
    tokenCrochF,
    tokenPvirgule, // ;
    tokenvirgule,  // ,
    tokenEOF_,
    token_int,
    token_if,
    token_else,
    tokenFor,
    tokenWhile,
    tokendebug,
    tokenDoubleEgale,
    tokenReturn,
    tokenIf,
    tokenElse,
    tokenOU,
    tokenET,
    tokenNOT,
    tokenInf,
    tokenInfEgal,
    tokenSup,
    tokenSupEgal,
    tokenDifferend,
};

enum NoeudType
{
    noeudK,
    noeudI,        // Identificateur
    noeudPlusUnaire,    // +
    noeudMoinsUnaire,   // -
    noeudAddition,
    noeudSoustraction, //TODO: modulo
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
    noeudAffect,
    noeudSeq, // I
    noeudDecl, // I
    noeudVide,
    noeudAppel,
    noeudFonction,
    noeudIndirection,
    noeudCondition,
    noeudLoop,
    noeudCible,
    noeudReturn,
    noeudOU,
    noeudET,
    noeudNot,
    noeudDifferent,
    noeudInf,
    noeudInfEgale,
    noeudSup,
    noeudSupEgale,
    noeudDoubleEgale,
    noeudBreak
};

enum SymboleTypes {
  fonction,
  variableLocal
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
