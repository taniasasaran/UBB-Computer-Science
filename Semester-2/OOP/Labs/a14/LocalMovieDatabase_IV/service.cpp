//
// Created by TANIA on 3/19/2022.
//

#include "service.h"

Service::Service(Repository repository) : repository(repository) {}

void Service::add(Movie movie){
    this->repository.add(movie);
    Operation* op = createOperation(ADD, movie);
    if (op == NULL)
        throw Exception("bing");
    undoStack.push_back(op);
}

int Service::search(std::string title, std::string genre){
    return this->repository.search(title, genre);
}

void Service::remove(std::string title, std::string genre){
    int pos = repository.search(title, genre);
    Movie m = repository.get(pos);
    Operation* op = createOperation(DELETE, m);
    if (op == NULL)
        throw Exception("bing");
    undoStack.push_back(op);
    this->repository.remove(title, genre);
}

void Service::update(std::string title, std::string genre, Movie movie){
    int pos = repository.search(title, genre);
    Movie m = repository.get(pos);
    Operation* op = createOperation(UPDATE, m);
    if (op == NULL)
        throw Exception("bing");
    undoStack.push_back(op);
    this->repository.update(title, genre, movie);
}

int Service::undo()
{
    int undoStackSize = undoStack.size();
    if (undoStackSize == 0)
        return 1; // no more undos
    Operation* op = undoStack[undoStackSize-1];

    if (op == NULL)
        return -1;
    Movie m = getOpObject(op);
    Operation* op_after_copy = createOperation(getOpType(op), getOpObject(op));
    if (getOpType(op) == ADD)
        repository.remove(m.getTitle(), m.getGenre());
    else if (getOpType(op) == DELETE)
        repository.add(m);
    else if (getOpType(op) == UPDATE)
    {
        int pos = repository.search(m.getTitle(), m.getGenre());
        Movie m2 = repository.get(pos);
        op_after_copy = createOperation(getOpType(op), m2);
        repository.update(m.getTitle(), m.getGenre(), m);
    }
    redoStack.push_back(op_after_copy);
    undoStack.pop_back();
    return 0;
}

int Service::redo()
{
    int redoStackSize = redoStack.size();
    if (redoStackSize == 0)
        return 1;
    Operation* op = redoStack[redoStackSize-1];
    if (op == NULL)
        return -1;
    Movie m = getOpObject(op);
    Operation* op_after_copy = createOperation(getOpType(op), getOpObject(op));
    if (getOpType(op) == ADD)
        repository.add(m);
    else if (getOpType(op) == DELETE)
        repository.remove(m.getTitle(), m.getGenre());
    else if (getOpType(op) == UPDATE)
    {
        int pos = repository.search(m.getTitle(), m.getGenre());
        Movie m2 = repository.get(pos);
        op_after_copy = createOperation(getOpType(op), m2);
        repository.update(m.getTitle(), m.getGenre(), m);
    }
    undoStack.push_back(op_after_copy);
    redoStack.pop_back();
    return 0;
}

