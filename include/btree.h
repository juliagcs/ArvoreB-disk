/**********************************************
* Trabalho - Árvore B                         *
*                                             *
* Feito por: Julia Gabriella Corrêa Silva     *
* RA: 0048842                                 *
**********************************************/

#ifndef BTREE_H
#define BTREE_H
#include "node.h"
#include "typedfile.h"
#include "intserial.h"
#include "record.h"
#include "serializable.h"

#include <queue>

using namespace std;

template <class T, const unsigned int MIN_DEGREE>
class btree: private typedFile<node<T, MIN_DEGREE>>{
    public:
        btree(); //construtor default
        btree(const string name, const string type, const unsigned int version);//construtor parametrico
        virtual ~btree(); //destrutor

        void insert(T k); //metodo para inserir a chave
        void remove(T k); //metodo para remover a chave
        int search(node<T, MIN_DEGREE> x, T k); //metodo para pesquisar a chave
        void print(); //metodo para printar a árvore
        void printTest();
    protected:
        void insertNonFull(node<T, MIN_DEGREE> &x, unsigned long long int ind, T k); //metodo para inserir se a raiz não estiver cheia
        void printAux(node<T, MIN_DEGREE> x, vector<string> &v, unsigned int lvl); //metodo auxiliar do print da árvore
        int searchAux(node<T, MIN_DEGREE> x, T k); //metodo auxiliar da busca
        void splitChild(node<T,MIN_DEGREE> &x, node<T,MIN_DEGREE> &y, unsigned int i, unsigned int ind); //metodo para fazer a divisão do bó
        void removeAux(node<T, MIN_DEGREE> &x, unsigned long long int r, T k); //metodo para auxiliar a remoção da chave
        node<T, MIN_DEGREE> root; //raiz
};

template <class T, const unsigned int MIN_DEGREE>
btree<T, MIN_DEGREE>::btree(const string name, const string type, const unsigned int version) : typedFile<node<T, MIN_DEGREE>>(name, type, version){
    if(this->isOpen()){ //se o arquivo esta aberto
        record<node<T, MIN_DEGREE>> auxR; //record auxiliar
        unsigned int r = this->head.getRoot(); //pegando o primeiro valido
        if(r == 0){ //se a raiz for igual a zero
            this->insertRecord(auxR); //então será inserido record na raiz
            this->readHeader(this->head); //lendo o cabeçalho
            this->head.setRoot(this->getFirstValid());
            this->writeHeader(this->head);
        }else{ //se já tiver raiz
            this->readRecord(auxR, r); //leio a raiz para record
        }
        root = auxR.getData(); //salvando o valor de auxR na raiz
    }
}

template <class T, const unsigned int MIN_DEGREE>
btree<T, MIN_DEGREE>::~btree(){}

template <class T, const unsigned int MIN_DEGREE>
void btree<T, MIN_DEGREE>::insert(T k){
    int r = this->getRoot(); //pegando endereço da raiz
    node<T, MIN_DEGREE> y = root;
    node<T, MIN_DEGREE> s; //no x

    if(root.getSizeN() == node<T, MIN_DEGREE>::MAX){ //verificando se a raiz esta cheia
        s.setLeaf(false); //nova raiz não é folha
        s.setSizeN(0); //não tem chaves
        s.setChild(r, 0); //tornar a antiga raiz (ind) sua filha da esquerda
        splitChild(s,y,0,r);
        insertNonFull(s,this->getRoot(),k);

    }else{ //Se a raiz não estiver cheia é feito a inserção sem necessidade de divisão da raiz
        insertNonFull(root, r, k); //manda a raiz, o primeiro valido e a chave
    }
}

template <class T, const unsigned int MIN_DEGREE>
void btree<T, MIN_DEGREE>::remove(T k) {
    unsigned int r = this->getRoot(); //pegando raiz

    if (root.getSizeN() == 0){ //se a raiz foi igual a 0
        cout << "Árvore vazia." << endl; //a árvore esta vazia
    }
    removeAux(root, r, k); //chamo a função auxiliar
}

template <class T, const unsigned int MIN_DEGREE>
int btree<T, MIN_DEGREE>::search(node<T, MIN_DEGREE> x, T k) {
   x = root; //x recebe a raiz
   return searchAux(x, k);
}

template <class T, const unsigned int MIN_DEGREE>
void btree<T, MIN_DEGREE>::print() {
   int lvl = 0;
   vector<string> levels(1);
   printAux(root, levels, lvl);

   for (string s : levels) {
      cout << s << endl;
   }
}

template <class T, const unsigned int MIN_DEGREE> //inserção na página folha correta, descendo pela árvore e fazendo todas as divisões de páginas cheias que encontrar pelo caminho.
void btree<T, MIN_DEGREE>::insertNonFull(node<T, MIN_DEGREE>& x, unsigned long long int ind, T k){
    int i = x.getSizeN()-1; //i recebe o tamanho do node
    record<node<T, MIN_DEGREE>> auxR, auxR2; //registro para guardar o no
    node<T, MIN_DEGREE> n,l;

    if(x.isLeaf()){ //se x for folha
        while (i >= 0 && k < x.getKey(i)) { //enquanto i for maior que zero e a chave for menor que a chave do indice i na raiz
            x.setKey(x.getKey(i), i + 1); //reorganizo os valores do no
            i--; //decremento
        }
        i++; //incremento
        x.setKey(k, i); //raiz recebe a chave e o indice
        x.setSizeN(x.getSizeN()+1); //aumento o tamanho de quantidade de chaves
        auxR.setData(x); //registro recebe x
        this->writeRecord(auxR, ind); //escrevendo o registro
    }else{
        while(i >= 0 && k < x.getKey(i)){ //
            i--;
        }
        i++;
        this->readRecord(auxR2, x.getChild(i));
        n = auxR2.getData();
        if(n.getSizeN() == node<T, MIN_DEGREE>::MAX){ //verifico se o no filho esta cheio
            splitChild(x, n, i, x.getChild(i)); //fazer a divisão deste no
            if(k > x.getKey(i)){ //realocar as chaves
                i++;
            }
        }
        this->readRecord(auxR2, x.getChild(i)); //carrego o filho correto
        n = auxR2.getData();
        insertNonFull(n, x.getChild(i), k);
    }
}

