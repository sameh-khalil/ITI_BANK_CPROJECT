
#include <stdio.h>
#include <stdlib.h>
#include "STD_TYPES.h"
#include "cusDB.h"
#define DBFILENAME "./cusDB.txt"
static void rhm(cus_t * s_cus);
static void cpytofile(FILE * file2 ,cus_t * s_cus);

/*
static u32 DBROWSSIZE (FILE * file);
static void reserve_heap_memory(cus_DB_t * db , u32 size);
static void free_heap_memory (cus_DB_t * db , u32 size);
static void parsfilefornamesandpasswordANDWritetonewfile (FILE*file,cus_DB_t * db ,u32 size);
void cpytofile(FILE * file2 ,cus_DB_t * db, u32 size);
*/



/*

cus_DB_t cusDB_INIT (void)
{
	//data base setup
	FILE * cussize =fopen("./cusdbsize.txt","r");
	cus_DB_t DB_ ;

	if(cussize==NULL)
	{printf("file didn't open \n");}
	else
	{
		DB_._MAX=DBROWSSIZE(cussize);
		DB_.strsize=100;
		DB_.rowsize = cusMRSIZE ;
	}
	
	fclose(cussize);

	return DB_ ;

}




static u32 DBROWSSIZE (FILE * file)
{
	int j = 1  ;
	u32 size= 0;
	char ch[20] ;
	fgets(ch,20,file);
	for(int i = strlen(ch)-1 ; i >=0 ;i-- )
	{
		size += ((int)(ch[i]-'0'))*j;
		j*=10;
	}
	return size ;
}




static void reserve_heap_memory(cus_DB_t * db , u32 size)
{
		db->_BID = (char ** )malloc(size*sizeof(char*));
		db->_N	 = (char ** )malloc(size*sizeof(char*));
		db->_P   = (char ** )malloc(size*sizeof(char*));
		db->_S   = (char ** )malloc(size*sizeof(char*));
		db->_BAL = (char ** )malloc(size*sizeof(char*));
		db->_nID = (char ** )malloc(size*sizeof(char*));
		db->_ADDR = (char ** )malloc(size*sizeof(char*));
		db->_AGE = (char ** )malloc(size*sizeof(char*));
		db->_GnID = (char ** )malloc(size*sizeof(char*));

		for(u32 i = 0 ; i < size ; i ++)
		{
			db->_BID[i]	=(char*)malloc((14)*sizeof(char));
            db->_N[i]	=(char*)malloc((db->strsize/2)*sizeof(char));
            db->_P[i]	=(char*)malloc((14)*sizeof(char));
            db->_S[i]	=(char*)malloc((14)*sizeof(char));
            db->_BAL[i]	=(char*)malloc((14)*sizeof(char));
            db->_nID[i]	=(char*)malloc((14)*sizeof(char));
            db->_ADDR[i]=(char*)malloc((db->strsize)*sizeof(char));
            db->_AGE[i]	=(char*)malloc((4)*sizeof(char));
            db->_GnID[i]=(char*)malloc((14)*sizeof(char));

		}
		
}


static void free_heap_memory (cus_DB_t * db , u32 size)
{
		for(u32 i = 0 ; i < size ; i ++)
		{
			free(db->_BID[i]	)  ;
			free(db->_N[i]		)  ;
			free(db->_P[i]		)  ;
			free(db->_S[i]		)  ;
			free(db->_BAL[i]	)  ;
			free(db->_nID[i]	)  ;
			free(db->_ADDR[i]	)  ;
			free(db->_AGE[i]	)  ;
			free(db->_GnID[i]	)  ;
		}
		free(db->_BID	)  ;
		free(db->_N		)  ;
		free(db->_P		)  ;
		free(db->_S		)  ;
		free(db->_BAL	)  ;
		free(db->_nID	)  ;
		free(db->_ADDR	)  ;
		free(db->_AGE	)  ;
		free(db->_GnID	)  ;
		
		db->_BID	= NULL;
		db->_N		= NULL;
		db->_P		= NULL;
		db->_S		= NULL;
		db->_BAL	= NULL;
		db->_nID	= NULL;
		db->_ADDR	= NULL;
		db->_AGE	= NULL;
		db->_GnID	= NULL;
		
}

static void parsfilefornamesandpasswordANDWritetonewfile (FILE*file,cus_DB_t * db ,u32 size)
{
	u32 i= 0 ;	
	reserve_heap_memory(db ,size);
	while (	  fscanf(file, "%s ", db->_BID[i]	)== 1 \
			&&fscanf(file, "%s ", db->_N[i]		)== 1 \
			&&fscanf(file, "%s ", db->_P[i]		)== 1 \
			&&fscanf(file, "%s ", db->_S[i]		)== 1 \
			&&fscanf(file, "%s ", db->_BAL[i]	)== 1 \
			&&fscanf(file, "%s ", db->_nID[i]	)== 1 \
			&&fscanf(file, "%s ", db->_ADDR[i]	)== 1 \
			&&fscanf(file, "%s ", db->_AGE[i]	)== 1 \
			&&fscanf(file, "%s ", db->_GnID[i]	)== 1  )
    {
		i++;		
		if(i==size-1)
		{break;}
	}
	#if 0
	u32 j = 0 ;
	j=i;
	for(i = 0 ; i < j ; i++)
	{printf("%s \t\t\t\t %s\n",db->_n[i],db->_p[i]);}

	#endif
}


int cussearch (cus_DB_t * db , char * name , char * password)
{
	FILE * file =fopen(DBFILENAME,"r");
	if(file==NULL)
	{printf("file didn't open \n");return 0;}
	FILE * file2 =fopen("new.txt","a");
	u32 REMAINFILEROWS = db->_MAX ;
	u32 _rs = db->rowsize ;
	while(_rs<= REMAINFILEROWS)
	{	
		parsfilefornamesandpasswordANDWritetonewfile (file,db,_rs);
		for(int i = 0 ; i < _rs;i++)
		{
			if(db->_N[i][0]==name[0])
			{
				if(strcmp(db->_N[i],name)==0)
				{
					if(strcmp(db->_P[i],password)==0)
					{
						cpytofile(file2,db,i-1);
						fclose(file2);
						fclose(file);
						//free_heap_memory(db,_rs);
						return i ;}
					else
					{
						fclose(file2);
						remove("new.txt");
						fclose(file);
						free_heap_memory(db,_rs);
						return -2;}
				}
			}
			
		}
		cpytofile(file2,db,_rs);
		free_heap_memory(db,_rs);
		REMAINFILEROWS-=_rs;
	}
	if(REMAINFILEROWS>0)
	{
		_rs = REMAINFILEROWS;
		parsfilefornamesandpasswordANDWritetonewfile (file,db,_rs);
		for(int i = 0 ; i < _rs;i++)
		{
			if(db->_N[i][0]==name[0])
			{
				if(strcmp(db->_N[i],name)==0)
				{
					if(strcmp(db->_P[i],password)==0)
					{
						cpytofile(file2,db,i-1);
						fclose(file2);
						fclose(file);
						//free_heap_memory(db,_rs);
						return i ;
					}
					else
					{
						fclose(file2);
						remove("new.txt");
						fclose(file);
						free_heap_memory(db,_rs);
						return -2;
					}
				}
			}
		}
		
		

	
		
	}
	fclose(file2);
	remove("new.txt");	
	free_heap_memory(db,_rs);	
	fclose(file);
	
	
	return -1 ;
		
}


void cpytofile(FILE * file2 ,cus_DB_t * db, u32 size)
{
	u32 i = 0 ;
	while(i<size)
	{	fprintf(file2,db->_BID[i]	)  ;
		fprintf(file2,"\t")            ;
		fprintf(file2,db->_N[i]		)  ;
		fprintf(file2,"\t")            ;
		fprintf(file2,db->_P[i]		)  ;
		fprintf(file2,"\t")            ;
		fprintf(file2,db->_S[i]		)  ;
		fprintf(file2,"\t")            ;
		fprintf(file2,db->_BAL[i]	)  ;
		fprintf(file2,"\t")            ;
		fprintf(file2,db->_nID[i]	)  ;
		fprintf(file2,"\t")            ;
		fprintf(file2,db->_ADDR[i]	)  ;
		fprintf(file2,"\t")            ;
		fprintf(file2,db->_AGE[i]	)  ;
		fprintf(file2,"\t")            ;
		fprintf(file2,db->_GnID[i]	)  ;
		fprintf(file2,"\n")            ;
		i++;
	}
}

*/



