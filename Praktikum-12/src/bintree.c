#include "bintree.h"
#include <stdio.h>
#include <stdlib.h>

BinTree Tree(infotype Akar, BinTree L, BinTree R){
    BinTree result = AlokNode(Akar);
    if (result != Nil){
        Left(result) = L;
        Right(result) = R;
    }
    return result;
}

void MakeTree(infotype Akar, BinTree L, BinTree R, BinTree *P){
    *P = Tree(Akar, L, R);
}

BinTree BuildBalanceTree(int n){
    if (n==0){
        return Nil;
    } else {
        int X;
        scanf("%d", &X);
        BinTree P = AlokNode(X);
        if (P != Nil){
            int nL = n/2;
            int nR = n-nL-1;
            BinTree L = BuildBalanceTree(nL);
            BinTree R = BuildBalanceTree(nR);
            Left(P) = L;
            Left(P) = R;
        }
        return P;
    }
}

addrNode AlokNode(infotype X){
    addrNode result;
    result = (addrNode) malloc (sizeof(Node));
    if (result != Nil){
        Akar(result) = X;
        Left(result) = Nil;
        Right(result) = Nil;
    }
    return result;
}

void DealokNode(addrNode P){
    free(P);
}

boolean IsTreeEmpty(BinTree P){
    return P == Nil;
}

boolean IsTreeOneElmt(BinTree P){
    if (!IsTreeEmpty(P)){
        return ((Left(P) == Nil) && (Right(P) == Nil));
    } else {
        return false;
    }
}

boolean IsUnerLeft(BinTree P){
    if (!IsTreeEmpty(P)){
        return ((Left(P) != Nil) && (Right(P) == Nil));
    } else {
        return false;
    }
}

boolean IsUnerRight(BinTree P){
    if (!IsTreeEmpty(P)){
        return ((Left(P) == Nil) && (Right(P) != Nil));
    } else {
        return false;
    }
}

boolean IsBiner(BinTree P){
    if (!IsTreeEmpty(P)){
        return ((Left(P) != Nil) && (Right(P) != Nil));
    } else {
        return false;
    }
}

void PrintPreorder(BinTree P){
    printf("(");
    if (!IsTreeEmpty(P)){
        printf("%d", Akar(P));
        PrintPreorder(Left(P));
        PrintPreorder(Right(P));
    }
    printf(")");
}

void PrintInorder(BinTree P){
    printf("(");
    if (!IsTreeEmpty(P)){
        PrintInorder(Left(P));
        printf("%d", Akar(P));
        PrintInorder(Right(P));
    }
    printf(")");
}

void PrintPostorder(BinTree P){
    printf("(");
    if (!IsTreeEmpty(P)){
        PrintPostorder(Left(P));
        PrintPostorder(Right(P));
        printf("%d", Akar(P));
    }
    printf(")");
}

void BetterPrintTree(BinTree P, int h, int lv){
    if(!IsTreeEmpty(P)){
        int i;
        for(i = 0; i < h*lv; i++){
            printf(" ");
        }
        printf("%d\n", Akar(P));
        BetterPrintTree(Left(P), h, lv+1);
        BetterPrintTree(Right(P), h, lv+1);
    }
}
void PrintTree(BinTree P, int h){
    BetterPrintTree(P, h, 0);
}

boolean SearchTree(BinTree P, infotype X){
    if (IsTreeEmpty(P)){
        return false;
    } else if (Akar(P) == X){
        return true;
    } else {
        return SearchTree(Left(P), X) || SearchTree(Right(P), X);
    }
}

boolean SearchDaun(BinTree P, infotype X){
    if (IsTreeOneElmt(P)){
        return Akar(P) == X;
    } else {
        return SearchDaun(Left(P), X) || SearchDaun(Right(P), X);
    }
}

int NbElmt(BinTree P){
    if (IsTreeEmpty(P)){
        return 0;
    } else {
        return 1 + NbElmt(Left(P)) + NbElmt(Right(P));
    }
}

int NbDaun(BinTree P){
    if (IsTreeOneElmt(P)){
        return 1;
    } else if (IsUnerLeft(P)){
        return NbDaun(Left(P));
    } else if (IsUnerRight(P)){
        return NbDaun(Right(P));
    } else { //IsBiner
        return NbDaun(Left(P)) + NbDaun(Right(P));
    }
}

boolean IsSkewLeft(BinTree P){
    return Tinggi(Left(P)) > Tinggi(Right(P));
}

boolean IsSkewRight(BinTree P){
    return Tinggi(Left(P)) < Tinggi(Right(P));
}

int Level(BinTree P, infotype X){
    if (Akar(P) == X){
        return 1;
    } else if (IsBiner(P)){
        if (SearchTree(Left(P), X)){
            return 1+Level(Left(P), X);
        } else {
            return 1+Level(Right(P), X);
        }
    } else if (IsUnerLeft(P)){
        return 1+Level(Left(P), X);
    } else if (IsUnerRight(P)){
        return 1+Level(Right(P), X);
    }
}

