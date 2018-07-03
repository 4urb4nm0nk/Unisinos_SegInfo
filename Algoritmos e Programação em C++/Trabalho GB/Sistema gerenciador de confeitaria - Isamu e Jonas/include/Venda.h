#ifndef VENDA_H
#define VENDA_H

#include <iostream>
#include <string>
#include <vector>
#include <iterator>
#include <fstream>

#include "Produto.h"

using namespace std;

class Venda{

    private:
        /// ATRIBUTOS
        Produto *produto;
        float quantidade;

    public:
        /// CONSTRUTOR
        Venda();
        Venda(Produto *produto, float quantidade);

        /// DESTRUTOR
        virtual ~Venda();

        /// SETTERS_&_GETTERS
        float getQuantidade();
        string getNomeProduto();

        void setQuantidade(float quantidade);

};

#endif // VENDA_H
