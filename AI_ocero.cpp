#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define N 10
#define T 100
int board[N][N] = { 0 }; //ボードの確保
int tokuten[N][N] = { 0 };
struct INPUT_DATA
{
	int x;
	int y;
};
void make_board(int board[N][N])
{
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 10; j++) {
			board[i][j] = 0;
		}
	}
	// 初期の4つの石を配置
	int i, j;
	for (i = 0; i < 10; i++) {
		board[0][i] = board[9][i] = 2;
		board[i][0] = board[i][9] = 2;
	}
	board[4][4] = board[5][5] = 1;
	board[5][4] = board[4][5] = -1;
	for (i = 1; i < 9; i++) {
		for (j = 1; j < 9; j++) {
			if (board[i][j] == 1 || board[i][j] == -1) {
				break;
			}
			else board[i][j] = 0;
		}
	}

	for (i = 0; i < 10; i++) {
		for (j = 0; j < 10; j++) {
			if (board[i][j] == 1 || board[i][j] == -1 || board[i][j] == 0) {
				break;
			}
		}
	}
}
int check_change(int k, int i, int j, int board[N][N])
{
	int I = i, J = j; //探索の初期位置の準備
	int l = k * -1; //配置する駒とは別の駒の準備
	int check = 0; //返り値の確保
	if (board[I][J] != 0) //配置するマスに何も置かれていないことの確認．
		return check;
	while (board[I + 1][J] == l) //隣のマスが別の駒かの確認(下)
	{
		check = 1; //while文を経由したかの確認 I++;
		I++;
	}
	if (board[I + 1][J] == k && check == 1) //別の駒が続いた先が自分の駒かの確認(下)
	{
		check = 1;
		return check;
	}
	I = i; //初期位置に戻す
	check = 0; //初期値に戻す

	while (board[I - 1][J] == l) //隣のマスが別の駒かの確認(上)
	{
		check = 1; //while文を経由したかの確認 I++;
		I--;
	}
	if (board[I - 1][J] == k && check == 1) //別の駒が続いた先が自分の駒かの確認(上)
	{
		check = 1;
		return check;
	}
	I = i; //初期位置に戻す
	check = 0; //初期値に戻す

	while (board[I][J + 1] == l) //隣のマスが別の駒かの確認(右)
	{
		check = 1; //while文を経由したかの確認 I++;
		J++;
	}
	if (board[I][J + 1] == k && check == 1) //別の駒が続いた先が自分の駒かの確認(右)
	{
		check = 1;
		return check;
	}
	J = j;
	check = 0; //初期値に戻す

	while (board[I][J - 1] == l) //隣のマスが別の駒かの確認(左)
	{
		check = 1; //while文を経由したかの確認 I++;
		J--;
	}
	if (board[I][J - 1] == k && check == 1) //別の駒が続いた先が自分の駒かの確認(左)
	{
		check = 1;
		return check;
	}
	J--;
	J = j; //初期位置に戻す
	check = 0; //初期値に戻す

	while (board[I + 1][J + 1] == l) //隣のマスが別の駒かの確認(右下)
	{
		check = 1; //while文を経由したかの確認 I++;
		I++;
		J++;
	}
	if (board[I + 1][J + 1] == k && check == 1) //別の駒が続いた先が自分の駒かの確認(右下)
	{
		check = 1;
		return check;
	}
	I = i; //初期位置に戻す
	J = j;
	check = 0; //初期値に戻す

	while (board[I + 1][J - 1] == l) //隣のマスが別の駒かの確認(左下)
	{
		check = 1; //while文を経由したかの確認 I++;
		I++;
		J--;
	}
	if (board[I + 1][J - 1] == k && check == 1) //別の駒が続いた先が自分の駒かの確認(左下)
	{
		check = 1;
		return check;
	}

	I = i; //初期位置に戻す
	J = j;
	check = 0; //初期値に戻す

	while (board[I - 1][J - 1] == l) //隣のマスが別の駒かの確認(左上)
	{
		check = 1; //while文を経由したかの確認 I++;
		I--;
		J--;
	}
	if (board[I - 1][J - 1] == k && check == 1) //別の駒が続いた先が自分の駒かの確認(左上)
	{
		check = 1;
		return check;
	}
	I = i; //初期位置に戻す
	J = j;
	check = 0; //初期値に戻す

	while (board[I - 1][J + 1] == l) //隣のマスが別の駒かの確認(右上)
	{
		check = 1; //while文を経由したかの確認 I++;
		I--;
		J++;
	}
	if (board[I - 1][J + 1] == k && check == 1) //別の駒が続いた先が自分の駒かの確認(右上)
	{
		check = 1;
		return check;
	}
	I = i; //初期位置に戻す
	J = j;
	check = 0; //初期値に戻す
	return check;
}
void change_board(int k, int i, int j, int board[N][N])
{
	int I = i, J = j; //探索の初期位置の準備
	int l = k * -1; //配置する駒とは別の駒の準備
	board[I][J] = k; //与えられたマスに駒を配置
	/*for (int n = -1; n < 2; n++) {
		for (int m = -1; m < 2; m++) {
			I = I + n;
			j = j + m;
			while (board[I][j] == l) //隣のマスが別の駒かの確認
			{
				I++;
			}
			if (board[I][j] == k) //別の駒が続いた先が自分の駒かの確認自分の駒だった場合にはマスの初期位置から別の駒を自分の駒に変更する
			{
				I = i;
				while (board[I][j] == l)//下
				{
					board[I][j] = k;
					I++;
				}
			}
			I = i;
		}

	}
}*/
	while (board[I + 1][j] == l) //隣のマスが別の駒かの確認
	{
		I++;
	}
	if (board[I + 1][j] == k) //別の駒が続いた先が自分の駒かの確認自分の駒だった場合にはマスの初期位置から別の駒を自分の駒に変更する
	{

		I = i;
		while (board[I + 1][j] == l)//下
		{
			board[I + 1][j] = k;
			I++;
		}
	}
	I = i;

	while (board[I - 1][j] == l) //隣のマスが別の駒かの確認
	{
		I--;
	}
	if (board[I - 1][j] == k) //別の駒が続いた先が自分の駒かの確認自分の駒だった場合にはマスの初期位置から別の駒を自分の駒に変更する
	{

		I = i;
		while (board[I - 1][j] == l)//上
		{
			board[I - 1][j] = k;
			I--;
		}
	}
	I = i;
	while (board[I][J + 1] == l) //隣のマスが別の駒かの確認
	{
		J++;
	}
	if (board[I][J + 1] == k) //別の駒が続いた先が自分の駒かの確認自分の駒だった場合にはマスの初期位置から別の駒を自分の駒に変更する
	{

		J = j;
		while (board[I][J + 1] == l)//右
		{
			board[I][J + 1] = k;
			J++;
		}
	}
	J = j;
	while (board[I][J - 1] == l) //隣のマスが別の駒かの確認
	{
		J--;
	}
	if (board[I][J - 1] == k) //別の駒が続いた先が自分の駒かの確認自分の駒だった場合にはマスの初期位置から別の駒を自分の駒に変更する
	{

		J = j;
		while (board[I][J - 1] == l)//左
		{
			board[I][J - 1] = k;
			J--;
		}
	}
	J = j;
	while (board[I + 1][J + 1] == l) //隣のマスが別の駒かの確認
	{
		I++;
		J++;
	}
	if (board[I + 1][J + 1] == k) //別の駒が続いた先が自分の駒かの確認自分の駒だった場合にはマスの初期位置から別の駒を自分の駒に変更する
	{

		I = i;
		J = j;
		while (board[I + 1][J + 1] == l)//右下
		{
			board[I + 1][J + 1] = k;
			I++;
			J++;
		}
	}
	I = i;
	J = j;
	while (board[I + 1][J - 1] == l) //隣のマスが別の駒かの確認
	{
		I++;
		J--;
	}
	if (board[I + 1][J - 1] == k) //別の駒が続いた先が自分の駒かの確認自分の駒だった場合にはマスの初期位置から別の駒を自分の駒に変更する
	{

		I = i;
		J = j;
		while (board[I + 1][J - 1] == l)//左下
		{
			board[I + 1][J - 1] = k;
			I++;
			J--;
		}
	}
	I = i;
	J = j;
	while (board[I - 1][J - 1] == l) //隣のマスが別の駒かの確認
	{
		I--;
		J--;
	}
	if (board[I - 1][J - 1] == k) //別の駒が続いた先が自分の駒かの確認自分の駒だった場合にはマスの初期位置から別の駒を自分の駒に変更する
	{

		I = i;
		J = j;
		while (board[I - 1][J - 1] == l)//左上
		{
			board[I - 1][J - 1] = k;
			I--;
			J--;
		}
	}
	I = i;
	J = j;
	while (board[I - 1][J + 1] == l) //隣のマスが別の駒かの確認
	{
		I--;
		J++;
	}
	if (board[I - 1][J + 1] == k) //別の駒が続いた先が自分の駒かの確認自分の駒だった場合にはマスの初期位置から別の駒を自分の駒に変更する
	{

		I = i;
		J = j;
		while (board[I - 1][J + 1] == l)//右上
		{
			board[I - 1][J + 1] = k;
			I--;
			J++;
		}
	}
	I = i;
	J = j;
}
int check_pass(int k, int board[N][N]) {
	for (int i = 1; i < 9; i++) {
		for (int j = 1; j < 9; j++) {
			if (check_change(k, i, j, board) == 1) {
				return 1;
			}

		}

	}
	printf("駒を打つことができないのでパスします。\n");
	return 0;
}
int check_finish(int t, int board[N][N]) {
	int k = 1;
	for (int i = 1; i < 9; i++) {
		for (int j = 1; j < 9; j++) {
			if (check_change(k, i, j, board) == 1) {
				return 1;
			}
		}
	}
	k = k * -1;
	for (int i = 1; i < 9; i++) {
		for (int j = 1; j < 9; j++) {
			if (check_change(k, i, j, board) == 1) {
				return 1;
			}
		}
	}
	printf("両者ともパスな為ゲームを終了します。\n");
	return 0;
}
void number_pieces(int board[N][N])
{
	int i, j;
	int a = 0;
	int b = 0;
	for (i = 1; i < 9; i++) {
		for (j = 1; j < 9; j++) {
			if (board[i][j] == 1) {
				a++;
			}
			else if (board[i][j] == -1) {
				b++;
			}

		}
	}
	printf("駒の数：白＝%d,黒＝%d\n", a, b);
}
void number_place(int k, int board[N][N])
{
	int a = 0;
	for (int i = 1; i < 9; i++) {
		for (int j = 1; j < 9; j++) {
			check_change(k, i, j, board);
			if (check_change(k, i, j, board) == 1)
			{

				a++;
			}
		}
	}
	printf("打てるマスの数は%dコ\n", a);
}
void print_board(int board[N][N]) {
	printf("  列 １２３４５６７８\n");
	printf("行 --------------------\n");
	int i, j;
	for (i = 0; i < 10; i++) {
		if (!(i == 0 || i == 9)) {
			printf("%2d|", i);
		}
		else printf("  |");
		for (j = 0; j < 10; j++) {
			if (board[i][j] == 1) printf("○ ");
			else if (board[i][j] == -1) printf("● ");
			else if (board[i][j] == 2) printf("□ ");
			else printf("　");
		}
		printf("\n");
	}
}
struct INPUT_DATA input_key(int k, int board[N][N])
{
	struct INPUT_DATA a {};

