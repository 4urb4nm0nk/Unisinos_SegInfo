#ifndef PRODUTO_H
#define PRODUTO_H

#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <fstream>
#include <cstdlib>

#include "InsumosProduto.h"

using namespace std;

class Produto{

    private:
        /// ATRIBUTOS
        int idProduto;
        string nome;
        float valor;
        string unidadeMedida;
        float quantEstoque;
        float quantMinEstoque;
        vector<InsumosProduto*> lstInsumos;

    public:
        /// CONSTRUTOR
        Produto();
        Produto(int idProduto, string nome, float valor, string unidadeMedida, float quantEstoque, float quantMinEstoque);

        /// DESTRUTOR
        virtual ~Produto();

        /// SETTERS_&_GETTERS
        int getIdProduto();
        string getNome();
        float getValor();
        string getUnidadeMedida();
        float getQuantEstoque();
        float getQuantMinEstoque();

        void setIdProduto(int idProduto);
        void setNome(string nome);
        void setValor(float valor);
        void setUnidadeMedida(string unidadeMedida);
        void setQuantEstoque(float quantEstoque);
        void setQuantMinEstoque(float quantMinEstoque);

        /// MÉTODOS
        void leInsumosProduto(Insumo *insumo, float quantidade);

        void listaInsumos();

        void produzir(int opcao);
        bool vender(float quantidade);

};

#endif // PRODUTO_H
