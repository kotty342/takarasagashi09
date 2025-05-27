#include <stdio.h> // 標準入出力ライブラリのインクルード

// プロトタイプ宣言
void initialize(int* tre_x, int* tre_y, int* get_comp, int* score, int* tries); // 配列・変数初期化
void input_and_validate(int* col, int* row, int* valid); // 入力と妥当性判定
void print_board(int input_col, int input_row); // 盤面表示
void check_all_treasure(int* tre_x, int* tre_y, int* get_comp, int input_col, int input_row, int* found); // 宝物一致判定
void add_score(int* score, int found); // スコア加算
void show_board_or_error(int valid, int input_col, int input_row); // 盤面またはエラー表示
void show_result_message(int found); // 結果表示
void show_score(int score); // スコア表示

#define TRE_COUNT 10    // 宝物の数
#define MAX_TRIES 20    // 最大試行回数
#define GRID_SIZE 10    // 盤面のサイズ

// 関数7: 配列初期化・値設定
void initialize(int* tre_x, int* tre_y, int* get_comp, int* score, int* tries) {
    int tx[TRE_COUNT] = { 5, 3, 0, 5, 1, 2, 4, 0, 3, 2 }; // 宝物のx座標
    int ty[TRE_COUNT] = { 8, 9, 5, 9, 7, 8, 6, 1, 7, 5 }; // 宝物のy座標
    for (int i = 0; i < TRE_COUNT; i++) { // 各宝物について
        tre_x[i] = tx[i]; // x座標を設定
        tre_y[i] = ty[i]; // y座標を設定
        get_comp[i] = 0;  // 取得済みフラグを0で初期化
    }
    *score = 0; // スコア初期化
    *tries = 0; // 試行回数初期化
}

// 関数8: 入力・妥当性判定
void input_and_validate(int* col, int* row, int* valid) {
    printf("列 = "); // 列入力を促す
    scanf_s("%d", col); // 列番号の入力
    printf("行 = "); // 行入力を促す
    scanf_s("%d", row); // 行番号の入力
    *valid = (*col >= 0 && *col < GRID_SIZE && *row >= 0 && *row < GRID_SIZE); // 入力値の妥当性判定
}

// 盤面を表示する関数
void print_board(int input_col, int input_row) {
    printf("   "); // 列番号の前のスペースを表示
    for (int col = 0; col < GRID_SIZE; col++) { // 列番号を0から9まで表示
        printf("%2d", col); // 列番号を2桁で表示
    }
    printf("\n"); // 列番号表示後に改行
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

// 関数9: 全宝物との一致判定（ポインタ渡し）
void check_all_treasure(int* tre_x, int* tre_y, int* get_comp, int input_col, int input_row, int* found) {
    *found = 0; // 初期値は未発見
    for (int i = 0; i < TRE_COUNT; i++) { // 全宝物を調べる
        if (!get_comp[i] && input_col == tre_x[i] && input_row == tre_y[i]) { // 未取得かつ座標一致
            *found = 1; // 発見フラグを立てる
            get_comp[i] = 1; // 取得済みにする
            break; // 1つ見つけたら終了
        }
    }
}

// 関数10: スコア加算（return命令は使わない）
void add_score(int* score, int found) {
    if (found) { // 宝物を発見した場合
        (*score)++; // スコアを加算
    }
}

// 関数3: 受理なら盤面表示、NGならエラーメッセージ表示
void show_board_or_error(int valid, int input_col, int input_row) {
    if (valid) { // 妥当な入力なら
        print_board(input_col, input_row); // 盤面を表示
    }
    else {
        printf("エラー：範囲外の入力です。\n"); // エラーメッセージを表示
    }
}

// 関数4: 一致判定結果に応じて「はずれ」「あたり」表示
void show_result_message(int found) {
    if (found) { // 宝物を発見した場合
        printf("あたり！\n"); // 当たりメッセージ
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
    int tre_x[TRE_COUNT], tre_y[TRE_COUNT], get_comp[TRE_COUNT]; // 宝物の座標・取得フラグ配列
    int input_col, input_row; // プレイヤーが入力する列・行
    int tries, score; // 試行回数カウンタとスコア（発見した宝物の数）
    int valid, found; // 妥当性判定フラグと宝物発見フラグ

    // 配列・変数初期化
    initialize(tre_x, tre_y, get_comp, &score, &tries);

    while (tries < MAX_TRIES && score < TRE_COUNT) { // 最大試行回数または全宝物発見で終了
        printf("[%d回目] 座標を入力してください。\n", tries + 1); // 試行回数を表示

        // 入力と妥当性判定
        input_and_validate(&input_col, &input_row, &valid);

        if (valid) { // 妥当な入力の場合
            // 全宝物との一致判定
            check_all_treasure(tre_x, tre_y, get_comp, input_col, input_row, &found);
            // スコア加算
            add_score(&score, found);
        }
        else {
            found = 0; // 妥当でない場合は発見フラグを0
        }

        // 盤面またはエラー表示
        show_board_or_error(valid, input_col, input_row);

        // 結果表示
        if (valid) {
            show_result_message(found);
        }

        tries++; // 試行回数をインクリメント
    }

    // スコア表示
    show_score(score);

    return 0; // プログラム終了
}