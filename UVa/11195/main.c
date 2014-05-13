#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_MIN   3
#define ARRAY_MAX   15
#define INPUT_SIZE  32

#define POS_VACANCY     0
#define POS_OCCUPIED    10
#define POS_MARKED      20
#define POS_NA          3

int mark_pos(int** board, int x, int y, int q)
{
    int i = 0, j = 0;
    int flag = 0;
    for( i = 0; i < q; i++){
        j = y;
        if(board[i][j] == POS_VACANCY){
            board[i][j] = POS_OCCUPIED;
        }
    }           
    for( j = 0; j < q; j++){
        i = x;
        if(board[i][j] == POS_VACANCY){
            board[i][j] = POS_OCCUPIED;
        }
    }
    for( i = x, j = y; i < q && j < q; i++, j++){
        if(board[i][j] == POS_VACANCY){
            board[i][j] = POS_OCCUPIED;
        }
    }
    for( i = x, j = y; i >= 0 && j >= 0; i--, j--){
        if(board[i][j] == POS_VACANCY){
            board[i][j] = POS_OCCUPIED;
        }
    }
    for( i = x, j = y; i < q && j >= 0; i++, j--){
        if(board[i][j] == POS_VACANCY){
            board[i][j] = POS_OCCUPIED;
        }
    }
    for( i = x, j = y; i >= 0 && j < q; i--, j++){
        if(board[i][j] == POS_VACANCY){
            board[i][j] = POS_OCCUPIED;
        }
    }
    board[x][y] = POS_MARKED;
    return 0;
}

int check_pos(int** board,int x, int y, int q)
{
    int i = 0, j = 0;
    int flag = 0;
    for( i = 0; i < q; i++){
        j = y;
//        printf("x:%d y:%d %x %d\n",i,j, board, board[i][j]);
        if( board[i][j] == POS_MARKED){
            flag = POS_OCCUPIED;
        }
    }           
    for( j = 0; j < q; j++){
        i = x;
//        printf("x:%d y:%d %x %d\n",i,j, board, board[i][j]);
        if( board[i][j] == POS_MARKED){
            flag = POS_OCCUPIED;
        }
    }
    for( i = x, j = y; i < q && j < q; i++, j++){
//        printf("x:%d y:%d %x %d\n",i,j, board, board[i][j]);
        if( board[i][j] == POS_MARKED){
            flag = POS_OCCUPIED;
        }
    }
    for( i = x, j = y; i >= 0 && j >= 0; i--, j--){
//        printf("x:%d y:%d %x %d\n",i,j, board, board[i][j]);
        if( board[i][j] == POS_MARKED){
            flag = POS_OCCUPIED;
        }
    }
    
    for( i = x, j = y; i < q && j >= 0; i++, j--){
//        printf("x:%d y:%d %x %d\n",i,j, board, board[i][j]);
        if( board[i][j] == POS_MARKED){
            flag = POS_OCCUPIED;
        }
    }
    for( i = x, j = y; i >= 0 && j < q; i--, j++){
//        printf("x:%d y:%d %x %d\n",i,j, board, board[i][j]);
        if( board[i][j] == POS_MARKED){
            flag = POS_OCCUPIED;
        }
    }
    return flag;
}

int dump_board( int** board, int q)
{
    int i =0, j = 0;
    for( i = 0; i < q; i++){
        for( j = 0; j < q; j++){
            printf("%3d", board[i][j]);
        }
        printf("\n");
    }
    return 0;
}

int clean_route(int** board, int q)
{
    int x,y;
    for(x =0; x<q;x++){
        for(y=0;y<q;y++){
            if(board[x][y] == POS_OCCUPIED)
            {
                board[x][y] = POS_VACANCY;
            }
            if(board[x][y] == POS_MARKED)
            {
                board[x][y] = POS_VACANCY;
            }
        }
    }
    return 0;
}


int parse_board(int** board,int x_init, int y_init, int q)
{
    int x, y;
    int i = 0, j = 0;
    int flag = 0;
    for( x = x_init; x < q; x++){
        for( y = y_init; y < q; y++){
            //printf("%x %d\n", board, board[x][y]);
            
            if( board[x][y] != POS_NA && check_pos( board, x, y, q) == 0){
                printf("x:%d y:%d\n", x ,y);
                mark_pos( board, x, y, q);
                dump_board(board,q);
                return 1;
            }
//            printf("\n");
        }
//        printf("\n");
    }
    return 0;
}

int main()
{
//#ifndef ONLINE_JUDGE
    freopen("in.txt", "r",stdin);
//#endif
    int q = 0, x = 0, y = 0, x_size = 0, y_size = 0;
    int cnt = 0, cnt2 = 0, line_size = 0;
    size_t input_size;
    char* rawinput;
    
    int final_num = 0;
    int **board = NULL;
    int ret = 0;
    while( getline( &rawinput, &input_size, stdin) >0 )
    {
        if( rawinput == NULL || atoi(rawinput) == 0)
        {
            break;
        }
        q = atoi(rawinput);
//        printf("q:%d\n", q);
        board = (int**) malloc( sizeof(int*)*q);
        for( x = 0; x < q; x++){
            board[x] = (int*)malloc(sizeof(int)* q);
            getline( &rawinput, &input_size, stdin);
//            printf("%s", rawinput);
            for( y = 0; y < q; y++){
                
                if(rawinput[y] == '*'){
                    board[x][y] = POS_NA;
                }else{
                    board[x][y] = 0;
                }
//                printf("%d", board[x][y]);
            }
//            printf("\n");
        }
        for( x = 0; x < q; x++){
            for( y = 0; y < q ; y++){
                for( cnt = 0; cnt < q; cnt++){
                    ret += parse_board(board,x,y, q);
                }
                printf("ret:%d\n", ret);
                if( ret != q){
                    clean_route(board,q);
                    dump_board(board,q);
                }
                else{
                    final_num++;
                }
                ret = 0;
                printf("\n");
//                board[x][y] = POS_NA;
            }
        }
        printf("final_num:%d\n", final_num);
        final_num = 0;
        free( board);
    }


    return 0;
}