int Tinggi(BinTree P){
    if (IsTreeEmpty(P)){
        return 0;
    } else {
        int tR = Tinggi(Right(P));
        int tL = Tinggi(Left(P));
        return 1 + (tR > tL ? tR : tL);
    }
}

void AddDaunTerkiri(BinTree *P, infotype X){
    if (IsTreeEmpty(*P)){
        *P = AlokNode(X);
    } else if (IsUnerRight(*P)){
        Left(*P) = AlokNode(X);
    } else {
        AddDaunTerkiri(&(Left(*P)), X);
    }
}

void AddDaun(BinTree *P, infotype X, infotype Y, boolean Kiri){
    if (IsTreeOneElmt(*P) && Akar(*P) == X){
        if (Kiri){
            Left(*P) = AlokNode(Y);
        } else {
            Right(*P) = AlokNode(Y);
        }
    } else if (IsUnerRight(*P)){
        AddDaun(&(Right(*P)), X, Y, Kiri);
    } else if (IsUnerLeft(*P)){
        AddDaun(&(Left(*P)), X, Y, Kiri);
    } else {
        if (SearchDaun(Left(*P), X)){
            AddDaun(&(Left(*P)), X, Y, Kiri);
        } else {
            AddDaun(&(Right(*P)), X, Y, Kiri);
        }
    }
}

void DelDaunTerkiri(BinTree *P, infotype *X){
    if (IsTreeOneElmt(*P)){
        *X = Akar(*P);
        BinTree N = *P;
        *P = Nil;
        DealokNode(N);
    } else if (IsUnerRight(*P)){
        DelDaunTerkiri(&(Right(*P)), X);
    } else {
        DelDaunTerkiri(&(Left(*P)), X);
    }
}

void DelDaun(BinTree *P, infotype X){
    if (IsTreeOneElmt(*P) && Akar(*P) == X){
        BinTree N = *P;
        *P = Nil;
        DealokNode(N);
    } else if (IsUnerRight(*P)){
        DelDaun(&(Right(*P)), X);
    } else if (IsUnerLeft(*P)){
        DelDaun(&(Left(*P)), X);
    } else {
        if (SearchDaun(Left(*P), X)){
            DelDaun(&(Left(*P)), X);
        }
        if (SearchDaun(Right(*P), X)){
            DelDaun(&(Right(*P)), X);
        }
    }
}


List MakeListPreorder(BinTree P){
    if (IsTreeEmpty(P)){
        return Nil;
    } else {
        address E = Alokasi(Akar(P));
        if (E != Nil){
            Next(E) = MakeListPreorder(Left(P));
            return Concat(E, MakeListPreorder(Right(P)));
        } else {
            return Nil;
        }
    }
}

List MakeListLevel(BinTree P, int N){
    if (IsTreeEmpty(P)){
        return Nil;
    } else if (N == 1){
        return Alokasi(Akar(P));
    } else {
        address E = Alokasi(Akar(P));
        if (E != Nil){
            Next(E) = MakeListLevel(Left(P), N-1);
            return Concat(E, MakeListLevel(Right(P), N-1));
        } else {
            return Nil;
        }
    }
}

List MakeListDaun(BinTree P){
    if (IsTreeEmpty(P)){
        return Nil;
    } else if (IsTreeOneElmt(P)){
        return Alokasi(Akar(P));
    } else if (Tinggi(Left(P)) == 1 && Tinggi(Right(P)) == 1){
        return Concat(Alokasi(Akar(Left(P))), Alokasi(Akar(Right(P))));
    } else if (Tinggi(Left(P)) == 1){
        return Concat(Alokasi(Akar(Left(P))), MakeListDaun(Right(P)));
    } else if (Tinggi(Right(P)) == 1){
        return Concat(MakeListDaun(Left(P)), Alokasi(Akar(Right(P))));
    } else {
        return Concat(MakeListDaun(Left(P)), MakeListDaun(Right(P)));
    }
}

boolean BSearch(BinTree P, infotype X){
    if (IsTreeEmpty(P)){
        return false;
    } else if (Akar(P) == X){
        return true;
    } else {
        if (X < Akar(P)){
            return BSearch(Left(P), X);
        } else {
            return BSearch(Right(P), X);
        }
    }
}

void InsSearch(BinTree *P, infotype X){
    if (IsTreeEmpty(*P)){
        MakeTree(X, Nil, Nil, P);
    } else if (X == Akar(*P)){
        return; //Do Nothing karena udah ada
    } else if (X < Akar(*P)){
        InsSearch(&(Left(*P)), X);
    } else if (X > Akar(*P)){
        InsSearch(&(Right(*P)), X);
    }
}

void DelBtree(BinTree *P, infotype X){
    if(Akar(*P)==X){
        addrNode Q = *P;
        *P = Nil;
        DealokNode(Q);
    }else if(X<Akar(*P)){
        DelBtree(&Left(*P), X);
    }else{
        DelBtree(&Right(*P), X);
    }
}