	if (k == -1) {
		printf("黒のターン\n");
		do {
			printf("行："); scanf_s("%d", &a.x);
			printf("列："); scanf_s("%d", &a.y);
			if (!(0 < a.x && a.x < 9) || !(0 < a.y && a.y < 9)) {
				puts("\a行列それぞれ”1～8”で入力せよ!!");
				printf("\n");
			}
		} while (!(0 < a.x && a.x < 9) || !(0 < a.y && a.y < 9));

		check_change(k, a.x, a.y, board);
		//if (check_change(k, a.x, a.y, board) == 0) {
		while (check_change(k, a.x, a.y, board) == 0) {
			printf("そこに駒を置くことはできません。\n");
			do {
				printf("\n");
				printf("行："); scanf_s("%d", &a.x);
				printf("列："); scanf_s("%d", &a.y);
				if (!(0 < a.x && a.x < 9) || !(0 < a.y && a.y < 9)) {
					puts("\a行列それぞれ”1～8”で入力せよ!!");
				}
			} while (!(0 < a.x && a.x < 9) || !(0 < a.y && a.y < 9));
			check_change(k, a.x, a.y, board);
		}
	}
	if (k == 1) {
		printf("白のターン\n");
		do {
			printf("行："); scanf_s("%d", &a.x);
			printf("列："); scanf_s("%d", &a.y);
			if (!(0 < a.x && a.x < 9) || !(0 < a.y && a.y < 9)) {
				puts("\a行列それぞれ”1～8”で入力せよ!!");
				printf("\n");
			}
		} while (!(0 < a.x && a.x < 9) || !(0 < a.y && a.y < 9));
		check_change(k, a.x, a.y, board);
		//if (check_change(k, a.x, a.y, board) == 0) {
		while (check_change(k, a.x, a.y, board) == 0) {
			printf("そこに駒を置くことはできません。\n");
			do {
				printf("\n");
				printf("行："); scanf_s("%d", &a.x);
				printf("列："); scanf_s("%d", &a.y);
				if (!(0 < a.x && a.x < 9) || !(0 < a.y && a.y < 9)) {
					puts("\a行列それぞれ”1～8”で入力せよ!!");
				}
			} while (!(0 < a.x && a.x < 9) || !(0 < a.y && a.y < 9));
			check_change(k, a.x, a.y, board);
		}
	}
	return a;
}
int positional_scores[8][8] = {
	{100, -20, 10,  5,  5, 10, -20, 100},
	{-20, -50, -2, -2, -2, -2, -50, -20},
	{ 10,  -2,  0,  0,  0,  0,  -2,  10},
	{  5,  -2,  0,  0,  0,  0,  -2,   5},
	{  5,  -2,  0,  0,  0,  0,  -2,   5},
	{ 10,  -2,  0,  0,  0,  0,  -2,  10},
	{-20, -50, -2, -2, -2, -2, -50, -20},
	{100, -20, 10,  5,  5, 10, -20, 100},
};
int evaluate_board(int board[N][N]) {
	int score = 0;
	int black_count = 0, white_count = 0;
	int black_mobility = 0, white_mobility = 0;
	int black_stable = 0, white_stable = 0;

	// 石の数と位置のスコアを考慮
	for (int i = 1; i <= 8; i++) {
		for (int j = 1; j <= 8; j++) {
			if (board[i][j] == 1) {
				score += positional_scores[i - 1][j - 1];
				black_count++;
			}
			else if (board[i][j] == -1) {
				score -= positional_scores[i - 1][j - 1];
				white_count++;
			}
		}
	}

	// 可動性の評価（打てる手の数をカウント）
	for (int i = 1; i <= 8; i++) {
		for (int j = 1; j <= 8; j++) {
			if (check_change(1, i, j, board) == 1) {
				black_mobility++;
			}
			if (check_change(-1, i, j, board) == 1) {
				white_mobility++;
			}
		}
	}

	// 安定石の評価（確定石のカウント）
	for (int i = 0; i < 8; i += 7) { // 上下の角
		for (int j = 0; j < 8; j += 7) { // 左右の角
			if (board[i + 1][j + 1] == 1) {
				black_stable++;
			}
			else if (board[i + 1][j + 1] == -1) {
				white_stable++;
			}
		}
	}

	// 評価スコアの計算
	int piece_diff = (black_count - white_count) * 10; // 石の数の評価
	int mobility_score = (black_mobility - white_mobility) * 15; // 可動性の評価
	int stability_score = (black_stable - white_stable) * 30; // 安定石の評価

	score += piece_diff + mobility_score + stability_score;

	return score;
}
struct INPUT_DATA endgame_solver(int k, int board[N][N]) {
	struct INPUT_DATA best_move = { 0, 0 };
	int best_score = (k == 1) ? -1000000 : 1000000;
	int temp_board[N][N];

