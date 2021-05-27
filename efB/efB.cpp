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
        return "Arvore vazia!";
    }
};

//Excepcão para posicões inválidas
struct INVALIDPOSITIONS : public exception {
    virtual const char* what() const throw() {
        return "Item inexistente!";
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
    int sinal;
    void inOrder(BSTNODE* no);

public:
    BSTREE();
    virtual ~BSTREE();
    bool isEmpty();
    void insert(int el);
    void remove(int el);
    void printInOrder();
    void clear();
    void clearTree(BSTNODE* no);
    void rotateTree(int el);
    void leftRotation(BSTNODE* pai, BSTNODE* no, BSTNODE* avo);
    void leftRightRotation(BSTNODE* pai, BSTNODE* no, BSTNODE* avo);
    void rightRotation(BSTNODE* pai, BSTNODE* no, BSTNODE* avo);
    void rightLeftRotation(BSTNODE* pai, BSTNODE* no, BSTNODE* avo);
    BSTNODE* findNode(int el);
    BSTNODE* findParentNode(int el);
    BSTNODE* findAntecessor(BSTNODE* no);
    BSTNODE* findSucessor(BSTNODE* no);
};

//algoritmo getNoEsquerdo() root getNoDireito() LVR
void BSTREE::inOrder(BSTNODE* no) {
    if (no != nullptr) {
        inOrder(no->getNoEsquerdo());
        if (no == raiz)
            cout << no->getElemento() << " ";
        else {
            BSTNODE* temp = findParentNode(no->getElemento());
            cout << no->getElemento() << "(" << temp->getElemento() << ")" << " ";
        }
        inOrder(no->getNoDireito());
    }

}


BSTREE::BSTREE() {
    sinal = 0;
    raiz = nullptr;
    atual = nullptr;
}

BSTREE::~BSTREE() {
    clear();
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
    BSTNODE* no = findNode(el), * pai = findParentNode(el), * noSucAnt, * paiAntSuc;
    if (no != nullptr) {
        if (this->sinal == 0)
            noSucAnt = findAntecessor(no);
        else
            noSucAnt = findSucessor(no);
        if (no->getNoDireito() == nullptr && no->getNoEsquerdo() == nullptr) {
            if (pai->getNoEsquerdo() == no)
                pai->setNoEsquerdo(nullptr);
            else
                pai->setNoDireito(nullptr);
        }
        paiAntSuc = findParentNode(noSucAnt->getElemento());
        if (paiAntSuc->getNoDireito() == noSucAnt && noSucAnt != no)
            paiAntSuc->setNoDireito(noSucAnt->getNoDireito());
        else if (paiAntSuc->getNoEsquerdo() == noSucAnt && noSucAnt != no)
            paiAntSuc->setNoEsquerdo(noSucAnt->getNoEsquerdo());
        else if (noSucAnt == no && no->getNoDireito() == nullptr)
            pai->setNoDireito(no->getNoEsquerdo());
        else if (noSucAnt == no && no->getNoEsquerdo() == nullptr)
            pai->setNoEsquerdo(no->getNoDireito());
        no->setElemento(noSucAnt->getElemento()); // copiar para o no o valor do elemento sucessor ou antecessor
        delete(noSucAnt);
    }
    else
        //lança a excepção com o valor do elemento inexistente
        throw el;
}

void BSTREE::clearTree(BSTNODE* no) {
    if (no == nullptr) {
        return;
    }
    // elimina arvore utilizando a recursão em  postorder
    clearTree(no->getNoEsquerdo());
    clearTree(no->getNoDireito());
    delete no;
    no = nullptr;
}

void BSTREE::clear() {
    clearTree(raiz);
}

void BSTREE::rotateTree(int el) {
    BSTNODE* no = findNode(el), *pai = findParentNode(el), *avo;

    if (no != nullptr) {
        if (no == raiz)
            return;
        avo = findParentNode(pai->getElemento());
        if (pai->getNoDireito() == no && (avo == nullptr || avo->getNoDireito() == pai))
            leftRotation(pai, no, avo);
        else if (pai->getNoEsquerdo() == no && (avo == nullptr || avo->getNoEsquerdo() == pai))
            rightRotation(pai, no, avo);
        else if (pai->getNoDireito() == no && avo->getNoEsquerdo() == pai)
            leftRightRotation(pai, no, avo);
        else if (pai->getNoEsquerdo() == no && avo->getNoDireito() == pai)
            rightLeftRotation(pai, no, avo);
    }
    else
        //lança a excepção com o valor do elemento inexistente
        throw el;

}

//Rotação para esquerda na subarvore direita
void BSTREE::leftRotation(BSTNODE* pai, BSTNODE* no, BSTNODE* avo) {
    //caso 1. avo não é null
    if (avo != nullptr) {
        avo->setNoDireito(no);
        pai->setNoDireito(no->getNoEsquerdo());
        no->setNoEsquerdo(pai);
    }
    //caso 2. avo é null
    else {
        pai->setNoDireito(no->getNoEsquerdo());
        no->setNoEsquerdo(pai);
        raiz = no;
    }

}

//rotacao para esquerda quando no esta na subarvore esquerda direita
void BSTREE::leftRightRotation(BSTNODE* pai, BSTNODE* no, BSTNODE* avo) {
    avo->setNoEsquerdo(no);
    pai->setNoDireito(no->getNoEsquerdo());
    no->setNoEsquerdo(pai);
}

//Rotação para direita na subarvore esquerda
void BSTREE::rightRotation(BSTNODE* pai, BSTNODE* no, BSTNODE* avo) {
    //caso 1. avo não é null
    if (avo != nullptr) {
        avo->setNoEsquerdo(no);
        pai->setNoEsquerdo(no->getNoDireito());
        no->setNoDireito(pai);
    }
    //caso 2. avo é null
    else {
        pai->setNoEsquerdo(no->getNoDireito());
        no->setNoDireito(pai);
        raiz = no;
    }
}

//rotacao para direita quando no esta na subarvore direita esquerda
void BSTREE::rightLeftRotation(BSTNODE* pai, BSTNODE* no, BSTNODE* avo) {
    avo->setNoDireito(no);
    pai->setNoEsquerdo(no->getNoDireito());
    no->setNoDireito(pai);
}

//precorre a lista na ordem getNoEsquerdo() root getNoDireito()
void BSTREE::printInOrder() {
    inOrder(raiz); 
}

//Encontra o no que tem o elemento do argumento
BSTNODE* BSTREE::findNode(int el) {
    BSTNODE* no = raiz;
    while (no != nullptr && el != no->getElemento()) {
        if (el < no->getElemento())
            no = no->getNoEsquerdo();
        else
            no = no->getNoDireito();
    }
    return no;
}

//Encontra o no que é pai do no que tem o elemento do argumento
BSTNODE* BSTREE::findParentNode(int el) {
    BSTNODE* no = raiz, *pai = nullptr;
    while (no != nullptr && el != no->getElemento()) {
        pai = no;
        if (el < no->getElemento())
            no = no->getNoEsquerdo();
        else
            no = no->getNoDireito();
    }
    return pai;
}

//Encontra no antecessor do no passado como argumento
//antecessor arvore esquerda elemento mais direita
BSTNODE* BSTREE::findAntecessor(BSTNODE* no) {
    BSTNODE* antecessor = no;
    this->sinal = 1;
    if (no->getNoEsquerdo() != nullptr) {
        antecessor = no->getNoEsquerdo();
        while (antecessor->getNoDireito() != nullptr)
            antecessor = antecessor->getNoDireito();
    }
    return antecessor;
}

//Encontra no sucessor do no passado como argumento
//Sucessor arvore direita elemento mais esquerda
BSTNODE* BSTREE::findSucessor(BSTNODE* no) {
    BSTNODE* sucessor = no;
    this->sinal = 0;
    if (no->getNoDireito() != nullptr) {
        sucessor = no->getNoDireito();
        while (sucessor->getNoEsquerdo() != nullptr)
            sucessor = sucessor->getNoEsquerdo();
    }
    return sucessor;
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
        cout << endl;
    }
    catch (EMPTYLIST& e) { //Se a arvore estiver vazia então trata a excepção
        cout << "Comando " << comando << ": " << e.what() << endl;
    }
}

