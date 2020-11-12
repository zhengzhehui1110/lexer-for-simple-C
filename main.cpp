#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

#define MAXNUM 10000 //token串的最大长度

#define ID 1  //标识符
#define CINT 2  //常量整数
#define CREAL 3  //常量实数
#define CCHAR 4   //常量字符
#define CSTRING 5  //常量字符串
//关键字
#define MAIN 6
#define VOID 7
#define INT 8
#define CHAR 9
#define FLOAT 10
#define PRINTF 11
#define SCANF 12
#define ELSE 13
#define IF 14
#define RETURN 15
#define WHILE 16
#define STRING 17

//运算符
#define ADD 100 //+
#define SUB 101 //-
#define MUL 102 //*
#define DIV 103 // /
#define ASSIGN 104 //=
#define GT 105 //> greater than
#define LT 106 //< less than
#define NGT 107 //<= not greater than
#define NLT 108 //>= not less than
#define MOD 109 //%
#define NOT 110 // !
#define AND 111 //&&
#define OR 112 //||
#define EQUAL 113 //==
#define ANDBIT 114 //&
#define ORBIT 115 //|

//分界符
#define COMMA 150 //,
#define SEMI 151 //;
#define LBR 152 //(
#define RBR 153 //)
#define LSBR 154 //[
#define RSBR 155 //]
#define LBRACE 156 //{
#define RBRACE 157 //}

char *keyword[12] = {  //关键字表
    "main",
    "void",
    "int",
    "char",
    "float",
    "printf",
    "scanf",
    "else",
    "if",
    "return",
    "while",
    "string"
};

struct Token{
    char name[30];  //单词
    int type;   //单词类型
};

Token token[MAXNUM];  //token串
char id[MAXNUM][30] = {'\0'};  //标识符集合
int token_count = 0; //单词的数量
int id_count = 0; //标识符的数量

void SetToken(char buf[30],int type) {
    token[token_count].type = type;
    strcpy(token[token_count].name,buf);
    printf("%s\t%d\n",token[token_count].name,token[token_count].type);
    return;
}


int IsKeyword(char *word) {
    for(int i = 0;i < 12;i++) {
        if(strcmp(word,keyword[i])==0) {
            return i;  //如果在关键字表中查到ch，ch是关键字
        }
    }
    return -1;   //查不到则ch是标识符
}

int IsIdExist(char buf[30]) {  //判断该标识符是否已出现过
    int i;
    for (i = 0;i < id_count;i++) {
        if(strcmp(buf,id[i])==0) {
            return i;  //出现过，返回在表中的index
        }
    }
    return -1; //未出现过
}

