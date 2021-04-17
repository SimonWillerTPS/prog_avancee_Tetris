// #include "board.hpp"

// board = new Board(0);

// void IA_play()
// {
//     while(board->gameOver == false)
//     {
//         Piece cur_p = board->getcurPiece();
//         int posx = cur_p.getX();
//         int posy = cur_p.getY();
//         int orientation = cur_p.getOrient();
//         int type = cur_p.getType();
//         int score[8][4] = {};   
//         int best_posx = 30;
//         if (board->isPieceMovable(posx + 1,posy))
//         {
//             board->movePieceDown();
//             if (type == 1)//I
//             {

//             }
//             while (board->isPieceMovable(posx,posy-1))
//             {
//                 board->movePieceLeft();
//                 posx = cur_p.getX();
//                 posy = cur_p.getY();
//                 orientation = cur_p.getOrient();
//             }
            
//             for(int i = 0; i<4 ; i++)
//                 {
//                     if (board->isPieceRotable(orientation))
//                     {
//                         board->rotatePiece();
//                         posx = cur_p.getX();
//                         posy = cur_p.getY();
//                         orientation = cur_p.getOrient();
//                         score[posy][orientation] += posx *2;
//                         score[posy][orientation] += board->deletePossibleLinesIA()*5000;
//                         score[posy][orientation] += board->pointsIA(); 
//                     }
//                 }

//             while (board->isPieceMovable(posx,posy+1))
//             {
//                 for(int i = 0; i<4 ; i++)
//                 {
//                     if (board->isPieceRotable(orientation))
//                     {
//                         board->rotatePiece();
//                         posx = cur_p.getX();
//                         posy = cur_p.getY();
//                         orientation = cur_p.getOrient();
//                         score[posy][orientation] += posx *2;
//                         score[posy][orientation] += board->deletePossibleLinesIA()*5000;
//                         score[posy][orientation] += board->pointsIA();  
//                     }
//                 }

//             }
//         }
//         int best_orientation =0; 
//         int best_score = 0 ;
//         for (int i = 0; i < 8; i++)
//         {
//             for (int j = 0; j < 4; j++)
//             {
//                 if (best_score < score[i][j])
//                 {
//                     best_score = score[i][j];
//                     best_posx = i;
//                     best_orientation = j ;

//                 }
                
//             }     
//         }
//         board->currentPiece.setOrient(best_orientation);
//         board->currentPiece.setX(best_posx);
//         board->dropPiece();
//     }
// }

