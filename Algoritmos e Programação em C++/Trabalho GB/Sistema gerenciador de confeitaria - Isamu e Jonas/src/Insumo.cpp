#include "Insumo.h"

/// CONSTRUTOR
Insumo::Insumo(){}

Insumo::Insumo(int idInsumo, string nome, float valor, string unidadeMedida, float quantEstoque, float quantMinEstoque){

    this->idInsumo = idInsumo;
    this->nome = nome;
    this->valor = valor;
    this->unidadeMedida = unidadeMedida;
    this->quantEstoque = quantEstoque;
    this->quantMinEstoque = quantMinEstoque;

}

/// DESTRUTOR
Insumo::~Insumo(){}

/// SETTERS_&_GETTERS
int Insumo::getIdInsumo(){ return this->idInsumo; }
string Insumo::getNome(){ return this->nome; }
float Insumo::getValor(){ return this->valor; }
string Insumo::getUnidadeMedida(){ return this->unidadeMedida; }
float Insumo::getQuantEstoque(){ return this->quantEstoque; }
float Insumo::getQuantMinEstoque(){ return this->quantMinEstoque; }

void Insumo::setIdInsumo(int idInsumo){ this->idInsumo = idInsumo; }
void Insumo::setNome(string nome){ this->nome = nome; }
void Insumo::setValor(float valor){ this->valor = valor; }
void Insumo::setUnidadeMedida(string unidadeMedida){ this->unidadeMedida = unidadeMedida; }
void Insumo::setQuantEstoque(float quantEstoque){ this->quantEstoque = quantEstoque; }
void Insumo::setQuantMinEstoque(float quantMinEstoque){ this->quantMinEstoque = quantMinEstoque; }

/// MÉTODOS
void Insumo::inserirEstoque(int opcao){
    if(opcao == 1) // ADICIONA APENAS AS QUANTIDADES QUE FALTAM
    {
        this->setQuantEstoque(this->getQuantMinEstoque());
    }
    if(opcao == 2)
    {
        if(this->getQuantEstoque() < this->getQuantMinEstoque()) // SE A QUANTIDADE MINIMA FOR MENOR QUE A ATUAL, ENTRA NO LAÇO
            {
                float dif = 0, quantAAdicionar = 0;

                dif = this->getQuantMinEstoque() - this->getQuantEstoque();

                cout << endl << "Dados do insumo:" ;
                cout << "\nID: " << "\t\t\t" << this->getIdInsumo()
                     << "\nNome: " << "\t\t\t" << this->getNome()
                     << "\nValor: " << "\t\t\t" << "R$" << this->getValor()
                     << "\nUnidadeMedida: " << "\t\t" << this->getUnidadeMedida()
                     << "\nQuantEstoque: " << "\t\t" << this->getQuantEstoque()
                     << "\nQuantMinEstoque: " << "\t" << this->getQuantMinEstoque()
                     << "\n\nInsira a quantidade que deseja adicionar:\n*O minimo para este insumo eh " << dif << '!' << endl << "Quantidade desejada: ";
                cin >> quantAAdicionar;

                while(cin.fail()){

                    cout << "ERRO! DIGITO INVALIDO!" << endl;
                    cin.clear();
                    cin.ignore(256,'\n');
                    cin >> quantAAdicionar;

                }

                while(quantAAdicionar < dif)
                {
                    cout << "\nERRO: A quantidade desejada deve ser maior que a minima! Por favor, tente novamente: "
                         << "\n*O minimo para este produto eh " << dif << '!' << endl << "Quantidade desejada: ";
                    cin >> quantAAdicionar;

                    while(cin.fail()){

                        cout << "ERRO! DIGITO INVALIDO!" << endl;
                        cin.clear();
                        cin.ignore(256,'\n');
                        cin >> quantAAdicionar;

                    }

                }
                this->setQuantEstoque(quantAAdicionar + this->getQuantEstoque());
                dif = 0;
            }
    }
}
bool Insumo::removerEstoque(float quantidade){

    if(quantidade > this->quantEstoque) return true;
    else{
        this->quantEstoque -= quantidade;
        return false;
    }

}
