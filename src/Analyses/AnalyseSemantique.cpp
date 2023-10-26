int nbVar = 0;
std::vector<Symbole> Variables;

Symbole declarer  (std::string nom, SymboleTypes type, int nbVar){
  for (int i = Variables.size() - 1; i >= 0; i--){
    if(Variables[i].m_nom.compare(nom) == 0) {
      exit(1);
    }if(Variables[i].m_nom.compare("") == 0) {
      break;
    }
  }
  Symbole S = Symbole(nom, type, nbVar);
  Variables.push_back(S);
  return S;
}

Symbole chercher(std::string nom) {
  for (int i = Variables.size() - 1; i >= 0; i--){
    if(Variables[i].m_nom.compare(nom) == 0){
      return Variables[i];
    }
  }
  std::cout << "ERREUR FATALE | chercher() : "<< nom << std::endl;
  exit(1);
}

int chercherIndice(std::string nom) {
  for (int i = Variables.size() - 1; i >= 0; i--){
    if(Variables[i].m_nom.compare(nom) == 0){
      return i;
    }
  }
  std::cout << "ERREUR FATALE | chercher indice()" << std::endl;
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

//void end() {
//  while(Variables[Variables.size() - 1].m_nom != "") {
//    Variables.pop_back();
//  }
//}

void AnalyseSementique(Noeud &N){
    if(N.m_type == noeudBlock) {
      begin();
      for (Noeud noeud: N.m_sousNoeud) {
        AnalyseSementique(noeud);
      }
      end();
    }else if(N.m_type == noeudDecl) {
      Symbole S = declarer(N.m_valeur , variableLocal, nbVar);
      nbVar++;
      N.m_symbole = S;
    }else if (N.m_type == noeudRef) {
      Symbole S = chercher(N.m_valeur);
      N.m_symbole = S;
    } else if (N.m_type == noeudFonction) {
      nbVar = 0;
      Symbole s1 = declarer(N.m_valeur, fonction, 0);
      begin();
      for (int i = 0; i < N.m_sousNoeud.size(); i++) {
        AnalyseSementique(N.m_sousNoeud[i]);
      }
      end();
      Variables[chercherIndice(s1.m_nom)].nbVars = nbVar - (N.m_sousNoeud.size() - 1);
      N.m_symbole = Variables[chercherIndice(s1.m_nom)];
    }
    else {
      for (Noeud noeud: N.m_sousNoeud) {
        AnalyseSementique(noeud);
      }
    }
}