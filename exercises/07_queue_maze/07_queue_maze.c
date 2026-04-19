#include <stdio.h>

#define MAX_ROW 5
#define MAX_COL 5

int maze[MAX_ROW][MAX_COL] = {
	0, 1, 0, 0, 0,
	0, 1, 0, 1, 0,
	0, 0, 0, 0, 0,
	0, 1, 1, 1, 0,
	0, 0, 0, 1, 0,
};

int main(void)
{
	// TODO: 在这里添加你的代码

    typedef struct {
        int row, col;
        int pre; // 记录上一个点在队列中的下标，用于回溯路径
    } Node;

    Node queue[MAX_ROW * MAX_COL];
    int head = 0, tail = 0; // 队头和队尾

    Node cur = {0, 0,-1};
    queue[tail++] = cur;
    maze[cur.row][cur.col] = 2;
    int found=0;

    while (head < tail) {
        cur = queue[head++];
        if (cur.row == MAX_ROW - 1 && cur.col == MAX_COL - 1) {
            found = 1;
            break;
        }

        if (cur.row + 1 < MAX_ROW && maze[cur.row + 1][cur.col] == 0) {
            cur.pre = head-1;
            Node next = {cur.row + 1, cur.col,cur.pre};
            queue[tail++] = next;
            maze[next.row][next.col] = 2;
        }
        // 2. 上
        if (cur.row - 1 >= 0 && maze[cur.row - 1][cur.col] == 0) {
            cur.pre = head-1;
            Node next = {cur.row - 1, cur.col,cur.pre};
            queue[tail++] = next;
            maze[next.row][next.col] = 2;
        }
        // 3. 左
        if (cur.col - 1 >= 0 && maze[cur.row][cur.col - 1] == 0) {
            cur.pre = head-1;
            Node next = {cur.row, cur.col - 1,cur.pre};
            queue[tail++] = next;
            maze[next.row][next.col] = 2;
        }
        // 4. 右
        if (cur.col + 1 < MAX_COL && maze[cur.row][cur.col + 1] == 0) {
            cur.pre = head-1;
            Node next = {cur.row, cur.col + 1,cur.pre};
            queue[tail++] = next;
            maze[next.row][next.col] = 2;
        }
    }


    if (found==1) {
        int i = head - 1;
        while (i != -1) {
            printf("(%d, %d)\n", queue[i].row, queue[i].col);
            i = queue[i].pre; // 顺着 pre 往回爬
        }
    }

	return 0;
}