// [1] ヘッダーをインクルードする場所
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "time.h"
#include "getch.h" // getch()関数を使用するために必要

// [2] 定数を定義する場所
#define FIELD_WIDTH  (160) // [2-1]フィールドの幅を定義する
#define FIELD_HEIGHT (160) // [2-1]フィールドの高さを定義する
#define FPS (5)           // [2-3]1秒当たりの更新回数を定義する
#define INTERVAL (1000000/FPS) // [2-4]更新間隔 (ナノ秒)を定義する

// [3] 変数を定義する場所
// [3-1] フィールドを定義する
bool field[FIELD_HEIGHT][FIELD_WIDTH] = {
    /*
    {0,1,0}, // 足りない部分は0 (false)で埋まる
    {0,0,1},
    {1,1,1},
    */
};

// [4] 関数を定義する場所
// [4-1] フィールドを描画する関数を定義する
void DrawField()
{
    system("clear"); // [4-1-1] 画面をクリアする
    // [4-1-1-1] 枠を描く
    for (int x = 0; x < FIELD_WIDTH+2; x++) {putc('+',stdout);} putc('\n', stdout);
    // [4-1-2] フィールドのすべての行を反復する
    for (int y = 0; y < FIELD_HEIGHT; y++) {
        // [4-1-2-1] 枠を描く
        putc('|',stdout);
        // [4-1-3] フィールドのすべての列を反復する
        for (int x = 0; x < FIELD_WIDTH; x++) {
            // [4-1-4]セルが生きていれば'■'を、死んでいれば'　’を描画する
            // printf("%s", field[y][x]? "■":"　");
            printf("%s", field[y][x]? "*":" ");
        }
        printf("|\n"); // [4-1-5] 1行描画する毎に改行する (枠も描く)
    }
    // [4-1-1-1] 枠を描く
    for (int x = 0; x < FIELD_WIDTH+2; x++) {putc('+',stdout);} putc('\n', stdout);
}
// [4-2] 対象のセルと隣接する生きたセルの数を取得する関数を宣言する
int GetLivingCellsCount(int _x, int _y)
{
    int count = 0; // [4-2-1] 生きているセルを数えるカウンターを定義する
    // [4-2-2] 対象のセルの上下一マスを反復する
    for (int y = _y -1; y <= _y + 1; y++) {
        // [4-2-3] 行が範囲内かどうか判定する
        if ((y < 0) || (y >= FIELD_HEIGHT)) {
            continue; // [4-2-4] 範囲外の行なのでスキップする
        }
        // [4-2-6]対象のセルの左右一マスを反復する
        for (int x = _x - 1; x <= _x + 1; x++) {
            // [4-2-7]列が範囲内かどうか判定する
            if ((x < 0) || (x >= FIELD_WIDTH)) {
                continue; // [4-2-8] 範囲外の列なのでスキップする
            }
            // [4-2-10]対象の座標が、中心のセルと同じかどうか判定する
            if ((x == _x) && (y == _y)) {
                continue; // [4-2-11]対象の座標をスキップする
            }
            // [4-2-12]対象のセルが生きていれば1を加算する
            count += field[y][x];
        }
    }

    return count;  // [4-2-13] 生きているセルの数を返す
}
// [4-3] 1ステップ分のシミュレーションを実行する関数を宣言する
void StepSimulation()
{
    // [4-3-1]次の世代のフィールドを宣言する
    bool nextField[FIELD_HEIGHT][FIELD_WIDTH] = {};
    // [4-3-2]すべての行を反復する
    for (int y = 0; y < FIELD_HEIGHT; y++) {
        // [4-3-3]すべての列を反復する
        for (int x = 0; x < FIELD_WIDTH; x++) {
            // [4-3-4]対象のセルと隣接する、生きているセルの数を取得する
            int livingCellCount = GetLivingCellsCount(x, y);
            // [4-3-5]隣接する生きているセルの数で分岐する
            if (livingCellCount <= 1) {
                // [4-3-6] 対象のセルを死滅させる
                nextField[y][x] = false;
            } else if (livingCellCount == 2) {
                // [4-3-8] 現状維持
                nextField[y][x] = field[y][x];
            } else if (livingCellCount == 3) {
                // [4-3-10] 対象のセルを誕生/生存させる 
                nextField[y][x] = true;
            } else {
                // [4-3-12] 対象のセルを死滅させる 
                nextField[y][x] = false;
            }
        }
        printf("\n");
    }
    // [4-3-13]次のステップのフィールドを現在のフィールドにコピーする
    memcpy(field, nextField, sizeof(field));
}
// [4-4]パターンをフィールドにコピーする関数を定義する
void PatternTransfer(
    int _destX, int _destY,
    int _srcWidth, int _srcHeight,
    bool *_pPattern)
{
    // [4-4-1]パターン内の全ての行を反復する
    for (int y = 0; y < _srcHeight; y++) {
        // [4-4-2]パターン内の全ての列を反復する
        for (int x = 0; x < _srcWidth; x++) {
            // [4-4-3]パターンをフィールドにコピーする
            field[_destY + y][_destX + x] = _pPattern[y * _srcWidth + x];
        }
    }
}
// [4-5] ログラムの開始点を定義する
int main()
{
    const int patternWidth = 10; // [4-5-1] パターンの幅を定義する
    const int patternHeight = 8; // [4-5-2] パターンの高さを定義する

    // [4-5-3] 初期パターンを定義する
    bool pattern[patternHeight][patternWidth] =
    {
        {0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,1,0,0},
        {0,0,0,0,0,1,0,1,1,0},
        {0,0,0,0,0,1,0,1,0,0},
        {0,0,0,0,0,1,0,0,0,0},
        {0,0,0,1,0,0,0,0,0,0},
        {0,1,0,1,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0},
    };

    PatternTransfer(
        FIELD_WIDTH / 2 - patternWidth / 2,
        FIELD_HEIGHT / 2 - patternHeight / 2,
        patternWidth,
        patternHeight,
        (bool*)pattern);

    clock_t lastClock = clock(); // [4-5-5]前回の経過時間を定義する
    // [4-5-6] メインループ
    while(1) {
        clock_t newClock = clock(); // [4-5-7] // 現在の経過時間を定義する
        // [4-5-8] 前回の経過時間から、待機時間が経過していなければ
        if (newClock < (lastClock + INTERVAL)) {
            continue; // 待機状態に戻る
        }
        // 前回の経過時間を、現在の経過時間で更新する
        lastClock = newClock;
        DrawField(); // [4-5-11]フィールドを描画する関数を呼び出す
        // getch();     // [4-5-12]キーボード入力を待つ
        StepSimulation(); // [4-5-13]シミュレーションを進める
    }
}