/**********************************************
* Trabalho - Árvore B                         *
*                                             *
* Feito por: Julia Gabriella Corrêa Silva     *
* RA: 0048842                                 *
**********************************************/
#include "header.h"

header::header() : serializable() {
   type = "";
   rootR = 0;
   firstDeleted = 0;
   firstValid = 0;
   version = 0;
}

header::header(const string t, unsigned int v) : serializable() {
   type = t.substr(0, 3); //pega os três primeiros caracteres
   rootR = 0;
   firstDeleted = 0;
   firstValid = 0;
   version = v;
}

header::header(const header &h) {
   type = h.getType();
   rootR = h.getRoot();
   firstDeleted = h.getFirstDeleted();
   firstValid = h.getFirstValid();
   version = h.getVersion();
}

header::~header() {}

header header::operator=(const header &h) {
   header aux(h);
   if (this == &h)
      return *this;

   type = h.getType();
   rootR = h.getRoot();
   firstDeleted = h.getFirstDeleted();
   firstValid = h.getFirstValid();
   version = h.getVersion();
   return aux;
}

bool header::operator==(const header &h) {
   return type == h.getType() && rootR == h.getRoot() && version == h.getVersion() && firstDeleted == h.getFirstDeleted() && firstValid == h.getFirstValid();
}

unsigned long long int header::getFirstDeleted() const {
   return firstDeleted;
}

void header::setFirstDeleted(unsigned long long int r) {
   firstDeleted = r;
}

unsigned long long int header::getFirstValid() const {
   return firstValid;
}

void header::setFirstValid(unsigned long long int r) {
   firstValid = r;
}

unsigned long long int header::getRoot() const{
    return rootR;
}

void header::setRoot(unsigned long long int r){
    rootR = r;
}

string header::getType() const {
   return type;
}

void header::setType(string t) {
   type = t.substr(0, 3);
}

unsigned int header::getVersion() const {
   return version;
}

void header::setVersion(unsigned int v) {
   version = v;
}

string header::toString() { //método para serializar o cabeçalho
   string aux = "";

   aux += type;
   //passando os objetos para string como uma sequência de bytes, junto com a contagem de bytes
   aux += string(reinterpret_cast<char*>(&version), sizeof(version));
   aux += string(reinterpret_cast<char*>(&rootR), sizeof(rootR));
   aux += string(reinterpret_cast<char*>(&firstValid), sizeof(firstValid));
   aux += string(reinterpret_cast<char*>(&firstDeleted), sizeof(firstDeleted));
   return aux;
}

void header::fromString(string repr) { //método para desserializar o cabeçalho
   int pos = 0;

   type = repr.substr(pos, 3); //recebe os três primeiros caracteres
   pos += type.length(); //pos vai receber o comprimento da string type
   repr.copy(reinterpret_cast<char*>(&version), sizeof(version), pos); //copia da string para o atributo versão
   pos += sizeof(version); //adicionando no pos o tamanho a contagem de bytes da versão
   repr.copy(reinterpret_cast<char*>(&rootR), sizeof(rootR), pos); //copia da string para o atributo raiz
   pos += sizeof(rootR); //adicionando no pos o tamanho a contagem de bytes da raiz
   repr.copy(reinterpret_cast<char*>(&firstValid), sizeof(firstValid), pos); //copia da string para o atributo primeiro valido
   pos += sizeof(firstValid); //adicionando no pos o tamanho a contagem de bytes do primeiro valido
   repr.copy(reinterpret_cast<char*>(&firstDeleted), sizeof(firstDeleted), pos); //copia da string para o atributo primeiro deletado
}

unsigned long long int header::size() const { //metodo para retornar o tamanho total do cabeçalho
   return type.length() + sizeof(version) + sizeof(rootR) + sizeof(firstValid) + sizeof(firstDeleted); //retorna o tamanho de 23 bytes
}
