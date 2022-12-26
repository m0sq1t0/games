#include <stdio.h>
#include <stdlib.h>
#include "getch.h"

// キャラクターの構造体を宣言する
typedef struct {
    int hp;        // HP     
    int maxHp;     // 最大HP
    int mp;        // MP
    int maxMp;     // 最大MP
    char name[20]; // 名前
    char aa[256];  // モンスターのアスキーアート
    int  command;  // コマンド
} CHARACTER; 

// モンスターの種類を宣言する
enum
{
    MONSTER_PLAYER, // プレイヤー
    MONSTER_SLIME,  // スライム
    MONSTER_MAX // モンスターの種類数
};

// モンスターのステータつの配列を定義する
CHARACTER monsters[MONSTER_MAX] = {
        { 15,15,15,15, "ゆうしゃ", ""},
        {  3, 3, 0, 0, "スライム", 
        "／・д・＼\n"
        "〜〜〜〜〜"
        },
};

// キャラクターの種類を宣言する
enum
{
    CHARACTER_PLAYER, // プレイヤー
    CHARACTER_MONSTER, // モンスター
    CHARACTER_MAX, // キャラクターの種類数
};

// キャラクターの配列を定義する
CHARACTER characters[CHARACTER_MAX];

// コマンドの種類を定義する
enum
{
    COMMAND_FIGHT, // 戦う
    COMMAND_SPELL, // 呪文
    COMMAND_RUN,   // 逃げる
    COMMAND_MAX,   // コマンドの種類の数
};

// ゲームを初期化する関数を定義する
void Init()
{
    // プレイヤーのステータスを初期化する
    characters[CHARACTER_PLAYER] = monsters[MONSTER_PLAYER];
}

//戦闘シーンの画面を描画する関数を定義する
void DrawBattleScreen()
{
    // 画面をクリアする (Linux)
    system("clear"); 
    // プレイヤーの名前を表示する 
    printf("%s\n",characters[MONSTER_PLAYER].name);
    // プレイヤーのステータスを表示する
    printf("ＨＰ：%d／%d　ＭＰ：%d／%d\n",
            characters[MONSTER_PLAYER].hp,
            characters[MONSTER_PLAYER].maxHp,
            characters[MONSTER_PLAYER].mp,
            characters[MONSTER_PLAYER].maxMp
        );
    printf("\n");
    // モンスターのアスキーアートを描画する 
    printf("%s", characters[CHARACTER_MONSTER].aa);
    // モンスターのHPを表示する
    printf("（ＨＰ：%d／%d）\n",
            characters[MONSTER_SLIME].hp,
            characters[MONSTER_SLIME].maxHp);
    printf("\n");
}

// コマンドの名前を宣言する
char commandNames[COMMAND_MAX][20] = {
    "たたかう",
    "じゅもん",
    "にげる",
};
// コマンドを選択する関数を定義する
void SelectCommand()
{
    // コマンドが決定されるまでループする
    while(1) {
        // コマンドの一覧を表示する
        for (int i = 0; i < COMMAND_MAX; i++) {
            // コマンドの名前を表示する
            printf("%s\n", commandNames[i]);
        }
        // 入力されたキーによって分岐する
        switch(getch()) {

        }
    }
}

// 戦闘シーンの関数を定義する
void Battle(int _monster)
{
    // モンスターのステータスを初期化する
    characters[CHARACTER_MONSTER] = monsters[_monster];
    // 戦闘シーンの最初のメッセージを表示する
    printf("%sが　あらわれた！\n", characters[CHARACTER_MONSTER].name);
    // キーボードから１文字読みこむ (Linux)
    getch();

    // 戦闘シーンを描画する関数を呼び出す
    DrawBattleScreen();

    // 戦闘が終了するまでループする
    while(1) {
        // 各キャラクターを反復する
        for (int i = 0; i < CHARACTER_MAX; i++) {
            // キャラクターが切り替わる毎に戦闘シーンを描画する関数を呼び出す
            DrawBattleScreen();
            // コマンドを選択する関数を呼び出す
            SelectCommand();
            // 選択されたコマンドで分岐する
            switch (characters[i].command) {
                case COMMAND_FIGHT: // 戦う
                    printf("%sの　こうげき！\n", characters[i].name);
                    getch(); // キーボード入力を待つ
                    break;
                case COMMAND_SPELL: // 呪文
                    break;
                case COMMAND_RUN:   // 逃げる
                    break;
            }
        }
    }
}

int main()
{
    // ゲームを初期化する関数を呼び出す
    Init();
    // 戦闘シーンの関数を呼び出す
    Battle(MONSTER_SLIME);
    return 0;
}