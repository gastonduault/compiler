
Noeud AnalSyntaxique() {
    Noeud n;
    //int main()
    accept(token_int);
    accept(tokenI);
    n = Noeud(noeudFonction, tokenLast.value);
    accept(tokenParaO);

    while(check(token_int)) {
        accept(tokenI);
        n.ajouterEnfant(Noeud(noeudDecl, tokenLast.value));
        if(check(tokenvirgule)){
            continue;
        }else{
            break;
        }
    }
    accept(tokenParaF);
    n.ajouterEnfant(Instruction());
    return n;
}

Noeud Atome(){
    if (check(tokenK))  {
        Noeud n =  Noeud(noeudK, tokenLast.value);
        return n;
    }
    else if (check(tokenI)) {
        Noeud n = Noeud(noeudRef, tokenLast.value);
        return n;
    }
    else if (check(tokenParaO)){
        Noeud n = Expression(0);
        if(accept(tokenParaF)) {
          return n;
        }
        return n;
    }
    else {
        std::cout <<"ERREUR FATALE | Atome() " << tokenCurrent.value << std::endl;
        exit(1);
    }
}

Noeud Prefixe() {
    if (check(tokenMoins)){
        Noeud p = Prefixe();
        std::vector<Noeud> v;
        v.push_back(p);
        Noeud n =  Noeud(noeudMoinsUnaire, v);
        return n;
    }
    else if (check(tokenSlash)) {
      Noeud p = Prefixe();
      std::vector<Noeud> v;
      v.push_back(p);
      Noeud n = Noeud(noeudDiv, v);
      return n;
    }
    else if (check(tokenEtoile)) {
      Noeud p = Prefixe();
      std::vector<Noeud> v;
      v.push_back(p);
      Noeud n = Noeud(noeudMult, v);
      return n;
    }
    // TODO: else if(check(&))
    //TODO: else if(check(*))
    else if (check(tokenNOT)) {
      Noeud p = Prefixe();
      std::vector<Noeud> v;
      v.push_back(p);
      Noeud n = Noeud(noeudNot, v);
      return n;
    }
    else if (check(tokenPlus))
    {
        return Prefixe();
    }
    else {
        return Suffixe();
    }
}

Noeud Suffixe() {
    Noeud n = Atome();
    if(check(tokenParaO)) {
        Noeud n_ = Noeud(noeudAppel);
        n_.ajouterEnfant(n);
        while(!check(tokenParaF)) {
            n_.ajouterEnfant(Expression(0));
            if(check(tokenParaF)) {
                break;
            }
            check(tokenvirgule);
        }
    }
    return n;
}

bool operateursContient(TokenType type){
    for(Operateur operateur : listeOperateurs) {
        if(operateur.m_cle == type) {
            return true;
        }
    }
    return false;
}

Operateur operateurListe(TokenType type) {
    for(Operateur operateur: listeOperateurs) {
      if (operateur.m_cle == type) {
        return operateur;
      }
    }
}

void printNoeud(NoeudType T) {
  if (T == noeudK)
  {
    std::cout << tokenLast.value << " : constante" << std::endl;
  }
  else if (T == noeudI)
  {
    std::cout << tokenLast.value << " : identificateur" << std::endl;
  }
  else if (T == noeudAddition ) {
    std::cout << " : Addition" << std::endl;
  }
  else if (T == noeudSoustraction)
  {
    std::cout << " : Signe moins" << std::endl;
  }
  else if (T == noeudParaO)
  {
    std::cout << " : Signe (" << std::endl;
  }
  else if (T == noeudParaF)
  {
    std::cout << " : Signe )" << std::endl;
  }
  else if (T == noeudEgal)
  {
    std::cout << " : Signe =" << std::endl;
  }
  else if (T ==  noeudAccO)
  {
    std::cout << " : Signe {";
  }
  else if (T == noeudAccF)
  {
    std::cout << " : Signe }" << std::endl;
  }
  else if(T == noeudAffect) {
    std::cout << " : Noeud affect" << std::endl;
  }
  else{
    std::cout << "  Pas trouvé" << std::endl;
  }
}


