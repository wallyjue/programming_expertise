#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ARRAY_MIN   3
#define ARRAY_MAX   15
#define INPUT_SIZE  32
int check_availability(int x, int x_size, int y, int y_size)
{
    return 0;
}

int main()
{
//#ifndef ONLINE_JUDGE
    freopen("in.txt", "r",stdin);
//#endif
    int q = 0, x = 0, y = 0, x_size = 0, y_size = 0;
    int cnt, cnt2, line_size = 0;
    size_t input_size;
    char* rawinput;
    
    int **board = NULL;

    while( getline( &rawinput, &input_size, stdin) >0 )
    {
        if( rawinput == NULL || atoi(rawinput) == 0)
        {
            break;
        }
        q = atoi(rawinput);
        printf("q:%d\n", q);
        board = (int**) malloc( sizeof(int)*q*q);
        for( cnt = 0; cnt < q; cnt++){
            getline( &rawinput, &input_size, stdin);
            printf("%s", rawinput);
        }
        free( board);
    }


    return 0;
}

