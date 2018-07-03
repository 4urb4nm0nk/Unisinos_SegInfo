#include "Venda.h"

/// CONSTRUTOR
Venda::Venda(){}

Venda::Venda(Produto *produto, float quantidade){

    this->produto = produto;
    this->quantidade = quantidade;

}

/// DESTRUTOR
Venda::~Venda(){}

/// SETTERS_&_GETTERS
float Venda::getQuantidade(){ return this->quantidade; }
string Venda::getNomeProduto(){ return this->produto->getNome(); }

void Venda::setQuantidade(float quantidade){ this->quantidade = quantidade; }
