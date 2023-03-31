#ifndef LINKED_LIST_H
#define LINKED_LIST_H

class Blue_Enemy_Hard;
class Blue_Enemy;
class Red_Enemy;
class Red_Enemy_Hard;

class Node
{
public:
    Red_Enemy *red_enemy = nullptr;
    Blue_Enemy *blue_enemy = nullptr;
    Red_Enemy_Hard *red_hard_enemy = nullptr;
    Blue_Enemy_Hard *blue_hard_enemy = nullptr;

    Node* next;

    Node(Red_Enemy *red_enemy);
    Node(Red_Enemy_Hard *red_hard_enemy);
    Node(Blue_Enemy *blue_enemy);
    Node(Blue_Enemy_Hard *blue_hard_enemy);
};

class Linkedlist {


public:
    Node* head;
    Linkedlist() { head = nullptr; }
    void insertNode(Red_Enemy *red_enemy);
    void insertNode(Red_Enemy_Hard *red_hard_enemy);
    void insertNode(Blue_Enemy *blue_enemy);
    void insertNode(Blue_Enemy_Hard *blue_hard_enemy);
    void printList();
    void deleteNode(int);
};

#endif // LINKED_LIST_H
