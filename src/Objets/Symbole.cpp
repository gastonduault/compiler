class Symbole
{
public:
    std::string m_nom;
    std::string m_valeur;
    SymboleTypes m_type;
    int position;
    int nbVars;

    Symbole(std::string nom, SymboleTypes type, int nbVar) : m_nom(nom), m_type(type), position(nbVar) {}
    Symbole(std::string nom, std::string valeur) : m_nom(nom), m_valeur(valeur) {}
    Symbole(std::string nom) : m_nom(nom) {}
    Symbole() {}
    
};
