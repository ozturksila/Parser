#include<stdio.h>
#include<ctype.h>
#include<string.h>


void keyw(char *p);
int i=0,id=0,kw=0,eolCh=0,paran=0,bparan=0;
FILE *f2;
char keys[15][8]= {"int","out","add","sub","to","from","move","loop","times","result","loop","times","newline","size"};
int main()

{
    char ch,str[500],seps[15]=" \t\n,;(){}[]#\"<>",oper[]="{([)]}";
    int j;
    char fname[100];
    FILE *f1;
    //clrscr();
    printf("enter file path:\n");
    scanf("%s",fname);
    strcat(fname,".txt");
    f1 = fopen(fname,"r");
    f2 = fopen("output.txt","w");
    //f1 = fopen("Input","r");
    if(f1==NULL)
    {
        printf("file not found");
        exit(0);
    }
    while((ch=fgetc(f1))!=EOF)
        
    {
        
        if (ch=='"')
        {
            printf("\"");
            do
            {
                
                ch=fgetc(f1);
                printf("%c",ch);
            }while(ch!='"');
            printf(" \b is a string\n");
            i=-1;
        }
        else{
            for(j=0; j<=5; j++)
            {
                if(ch==oper[j])
                {
                    if(ch=='{')
                    {
                        printf("{ :is a comment paranthesis.\n");
                        fprintf(f2,"{ :is a comment paranthesis.\n");
                        paran++;
                        do
                        {
                            ch=fgetc(f1);// BURDA PARANTEZ KAPATMA HATA KONTROLU YAPILIR
                            if(feof(f1) || ch == '\n'){printf("ERROR: There is no '}'.\n");break;}
                            
                            
                        }while(ch!='}');
                        if(ch=='}'){
                            paran++;
                            printf("}:is a comment paranthesis.\n");
                            fprintf(f2,"} :is a comment paranthesis.\n");
                        }
                        i=-1;
                        break;
                    }
                    
                    paran++;
                    str[i]='\0';
                    keyw(str);
                    if(ch==oper[2]||ch==oper[4]){
                        printf("%c :is a block paranthesis.\n",ch);
                        bparan++;
                    }
                    if(ch==oper[2]||ch==oper[4]) printf("%c :is a block paranthesis.\n",ch);
                    else if(ch==oper[0]||ch==oper[5]) printf("%c :is a paranthesis.\n",ch);
                    
                    fprintf(f2,"%c :is a paranthesis.\n",ch);
                    
                }
            }
            for(j=0; j<=14; j++)
            {
                if(i==-1) break;
                if(ch==seps[j])
                {
                    
                    if(ch=='{')
                    {
                        do
                        {
                            ch=fgetc(f1);
                            printf("%c",ch);
                        }while(ch!='}');
                        printf("\b is a comment\n");
                        i=-1;
                        break;
                    }
                    str[i]='\0';
                    keyw(str);
                }
            }
            
            if(i!=-1 && ch!='\r')
            {
                str[i]=ch;
                i++;
            }
            else
                i=0;
        }
        }
        if (bparan%2!=0){
            printf("Expected ']' \n");
        } // açılan blok parantez sayısı kapanan blok parantez sayısına uymaz ise hata verir
    
        printf("Keywords: %d\nIdentifiers: %d\nParanthesis: %d\nEnd of Line characters: %d\n",kw,id,paran,eolCh);
        fprintf(f2,"Keywords: %d\nIdentifiers: %d\nParanthesis: %d\nEnd of Line characters: %d\n",kw,id,paran,eolCh);
        //getch();
        
        return 0;
    }

    void keyw(char *p)
    
    {
        int k,flag=0;
        
        for(k=0; k<=8; k++)
        {
            if(strcmp(keys[k],p)==0)
                
                
            {
                printf("%s :is a keyword\n",p);
                fprintf(f2,"%s :is a keyword\n",p);
                kw++;
                flag=1;
                break;
            }
        }
        if(flag==0)
        {
            if(p[0]=='.')
            {
                printf("%s :is a end of line character\n",p);
                fprintf(f2,"%s :is a end of line character\n",p);
                eolCh++;
            }
            else
            {
                //if(p[0]!=13&&p[0]!=10)
                
                if(p[0]!=0 && !isdigit(p[0]) && p[0]!='\r')
                {
                    
                    printf("%s :is an identifier\n",p);
                    fprintf(f2,"%s :is an identifier\n",p);
                    id++;
                
                }
        
            }
        }
        i=-1;
        
        
    }
