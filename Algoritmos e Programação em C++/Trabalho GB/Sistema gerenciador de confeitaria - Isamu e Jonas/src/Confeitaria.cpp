#include "Confeitaria.h"

/// CONSTRUTOR
Confeitaria::Confeitaria(){

    fstream file;

    int id;
    string nome;
    float valor;
    string unidadeMedida;
    float quantEstoque;
    float quantMinEstoque;

    string nomeInsumo;
    float quantidade;

    file.open("Produtos.txt", fstream::in); // ABRE O ARQUIVO Produtos.txt PARA LEITURA

    if(file.is_open()){

        getline(file, nome); // CAPTURA A PRIMEIRA LINHA QUE CONTÉM APENAS DADOS NOMINAIS

        while(!file.eof()){ // ENQUANTO NÃO CHEGAR NO FINAL DO ARQUIVO

            file >> id;

            file.get(); // FUNÇÃO PARA CAPTURAR APENAS UM CARACTER, NO CASO '\t'
            getline(file, nome, '\t');

            file >> valor;

            file.get();
            getline(file, unidadeMedida, '\t');

            file >> quantEstoque;

            file >> quantMinEstoque;

            Produto *ponteiroProduto = new Produto(id, nome, valor, unidadeMedida, quantEstoque, quantMinEstoque); // ARMAZENA AS VARIAVEIS NUM PONTEIRO DA CLASSE PRODUTOS...

            this->lstProdutos.push_back(ponteiroProduto); // ...PARA INTRODUZI-LOS NO FINAL DO VECTOR lstProdutos

        }

        file.close();

    } // FIM DA LEITURA DOS DADOS PARA A LISTA DE PRODUTOS
    else cout << "ERRO! FALHA AO ABRIR O ARQUIVO!" << endl;

    file.open("Insumos.txt", fstream::in); // ABRE O ARQUIVO Insumos.txt PARA LEITURA

    if(file.is_open()){

        getline(file, nome);

        while(!file.eof()){

            file >> id;

            file.get();
            getline(file, nome, '\t');

            file >> valor;

            file.get();
            getline(file, unidadeMedida, '\t');

            file >> quantEstoque;

            file >> quantMinEstoque;

            Insumo *ponteiroInsumo = new Insumo(id, nome, valor, unidadeMedida, quantEstoque, quantMinEstoque); // ARMAZENA AS VARIAVEIS NUM PONTEIRO DA CLASSE INSUMOS...

            this->lstInsumos.push_back(ponteiroInsumo); // ...PARA INTRODUZI-LOS NO FINAL DO VECTOR lstInsumos

        }

        file.close();

    } // FIM DA LEITURA DOS DADOS PARA A LISTA DE INSUMOS
    else cout << "ERRO! FALHA AO ABRIR O ARQUIVO!" << endl;

    file.open("InsumosProduto.txt", fstream::in); // ABRE O ARQUIVO InsumosProduto.txt PARA LEITURA

    if(file.is_open()){

        getline(file, nome);

        while(!file.eof()){

            getline(file, nome, '\t'); // CAPTURA NOME DO PRODUTO
            //cout << nome << '&';
            getline(file, nomeInsumo, '\t'); // CAPTURA NOME DO INSUMO
            //cout << nomeInsumo << '&';
            file >> quantidade; // CAPTURA QUANTIDADE
            //cout << quantidade << endl;
            file.get(); // CAPTURA '\n'

            for(vector<Produto*>::iterator itP = this->lstProdutos.begin(); itP != this->lstProdutos.end(); itP++){

                for(vector<Insumo*>::iterator itI = this->lstInsumos.begin(); itI != this->lstInsumos.end(); itI++){

                    if(nome == (*itP)->getNome() && nomeInsumo == (*itI)->getNome()){

                        //cout << nome << '&' << nomeInsumo << endl;
                        (*itP)->leInsumosProduto(*itI, quantidade);
                        break;

                    }
                }

            }

        }

        file.close();

    } // FIM DA LEITURA DOS DADOS PARA A LISTA DE INSUMOS DE CADA PRODUTO
    else cout << "ERRO! FALHA AO ABRIR O ARQUIVO!" << endl;

}

