#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "getch.h"

// キャラクターの構造体を宣言する
typedef struct {
    int hp;        // HP     
    int maxHp;     // 最大HP
    int mp;        // MP
    int maxMp;     // 最大MP
    int  attack;   // 攻撃力
    char name[20]; // 名前
    char aa[256];  // モンスターのアスキーアート
    int  command;  // コマンド
    int  target;   // 攻撃対象
} CHARACTER; 

// モンスターの種類を宣言する
enum
{
    MONSTER_PLAYER, // プレイヤー
    MONSTER_SLIME,  // スライム
    MONSTER_BOSS,   // 魔王
    MONSTER_MAX // モンスターの種類数
};

// モンスターのステータつの配列を定義する
CHARACTER monsters[MONSTER_MAX] = {
        { 100,100,15,15, 30, "ゆうしゃ", ""},
        {  3, 3, 0, 0, 2, "スライム",
        "／・д・＼\n"
        "〜〜〜〜〜"
        },
        { 255,255,255,255, 50, "まおう",
        "　Ａ＠Ａ\n"
        "ψ（▼皿▼）ψ"},
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
        // 戦闘画面を描画する関数を呼び出す
        DrawBattleScreen();
        // コマンドの一覧を表示する
        for (int i = 0; i < COMMAND_MAX; i++) {
            // 選択中のコマンドなら
            if (i == characters[CHARACTER_PLAYER].command) {
                // カーソルを描画する
                printf("＞");
            } else {
                // そうでなければ全角スペースを表示する
                printf("　");
            }
            // コマンドの名前を表示する
            printf("%s\n", commandNames[i]);
        }
        // 入力されたキーによって分岐する
        switch(getch()) {
            case 'w': // wキーが押されたら
                // 上のコマンドに切り替える
                characters[CHARACTER_PLAYER].command--;
                break;
            case 's': // sキーが押されたら
                // 下のコマンドに切り替える
                characters[CHARACTER_PLAYER].command++;
                break;
            default: // 上記以外のキーが押されたら
                return;  // 関数を抜ける
        }
        // カーソルを上下にループさせる
        characters[CHARACTER_PLAYER].command = 
            (COMMAND_MAX + characters[CHARACTER_PLAYER].command) % COMMAND_MAX;
    }
}

// 戦闘シーンの関数を定義する
void Battle(int _monster)
{
    // モンスターのステータスを初期化する
    characters[CHARACTER_MONSTER] = monsters[_monster];
    // プレイヤーの攻撃対象をモンスターに設定する
    characters[CHARACTER_PLAYER].target = CHARACTER_MONSTER;
    // モンスターの攻撃対象をプレイヤーに設定する
    characters[CHARACTER_MONSTER].target = CHARACTER_PLAYER;

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
                {
                    printf("%sの　こうげき！\n", characters[i].name);
                    // 敵に与えるダメージを計算する
                    int damage = 1 + rand() % characters[i].attack;
                    // 敵にダメージを与える
                    characters[characters[i].target].hp -= damage;
                    getch(); // キーボード入力を待つ
                    printf("%sに　%dの　ダメージ！\n",
                        characters[characters[i].target].name, damage);
                    getch(); // キーボード入力を待つ
                    // 敵のHPが負になったかどうかを判定する
                    if (characters[characters[i].target].hp < 0) {
                        // 敵のHPを0にする
                        characters[characters[i].target].hp = 0;
                    }
                    // 攻撃対象を倒したかどうかを判定する
                    if (characters[characters[i].target].hp <= 0) {
                        //攻撃対象によって処理を分岐させる
                        switch(characters[i].target) {
                            // プレイヤーなら
                            case CHARACTER_PLAYER:
                            // プレイヤーが死んでしまったメッセージを表示する
                            printf("あなたは　しにました");
                            break;
                            // モンスターなら
                            case CHARACTER_MONSTER:
                            // モンスターを倒したメッセージを表示させる
                            getch(); // キーボードからの入力を待つ
                            strcpy(characters[characters[i].target].aa, "\n"); // Linux
                            // 戦闘シーンを描画する関数を呼び出す
                            DrawBattleScreen();
                            printf("%sを　たおした！\n", characters[characters[i].target].name);
                            // モンスターのアスキーアートを何も表示しないように書き換える
                            break;
                        }
                        getch(); // キーボードからの入力を待つ
                        // 戦闘シーンの関数を抜ける
                        return;
                    }

                    // 戦闘シーンを描画する関数を呼び出す
                    DrawBattleScreen();
                }
                break;
                case COMMAND_SPELL: // 呪文
                    break;
                case COMMAND_RUN:   // 逃げる
                    // 逃げ出したメッセージを表示する
                    printf("%sは　にげだした！\n", characters[i].name);
                    // キーボード入力を待つ
                    getch();
                    // 戦闘処理を抜ける
                    return;
                    break;
            }
        }
    }
}

int main()
{
    // 乱数を初期化する
    srand((unsigned int)time(NULL));
    // ゲームを初期化する関数を呼び出す
    Init();
    // 戦闘シーンの関数を呼び出す
    Battle(MONSTER_BOSS);
    return 0;
}