/**********************************************
* Trabalho - Árvore B                         *
*                                             *
* Feito por: Julia Gabriella Corrêa Silva     *
* RA: 0048842                                 *
**********************************************/

#ifndef NODE_H
#define NODE_H
#include<iostream>
#include <vector>
#include "serializable.h"

using namespace std;

template <class T, const unsigned int MIN_DEGREE>
class node : public serializable{ //Classe no
    public:
        node(); //construtor defaut
        node(const node<T, MIN_DEGREE> &other); //construtor de copia
        virtual ~node(); //destrutor

        //metodos para sobrecarga de operadores
        node<T, MIN_DEGREE> operator=(const node<T, MIN_DEGREE>& other); //sobrecarga de = (atribuição)

        //acessores
        void setLeaf(bool leaf); //alterador da folha
        bool isLeaf() const; //mostra se o no é folha (get)
        void setSizeN(unsigned int s); //alterador do tamanho do no
        unsigned int getSizeN() const; //consultor para o tamanho do no
        void setKey(T k, unsigned int i); //alterador da chave do no
        T getKey(int i); //consultor para a chave do no
        void insertKey(T k); //inserção em uma página folha
        string auxPrintKey(unsigned int i); //metodo auxiliar para ptint da chave
        unsigned int hasKey(T k); //metodo que retorna se tem chave
        void removeKey(unsigned int i); //metodo para remover a chave
        void setChild(unsigned long long int c, unsigned int i); //alterador filho do no
        unsigned int getChild(unsigned int i); //consultor filho do no

        static const unsigned int MAX = 2 * MIN_DEGREE - 1; //maximo = 2t-1 chaves
        static const unsigned int MIN = MIN_DEGREE - 1; //minimo = t-1 chaves
        static const unsigned int NOT_FOUND = -1;

        virtual string toString(); //serialização
        virtual void fromString(string repr); //desserialização
        virtual string toCSV() { return ""; }
        virtual void fromCSV(string repr) {}
        virtual string toJSON() { return ""; }
        virtual void fromJSON(string repr) {}
        virtual string toXML() { return ""; }
        virtual void fromXML(string repr) {}
        virtual unsigned long long int size() const; //método do tamanho
    protected:
        vector<T> keys; //vetor de chaves
        vector<unsigned int> children; //vetor de inteiros para os filhos
        bool leaf; //boleana para folha
        unsigned int numKeys; //inteiro do numeros de chaves
};

template <class T, const unsigned int MIN_DEGREE>
node<T, MIN_DEGREE>::node(){
    unsigned int i;

    leaf = true;
    numKeys = 0;
    keys.resize(MAX);
    for (i = 0; i < keys.size(); i++) {
        keys[i] = NOT_FOUND;
    }
    children.resize(MAX + 1);
    for (i = 0; i < children.size(); i++) {
        children[i] = NOT_FOUND;
    }
}

template <class T, const unsigned int MIN_DEGREE>
node<T, MIN_DEGREE>::node(const node<T, MIN_DEGREE> &other){
    leaf = other.isLeaf();
    numKeys = other.getSizeN();
    keys = other.keys;
    children = other.children;
}

template <class T, const unsigned int MIN_DEGREE>
node<T, MIN_DEGREE>::~node(){}

template <class T, const unsigned int MIN_DEGREE>
node<T, MIN_DEGREE> node<T, MIN_DEGREE>::operator=(const node<T, MIN_DEGREE> &other){
    node<T, MIN_DEGREE> aux(other);

    leaf = other.isLeaf();
    numKeys = other.getSizeN();
    keys = other.keys;
    children = other.children;
    return aux;
}

template <class T, const unsigned int MIN_DEGREE>
void node<T, MIN_DEGREE>::setLeaf(bool l){
    leaf = l;
}

template <class T, const unsigned int MIN_DEGREE>
bool node<T, MIN_DEGREE>::isLeaf() const{
    return leaf;
}

template <class T, const unsigned int MIN_DEGREE>
void node<T, MIN_DEGREE>::setSizeN(unsigned int s){
    numKeys = s;
}

template <class T, const unsigned int MIN_DEGREE>
unsigned int node<T, MIN_DEGREE>::getSizeN() const{
    return numKeys;
}

template <class T, const unsigned int MIN_DEGREE>
void node<T, MIN_DEGREE>::setKey(T k, unsigned int i){
    keys[i] = k;
}