/// DESTRUTOR
Confeitaria::~Confeitaria(){}

/// MÉTODOS
void Confeitaria::salvarConfeitaria(){

    int conta = 0;
    fstream file;

    file.open("Produtos.txt", fstream::out);

    if(file.is_open()){

        file << "idProduto" << '\t' << "nome" << '\t' << "valor" << '\t' << "unidadeMedida" << '\t' << "quantEstoque" << '\t' << "quantMinEstoque" << '\n';

        for(vector<Produto*>::iterator itP = this->lstProdutos.begin(); itP != this->lstProdutos.end(); itP++){

            if(conta == this->lstProdutos.size() - 1){
                file << (*itP)->getIdProduto() << '\t'
                << (*itP)->getNome() << '\t'
                << (*itP)->getValor() << '\t'
                << (*itP)->getUnidadeMedida() << '\t'
                << (*itP)->getQuantEstoque() << '\t'
                << (*itP)->getQuantMinEstoque();
            }
            else{
                file << (*itP)->getIdProduto() << '\t'
                << (*itP)->getNome() << '\t'
                << (*itP)->getValor() << '\t'
                << (*itP)->getUnidadeMedida() << '\t'
                << (*itP)->getQuantEstoque() << '\t'
                << (*itP)->getQuantMinEstoque() << '\n';
            }

            conta++;

        }

        file.close();

    }
    else cout << "ERRO! FALHA AO ABRIR O ARQUIVO!" << endl;

    conta = 0;
    file.open("Insumos.txt", fstream::out);

    if(file.is_open()){

        file << "idInsumo" << '\t' << "nome" << '\t' << "valor" << '\t' << "unidadeMedida" << '\t' << "quantEstoque" << '\t' << "quantMinEstoque" << '\n';

        for(vector<Insumo*>::iterator itI = this->lstInsumos.begin(); itI != this->lstInsumos.end(); itI++){

            if(conta == this->lstInsumos.size() - 1){
                file << (*itI)->getIdInsumo() << '\t'
                << (*itI)->getNome() << '\t'
                << (*itI)->getValor() << '\t'
                << (*itI)->getUnidadeMedida() << '\t'
                << (*itI)->getQuantEstoque() << '\t'
                << (*itI)->getQuantMinEstoque();
            }
            else{
                file << (*itI)->getIdInsumo() << '\t'
                << (*itI)->getNome() << '\t'
                << (*itI)->getValor() << '\t'
                << (*itI)->getUnidadeMedida() << '\t'
                << (*itI)->getQuantEstoque() << '\t'
                << (*itI)->getQuantMinEstoque() << '\n';
            }

            conta++;

        }

        file.close();

    }
    else cout << "ERRO! FALHA AO ABRIR O ARQUIVO!" << endl;

}

void Confeitaria::consultaProduto(int idEscolhido){

    for(vector<Produto*>::iterator itP = this->lstProdutos.begin(); itP != this->lstProdutos.end(); itP++){ // LAÇO PARA PROCURA DO PRODUTO ESCOLHIDO

        if(idEscolhido == (*itP)->getIdProduto()){

            cout << "\nID: " << "\t\t\t" << (*itP)->getIdProduto()
            << "\nNome: " << "\t\t\t" << (*itP)->getNome()
            << "\nValor: " << "\t\t\t" << (*itP)->getValor()
            << "\nUnidadeMedida: " << "\t\t" << (*itP)->getUnidadeMedida()
            << "\nQuantEstoque: " << "\t\t" << (*itP)->getQuantEstoque()
            << "\nQuantMinEstoque: " << "\t" << (*itP)->getQuantMinEstoque() << endl;
            cout << "\nInsumos necessarios para produzi-lo:" << endl;
            (*itP)->listaInsumos();

        }

    }

}
void Confeitaria::consultaProduto(string nomeEscolhido){

    for(vector<Produto*>::iterator itP = this->lstProdutos.begin(); itP != this->lstProdutos.end(); itP++){ // LAÇO PARA PROCURA DO PRODUTO ESCOLHIDO

        if(nomeEscolhido == (*itP)->getNome()){

            cout << "\nID: " << "\t\t\t" << (*itP)->getIdProduto()
            << "\nNome: " << "\t\t\t" << (*itP)->getNome()
            << "\nValor: " << "\t\t\t" << (*itP)->getValor()
            << "\nUnidadeMedida: " << "\t\t" << (*itP)->getUnidadeMedida()
            << "\nQuantEstoque: " << "\t\t" << (*itP)->getQuantEstoque()
            << "\nQuantMinEstoque: " << "\t" << (*itP)->getQuantMinEstoque() << endl;
            cout << "\nInsumos necessarios para produzi-lo:" << endl;
            (*itP)->listaInsumos();

        }

    }

}

