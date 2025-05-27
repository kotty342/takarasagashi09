#include <stdio.h> // 標準入出力ライブラリのインクルード

#define TRE_COUNT 10    // 宝物の数
#define MAX_TRIES 20    // 最大試行回数
#define GRID_SIZE 10    // 盤面のサイズ

// 宝物構造体
typedef struct {
    int x;
    int y;
    int gold;
    int get_comp;
} obj;

// プレイヤー構造体（今回はスコアのみ管理）
typedef struct {
    int score;
} actor;

// 宝物初期化
void initialize(obj* treasures, actor* player, int* tries) {
    int tx[TRE_COUNT]   = {5,3,0,5,1,2,4,0,3,2};
    int ty[TRE_COUNT]   = {8,9,5,9,7,8,6,1,7,5};
    int tgold[TRE_COUNT]= {8,7,6,5,4,3,2,2,1,1};
    for (int i = 0; i < TRE_COUNT; i++) {
        treasures[i].x = tx[i];
        treasures[i].y = ty[i];
        treasures[i].gold = tgold[i];
        treasures[i].get_comp = 0;
    }
    player->score = 0;
    *tries = 0;
}

// 入力・妥当性判定
void input_and_validate(int* col, int* row, int* valid) {
    printf("列 = ");
    scanf_s("%d", col);
    printf("行 = ");
    scanf_s("%d", row);
    *valid = (*col >= 0 && *col < GRID_SIZE && *row >= 0 && *row < GRID_SIZE);
}

// 盤面表示
void print_board(int input_col, int input_row) {
    printf("   ");
    for (int col = 0; col < GRID_SIZE; col++) {
        printf("%2d", col);
    }
    printf("\n");
    for (int row = 0; row < GRID_SIZE; row++) {
        printf("%2d ", row);
        for (int col = 0; col < GRID_SIZE; col++) {
            if (col == input_col && row == input_row) {
                printf("■ ");
            } else {
                printf("□ ");
            }
        }
        printf("\n");
    }
}

// 宝物一致判定
void check_all_treasure(obj* treasures, int input_col, int input_row, int* found, int* found_index) {
    *found = 0;
    *found_index = -1;
    for (int i = 0; i < TRE_COUNT; i++) {
        if (!treasures[i].get_comp && input_col == treasures[i].x && input_row == treasures[i].y) {
            *found = 1;
            *found_index = i;
            treasures[i].get_comp = 1;
            break;
        }
    }
}

// スコア加算
void add_score(actor* player, obj* treasures, int found, int found_index) {
    if (found && found_index >= 0) {
        player->score += treasures[found_index].gold;
    }
}

// 盤面またはエラー表示
void show_board_or_error(int valid, int input_col, int input_row) {
    if (valid) {
        print_board(input_col, input_row);
    } else {
        printf("エラー：範囲外の入力です。\n");
    }
}

// 結果表示
void show_result_message(int found) {
    if (found) {
        printf("あたり！\n");
    } else {
        printf("はずれ。\n");
    }
}

// スコア表示
void show_score(int score) {
    printf("スコア: %d\n", score);
}

int main() {
    obj treasures[TRE_COUNT];
    actor player;
    int input_col, input_row;
    int tries;
    int valid, found, found_index;

    initialize(treasures, &player, &tries);

    while (tries < MAX_TRIES && player.score < 37) { // すべての宝物合計点数は37
        printf("[%d回目] 座標を入力してください。\n", tries + 1);

        input_and_validate(&input_col, &input_row, &valid);

        if (valid) {
            check_all_treasure(treasures, input_col, input_row, &found, &found_index);
            add_score(&player, treasures, found, found_index);
        } else {
            found = 0;
        }

        show_board_or_error(valid, input_col, input_row);

        if (valid) {
            show_result_message(found);
        }

        tries++;
    }

    show_score(player.score);

    return 0;
}