#include "Produto.h"

/// CONSTRUTOR
Produto::Produto(){}

Produto::Produto(int idProduto, string nome, float valor, string unidadeMedida, float quantEstoque, float quantMinEstoque){

    this->idProduto = idProduto;
    this->nome = nome;
    this->valor = valor;
    this->unidadeMedida = unidadeMedida;
    this->quantEstoque = quantEstoque;
    this->quantMinEstoque = quantMinEstoque;

}

/// DESTRUTOR
Produto::~Produto(){}

/// SETTERS_&_GETTERS
int Produto::getIdProduto(){ return this->idProduto; }
string Produto::getNome(){ return this->nome; }
float Produto::getValor(){ return this->valor; }
string Produto::getUnidadeMedida(){ return this->unidadeMedida; }
float Produto::getQuantEstoque(){ return this->quantEstoque; }
float Produto::getQuantMinEstoque(){ return this->quantMinEstoque; }

void Produto::setIdProduto(int idProduto){ this->idProduto = idProduto; }
void Produto::setNome(string nome){ this->nome = nome; }
void Produto::setValor(float valor){ this->valor = valor; }
void Produto::setUnidadeMedida(string unidadeMedida){ this->unidadeMedida = unidadeMedida; }
void Produto::setQuantEstoque(float quantEstoque){ this->quantEstoque = quantEstoque; }
void Produto::setQuantMinEstoque(float quantMinEstoque){ this->quantMinEstoque = quantMinEstoque; }

/// MÉTODOS
void Produto::leInsumosProduto(Insumo *insumo, float quantidade){ // FUNÇÃO PARA ADICIONAR UM INSUMO A LISTA DE INSUMOS NECESSÁRIOS PARA O PRODUTO

    InsumosProduto *ponteiroInsumosProduto = new InsumosProduto(insumo, quantidade);

    this->lstInsumos.push_back(ponteiroInsumosProduto);

}

void Produto::listaInsumos(){

    for(vector<InsumosProduto*>::iterator itIP = this->lstInsumos.begin(); itIP != this->lstInsumos.end(); itIP++){ // LAÇO PARA LISTAR OS INSUMOS DE UM PRODUTO

        cout << "---" << (*itIP)->getNomeInsumo() << '\t';
        cout << (*itIP)->getQuantidade() << endl;

    }

}

void Produto::produzir(int opcao){
    Insumo *insumo;
    float quantInsumo = 0;
    float dif = 0, quantAAdicionar = 0;
    bool flag_falta = false;

    if(opcao == 1){

        for(vector<InsumosProduto*>::iterator itIP = this->lstInsumos.begin(); itIP != this->lstInsumos.end(); itIP++){

            insumo = (*itIP)->getInsumo(); // RECEBE O ENDEREÇO NA MEMÓRIA DO INSUMO A CONSUMIR NO PRODUTO
            quantAAdicionar = this->quantMinEstoque - this->quantEstoque;

            quantInsumo = quantAAdicionar * (*itIP)->getQuantidade();
            flag_falta = insumo->removerEstoque(quantInsumo); // FLAG VERIFICADORA DE FALTA DE INSUMOS SUFICIENTES

            if(flag_falta == true){
                cout << "INSUMOS INSUFICIENTES! CANCELANDO ADD!" << endl;
                //cout << insumo->getNome() << endl;
                break;
            }

        }

    }
    else if(opcao == 2){

        if(this->getQuantEstoque() < this->getQuantMinEstoque()){

            dif = this->getQuantMinEstoque() - this->getQuantEstoque();

            cout << "\nDados do produto:" ;
            cout << "\nID: " << "\t\t\t" << this->getIdProduto()
                 << "\nNome: " << "\t\t\t" << this->getNome()
                 << "\nValor: " << "\t\t\t" << "R$" << this->getValor()
                 << "\nUnidadeMedida: " << "\t\t" << this->getUnidadeMedida()
                 << "\nQuantEstoque: " << "\t\t" << this->getQuantEstoque()
                 << "\nQuantMinEstoque: " << "\t" << this->getQuantMinEstoque()
                 << "\n\nInsira a quantidade que deseja adicionar:\n*O minimo para este produto eh " << dif << '!' << endl << "Quantidade desejada: ";
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

            for(vector<InsumosProduto*>::iterator itIP = this->lstInsumos.begin(); itIP != this->lstInsumos.end(); itIP++){ // LAÇO PARA LISTAR OS INSUMOS DE UM PRODUTO

                insumo = (*itIP)->getInsumo(); // RECEBE O ENDEREÇO NA MEMÓRIA DO INSUMO A CONSUMIR NO PRODUTO

                quantInsumo = quantAAdicionar * (*itIP)->getQuantidade();
                flag_falta = insumo->removerEstoque(quantInsumo); // FLAG VERIFICADORA DE FALTA DE INSUMOS SUFICIENTES

                if(flag_falta == true){
                    cout << "INSUMOS INSUFICIENTES! CANCELANDO ADD!" << endl;
                    //cout << insumo->getNome() << endl;
                    break;
                }

            }

        }

    }

    if(flag_falta == false) this->quantEstoque += quantAAdicionar;

}

bool Produto::vender(float quantidade){

    if(this->quantEstoque - quantidade < 0){ // VERIFICA SE HÁ PRODUTOS SUFICIENTES PARA ALGUM PEDIDO...

        cout << "QUANTIDADE INSUFICIENTE! CANCELANDO PEDIDO!" << endl; // ... SE NÃO, CANCELA O PEDIDO E NÃO COMPUTA A VENDA

        return false;

    }
    else{

        this->quantEstoque -= quantidade; // ... SE SIM, COMPUTA A VENDA E DA BAIXA DE PRODUTOS NO SISTEMA

        return true;

    }

}
