/*
 * Zeynep Doğa Dellal
 * 22002572
 * 21.04.2022
 * */
#ifndef UNTITLED_PUZZLEPIECE_H
#define UNTITLED_PUZZLEPIECE_H


class PuzzlePiece {

public:
    void shapeConverter(unsigned char shape, int& down, int& up, int& right, int& left){
        down = shape%4;
        up = (shape/4)%4;
        right= (shape/16)%4;
        left= shape/64;
    }
    PuzzlePiece* next;
    unsigned char shape;
    int rowindex;
    int colindex;
    int up;
    int down;
    int left;
    int right;
    PuzzlePiece( int rowindex, int colindex,unsigned char shape);
    ~PuzzlePiece();
    void setShape(unsigned char shape);
    unsigned char getShape();

};


#endif //UNTITLED_PUZZLEPIECE_H
