/**********************************************
* Trabalho - Árvore B                         *
*                                             *
* Feito por: Julia Gabriella Corrêa Silva     *
* RA: 0048842                                 *
**********************************************/

#ifndef RECORD_H
#define RECORD_H
#include <string>
#include "serializable.h"

using namespace std;

template <class T>
class record : public serializable { //Classe registro
   static_assert(is_base_of<serializable, T>::value, "T must be serializable");
   public:
      record(); //construtor defaut
      record(T d); //construtor parametrico
      record(const record<T> &other); //construtor de cópia
      virtual ~record(); //destrutor

      //metodos para sobrecarga de operadores
      record<T> operator=(const record<T> &other); //sobrecarga de = (atribuição)
      bool operator==(const record<T> &other); //sobrecarga de == (igualdade)

      //acessores
      T getData() const; //consultor para o data
      void setData(T d); //alteradores do data
      unsigned long long int getNext() const; //consultor para o next
      void setNext(unsigned long long int n); //alteradores do next
      bool isDeleted() const; //mostra se o registro foi deletado (get)
      void del(); //define deletado como true (set)
      void undel(); //define deletado como false (set)

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
      T data; //dado do tipo intserial
      bool deleted; //flag para indicar se o registro está na lista dos deletados
      unsigned long long int next; //apontador que guarda o numero do proximo registro
};

template <class T>
record<T>::record() : serializable() {
    T aux;

    data = aux;
    deleted = false;
    next = 0;
}

template <class T>
record<T>::record(T d) : serializable() {
    data = d;
    deleted = false;
    next = 0;
}

template <class T>
record<T>::record(const record<T> &other) {
    data = other.getData();
    deleted = other.isDeleted();
    next = other.getNext();
}

template <class T>
record<T>::~record() {
}

template <class T>
record<T> record<T>::operator=(const record<T> &other) {
    record<T> aux(other);

    data = other.getData();
    deleted = other.isDeleted();
    next = other.getNext();
    return aux;
}

template <class T>
bool record<T>::operator==(const record<T> &other) {
    return data == other.getData() && deleted == other.isDeleted() && next == other.getNext();
}

template <class T>
T record<T>::getData() const { //retorna o objeto intserial
    return data;
}

template <class T>
void record<T>::setData(T d) {
    data = d;
}

template <class T>
unsigned long long int record<T>::getNext() const {
    return next;
}

template <class T>
void record<T>::setNext(unsigned long long int n) {
    next = n;
}

template <class T>
bool record<T>::isDeleted() const {
    return deleted;
}

template <class T>
void record<T>::del() { //registro vai para lista dos excluidos
    deleted = true; //retorna true para marcar que o registro foi deletado
}

template <class T>
void record<T>::undel() { //registro vai para lista dos validos
    deleted = false; //retorna false para marcar que o registro não está deletado
}

template <class T>
string record<T>::toString() { //método para serializar o registro
    string aux = "";
    aux += data.toString();
    aux += string(reinterpret_cast<char*>(&deleted), sizeof(deleted));
    aux += string(reinterpret_cast<char*>(&next), sizeof(next));
    return aux;
}

template <class T>
void record<T>::fromString(string repr) { //método para desserializar o registro
    int pos = 0;
    int sizeD = data.size(); //pegando o tamanho
    string serializedR = repr.substr(pos,sizeD);
    data.fromString(serializedR);
    pos += sizeD;
    repr.copy(reinterpret_cast<char*>(&deleted), sizeof(deleted), pos);
    pos += sizeof(deleted);
    repr.copy(reinterpret_cast<char*>(&next), sizeof(next), pos);
    pos += sizeof(next);
}

template <class T>
unsigned long long int record<T>::size() const { //metodo para retornar o tamanho total do registro
    return data.size() + sizeof(bool) + sizeof(int);
}

#endif // RECORD_H
