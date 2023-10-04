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