void Scan(FILE *fp) {


    char buf[30] = {'\0'};  //缓冲区,任何一个单词的长度不能超过30
    char ch;
    int i;
    ch = fgetc(fp);  //读入一个字符
    //printf("ch is %c\n",ch);
    if(isalpha(ch)) {  //第一个字符为字母，则有可能是关键字或标识符
        buf[0] = ch;
        ch = fgetc(fp);
        i = 1;
        int keytype; //关键字的种类
        while(isalnum(ch)||isdigit(ch)) {  //后面的字符是数字或字母
            buf[i] = ch;
            i++;
            ch = fgetc(fp);
        }
        buf[i] = '\0';
        fseek(fp,-1,1);
        keytype = IsKeyword(buf);
        if(keytype != -1) {
            //printf("(%s) 是关键字 %d\n",buf,keytype);
            SetToken(buf,keytype + 6);
        }
        else {
            //printf("(%s) 是标识符\n",buf);
            int n = IsIdExist(buf);
            if(n==-1){  //如果出现了新的标识符
                strcpy(id[id_count],buf);
                id_count++;
            }
            SetToken(buf,ID);
        }
    }

    else if(isdigit(ch) ) {   //第一个字符是数字
        buf[0] = ch;
        ch = fgetc(fp);
        i = 1;
        while(isdigit(ch)) {
            buf[i] = ch;
            i++;
            ch = fgetc(fp);
        }
        if(ch == '.') { //有小数点，是实数
            buf[i] = ch;
            i++;
            ch = fgetc(fp);
            while(isdigit(ch)) {
            buf[i] = ch;
            i++;
            ch = fgetc(fp);
            }
            buf[i] = '\0';
            fseek(fp,-1,1);
            //printf("(%s) 是实数\n",buf);
            SetToken(buf,CREAL);
        }
        else{  //无小数点，是整数
            buf[i] = '\0';
            fseek(fp,-1,1);
            //printf("(%s) 是整数\n",buf);
            SetToken(buf,CINT);
        }

    }

    else {
        buf[0] = ch;
        buf[1] = '\0';
        switch(ch) {
        case '[':
            //printf("(%s) %d\n",buf,LSBR);
            SetToken(buf,LSBR);
            break;
        case ']':
            //printf("(%s) %d\n",buf,RSBR);
            SetToken(buf,RSBR);
            break;
        case '(':
            //printf("(%s) %d\n",buf,LBR);
            SetToken(buf,LBR);
            break;
        case ')':
            //printf("(%s) %d\n",buf,RBR);
            SetToken(buf,RBR);
            break;
        case '{':
            //printf("(%s) %d\n",buf,LBRACE);
            SetToken(buf,LBRACE);
            break;
        case '}':
            //printf("(%s) %d\n",buf,RBRACE);
            SetToken(buf,RBRACE);
            break;
        case ',':
            //printf("(%s) %d\n",buf,COMMA);
            SetToken(buf,COMMA);
            break;
        case '"':
            i = 1;
            ch = fgetc(fp);
            while(ch != '"') {
                buf[i] = ch;
                ch = fgetc(fp);
                i++;
            }
            buf[i] = ch;
            buf[i+1] = '\0';
            //printf("(%s) %d\n",buf,CSTRING);
            SetToken(buf,CSTRING);
            break;
        case 39:  //单引号
            i = 1;
            ch = fgetc(fp);
            while(ch != 39) {
                buf[i] = ch;
                ch = fgetc(fp);
                i++;
            }
            buf[i] = ch;
            buf[i+1] = '\0';
            //printf("(%s) %d\n",buf,CCHAR);
            SetToken(buf,CCHAR);
            break;
        case ';':
            //printf("(%s) %d\n",buf,SEMI);
            SetToken(buf,SEMI);
            break;
        case '+':
            //printf("(%s) %d\n",buf,ADD);
            SetToken(buf,ADD);
            break;
        case '-':
            //printf("(%s) %d\n",buf,SUB);
            SetToken(buf,SUB);
            break;
        case '*':
            //printf("(%s) %d\n",buf,MUL);
            SetToken(buf,MUL);
            break;
        case '/':
            //printf("(%s) %d\n",buf,DIV);
            SetToken(buf,DIV);
            break;
        case '%':
            //printf("(%s) %d\n",buf,MOD);
            SetToken(buf,MOD);
            break;
        case '=':
            ch = fgetc(fp);
            if(ch == '=') { //逻辑相等号
                buf[1] = ch;
                buf[2] = '\0';
                //printf("(%s) %d\n",buf,EQUAL);
                SetToken(buf,EQUAL);
            }
            else { //等号
                //printf("(%s) %d\n",buf,ASSIGN);
                SetToken(buf,ASSIGN);
                fseek(fp,-1,1);
            }
            break;
        case '!':
            //printf("(%s) %d\n",buf,NOT);
            SetToken(buf,NOT);
            break;
        case '<':
            ch = fgetc(fp);
            if(ch == '=') { //小于等于号
                buf[1] = ch;
                buf[2] = '\0';
                //printf("(%s) %d\n",buf,NGT);
                SetToken(buf,NGT);
            }
            else{  //小于号
                buf[1] = '\0';
                //printf("(%s) %d\n",buf,LT);
                SetToken(buf,LT);
                fseek(fp,-1,1);
            }
            break;
        case '>':
            ch = fgetc(fp);
            if(ch == '=') {  //大于等于号
                buf[1] = ch;
                buf[2] = '\0';
                //printf("(%s) %d\n",buf,NLT);
                SetToken(buf,NLT);
            }
            else{  //大于号
                buf[1] = '\0';
                //printf("(%s) %d\n",buf,GT);
                SetToken(buf,GT);
                fseek(fp,-1,1);
            }
            break;
        case '&':
            ch = fgetc(fp);
            if(ch == '&') {
                buf[1] = ch;
                buf[2] = '\0';
                //printf("(%s) %d\n",buf,AND);
                SetToken(buf,AND);
            }
            else {
                buf[1] = '\0';
                //printf("(%s) %d\n",buf,ANDBIT);
                SetToken(buf,ANDBIT);
                fseek(fp,-1,1);
            }
            break;
        case '|':
            ch = fgetc(fp);
            if(ch == '|') {
                buf[1] = ch;
                buf[2] = '\0';
                //printf("(%s) %d\n",buf,OR);
                SetToken(buf,OR);
            }
            else {
                buf[1] = '\0';
                //printf("(%s) %d\n",buf,ORBIT);
                SetToken(buf,ORBIT);
                fseek(fp,-1,1);
            }
            break;
        default: ;

        }
    }



    return;
}

int main() {
    FILE *fp = fopen("input.txt","r");

    if(fp == NULL) {  //文件打开错误
        printf("cannot open input file\n");
        return 0;
    }
    char ch;

    do{
        ch = fgetc(fp);
        if (ch == '#') break;
        else if (ch == ' '||ch == '\t'||ch == '\n') continue; //忽略空格和换行
        //printf("%c\n",ch);
        fseek(fp,-1,1);  //回退一个字符
        Scan(fp);   //从第一个不是空格和换行的字符开始扫描
        token_count++;
    }while(ch!='#');
    fclose(fp);

    FILE *tokenfile = fopen("token.txt","w");
    if(tokenfile == NULL) {  //输出文件token打开失败
        printf("cannot open tokenfile\n");
        return 0;
    }
    fwrite(token, token_count, sizeof(Token), tokenfile);
    fclose(tokenfile);

    //FILE *testfp = fopen("token.txt","r");
    //Token test;
    //fread(&test, 1, sizeof(Token), testfp);
    //printf("\n%d %s\n",test.type,test.name);

    FILE *idfile = fopen("idfile.txt","w");
    if(idfile == NULL) {  //输出文件idfile打开失败
        printf("cannot open idfile\n");
        return 0;
    }
    fwrite(id, id_count, sizeof(char)*30, idfile);
    fclose(idfile);
    return 0;
}
