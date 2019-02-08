#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
int convert(int);
main(){
        char LABEL[10],OPCODE[10],OPERAND[10],LOC[10];
        int LOCCTR,hex,STARTP,ENDP,LENGTH;
        FILE *fpr,*fpw,*fp;
        fpr=fopen("symtab.txt","r");
        fpw=fopen("intermediate.txt","w");
        if(fpr==NULL)
            printf("file not found");
        fscanf(fpr,"%s%s%s",LABEL,OPCODE,OPERAND);
        if(strcmp(OPCODE,"START")==0){
            hex=atoi(OPERAND);
            LOCCTR=convert(hex);
        fprintf(fpw,"%0X\t%s\t%s\t%s\n",LOCCTR,LABEL,OPCODE,OPERAND);
        fscanf(fpr,"%s%s%s",LABEL,OPCODE,OPERAND);
        }
        else
            LOCCTR=0;
        while((strcmp(OPCODE,"END"))!=0){
                fprintf(fpw,"%0X\t%s\t%s\t%s\n",LOCCTR,LABEL,OPCODE,OPERAND);
                if(strcmp(OPCODE,"WORD")==0)
                    LOCCTR=LOCCTR+3;
                else if(strcmp(OPCODE,"RESW")==0)
                    LOCCTR=LOCCTR+(3*atoi(OPERAND));
                else if(strcmp(OPCODE,"RESB")==0)
                    LOCCTR=LOCCTR+(atoi(OPERAND));
                else if(strcmp(OPCODE,"BYTE")==0){
                    if(OPERAND[0]=='C')
                        LOCCTR=LOCCTR+(strlen(OPERAND)-3);
                    else if(OPERAND[0]=='X')
                        LOCCTR=LOCCTR+1;
                }
                else
                    LOCCTR=LOCCTR+3;
               fscanf(fpr,"%s%s%s",LABEL,OPCODE,OPERAND);
}
        if(strcmp(OPCODE,"END")==0){
           fprintf(fpw,"%0X\t%s\t%s\t%s\n",LOCCTR,LABEL,OPCODE,OPERAND);
        }
        fclose(fpr);
        fclose(fpw);
        fpw=fopen("intermediate.txt","r");
        fp=fopen("final_symtab.txt","w");
        fscanf(fpw,"%s%s%s%s",LOC,LABEL,OPCODE,OPERAND);
        STARTP=convert(atoi(LOC));
        while(!feof(fpw)){
            if((strcmp(LABEL,"NULL"))!=0)
                fprintf(fp,"\n%s\t%s",LABEL,LOC);
            fscanf(fpw,"%s%s%s%s",LOC,LABEL,OPCODE,OPERAND);
        }
       /* ENDP=convert(atoi(LOC));
        fclose(fpw);
        fclose(fp);
        LENGTH=ENDP-STARTP+1;*/
        printf("\nThe length of the program is %s",LOC);
}
int convert(int h){
    int dec=0,rem,i=0;
    while(h!=0){
        rem=h%10;
        dec=dec+rem*pow(16,i);
        h/=10;
        i++;
    }
    return(dec);
}
