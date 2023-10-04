int labelContinue;
int labelBreak;
int nombreLabel;


void GenCode(Noeud N) {
  switch (N.m_type){
    case noeudK :
      std::cout << "push " <<  N.m_valeur << std::endl;
      break;
  }
}