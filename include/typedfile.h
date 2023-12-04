/**********************************************
* Trabalho - Árvore B                         *
*                                             *
* Feito por: Julia Gabriella Corrêa Silva     *
* RA: 0048842                                 *
**********************************************/

#ifndef TYPEDFILE_H
#define TYPEDFILE_H
#include "record.h"
#include "header.h"
#include <fstream>
#include <type_traits>

using namespace std;

const ios::openmode mode = ios::in | ios::out | ios::binary;

template <class T>
class typedFile : private fstream { //CLasse arquivo
   static_assert(is_base_of<serializable, T>::value, "T must be serializable"); //essa função veririca se o tipo T é uma classe que herdou a serializable
   public:
      typedFile(); //construtor defaut
      typedFile(const string name, const string type, const unsigned int version, ios::openmode openmode = mode); //construtor parametrico
      virtual ~typedFile(); //destrutor
      bool open(const string name, const string type, const unsigned int version, ios::openmode openmode = mode); //metodo para abrir o arquivo
      bool isOpen(); //metodo para conferir se o arquivo esta aberto
      bool close(); //metodo para fechar o arquivo
      bool clear(); //metodo para limpar o arquivo
      bool readRecord(record<T> &r, unsigned long long int i); //metodo para ler o registro
      bool writeRecord(record<T> &r, unsigned long long int i); //metodo para escrever o registro
      bool insertRecord(record<T> &r); //metodo para criar e inserir o registro
      bool deleteRecord(unsigned long long int i); //metodo para excluir o registro
      unsigned long long int getRoot();  //acessar o primeiro valido
      unsigned long long int getFirstValid();  //acessar o primeiro valido
      unsigned long long int getFirstDeleted(); //acessar o prmeiro invalido
      unsigned long long int search(T data); //metodo para buscar o registro
   protected:
      header head; //cabeçalho
      bool readHeader(header &h); //le o cabeçalho
      bool writeHeader(header &h); //escreve o cabeçalho
      unsigned long long int index2pos(unsigned long long int i); //transformar o indice na posição
      unsigned long long int pos2index(unsigned long long int p); //trasformar a posição no indice
};

template <class T>
typedFile<T>::typedFile() : fstream() {
    header aux;

    head = aux;
    readHeader = false;
    writeHeader = false;
    index2pos = 0;
    pos2index = 0;
}

template <class T>
typedFile<T>::typedFile(const string name, const string type, const unsigned int version, ios::openmode openmode) : fstream(name.c_str(), mode) {
    open(name, type, version, openmode);
}

template <class T>
typedFile<T>::~typedFile() {
}

template <class T>
bool typedFile<T>::open(const string name, const string type, const unsigned int version, ios::openmode openmode) {
    if(!isOpen()) { //se o arquivo não existir
        header h;
        h.setVersion(version);
        h.setType(type);
        this->head = h;
       // head.setVersion(version); //setando a versão
        //head.setType(type); //setando o tipo
        fstream::open(name, ios::out); //abrindo o arquivo somente com a flag de escrita para que seja criado
        close(); //fechando o arquivo
        fstream::open(name, openmode); //reabrindo com as flags originais
        writeHeader(head); //escrevendo o cabeçalho
    }else{ //se o arquivo existir
        readHeader(head); //ler cabeçalho
    }
    return true;
}

template <class T>
bool typedFile<T>::isOpen() { //abrindo o arquivo
    return fstream::is_open();
}

template <class T>
bool typedFile<T>::close() { //fechando o arquivo
    fstream::close();
    return true;
}

template <class T>
bool typedFile<T>::clear() { //limpando o arquivo
    fstream::clear();
    return true;
}

template <class T>
bool typedFile<T>::readRecord(record<T> &r, unsigned long long int i) { //desserialização do registro
    if(isOpen() && i != 0){ // verificando se o arquivo esta aberto e o numero do registro é diferente de 0
        int sizeR = r.size();// pegando o tamanho do registro
        char *auxR = new char[sizeR]; //ponteiro de char com o tamanho do registro para guardar o conteúdo desserializado
        string serializedR = "";
        seekg(index2pos(i), ios::beg); //posicionando a cabeça de leitura na posição do arquivo
        read(auxR, sizeR); //fazendo a leitura para o buffer de auxR
        serializedR = string(auxR, sizeR); //atribuindo à string com a representação, passando o tamanho da string a ser criada
        r.fromString(serializedR); //passando serializedR para o método fromString, para que o objeto seja desserializado
        //evitando memory leaking
        delete[] auxR; //operador para excluir
        auxR = NULL; //aux recebe null
        return true;
    }
    return false;
}

