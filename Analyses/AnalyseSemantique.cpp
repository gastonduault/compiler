int nbVar = 0;


Symbole declarer  (std::string nom){
  for (int i = Variables.size() - 1; i >= 0; i--){
    if(Variables[i].m_nom.compare(nom) == 0) {
      std::cout << "ERREUR FATALE | declarer()" << std::endl;
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
  std::cout << "ERREUR FATALE | chercher()" << std::endl;
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

void AnalyseSementique(Noeud N){
  Symbole S;
  switch (N.m_type)
  {
    default:
      for (int i = 0; i < N.m_sousNoeud.size(); i++)
      {
          AnalyseSementique(N.m_sousNoeud[i]);
      }
      break;// TODO: noeud fonction
    case noeudBlock:
      begin();
      for (int i = 0; i < N.m_sousNoeud.size(); i++)
      {
        AnalyseSementique(N.m_sousNoeud[i]);
      }
      end();
      break;
    case noeudDecl:
      S = declarer(N.m_valeur);
      S.position = nbVar;
      nbVar++;
      S.m_type = variableLocal;
      break;
    case noeudRef:
      S = chercher(N.m_valeur);
      N.m_symbole = S;
      break;
    case noeudFonction:
      nbVar = 0;
      Symbole s1 = declarer(N.m_valeur);
      begin();
//      for(Noeud noeud: N.m_sousNoeud) {
//        AnalyseSementique(noeud);
//      }
      for(int i = 0; i < N.m_sousNoeud.size(); i++) {
        AnalyseSementique(N.m_sousNoeud[i]);
      }
      end();
      s1.m_type = fonction;
      s1.nbVars = nbVar - (N.m_sousNoeud.size() - 1);
      N.m_symbole = s1;
      break;
  }
}
