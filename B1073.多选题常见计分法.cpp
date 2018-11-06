#include<iostream>
#include<vector>
#include<cmath>
using namespace std;

int main()
{
	int n, m;
	int hashTable[10] = {1, 2, 4, 8, 16}, opt[1010][110] = {0};
	int opt_num = 0, true_opt_num = 0, temp = 0, max_error_cnt = 0;
	char c;
	scanf("%d %d", &n, &m);
	//每道题的满分值，每道题的正确选项 
	vector<int> full_score(m), true_opt(m);
	vector<vector<int> > fre(m);	//错误的次数
	for(int i = 0; i < m; i++){
		scanf("%d %d %d", &full_score[i], &opt_num, &true_opt_num);
		for(int j = 0; j < true_opt_num; j++){
			scanf(" %c", &c);
			true_opt[i] += hashTable[c-'a'];
		}
		fre[i].resize(5);
	} 
	for(int i = 0; i < n; i++){
		double grade = 0.0;
		for(int j = 0; j < m; j++){
			getchar();	//吸收换行符 
			getchar();	//吸收 (
			scanf("%d", &temp);
			for(int k = 0; k < temp; k++){
				scanf(" %c", &c);
				opt[i][j] += hashTable[c-'a'];
			}
			getchar();	//吸收 )
			int el = opt[i][j] ^ true_opt[j];	//进行异或运算 
			if(el){
				if((opt[i][j] | true_opt[j]) == true_opt[j]){
					grade += full_score[j] * 1.0 / 2;
				}
				if(el){
					if(el & hashTable[0]) fre[j][0]++;	//a
					if(el & hashTable[1]) fre[j][1]++;	//b
					if(el & hashTable[2]) fre[j][2]++;	//c
					if(el & hashTable[3]) fre[j][3]++;	//d
					if(el & hashTable[4]) fre[j][4]++;	//e
				}
			}else{
				grade += full_score[j];
			}
		}	
		printf("%.1f\n", grade);
	}
	for(int i = 0; i < m; i++){
		for(int j = 0; j < 5; j++){
			max_error_cnt = max_error_cnt > fre[i][j] ? max_error_cnt : fre[i][j];
		}
	}
	if(max_error_cnt == 0){
		printf("Too simple\n");
	}else{
		for(int i = 0; i < m; i++){
			for(int j = 0; j < fre[i].size(); j++){
				if(max_error_cnt == fre[i][j]){
					printf("%d %d-%c\n", max_error_cnt, i+1, 'a'+j);
				}
			}
		}
	}			
	return 0;
}
