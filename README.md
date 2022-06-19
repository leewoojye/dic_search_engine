개요
===========

100개의 텍스트 파일을 읽어서 영단어 탐색을 기능하는 C언어 프로젝트

1. 찾고자 하는 단어 검색
2. 단어가 포함된 문서 번호와 문서당 해당 단어 출연 빈도수 출력
3. 해당 단어가 포함된 주위 문장 출력
4. 색인 알고리즘에 따라 색인 과정 중 몇 번의 탐색 횟수가 있었는지 출력


주의사항
==========

1. doc001.txt~doc100.txt 파일들의 이름을 읽어내는 코드로 구성되어 있어 다른 이름의 텍스트 파일을 읽을 경우 수정해야 합니다.
또한 문서의 개수가 100개를 넘어갈 경우 main 혹은 search 함수의 반복문을 수정할 필요가 있습니다.

2. 찾고자 하는 단어가 포함된 문장을 출력하는 print_doc 함수는 단어가 아닌 글자 단위로 토큰화를 진행하기 때문에 일부 문장을 출력하지 못하는 예외가 발생할 수 있습니다.

#해결방안

*파일 입출력 - 파일 위치 지정자와 ftell(),fseek()

파일에서 입출력을 처음부터 끝까지 순서대로 받을 수 있는 이유는 파일 위치 지정자가 한 칸씩 이동하며 작업을 수행했기 때문입니다.

	long ftell(FILE *); 
	int fseek(FILE *, long, int);

ftell()함수는 인자로 *FILE을 넘기면 현재 파일의 입출력 작업 위치를 확인하여 반환하는 함수이며 fseek()함수는 파일 입출력 작업 위치를 변경할 수 있는 함수입니다.

*문자열 관련 함수 - strstr()
	char *strstr(const char *, const char *) 

strstr()함수는 원본 문자열, 찾을 문자열을 차례로 전달해 원본 문자열에서 찾을 문자열의 위치를 반환하고, 만약 찾을 문자열이 존재하지 않는다면 NULL을 반환하는 함수입니다. 이 두 가지 함수를 이용하여 출력 부분을 수정할 수 있을 것 같습니다.

3. 해당 
