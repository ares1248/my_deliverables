#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define N 10
#define T 100
int board[N][N] = { 0 }; //�{�[�h�̊m��
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
	// ������4�̐΂�z�u
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
	int I = i, J = j; //�T���̏����ʒu�̏���
	int l = k * -1; //�z�u�����Ƃ͕ʂ̋�̏���
	int check = 0; //�Ԃ�l�̊m��
	if (board[I][J] != 0) //�z�u����}�X�ɉ����u����Ă��Ȃ����Ƃ̊m�F�D
		return check;
	while (board[I + 1][J] == l) //�ׂ̃}�X���ʂ̋�̊m�F(��)
	{
		check = 1; //while�����o�R�������̊m�F I++;
		I++;
	}
	if (board[I + 1][J] == k && check == 1) //�ʂ̋�������悪�����̋�̊m�F(��)
	{
		check = 1;
		return check;
	}
	I = i; //�����ʒu�ɖ߂�
	check = 0; //�����l�ɖ߂�

	while (board[I - 1][J] == l) //�ׂ̃}�X���ʂ̋�̊m�F(��)
	{
		check = 1; //while�����o�R�������̊m�F I++;
		I--;
	}
	if (board[I - 1][J] == k && check == 1) //�ʂ̋�������悪�����̋�̊m�F(��)
	{
		check = 1;
		return check;
	}
	I = i; //�����ʒu�ɖ߂�
	check = 0; //�����l�ɖ߂�

	while (board[I][J + 1] == l) //�ׂ̃}�X���ʂ̋�̊m�F(�E)
	{
		check = 1; //while�����o�R�������̊m�F I++;
		J++;
	}
	if (board[I][J + 1] == k && check == 1) //�ʂ̋�������悪�����̋�̊m�F(�E)
	{
		check = 1;
		return check;
	}
	J = j;
	check = 0; //�����l�ɖ߂�

	while (board[I][J - 1] == l) //�ׂ̃}�X���ʂ̋�̊m�F(��)
	{
		check = 1; //while�����o�R�������̊m�F I++;
		J--;
	}
	if (board[I][J - 1] == k && check == 1) //�ʂ̋�������悪�����̋�̊m�F(��)
	{
		check = 1;
		return check;
	}
	J--;
	J = j; //�����ʒu�ɖ߂�
	check = 0; //�����l�ɖ߂�

	while (board[I + 1][J + 1] == l) //�ׂ̃}�X���ʂ̋�̊m�F(�E��)
	{
		check = 1; //while�����o�R�������̊m�F I++;
		I++;
		J++;
	}
	if (board[I + 1][J + 1] == k && check == 1) //�ʂ̋�������悪�����̋�̊m�F(�E��)
	{
		check = 1;
		return check;
	}
	I = i; //�����ʒu�ɖ߂�
	J = j;
	check = 0; //�����l�ɖ߂�

	while (board[I + 1][J - 1] == l) //�ׂ̃}�X���ʂ̋�̊m�F(����)
	{
		check = 1; //while�����o�R�������̊m�F I++;
		I++;
		J--;
	}
	if (board[I + 1][J - 1] == k && check == 1) //�ʂ̋�������悪�����̋�̊m�F(����)
	{
		check = 1;
		return check;
	}

	I = i; //�����ʒu�ɖ߂�
	J = j;
	check = 0; //�����l�ɖ߂�

	while (board[I - 1][J - 1] == l) //�ׂ̃}�X���ʂ̋�̊m�F(����)
	{
		check = 1; //while�����o�R�������̊m�F I++;
		I--;
		J--;
	}
	if (board[I - 1][J - 1] == k && check == 1) //�ʂ̋�������悪�����̋�̊m�F(����)
	{
		check = 1;
		return check;
	}
	I = i; //�����ʒu�ɖ߂�
	J = j;
	check = 0; //�����l�ɖ߂�

	while (board[I - 1][J + 1] == l) //�ׂ̃}�X���ʂ̋�̊m�F(�E��)
	{
		check = 1; //while�����o�R�������̊m�F I++;
		I--;
		J++;
	}
	if (board[I - 1][J + 1] == k && check == 1) //�ʂ̋�������悪�����̋�̊m�F(�E��)
	{
		check = 1;
		return check;
	}
	I = i; //�����ʒu�ɖ߂�
	J = j;
	check = 0; //�����l�ɖ߂�
	return check;
}
void change_board(int k, int i, int j, int board[N][N])
{
	int I = i, J = j; //�T���̏����ʒu�̏���
	int l = k * -1; //�z�u�����Ƃ͕ʂ̋�̏���
	board[I][J] = k; //�^����ꂽ�}�X�ɋ��z�u
	/*for (int n = -1; n < 2; n++) {
		for (int m = -1; m < 2; m++) {
			I = I + n;
			j = j + m;
			while (board[I][j] == l) //�ׂ̃}�X���ʂ̋�̊m�F
			{
				I++;
			}
			if (board[I][j] == k) //�ʂ̋�������悪�����̋�̊m�F�����̋�����ꍇ�ɂ̓}�X�̏����ʒu����ʂ̋�������̋�ɕύX����
			{
				I = i;
				while (board[I][j] == l)//��
				{
					board[I][j] = k;
					I++;
				}
			}
			I = i;
		}

	}
}*/
	while (board[I + 1][j] == l) //�ׂ̃}�X���ʂ̋�̊m�F
	{
		I++;
	}
	if (board[I + 1][j] == k) //�ʂ̋�������悪�����̋�̊m�F�����̋�����ꍇ�ɂ̓}�X�̏����ʒu����ʂ̋�������̋�ɕύX����
	{

		I = i;
		while (board[I + 1][j] == l)//��
		{
			board[I + 1][j] = k;
			I++;
		}
	}
	I = i;

	while (board[I - 1][j] == l) //�ׂ̃}�X���ʂ̋�̊m�F
	{
		I--;
	}
	if (board[I - 1][j] == k) //�ʂ̋�������悪�����̋�̊m�F�����̋�����ꍇ�ɂ̓}�X�̏����ʒu����ʂ̋�������̋�ɕύX����
	{

		I = i;
		while (board[I - 1][j] == l)//��
		{
			board[I - 1][j] = k;
			I--;
		}
	}
	I = i;
	while (board[I][J + 1] == l) //�ׂ̃}�X���ʂ̋�̊m�F
	{
		J++;
	}
	if (board[I][J + 1] == k) //�ʂ̋�������悪�����̋�̊m�F�����̋�����ꍇ�ɂ̓}�X�̏����ʒu����ʂ̋�������̋�ɕύX����
	{

		J = j;
		while (board[I][J + 1] == l)//�E
		{
			board[I][J + 1] = k;
			J++;
		}
	}
	J = j;
	while (board[I][J - 1] == l) //�ׂ̃}�X���ʂ̋�̊m�F
	{
		J--;
	}
	if (board[I][J - 1] == k) //�ʂ̋�������悪�����̋�̊m�F�����̋�����ꍇ�ɂ̓}�X�̏����ʒu����ʂ̋�������̋�ɕύX����
	{

		J = j;
		while (board[I][J - 1] == l)//��
		{
			board[I][J - 1] = k;
			J--;
		}
	}
	J = j;
	while (board[I + 1][J + 1] == l) //�ׂ̃}�X���ʂ̋�̊m�F
	{
		I++;
		J++;
	}
	if (board[I + 1][J + 1] == k) //�ʂ̋�������悪�����̋�̊m�F�����̋�����ꍇ�ɂ̓}�X�̏����ʒu����ʂ̋�������̋�ɕύX����
	{

		I = i;
		J = j;
		while (board[I + 1][J + 1] == l)//�E��
		{
			board[I + 1][J + 1] = k;
			I++;
			J++;
		}
	}
	I = i;
	J = j;
	while (board[I + 1][J - 1] == l) //�ׂ̃}�X���ʂ̋�̊m�F
	{
		I++;
		J--;
	}
	if (board[I + 1][J - 1] == k) //�ʂ̋�������悪�����̋�̊m�F�����̋�����ꍇ�ɂ̓}�X�̏����ʒu����ʂ̋�������̋�ɕύX����
	{

		I = i;
		J = j;
		while (board[I + 1][J - 1] == l)//����
		{
			board[I + 1][J - 1] = k;
			I++;
			J--;
		}
	}
	I = i;
	J = j;
	while (board[I - 1][J - 1] == l) //�ׂ̃}�X���ʂ̋�̊m�F
	{
		I--;
		J--;
	}
	if (board[I - 1][J - 1] == k) //�ʂ̋�������悪�����̋�̊m�F�����̋�����ꍇ�ɂ̓}�X�̏����ʒu����ʂ̋�������̋�ɕύX����
	{

		I = i;
		J = j;
		while (board[I - 1][J - 1] == l)//����
		{
			board[I - 1][J - 1] = k;
			I--;
			J--;
		}
	}
	I = i;
	J = j;
	while (board[I - 1][J + 1] == l) //�ׂ̃}�X���ʂ̋�̊m�F
	{
		I--;
		J++;
	}
	if (board[I - 1][J + 1] == k) //�ʂ̋�������悪�����̋�̊m�F�����̋�����ꍇ�ɂ̓}�X�̏����ʒu����ʂ̋�������̋�ɕύX����
	{

		I = i;
		J = j;
		while (board[I - 1][J + 1] == l)//�E��
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
	printf("���ł��Ƃ��ł��Ȃ��̂Ńp�X���܂��B\n");
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
	printf("���҂Ƃ��p�X�Ȉ׃Q�[�����I�����܂��B\n");
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
	printf("��̐��F����%d,����%d\n", a, b);
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
	printf("�łĂ�}�X�̐���%d�R\n", a);
}
void print_board(int board[N][N]) {
	printf("  �� �P�Q�R�S�T�U�V�W\n");
	printf("�s --------------------\n");
	int i, j;
	for (i = 0; i < 10; i++) {
		if (!(i == 0 || i == 9)) {
			printf("%2d|", i);
		}
		else printf("  |");
		for (j = 0; j < 10; j++) {
			if (board[i][j] == 1) printf("�� ");
			else if (board[i][j] == -1) printf("�� ");
			else if (board[i][j] == 2) printf("�� ");
			else printf("�@");
		}
		printf("\n");
	}
}
struct INPUT_DATA input_key(int k, int board[N][N])
{
	struct INPUT_DATA a {};

	if (k == -1) {
		printf("���̃^�[��\n");
		do {
			printf("�s�F"); scanf_s("%d", &a.x);
			printf("��F"); scanf_s("%d", &a.y);
			if (!(0 < a.x && a.x < 9) || !(0 < a.y && a.y < 9)) {
				puts("\a�s�񂻂ꂼ��h1�`8�h�œ��͂���!!");
				printf("\n");
			}
		} while (!(0 < a.x && a.x < 9) || !(0 < a.y && a.y < 9));

		check_change(k, a.x, a.y, board);
		//if (check_change(k, a.x, a.y, board) == 0) {
		while (check_change(k, a.x, a.y, board) == 0) {
			printf("�����ɋ��u�����Ƃ͂ł��܂���B\n");
			do {
				printf("\n");
				printf("�s�F"); scanf_s("%d", &a.x);
				printf("��F"); scanf_s("%d", &a.y);
				if (!(0 < a.x && a.x < 9) || !(0 < a.y && a.y < 9)) {
					puts("\a�s�񂻂ꂼ��h1�`8�h�œ��͂���!!");
				}
			} while (!(0 < a.x && a.x < 9) || !(0 < a.y && a.y < 9));
			check_change(k, a.x, a.y, board);
		}
	}
	if (k == 1) {
		printf("���̃^�[��\n");
		do {
			printf("�s�F"); scanf_s("%d", &a.x);
			printf("��F"); scanf_s("%d", &a.y);
			if (!(0 < a.x && a.x < 9) || !(0 < a.y && a.y < 9)) {
				puts("\a�s�񂻂ꂼ��h1�`8�h�œ��͂���!!");
				printf("\n");
			}
		} while (!(0 < a.x && a.x < 9) || !(0 < a.y && a.y < 9));
		check_change(k, a.x, a.y, board);
		//if (check_change(k, a.x, a.y, board) == 0) {
		while (check_change(k, a.x, a.y, board) == 0) {
			printf("�����ɋ��u�����Ƃ͂ł��܂���B\n");
			do {
				printf("\n");
				printf("�s�F"); scanf_s("%d", &a.x);
				printf("��F"); scanf_s("%d", &a.y);
				if (!(0 < a.x && a.x < 9) || !(0 < a.y && a.y < 9)) {
					puts("\a�s�񂻂ꂼ��h1�`8�h�œ��͂���!!");
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

	// �΂̐��ƈʒu�̃X�R�A���l��
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

	// �����̕]���i�łĂ��̐����J�E���g�j
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

	// ����΂̕]���i�m��΂̃J�E���g�j
	for (int i = 0; i < 8; i += 7) { // �㉺�̊p
		for (int j = 0; j < 8; j += 7) { // ���E�̊p
			if (board[i + 1][j + 1] == 1) {
				black_stable++;
			}
			else if (board[i + 1][j + 1] == -1) {
				white_stable++;
			}
		}
	}

	// �]���X�R�A�̌v�Z
	int piece_diff = (black_count - white_count) * 10; // �΂̐��̕]��
	int mobility_score = (black_mobility - white_mobility) * 15; // �����̕]��
	int stability_score = (black_stable - white_stable) * 30; // ����΂̕]��

	score += piece_diff + mobility_score + stability_score;

	return score;
}
struct INPUT_DATA endgame_solver(int k, int board[N][N]) {
	struct INPUT_DATA best_move = { 0, 0 };
	int best_score = (k == 1) ? -1000000 : 1000000;
	int temp_board[N][N];

	// ���ׂĂ̗L���Ȏ������
	for (int I = 1; I <= 8; I++) {
		for (int J = 1; J <= 8; J++) {
			if (check_change(k, I, J, board) == 1) {
				// �{�[�h���R�s�[
				for (int i = 0; i < N; i++) {
					for (int j = 0; j < N; j++) {
						temp_board[i][j] = board[i][j];
					}
				}
				change_board(k, I, J, temp_board);

				// ������ **���S�T��** ���s��
				int final_score = evaluate_board(temp_board);

				// �œK�Ȏ���X�V
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
	int max_score = (k == 1) ? -100000 : 100000; // �����l
	int score;


	// ���ׂĂ̗L���Ȏ������
	for (int I = 1; I <= 8; I++) {
		for (int J = 1; J <= 8; J++) {
			if (check_change(k, I, J, board) == 1) {
				// �Ֆʂ��R�s�[���ăV�~�����[�V����
				for (int i = 0; i < N; i++) {
					for (int j = 0; j < N; j++) {
						temp_board[i][j] = board[i][j];
					}
				}
				change_board(k, I, J, temp_board); // ���i�߂�

				// �ċA�I�ɃA���t�@�x�[�^�T��
				if (depth > 1) {
					struct INPUT_DATA next_move = alpha_beta(depth - 1, alpha, beta, -k, temp_board);
				}

				// **�����ŕ]���֐����g���ăX�R�A���v�Z**
				score = evaluate_board(temp_board);

				// **�ő�E�ŏ��X�R�A�̍X�V**
				if (k == 1) { // �����i���j�̎��
					if (score > max_score) {
						max_score = score;
						best_move.x = I;
						best_move.y = J;
					}
					alpha = (alpha > max_score) ? alpha : max_score;
				}
				else { // ����i���j�̎��
					if (score < max_score) {
						max_score = score;
						best_move.x = I;
						best_move.y = J;
					}
					beta = (beta < max_score) ? beta : max_score;
				}

				// **�}����̏���**
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
	int l = -k; // ����̎��
	srand(time(NULL));
	// ���ׂĂ̎������
	for (int I = 1; I <= 8; I++) {
		for (int J = 1; J <= 8; J++) {
			if (check_change(k, I, J, board) == 1) {
				for (int i = 0; i < N; i++) {
					for (int j = 0; j < N; j++) {
						temp_board[i][j] = board[i][j];
					}
				}
				change_board(k, I, J, temp_board);
				// ����̎������
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

							// �����̋���v�Z
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

				// ���Ғl���v�Z
				double expectation = (valid_moves > 0) ? (double)total_pieces / valid_moves : 0.0;
				//printf("%d.%d:%.2f\n", I, J, expectation);
				// �ő���Ғl�������I��
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

	// �őP���ՖʂɓK�p
	change_board(k, best_move.x, best_move.y, board);
	return best_move;
}

int main(void) // �o�͉�ʂɂ����Ĕw�i�����A���������ł��邱��
{
	int board[N][N] = { 0 };
	int t; // �o�߃^�[���̊m��
	int k; // �ł���̊m��
	int i;
	int l;

	struct INPUT_DATA input_data; // ���͂̊m��

	make_board(board); // ��ƃ{�[�h�̏����ݒ�
	print_board(board); // �����̃{�[�h�̕\��
	t = 0; // �o�߃^�[���̏����ݒ�
	k = -1; // �ł���̏����ݒ�

	printf("�T���A���S���Y�������s���܂����H(1:YES/else_number:NO):");
	scanf_s("%d", &i);

	if (i == 1) {
		printf("��肩���ǂ���Ŏ��s���܂����H(���:1/���:2):");
		scanf_s("%d", &l);
		while (l != 1 && l != 2) {
			printf("1�܂���2����͂��Ă�������(���:1/���:2):");
			scanf_s("%d", &l);
		}
		printf(l == 1 ? "���ŒT���A���S���Y�������s���܂�\n" : "���ŒT���A���S���Y�������s���܂�\n");
	}
	else {
		printf("�T���A���S���Y���͎��s���܂���\n");
	}

	if (i == 1) {
		while (check_finish(t, board) != 0) // �I������
		{
			t++; // 1�^�[���i�߂�
			if ((l == 1 && k == -1) || (l == 2 && k == 1)) {
				number_place(k, board);
				if (check_pass(k, board) != 0) // �p�X���ɂ��ł���̔���
				{
					int remaining_moves = 0;
					for (int i = 1; i <= 8; i++) {
						for (int j = 1; j <= 8; j++) {
							if (board[i][j] == 0) {
								remaining_moves++;
							}
						}
					}
					// **�I�Ղ͊��S�ǂ�**
					if (remaining_moves <= 12) {
						input_data = endgame_solver(k, board);
						change_board(k, input_data.x, input_data.y, board);
					}
					// **����ȊO�͒ʏ�̃����T��**
					else {
						input_data = alpha_beta(7, -100000, 100000, k, board);
					}

					number_pieces(board);
					print_board(board);
				}
				k = k * -1; //�ł���̌��
			}
			else {
				t++; //�P�^�[���i�߂�
				number_place(k, board);
				if (check_pass(k, board) != 0) //�p�X���ɂ��ł���̔��� ��O��
				{
					input_data = input_key(k, board); //�L�[�{�[�h����ł��Ƃ�
					//�o����}�X�̏ꏊ��ۑ� ����
					change_board(k, input_data.x, input_data.y, board); //���͂���
					//�{�[�h�̏�Ԃ��X�V ����
					number_pieces(board);
					print_board(board); //�X�V���ꂽ�{�[�h�̕\�� ����

				}
				k = k * -1; //�ł���̌��
			}
			//�I�[�g
			/*else {
				t++; //�P�^�[���i�߂�
				number_place(k, board);
				if (check_pass(k, board) != 0) //�p�X���ɂ��ł���̔��� ��O��
				{
					input_data = two_step_expectation(k, board);//alpha_beta(7, -100000, 100000, k, board); //minimum_mass(k, board); //search_algorithm(k, board);// side_end(k, board);//  tokuten_algorithm(k, board);//maximum_mass(k,board);//  //�L�[�{�[�h����ł��Ƃ�
					//�o����}�X�̏ꏊ��ۑ� ����
					number_pieces(board);
					print_board(board); //�X�V���ꂽ�{�[�h�̕\�� ����

				}

				k = k * -1; //�ł���̌��
			}*/
		}
	}
	else {
		while (check_finish(t, board) != 0) //�I������ ��O��
		{

			t++; //�P�^�[���i�߂�
			number_place(k, board);
			if (check_pass(k, board) != 0) //�p�X���ɂ��ł���̔��� ��O��
			{
				input_data = input_key(k, board); //�L�[�{�[�h����ł��Ƃ�
				//�o����}�X�̏ꏊ��ۑ� ����
				change_board(k, input_data.x, input_data.y, board); //���͂���
				//�{�[�h�̏�Ԃ��X�V ����
				number_pieces(board);
				print_board(board); //�X�V���ꂽ�{�[�h�̕\�� ����

			}

			k = k * -1; //�ł���̌��
		}
	}

	return 0;
}