template <class T, const unsigned int MIN_DEGREE>
T node<T, MIN_DEGREE>::getKey(int i){
    return keys[i];
}

template <class T, const unsigned int MIN_DEGREE>
unsigned int node<T, MIN_DEGREE>::hasKey(T k){
   unsigned int i = 0;
   int pos = NOT_FOUND;

   while (i < numKeys && pos == -1){ //enquanto tiver chaves, pos vai retornando
      if (keys[i] == k) {
         pos = i;
      }
      i++;
    }
   return pos;
}

template <class T, const unsigned int MIN_DEGREE>
void node<T, MIN_DEGREE>::removeKey(unsigned int i) {
   unsigned int j = i;

   while(j < numKeys - 1) {
      keys[j] = keys[j + 1];
      j++;
   }
   if(!leaf) {
      j = i + 1;
      while(j < numKeys){
         children[j] = children[j + 1];
         j++;
      }
   }
   numKeys = numKeys - 1;
}

template <class T, const unsigned int MIN_DEGREE>
void node<T, MIN_DEGREE>::insertKey(T k) {
   int i = numKeys - 1;

   while (i >= 0 && k < keys[i]) {
      keys[i + 1] = keys[i];
      i--;
   }

   keys[i + 1] = k;
   numKeys = (numKeys + 1);
}

template <class T, const unsigned int MIN_DEGREE>
string node<T, MIN_DEGREE>::auxPrintKey(unsigned int i){
    string auxKey = "";

    auxKey = to_string(getKey(i).getX());
    auxKey += ".";
    auxKey += to_string(getKey(i).getY());
    return auxKey;
}

template <class T, const unsigned int MIN_DEGREE>
void node<T, MIN_DEGREE>::setChild(unsigned long long int c, unsigned int i){
    children[i] = c;
}

template <class T, const unsigned int MIN_DEGREE>
unsigned int node<T, MIN_DEGREE>::getChild(unsigned int i){
    return children[i];
}

template <class T, const unsigned int MIN_DEGREE>
string node<T, MIN_DEGREE>::toString(){ //método para serializar o registro
    int i = 0;
    string aux = "";
    //passando os objetos para string como uma sequência de bytes, junto com a contagem de bytes
    aux += string(reinterpret_cast<char*>(&leaf), sizeof(leaf));
    aux += string(reinterpret_cast<char*>(&numKeys), sizeof(numKeys));
    for (i = 0;i < keys.size(); i++){  //serializando todos as chaves
        aux += keys[i].toString();
    }
    for (i = 0;i < children.size(); i++){ //serializando todos os filhos
        aux += string(reinterpret_cast<char*>(&children[i]), sizeof(children[i]));
    }
    return aux;
}

template <class T, const unsigned int MIN_DEGREE>
void node<T, MIN_DEGREE>::fromString(string repr){ //método para desserializar o registro
    string subD;
    int pos = 0;
    int i = 0;

    repr.copy(reinterpret_cast<char*>(&leaf), sizeof(leaf), pos); //copia da string para o atributo leaf
    pos += sizeof(leaf); //adicionando no pos o tamanho a contagem de bytes da leaf
    repr.copy(reinterpret_cast<char*>(&numKeys), sizeof(numKeys), pos);  //copia da string para o atributo n
    pos += sizeof(numKeys); //adicionando no pos o tamanho a contagem de bytes de n
    for (i = 0;i < keys.size(); i++){ //desserializando todos as chaves
        subD = repr.substr(pos,keys[i].size());
        keys[i].fromString(subD);
        pos += keys[i].size(); //adicionando no pos o tamanho a contagem de bytes das chaves
        subD = "";
    }
    for (i = 0;i < children.size(); i++){ //desserializando todos os filhos
        repr.copy(reinterpret_cast<char*>(&children[i]), sizeof(children[i]), pos); //copia da string para o atributo filhos
        pos += sizeof(children[i]); //adicionando no pos o tamanho a contagem de bytes dos filhos
    }
}

template <class T, const unsigned int MIN_DEGREE>
unsigned long long int node<T, MIN_DEGREE>::size() const{ //metodo para retornar o tamanho total
    return ((keys.size() * keys[0].size()) +(children.size() * sizeof(children[0])) + sizeof(leaf) + sizeof(numKeys));
}

#endif // NODE_H
