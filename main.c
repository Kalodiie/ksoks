#include<stdio.h>
#define O 3

typedef struct pobeda{
	int iks;
	int oks;
	int ner;
}mem;

int provera(int a[O][O]);
void ispis(int a[O][O],char c[3][3]);
int unos(FILE *f,mem *m)
{
	fscanf(f,"%d%d%d",&(m->iks),&(m->oks),&(m->ner));
	return !feof(f);
}


main()
{
	FILE *f=fopen("partije.txt","r");
	mem Upis;
	char yn;
	unos(f,&Upis);
	fclose(f);
	printf("Trenutni rezultati:\n-------\nX = %d\nO = %d\nNereseno = %d\n------\n",Upis.iks,Upis.oks,Upis.ner);
	printf("Da li zelite da vratite sve rezultate na 0? Y/N?");
	yn=getchar();
	if(yn=='y' || yn=='Y')
	{	putchar('\n');
		Upis.iks=Upis.oks=Upis.ner=0;
		printf("Trenutni rezultati nakon restartovanja:\n-------\nX = %d\nO = %d\nNereseno = %d\n------\n",Upis.iks,Upis.oks,Upis.ner);
	
	}
	int x=1;
	int a[O][O]={{0,0,0},{0,0,0},{0,0,0}},i=0,j=0,potez=0,pobednik=0,polje,zauzeto[]={0,0,0,0,0,0,0,0,0};
	char c[O][O]={{'-','-','-'},{'-','-','-'},{'-','-','-'}},win,igrac,string[100];
	printf("Brojevi na koje ubacujete karktere.\n");
	for(i=0;i<9;i++)
	{
		if(i%3==0) putchar('\n');
		printf("%d\t",i+1);
	}
	do{
		if(potez%2==0) igrac='x';
			else igrac='o';
		printf("\n\nIgrac na redu: %c",igrac);	
		printf("\n%d. potez\n",potez+1);
		//UNOS ZELJENOG POLJA
		printf("Unesite broj polja na tastaturi (od 1 do 9) za polje u koje zelite da unesete znak.\n");
		scanf("%d",&polje);
		x=1;
		while(x>0){
			
				while(zauzeto[polje-1]!=0 || polje<=0 || polje>9){
					fflush(stdin);
					printf("Polje na koje ste pokusali da unesete znak je zauzeto ili ne postoji. Unesite drugi odgovor.\n");
					scanf("%d",&polje);
				}
				 
					switch(polje)
					{
						case 1:
							if(potez%2==0)
								a[0][0]=1;
							else a[0][0]=-1; 
							zauzeto[0]=1; break;
						case 2:
							if(potez%2==0)
								a[0][1]=1;
							else a[0][1]=-1; 
							zauzeto[1]=1; break;
						case 3:
							if(potez%2==0)
								a[0][2]=1;
							else a[0][2]=-1; 
							zauzeto[2]=1; break;
						case 4:
							if(potez%2==0)
								a[1][0]=1;
							else a[1][0]=-1; 
							zauzeto[3]=1; break;
						case 5:
							if(potez%2==0)
								a[1][1]=1;
							else a[1][1]=-1; 
							zauzeto[4]=1; break;
						case 6:
							if(potez%2==0)
								a[1][2]=1;
							else a[1][2]=-1; 
							zauzeto[5]=1; break;
						case 7:
							if(potez%2==0)
								a[2][0]=1;
							else a[2][0]=-1; 
							zauzeto[6]=1; break;
						case 8:
							if(potez%2==0)
								a[2][1]=1;
							else a[2][1]=-1; 
							zauzeto[7]=1; break;
						case 9:
							if(potez%2==0)
							
								a[2][2]=1;
							else a[2][2]=-1; 
							zauzeto[8]=1; break;
					}
					x=0;	
		}
		potez++;
		printf("\n");
		ispis(a,c);
		pobednik=provera(a);
	}
	while(potez<9 && pobednik==0);
		
		if(pobednik!=0){
			if(pobednik==1){
				Upis.iks++;
				win='x';
			}
			else{
				Upis.oks++;
			 win='o';
			}
			printf("Pobednik je %c!",win);
		}
		else
		{
			Upis.ner++;	
			printf("NERESENA IGRA");
		}	
		f=fopen("partije.txt","w");
		fprintf(f,"%d %d %d",Upis.iks,Upis.oks,Upis.ner);
		fclose(f);
		
		system("PAUSE");
	}



//FUNKCIJE
int provera(int a[O][O])
{
	int i,j,n=0,zbir1=0,zbir2=0,zbir3=0,zbir4=0;	//Zbir1 je za vodoravne pobede,Zbir2 je za vertikalne
	for(i=0;i<O;i++)								//Zbir3 je glavnda dijagonala a Zbir4 sporedna
	{
		zbir3+=a[i][i];
		zbir4 += a[i][2 - i];
		for(j=0;j<O;j++)
		{
			zbir1+=a[i][j];
			zbir2+=a[j][i];
			n=i+j+1;
			//Sabiranje redova kolona i dijagonala		
			if(zbir1==3 || zbir2==3 || zbir3==3 || zbir4==3)	return 1;
			if(zbir1==-3 || zbir2==-3 || zbir3==-3 || zbir4==-3) return -1;
	
		}
		zbir1=0;
		zbir2=0;
	}
	return 0;
}

void ispis(int a[O][O],char c[O][O])
{
	int i,j;
	for(i=0;i<O;i++)
		{	
			if(i==0) printf("\n+-----+-----+-----+\n");
			for(j=0;j<O;j++)
			{
						
				if(a[i][j]==1)
					c[i][j]='x';
				if(a[i][j]==-1)
					c[i][j]='o';
				printf("|%3c  ",c[i][j]);
				
				if(j==O-1)
				{
					putch('|');
					printf("\n+-----+-----+-----+\n");
				}
					
			}
			
		}	
}
