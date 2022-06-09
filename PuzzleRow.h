/*
 * Zeynep Doğa Dellal
 * 22002572
 * 21.04.2022
 * */

#ifndef UNTITLED_PUZZLEROW_H
#define UNTITLED_PUZZLEROW_H


#include "PuzzlePiece.h"

class PuzzleRow {
private:
    PuzzlePiece* head;
    PuzzleRow* next;
    int row;
    int maxSize; //equals to puzzleContainer width

public:

    PuzzleRow( int size, int rowindex);
    ~PuzzleRow();
    int getLength();
    int getRowIndex();
    void setRowIndex(int rowindex);
    void setNext( PuzzleRow* next );
    PuzzleRow* getNext();
    bool insert( const int index, const unsigned char shape );
    bool remove( int index );
    bool isEmpty();
    unsigned char getPiece(int index );
    void printRow();
    bool doesFitInPlace(PuzzlePiece* left, PuzzlePiece* curr, PuzzlePiece* right);
    PuzzlePiece* find(int index);

};
#endif //UNTITLED_PUZZLEROW_H