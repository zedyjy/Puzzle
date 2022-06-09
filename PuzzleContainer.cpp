/*
 * Zeynep Doğa Dellal
 * 22002572
 * 21.04.2022
 * */
#include <iostream>
using namespace std;
#include "PuzzleContainer.h"

PuzzleContainer::PuzzleContainer(int h, int w) {
    this->height=h;
    this->width=w;
    rowLists=NULL;
}

PuzzleContainer::~PuzzleContainer() {
    delete rowLists;
}

PuzzleRow *PuzzleContainer::getRow(int index) {
    if(index < 1 || index > height) {
        return NULL;
    }
    for(PuzzleRow*prev =rowLists;prev!=NULL; prev=prev->getNext()){
        if(prev->getRowIndex()==index){
            return prev;
        }
    }
    return NULL;
}

bool PuzzleContainer::insertRow(int index) {
    PuzzleRow* puzzleRow = new PuzzleRow(width,index);
    puzzleRow->setNext(NULL);
    PuzzleRow* curr;
    PuzzleRow* prev ;
    if(index>height){
        delete puzzleRow;
        return false;
    }
    if(rowLists==NULL){
        rowLists=puzzleRow;
        return true;
    }
    else if(rowLists!=NULL){
        curr = rowLists;
        if (curr->getRowIndex() > index) {
            puzzleRow->setNext(rowLists);
            rowLists = puzzleRow;
            delete puzzleRow;
            return true;
        }
        else if(curr->getRowIndex() <= index) {
            prev = curr;
            while (curr != NULL && curr->getRowIndex() < index) {
                prev = curr;
                curr = curr->getNext();
            }

            if (curr == NULL) {
                prev->setNext(puzzleRow);
            } else {
                puzzleRow->setNext(curr);
                prev->setNext(puzzleRow);
            }
            return true;
        }
        delete puzzleRow;
    }
    delete puzzleRow;
}

bool PuzzleContainer::removeRow(int index) {
    if(getRow(index)==NULL){
        return false;
    }
    for(PuzzleRow * curr = rowLists;curr!=NULL;curr=curr->getNext()){
        if(curr==rowLists){
            if(curr->getRowIndex()==index){
                PuzzleRow * temp = rowLists;
                rowLists = rowLists->getNext();
                for(int i=1;i< getRow(index)->getRowIndex();i++){
                    getRow(index)->remove(i);
                }
                delete temp;
                return true;
            }
        }
        else{
            if(curr->getRowIndex()==index){
                PuzzleRow * temp = curr->getNext();
                curr->setNext(temp->getNext());
                for(int i=1;i< getRow(index)->getRowIndex();i++){
                    getRow(index)->remove(i);
                }
                delete temp;
                return true;
            }
        }
    }
    return false;
}

bool PuzzleContainer::addPiece(int row, int col, unsigned char shape) {

    //check row and col
    if(row<=0 || col<=0||row>height||col>width){
        cout<<"(" << row << "," << col << "), is out of frame, it cannot be added"<<endl;
        return false;
    }

    //if row empty insert row
    if (getRow(row) == NULL) {
        insertRow(row);
    }

    if(getRow(row) && ((getRow(row)->getPiece(col)) != 255)){
        cout<< "(" << row << "," << col <<") has been already occupied, it cannot be added"<<endl;
        return false;
    }

    //declare and set shapes
    int left, right, down, up;
    shapeConverter(shape, down, up, right, left);
    unsigned char upPiece=255;
    unsigned char downPiece=255;

    if(getRow(row-1)){
        upPiece = getRow(row-1)->getPiece(col);
    }
    if(getRow(row+1)){
        downPiece = getRow(row+1)->getPiece(col);
    }
    int downU,downD,upU,upD,rightU,rightD,leftU,leftD;
    shapeConverter(upPiece, downU, upU, rightU, leftU);
    shapeConverter(downPiece, downD, upD, rightD, leftD);


    if((row==1) && (up != 2)){
        cout<<"Shape does not fit into (" << row << "," << col << "), it cannot be added"<<endl;
        return false;
    }
    if (row == height && down != 2) {
        cout<<"Shape does not fit into (" << row << "," << col << "), it cannot be added"<<endl;
        return false;
    }
    if (row != 1 && up == 2) {
        cout<<"Shape does not fit into (" << row << "," << col << "), it cannot be added"<<endl;
        return false;
    }
    if (row != height && down == 2) {
        cout<<"Shape does not fit into (" << row << "," << col << "), it cannot be added"<<endl;
        return false;
    }

    if(upPiece!=255 || downPiece!=255){
        if(upPiece!=255){
            //check up's shape and up piece's down shape
            if(up+downU != 1){
                cout<<"Shape does not fit into (" << row << "," << col << "), it cannot be added"<<endl;
                return false;
            }
        }
        if(downPiece!=255){
            //check down shape and down piece's up shape
            if(down+upD!=1){
                cout<<"Shape does not fit into (" << row << "," << col << "), it cannot be added"<<endl;
                return false;
            }
        }
    }
    if(getRow(row)->insert(col, shape)){
        cout<<"A piece is added to ("<<row<<","<<col<<")"<<endl;
        return true;
    }
}