void Confeitaria::consultaInsumo(int idEscolhido){

    for(vector<Insumo*>::iterator itI = this->lstInsumos.begin(); itI != this->lstInsumos.end(); itI++){ // LAÇO PARA PROCURA DO INSUMO ESCOLHIDO

        if(idEscolhido == (*itI)->getIdInsumo()){

            cout << "\nID: " << "\t\t\t" <<(*itI)->getIdInsumo()
            << "\nNome: " << "\t\t\t" <<(*itI)->getNome()
            << "\nValor: " << "\t\t\t" << (*itI)->getValor()
            << "\nUnidadeMedida: " << "\t\t" << (*itI)->getUnidadeMedida()
            << "\nQuantEstoque: " << "\t\t" << (*itI)->getQuantEstoque()
            << "\nQuantMinEstoque: " << "\t" << (*itI)->getQuantMinEstoque() << endl;

        }

    }

}
void Confeitaria::consultaInsumo(string nomeEscolhido){

    for(vector<Insumo*>::iterator itI = this->lstInsumos.begin(); itI != this->lstInsumos.end(); itI++){ // LAÇO PARA PROCURA DO INSUMO ESCOLHIDO

        if(nomeEscolhido == (*itI)->getNome()){

            cout << "\nID: " << "\t\t\t" <<(*itI)->getIdInsumo()
            << "\nNome: " << "\t\t\t" <<(*itI)->getNome()
            << "\nValor: " << "\t\t\t" << (*itI)->getValor()
            << "\nUnidadeMedida: " << "\t\t" << (*itI)->getUnidadeMedida()
            << "\nQuantEstoque: " << "\t\t" << (*itI)->getQuantEstoque()
            << "\nQuantMinEstoque: " << "\t" << (*itI)->getQuantMinEstoque() << endl;

        }

    }

}

void Confeitaria::listarVendas(){

    system("cls");
    cout << "==================================================================================================" << endl;
    cout << "-----LISTA DE VENDAS-----\n";

    cout << "\nProduto" << '\t' << "Quantidade vendida" << endl;

    for(vector<Venda*>::iterator itV = this->lstVendas.begin(); itV != this->lstVendas.end(); itV++){

        cout << "---" << (*itV)->getNomeProduto();
        cout << '\t' << (*itV)->getQuantidade() << endl;

    }

    cout << "==================================================================================================" << endl;

}

void Confeitaria::listarProdutos(){

    system("cls");
    cout << "==================================================================================================" << endl;
    cout << "-----LISTA DE PRODUTOS-----\n" << endl;
    cout << "Id" << '\t' << "Nome" << endl;

    for(vector<Produto*>::iterator itP = this->lstProdutos.begin(); itP != this->lstProdutos.end(); itP++){ // UTILIZA O ITERADOR PARA PEGAR APENAS DADOS DE CADA COMPONENTE DO VECTOR DE PRODUTOS
        cout << (*itP)->getIdProduto();
        cout << '\t' << (*itP)->getNome();
        cout << "\n\t---Valor: " << (*itP)->getValor();
        cout << "\n\t---Unidade Medida: " << (*itP)->getUnidadeMedida();
        cout << "\n\t---Quantidade em Estoque: " << (*itP)->getQuantEstoque();
        cout << "\n\t---Quantidade Minima em Estoque: " << (*itP)->getQuantMinEstoque() << endl;

        //(*itP)->listaInsumos();
    }

    cout << "==================================================================================================" << endl;

}

