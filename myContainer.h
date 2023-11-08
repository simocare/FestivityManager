#ifndef MYCONTAINER_H
#define MYCONTAINER_H

template <class T, class P>
class myContainer {
private:
    class nodo {
    public:
        T firstInfo;
        P secondInfo;
        nodo* next;

        nodo(const T& t, const P& p, nodo* n = nullptr) : firstInfo(t), secondInfo(p), next(n) {}
    };

    nodo* first;

    //copia della prima lista in una seconda
    static void copy(nodo* f1, nodo*& f2) {
        if(!f1) {
            f2 = nullptr;
        } else {
            while(f1) {
                f2 = new nodo(f1->firstInfo, f1->secondInfo);
                f1 = f1->next;
                f2 = f2->next;
            }
        }
    }

    static void destroy(nodo* f) {
        if(f) {
            destroy(f->next);
            delete f;
        }
    }

public:
    myContainer() : first(nullptr) {}

    myContainer(const T& t, const P& p) : first(new nodo(t, p)) {}

    myContainer(const myContainer& c) : first(nullptr) { 
        if (this != &c) {
            destroy(first);
            copy(c.first, first);
        }
     }

    ~myContainer() { destroy(first); }

    myContainer& operator=(const myContainer& c) {
        if(this != &c) {    //controllo che non stia facendo l'assegnazione di un oggetto a se stesso
            destroy(first); //dealloco il contenuto di this
            copy(c.first, first);  //copio il contenuto di c
        }
        return *this;
    }

    //isert (back)
    void insert(const T& t, const P& p) {
        if(first == nullptr) {
            first = new nodo(t, p);
        } else {
            nodo* temp = first;
            while(temp->next) {
                temp = temp->next;
            }
            temp->next = new nodo(t, p);
        }
    }

    void remove(const T& t) {
        if(first) {
            if(first->firstInfo == t) { //se il primo nodo è da eliminare
                nodo* temp = first;
                first = first->next;
                delete temp;
            } else {
                nodo* temp = first;
                while(temp->next && temp->next->firstInfo != t) {
                    temp = temp->next;
                }

                if(temp->next) {                    //se il nodo da eliminare esiste
                    nodo* temp2 = temp->next;       //lo salvo in un puntatore
                    temp->next = temp->next->next;  //aggiorno il next del nodo precedente
                    delete temp2;
                }
            }
        }
    }

    class const_iterator {
        friend class myContainer<T, P>; //per poter accedere ai membri privati di myContainer
    
    private:
        const nodo* ptr; //puntatore costante al nodo corrente
        bool pastTheEnd; //indica se l'iteratore è "oltre la fine" della lista

        const_iterator(nodo* p, bool b=false) : ptr(p), pastTheEnd(b) {}

    public:
        const_iterator() : ptr(nullptr), pastTheEnd(false) {}

        const_iterator& operator++() {
            if(ptr && !pastTheEnd) {
                if(ptr->next) {
                    ptr = ptr->next;
                } else {
                    pastTheEnd = true;
                }
            }
            return *this;
        }

        const_iterator operator++(int) {
            const_iterator temp(*this);
            if(ptr && !pastTheEnd) {
                if(ptr->next) {
                    ptr = ptr->next;
                } else {
                    pastTheEnd = true;
                }
            }
            return temp;
        }

        //non viene definito l'operatore -- perché non è necessario. La lista è fatta per essere acceduta solo in avanti
    
        bool operator==(const const_iterator& it) const {
            return ptr == it.ptr && pastTheEnd == it.pastTheEnd;
        }

        bool operator!=(const const_iterator& it) const {
            return ptr != it.ptr || pastTheEnd != it.pastTheEnd;
        }

        const T& firstInfo() const {
                return ptr->firstInfo;
        }

        const P& secondInfo() const {
            return ptr->secondInfo;
        }

        bool isPastTheEnd() const {
            return pastTheEnd;
        }
    };

    const_iterator begin() const {
        return const_iterator(first);
    }

    //da non utilizzare per scorrere la lista, perché è costoso
    //metodo che mi restituisce l'ultimo elemento
    const_iterator end() const {
        if(first) {
            nodo* temp = first;
            while(temp->next) {
                temp = temp->next;
            }
            return const_iterator(temp, true);
        } else {
            return const_iterator(nullptr, true);
        }
    }

    const_iterator find(const T& t) const {
        if (isEmpty()) throw std::runtime_error("myContainer::find() container vuoto"); 
        nodo* temp = first;
        while(temp && temp->firstInfo != t) {
            temp = temp->next;
        }
        return const_iterator(temp);
    }

    bool isEmpty() const {
        return first == nullptr;
    }
};

#endif