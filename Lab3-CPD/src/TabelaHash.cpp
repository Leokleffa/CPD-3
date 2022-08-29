#include "../include/TabelaHash.h"

#include <iostream>

//////////////////////////////////
/// CONSTRUTORES E DESTRUTORES ///
//////////////////////////////////

TabelaHash_EndAberto::TabelaHash_EndAberto(unsigned int m):
M(m)
{
    tabela.resize(M);
    for(unsigned int i=0;i<M;i++)
    {
        tabela[i].usado=false;
        tabela[i].ocupado=false;
        tabela[i].registro=NULL;
    }

    totalColisoes=0;
}

TabelaHash_EndFechado::TabelaHash_EndFechado(unsigned int m, unsigned int t):
M(m), TamanhoBucket(t)
{
    tabelaChaining.resize(M);

    tabelaBuckets.resize(M);
    for(unsigned int i=0;i<M; i++)
        tabelaBuckets[i].resize(TamanhoBucket);

    totalColisoes=0;
}

TabelaHash_EndAberto::~TabelaHash_EndAberto()
{

}

TabelaHash_EndFechado::~TabelaHash_EndFechado()
{

}

////////////////////////////
/// ENDERECAMENTO ABERTO ///
////////////////////////////

bool TabelaHash_EndAberto::insereEABL(std::string chave, Registro* reg)
{
    int colisoes = 0;
    bool inseriu = false;

    ///TODO: Completar funcao de insercao em tabela de enderecamento aberto com busca linear
    int e, marca, endc, endL;
    e = -1;
    marca = -1;
    endc = MapearChavesA(chave, M);
    endL = endc;

    do{
        if(tabela[endL].usado == true)
            if(tabela[endL].ocupado == true)
                if(tabela[endL].chave == chave)
                    e = endL;
                else{
                    endL = (endL + 1)%M;
                    colisoes++;
                }
            else{
                if(marca == -1)
                    marca = endL;
                endL = (endL + 1)%M;
            }
        else{
            if(marca == -1)
                marca = endL;
            break;
        }
    }while(endL != endc || e == -1);

    if(marca != -1 && e == -1){
        inseriu = true;
        tabela[marca].chave = chave;
        tabela[marca].registro = reg;
        tabela[marca].usado = true;
        tabela[marca].ocupado = true;
    }

    totalColisoes += colisoes;

    return inseriu;
}

Registro* TabelaHash_EndAberto::buscaEABL(std::string chave)
{
    int colisoes=0;
    Registro* r = NULL;

    ///TODO: Completar funcao de busca em tabela de enderecamento aberto com busca linear

    int endc, endL;
    endc = MapearChavesA(chave, M);
    endL = endc;

    do{
        if(tabela[endL].usado == true)
            if(tabela[endL].ocupado == true && tabela[endL].chave == chave)
                r = tabela[endL].registro;
            else{
                colisoes++;
                if(endL == M-1)
                    endL=0;
                else
                    endL++;
            }
        else
            break;
    }while(endL != endc || r == NULL);

    totalColisoes += colisoes;

    return r;
}

bool TabelaHash_EndAberto::insereDoubleHashing(std::string chave, Registro* reg)
{
    int colisoes=0;
    bool inseriu = false;

    ///TODO: Completar funcao de insercao em tabela de enderecamento aberto com double hashing
    int e, marca, endc, endL;
    e = -1;
    marca = -1;
    endc = MapearChavesA(chave, M);
    endL = endc;

    do{
        if(tabela[endL].usado == true)
            if(tabela[endL].ocupado == true)
                if(tabela[endL].chave == chave)
                    e = endL;
                else{
                    endL = endL%M+1;
                    colisoes++;
                }
            else{
                if(marca == -1)
                    marca = endL;
                endL = endL%M+1;
            }
        else{
            if(marca == -1)
                marca = endL;
            break;
        }
    }while(endL != endc || e == -1);

    if(marca != -1 && e == -1){
        inseriu = true;
        tabela[marca].chave = chave;
        tabela[marca].registro = reg;
        tabela[marca].usado = true;
        tabela[marca].ocupado = true;
    }

    totalColisoes += colisoes;

    return inseriu;
}

Registro* TabelaHash_EndAberto::buscaDoubleHashing(std::string chave)
{
    Registro* r = NULL;

    ///TODO: Completar funcao de busca em tabela de enderecamento aberto com double hashing




    return r;
}

int TabelaHash_EndAberto::colisoesOcorridas()
{
    return totalColisoes;
}

/////////////////////////////
/// ENDERECAMENTO FECHADO ///
/////////////////////////////

bool TabelaHash_EndFechado::insereChaining(std::string chave, Registro* reg)
{
    int colisoes=0;
    bool inseriu = false;

    ///TODO: Completar funcao de insercao em tabela de enderecamento fechado com encadeamento (chaining)



    totalColisoes += colisoes;

    return inseriu;
}

Registro* TabelaHash_EndFechado::buscaChaining(std::string chave)
{
    Registro* r = NULL;

    ///TODO: Completar funcao de busca em tabela de enderecamento fechado com encadeamento (chaining)




    return r;
}

bool TabelaHash_EndFechado::insereBuckets(std::string chave, Registro* reg)
{
    int colisoes=0;
    bool inseriu = false;

    ///TODO: Completar funcao de insercao em tabela de enderecamento fechado com blocos de tamanho fixo (buckets) e area de overflow




    totalColisoes += colisoes;

    return inseriu;
}

Registro* TabelaHash_EndFechado::buscaBuckets(std::string chave)
{
    Registro* r = NULL;

    ///TODO: Completar funcao de busca em tabela de enderecamento fechado com blocos de tamanho fixo (buckets) e area de overflow





    return r;
}

int TabelaHash_EndFechado::colisoesOcorridas()
{
    return totalColisoes;
}

int TabelaHash_EndAberto::MapearChavesA(std::string s, int M){
    int hash = 0;
    for (int i = 0; i < s.length(); i++)
        hash = (31 * hash + s.at(i)) % M;
    return hash;
}

int TabelaHash_EndFechado::MapearChavesF(std::string s, int M){
    int hash = 0;
    for (int i = 0; i < s.length(); i++)
        hash = (31 * hash + s.at(i)) % M;
    return hash;
}