static void rhm(cus_t * s_cus)
{
	s_cus->_BID		=(char*)malloc((14)*sizeof(char));
	s_cus->_N	=(char**)malloc(4*sizeof(char*));
	s_cus->_N[0]	=(char*)malloc((s_cus->strsize/2)*sizeof(char));
	s_cus->_N[1]	=(char*)malloc((s_cus->strsize/2)*sizeof(char));
	s_cus->_N[2]	=(char*)malloc((s_cus->strsize/2)*sizeof(char));
	s_cus->_N[3]	=(char*)malloc((s_cus->strsize/2)*sizeof(char));
	s_cus->_P		=(char*)malloc((14)*sizeof(char));
	s_cus->_S		=(char*)malloc((14)*sizeof(char));
	s_cus->_BAL		=(char*)malloc((14)*sizeof(char));
	s_cus->_nID		=(char*)malloc((14)*sizeof(char));
	s_cus->_ADDR	=(char*)malloc((s_cus->strsize)*sizeof(char));
	s_cus->_AGE		=(char*)malloc((4)*sizeof(char));
	s_cus->_GnID	=(char*)malloc((14)*sizeof(char));		
}

void fhm(cus_t * s_cus)
{
	free(s_cus->_BID	);
	if(s_cus->_N!=NULL && sizeof(s_cus->_N)>0)
	{
		free(s_cus->_N[0]   );
		free(s_cus->_N[1]   );
		free(s_cus->_N[2]   );
		free(s_cus->_N[3]   );
	}
	free(s_cus->_N	    );
	free(s_cus->_P	    );
	free(s_cus->_S	    );
	free(s_cus->_BAL	);
	free(s_cus->_nID	);
	free(s_cus->_ADDR	);
	free(s_cus->_AGE	);
	free(s_cus->_GnID	);
}

