#include <iostream>
#include <string>


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
    token_if,
    token_else,
    tokendebug, //TODO: token ==
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
