#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
#include<limits.h>

typedef struct {	
	char *deinloc;
	int t,y;
	char *inloc;
} dict;
long long euclid(long long a, long long b)
	
{
    long long c;
    while (b) {
        c = a % b;
        a = b;
        b = c;
    }
    return a;
}
char *citire(char *s1, int n,char **s)
{char *aux,p[2];int i,num,k,lung,poz=0;
	aux=malloc(2*n*sizeof(char));

	for(i=0;i<n;i++)
		{	p[0]=s1[i];
			if(s1[i]=='#')
							continue;
			else {k=atoi(p);
								if(k==0)
										{aux[poz]=' ';
										poz++;}
								 else if(k==1)
											{ i++;
												num=0;
												p[0]=s1[i];
												k=atoi(p);
											while(atoi(p)==k)
													{   i++;
														num++;
														p[0]=s1[i];
													} i--;
											lung=strlen(s[k]);
											while(num > lung)
													num=num-lung;
											aux[poz]=s[k][num-1];
											aux[poz]=toupper(aux[poz]);
											poz++;
											}
								else
										{num=0;
										while(atoi(p)==k)
												{   i++;
													num++; 	
													p[0]=s1[i];
												} i--;
										lung=strlen(s[k]);
										while(num > lung)
												num=num-lung;
										aux[poz]=s[k][num-1];
										poz++;
										}

			}
		}return aux;

} 

char *codificare(char *s2,int m,char **s)
{
	char *aux; int i, poz=0,lung,j,tul,tast,ant=0,l;
		aux=malloc(301*sizeof(char));
	for(i=0;i<m;i++)
	{ if(s2[i]==' ')
			{
				aux[poz]='0';
				poz++;
			}
			else if(s2[i]>='a'&&s2[i]<='z')
			{	for(j=2;j<=9;j++)
				{
					lung=strlen(s[j]);
						for(l=0;l<lung;l++)
							{if(s2[i]==s[j][l])
									{if(ant==j)
										{aux[poz]='#';
										poz++;}
										ant=j;
										tast=l+1;
											while(tast!=0)
											{aux[poz]=j+'0';
											poz++;
											tast--;
											}
											l=lung-1;
									}
							}

				}

			}
			else if(s2[i]>='A'&& s2[i]<='Z')
			{
				for(j=2;j<=9;j++)
				{
					lung=strlen(s[j]);
						for(l=0;l<lung;l++)
							{if(s2[i]==s[j][l]-32)
									{if(ant==j)
										{aux[poz]='#';
										poz++;}
										aux[poz]='1';
										poz++;
										ant=j;
										tast=l+1;
											while(tast!=0)
											{aux[poz]=j+'0';
											poz++;
											tast--;
											}
											l=lung-1;
									}
							}

				}

			}



	}return aux;
}

