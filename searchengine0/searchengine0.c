#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include "searchengine0.h"

int main()
{
	char	c, fname[NAME_LENGTH];
	char	key[WORD_LENGTH];
	int	dcount = 0; //�����͸� �о�� ������ ������ �����ϴ� �����̴�.

		for (int dcount = 0; dcount < 100; dcount++) {
			sprintf(fname, "doc%03d.txt", dcount + 1);
			strcpy(document_name[dcount], fname);
			bulid_hash_table(fname, dcount);
		}
		printf("----------Result----------\n");
		printf("keyword: ");
		scanf("%s", key);
		search_word(key, dcount);
		print_idx_result(dcount);

		return 0;
	}


int transform(char* key) {
	int n = 0;
	while (key == '\0')
		n += *key++;
	return n;
} //folding ������� key�� �� character ���� ���� ���ڷ� ��ȯ�ϴ� �Լ�

void search_word(char* key, int d) {
	int i;
	treePtr result;
	int f = 0;

	for (i = 0; i < 100; i++)
	{
		treePtr p = hash_table[i][hash(key)];
		result = search_bst(key, p);
		print_result(result, i); 
		if (result != NULL) {
			print_doc(document_name[i], result);
			f++;
		}
	}
	printf("\nTotal number of comparison = %d\n", num_search);
	printf("Total number of documents = %d \n", f);
	num_search = 0;
} //�ܾ �˻��ϰ�, �� �ܾ ���� ���� �̸��� �˻��ϴµ��� �Ͼ �񱳿��� Ƚ���� ����ϴ� �Լ�

void make_bst(char* key, treePtr p, treePtr temp)
{
	indexed_word++;
	treePtr a;
	a = p;
	while (a) {
		num_comparison++; //���� �񱳿��� �� ����
		if (strcmp(key, a->data) == 0)
		{
			a->count++;
			return;
		} //���� a�� �����Ϳ� Ű�� ���ٸ�, a�� ����Ƚ���� ������Ų��.
		p = a;
		if (strcmp(key, a->data) < 0)
			a = a->left;
		else
			a = a->right; //a�� �����Ϳ� Ű�� �ٸ��ٸ�, ��ġ�ϴ� �����͸� ã�� ��������.
	}

	if (p != NULL)
	{
		if (strcmp(key, p->data) < 0)
			p->left = temp;
		else
			p->right = temp;
	} //��ġ�ϴ� �����Ͱ� ���ٸ� ��带 ����.
} //�ؽ����̺� ����Ž��Ʈ���� �����ϴ� �Լ�

treePtr search_bst(char* key, treePtr p)
{
	treePtr ptr = p;
	//int e, doccount= 0;
	while (ptr != NULL) {
		num_search++; //Ű�� ����� �����Ͱ� �񱳰� �Ͼ�Ƿ� �˻� �񱳿����� Ƚ���� ������Ų��.
		if (strcmp(key, ptr->data) == 0)
			return ptr; //Ű�� ����� ������ ���� ���ٸ� �� ��带 ��ȯ.
		if (strcmp(key, ptr->data) < 0)
			ptr = ptr->left;
		else
			ptr = ptr->right; //�ٸ��ٸ� ���ϴ� ��带 ã�� ������.
	}
	return NULL;
} //����Ž��Ʈ���� �˻��Ͽ� ���ϴ� ��带 ��ȯ�ϴ� �Լ�. ã�� �����Ͱ� ���ٸ� NULL�� ��ȯ.

void bulid_hash_table(char* fname, int d)
{
	char line[256];
	char* token;

	FILE* fp;
	fp = fopen(fname, "r"); //���� ����� ��Ʈ���� �б���� ����.
	if (fp == NULL)
	{
		printf("There is no file.\n");
		return;
	} //������ �������� �ʴ´ٸ� ������ �о�� �� ����.
	else {
		while (fgets(line, 256, fp) != NULL) //������ ���������� ���پ� �д´�.
		{
			token = strtok(line, delimiter); //��ū�� �и��س���.
			while (token != NULL)
			{
				insert_hash_table(token,d);
				token = strtok(NULL, delimiter);
			} //�� ��ū�� �ؽ����̺� �����ϰ�, ��ū�� �� ������ ���� ������ ���������� �ݺ��Ѵ�.
		}
		printf("<%s> File indexig is completed.\n", fname);//���� ������ �������� ǥ��.
	}
	fclose(fp); //���� ����� ��Ʈ���� �ݴ´�.
} //������ �����Ͽ� �ؽ����̺��� ����� �Լ��̴�.

void insert_hash_table(char* key, int d)
{
	treePtr temp = (treePtr)malloc(sizeof(node));
	strcpy(temp->data, key);
	temp->count = 1;
	temp->left = temp->right = NULL; //Ʈ���� ��带 ���� �Ҵ��ϰ�, ������ �ʱ�ȭ�Ѵ�.

	treePtr q = hash_table[d][hash(key)];
	if (q == NULL)
	{
		num_comparison++; //���νÿ� �Ͼ�� �� ������ ���� ������Ų��.
		indexed_word++;
		hash_table[d][hash(key)] = temp;
	}
	else
		make_bst(key, q, temp);
	//���� hash_table[d][hash(key)]�� ��尡 ���ٸ� �װ��� ��� ����. �̹� ��� �����Ѵٸ� ����Ž��Ʈ���� �����.
} //�ؽ� ���̺� �ڷḦ �����ϴ� �Լ�

int hash(char* key) {
	return transform(key) % 30;
} //folding���� 30���� ���� �������� �ؽ��Լ� ������ �̿�

void print_idx_result(int i)
{
	//printf("\nTotal number of documents = %d \n", i);
	printf("Total number of indexed words = %d \n", indexed_word);
	printf("Total number of comparison = %d\n", num_comparison);
} //���� ����� ����Ʈ�Ѵ�.

void print_result(treePtr p, int i)
{
	if (p) {
		printf("\n<%s> %s : %d", document_name[i], p->data, p->count);
	}
} //�˻� �� ����� ����Ʈ��.

void print_doc(char* fname, treePtr p)
{
	char line[64];
	char printLine[64];
	char* token, * token2;

	FILE* fp;
	fp = fopen(fname, "r"); //���� ����� ��Ʈ���� ����
	if (fp == NULL)
	{
		printf("There is no file.\n");
		return;
	} //������ �������� �ʴ´ٸ�, ����� ������ �� ������ ǥ���Ѵ�.

	while (fgets(line, 64, fp) != NULL) //���Ͽ��� 32���� ���ھ� �о�´�
	{
		strcpy(printLine, line);
		token = strtok(line, delimiter);
		while (token != NULL)
		{
			if (strcmp(token, p->data) == 0) { //���� token�� ã�� �ܾ�� ��ġ�Ѵٸ�
				printf("\n * %s", printLine);
			} //�� token�� ���ϴ� ������ ����Ѵ�.

			token = strtok(NULL, delimiter);
		}
	}
	printf("\n");
	fclose(fp); //���� ����� ��Ʈ���� �ݴ´�.
} //�˻� ����� �ִ� ������ ��ġ�� ����Ʈ�ϴ� �Լ