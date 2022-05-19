//
// Created by Kirill on 17.05.2022.
//

#include "List.h"

List::List() {
    this->Size = 0;
    this->head = this->tail = NULL;
}

List::~List(){
   while(this->head){
       this->remove(this->tail);
   }
}

void List::push_back(Entity* entity){

    if (this->head){
        entity->prev = this->tail;
        this->tail->next = entity;
        this->tail = entity;
        this->tail->next = NULL;
        this->Size++;
    }else{
        entity->prev = NULL;
        entity->next = NULL;
        this->head = this->tail = entity;
        this->Size++;
    }
}
Entity* List::back(){
    return this->tail;
}

Entity* List::remove(Entity*& entity){
    if(this->head != this->tail){
        if(this->head) {
            if (entity == this->head) {
                this->head = entity->next;
                this->head->prev = NULL;
                delete entity;
                this->Size--;
                return this->head;
            }
            if (entity == this->tail) {
                this->tail = entity->prev;
                this->tail->next = NULL;
                delete entity;
                this->Size--;
                return this->tail;
            }
            Entity* p;
            entity->prev->next = entity->next;
            entity->next->prev = entity->prev;
            p = entity->next;
            delete entity;
            this->Size--;
            return p;
        }
    }else{
        delete this->head;
        this->head = this->tail = NULL;
        this->Size--;
        return NULL;
    }
}
void List::clear(){
    while(this->head){
        this->remove(this->tail);
    }
}

size_t List::size(){
    return this->Size;
}
bool List::empty(){
    if(this->size() == 0)
        return true;
    return false;
}
Entity* List::getHead() {
    return this->head;
}
Entity* List::getNext(Entity* entity) {
    return entity->next;
}
Entity* List::getPrev(Entity* entity) {
    return entity->prev;
}