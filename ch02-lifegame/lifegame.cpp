// [1] ヘッダーをインクルードする場所
#include <stdio.h>
#include <stdlib.h>
#include "getch.h" // getch()関数を使用するために必要

// [2] 定数を定義する場所
#define FIELD_WIDTH  (12) // [2-1]フィールドの幅を定義する
#define FIELD_HEIGHT (12) // [2-1]フィールドの高さを定義する

// [3] 変数を定義する場所
// [3-1] フィールドを定義する
bool field[FIELD_HEIGHT][FIELD_WIDTH] = {
    {0,1,0}, // 足りない部分は0 (false)で埋まる
    {0,0,1},
    {1,1,1},
};

// [4] 関数を定義する場所
// [4-1] フィールドを描画する関数を定義する
void DrawField()
{
    system("clear"); // [4-1-1] 画面をクリアする
    // [4-1-2] フィールドのすべての行を反復する
    for (int y = 0; y < FIELD_HEIGHT; y++) {
    // [4-1-3] フィールドのすべての列を反復する
        for (int x = 0; x < FIELD_WIDTH; x++) {
            // [4-1-4]セルが生きていれば'■'を、死んでいれば'　’を描画する
            printf("%s", field[y][x]? "■":"　");
        }
        printf("\n"); // [4-1-5] 1行描画する毎に改行する
    }
}
// [4-5] ログラムの開始点を定義する
int main()
{
    // [4-5-6] メインループ
    while(1) {
        DrawField(); // [4-5-11]フィールドを描画する関数を呼び出す
        getch();     // [4-5-12]キーボード入力を待つ
    }
}