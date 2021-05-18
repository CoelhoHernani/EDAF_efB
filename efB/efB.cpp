/* Estrutura de dados e algoritmos fundamentais
 * efolioA.cpp
 *
 *  Author: Hernani Coelho - 1800045
 *
 * Implementation file
 */

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <exception>


using namespace std;

//Excepção para lista vazia
struct EMPTYLIST : public exception {
    const char* what() const throw() {
        return "Lista vazia!";
    }
};

//Excepcão para posicões inválidas
struct INVALIDPOSITIONS : public exception {
    virtual const char* what() const throw() {
        return "Posicao invalida!";
    }
};


//Classe que representa cada nó da árvore binária
class BSTNODE {
private:
    int elemento;
    BSTNODE *esquerdo, *direito;
public:
    BSTNODE(int el);
    BSTNODE(int el, BSTNODE* esq, BSTNODE* dir);
    virtual ~BSTNODE();
    int getElemento();
    void setElemento(int el);
    BSTNODE* getNoEsquerdo();
    BSTNODE* getNoDireito();
    void setNoEsquerdo(BSTNODE* esq);
    void setNoDireito(BSTNODE* dir);
};

BSTNODE::BSTNODE(int el) {
    elemento = el;
    esquerdo = nullptr;
    direito = nullptr;
}

BSTNODE::BSTNODE(int el, BSTNODE* esq, BSTNODE* dir) {
    elemento = el;
    esquerdo = esq;
    direito = dir;
}

BSTNODE::~BSTNODE(){
    elemento = 0;
    esquerdo = nullptr;
    direito = nullptr;
}

int BSTNODE::getElemento() {
    return elemento;
}

void BSTNODE::setElemento(int el) {
    elemento = el;
}

BSTNODE* BSTNODE::getNoEsquerdo() {
    return esquerdo;
}

BSTNODE* BSTNODE::getNoDireito() {
    return direito;
}

void BSTNODE::setNoEsquerdo(BSTNODE* esq) {
    esquerdo = esq;
}

void BSTNODE::setNoDireito(BSTNODE* dir) {
    direito = dir;
}


//classe de representa a árvore binária
class BSTREE {
private:
    BSTNODE *raiz, *atual;
    void inOrder(BSTNODE* no);

public:
    BSTREE();
    virtual ~BSTREE();
    bool isEmpty();
    void insert(int el);
    void remove(int el);
    void printInOrder();
    int findParent(int el);
};

//algoritmo left root right LVR
void BSTREE::inOrder(BSTNODE* no) {
    if (no != nullptr) {
        inOrder(no->getNoEsquerdo());
        if (no == raiz)
            cout << no->getElemento() << " ";
        else
            cout << no->getElemento() <<"(" << findParent(no->getElemento()) << ")" << " ";
        inOrder(no->getNoDireito());
    }

}


BSTREE::BSTREE() {
    raiz = nullptr;
    atual = nullptr;
}

BSTREE::~BSTREE() {
    //definir remoção da arvore
}

//verifica se a arvore está vazia
bool BSTREE::isEmpty() {
    return raiz == nullptr; 
}

//inserir novo elemento na arvore
void BSTREE::insert(int el) {
    if (raiz == nullptr)
        raiz = new BSTNODE(el);
    else {
        BSTNODE* noSeguidor = nullptr, * noFrente = raiz;
        while (noFrente != nullptr) {
            noSeguidor = noFrente;
            if (el < noSeguidor->getElemento())
                noFrente = noSeguidor->getNoEsquerdo();
            else
                noFrente = noSeguidor->getNoDireito();
        }
        if (el < noSeguidor->getElemento()) {
            BSTNODE* esq = new BSTNODE(el);
            noSeguidor->setNoEsquerdo(esq);
        }
        else {
            BSTNODE* dir = new BSTNODE(el);
            noSeguidor->setNoDireito(dir);
        }
    }
}

void BSTREE::remove(int el) {

}

//precorre a lista na ordem left root right
void BSTREE::printInOrder() {
    inOrder(raiz); 
}

int BSTREE::findParent(int el) {
    int pai=-1;
    BSTNODE* no = raiz;
    while (no != nullptr && el != no->getElemento()) {
        pai = no->getElemento();
        if (el < no->getElemento())
            no = no->getNoEsquerdo();
        else
            no = no->getNoDireito();
    }
    return pai;
}