bool PuzzleContainer::removePiece(int row, int col) {
    if(getRow(row)==NULL){
        cout<<"("<<row<<","<<col<<") is out of frame, it cannot be removed"<<endl;
        return false;
    }
    else if(row>height||row<0||col>width||col<0){
        cout<<"("<<row<<","<<col<<") is out of frame, it cannot be removed"<<endl;
        return false;
    }
    else{
        if(getRow(row)&&getRow(row)->getPiece(col)!=255) {
            getRow(row)->remove(col);
            cout<<"The piece on ("<< row<<","<<col<<") is removed"<<endl;
            return true;
        }
        else{
            cout<<"There is no piece on ("<< row<<","<<col<<") , it cannot be removed"<<endl;
            return false;
        }
    }
    if(getRow(row)->isEmpty()){
        removeRow(row);
    }
}

int PuzzleContainer::getHeight() {
    return height;
}

int PuzzleContainer::getWidth() {
    return width;
}

void PuzzleContainer::showPiece(int row, int col) {
    if(row>height || row<0 || col>width || col<0){
        cout<<"("<<row<<","<<col<<") is out of frame, it cannot be shown"<<endl;
    }
    else if(getRow(row)!=NULL){
        if(getRow(row)->getPiece(col)==255){
            cout<<"There is no piece on "<<"("<<row<<","<<col<<") , it cannot be shown"<<endl;
        }
        else{
            cout<<"Piece on"<<"("<<row<<","<<col<<") as following:"<<endl;
            int up,down,left,right;
            shapeConverter(getRow(row)->getPiece(col),down,up,right,left);
            cout<<"Down: ";
            shapeToStringConverter(down);
            cout<<endl;
            cout<<"Up: ";
            shapeToStringConverter(up);
            cout<<endl;
            cout<<"Right: ";
            shapeToStringConverter(right);
            cout<<endl;
            cout<<"Left: ";
            shapeToStringConverter(left);
            cout<<endl;
        }
    }
}

void PuzzleContainer::displayContainer() {
    cout<<"Container"<<"("<<getHeight()<<","<<getWidth()<<")"<<endl;
    cout<<"   ";
    for(int i =1;i<=getWidth();i++){
        cout<<i<<" ";
    }
    cout<<endl;
    for(int i=1;i<height+1;i++){
        cout<<i<<"  ";
        if(getRow(i)!=NULL) {
            getRow(i)->printRow();
            cout << endl;
        }
        else{
            for(int j =0;j<width;j++) {
                cout <<"O ";
            }
            cout<<endl;
        }
    }
}

void PuzzleContainer::showColumn(int col) {
    if( col>width || col<=0){
        cout<<"Column "<<col<<" is out of border"<<endl;
        return;
    }
    else{
        cout<< "Column: "<< col<<endl;
    }
    for(int i = 1; i < height+1; i++){
        if(getRow(i)==NULL){
            cout<<"O"<<endl;
        }
        else if(getRow(i)->getPiece(col)==255){
            cout<<"O"<<endl;
        }
        else {
            cout<<"X"<<endl;
        }
    }
}

void PuzzleContainer::showRow(int row) {
    if( row>height || row<=0){
        cout<<"Row "<<row<<" is out of border"<<endl;
        return;
    }
    else{
        cout<< "Row: "<< row<<endl;
    }
    if(getRow(row)==NULL) {
        //cout<<"Row is empty";

    }
    else{
        getRow(row)->printRow();
    }
    cout<<endl;
}

void PuzzleContainer::findPiece(unsigned char shape) {

    bool pieceFound = false;
    for(int i = 1;i<height+1;i++){
        for(int j = 1;j<width+1;j++){
            if(getRow(i)==NULL) {

            }
            else if(getRow(i)->getPiece(j)==shape){
                pieceFound=true;
                cout<<" ("<<i<<","<<j<<") ";
            }
        }
    }
    int left, right, down, up;
    shapeConverter(shape, down, up, right, left);
    if(pieceFound){
        cout<<" contain the piece that has shape"<<endl;
        int up,down,left,right;
        shapeConverter(shape,down,up,right,left);
        cout<<"Down: ";
        shapeToStringConverter(down);
        cout<<endl;
        cout<<"Up: ";
        shapeToStringConverter(up);
        cout<<endl;
        cout<<"Right: ";
        shapeToStringConverter(right);
        cout<<endl;
        cout<<"Left: ";
        shapeToStringConverter(left);
        cout<<endl;
    }
    else{
        cout<<"There is no piece that has shape"<<endl;
        int up,down,left,right;
        shapeConverter(shape,down,up,right,left);
        cout<<"Down: ";
        shapeToStringConverter(down);
        cout<<endl;
        cout<<"Up: ";
        shapeToStringConverter(up);
        cout<<endl;
        cout<<"Right: ";
        shapeToStringConverter(right);
        cout<<endl;
        cout<<"Left: ";
        shapeToStringConverter(left);
        cout<<endl;
    }
}

//Prints given int (0,1,2) as Border,Knob,Hole appropriately
void PuzzleContainer::shapeToStringConverter(int shape) {
    if(shape==0){
        cout<<"Hole";
    }
    else if(shape==1){
        cout<<"Knob";
    }
    else{
        cout<<"Border";
    }
}



