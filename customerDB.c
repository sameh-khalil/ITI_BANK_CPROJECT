
#include <stdio.h>
#include <stdlib.h>
#include "STD_TYPES.h"
#include "cusDB.h"
#define DBFILENAME "./cusDB.txt"
static void rhm(cus_t * s_cus);
static void cpytofile(FILE * file2 ,cus_t * s_cus);



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

