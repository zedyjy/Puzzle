//
// Created by zeyne on 25.04.2022.
//

#include <iostream>
using namespace std;
#include "PuzzleContainer.h"
int main() {
      PuzzleContainer P(8,4);
        P.displayContainer();
// Testing add piece
        cout << endl;
        cout << "Testing Add Piece" << endl;
        cout << endl;
        P.addPiece( 1,2, 0x58);
        P.addPiece( 2,4, 0x20);
        P.addPiece( 5,2, 0x05);
        P.addPiece( 5,3, 0x54);
        P.addPiece( 6,3, 0x55);
        P.addPiece( 7,2, 0x00);
        P.addPiece( 7,4, 0x65);
        P.addPiece( 8,3, 0x42);

    cout << endl;
        P.displayContainer();
        cout << endl;
        P.addPiece( 0,0, 0x58);
        P.addPiece( 1,2, 0x58);
        P.addPiece( 2,2, 0x58);
        P.addPiece( 7,3, 0x55);
        P.addPiece( 4,4, 0x55);
        P.addPiece( 5,5, 0x55);
        cout << endl;
        P.displayContainer();
        cout << endl;
// Testing remove piece
        cout << endl;
        cout << "Testing Remove Piece" << endl;
        cout << endl;
        P.removePiece(5,9);
        P.removePiece(5,3);
        P.removePiece(4,4);
        P.removePiece(1,2);
        cout << endl;
        P.displayContainer();
        cout << endl;
        P.addPiece( 1,2, 0x58);
        cout << endl;
        P.displayContainer();
        cout << endl;
// Testing show piece
        cout << endl;
        cout << "Testing Show Piece" << endl;
        cout << endl;
        P.showPiece(5,9);
        P.showPiece(4,4);
        P.showPiece(1,2);
// Testing show column
        cout << endl;
        cout << "Testing Show Column" << endl;
        cout << endl;
        P.showColumn(0);
        P.showColumn(1);
// Testing show row
        cout << endl;
        cout << "Testing Show Row" << endl;
        cout << endl;
        P.showRow(9);
        P.showRow(8);
// Testing find piece
        cout << endl;
        cout << "Testing Find Piece" << endl;
        cout << endl;
        P.findPiece(0x21);
        cout << endl;
        P.addPiece( 3,2, 0x05);
        P.findPiece(0x05);

    cout<<"testing remove row";
    cout << endl;
    P.getRow(5)->printRow();
    cout << endl;

    cout<<P.removeRow(5)<<endl;
    cout << endl;

    P.getRow(5)->printRow();
    cout << endl;

}