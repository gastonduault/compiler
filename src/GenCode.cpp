int nombreLabel = 0;
int labelDebut = 0;
int labelContinu = 0;
int labelArret = 0;


void GenCode(Noeud &N) {
  if(N.m_type == noeudK || N.m_type == noeudI) {
      std::cout << "push " <<  N.m_valeur << std::endl;
  }
  else if (N.m_type == noeudAddition) {
    GenCode(N.m_sousNoeud[0]);
    GenCode(N.m_sousNoeud[1]);
    std::cout << "add " << std::endl;
  }
  else if(N.m_type == noeudSoustraction) {
    GenCode(N.m_sousNoeud[0]);
    GenCode(N.m_sousNoeud[1]);
    std::cout << "sub " << std::endl;
  }
  else if(N.m_type == noeudMult) {
    std::cout << "PAssage noeud mult " << std::endl;
    GenCode(N.m_sousNoeud[0]);
    GenCode(N.m_sousNoeud[1]);
    std::cout << "mult " << std::endl;
  }
  else if(N.m_type == noeudDiv) {
    GenCode(N.m_sousNoeud[0]);
    GenCode(N.m_sousNoeud[1]);
    std::cout << "div " << std::endl;
  }
  else if (N.m_type == noeudNot) {
    GenCode(N.m_sousNoeud[0]);
    std::cout << "not" << std::endl;
  }
  else if(N.m_type == noeudET) {
    GenCode(N.m_sousNoeud[0]);
    GenCode(N.m_sousNoeud[1]);
    std::cout << "and " << std::endl;
  }
  else if(N.m_type == noeudOU) {
    GenCode(N.m_sousNoeud[0]);
    GenCode(N.m_sousNoeud[1]);
    std::cout << "or " << std::endl;
  }
  else if(N.m_type == noeudCondition) {
    int lb1, lb2;
    if(N.m_sousNoeud.size() == 2) {
      lb1 = nombreLabel++;
      GenCode(N.m_sousNoeud[0]);
      std::cout << "jumpf l" << lb1 << std::endl;
      GenCode(N.m_sousNoeud[1]);
      std::cout << ".l" << lb1 << std::endl;
    }
    else {
      lb1 = nombreLabel++;
      lb2 = nombreLabel++;
      GenCode(N.m_sousNoeud[0]);
      std::cout << "jumpf l" << lb1 << std::endl;
      GenCode(N.m_sousNoeud[1]);
      std::cout << "jump l" << lb2 << std::endl;
      std::cout << ".l" << lb1 << std::endl;
      GenCode(N.m_sousNoeud[2]);
      std::cout << ".l" << lb2 << std::endl;
    }
  }
  else if(N.m_type == noeudDoubleEgale) {
    GenCode(N.m_sousNoeud[0]);
    GenCode(N.m_sousNoeud[1]);
    std::cout << "cmpeq " << std::endl;
  }
  else if(N.m_type == noeudDifferent) {
    GenCode(N.m_sousNoeud[0]);
    GenCode(N.m_sousNoeud[1]);
    std::cout << "cmpne " << std::endl;
  }
  else if(N.m_type == noeudSup) {
    GenCode(N.m_sousNoeud[0]);
    GenCode(N.m_sousNoeud[1]);
    std::cout << "cmpgt " << std::endl;
  }
  else if(N.m_type == noeudSupEgale) {
    GenCode(N.m_sousNoeud[0]);
    GenCode(N.m_sousNoeud[1]);
    std::cout << "cmpge " << std::endl;
  }
  else if(N.m_type == noeudInf) {
    GenCode(N.m_sousNoeud[0]);
    GenCode(N.m_sousNoeud[1]);
    std::cout << "cmplt " << std::endl;
  }
  else if(N.m_type == noeudInfEgale) {
    GenCode(N.m_sousNoeud[0]);
    GenCode(N.m_sousNoeud[1]);
    std::cout << "cmple " << std::endl;
  }
  else if(N.m_type ==  noeudVide) {
  }
  else if (N.m_type == noeudBlock || N.m_type == noeudSeq) {
    for (Noeud noeud: N.m_sousNoeud) {
      GenCode(noeud);
    }
  }
  else if(N.m_type  == noeudDebug) {
    GenCode(N.m_sousNoeud[0]);
    std::cout << "dbg" << std::endl;
  }
  else if (N.m_type == noeudDrop) {
    GenCode(N.m_sousNoeud[0]);
    std::cout << "drop 1" << std::endl;
  }
  else if (N.m_type == noeudDecl ) {
    return;
  }
  else if (N.m_type == noeudBlock || N.m_type == noeudSeq) {
    for (Noeud noeud: N.m_sousNoeud) {
      GenCode(noeud);
    }
  }
  else if(N.m_type == noeudRef) {
    if (N.m_symbole.m_type == variableLocal) {
      std::cout << "get " << N.m_symbole.position << std::endl;
    } else {
      std::cout << "ERREUR FATALE | GenCode reference";
      exit(1);
    }
  }
  else if (N.m_type == noeudAffect) {
    GenCode(N.m_sousNoeud[1]);
    std::cout << "dup" << std::endl;

    if (N.m_sousNoeud[0].m_type == noeudRef && N.m_sousNoeud[0].m_symbole.m_type == variableLocal) {
      std::cout << "set " << N.m_sousNoeud[0].m_symbole.position << std::endl;
    }
    else {
      std::cout << "ERREUR FATALE | GenCode Affectœ";
      exit(1);
    }
  }
  else if(N.m_type == noeudFonction) {
    std::cout << "." << N.m_valeur << std::endl;
    std::cout << "resn " << N.m_symbole.nbVars << std::endl;
    GenCode(N.m_sousNoeud[N.m_sousNoeud.size() - 1]);
    std::cout << "push 0" << std::endl;
    std::cout << "ret" << std::endl;
  }
  else if (N.m_type == noeudReturn) {
    GenCode(N.m_sousNoeud[0]);
    std::cout << "ret " << std::endl;
  }
  else if (N.m_type == noeudLoop) {
    int continu = labelContinu;
    int break_ = labelArret;
    labelDebut = nombreLabel++;
    labelContinu = nombreLabel++;
    labelArret = nombreLabel++;
    std::cout << ".l" << labelDebut << std::endl;
    for(Noeud noeud: N.m_sousNoeud) {
      GenCode(noeud);
    }
    std::cout << "jump l" << labelDebut << std::endl;
    std::cout << ".l" << labelArret << std::endl;
    labelContinu = continu;
    labelArret = break_;
  }
  else if (N.m_type == noeudCible) {
    std::cout << ".l" << labelContinu << std::endl;
  }
  else if(N.m_type == noeudAppel) {
    if(N.m_sousNoeud[0].m_type == noeudFonction) {
      std::cout << "ERREUR FATALE | GenCode > noeudAppel > noeudFonction" << std::endl;
      exit(1);
    }
    else if(N.m_sousNoeud[0].m_type == noeudRef) {
      std::cout << "ERREUR FATALE | GenCode > noeudAppel > noeudRef" << std::endl;
      exit(1);
    }else{
      std::cout << "prep " << N.m_sousNoeud[0].m_valeur << std::endl;
      for(int i = 1; i < N.m_sousNoeud.size() ; i++) {
        GenCode(N.m_sousNoeud[i]);
      }
      std::cout << "call " << N.m_sousNoeud.size() - 1 << std::endl;
    }
  }
  else if(N.m_type == noeudBreak) {
    std::cout << "jump l" << labelArret << std::endl;
  }
  else{
    printf("ERREUR GenCode");
    exit(1);
  }
}

void debutAssembleur() {
  std::cout << ".start" << std::endl;
  std::cout << "prep main" << std::endl;
  std::cout << "call 0" << std::endl;
  std::cout << "halt" << std::endl;
}
