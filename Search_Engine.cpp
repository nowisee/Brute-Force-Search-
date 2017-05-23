#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define STC_MAX 1000
#define LINE_MAX 50
#define NEWS_NUM 25

double cmp = 0, cpt = 0;

typedef struct {
	char stc[STC_MAX];
	int line;
} LSTRING;

LSTRING list[NEWS_NUM][LINE_MAX];

int brute(char *pattern, char *text)
{
	int lenPattern = strlen(pattern)-1, lenText = strlen(text)-1;
	int i, j;

	cpt+=2;

	cmp++;
	cpt++;
	for (i = 0; i <= lenText - lenPattern; i++) {
		cmp++;
		cpt++;

		cmp++;
		for (j = 0; j < lenPattern; j++) {
			cmp++;
			if (pattern[j] != text[i + j])
				break;
		}
		cmp++;
		if (j == lenPattern)
			return i;
	}
	return -1;
}

int main(void) {
	int indexPattern;
	int i, j, k, line[NEWS_NUM], input_cnt=0, line_cnt=0;
	char input_stc[100];
	char dels1[] = ",";
	char *word[4];
	char file_name[128];
	bool b_or[4];
	
	for(i=0; i<4; i++) b_or[i] = false;
	for(i=0; i<NEWS_NUM; i++) line[i] = 1;

	for(j=0; j < NEWS_NUM; j++)
	{
		// File Open 1~25.txt
		sprintf(file_name, "%d.txt\0", j+1);
		FILE *fp = fopen(file_name, "r");
		if(fp == NULL)
		{
			printf("파일 오픈 실패!\n");
			exit(-1);
		}

		// Numbering Sentence_line
		line[j]=1;
		while(fgets(list[j][line[j]].stc, sizeof(list[j][line[j]].stc), fp) != NULL)
		{
			list[j][line[j]].line = line[j];
			line[j]++;
		}

		fclose(fp);
	}

	// Input Sentence
	printf("Input Word(,로 구분하여 두 단어까지) : ");
	fgets(input_stc, sizeof(word), stdin);
	printf("\n");
	strlwr(input_stc);

	// Setence -> Words
	word[0] = strtok(input_stc, dels1);

	input_cnt=0;
	while(word[input_cnt] != NULL)
	{
		input_cnt++;
		word[input_cnt] = strtok(NULL, dels1);
	}

	for(j=0; j<NEWS_NUM; j++)
	{
		line_cnt=0;

		for(i=1; i<line[j]; i++)
		{
			strcpy(list[j][0].stc, list[j][i].stc);
			strlwr(list[j][0].stc);
			cpt+=3;

			for(k=0; k<4; k++) b_or[k] = false;

			for(k=0; k<input_cnt; k++)
			{
				indexPattern = brute(word[k], list[j][0].stc);
		
				if(indexPattern != -1)
				{
					if(line_cnt==0) // Print Headline
						printf("########### News %d : %s", j+1, list[j][1].stc);
					if(!b_or[0] && !b_or[1] && !b_or[2] && !b_or[3]) // OR
						printf("Line %d : %s\n", i, list[j][i].stc);
					line_cnt++;
					b_or[k] = true;
				}
			}
		}

		if(line_cnt!=0) printf("\n");
	}

	printf("총 비교 횟수 : %d, 자료이동 횟수 : %d\n", cmp, cpt);

	return 0;
}