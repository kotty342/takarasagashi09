#include <stdio.h>

// 定数定義
constexpr auto MAX_TRIES = 20;     // 最大試行回数
constexpr auto GRID_SIZE = 10;     // 盤面のサイズ
constexpr auto TRE_COUNT = 10;     // 宝物の数

// プロトタイプ宣言
int is_valid_position(int x, int y); // 入力座標の妥当性判定関数のプロトタイプ
void show_board_or_error(int input_error, int input_x, int input_y); // 盤面表示またはエラー表示関数のプロトタイプ
void show_result_message(int get_treasure); // 判定結果表示関数のプロトタイプ
int is_game_end(int game_count, int score); // ゲーム終了判定関数のプロトタイプ
void show_score(int score); // スコア表示関数のプロトタイプ
void initialize_game(int* tre_x, int* tre_y, int* get_comp); // 関数7: 配列初期化・値設定
void input_and_validate(int* input_x, int* input_y, int* input_error); // 関数8: 入力・妥当性判定
void check_all_treasure(const int* tre_x, const int* tre_y, int* get_comp, int input_x, int input_y, int* get_treasure); // 関数9: 一致判定
void update_score(int* score, int get_treasure); // 関数10: スコア加算

int main() {
    int tre_x[TRE_COUNT];
    int tre_y[TRE_COUNT];
    int get_comp[TRE_COUNT];
    int input_x = 0, input_y = 0;
    int score = 0;
    int game_count = 0;

    initialize_game(tre_x, tre_y, get_comp); // 配列初期化

    while (!is_game_end(game_count, score)) {
        printf("[%d回目] 座標を入力してください。\n", game_count + 1);

        int input_error = 0;
        input_and_validate(&input_x, &input_y, &input_error); // 入力と妥当性判定

        int get_treasure = 0;
        if (input_error) {
            check_all_treasure(tre_x, tre_y, get_comp, input_x, input_y, &get_treasure); // 一致判定
            update_score(&score, get_treasure); // スコア加算
        }

        show_board_or_error(input_error, input_x, input_y);
        show_result_message(get_treasure);

        game_count++;
    }

    show_score(score);

    return 0;
}

// 関数1: 入力座標の妥当性判定
int is_valid_position(int x, int y) {
    if (x < 0 || x >= GRID_SIZE) {
        return 0;
    }
    if (y < 0 || y >= GRID_SIZE) {
        return 0;
    }
    return 1;
}

// 関数3: エラーフラグに応じて盤面表示またはエラーメッセージを表示
// エラー時はエラーメッセージのみ表示
void show_board_or_error(int input_error, int input_x, int input_y) {
    if (input_error) {
        // 盤面を表示
        printf("   ");
        for (int col = 0; col < GRID_SIZE; col++) {
            printf("%2d", col);
        }
        printf("\n");
        for (int row = 0; row < GRID_SIZE; row++) {
            printf("%2d ", row);
            for (int col = 0; col < GRID_SIZE; col++) {
                if (col == input_x && row == input_y) {
                    printf("■ ");
                }
                else {
                    printf("□ ");
                }
            }
            printf("\n");
        }
    }
    else {
        printf("エラー：範囲外の入力です。(0から%dの間で入力してください)\n", GRID_SIZE - 1); // エラーメッセージのみ表示
    }
}

// 関数4: 一致判定結果に応じて「はずれ」「あたり」表示
void show_result_message(int get_treasure) {
    if (get_treasure) { // 宝物を発見した場合
        printf("あたり\n"); // 当たりメッセージ
    }
    else {
        printf("はずれ\n"); // 外れメッセージ
    }
}

// 関数5: ゲーム終了判定
int is_game_end(int game_count, int score) {
    if (game_count >= MAX_TRIES) {
        return 1;
    }
    if (score >= TRE_COUNT) {
        return 1;
    }
    return 0;
}

// 関数6: スコア表示
void show_score(int score) {
    printf("スコア: %d\n", score);
}

// 関数7: 宝物の配列等、配列変数の設定をする
void initialize_game(int* tre_x, int* tre_y, int* get_comp) {
    int tx[TRE_COUNT] = { 5, 3, 0, 5, 1, 2, 4, 0, 3, 2 };
    int ty[TRE_COUNT] = { 8, 9, 5, 9, 7, 8, 6, 1, 7, 5 };
    for (int i = 0; i < TRE_COUNT; i++) {
        tre_x[i] = tx[i];
        tre_y[i] = ty[i];
        get_comp[i] = 0;
    }
}

// 関数8: キー入力と妥当性判定
void input_and_validate(int* input_x, int* input_y, int* input_error) {
    printf("列 = ");
    scanf_s("%d", input_x);
    printf("行 = ");
    scanf_s("%d", input_y);
    *input_error = is_valid_position(*input_x, *input_y);
}

// 関数9: 全宝物の座標と入力座標の一致判定
void check_all_treasure(const int* tre_x, const int* tre_y, int* get_comp, int input_x, int input_y, int* get_treasure) {
    *get_treasure = 0;
    for (int i = 0; i < TRE_COUNT; i++) {
        if (input_x == tre_x[i] && input_y == tre_y[i]) {
            if (get_comp[i] == 0) {
                get_comp[i] = 1;
                *get_treasure = 1;
            }
            break;
        }
    }
}

// 関数10: スコア加算（return命令は使わない）
void update_score(int* score, int get_treasure) {
    if (get_treasure) {
        (*score)++;
    }
}