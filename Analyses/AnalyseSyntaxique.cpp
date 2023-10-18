
Noeud AnalSyntaxique() {
    Noeud n;
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
    Noeud ins = Instruction();
    n.ajouterEnfant(ins);

    return n;
}

Noeud Atome(){
    Noeud n;
    if (check(tokenK))  {
        return Noeud(noeudK, tokenLast.value);
    }
    else if (check(tokenI)) {
        return Noeud(noeudRef, tokenLast.value);
    }
    else if (check(tokenParaO)){
        Noeud n = Expression(0);
        accept(tokenParaF);
        return n;
    }
    else {
        std::cout <<"ERREUR FATALE | Atome() " << tokenCurrent.value << std::endl;
        exit(1);
    }
}

Noeud Prefixe() {
    Noeud n;
    if (check(tokenMoins))
    {
        Noeud N = Prefixe();
        std::vector<Noeud> v;
        v.push_back(N);
        return Noeud(noeudMoinsUnaire, v);
    } // TODO: else if(check(pointExclam))
        // TODO: else if(check(esperluette))
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
        n.m_sousNoeud.push_back(n);
        while(!check(tokenParaF)) {
            n_.m_sousNoeud.push_back(Expression(0));
            if(check(tokenParaF)) {
                break;
            }
            check(tokenvirgule);
        }
        return n_;
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


Noeud Expression(int minPriorite) {
    Noeud n = Prefixe();
    while(operateursContient(tokenCurrent.type)){
        Operateur o;
        for (Operateur operateur : listeOperateurs){
            if (operateur.m_cle == tokenCurrent.type){
                o = operateur;
            }
        }
        if(o.m_priorite > minPriorite){
            next();
            Noeud n_ = Expression(o.m_priorite - o.m_assoDroite);
            n = Noeud(o.m_token);
            n.m_sousNoeud.push_back(n_);
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
            N.m_sousNoeud.push_back(Instruction());
        }
        return N;
    }
    else if (check(tokendebug)) {
        Noeud N = Expression(0);
        accept(tokenPvirgule);
        Noeud n = Noeud(noeudDebug);
        n.m_sousNoeud.push_back(N);
        return n;
    } //TODO: token_return
        // else if (check(I)) {
        //   return Noeud(noeudRef, tokenLast.value);
        // }
    else if (check(token_int)) {
        Noeud N = Noeud(noeudSeq);
        do {
            accept(tokenI);
            N.ajouterEnfant(Noeud(noeudDecl, tokenLast.value));
        } while (check(tokenvirgule));
        accept(tokenPvirgule);
        return N;
    }
    else if (check(tokenvirgule)) {
        Noeud N = Noeud(noeudSeq);
        do {
            accept(tokenI);
            N.ajouterEnfant(Noeud(noeudDecl, tokenLast.value));
        } while (check(tokenvirgule));
        accept(tokenPvirgule);
        return N;
    }
        //TODO: If
        //TODO: While
        //TODO: break_token
        //TODO: continue_token
    else {
        Noeud N = Expression(0);
        accept(tokenPvirgule);
        std::vector<Noeud> v;
        v.push_back(N);
        return Noeud(noeudDrop, v);
    }
}