template <class T>
bool typedFile<T>::writeRecord(record<T> &r, unsigned long long int i) { //serialização do registro
    if(isOpen()){ //verificando se o arquivo está aberto
        int sizeR = r.size(); //pegando o tamanho do registro
        string serializedR = r.toString(); //serializando o registro

        seekp(index2pos(i), ios::beg); //posicionando a cabeça de escrita
        write(serializedR.c_str(), sizeR); //gravação do objeto serializado
        return true;
    }
    return false;
}

template <class T>
bool typedFile<T>::insertRecord(record<T> &r){ //insere o registro
    if(isOpen()){ //verificando se o arquivo está aberto
        unsigned long long int firstDeleted = head.getFirstDeleted(); //firstDeleted recebe a cabeça da lista de excluidos
        unsigned long long int firstValid = head.getFirstValid(); //firstValid recebe a cabeça da lista de validos
        record<T> auxR; //registro auxiliar

        if(firstDeleted == 0){ //aumentar o tamanho do arquivo
            r.setNext(firstValid); //o registro inserido vai apontar pra cabeça da lista dos validos
            seekp(0, ios::end); //possicionando a cabeça de escrita no final
            head.setFirstValid(pos2index(tellp())); //cabeça da lista dos validoa recebe o número do registro a partir da posição do ponteiro da escrita
            writeRecord(r, pos2index(tellp())); //ecrevendo o registro
        }else{ //reciclar o registro
            readRecord(auxR, firstDeleted); //lendo o registro e sua posição na lista de deletados
            auxR.undel(); //colocando na lista de validos
            head.setFirstValid(firstDeleted); //ponteiro da cabeça da lista de validos está recebendo a cabeça da lista dos registros excluídos
            head.setFirstDeleted(auxR.getNext()); //ponteiro da cabeça da lista de excluidos esta fazendo o cabeçalho apontar para o proximo registro como nova cabeça
            auxR.setNext(firstValid); //o registro vai apontar pro proximo da cabeça da lista dos validos
            auxR.setData(r.getData()); //recebendo o valor do registro inserido
            writeRecord(auxR, firstDeleted); //escrevendo o registro
       }
        writeHeader(head); //serializando o cabeçalho
        return true;
    }else{
        return false;
    }
}

