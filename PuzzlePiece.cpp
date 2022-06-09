/*
 * Zeynep Doğa Dellal
 * 22002572
 * 21.04.2022
 * */

#include "PuzzlePiece.h"
#include <iostream>
using namespace std;

PuzzlePiece::PuzzlePiece(int rowindex, int colindex,unsigned char shape):next(NULL),colindex(colindex),rowindex(rowindex) {
    setShape(shape);
    shapeConverter(shape,down,up,right,left);
}

PuzzlePiece::~PuzzlePiece() {
    delete next;
}

void PuzzlePiece::setShape(unsigned char shape) {
    this->shape=shape;
}

unsigned char PuzzlePiece::getShape() {
    return shape;
}