//Classe dos comandos que estão no ficheiro
class PAINEL {
private:
    string comando;
    string args;
    BSTREE* bst;
    //comandos como privados para não ser acessados fora da classe
    void insert();
    void print_inorder();
    void delete_();
    void clear();
    void rotate();
public:
    PAINEL();
    virtual ~PAINEL();
    void inserirComando(string comando);
    void inserirArgumentos(string arg);
    void executaComando();
};

void PAINEL::insert() {
    int aux;
    if (args != " ") {
        istringstream arg(args);
        while (arg >> aux) {
            bst->insert(aux);
        }
    }
    else {
        cout << "Comando " << comando << ": sem argumentos!" << endl;
    }
}

void PAINEL::print_inorder() {
    try {
        if (bst->isEmpty() == true)
            throw EMPTYLIST();
        cout << "Arvore= ";
        bst->printInOrder();
    }
    catch (EMPTYLIST& e) { //Se a lista estiver vazia então trata a excepção
        cout << "Comando " << comando << ": " << e.what() << endl;
    }
}

void PAINEL::delete_() {

}

void PAINEL::clear() {

}

void PAINEL::rotate() {

}

//Construtor do menu
PAINEL::PAINEL() {
    bst = new BSTREE();
    this->comando = "";
    this->args = "";
}

//Destrutor 
PAINEL::~PAINEL() {


}

//Inserir os camandos 
void PAINEL::inserirComando(string comando) {
    this->comando = comando;
}

//insere os argumentos
void PAINEL::inserirArgumentos(string arg) {
    this->args = arg;
}

//Executa o comando respectivo
void PAINEL::executaComando() {
    if (comando == "insert")
        insert();
    else if (comando == "print_inorder")
        print_inorder();
    else if (comando == "delete_")
        delete_();
    else if (comando == "clear")
        clear();
    else if (comando == "rotate")
        rotate();        
    else
        cout << "Comando inválido!" << endl;
}



class PROCESSARDADOS {
private:
    PAINEL* painelComandos;
public:
    PROCESSARDADOS();
    virtual ~PROCESSARDADOS();
    void lerFicheiro();
};

PROCESSARDADOS::PROCESSARDADOS() {
    painelComandos = new PAINEL();
    lerFicheiro();
}

PROCESSARDADOS::~PROCESSARDADOS() {
    delete(painelComandos);
}

void PROCESSARDADOS::lerFicheiro() {
    string linha;
    /*while (getline(cin, linha)) {           //ler cin
        if (linha.substr(0, 1) == "#" || linha == "") { //ignora linha vazia ou comentada
            continue;
        }
        int pos = linha.find_first_of(" ", 0);  //verifica posição do último caracter do comando
        painelComandos->inserirComando(linha.substr(0, pos)); //captura nome do comando
        pos = linha.find_first_not_of(" ", pos);    //verifica primeiro caracter após a posição anterior
        if (pos != -1) {
            painelComandos->inserirArgumentos(linha.substr(pos, linha.size())); // Se a posição for válida copia os arg para o painel de comandos
        }
        painelComandos->executaComando();
    }*/


    fstream file;
    file.open("cmd.txt", ios::in);
    while (getline(file, linha)) { //L� o ficheiro at� ao final
        if (linha.substr(0, 1) == "#" || linha == "") {
            continue;//Verifica se � uma linha vazia ou comentada e ignora
        }
        int pos = linha.find_first_of(" ", 0);//Procura o primeiro espa�o para verificar onde termina o nome do comando
        painelComandos->inserirComando(linha.substr(0, pos)); //Insere o nome do comando na interface
        pos = linha.find_first_not_of(" ", pos);//Procura o ultimo espa�o ap�noSeguidor a posi��o anterior para verificar onde come�a os argumentos
        if (pos != -1) {
            painelComandos->inserirArgumentos(linha.substr(pos, linha.size())); // Se a posi��o for v�lida copia os argumentos para a interface
        }
        painelComandos->executaComando(); //Executa o comando
    }
    file.close();
}

int main() {

    //Objeto que trata execução do programa
    PROCESSARDADOS PROCESSARDADOS;

    return 0;
}
//Fim do Código IDE*/