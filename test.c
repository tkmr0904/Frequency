#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define width 2001
#define height 1000
#define num_data 2001
#define times 10000


void drawbox(int color[], int size_x, int size_y, int x, int y, int size)//指定された座標を中心とする正方形を描画する(黒色)
{
    int halfsize = size/2;
    for(int j = y-halfsize; j<=y+halfsize; j++)
    {
        for(int i = x-halfsize; i<=x+halfsize; i++)
        {
            if((0<=i)&&(0<=j)&&(i<size_x)&&(j<size_y))
            {
                color[size_x*j+i] = 0;
            }
        }
    }
}

int abc(char input[], char output[])
{
    int *color = malloc(width*height*sizeof(int));

    /**********まずは全部白に*************/
    for(int i = 0; i<width*height; i++)
    {
        color[i] = 255;
    }
    /***********************************/

    /************************************/
    double magnitude[num_data];
    double frequency[num_data];
    /***********************************/

    FILE* fp;
    char str[100];

    /************数値の取得*******************************/
    snprintf(str, 99, "%s.txt", input);
    fp = fopen(str, "r");
    for(int i = 0; i<num_data; i++)
    {
        if(feof(fp))
        {
            printf("end of the file\n");
            return 1;
        }
        else
        {
            fscanf(fp, "%lf\x09%lf\n", frequency + i, magnitude + i);
        }
    }
    fclose(fp);
    /******************************************************/
    

    #if 1
    /****************ppmに書くためのデータを一旦配列に**********/
    for(int i = 0; i<num_data; i++)
    {
        drawbox(color, width, height, (int)(frequency[i]/3), (height-1-(int)(magnitude[i]*times)), 2);
    }
    /******************************************************/


    
    /*************ppmに書く*********************************/
    snprintf(str, 99, "%s.ppm", output);
    fp = fopen(str, "wb");
    fprintf(fp, "P6\n%d %d\n255\n", width, height);

    for(int i = 0; i<width*height; i++)
    {
        fprintf(fp, "%c%c%c", color[i], color[i], color[i]);
    }
    fclose(fp);
    /******************************************************/
    

    /*********ppmをpngに変換し元のppmを消す****その後,そのpngを表示する******/
    snprintf(str, 99, "convert %s.ppm ./PNG/%s.png", output, output);
    system(str);

    snprintf(str, 99, "rm %s.ppm", output);
    system(str);

    snprintf(str, 99, "eog ./PNG/%s.png &", output);
    system(str);
    /*****************************************************************/
    #endif

    #if 1
    snprintf(str, 99, "./CSV/%s.csv", output);
    fp = fopen(str, "w");
    for(int i = 0; i<num_data; i++)
    {
        fprintf(fp, "%.6e,%.6e\n", frequency[i], magnitude[i]);
    }
    #endif




    free(color);
    
    return 0;
}

int main()
{    
    #if 1
    abc("ド", "ド");
    #endif


    #if 0
    for(int i = 1; i<=6; i++)
    {
        char input[20];
        char output[20];
        snprintf(input, 19, "和音%d", i);
        snprintf(output, 19, "和音%d", i);

        abc(input, output);
    }
    #endif

    #if 0

    abc("R304.1", "R304.1");
    abc("R1497", "R1497");
    abc("R5110", "R5110");
    abc("R10380", "R10380");
    abc("Through", "Through");

    #endif




    
}