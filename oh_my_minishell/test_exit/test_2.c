#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("test_1 번 파일 실행되었습니다. exit(30) 인지 확인하세요.\n");
	printf("bash: 30: command not found ~라고 나오면 정상입니다.\n");
	exit(30);
	return (0);
}