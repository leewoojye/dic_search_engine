#define NAME_LENGTH 11//파일의 이름 길이 제한
#define WORD_LENGTH 20//검색하는 단어의 길이 제한
#define MAX_NUM_DOC 100//읽어들이는 최대 문서의 수 제한
#define delimiter " \"\n\t`'…?!.,:()"//구분자(문자열에서 토큰을 나눌때 쓰임)

typedef struct treeNode* treePtr;//트리노드를 가리키는 포인터를 treePtr로 정의 
typedef struct treeNode {
	char data[WORD_LENGTH];//단어
	int  count;//단어의 출현 횟수
	int docnum[100];
	treePtr left;
	treePtr right;//단어의 자식 노드
}node;//트리 노드 구조체를 node로 정의.

treePtr hash_table[MAX_NUM_DOC][100];//해시테이블로, 입력받은 파일의 순서대로 크기가 30인 일차원 해시테이블을 이용하는 셈이 된다.
int num_comparison = 0;//삽입시 비교연산이 일어나는 횟수
int num_search = 0;//검색시 비교연산이 일어나는 총 횟수
char document_name[MAX_NUM_DOC][NAME_LENGTH];//입력받은 파일의 이름을 순서대로 저장하는 문자열 배열
int indexed_word = 0;//색인된 단어의 개수

int transform(char* key);//folding 방식으로 key의 각 character 값을 더해 숫자로 변환하는 함수
void search_word(char* key, int d);//단어를 검색하고, 그 단어가 속한 파일 이름과 검색하는동안 일어난 비교연산 횟수를 출력하는 함수
void make_bst(char* key, treePtr p, treePtr temp);//해시테이블에 이진탐색트리를 연결하는 함수
treePtr search_bst(char* key, treePtr p);//이진탐색트리를 검색하여 원하는 노드를 반환하는 함수. 찾는 데이터가 없다면 NULL을 반환.
void bulid_hash_table(char* fname, int d);//파일을 색인하여 해시테이블을 만드는 함수
void insert_hash_table(char* key, int d);//해시 테이블에 자료를 삽입하는 함수

int hash(char* key);//folding값을 30으로 나눈 나머지를 해시함수 값으로 이용
void print_idx_result(int i);//색인 결과를 프린트한다.
void print_result(treePtr p, int i);//검색 후 결과를 프린트함.
void print_doc(char* fname, treePtr p);//검색 결과가 있는 문서의 위치를 프린트하는 함수