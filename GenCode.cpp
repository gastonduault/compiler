int labelContinue;
int labelBreak;
int nombreLabel;

// TODO : Addition, soustraction, multiplication, division
// TODO: supperieur, inferieur, égalité
void GenCode(Noeud N) {

  switch (N.m_type){
    case noeudK :
      printf("noeudK \n");
      std::cout << "push " <<  N.m_valeur << std::endl;
      break;
    case noeudAddition :
      printf("noeudAddition \n");
      GenCode(N.m_sousNoeud[0]);
      GenCode(N.m_sousNoeud[1]);
      std::cout << "add " << std::endl;
      break;
    case noeudSoustraction :
      printf("noeudSoustraction \n");
      GenCode(N.m_sousNoeud[0]);
      GenCode(N.m_sousNoeud[1]);
      std::cout << "sub " << std::endl;
      break;
    case noeudBlock:
      printf("noeudBloc \n");
      for(Noeud noeud: N.m_sousNoeud){
        GenCode(noeud);
      }
      break;
    case noeudFonction:
      printf("noeudFonction \n");
      std::cout << "." << N.m_valeur << std::endl;
      std::cout << "resn " << N.m_symbole.nbVars << std::endl;
      GenCode(N.m_sousNoeud[N.m_sousNoeud.size() - 1]);
      std::cout << "push 0" << std::endl;
      std::cout << "ret" << std::endl;
      printf("fin noeud fonction \n");
      break;
    case noeudVide:
      printf("noeudVide \n");
      break;
    //TODO: Erreur avec debug
    case noeudDebug:
      printf("noeudDebug \n");
      GenCode(N.m_sousNoeud[0]);
      std::cout << "dbg" << std::endl;
      break;
    case noeudDrop:
      printf("noeudDrop \n");
      GenCode(N.m_sousNoeud[0]);
      std::cout << "drop 1" << std::endl;
      break;
    case noeudBlock || noeudSeq:
      printf("noeudBlock ou noeudSeq \n");
      for(Noeud noeud : N.m_sousNoeud){
        GenCode(noeud);
      }
      break;
    case noeudRef:
      printf("noeudRef \n");
      if(N.m_symbole.m_type == variableLocal) {
        std::cout << "get " << N.m_symbole.position << std::endl;
      }
      else{
        std::cout << "ERREUR FATALE | GenCode reference";
        exit(1);
      }
      break;
    case noeudAffect:
      //TODO: ERREUR ICI a comparer avec l'ordre d'exec de david
      printf("noeudAffect \n");

      GenCode(N.m_sousNoeud[1]);
      std::cout << "dup" << std::endl;

      if(N.m_sousNoeud[0].m_type == noeudRef && N.m_sousNoeud[0].m_symbole.m_type == variableLocal){
        std::cout << "set" << N.m_sousNoeud[0].m_symbole.position << std::endl;
      }
      else if(N.m_sousNoeud[0].m_type == noeudIndirection) {
        GenCode(N.m_sousNoeud[0].m_sousNoeud[0]);
        std::cout << "write" << std::endl;
      }
      else{
        std::cout << "ERREUR FATALE | GenCode reference";
        exit(1);
      }
      break;
      //TODO: Noeud Drop
      //TODO: Noeud return



  }
}




