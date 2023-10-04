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

Noeud Atome(); //Atome
Noeud Expression(int minPriorite); //Expression
Noeud Prefixe(); //Préfixe
Noeud Suffixe(); //Suffixe
Noeud Instruction();
