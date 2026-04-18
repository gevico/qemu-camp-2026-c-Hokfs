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
        int row;
        int col;
    }Point;

    Point stack[MAX_ROW * MAX_COL];
    int top = 0;

    Point cur={0,0};
    stack[top++]=cur;
    maze[cur.row][cur.col]=2;

    while (top>0) {
        cur=stack[top-1];
        if (cur.row==MAX_ROW-1 && cur.col==MAX_COL-1) {
            break;
        }
        if (cur.col<MAX_COL-1 && maze[cur.row][cur.col+1]==0) {
            Point next={cur.row,cur.col+1};
            stack[top++]=next;
            maze[next.row][next.col]=2;
        }else if (cur.row<MAX_ROW-1 && maze[cur.row+1][cur.col]==0) {
            Point next={cur.row+1,cur.col};
            stack[top++]=next;
            maze[next.row][next.col]=2;
        }else if (cur.col-1>=0 && maze[cur.row][cur.col-1]==0) {
            Point next={cur.row,cur.col-1};
            stack[top++]=next;
            maze[next.row][next.col]=2;
        }else if (cur.row-1>=0 && maze[cur.row-1][cur.col]==0) {
            Point next={cur.row-1,cur.col};
            stack[top++]=next;
            maze[next.row][next.col]=2;
        }else {
            top--;
        }
    }
    if (top>0) {
        for (int i=0; i<top; i++) {
            printf("(%d, %d)\n", stack[i].row, stack[i].col);
        }
    }
        else {
            printf("not\n");
        }
	return 0;
}