void Confeitaria::listarInsumos(){

    system("cls");
    cout << "==================================================================================================" << endl;
    cout << "-----LISTA DE INSUMOS-----\n" << endl;
    cout << "Id" << '\t' << "Nome" << endl;

    for(vector<Insumo*>::iterator itI = this->lstInsumos.begin(); itI != this->lstInsumos.end(); itI++){ // UTILIZA O ITERADOR PARA PEGAR APENAS DADOS DE CADA COMPONENTE DO VECTOR DE PRODUTOS
        cout << (*itI)->getIdInsumo();
        cout << '\t' << (*itI)->getNome();
        cout << "\n\t---Valor: " << (*itI)->getValor();
        cout << "\n\t---Unidade Medida: " << (*itI)->getUnidadeMedida();
        cout << "\n\t---Quantidade em Estoque: " << (*itI)->getQuantEstoque();
        cout << "\n\t---Quantidade Minima em Estoque: " << (*itI)->getQuantMinEstoque() << endl;
    }

    cout << "==================================================================================================" << endl;

}

void Confeitaria::atualizarProdutos(){
    char opSN;
    int opcao, cont = 0;

    system("cls");
    cout << "==================================================================================================" << endl;
    cout << "-----LISTA DE PRODUTOS A PRODUZIR-----\n";

    for(vector<Produto*>::iterator itI = lstProdutos.begin(); itI != lstProdutos.end(); itI++)  // LÊ LISTA DE PRODUTOS DO INÍCIO AO FIM
    {
        if((*itI)->getQuantEstoque() < (*itI)->getQuantMinEstoque())  // SE A QUANTIDADE MINIMA FOR MENOR QUE A ATUAL, ENTRA NO LAÇO PARA MOSTRAR PRODUTOS COM ESTOQUE MENOR QUE MÍNIMO
        {
            cout << "\nID: " << "\t\t\t" <<(*itI)->getIdProduto()
                 << "\nNome: " << "\t\t\t" <<(*itI)->getNome()
                 << "\nValor: " << "\t\t\t" << "R$" << (*itI)->getValor()
                 << "\nUnidadeMedida: " << "\t\t" << (*itI)->getUnidadeMedida()
                 << "\nQuantEstoque: " << "\t\t" << (*itI)->getQuantEstoque()
                 << "\nQuantMinEstoque: " << "\t" << (*itI)->getQuantMinEstoque() << endl;
            cont++;
        }
    }
    cout << "==================================================================================================" << endl;
    if(cont != 0) // VERIFICA SE A LISTAGEM ESTÁ VAZIA
    {
        cout << "Deseja comprar os produtos que faltam (s/n)? ";
        cin >> opSN;

        if(opSN == 's' || opSN == 'S') //ESSAS OPÕES APENAS SUBSTITUEM OS VALORES DE quantEstoque DO INSUMO NA MEMÓRIA, NÃO SALVA NO ARQUIVO TXT!!!
        {
            cout << "1- Para adicionar apenas as quantidades que faltam.\n2- Para adicionar quantidades personalizadas\nOpcao escolhida: ";
            cin >> opcao;

            system("cls");

            if(opcao == 1 || opcao == 2){
                for(vector<Produto*>::iterator itP = lstProdutos.begin(); itP != lstProdutos.end(); itP++){  // LÊ LISTA DE INSUMOS DO INÍCIO AO FIM
                    if((*itP)->getQuantEstoque() < (*itP)->getQuantMinEstoque())  // SE A QUANTIDADE MINIMA FOR MENOR QUE A ATUAL, ENTRA NO LAÇO
                         (*itP)->produzir(opcao);
                }
            }
        }
    }
}

