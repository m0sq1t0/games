#include <stdio.h>
#include <string>

// キャラクターの構造体を宣言する
typedef struct {
    int hp;        // HP     
    int maxHp;     // 最大HP
    int mp;        // MP
    int maxMp;     // 最大MP
    char name[20]; // 名前
    char aa[256];  // モンスターのアスキーアート
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

// ゲームを初期化する関数を定義する
void Init()
{
    // プレイヤーのステータスを初期化する
    characters[CHARACTER_PLAYER] = monsters[MONSTER_PLAYER];
}

//戦闘シーンの画面を描画する関数を定義する
void DrawBattleScreen()
{
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
// 戦闘シーンの関数を定義する
void Battle(int _monster)
{
    // モンスターのステータスを初期化する
    characters[CHARACTER_MONSTER] = monsters[_monster];
    // 戦闘シーンを描画する関数を呼び出す
    DrawBattleScreen();
    // キーボードから１文字読みこむ (Linux)
    getc(stdin);
}

int main()
{
    // ゲームを初期化する関数を呼び出す
    Init();
    // 戦闘シーンの関数を呼び出す
    Battle(MONSTER_SLIME);
    return 0;
}