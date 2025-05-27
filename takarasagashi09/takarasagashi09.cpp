#include <stdio.h> // 標準入出力ライブラリのインクルード

// プロトタイプ宣言
void initialize(struct obj* treasures, int* score, int* tries); // 宝物配列・スコア・試行回数の初期化
void input_and_validate(int* col, int* row, int* valid); // 入力と妥当性判定
void print_board(int input_col, int input_row); // 盤面表示
void check_all_treasure(obj* treasures, int input_col, int input_row, int* found, int* add_gold); // 宝物一致判定
void add_score(int* score, int add_gold); // スコア加算
void show_board_or_error(int valid, int input_col, int input_row); // 盤面またはエラー表示
void show_result_message(int found, int add_gold); // 結果表示
void show_score(int score); // スコア表示

#define TRE_COUNT 10    // 宝物の数
#define MAX_TRIES 20    // 最大試行回数
#define GRID_SIZE 10    // 盤面のサイズ

// 宝物用構造体
typedef struct obj {
    int x;         // x座標
    int y;         // y座標
    int gold;      // 宝物の点数
    int get_comp;  // 取得済みフラグ
} obj;

// プレイヤー用構造体（今回は使わないがヒントに従い定義）
typedef struct {
    int x;      // プレイヤーのx座標
    int y;      // プレイヤーのy座標
    int score;  // プレイヤーのスコア
} actor;

// 宝物配列の初期化
void initialize(obj* treasures, int* score, int* tries) {
    int tx[TRE_COUNT]   = { 5, 3, 0, 5, 1, 2, 4, 0, 3, 2 }; // 各宝物のx座標
    int ty[TRE_COUNT]   = { 8, 9, 5, 9, 7, 8, 6, 1, 7, 5 }; // 各宝物のy座標
    int gold[TRE_COUNT] = { 8, 9, 5, 7, 7, 8, 6, 1, 7, 5 }; // 各宝物の点数
    for (int i = 0; i < TRE_COUNT; i++) { // 宝物の数だけ繰り返す
        treasures[i].x = tx[i];           // x座標を設定
        treasures[i].y = ty[i];           // y座標を設定
        treasures[i].gold = gold[i];      // 点数を設定
        treasures[i].get_comp = 0;        // 取得済みフラグを0で初期化
    }
    *score = 0; // スコア初期化
    *tries = 0; // 試行回数初期化
}

// 入力と妥当性判定
void input_and_validate(int* col, int* row, int* valid) {
    printf("列 = "); // 列番号入力を促す
    scanf_s("%d", col); // 列番号を入力
    printf("行 = "); // 行番号入力を促す
    scanf_s("%d", row); // 行番号を入力
    *valid = (*col >= 0 && *col < GRID_SIZE && *row >= 0 && *row < GRID_SIZE); // 入力値の妥当性判定
}

// 盤面表示
void print_board(int input_col, int input_row) {
    printf("   "); // 列番号の前のスペース
    for (int col = 0; col < GRID_SIZE; col++) { // 列番号を表示
        printf("%2d", col); // 列番号を2桁で表示
    }
    printf("\n"); // 改行
    for (int row = 0; row < GRID_SIZE; row++) { // 各行を表示
        printf("%2d ", row); // 行番号を2桁で表示
        for (int col = 0; col < GRID_SIZE; col++) { // 各列を表示
            if (col == input_col && row == input_row) { // 入力座標と一致する場合
                printf("■ "); // プレイヤーの入力位置を強調表示
            }
            else {
                printf("□ "); // それ以外は通常のマスを表示
            }
        }
        printf("\n"); // 行の終わりで改行
    }
}

// 宝物との一致判定とスコア加算
void check_all_treasure(obj* treasures, int input_col, int input_row, int* found, int* add_gold) {
    *found = 0;    // 初期値は未発見
    *add_gold = 0; // 加算点も初期化
    for (int i = 0; i < TRE_COUNT; i++) { // 全宝物を調べる
        if (!treasures[i].get_comp && input_col == treasures[i].x && input_row == treasures[i].y) { // 未取得かつ座標一致
            *found = 1; // 発見フラグを立てる
            *add_gold = treasures[i].gold; // 点数をセット
            treasures[i].get_comp = 1; // 取得済みにする
            break; // 1つ見つけたら終了
        }
    }
}

// スコア加算
void add_score(int* score, int add_gold) {
    *score += add_gold; // スコアに点数を加算
}

// 盤面またはエラー表示
void show_board_or_error(int valid, int input_col, int input_row) {
    if (valid) { // 妥当な入力なら
        print_board(input_col, input_row); // 盤面を表示
    }
    else {
        printf("エラー：範囲外の入力です。\n"); // エラーメッセージを表示
    }
}

// 結果表示
void show_result_message(int found, int add_gold) {
    if (found) { // 宝物を発見した場合
        printf("あたり！ %d点獲得！\n", add_gold); // 当たりメッセージ
    }
    else {
        printf("はずれ。\n"); // 外れメッセージ
    }
}

// スコア表示
void show_score(int score) {
    printf("スコア: %d\n", score); // スコアを表示
}

int main() {
    obj treasures[TRE_COUNT]; // 宝物配列
    int input_col, input_row; // 入力された列・行
    int tries, score;         // 試行回数・スコア
    int valid, found, add_gold; // 妥当性・発見フラグ・加算点

    initialize(treasures, &score, &tries); // 初期化

    while (tries < MAX_TRIES) { // 最大試行回数まで繰り返す
        printf("[%d回目] 座標を入力してください。\n", tries + 1); // 試行回数表示

        input_and_validate(&input_col, &input_row, &valid); // 入力と妥当性判定

        if (valid) { // 妥当な入力の場合
            check_all_treasure(treasures, input_col, input_row, &found, &add_gold); // 宝物判定
            add_score(&score, add_gold); // スコア加算
        }
        else {
            found = 0;    // 発見フラグを0
            add_gold = 0; // 加算点も0
        }

        show_board_or_error(valid, input_col, input_row); // 盤面またはエラー表示

        if (valid) {
            show_result_message(found, add_gold); // 結果表示
        }

        tries++; // 試行回数をインクリメント
    }

    show_score(score); // 最終スコア表示

    return 0; // プログラム終了
}
