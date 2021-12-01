#include <iostream>
#include <stdlib.h>
class GamePiece
{
public:
    GamePiece(char PieceColor) : mPieceColor(PieceColor) {}
    ~GamePiece() {}
    virtual char GetPiece() = 0;
    char GetColor() {
        return mPieceColor;
    }
    bool IsLegalMove(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, GamePiece* GameBoard[8][8]) {
        GamePiece* qpDest = GameBoard[iDestRow][iDestCol];
        if ((qpDest == 0) || (mPieceColor != qpDest->GetColor())) {
            return AreSquaresLegal(iSrcRow, iSrcCol, iDestRow, iDestCol, GameBoard);
        }
        return false;
    }
private:
    virtual bool AreSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, GamePiece* GameBoard[8][8]) = 0;
    char mPieceColor;
};

class PawnPiece : public GamePiece
{
public:
    PawnPiece(char PieceColor) : GamePiece(PieceColor) {}
    ~PawnPiece() {}
private:
    virtual char GetPiece() {
        return 'P';
    }
    bool AreSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, GamePiece* GameBoard[8][8]) {
        GamePiece* qpDest = GameBoard[iDestRow][iDestCol];
        if (qpDest == 0) {
            // Galamērķa laukums nav aizņemts
            if (iSrcCol == iDestCol) {
                if (GetColor() == 'W') {
                    if (iDestRow == iSrcRow + 1) {
                        return true;
                    }
                } else {
                    if (iDestRow == iSrcRow - 1) {
                        return true;
                    }
                }
            }
        } else {
            
            if ((iSrcCol == iDestCol + 1) || (iSrcCol == iDestCol - 1)) {
                if (GetColor() == 'W') {
                    if (iDestRow == iSrcRow + 1) {
                        return true;
                    }
                } else {
                    if (iDestRow == iSrcRow - 1) {
                        return true;
                    }
                }
            }
        }
        return false;
    }
};

class KnightPiece : public GamePiece
{
public:
    KnightPiece(char PieceColor) : GamePiece(PieceColor) {}
    ~KnightPiece() {}
private:
    virtual char GetPiece() {
        return 'N';
    }
    bool AreSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, GamePiece* GameBoard[8][8]) {
        // Galamērķa laukums ir neaizņemts vai aizņemts ar pretēju krāsu
        if ((iSrcCol == iDestCol + 1) || (iSrcCol == iDestCol - 1)) {
            if ((iSrcRow == iDestRow + 2) || (iSrcRow == iDestRow - 2)) {
                return true;
            }
        }
        if ((iSrcCol == iDestCol + 2) || (iSrcCol == iDestCol - 2)) {
            if ((iSrcRow == iDestRow + 1) || (iSrcRow == iDestRow - 1)) {
                return true;
            }
        }
        return false;
    }
};