cus_t cussearch ( char ** name , char * password)
{

	cus_t s_cus ={NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,100,0};
	FILE * file =fopen(DBFILENAME,"r");
	if(file==NULL)
	{printf("file didn't open \n");return s_cus;}
	rhm(&s_cus);
	while (	  fscanf(file, "%s ", s_cus._BID	)== 1 \
			&&fscanf(file, "%s ", s_cus._N[0]	)== 1 \
			&&fscanf(file, "%s ", s_cus._N[1]	)== 1 \
			&&fscanf(file, "%s ", s_cus._N[2]	)== 1 \
			&&fscanf(file, "%s ", s_cus._N[3]	)== 1 \
			&&fscanf(file, "%s ", s_cus._P		)== 1 \
			&&fscanf(file, "%s ", s_cus._S		)== 1 \
			&&fscanf(file, "%s ", s_cus._BAL	)== 1 \
			&&fscanf(file, "%s ", s_cus._nID	)== 1 \
			&&fscanf(file, "%s ", s_cus._ADDR	)== 1 \
			&&fscanf(file, "%s ", s_cus._AGE	)== 1 \
			&&fscanf(file, "%s ", s_cus._GnID	)== 1  )
	{
		if(s_cus._N[0][0]==name[0][0])
		{
			if(strcmp(s_cus._N[0],name[0])==0&&strcmp(s_cus._N[1],name[1])==0&&strcmp(s_cus._N[2],name[2])==0&&strcmp(s_cus._N[3],name[3])==0)
			{
				if(strcmp(s_cus._P,password)==0)
				{
					fclose(file);
					return s_cus ;
				}
				else
				{
					s_cus.state=1;
				}
			}
		}
	}
	fclose(file);
	fhm(&s_cus);
	s_cus._BID	=NULL;
	s_cus._N	=NULL;
	s_cus._P	=NULL;	
	s_cus._S	=NULL;	
	s_cus._BAL	=NULL;
	s_cus._nID	=NULL;
	s_cus._ADDR	=NULL;
	s_cus._AGE	=NULL;
	s_cus._GnID	=NULL;
	printf("kkkk\n");
	if(s_cus.state==0){s_cus.state=2;} 
	return s_cus;

}

