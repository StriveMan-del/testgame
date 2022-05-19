//
// Created by Kirill on 17.05.2022.
//

#ifndef UNTITLED1_LIST_H
#define UNTITLED1_LIST_H

#include "Entity.h"

class List {
private:
    Entity* head;
    Entity* tail;
    size_t Size;
public:
    List();
    virtual ~List();
    Entity* back();
    void push_back(Entity* entity);
    Entity* remove(Entity*& entity);
    void clear();
    size_t size();
    bool empty();
    Entity* getHead();
    Entity* getPrev(Entity* entity);
    Entity* getNext(Entity* entity);
};


#endif //UNTITLED1_LIST_H