class BishopPiece : public GamePiece
{
public:
    BishopPiece(char PieceColor) : GamePiece(PieceColor) {}
    ~BishopPiece() {}
private:
    virtual char GetPiece() {
        return 'B';
    }
    bool AreSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, GamePiece* GameBoard[8][8]) {
        if ((iDestCol - iSrcCol == iDestRow - iSrcRow) || (iDestCol - iSrcCol == iSrcRow - iDestRow)) {
            // Pārliecinieties, vai visi apgrieztie kvadrāti ir tukši
            int iRowOffset = (iDestRow - iSrcRow > 0) ? 1 : -1;
            int iColOffset = (iDestCol - iSrcCol > 0) ? 1 : -1;
            int iCheckRow;
            int iCheckCol;
            for (iCheckRow = iSrcRow + iRowOffset, iCheckCol = iSrcCol + iColOffset;
                iCheckRow !=  iDestRow;
                iCheckRow = iCheckRow + iRowOffset, iCheckCol = iCheckCol + iColOffset)
            {
                if (GameBoard[iCheckRow][iCheckCol] != 0) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }
};

class RookPiece : public GamePiece
{
public:
    RookPiece(char PieceColor) : GamePiece(PieceColor) {}
    ~RookPiece() {}
private:
    virtual char GetPiece() {
        return 'R';
    }
    bool AreSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, GamePiece* GameBoard[8][8]) {
        if (iSrcRow == iDestRow) {
            // Pārliecinieties, vai visas kolonas ir tukšas
            int iColOffset = (iDestCol - iSrcCol > 0) ? 1 : -1;
            for (int iCheckCol = iSrcCol + iColOffset; iCheckCol !=  iDestCol; iCheckCol = iCheckCol + iColOffset) {
                if (GameBoard[iSrcRow][iCheckCol] != 0) {
                    return false;
                }
            }
            return true;
        } else if (iDestCol == iSrcCol) {
            // Pārliecinieties, vai visas līnijas ir tukši
            int iRowOffset = (iDestRow - iSrcRow > 0) ? 1 : -1;
            for (int iCheckRow = iSrcRow + iRowOffset; iCheckRow !=  iDestRow; iCheckRow = iCheckRow + iRowOffset) {
                if (GameBoard[iCheckRow][iSrcCol] != 0) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }
};

class QueenPiece : public GamePiece
{
public:
    QueenPiece(char PieceColor) : GamePiece(PieceColor) {}
    ~QueenPiece() {}
private:
    virtual char GetPiece() {
        return 'Q';
    }
    bool AreSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, GamePiece* GameBoard[8][8]) {
        if (iSrcRow == iDestRow) {
            // Pārliecinieties, vai visas kolonas ir tukšas
            int iColOffset = (iDestCol - iSrcCol > 0) ? 1 : -1;
            for (int iCheckCol = iSrcCol + iColOffset; iCheckCol !=  iDestCol; iCheckCol = iCheckCol + iColOffset) {
                if (GameBoard[iSrcRow][iCheckCol] != 0) {
                    return false;
                }
            }
            return true;
        } else if (iDestCol == iSrcCol) {
            // Pārliecinieties, vai visas līnijas ir tukši
            int iRowOffset = (iDestRow - iSrcRow > 0) ? 1 : -1;
            for (int iCheckRow = iSrcRow + iRowOffset; iCheckRow !=  iDestRow; iCheckRow = iCheckRow + iRowOffset) {
                if (GameBoard[iCheckRow][iSrcCol] != 0) {
                    return false;
                }
            }
            return true;
        } else if ((iDestCol - iSrcCol == iDestRow - iSrcRow) || (iDestCol - iSrcCol == iSrcRow - iDestRow)) {
            // Pārliecinieties, vai visi kvadrāti ir tukši
            int iRowOffset = (iDestRow - iSrcRow > 0) ? 1 : -1;
            int iColOffset = (iDestCol - iSrcCol > 0) ? 1 : -1;
            int iCheckRow;
            int iCheckCol;
            for (iCheckRow = iSrcRow + iRowOffset, iCheckCol = iSrcCol + iColOffset;
                iCheckRow !=  iDestRow;
                iCheckRow = iCheckRow + iRowOffset, iCheckCol = iCheckCol + iColOffset)
            {
                if (GameBoard[iCheckRow][iCheckCol] != 0) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }
};

class KingPiece : public GamePiece
{
public:
    KingPiece(char PieceColor) : GamePiece(PieceColor) {}
    ~KingPiece() {}
private:
    virtual char GetPiece() {
        return 'K';
    }
    bool AreSquaresLegal(int iSrcRow, int iSrcCol, int iDestRow, int iDestCol, GamePiece* GameBoard[8][8]) {
        int iRowDelta = iDestRow - iSrcRow;
        int iColDelta = iDestCol - iSrcCol;
        if (((iRowDelta >= -1) && (iRowDelta <= 1)) &&
            ((iColDelta >= -1) && (iColDelta <= 1)))
        {
            return true;
        }
        return false;
    }
};

class CBoard
{
public:
    CBoard() {
        for (int iRow = 0; iRow < 8; ++iRow) {
            for (int iCol = 0; iCol < 8; ++iCol) {
                MainGameBoard[iRow][iCol] = 0;
            }
        }
        // Melnie gabali
        for (int iCol = 0; iCol < 8; ++iCol) {
            MainGameBoard[6][iCol] = new PawnPiece('B');
        }
        MainGameBoard[7][0] = new RookPiece('B');
        MainGameBoard[7][1] = new KnightPiece('B');
        MainGameBoard[7][2] = new BishopPiece('B');
        MainGameBoard[7][3] = new KingPiece('B');
        MainGameBoard[7][4] = new QueenPiece('B');
        MainGameBoard[7][5] = new BishopPiece('B');
        MainGameBoard[7][6] = new KnightPiece('B');
        MainGameBoard[7][7] = new RookPiece('B');
        // Baltie gabali
        for (int iCol = 0; iCol < 8; ++iCol) {
            MainGameBoard[1][iCol] = new PawnPiece('W');
        }
        MainGameBoard[0][0] = new RookPiece('W');
        MainGameBoard[0][1] = new KnightPiece('W');
        MainGameBoard[0][2] = new BishopPiece('W');
        MainGameBoard[0][3] = new KingPiece('W');
        MainGameBoard[0][4] = new QueenPiece('W');
        MainGameBoard[0][5] = new BishopPiece('W');
        MainGameBoard[0][6] = new KnightPiece('W');
        MainGameBoard[0][7] = new RookPiece('W');
    }
    ~CBoard() {
        for (int iRow = 0; iRow < 8; ++iRow) {
            for (int iCol = 0; iCol < 8; ++iCol) {
                delete MainGameBoard[iRow][iCol];
                MainGameBoard[iRow][iCol] = 0;
            }
        }
    }

    void Print() {
        using namespace std;
        const int kiSquareWidth = 4;
        const int kiSquareHeight = 3;
        for (int iRow = 0; iRow < 8*kiSquareHeight; ++iRow) {
            int iSquareRow = iRow/kiSquareHeight;
            // Printe sānu apmale ar numerāciju
            if (iRow % 3 == 1) {
                cout << '-' << (char)('1' + 7 - iSquareRow) << '-';
            } else {
                cout << "---";
            }
            // Printē pašu laukumu
            for (int iCol = 0; iCol < 8*kiSquareWidth; ++iCol) {
                int iSquareCol = iCol/kiSquareWidth;
                if (((iRow % 3) == 1) && ((iCol % 4) == 1 || (iCol % 4) == 2) && MainGameBoard[7-iSquareRow][iSquareCol] != 0) {
                    if ((iCol % 4) == 1) {
                        cout << MainGameBoard[7-iSquareRow][iSquareCol]->GetColor();
                    } else {
                        cout << MainGameBoard[7-iSquareRow][iSquareCol]->GetPiece();
                    }
                } else {
                    if ((iSquareRow + iSquareCol) % 2 == 1) {
                        cout << '*';
                    } else {
                        cout << ' ';
                    }
                }
            }
            cout << endl;
        }
        // Print the bottom border with numbers
        for (int iRow = 0; iRow < kiSquareHeight; ++iRow) {
            if (iRow % 3 == 1) {
                cout << "---";
                for (int iCol = 0; iCol < 8*kiSquareWidth; ++iCol) {
                    int iSquareCol = iCol/kiSquareWidth;
                    if ((iCol % 4) == 1) {
                        cout << (iSquareCol + 1);
                    } else {
                        cout << '-';
                    }
                }
                cout << endl;
            } else {
                for (int iCol = 1; iCol < 9*kiSquareWidth; ++iCol) {
                    cout << '-';
                }
                cout << endl;
            }
        }
    }

    bool IsInCheck(char PieceColor) {
        // Atrod karali
        int iKingRow;
        int iKingCol;
        for (int iRow = 0; iRow < 8; ++iRow) {
            for (int iCol = 0; iCol < 8; ++iCol) {
                if (MainGameBoard[iRow][iCol] != 0) {
                    if (MainGameBoard[iRow][iCol]->GetColor() == PieceColor) {
                        if (MainGameBoard[iRow][iCol]->GetPiece() == 'K') {
                            iKingRow = iRow;
                            iKingCol = iCol;
                        }
                    }
                }
            }
        }
        //Skatas vai pretinieka figūras var paņemt karali
        for (int iRow = 0; iRow < 8; ++iRow) {
            for (int iCol = 0; iCol < 8; ++iCol) {
                if (MainGameBoard[iRow][iCol] != 0) {
                    if (MainGameBoard[iRow][iCol]->GetColor() != PieceColor) {
                        if (MainGameBoard[iRow][iCol]->IsLegalMove(iRow, iCol, iKingRow, iKingCol, MainGameBoard)) {
                            return true;
                        }
                    }
                }
            }
        }

        return false;
    }

    bool CanMove(char PieceColor) {
        // skatas cauri visiem gabaliem
        for (int iRow = 0; iRow < 8; ++iRow) {
            for (int iCol = 0; iCol < 8; ++iCol) {
                if (MainGameBoard[iRow][iCol] != 0) {
                    //Vai gabalm, pārbauda vai tam ir likumīgs gājiens
                    if (MainGameBoard[iRow][iCol]->GetColor() == PieceColor) {
                        for (int iMoveRow = 0; iMoveRow < 8; ++iMoveRow) {
                            for (int iMoveCol = 0; iMoveCol < 8; ++iMoveCol) {
                                if (MainGameBoard[iRow][iCol]->IsLegalMove(iRow, iCol, iMoveRow, iMoveCol, MainGameBoard)) {
                                    // Veiciet kustību un pārbaudiet, vai karalis ir 
                                    GamePiece* qpTemp                   = MainGameBoard[iMoveRow][iMoveCol];
                                    MainGameBoard[iMoveRow][iMoveCol]   = MainGameBoard[iRow][iCol];
                                    MainGameBoard[iRow][iCol]           = 0;
                                    bool bCanMove = !IsInCheck(PieceColor);
                                   
                                    MainGameBoard[iRow][iCol]           = MainGameBoard[iMoveRow][iMoveCol];
                                    MainGameBoard[iMoveRow][iMoveCol]   = qpTemp;
                                    if (bCanMove) {
                                        return true;
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        return false;
    }

    GamePiece* MainGameBoard[8][8];
};

class ChessBoard
{
public:
    ChessBoard() : mcPlayerTurn('W') {}
    ~ChessBoard() {}

    void Start() {
        do {
            GetNextMove(mqGameBoard.MainGameBoard);
            AlternateTurn();
        } while (!IsGameOver());
        mqGameBoard.Print();
    }

    void GetNextMove(GamePiece* GameBoard[8][8]) {
        using namespace std;
        bool bValidMove     = false;
        do {
            system ("clear");
            cout<<endl<<endl<<"                            Chess Game "<<endl<<endl<<endl;
            cout<<"                         Lietojamie simboli "<<endl<<endl<<endl;
            cout<<" * = balta vieta"<<endl;
            cout<<" Tukša vieta = melna vieta"<<endl;
            cout<<" WP = baltais bandinieks & BP = melns bandinieks"<<endl;
            cout<<" WN = baltais bruņinieks un BN = melnais bruņinieks"<<endl;
            cout<<" WB = baltais bīskaps un BB = melnais bīskaps"<<endl;
            cout<<" WR = Baltais brūķis & BR = Melnais brūķis"<<endl;
            cout<<" WQ = Baltā karaliene & BQ =Melnā karaliene"<<endl;
            cout<<" WK = Baltais karalis & BK =Melnais karalis"<<endl;
            cout<<"Pārvietošanās noteikums ir :"<<endl;
            cout<<"Pārvietojieties, atlasot rindu un kolonnu uz citu derīgu vietu, izmantojot rindu un kolonnu"<<endl<<endl<<endl;
            mqGameBoard.Print();

            // Get input and convert to coordinates
            cout << mcPlayerTurn << "'s Move: ";
            int iStartMove;
            cin >> iStartMove;
            int iStartRow = (iStartMove / 10) - 1;
            int iStartCol = (iStartMove % 10) - 1;

            cout << "To: ";
            int iEndMove;
            cin >> iEndMove;
            int iEndRow = (iEndMove / 10) - 1;
            int iEndCol = (iEndMove % 10) - 1;

            // Pārbaudiet, vai indeksi ir diapazonā
            // 
            if ((iStartRow >= 0 && iStartRow <= 7) &&
                (iStartCol >= 0 && iStartCol <= 7) &&
                (iEndRow >= 0 && iEndRow <= 7) &&
                (iEndCol >= 0 && iEndCol <= 7)) {
          
                GamePiece* qpCurrPiece = GameBoard[iStartRow][iStartCol];
                // pārbaudiet, vai gabalam ir pareizā krāsa
                if ((qpCurrPiece != 0) && (qpCurrPiece->GetColor() == mcPlayerTurn)) {
                    //Pārbaudiet, vai galamērķis ir derīgs galamērķis
                    if (qpCurrPiece->IsLegalMove(iStartRow, iStartCol, iEndRow, iEndCol, GameBoard)) {
                        // Veiciet kustību
                        GamePiece* qpTemp                   = GameBoard[iEndRow][iEndCol];
                        GameBoard[iEndRow][iEndCol]     = GameBoard[iStartRow][iStartCol];
                        GameBoard[iStartRow][iStartCol] = 0;
                        // Pārliecinieties, vai pašreizējais spēlētājs nav čekā
                        if (!mqGameBoard.IsInCheck(mcPlayerTurn)) {
                            delete qpTemp;
                            bValidMove = true;
                        } else { 
                            GameBoard[iStartRow][iStartCol] = GameBoard[iEndRow][iEndCol];
                            GameBoard[iEndRow][iEndCol]     = qpTemp;
                        }
                    }
                }
            }
            if (!bValidMove) {
                cout << "Invalid Move!" << endl;
            }
        } while (!bValidMove);
    }

    void AlternateTurn() {
        mcPlayerTurn = (mcPlayerTurn == 'W') ? 'B' : 'W';
    }

    bool IsGameOver() {
        // Pārbauda vai spēlētājas var kustēties
        // vai spēle ir beigusies
        bool bCanMove(false);
        bCanMove = mqGameBoard.CanMove(mcPlayerTurn);
        if (!bCanMove) {
            if (mqGameBoard.IsInCheck(mcPlayerTurn)) {
                AlternateTurn();
                std::cout << "Checkmate, " << mcPlayerTurn << " Wins!" << std::endl;
            } else {
                std::cout << "Stalemate!" << std::endl;
            }
        }
        return !bCanMove;
    }
private:
    CBoard mqGameBoard;
    char mcPlayerTurn;
};

int main() {
    ChessBoard qGame;
    qGame.Start();
    return 0;
}