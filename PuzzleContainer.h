/*
 * Zeynep Doğa Dellal
 * 22002572
 * 21.04.2022
 * */

#ifndef UNTITLED_PUZZLECONTAINER_H
#define UNTITLED_PUZZLECONTAINER_H


#include "PuzzleRow.h"

class PuzzleContainer {
    void shapeConverter(unsigned char shape, int& down, int& up, int& right, int& left){
        down = shape%4;
        up = (shape/4)%4;
        right= (shape/16)%4;
        left= shape/64;
    }
private:
        PuzzleRow* rowLists;
        int height;
        int width;

    public:
        PuzzleContainer( int h, int w);
        ~PuzzleContainer();
        PuzzleRow* getRow( int index );
        bool insertRow( int index );
        bool removeRow( int index );
        bool addPiece( int row, int col , unsigned char shape );
        bool removePiece(int row, int col);
        int getHeight();
        int getWidth();
        void showPiece(int row, int col);
        void displayContainer();
        void showColumn(int col);
        void showRow(int row);
        void findPiece(unsigned char shape);
        void shapeToStringConverter(int shape);
    };


#endif //UNTITLED_PUZZLECONTAINER_H