void Confeitaria::atualizarInsumos(){
    char opSN;
    int opcao, cont = 0;

    system("cls");
    cout << "==================================================================================================" << endl;
    cout << "-----LISTA DE INSUMOS A PRODUZIR-----" << endl;

    for(vector<Insumo*>::iterator itI = lstInsumos.begin(); itI != lstInsumos.end(); itI++){  // LÊ LISTA DE INSUMOS DO INÍCIO AO FIM

        if((*itI)->getQuantEstoque() < (*itI)->getQuantMinEstoque()){  // SE A QUANTIDADE MINIMA FOR MENOR QUE A ATUAL, ENTRA NO LAÇO PARA MOSTRAR INSUMOS COM ESTOQUE MENOR QUE MINIMO
            cout << "ID: " << "\t\t\t" <<(*itI)->getIdInsumo()
                 << "\nNome: " << "\t\t\t" <<(*itI)->getNome()
                 << "\nValor: " << "\t\t\t" << "R$" << (*itI)->getValor()
                 << "\nUnidadeMedida: " << "\t\t" << (*itI)->getUnidadeMedida()
                 << "\nQuantEstoque: " << "\t\t" << (*itI)->getQuantEstoque()
                 << "\nQuantMinEstoque: " << "\t" << (*itI)->getQuantMinEstoque() << endl << endl;
            cont++;
        }

    }

    cout << "==================================================================================================" << endl;

    if(cont != 0){ // VERIFICA SE A LISTAGEM ESTÁ VAZIA

        cout << "Deseja comprar os insumos que faltam (s/n)? ";
        cin >> opSN;

        if(opSN == 's' || opSN == 'S'){

            cout << "1- Para adicionar apenas as quantidades que faltam.\n2- Para adicionar quantidades personalizadas\nOpcao escolhida: ";
            cin >> opcao;

            system("cls");

            if(opcao == 1 || opcao == 2){  // LÊ LISTA DE INSUMOS DO INÍCIO AO FIM
                for(vector<Insumo*>::iterator itI = lstInsumos.begin(); itI != lstInsumos.end(); itI++){
                    if((*itI)->getQuantEstoque() < (*itI)->getQuantMinEstoque())  // SE A QUANTIDADE MINIMA FOR MENOR QUE A ATUAL, ENTRA NO LAÇO
                        (*itI)->inserirEstoque(opcao);
                }
            }
            else cout << "ERRO! OPCAO INVÁLIDA!" << endl;

        }

    }

}

void Confeitaria::venderProdutos(){

    string nomeEscolhido;
    float quantidade;

    while(1){ // ABRE O LAÇO PARA A RECEPÇÃO DE PRODUTOS

        fflush(stdin);
        cout << "\nDigite o nome do produto a ser vendido: ";
        getline(cin, nomeEscolhido);
        fflush(stdin);
        cout << "Digite a quantidade a ser vendida: ";
        cin >> quantidade;

        while(cin.fail()){

            cout << "ERRO! DIGITO INVALIDO!" << endl;
            cin.clear();
            cin.ignore(256,'\n');
            cin >> quantidade;

        }

        if(quantidade > 0){

            for(vector<Produto*>::iterator itP = this->lstProdutos.begin(); itP != this->lstProdutos.end(); itP++){ // LAÇO PARA BUSCAR O PRODUTO NA LISTA DE PRODUTOS DA CONFEITARIA

                if(nomeEscolhido == (*itP)->getNome()){

                    if((*itP)->vender(quantidade)){ // REALIZA A VENDA CASO A HAJA PRODUTO SUFICIENTE PARA O PEDIDO

                        Venda *ponteiroVenda = new Venda(*itP, quantidade);

                        this->saldo += (*itP)->getValor() * quantidade;

                        this->lstVendas.push_back(ponteiroVenda); // SALVA NA LISTA A QUANTIDADE DE VENDAS

                        //this->listarProdutos();

                    }

                }

            }

        }
        else if(quantidade < 0) cout << "ERRO! ENTRADA INVALIDA!" << endl;
        else{ // FECHA O LAÇO E ENCERRA A LISTA DE VENDA

            cout << "\nLista de vendas encerrada!" << endl;
            break;

        }

    }

    //cout << "Receita da compra: " << this->saldo << endl;

}
