std::string code;


void printAnaLex()
{
    if (tokenLast.type == tokenK)
    {
        std::cout << tokenLast.value << " : constante" << std::endl;
    }
    else if (tokenLast.type == tokenI)
    {
        std::cout << tokenLast.value << " : identificateur" << std::endl;
    }
    else if (tokenLast.type == tokenPlus)
    {
        std::cout << tokenLast.value << " : Signe plus" << std::endl;
    }
    else if (tokenLast.type == tokenMoins)
    {
        std::cout << tokenLast.value << " : Signe moins" << std::endl;
    }
    else if (tokenLast.type == tokenMult)
    {
        std::cout << tokenLast.value << " : Signe mult" << std::endl;
    }
    else if (tokenLast.type == tokenDiv)
    {
        std::cout << tokenLast.value << " : Signe div" << std::endl;
    }
    else if (tokenLast.type == tokenParaO)
    {
        std::cout << tokenLast.value << " : Signe (" << std::endl;
    }
    else if (tokenLast.type == tokenParaF)
    {
        std::cout << tokenLast.value << " : Signe )" << std::endl;
    }
    else if (tokenLast.type == tokenEgal)
    {
        std::cout << tokenLast.value << " : Signe =" << std::endl;
    }
    else if (tokenLast.type == tokenAccO)
    {
        std::cout << tokenLast.value << " : Signe {" << std::endl;
    }
    else if (tokenLast.type == tokenAccF)
    {
        std::cout << tokenLast.value << " : Signe }" << std::endl;
    }
    else if (tokenLast.type == tokenvirgule)
    {
        std::cout << tokenLast.value << " : Signe tokenvirgule" << std::endl;
    }
}

bool mot(std::string m) {
    int i = 0;
    while(m[i] == code[i] && i<=m.size() && i<=code.size()){
        i++;
    }
    return i == m.size();
}

void lecture() {
    while (std::isspace(code[0]) && code.size() > 0)
    {
        code.erase(0, 1);
    }

    if ((code.size() == 0))
    {
        tokenCurrent.type = tokenEOF_;
    }

    if(mot("if")) {
        tokenCurrent.value = "if";
        tokenCurrent.type = token_if;
        code.erase(0,2);
    }

    else if(mot("int")) {
        tokenCurrent.value = "int";
        tokenCurrent.type = token_int;
        code.erase(0,3);
    }

    else if(mot("else")) {
        tokenCurrent.value = "else";
        tokenCurrent.type = token_else;
        code.erase(0, 4);
    }

    else if(mot("=")) {
      tokenCurrent.value = "=";
      tokenCurrent.type = tokenEgal;
      code.erase(0,1);
    }

    else if (std::isalpha(code[0]) && code.size() > 0)
    {
        tokenCurrent.type = tokenI;
        tokenCurrent.value = code[0];
        code.erase(0, 1);

        // Les caractères qui suivent sont aussi des identificateurs
        while (std::isalpha(code[0]) && code.size() > 0)
        {
            tokenCurrent.value += (code[0]);
            code.erase(0, 1);
        }
        if(tokenCurrent.value.compare(tokenDEBUG) == 0){
            std::cout << "debug";
            tokenCurrent.type = tokendebug;
        }
    }

    else if (code[0] == POINT_tokenVIRGULE && code.size() > 0)
    {
        tokenCurrent.type = tokenPvirgule;
        tokenCurrent.value = code[0];
        code.erase(0, 1);
    }

    else if (code[0] == tokenVIRGULE && code.size() > 0)
    {
        tokenCurrent.type = tokenvirgule;
        tokenCurrent.value = code[0];
        code.erase(0, 1);
    }

        // Le caractère courant est signe +
    else if (code[0] == SIGNE_PLUS && code.size() > 0)
    {
        tokenCurrent.type = tokenPlus;
        tokenCurrent.value = code[0];
        code.erase(0, 1);
    }

        // Le caractère courant est signe -
    else if (code[0] == SIGNE_MOINS && code.size() > 0)
    {
        tokenCurrent.type = tokenMoins;
        tokenCurrent.value = code[0];
        code.erase(0, 1);
    }

        // Le caractère courant est signe *
    else if (code[0] == SIGNE_MULT && code.size() > 0)
    {
        tokenCurrent.type = tokenMult;
        tokenCurrent.value = code[0];
        code.erase(0, 1);
    }

        // Le caractère courant est signe /
    else if (code[0] == SIGNE_DIV && code.size() > 0)
    {
        tokenCurrent.type = tokenDiv;
        tokenCurrent.value = code[0];
        code.erase(0, 1);
    }

        // Le caractère courant est signe (
    else if (code[0] == PARA_OUV && code.size() > 0)
    {
        tokenCurrent.type = tokenParaO;
        tokenCurrent.value = code[0];
        code.erase(0, 1);
    }

        // Le caractère courant est signe )
    else if (code[0] == PARA_FERM && code.size() > 0)
    {
        tokenCurrent.type = tokenParaF;
        tokenCurrent.value = code[0];
        code.erase(0, 1);
    }

        // Le caractère courant est signe {
    else if (code[0] == ACC_OUV && code.size() > 0)
    {
        tokenCurrent.type = tokenAccO;
        tokenCurrent.value = code[0];
        code.erase(0, 1);
    }

        // Le caratère courant est signe }
    else if (code[0] == ACC_FERM && code.size() > 0)
    {
        tokenCurrent.type = tokenAccF;
        tokenCurrent.value = code[0];
        code.erase(0, 1);
    }

        // Le caractère courant est une constante
    else if (isdigit(code[0]) && code.size() > 0)
    {
        tokenCurrent.type = tokenK;
        tokenCurrent.value = code[0];
        code.erase(0, 1);

        // Les caractères qui suivent sont aussi des constantes
        while (isdigit(code[0]) && code.size() > 0)
        {
            tokenCurrent.value += (code[0]);
            code.erase(0, 1);
        }
    }
}