char *dictionar(char* s3,int marime,dict dicti[])
{ char sep[1]={' '}, *p, *aux,*sir;
		int i, k=0;
			aux=malloc(256*sizeof(char));
			aux[0]='0';
			p=strtok(s3,sep);
			while(p)
			{
				k=0;
				for(i=0;i<marime;i++)
					if(strcmp(p,dicti[i].deinloc)==0)
						{
						strcat(aux,dicti[i].inloc);
						strcat(aux,sep);
						p=strtok(NULL,sep);
						k=1;
						i=marime;
						}
						if(k==0)
							{strcat(aux,p);
								strcat(aux,sep);
							p=strtok(NULL,sep);	}
						



			} 
			int n=strlen(aux);
			aux[n]='\0';
			aux=aux+1;

			return aux;



		}
		void prim(char **s,char *s4)
		{char *aux,p[2],*magic;
			magic=malloc(256*sizeof(char));
			long long *magic1,schimb,*v,maxi=LLONG_MIN;
			magic1=malloc(256*sizeof(int));

			int pozitie,schimbare;
			int mini=INT_MAX;
			int k=0,suma=0;
			int n,j1=0,i=0,j;
			aux=malloc(256*sizeof(char));
			v=malloc(256*sizeof(long long));
			v[0]=0;
			aux=codificare(s4,strlen(s4),s);
			printf("%s\n",aux);
			strcpy(magic,aux);
			for(i=0;i<strlen(aux);i++)
								{
									if(aux[i]=='#')
										{
											continue;}
									else if(aux[i]=='0')
										{
											j1++;
											v[j1]=0;
											continue;
											}
											else {p[0]=aux[i];
													v[j1]=10*v[j1]+atoi(p);
													suma=suma+atoi(p);
													printf("%d\n",suma);
											}
								}			
							
					long long *prim1;
					prim1=malloc(256*sizeof(long long));
						for(i=0;i<j1;i++)
							for(j=i+1;j<=j1;j++)
								{prim1[k]=euclid(v[i],v[j]);
									k++;
						}
						k=0;
						for(i=0;i<=j1;i++)
						{printf("%lld ",v[i]);
						}
						printf("\n");
						for(i=0;i<j1;i++)
							if(prim1[i]!=1)
								k=1;
							if(k!=1)	
						printf("%d\n",k);

						for(i=0;i<=j1;i++)
						{if(v[i]>maxi)
							{maxi=v[i];
								pozitie=i;}

						}
						printf("%lld %d\n",maxi,pozitie+1);
						if(k==0)
							printf("1\n");
						else printf("0\n");

						printf("Nr de componente este: %d\n",j1+1);
						printf("%d\n",suma);
						suma=suma%9;
						j=0;
						for(i=0;i<strlen(magic);i++)
						{
							magic1[i]=0; 
						}
						j=0;
						n=0;
					if(suma==0)
						printf("0");

					else if(suma!=0)
						{	for(i=0;i<strlen(magic);i++)
								{	
										if(magic[i]=='#')
											{i++;
												}
									if(magic[i]!='#')
										{	p[0]=magic[i];
											k=atoi(p);
											magic1[j]=10*magic1[j]+k;
											n++;

										}
										if(n%suma==0)
											{j++;
												n=0;}

										
								}
								}k=j;
									for(i=0;i<k;i++)
										for(j=i+1;j<k;j++)
											if(magic1[i]<magic1[j])
												{
												schimb=magic1[i];
												magic1[i]=magic1[j];
												magic1[j]=schimb;

											}
											for(i=0;i<k;i++)
									printf("%lld ",magic1[i]);

							}

					
						





int main()
{ char **s,*s1,*p,*s2,*p2,*p3;
	int i,n,m,k=0;
	s=malloc(12*sizeof(char*));
	for(i=0;i<11;i++)
		s[i]=malloc(12*sizeof(char));
	s[0]=(" ");
	s[2]=("abc");
	s[3]=("def");
	s[4]=("ghi");
	s[5]=("jkl");
	s[6]=("mno");
	s[7]=("pqrs");
	s[8]=("tuv");
	s[9]=("wxyz");
s1=malloc(256*sizeof(char));
s2=malloc(256*sizeof(char));
 	fgets(s2,256,stdin);
 	m=strlen(s2);
 	p2=codificare(s2,m,s);
 	
fgets(s1,256,stdin);
n=strlen(s1);
 	p=citire(s1,n,s);
 	char *s3;
 	s3=malloc(256*sizeof(char));
 	scanf(" %[^\n]",s3);
 	int marime;
 	scanf("%d",&marime);
 	dict dicti[100];
 	for(i=0;i<marime;i++)
 		{	k=0;
 			dicti[i].t=1;
 			dicti[i].y=1;
 			dicti[i].deinloc=malloc(dicti[i].t*sizeof(char));
 			dicti[i].inloc=malloc(dicti[i].y*sizeof(char));
 			scanf(" %c",&dicti[i].deinloc[k]);
 			
 				while(dicti[i].deinloc[k]!=' ')
 		{k++;
 			if(k==dicti[i].t)
 				{dicti[i].t=dicti[i].t+1;
 				dicti[i].deinloc=realloc(dicti[i].deinloc,dicti[i].t*sizeof(char));
 						}
 					scanf("%c",&dicti[i].deinloc[k]);
 					
 	}
 		dicti[i].deinloc[k]='\0';
 		k=0;
 		scanf(" %c",&dicti[i].inloc[k]);
 		
 	{	while(dicti[i].inloc[k]!='\n')
 		{k++;
 			if(k==dicti[i].y)
 				{dicti[i].y=dicti[i].y+1;
 				dicti[i].inloc=realloc(dicti[i].inloc,dicti[i].y*sizeof(char));
 						}
 					scanf("%c",&dicti[i].inloc[k]);
 				
 	}
 		dicti[i].inloc[k]='\0';
 	}
 	}
 	
 	p3=dictionar(s3,marime,dicti);
 	k=strlen(p3);
 	p3=codificare(p3,k,s);
 	k=strlen(p3);
 	p3[k-1]='\0';
 	char *s4;
 	s4=malloc(256*sizeof(char));
 	scanf(" %[^\n]",s4);
 	printf("%s\n",p2);
printf("%s",p);
 	printf("\n");
 	printf("%s\n",p3);
 	prim(s,s4);
}
