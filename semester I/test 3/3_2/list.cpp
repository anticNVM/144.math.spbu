#include "list.h"
#include <iostream>
#include <assert.h>

using namespace std;

struct ListElement {
    TypeElement value;
    ListElement* next;
};

struct Iterator {
    ListElement* current;
    int index;
};

struct List {
    ListElement* sentinel;
    ListElement* end;
    Iterator* iter;
    int size;
};

ListElement* & getCurrent(List* list)
{
    return list->iter->current;
}

void next(List* list)
{
    assert(getCurrent(list)->next != nullptr);
    getCurrent(list) = getCurrent(list)->next;
    (list->iter->index)++;
}

void begin(List* list)
{
    // -1
    getCurrent(list) = list->sentinel;
    list->iter->index = -1;
}

void moveIterToPosition(List* list, int index)
{
    if (index < list->iter->index) {
        begin(list);
    }
    while (list->iter->index != index) {
        next(list);
    }
}

void add(TypeElement value, List* list, int index)
{
    ListElement* newElement = new ListElement{value, nullptr};
    if (index == -1) {
        list->end->next = newElement;
        list->end = newElement;
    } else {
        index--;
        moveIterToPosition(list, index);
        newElement->next = getCurrent(list)->next;
        getCurrent(list)->next = newElement;
    }
    (list->size)++;
}

int pop(List* list, int index)
{
    if (index == -1) {
        index = list->size - 1;
    } else if (index < list->size && index >= 0) {
        moveIterToPosition(list, index - 1);
        ListElement* buffer = getCurrent(list)->next;
        getCurrent(list)->next = buffer->next;
        if (list->end == buffer) {
            list->end = getCurrent(list);
        }
        delete buffer;
        (list->size)--;
        return 0;
    } else {
        return -1;
    }
}

TypeElement getValue(List* list, int index)
{
    if (index < list->size && index >= 0) {
        moveIterToPosition(list, index);
        return getCurrent(list)->value;
    } else {
        return "";
    }
}

int getIndex(TypeElement value, List *list)
{
    begin(list);
    bool isExist = false;
    while (getCurrent(list)->next != 0) {
        next(list);
        if (getCurrent(list)->value == value) {
            isExist = true;
            break;
        }
    }
    return (isExist ? list->iter->index : (-1));
}

int getSize(List *list)
{
    return list->size;
}

bool isEmpty(List *list)
{
    return (list->sentinel->next == nullptr);
}

void reverse(List*& list)
{
    if (list == nullptr)
        return;

    List* reversedList = createList();
    begin(list);
    while (getCurrent(list)->next != nullptr) {
        next(list);
        add(getCurrent(list)->value, reversedList, 0);
    }
    deleteList(list);
    list = reversedList;
}

void printList(List *list)
{
    begin(list);
    while (getCurrent(list)->next != nullptr) {
        cout << getCurrent(list)->next->value << ' ';
        next(list);
    }
    cout << endl;
}

List* createList()
{
    ListElement* sent = new ListElement{"", nullptr};
    Iterator* iter = new Iterator{sent, -1};
    return new List{sent, sent, iter, 0};
}

void clearList(List *list)
{
    begin(list);
    while (getCurrent(list)->next != nullptr) {
        pop(list, 0);
    }
}

void deleteList(List* list)
{
    begin(list);
    while (getCurrent(list)->next != nullptr) {
        pop(list, 0);
    }
    delete list->sentinel;
    delete list->iter;
    delete list;
}

bool isEnd(List* list)
{
    return (getCurrent(list)->next == nullptr);
}

bool isInList(List* list, const TypeElement& str)
{
    if (getSize(list) == 0) {
        return false;
    }
    moveIterToPosition(list, 0);
    do {
        if (getCurrent(list)->value == str) {
            return true;
        }
        if (!isEnd(list)) {
            next(list);
        }
    } while (!isEnd(list));

    return false;
}

List* getUnique(List* list)
{
    List* unique = createList();
    if (list->size == 0) {
        return unique;
    }
    moveIterToPosition(list, 0);
    do {
        if (!isInList(unique, getCurrent(list)->value)) {
            add(getCurrent(list)->value, unique);
        }
        if (!isEnd(list)) {
            next(list);
        }
    } while (!isEnd(list));

    return unique;
}