void insertEditedcus (cus_t * s_new_cus)
{

	cus_t s_cus ={NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,100};	
	FILE * file =fopen(DBFILENAME,"r");
	if(file==NULL)
	{printf("file didn't open \n");return ;}

	FILE * file2 =fopen("new.txt","a");
	if(file2==NULL)
	{printf("file2 didn't open \n");return ;}

	rhm(&s_cus);
	
	while (	  fscanf(file, "%s ", s_cus._BID	)== 1 \
			&&fscanf(file, "%s ", s_cus._N[0]	)== 1 \
			&&fscanf(file, "%s ", s_cus._N[1]	)== 1 \
			&&fscanf(file, "%s ", s_cus._N[2]	)== 1 \
			&&fscanf(file, "%s ", s_cus._N[3]	)== 1 \
			&&fscanf(file, "%s ", s_cus._P		)== 1 \
			&&fscanf(file, "%s ", s_cus._S		)== 1 \
			&&fscanf(file, "%s ", s_cus._BAL	)== 1 \
			&&fscanf(file, "%s ", s_cus._nID	)== 1 \
			&&fscanf(file, "%s ", s_cus._ADDR	)== 1 \
			&&fscanf(file, "%s ", s_cus._AGE	)== 1 \
			&&fscanf(file, "%s ", s_cus._GnID	)== 1  )
	{
		if(s_cus._BID[0]==s_new_cus->_BID[0])
		{
				if(strcmp(s_cus._BID,s_new_cus->_BID)==0)
				{
					cpytofile(file2 ,s_new_cus);

				}
				else
				{cpytofile(file2 ,&s_cus);}
		}
		else
		{	
			cpytofile(file2 ,&s_cus);
			#if 0
			printf("%s\t",s_cus._BID	);
			printf("%s\t",s_cus._N[0]	);
			printf("%s\t",s_cus._N[1]	);
			printf("%s\t",s_cus._N[2]	);
			printf("%s\t",s_cus._N[3]	);
			printf("%s\t",s_cus._P		);
			printf("%s\t",s_cus._S		);
			printf("%s\t",s_cus._BAL	);
			printf("%s\t",s_cus._nID	);
			printf("%s\t",s_cus._ADDR	);
			printf("%s\t",s_cus._AGE	);
			printf("%s\n",s_cus._GnID	);
			#endif
		}
	}
	fclose(file);
	fclose(file2);
	fhm(&s_cus);
	s_cus._BID	=NULL;
	s_cus._N	=NULL;	
	s_cus._P	=NULL;	
	s_cus._S	=NULL;	
	s_cus._BAL	=NULL;
	s_cus._nID	=NULL;
	s_cus._ADDR	=NULL;
	s_cus._AGE	=NULL;
	s_cus._GnID	=NULL;
	remove(DBFILENAME);
	rename("new.txt",DBFILENAME);
	return ;

}

static void cpytofile(FILE * file2 ,cus_t * s_cus)
{
	fprintf(file2,s_cus->_BID		)   ;
	fprintf(file2,"\t")            		;
	fprintf(file2,s_cus->_N[0]		)   ;
	fprintf(file2,"\t")            		;
	fprintf(file2,s_cus->_N[1]		)   ;
	fprintf(file2,"\t")            		;
	fprintf(file2,s_cus->_N[2]		)   ;
	fprintf(file2,"\t")            		;
	fprintf(file2,s_cus->_N[3]		)   ;
	fprintf(file2,"\t")            		;
	fprintf(file2,s_cus->_P			)   ;
	fprintf(file2,"\t")            		;
	fprintf(file2,s_cus->_S			)   ;
	fprintf(file2,"\t")            		;
	fprintf(file2,s_cus->_BAL		)   ;
	fprintf(file2,"\t")            		;
	fprintf(file2,s_cus->_nID		)   ;
	fprintf(file2,"\t")            		;
	fprintf(file2,s_cus->_ADDR		)   ;
	fprintf(file2,"\t")            		;
	fprintf(file2,s_cus->_AGE		)   ;
	fprintf(file2,"\t")            		;
	fprintf(file2,s_cus->_GnID		)   ;
	fprintf(file2,"\n")            		;
	
}