void next()
{
    tokenLast.type = tokenCurrent.type;
    tokenLast.value = tokenCurrent.value;
    lecture();
}

bool check(TokenType type)
{
    if (tokenCurrent.type == type)
    {
        next();
        return true;
    }
    return false;
}

void accept(TokenType T)
{
    if (!check(T))
    {
      std::cout << "ERREUR FATALE | accept() " << T  << std::endl;
      if (T == tokenK)
      {
        std::cout << tokenLast.value << " : constante" << std::endl;
      }
      else if (T == tokenI)
      {
        std::cout << tokenLast.value << " : identificateur" << std::endl;
      }
      else if (T == tokenPlus ) {
        std::cout << " : Signe plus" << std::endl;
      }
      else if (T == tokenMoins)
      {
        std::cout << " : Signe moins" << std::endl;
      }
      else if (T == tokenMult)
      {
        std::cout << " : Signe mult" << std::endl;
      }
      else if (T == tokenDiv)
      {
        std::cout << " : Signe div" << std::endl;
      }
      else if (T == tokenParaO)
      {
        std::cout << " : Signe (" << std::endl;
      }
      else if (T == tokenParaF)
      {
        std::cout << " : Signe )" << std::endl;
      }
      else if (T == tokenEgal)
      {
        std::cout << " : Signe =" << std::endl;
      }
      else if (T == tokenAccO)
      {
        std::cout << " : Signe {";
      }
      else if (T == tokenAccF)
      {
        std::cout << " : Signe }" << std::endl;
      }
      else if (T == tokenvirgule)
      {
        std::cout << " : Signe tokenvirgule" << std::endl;
      }
      else if (T == tokenPvirgule)
      {
        std::cout << " : Signe tokenPvirgule" << std::endl;
      }
      else{
        std::cout << " : Pas trouvé" << std::endl;
      }
      exit(1);
    }
}
