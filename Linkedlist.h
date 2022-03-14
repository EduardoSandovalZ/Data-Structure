#include <iostream>
using namespace std;
// Programamos la clase nodo
class Node
{
public:
    int key, data;
    Node *next;

public:
    Node()
    {
        key = 0;
        data = 0;
        next = NULL;
    }
    Node(int k, int d)
    {
        key = k;
        data = d;
    }
};
// programamos la clase singly linked list
class Linkedlist
{
public:
    Node *head;

public:
    Linkedlist()
    {
        head = NULL;
    }
    Linkedlist(Node *n)
    {
        head = n;
    }
    // verificamos la existencia del nodo en la lista ligada
    Node *nodeExists(int k)
    {
        Node *temp = NULL;
        Node *ptr = head;
        while (ptr != NULL)
        {
            if (ptr->key == k)
            {
                temp = ptr;
            }
            ptr = ptr->next;
        }
        return temp;
    }
    void appendNode(Node *n)
    {
        if (nodeExists(n->key) != NULL)
        {
            cout << "El nodo ya existe con el valor: " << n->key << " Introduzca otro nodo con un valor diferente" << endl;
        }
        else
        {
            if (head == NULL)
            {
                head = n;
                cout << "El nodo ha sido agregado" << endl;
            }
            else
            {
                Node *ptr = head;
                while (ptr->next != NULL)
                {
                    ptr = ptr->next;
                }
                ptr->next = n;
                cout << "El nodo ha sido agregado" << endl;
            }
        }
    }
    // agregar un nodo al incio
    void prependNodes(Node *n)
    {
        if (nodeExists(n->key) != NULL)
        {
            cout << "El nodo ya existe con el valor: " << n->key << " Introduzca otro nodo con un valor diferente" << endl;
        }
        else
        {
            n->next = head;
            head = n;
            cout << "El nodo ha sido agregado" << endl;
        }
    }
    // instar un nodo despues de un nodo en especifico
    void insertNodeAfter(int k, Node *n)
    {
        Node *ptr = nodeExists(k);
        if (ptr == NULL)
        {
            cout << "El nodo con el valor " << k << " no existe" << endl;
        }
        else
        {
            if (nodeExists(n->key) != NULL)
            {
                cout << "El nodo ya existe con el valor: " << n->key << " Introduzca otro nodo con un valor diferente" << endl;
            }
            else
            {
                n->next = ptr->next;
                ptr->next = n;
                cout << "El nodo ha sido agregado" << endl;
            }
        }
    }
    void deleteNodeByKey(int k)
    {
        if (head == NULL)
        {
            cout << "La lista ligada esta vacia" << endl;
        }
        else if (head != NULL)
        {
            if (head->key == k)
            {
                head = head->next;
                cout << "El nodo: " << k << " ha sido eliminado" << endl;
            }
            else
            {
                Node *temp = NULL;
                Node *prevptr = head;
                Node *currentptr = head->next;
                while (currentptr != NULL)
                {
                    if (currentptr->key == k)
                    {
                        temp = currentptr;
                        currentptr = NULL;
                    }
                    else
                    {
                        prevptr = prevptr->next;
                        currentptr = currentptr->next;
                    }
                }
                if (temp != NULL)
                {
                    prevptr->next = temp->next;
                    cout << "El nodo: " << k << " ha sido eliminado" << endl;
                }
                else
                {
                    cout << "El nodo: " << k << " no existe" << endl;
                }
            }
        }
    }
    // actualizar nodo
    void updateNodeByKey(int k, int d)
    {
        Node *ptr = nodeExists(k);
        if (ptr != NULL)
        {
            ptr->data = d;
            cout << "La informacion del nodo ha sido actualizada" << endl;
        }
        else
        {
            cout << "El nodo: " << k << " no existe" << endl;
        }
    }
    // imprimir la lista
    void printList()
    {
        if (head == NULL)
        {
            cout << "La lista esta vacia" << endl;
        }
        else
        {
            cout << "\nValores de la lista ligada: " << endl;
            Node *temp = head;
            while (temp != NULL)
            {
                cout << "(" << temp->key << "," << temp->data << ") --> " << temp->data << endl;
                temp = temp->next;
            }
        }
    }
};
