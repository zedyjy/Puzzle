/*
 * Zeynep Doğa Dellal
 * 22002572
 * 21.04.2022
 * */
#include "PuzzleRow.h"
#include <iostream>
using namespace std;

PuzzleRow::PuzzleRow(int size, int rowindex) {
    maxSize=size;
    head=NULL;
    next=NULL;
    row=rowindex;
    setRowIndex(rowindex);
}

PuzzleRow::~PuzzleRow() {
    for(int i = 0; i < maxSize; i++){
        remove(i);
    }
    delete head;
}


int PuzzleRow::getRowIndex() {
    return row;
}


void PuzzleRow::setNext(PuzzleRow *next) {
    this->next = next;
}

PuzzleRow *PuzzleRow::getNext() {
    return next;
}

bool PuzzleRow::insert(int index, unsigned char shape) {
    PuzzlePiece* found = new PuzzlePiece(row,index,shape);

    if(index > maxSize){
        delete found;
        return false;
    }

    for( PuzzlePiece* piece = head; piece!=NULL; piece=piece->next ){
        if(piece->colindex==index) {
            delete found;
            return false;
        }
    }

    if(!(doesFitInPlace(find(index-1), found, find(index+1)))){
        delete found;
        return false;
    }

    if ( isEmpty() ) {
        head = new PuzzlePiece(row,index, shape);

        head->shape = shape;
        head->rowindex = index;
        head->next = NULL;

        delete found;
        return true;
    }
    else {
        PuzzlePiece* curr = head;
        PuzzlePiece* prev = NULL;

        while ( curr !=NULL && curr->colindex < index ) {
            prev = curr;
            curr = curr->next;
        }

        PuzzlePiece* newNode = new PuzzlePiece(row,index,shape);

        newNode->shape = shape;
        newNode->rowindex = index;
        newNode->next = curr;

        if ( prev == NULL ) {
            head = newNode;
        }
        else {
            prev->next = newNode;
        }

        delete found;
        found=NULL;
        return true;
    }
}

bool PuzzleRow::remove(int index) {
    PuzzlePiece *prev;
    for( prev = head;prev!=NULL;prev=prev->next){
        if(prev==head){
            if(prev->colindex==index){
                PuzzlePiece *temp = head;
                head = temp->next;
                delete temp;
                return true;
            }
        }
        if(prev->next!=NULL && prev->next->colindex==index){
            PuzzlePiece *temp = prev->next;
            prev->next=temp->next;
            delete temp;
            return true;
        }
    }
    delete prev;
    return false;
}

bool PuzzleRow::isEmpty() {
    return head == NULL;
}

unsigned char PuzzleRow::getPiece(int index) {
    PuzzlePiece* prev;
    for(prev =head;prev!=NULL; prev=prev->next){
        if(prev->colindex==index){
            return prev->getShape();
        }
    }
    delete prev;
    return 255;
}

void PuzzleRow::printRow() {
    for(int i =1; i< maxSize+1; i++){
        if((int)(getPiece(i))==255){
            cout<<"O ";
        }
        else{
            cout<<"X ";
        }
    }
}


int PuzzleRow::getLength() {
    return maxSize;
}

//This method checks if piece fits in right and left
bool PuzzleRow:: doesFitInPlace(PuzzlePiece* left, PuzzlePiece* curr, PuzzlePiece* right){

    int leftCode, rightCode=-1;
    int currentLeft= curr->left;
    int currentRight=curr->right;

    //checks if border and smooth
    if(curr->colindex==maxSize && curr->right!=2){
        cout<<"Shape does not fit into (" << row << "," << maxSize << "), it cannot be added"<<endl;
        return false;
    }
    if(curr->colindex==1 && curr->left!=2){
        cout<<"Shape does not fit into (" << row << "," << maxSize << "), it cannot be added"<<endl;
        return false;
    }
    if((curr->colindex!=1) && curr->left==2){
        cout<<"Shape does not fit into (" << row << "," << maxSize << "), it cannot be added"<<endl;
        return false;
    }
    if((curr->colindex!=maxSize) && curr->right==2){
        cout<<"Shape does not fit into (" << row << "," << maxSize << "), it cannot be added"<<endl;
        return false;
    }
    if(left!=NULL || right!=NULL){
        if(left != NULL){
            leftCode= left->right;
            if((leftCode+currentLeft)!=1) {
                cout << "Shape does not fit into (" << row << "," << maxSize << "), it cannot be added" << endl;
                return false;
            }
        }
        if(right != NULL) {
            rightCode = right->left;
            if ((rightCode + currentRight) != 1) {
                cout << "Shape does not fit into (" << row << "," << maxSize << "), it cannot be added" << endl;
                return false;
            }
        }
    }
    else{
        return true;
        }
}

void PuzzleRow::setRowIndex(int rowindex) {
    row=rowindex;
}

//finds and returns piece according to shape in that row
PuzzlePiece *PuzzleRow::find(int index) {
    for(PuzzlePiece* curr = head; curr!=NULL;curr=curr->next){
        if(curr->colindex==index){
            return curr;
        }
    }
    return NULL;
}

