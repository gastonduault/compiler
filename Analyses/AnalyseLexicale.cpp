std::string line;

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


void lecture() {
    while (std::isspace(line[0]) && line.size() > 0)
    {
        line.erase(0, 1);
    }

    if ((line.size() == 0))
    {
        tokenCurrent.type = tokenEOF_;
    }

    if (std::isalpha(line[0]) && line.size() > 0)
    {
        tokenCurrent.type = tokenI;
        tokenCurrent.value = line[0];
        line.erase(0, 1);

        // Les caractères qui suivent sont aussi des identificateurs
        while (std::isalpha(line[0]) && line.size() > 0)
        {
            tokenCurrent.value += (line[0]);
            line.erase(0, 1);
        }
        if(tokenCurrent.value.compare(tokenDEBUG) == 0){
            tokenCurrent.type = tokendebug;
        }
    }

    else if (line[0] == POINT_tokenVIRGULE && line.size() > 0)
    {
        tokenCurrent.type = tokenPvirgule;
        tokenCurrent.value = line[0];
        line.erase(0, 1);
    }

    else if (line[0] == tokenVIRGULE && line.size() > 0)
    {
        tokenCurrent.type = tokenvirgule;
        tokenCurrent.value = line[0];
        line.erase(0, 1);
    }

        // Le caractère courant est signe +
    else if (line[0] == SIGNE_PLUS && line.size() > 0)
    {
        tokenCurrent.type = tokenPlus;
        tokenCurrent.value = line[0];
        line.erase(0, 1);
    }

        // Le caractère courant est signe -
    else if (line[0] == SIGNE_MOINS && line.size() > 0)
    {
        tokenCurrent.type = tokenMoins;
        tokenCurrent.value = line[0];
        line.erase(0, 1);
    }

        // Le caractère courant est signe *
    else if (line[0] == SIGNE_MULT && line.size() > 0)
    {
        tokenCurrent.type = tokenMult;
        tokenCurrent.value = line[0];
        line.erase(0, 1);
    }

        // Le caractère courant est signe /
    else if (line[0] == SIGNE_DIV && line.size() > 0)
    {
        tokenCurrent.type = tokenDiv;
        tokenCurrent.value = line[0];
        line.erase(0, 1);
    }

        // Le caractère courant est signe (
    else if (line[0] == PARA_OUV && line.size() > 0)
    {
        tokenCurrent.type = tokenParaO;
        tokenCurrent.value = line[0];
        line.erase(0, 1);
    }

        // Le caractère courant est signe )
    else if (line[0] == PARA_FERM && line.size() > 0)
    {
        tokenCurrent.type = tokenParaF;
        tokenCurrent.value = line[0];
        line.erase(0, 1);
    }

        // Le caractère courant est signe {
    else if (line[0] == ACC_OUV && line.size() > 0)
    {
        tokenCurrent.type = tokenAccO;
        tokenCurrent.value = line[0];
        line.erase(0, 1);
    }

        // Le caratère courant est signe }
    else if (line[0] == ACC_FERM && line.size() > 0)
    {
        tokenCurrent.type = tokenAccF;
        tokenCurrent.value = line[0];
        line.erase(0, 1);
    }

        // Le caractère courant est une constante
    else if (isdigit(line[0]) && line.size() > 0)
    {
        tokenCurrent.type = tokenK;
        tokenCurrent.value = line[0];
        line.erase(0, 1);

        // Les caractères qui suivent sont aussi des constantes
        while (isdigit(line[0]) && line.size() > 0)
        {
            tokenCurrent.value += (line[0]);
            line.erase(0, 1);
        }
    }
}

void next()
{
    tokenLast.type = tokenCurrent.type;
    tokenLast.value = tokenCurrent.value;
    lecture();
    printAnaLex();
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
        std::cout << "ERREUR FATALE | accept()" << std::endl;
        exit(1);
    }
}