	// すべての有効な手を試す
	for (int I = 1; I <= 8; I++) {
		for (int J = 1; J <= 8; J++) {
			if (check_change(k, I, J, board) == 1) {
				// ボードをコピー
				for (int i = 0; i < N; i++) {
					for (int j = 0; j < N; j++) {
						temp_board[i][j] = board[i][j];
					}
				}
				change_board(k, I, J, temp_board);

				// ここで **完全探索** を行う
				int final_score = evaluate_board(temp_board);

				// 最適な手を更新
				if ((k == 1 && final_score > best_score) || (k == -1 && final_score < best_score)) {
					best_score = final_score;
					best_move.x = I;
					best_move.y = J;
				}
			}
		}
	}
	return best_move;
}
struct INPUT_DATA alpha_beta(int depth, int alpha, int beta, int k, int board[N][N]) {
	struct INPUT_DATA best_move = { 0, 0 };
	int temp_board[N][N];
	int max_score = (k == 1) ? -100000 : 100000; // 初期値
	int score;


	// すべての有効な手を試す
	for (int I = 1; I <= 8; I++) {
		for (int J = 1; J <= 8; J++) {
			if (check_change(k, I, J, board) == 1) {
				// 盤面をコピーしてシミュレーション
				for (int i = 0; i < N; i++) {
					for (int j = 0; j < N; j++) {
						temp_board[i][j] = board[i][j];
					}
				}
				change_board(k, I, J, temp_board); // 一手進める

				// 再帰的にアルファベータ探索
				if (depth > 1) {
					struct INPUT_DATA next_move = alpha_beta(depth - 1, alpha, beta, -k, temp_board);
				}

				// **ここで評価関数を使ってスコアを計算**
				score = evaluate_board(temp_board);

				// **最大・最小スコアの更新**
				if (k == 1) { // 自分（黒）の手番
					if (score > max_score) {
						max_score = score;
						best_move.x = I;
						best_move.y = J;
					}
					alpha = (alpha > max_score) ? alpha : max_score;
				}
				else { // 相手（白）の手番
					if (score < max_score) {
						max_score = score;
						best_move.x = I;
						best_move.y = J;
					}
					beta = (beta < max_score) ? beta : max_score;
				}

				// **枝刈りの処理**
				if (alpha >= beta) {
					change_board(k, best_move.x, best_move.y, board);
					return best_move;
				}
			}
		}
	}
	change_board(k, best_move.x, best_move.y, board);
	return best_move;
}
struct INPUT_DATA two_step_expectation(int k, int board[N][N])
{
	struct INPUT_DATA best_move;
	double max_expectation = -1;
	int temp_board[N][N];
	int l = -k; // 相手の手番
	srand(time(NULL));
	// すべての手を試す
	for (int I = 1; I <= 8; I++) {
		for (int J = 1; J <= 8; J++) {
			if (check_change(k, I, J, board) == 1) {
				for (int i = 0; i < N; i++) {
					for (int j = 0; j < N; j++) {
						temp_board[i][j] = board[i][j];
					}
				}
				change_board(k, I, J, temp_board);
				// 相手の手を試す
				int total_pieces = 0;
				int valid_moves = 0;
				for (int i = 1; i <= 8; i++) {
					for (int j = 1; j <= 8; j++) {
						if (check_change(l, i, j, temp_board) == 1) {
							int future_board[N][N];
							for (int i = 0; i < N; i++) {
								for (int j = 0; j < N; j++) {
									future_board[i][j] = temp_board[i][j];
								}
							}
							change_board(l, i, j, future_board);

							// 自分の駒数を計算
							int pieces = 0;
							for (int m = 1; m <= 8; m++) {
								for (int n = 1; n <= 8; n++) {
									if (future_board[m][n] == k) {
										pieces++;
									}
								}
							}
							total_pieces += pieces;
							valid_moves++;
						}
					}
				}

				// 期待値を計算
				double expectation = (valid_moves > 0) ? (double)total_pieces / valid_moves : 0.0;
				//printf("%d.%d:%.2f\n", I, J, expectation);
				// 最大期待値を持つ手を選択
				if (expectation > max_expectation) {
					max_expectation = expectation;
					best_move.x = I;
					best_move.y = J;
				}
				else if (expectation == max_expectation && rand() % 2 == 0) {
					best_move.x = I;
					best_move.y = J;
				}
				//printf("MAX %d.%d:%.2f\n", best_move.x, best_move.y, max_expectation);
			}
		}
	}

