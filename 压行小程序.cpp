#include <bits/stdc++.h>
using namespace std;
int main()
{

    // system("chcp 65001");
    // setlocale(LC_ALL, "zh-CN");
    char s[100000];
    printf("请输入您的代码，输入之后：linux:按下ctrl+d，windows下，按下ctrl+z\n");
    FILE *p = freopen("yahang.out", "w", stdout);
    while(scanf("%s", s) != EOF){
        if(s[0] == s[1] && s[1] == '/') {
            fgets(s, 100000, stdin);
            continue;
        }
        if(s[0] == '#') {
            fprintf(p, "%s ", s);
            fgets(s, 100000, stdin);
            fprintf(p, "%s ", s);
            puts("");
        }
        else
            fprintf(p, "%s ", s);
    }
    fclose(p);
    printf("请到yahang.out查看，注意在#之后添加换行");
    system("pause");
    return 0;
}