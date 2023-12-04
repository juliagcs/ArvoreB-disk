/**********************************************
* Trabalho - Árvore B                         *
*                                             *
* Feito por: Julia Gabriella Corrêa Silva     *
* RA: 0048842                                 *
**********************************************/
#include <iostream>
#include <clocale>
#include <vector>
#include "btree.h"
#include "intserial.h"
#include "serialcurrency.h"

using namespace std;

int main(){
    setlocale(LC_ALL, "Portuguese");
    int option;
    float value;
    bool exit = false;
    serialcurrency vectorInsert[21] = {5.50, 2.01, -5.33, 10.05, 21.13, 1.88, -3.14, 2.86, 37.55, 2.99, 34.31, 49.00, 38.26, 20.85, 23.02, 17.01, 14.92, 13.81, 39.89, -13.22, 7.20};
    serialcurrency vectorRemove[11] = {5.50, -5.33, 21.13, 1.88, -3.14, 34.31, 38.26, 23.02, 14.92, 39.89, 7.20};
    btree<serialcurrency, 3> btree("Data.dat","tpg", 1);
    node<serialcurrency, 3> nod;
    serialcurrency n;

        do{
            cout << "\n--- Árvore B em disco ---\n"
                << "1. Inserir um valor na árvore\n"
                << "2. Remover um valor da árvore\n"
                << "3. Pesquisar um valor na árvore\n"
                << "4. Imprimir a árvore\n"
                << "5. Teste automatizado\n"
                << "6. Sair\n\n"
                << "Digite uma opção: ";
            cin >> option;

            switch (option){
                case 1:{
                    cout << "Digite o valor que deseja inserir: ";
                    cin >> value;
                    n = serialcurrency(value);
                    btree.insert(n);
                    btree.print();

                    break;
                }
                case 2:
                    cout << "Digite o valor que deseja remover: ";
                    cin >> value;
                    n = serialcurrency(value);
                    btree.remove(n);
                    btree.print();

                    break;
                case 3:
                    cout << "Digite o valor que deseja pesquisar: ";
                    cin >> value;
                    n = serialcurrency(value);
                    if(btree.search(nod, n)){
                        cout << "O valor " << value << " foi encontrado na árvore." << endl;
                    }else{
                        cout << "O valor " << value << " não foi encontrado na árvore." << endl;
                    }
                    break;
                case 4:
                    btree.print();
                    break;
                case 5:
                    cout << "Inserções teste" << endl;
                    for(serialcurrency i : vectorInsert) {
                        cout << "\nInserindo: " << i << ":" << endl;
                        btree.insert(i);
                        btree.print();
                    }
//                    cout << "Remoções teste" << endl;
//                    for(serialcurrency i : vectorRemove) {
//                        cout << "\nRemovendo: " << i << ":" << endl;
//                        btree.remove(i);
//                        btree.print();
//                    }
                    break;

                case 6:
                    cout << "Encerrando o programa." << endl;
                    exit = true;
                    break;
                default:
                    cout << "Opção inválida! Tente novamente." << endl;
                    break;
            }
        }while(exit != true);
}