Noeud Expression(int minPriorite) {
    Noeud n = Prefixe();
    while(operateursContient(tokenCurrent.type)){
        Operateur o = operateurListe(tokenCurrent.type);
//        printNoeud(o.m_token);
//        for (Operateur operateur : listeOperateurs){
//            if (operateur.m_cle == tokenCurrent.type){
//                o = operateur;
//            }
//        }
        if(o.m_priorite > minPriorite){
            next();
            Noeud n2 = Expression(o.m_priorite - o.m_assoDroite);
            std::vector<Noeud> v;
            v.push_back(n);
            v.push_back(n2);
            n = Noeud(o.m_token, v);
        }
        else {
            break;
        }
    }
    return n;
}


Noeud Instruction() {
    if (check(tokenPvirgule)){
        return Noeud(noeudVide);
    }
    else if (check(tokenAccO)) {
        Noeud N = Noeud(noeudBlock);
        while (!check(tokenAccF)){
            N.ajouterEnfant(Instruction());
        }
        return N;
    }
    else if (check(tokendebug)) {
        Noeud N = Expression(0);
        accept(tokenPvirgule);
        Noeud n = Noeud(noeudDebug);
        n.ajouterEnfant(N);
        return n;
    }
    else if (check(tokenReturn)) {
      Noeud N = Expression(0);
      accept(tokenPvirgule);
      std::vector<Noeud> v;
      v.push_back(N);
      return Noeud(noeudReturn, v);
    }
    else if (check(tokenIf)) {
      accept(tokenParaO);
      Noeud E = Expression(0);
      accept(tokenParaF);
      Noeud n1 = Instruction();
      std::vector<Noeud> v;
      v.push_back(E);
      v.push_back(n1);
      Noeud n = Noeud(noeudCondition, v);
      if(check(tokenElse)) {
        Noeud n2 = Instruction();
        n.ajouterEnfant(n2);
      }
      return n;
    }
    else if (check(token_int)) {
        Noeud N = Noeud(noeudSeq);
        do {
            accept(tokenI);
            N.ajouterEnfant(Noeud(noeudDecl, tokenLast.value));
        } while (check(tokenvirgule));
        accept(tokenPvirgule);
        return N;
    }
    else if(check(tokenWhile)){
      accept(tokenParaO);
      Noeud expr = Expression(0);
      accept(tokenParaF);
      Noeud boucle = Noeud(noeudLoop);
      Noeud instr = Instruction();
      Noeud cible = Noeud(noeudCible);
      Noeud cond = Noeud(noeudCondition);
      Noeud break_ = Noeud(noeudBreak);
      cond.ajouterEnfant(expr);
      cond.ajouterEnfant(instr);
      cond.ajouterEnfant(break_);
      boucle.ajouterEnfant(cible);
      boucle.ajouterEnfant(cond);
      return boucle;
    }
//    else if (check(tokenvirgule)) {
//        N = Noeud(noeudSeq);
//        do { // int a,b;
//            accept(tokenI);
//            N.ajouterEnfant(Noeud(noeudDecl, tokenLast.value));
//        } while (check(tokenvirgule));
//
//        accept(tokenPvirgule);
//        return N;
//    }
    else if (check(tokenFor)) {
      accept(tokenParaO);
      Noeud E1 = Expression(0);
      accept(tokenPvirgule);
      Noeud E2 = Expression(0);
      accept(tokenPvirgule);
      Noeud E3 = Expression(0);
      accept(tokenParaF);
      Noeud instr = Instruction();
      Noeud loop = Noeud(noeudLoop);
      Noeud cible = Noeud(noeudCible);
      Noeud seq1 = Noeud(noeudSeq);
      Noeud seq2 = Noeud(noeudSeq);
      Noeud drop1 = Noeud(noeudDrop);
      Noeud drop2 = Noeud(noeudDrop);
      Noeud break_ = Noeud(noeudBreak);
      Noeud condition = Noeud(noeudCondition);

      drop1.ajouterEnfant(E3);
      seq1.ajouterEnfant(instr);
      seq1.ajouterEnfant(cible);
      seq1.ajouterEnfant(drop1);

      condition.ajouterEnfant(E2);
      condition.ajouterEnfant(seq1);
      condition.ajouterEnfant(break_);

      loop.ajouterEnfant(condition);
      drop2.ajouterEnfant(E1);
      seq2.ajouterEnfant(drop2);
      seq2.ajouterEnfant(loop);

      return seq2;
    }
    //TODO: BREAK
    //TODO: CONTINUE
    else {
        Noeud N = Expression(0);
        accept(tokenPvirgule);
        std::vector<Noeud> v;
        v.push_back(N);
        return Noeud(noeudDrop, v);
    }
}