template <class T>
bool typedFile<T>::deleteRecord(unsigned long long int i) { //exclui o registro
    if (isOpen()){ //verificando se o arquivo está aberto
        unsigned long long int firstDeleted = head.getFirstDeleted(); //firstDeleted recebe a cabeça da lista de excluidos
        unsigned long long int firstValid = head.getFirstValid(); //firstValid recebe a cabeça da lista de validos
        unsigned long long int next; //variavel para salvar auxR.getNext()
        record<T> auxR; //registro auxiliar 1
        record<T> auxR2; //registro auxiliar 2

        if(i == firstValid){ //verificamos se o registro que será removido é a cabeça da lista dos validos
            readRecord(auxR, firstValid); //lendo firstValid para auxR
            auxR.del(); //colocando na lista de deletados
            head.setFirstValid(auxR.getNext()); //ponteiro da cabeça da lista de validos esta fazendo o cabeçalho apontar para o proximo registro como nova cabeça
            head.setFirstDeleted(firstValid); //ponteiro da cabeça da lista de excluidos está recebendo a cabeça da lista dos registros validos
            auxR.setNext(firstDeleted); //registro aponta pro proximo da cabeça da lista dos excluidos
            writeRecord(auxR, firstValid); //escrevendo o registro
        }else{ //se o registro não for a cabeça dos validos, verificamos ao longo da lista
            while(auxR.getNext() != i && readRecord(auxR, firstValid)) { //verifico se o proximo registro é diferente de i e leio firstValid para auxR
                if (auxR.getNext() == i){ //verificando se o proximo é o registro procurado
                    readRecord(auxR2, auxR.getNext()); //leio o proximo registro para auxR2
                    auxR2.del(); //colocando na lista de deletados
                    next = auxR.getNext(); //next guarda a posção auxR.getNext
                    auxR.setNext(auxR2.getNext()); //registro anterior aponta para o proximo
                    auxR2.setNext(firstDeleted); //registro aponta pro proximo da cabeça da lista dos excluidos
                    head.setFirstDeleted(next); //registro removido aponta para a cabeça dos excuidos
                    writeRecord(auxR2, next); //escrevendo o registro auxr2
                    writeRecord(auxR, firstValid); //escrevendo o registro auxr
                    return true;
                }else{
                    firstValid = auxR.getNext(); //firstValid recebe o proximo registro
                }
            }
        }
        if(writeHeader(head)){ //serializando o cabeçalho
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
}

template <class T>
unsigned long long int typedFile<T>::getRoot() {
    return head.getRoot(); //retorna a raz
}

template <class T>
unsigned long long int typedFile<T>::getFirstValid() {
    return head.getFirstValid(); //retorna a cabeça dos validos
}

template <class T>
unsigned long long int typedFile<T>::getFirstDeleted() {
    return head.getFirstDeleted(); //retorna a cabeça dos excluidos
}

template <class T>
unsigned long long int typedFile<T>::search(T data) { //busca o registro na lista dos validos
    if (isOpen()){ //verifico se o arquivo esta aberto
        unsigned long long int firstValid = head.getFirstValid(); //firstValid recebe a cabeça da lista dos validos
        record<T> r; //registro auxiliar

        while(readRecord(r, firstValid)){ //lendo o primeiro valido para r
            if(r.getData() == data){ //se o valor registro r for igual ao registro data
                return firstValid; //retorna a posição deste registro
            }else{
                firstValid = r.getNext(); //firstValid recebe o proximo registro
            }
        }
        return 0; //retorna 0 se caso o registro não for encontrado
    }else{
        return 0;
    }
}

template <class T>            //h = cabeçalho
bool typedFile<T>::readHeader(header &h) { //desserializa o cabeçalho
    if(isOpen()){ //verificando se o arquivo está aberto
        unsigned long long int sizeH = h.size(); //pegando o tamanho do cabeçalho
        char *auxH = new char[sizeH]; //ponteiro de char com o tamanho do cabeçalho para guardar o conteúdo desserializado
        string serializedH;

        seekg(0, ios::beg); //posicionando a cabeça de leitura no primeiro byte do arquivo4
        read(auxH, sizeH); //fazendo a leitura para o buffer de auxH
        serializedH = string(auxH, sizeH); //atribuindo à string com a representação, passando o tamanho da string a ser criada
        h.fromString(serializedH); //passando serializedH para o método fromString, para que o objeto seja preenchido com os dados obtidos em disco (desserializando)

        //Evitando memory leaking
        delete[] auxH; //operador para excluir
        auxH = NULL; //aux recebe null
        return true;
    }
    return false;
}

template <class T>             //h = cabecalho
bool typedFile<T>::writeHeader(header &h) { //serializa o cabeçalho
    if(isOpen()){ //verificando se o arquivo está aberto
        int sizeH = h.size(); //pegando o tamanho do cabeçalho
        string serializedH = h.toString(); //serializando o cabeçalho

        seekp(0, ios::beg); //posicionando a cabeça de escrita no primeiro byte do arquivo, a partir do início
        write(serializedH.c_str(), sizeH); //gravação do objeto serializado
        return true;
    }
    return false;
}

template <class T>                             //numero do registro
unsigned long long int typedFile<T>::index2pos(unsigned long long int i) { //retorna a posição do registro, a apartir do número do registro
    record<T> rec;
    int pos, r = rec.size();

    pos = head.size() + (i - 1) * r;
    return pos;
}

template <class T>                             //posição
unsigned long long int typedFile<T>::pos2index(unsigned long long int p) { //retorna o número do registro, a apartir da posição do registro
    record<T> rec;
    int n, r = rec.size();

    n = (p - head.size())/r + 1;
    return n; //retorna
}
#endif // TYPEDFILE_H
