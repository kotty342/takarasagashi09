#include <stdio.h>

// 定数定義
constexpr auto MAX_TRIES = 20;     // 最大試行回数
constexpr auto GRID_SIZE = 10;     // 盤面のサイズ
constexpr auto TRE_COUNT = 10;     // 宝物の数

// 構造体定義
struct obj {
    int x;
    int y;
    int gold;
    int get_comp;
};

struct actor {
    int x;
    int y;
    int score;
};

// プロトタイプ宣言
int is_valid_position(int x, int y); // 入力座標の妥当性判定関数のプロトタイプ
void show_board_or_error(int input_error, int input_x, int input_y); // 盤面表示またはエラー表示関数のプロトタイプ
void show_result_message(int get_treasure); // 判定結果表示関数のプロトタイプ
int is_game_end(int game_count); // ゲーム終了判定関数のプロトタイプ
void show_score(int score); // スコア表示関数のプロトタイプ
void initialize_game(obj* treasures); // 構造体配列初期化
void input_and_validate(actor* player, int* input_error); // 入力・妥当性判定
void check_all_treasure(obj* treasures, actor* player, int* get_treasure, int* get_gold); // 一致判定
void update_score(actor* player, int get_gold); // スコア加算

int main() {
    obj treasures[TRE_COUNT];
    actor player = {0, 0, 0};
    int game_count = 0;

    initialize_game(treasures); // 構造体配列初期化

    while (!is_game_end(game_count)) {
        printf("[%d回目] 座標を入力してください。\n", game_count + 1);

        int input_error = 0;
        input_and_validate(&player, &input_error); // 入力と妥当性判定

        int get_treasure = 0;
        int get_gold = 0;
        if (input_error) {
            check_all_treasure(treasures, &player, &get_treasure, &get_gold); // 一致判定
            update_score(&player, get_gold); // スコア加算
        }

        show_board_or_error(input_error, player.x, player.y);
        show_result_message(get_treasure);

        game_count++;
    }

    show_score(player.score);

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
int is_game_end(int game_count) {
    if (game_count >= MAX_TRIES) {
        return 1;
    }   
    return 0;
}

// 関数6: スコア表示
void show_score(int score) {
    printf("スコア: %d\n", score);
}

// 構造体配列の初期化
void initialize_game(obj* treasures) {
    int tx[TRE_COUNT]   = { 5, 3, 0, 5, 1, 2, 4, 0, 3, 2 };
    int ty[TRE_COUNT]   = { 8, 9, 5, 9, 7, 8, 6, 1, 7, 5 };
    int gold[TRE_COUNT] = { 3, 2, 1, 2, 4, 1, 1, 3, 2, 1 };
    for (int i = 0; i < TRE_COUNT; i++) {
        treasures[i].x = tx[i];
        treasures[i].y = ty[i];
        treasures[i].gold = gold[i];
        treasures[i].get_comp = 0;
    }
}

// 入力・妥当性判定
void input_and_validate(actor* player, int* input_error) {
    printf("列 = ");
    scanf_s("%d", &player->x);
    printf("行 = ");
    scanf_s("%d", &player->y);
    *input_error = is_valid_position(player->x, player->y);
}

// 全宝物の座標と入力座標の一致判定
void check_all_treasure(obj* treasures, actor* player, int* get_treasure, int* get_gold) {
    *get_treasure = 0;
    *get_gold = 0;
    for (int i = 0; i < TRE_COUNT; i++) {
        if (player->x == treasures[i].x && player->y == treasures[i].y) {
            if (treasures[i].get_comp == 0) {
                treasures[i].get_comp = 1;
                *get_treasure = 1;
                *get_gold = treasures[i].gold;
            }
            break;
        }
    }
}

// スコア加算
void update_score(actor* player, int get_gold) {
    if (get_gold > 0) {
        player->score += get_gold;
    }
}