template <class T, const unsigned int MIN_DEGREE>
void btree<T, MIN_DEGREE>::printAux(node<T, MIN_DEGREE> x, vector<string> &v, unsigned int lvl) {
   string aux = "[";
   unsigned int i = 0;
   record<node<T,MIN_DEGREE>> rec;
   node<T, MIN_DEGREE> auxRec;

   if (v.size() < lvl + 1) {
      v.resize(lvl + 1);
   }

   if (!x.isLeaf()) {
      for (i = 0; i <= x.getSizeN(); i++) {
         if (x.getChild(i) != x.NOT_FOUND){
            this->readRecord(rec, x.getChild(i));
            auxRec = rec.getData();
            printAux(auxRec, v, lvl + 1);
         }
      }
   }

   for (i = 0; i < x.getSizeN(); i++) {
      string n = x.auxPrintKey(i);
      aux +=  (n + ", ");
   }

   if (aux.length() > 1) {
      aux += "\b\b] ";
   } else {
      aux += "] ";
   }
   v[lvl] += aux;
}

template <class T, const unsigned int MIN_DEGREE>
int btree<T, MIN_DEGREE>::searchAux(node<T, MIN_DEGREE> x, T k) {
    unsigned int i = 0;
    record<node<T, MIN_DEGREE>> aux;

    while(i < x.getSizeN() && k > x.getKey(i)){
        i++;
    }
    if(i < x.getSizeN() && k == x.getKey(i)) {
        return i;
    }else {
        if(x.isLeaf()) {
            x.setSizeN(0);
            return -1;
        }else{
            this->readRecord(aux, x.getChild(i));
            x = aux.getData();
            return searchAux(x, k);
        }
    }
}

template <class T, const unsigned int MIN_DEGREE>
void btree<T, MIN_DEGREE>::splitChild(node<T,MIN_DEGREE> &x, node<T,MIN_DEGREE> &y, unsigned int i, unsigned int t) {
    record<node<T, MIN_DEGREE>> auxX, auxY, auxZ; //records auxiliadores
    node<T, MIN_DEGREE> z; //no z
    z.setLeaf(y.isLeaf()); //no z vai ser folha se o no y for
    T middle = y.getKey(MIN_DEGREE - 1); //mediana

    for (unsigned int j = 0; j < MIN_DEGREE - 1; j++) { //inserindo as chave de y em Z
        z.insertKey(y.getKey(j + MIN_DEGREE));
    }

    if (!y.isLeaf()) { //atualizando os filhos -- nao testamos
        for (unsigned int j = 0; j < MIN_DEGREE; j++) {
            z.setChild(y.getChild(j + MIN_DEGREE), j);
        }
    }

    for (unsigned int j = x.getSizeN(); j >= i + 1; j--) { //atualizando os fihos de x
        x.setChild(x.getChild(j), j+1);
    }

    //y
    y.setSizeN(node<T, MIN_DEGREE>::MIN); //define tamanho de y para min
    this->readRecord(auxY, t); //atualizou
    auxY.setData(y); //passando o valor de z para o record
    this->writeRecord(auxY,t); //escrevendo o record y

    //z
    auxZ.setData(z); //passando o valor de z para o record
    this->insertRecord(auxZ); //inseri o record z

    //x
    x.setChild(this->getFirstValid(),i+1); //x recebe z como o filho da direita
    x.insertKey(middle); //x recebe a mediana

    auxX.setData(x); //passando o valor de X para o record
    this->insertRecord(auxX); //inserir record x
    this->readHeader(this->head); //lendo o cabeçalho
    this->head.setRoot(this->getFirstValid()); //raiz recebe o primeiro valido (x)
    this->writeHeader(this->head); //escrevendo o cabeçalho
    root = x; //atualizando a raiz
}

template <class T, const unsigned int MIN_DEGREE>
void btree<T, MIN_DEGREE>::removeAux(node<T, MIN_DEGREE> &x, unsigned long long int i, T k) {
    unsigned int p = x.hasKey(k); //se a chave existir eu retorno a poisção
    record<node<T, MIN_DEGREE>> auxR; //record auxiliar

    if(p < x.getSizeN() && x.getKey(p) == k){ //se minha posição for diferente de -1
        if(x.isLeaf()) { //caso 1: se a chave k está em uma página folha x, remova k de x
            x.removeKey(p); //removo a chave da posição p
            auxR.setData(x); //paaso o valor de x para auxR
            this->writeRecord(auxR, i); //escrevo o record na posição i
        }
    }
}

#endif // BTREE_H
