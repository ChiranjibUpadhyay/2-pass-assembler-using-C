#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
main(){
    int j,len;
    char LOC[10],LABEL[10],OPCODE[10],OPERAND[10],MNEMONIC[10],OP[10];
    char fLOC[10],fLABEL[10];
    FILE *fpi,*fpop,*fpobj,*fp;
    fpi=fopen("intermediate.txt","r");
    fp=fopen("final_symtab.txt","r");
    fpop=fopen("opcode.txt","r");
    fpobj=fopen("object_code.txt","w");
    fscanf(fpi,"%s%s%s%s",LOC,LABEL,OPCODE,OPERAND);
    fprintf(fpobj,"%s\t%s\t%s\t%s\n",LOC,LABEL,OPCODE,OPERAND);
    while(!feof(fpi)){
            fscanf(fpi,"%s%s%s%s",LOC,LABEL,OPCODE,OPERAND);
        if(strcmp(OPCODE,"RSUB")==0){
            fprintf(fpobj,"%s\t%s\t%s\t%s\t\t4C0000\n",LOC,LABEL,OPCODE,OPERAND);
        }
        else if((strcmp(OPCODE,"RESB")==0) || (strcmp(OPCODE,"RESW")==0))
            fprintf(fpobj,"%s\t%s\t%s\t%s\n",LOC,LABEL,OPCODE,OPERAND);
        else if(strcmp(OPCODE,"WORD")==0)
            fprintf(fpobj,"%s\t%s\t%s\t%s\t\t%.6X\n",LOC,LABEL,OPCODE,OPERAND,atoi(OPERAND));
        else if(strcmp(OPCODE,"BYTE")==0){
             fprintf(fpobj,"%s\t%s\t%s\t%s\t\t",LOC,LABEL,OPCODE,OPERAND);
            len=strlen(OPERAND);
            if(OPERAND[0]=='C'){
                for(j=2;j<len-1;j++)
                    fprintf(fpobj,"%0X",OPERAND[j]);

                    fprintf(fpobj,"\n");
            }
            if(OPERAND[0]=='X'){
                for(j=2;j<len-1;j++)
                    fprintf(fpobj,"%c",OPERAND[j]);

                    fprintf(fpobj,"\n");
            }
        }
        else if(strcmp(OPCODE,"END")==0){
            fprintf(fpobj,"%s\t%s\t%s\t%s\n",LOC,LABEL,OPCODE,OPERAND);
            break;
        }

       else if(strcmp(OPERAND,"BUFFER,X")==0){

                   rewind(fp);
                    while(!feof(fp)){
                        fscanf(fp,"%s%s",fLABEL,fLOC);
                        if(strcmp(fLABEL,"BUFFER")==0)
                            break;
                        else
                            continue;
                    }

            rewind(fpop);
            while(!feof(fpop)){
                fscanf(fpop,"%s%s",MNEMONIC,OP);
                if(strcmp(MNEMONIC,OPCODE)==0)
                        break;
                else
                    continue;
            }

                            fprintf(fpobj,"%s\t%s\t%s\t%s\t%s9",LOC,LABEL,OPCODE,OPERAND,OP);
                            len=strlen(fLOC);
                            for(j=1;j<len;j++)
                                fprintf(fpobj,"%c",fLOC[j]);

                                fprintf(fpobj,"\n");

        }
            else {

           rewind(fpop);
            while(!feof(fpop)){
                fscanf(fpop,"%s%s",MNEMONIC,OP);
                if(strcmp(MNEMONIC,OPCODE)==0)
                    break;
                else
                    continue;
            }
                        rewind(fp);

                    while(!feof(fp)){
                        fscanf(fp,"%s%s",fLABEL,fLOC);
                        if(strcmp(fLABEL,OPERAND)==0)
                            break;
                        else
                            continue;
                    }
                            fprintf(fpobj,"%s\t%s\t%s\t%s\t\t%s%s\n",LOC,LABEL,OPCODE,OPERAND,OP,fLOC);
                }

        }
    fclose(fpi);
    fclose(fp);
    fclose(fpop);
    fclose(fpobj);
}

