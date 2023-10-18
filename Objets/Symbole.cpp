class Symbole
{
public:
    std::string m_nom;
    std::string m_valeur;
    Types m_type;
    int position;
    int nbVars;
    Symbole(std::string nom, std::string valeur) : m_nom(nom), m_valeur(valeur) {nbVars = 0;}
    Symbole(std::string nom) : m_nom(nom) {nbVars = 0;}
    Symbole() {nbVars = 0;}
};

std::vector<Symbole> Variables;
