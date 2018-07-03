//#include "C:\Users\user\Desktop\TRB_GB_Melhorado\EXTRA\snake_game.h"
#include "Confeitaria.h"
#include "cstdlib"
#include "cstdio"

int main(){

    Confeitaria *sonho = new Confeitaria();

    char opcao = ' ';

    while(opcao != '0'){

        system("cls");

        cout << "Administrador de Confeitaria" << endl;
        cout << "1 - Realizar venda" << endl
        << "2 - Consultar produto" << endl
        << "3 - Consultar insumo" << endl
        << "4 - Listar produtos a produzir" << endl
        << "5 - Listar insumos a comprar" << endl
        << "6 - Listar todos os produtos" << endl
        << "7 - Listar todos os insumos" << endl
        << "8 - Listar vendas" << endl
        << "9 - Salvar" << endl
        << "0 - Sair" << endl
        << "\nOpcao: ";

        cin >> opcao;

        switch(opcao){

            case '1':
                sonho->venderProdutos();//PROBLEMA
                break;

            case '2':

                system("cls");
                cout << "==================================================================================================" << endl;
                cout << "-----CONSULTA DE PRODUTOS-----\n" << endl;

                fflush(stdin);
                cout << "Digite <1> para consultar por ID - Digite <2> para consultar por Nome: ";
                cin >> opcao;

                if(opcao == '1'){
                    int id;
                    fflush(stdin);
                    cout << "\nDigite o ID do produto desejado: ";
                    cin >> id;

                    while(cin.fail()){

                        cout << "ERRO! DIGITO INVALIDO!" << endl;
                        cin.clear();
                        cin.ignore(256,'\n');
                        cin >> id;

                    }

                    sonho->consultaProduto(id);

                    cout << "==================================================================================================" << endl;

                    break;
                }
                else if(opcao == '2'){
                    string nome;
                    fflush(stdin);
                    cout << "Digite o Nome do produto desejado: ";
                    getline(cin, nome);

                    sonho->consultaProduto(nome);

                    cout << "==================================================================================================" << endl;

                    break;
                }
                else cout << "ERRO! OPCAO INVALIDA!" << endl;


                break;

            case '3':
                system("cls");
                cout << "==================================================================================================" << endl;
                cout << "-----CONSULTA DE PRODUTOS-----\n" << endl;

                fflush(stdin);
                cout << "Digite <1> para consultar por ID - Digite <2> para consultar por Nome: ";
                cin >> opcao;

                if(opcao == '1'){
                    int id;
                    fflush(stdin);
                    cout << "\nDigite o ID do insumo desejado: ";
                    cin >> id;

                    while(cin.fail()){

                        cout << "ERRO! DIGITO INVALIDO!" << endl;
                        cin.clear();
                        cin.ignore(256,'\n');
                        cin >> id;

                    }

                    sonho->consultaInsumo(id);

                    cout << "==================================================================================================" << endl;

                    break;
                }
                else if(opcao == '2'){
                    string nome;
                    fflush(stdin);
                    cout << "\nDigite o Nome do insumo desejado: ";
                    getline(cin, nome);
                    sonho->consultaInsumo(nome);

                    cout << "==================================================================================================" << endl;

                    break;
                }
                else cout << "ERRO! OPCAO INVALIDA!" << endl;

                break;

            case '4':
                sonho->atualizarProdutos();
                break;

            case '5':
                sonho->atualizarInsumos();
                break;

            case '6':
                sonho->listarProdutos();
                break;

            case '7':
                sonho->listarInsumos();
                break;

            case '8':
                sonho->listarVendas();
                break;

            case '9':
                cout << "\nSalvando dados do sistema...\n" << endl;
                sonho->salvarConfeitaria();
                break;

            case '0':
                cout << "\ndesligando programa...\n" << endl;
                sonho->salvarConfeitaria();
                break;

            /*case 'p':
                snake_game();
                break;*/

            default:
                cout << "\nERRO! OPCAO INVALIDA!\n" << endl;
                break;

        }

        system("pause");

    }

    delete sonho;
    return 0;

}
