#include <stdio.h>
#include <stdlib.h>

int main()
{
	printf("test_1 번 파일 실행되었습니다. exit(100) 인지 확인하세요.\n");
	printf("bash: 100: command not found ~라고 나오면 정상입니다.\n");
	exit(100);
	return (0);
}