void PAINEL::delete_() {
    try {
        if (bst->isEmpty() == true)
            throw EMPTYLIST();
        int aux;
        if (args != " ") {
            istringstream arg(args);
            while (arg >> aux)
                bst->remove(aux);
        }
    }
    catch (EMPTYLIST& e) { //Se a arvore estiver vazia então trata a excepção
        cout << "Comando " << comando << ": " << e.what() << endl;
    }
    catch (int i) {     //Se item não existir então trata a excepção
        cout << "Comando " <<comando << ": Item " << i <<" inexistente!" << endl;
    }
}

void PAINEL::clear() {
    try {
        if (bst->isEmpty() == true)
            throw EMPTYLIST();
        bst->clear();
    }
    catch (EMPTYLIST& e) { //Se a arvore estiver vazia então trata a excepção
        cout << "Comando " << comando << ": " << e.what() << endl;
    }
}

void PAINEL::rotate() {
    try {
        if (bst->isEmpty() == true)
            throw EMPTYLIST();
        int aux;
        if (args != " ") {
            istringstream arg(args);
            while (arg >> aux)
                bst->rotateTree(aux);
        }
    }
    catch (EMPTYLIST& e) { //Se a arvore estiver vazia então trata a excepção
        cout << "Comando " << comando << ": " << e.what() << endl;
    }
    catch (int i) {     //Se item não existir então trata a excepção
        cout << "Comando " << comando << ": Item " << i << " inexistente!" << endl;
    }
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
    else if (comando == "delete")
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