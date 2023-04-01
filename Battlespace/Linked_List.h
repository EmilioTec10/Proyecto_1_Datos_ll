#ifndef LINKED_LIST_H
#define LINKED_LIST_H

class Blue_Enemy_Hard;
class Blue_Enemy;
class Red_Enemy;
class Red_Enemy_Hard;

class Node
{
public:
    //Data of the node
    Node* next;
    int token;
    Red_Enemy *red_enemy = nullptr;
    Blue_Enemy *blue_enemy = nullptr;
    Red_Enemy_Hard *red_hard_enemy = nullptr;
    Blue_Enemy_Hard *blue_hard_enemy = nullptr;

    //Main methods
    Node(Red_Enemy *red_enemy);
    Node(Red_Enemy_Hard *red_hard_enemy);
    Node(Blue_Enemy *blue_enemy);
    Node(Blue_Enemy_Hard *blue_hard_enemy);
};

class Linkedlist
{
public:
    Linkedlist() { head = nullptr; };

    Node* head;

    void insertNode(Red_Enemy *red_enemy, int token);
    void insertNode(Red_Enemy_Hard *red_hard_enemy, int token);
    void insertNode(Blue_Enemy *blue_enemy, int token);
    void insertNode(Blue_Enemy_Hard *blue_hard_enemy, int token);

    void printList();

    void deleteNode(Blue_Enemy *blue_enemy);
    void deleteNode(Red_Enemy *red_enemy);
    void deleteNode(Blue_Enemy_Hard *blue_hard_enemy);
    void deleteNode(Red_Enemy_Hard *red_hard_enemy);
};

#endif // LINKED_LIST_H