	// 最善手を盤面に適用
	change_board(k, best_move.x, best_move.y, board);
	return best_move;
}

int main(void) // 出力画面において背景が白、文字が黒であること
{
	int board[N][N] = { 0 };
	int t; // 経過ターンの確保
	int k; // 打ち手の確保
	int i;
	int l;

	struct INPUT_DATA input_data; // 入力の確保

	make_board(board); // 駒とボードの初期設定
	print_board(board); // 初期のボードの表示
	t = 0; // 経過ターンの初期設定
	k = -1; // 打ち手の初期設定

	printf("探索アルゴリズムを実行しますか？(1:YES/else_number:NO):");
	scanf_s("%d", &i);

	if (i == 1) {
		printf("先手か後手どちらで実行しますか？(先手:1/後手:2):");
		scanf_s("%d", &l);
		while (l != 1 && l != 2) {
			printf("1または2を入力してください(先手:1/後手:2):");
			scanf_s("%d", &l);
		}
		printf(l == 1 ? "先手で探索アルゴリズムを実行します\n" : "後手で探索アルゴリズムを実行します\n");
	}
	else {
		printf("探索アルゴリズムは実行しません\n");
	}

	if (i == 1) {
		while (check_finish(t, board) != 0) // 終了判定
		{
			t++; // 1ターン進める
			if ((l == 1 && k == -1) || (l == 2 && k == 1)) {
				number_place(k, board);
				if (check_pass(k, board) != 0) // パス等による打ち手の判定
				{
					int remaining_moves = 0;
					for (int i = 1; i <= 8; i++) {
						for (int j = 1; j <= 8; j++) {
							if (board[i][j] == 0) {
								remaining_moves++;
							}
						}
					}
					// **終盤は完全読み**
					if (remaining_moves <= 12) {
						input_data = endgame_solver(k, board);
						change_board(k, input_data.x, input_data.y, board);
					}
					// **それ以外は通常のαβ探索**
					else {
						input_data = alpha_beta(7, -100000, 100000, k, board);
					}

					number_pieces(board);
					print_board(board);
				}
				k = k * -1; //打ち手の交替
			}
			else {
				t++; //１ターン進める
				number_place(k, board);
				if (check_pass(k, board) != 0) //パス等による打ち手の判定 第三回
				{
					input_data = input_key(k, board); //キーボードから打つことの
					//出来るマスの場所を保存 第一回
					change_board(k, input_data.x, input_data.y, board); //入力から
					//ボードの状態を更新 第二回
					number_pieces(board);
					print_board(board); //更新されたボードの表示 第一回

				}
				k = k * -1; //打ち手の交替
			}
			//オート
			/*else {
				t++; //１ターン進める
				number_place(k, board);
				if (check_pass(k, board) != 0) //パス等による打ち手の判定 第三回
				{
					input_data = two_step_expectation(k, board);//alpha_beta(7, -100000, 100000, k, board); //minimum_mass(k, board); //search_algorithm(k, board);// side_end(k, board);//  tokuten_algorithm(k, board);//maximum_mass(k,board);//  //キーボードから打つことの
					//出来るマスの場所を保存 第一回
					number_pieces(board);
					print_board(board); //更新されたボードの表示 第一回

				}

				k = k * -1; //打ち手の交替
			}*/
		}
	}
	else {
		while (check_finish(t, board) != 0) //終了判定 第三回
		{

			t++; //１ターン進める
			number_place(k, board);
			if (check_pass(k, board) != 0) //パス等による打ち手の判定 第三回
			{
				input_data = input_key(k, board); //キーボードから打つことの
				//出来るマスの場所を保存 第一回
				change_board(k, input_data.x, input_data.y, board); //入力から
				//ボードの状態を更新 第二回
				number_pieces(board);
				print_board(board); //更新されたボードの表示 第一回

			}

			k = k * -1; //打ち手の交替
		}
	}

	return 0;
}