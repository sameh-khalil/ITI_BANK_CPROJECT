
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "empDB.h"
#include "cusDB.h"
int ADMINCHECK(void);
u8 GetOptions (void);
cus_t cusCHECK (void);
void printCusInfo (cus_t * s_cus);
s8 SetAccUserName (cus_t * s_cus);
s8 SetNationalID (cus_t * s_cus);
s8 SetUserAddress (cus_t * s_cus);
char * concat(char ** x, u8 size);
s8 SetAccBalance (cus_t * s_cus);
s8 SetUserAge (cus_t * s_cus);
s8 SetAccState (cus_t * s_cus , u8 op);
s8 SetGARDIANNationalID (cus_t * s_cus);
void CreatAcc (void);
u8 GetexistingaccOptions (void);
u8 trransop (cus_t * s_cus);
u8 deposit (cus_t * s_cus);
void openexistingaccount (void);
u8 Getuser_adminOptions (void);
u8 getmony (cus_t * s_cus);
u8 checkstatus (cus_t * s_cus);
u8 GetuserOptions (void);
u8 changePass (cus_t * s_cus);
void RandomPass (cus_t * s_cus);




int main (int argc , char * argv[])
{
	u8 adminflag=0;
	u8 options = 0;
	s8 flag = 0 ;	
	while (1)
	{
		u8 user_admin = 0 ;
		do{user_admin=Getuser_adminOptions();}while(user_admin==0);
		if(user_admin==1)
		{
			/* if employee is chosen then he need to enter user name and password */
			u8 adminflag 	= ADMINCHECK();
			while(adminflag == 1)
			{
				do{options = GetOptions ();}while(options<1);
				if(options==1)
				{
					CreatAcc();
					options = 0 ;
				}
				else if(options==2)
				{
					openexistingaccount ();
					options = 0 ;
				}
				else if(options==3)
				{
					adminflag=0;
					options = 0 ;
				}
	
				
			}
		}
		else
		{
			cus_t s_cus={NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,100,1} ; 
			char q;
			u8 userflag = 0 ;
			do{
				s_cus=cusCHECK ();
				if(s_cus.state!=0)
				{	printf("again / exit?  1 / 2 \n");
					scanf("\n");
					scanf("%c",&q);
					if(q == '1' )
					{}
					else
					{break;}
				}
				}while(s_cus.state!=0);
			if(checkstatus (&s_cus)==0)
			{printf("accpont not active \n");continue;}
			userflag = 1 ;
			while(userflag ==1 )
			{
					u8 useropflag = 0 ;
					do{useropflag=GetuserOptions ();}while(useropflag==0);
					if(useropflag==3)
					{userflag=0; break;}
					else if (useropflag==1)
					{
						getmony (&s_cus);
					}
					else if (useropflag==2)
					{
						printCusInfo (&s_cus);
					}
					else if (useropflag==4)
					{
						deposit (&s_cus);
					}
					else if (useropflag==5)
					{
						changePass (&s_cus);
					}
					else if (useropflag==6)
					{
						trransop (&s_cus);
					}
			}
			
			
			
		}

	}
	
	
	
}


/*ask for user name and password 
-search if the username and password is correct in the database
 I need to handel the data base*/

int ADMINCHECK ()
{

		char name [30];
		char password [30];
		printf("pls enter username \n");
		scanf("%s",name);
		printf("pls enter password \n");
		scanf("%s",password);
		emp_t s_emp =empsearch(name,password);
		if(s_emp._n==NULL)
		{printf("error\n");return -1;}
		else
		{printf("welc %s\n",s_emp._n);return 1;}
		
}


cus_t cusCHECK ()
{
	char ** name = (char **)malloc(4*sizeof(char*));
	name[0] = (char *)malloc(15*sizeof(char));
	name[1] = (char *)malloc(15*sizeof(char));
	name[2] = (char *)malloc(15*sizeof(char));
	name[3] = (char *)malloc(15*sizeof(char));
	char password [30];
	printf("pls enter username \n");
	scanf("%s",name[0]);
	scanf("%s",name[1]);
	scanf("%s",name[2]);
	scanf("%s",name[3]);
	printf("pls enter password \n");
	scanf("%s",password);
	cus_t s_cus =cussearch(name,password);

	if(s_cus.state==2)
	{

		fhm(&s_cus);
		printf("no such name\n");
		free(name[0] );
		free(name[1] );
		free(name[2] );
		free(name[3] );
		free(name);
		return s_cus;}
		
	else if(s_cus.state==1)
	{
		fhm(&s_cus);
		printf("wrong Password\n");
		free(name[0] );
		free(name[1] );
		free(name[2] );
		free(name[3] );
		free(name);
		return s_cus;
	}
	else
	{
		free(name[0] );
		free(name[1] );
		free(name[2] );
		free(name[3] );
		free(name);
		return s_cus;
	}
}





void printCusInfo (cus_t * s_cus)
{
	printf("Bank ID\t: %s\n",s_cus->_BID	);
	printf("NAME\t: %s %s %s %s \n",s_cus->_N[0],s_cus->_N[1],s_cus->_N[2],s_cus->_N[3]		);
	printf(": %s\n",s_cus->_P		);
	printf("STATUS\t: %s\n",s_cus->_S		);
	printf("BALANCE\t: %s\n",s_cus->_BAL	);
	printf("national id: %s\n",s_cus->_nID	);
	printf("address: %s\n",s_cus->_ADDR	);
	printf("Age\t: %s\n",s_cus->_AGE	);
	printf("gid\t: %s\n",s_cus->_GnID	);
}





//show a list of options return user option 
u8 GetOptions ()
{
		char op [5];
		printf("pls enter the process \n");
		printf("1 : Creat New Account\n2 : Open Existing Accont\n3 : Exit\n");
		printf("your option is : \n");
		scanf("\n");
		scanf("%5s",op);
		if(op[0]=='1')
		{return 1 ;}
		else if(op[0]=='2')
		{return 2 ;}
		else if(op[0]=='3')
		{return 3 ;}
		else{printf("\nwrong op\n");return 0;}

		

	
}



s8 SetAccUserName (cus_t * s_cus)
{
	char ** fullname = (char**)malloc(4*sizeof(char*));
	fullname[0] = (char*)malloc(15*sizeof(char));
	fullname[1] = (char*)malloc(15*sizeof(char));
	fullname[2] = (char*)malloc(15*sizeof(char));
	fullname[3] = (char*)malloc(15*sizeof(char));
	printf("enter the username in the following format \"1st 2nd 3d 4th\" :\n");
	scanf("%s",fullname[0]);
	scanf("%s",fullname[1]);
	scanf("%s",fullname[2]);
	scanf("%s",fullname[3]);
	for(int i = 0 ; i < 4 ; i++)
	{
		if(strlen(fullname[i])<=1)
		{
			free(fullname[0] );
			free(fullname[1] );
			free(fullname[2] );
			free(fullname[3] );
			free(fullname);
			
			printf("too short\n");
			return -1;
		}
		if (strlen(fullname[i])>=15)
		{
			free(fullname[0] );
			free(fullname[1] );
			free(fullname[2] );
			free(fullname[3] );
			free(fullname);

			printf("too long\n");
			return -1 ;
		}
		u8 j = 0 ;
		while(fullname[i][j]!='\0')
		{
			if(!((fullname[i][j]>='a'&&fullname[i][j]<='z')||(fullname[i][j]>='A'&&fullname[i][j]<='Z')))
			{
				printf("cant accept any nums or sympols \n");
				free(fullname[0] );
				free(fullname[1] );
				free(fullname[2] );
				free(fullname[3] );
				free(fullname);

				return-1;
			}
			j++;
		}
	}

	s_cus->_N=fullname;
	
	return 1 ;
}




s8 SetNationalID (cus_t * s_cus)
{
	char * NID_ = (char*)malloc(14*sizeof(char));

	printf("enter the national your Id :\n");
	scanf("%s",NID_);


	if(strlen(NID_)!=14)
	{
		free(NID_);
		printf("wrong Id\n");
		return -1;
	}
	u8 j = 0 ;
	while(NID_[j]!='\0')
	{
		if(NID_[j]>'9'||NID_[j]<'0')
		{
			free(NID_);
			printf("cant accept any but nums\n");
			return-1;
		}
		j++;
	}


	s_cus->_nID=NID_;

	return 1 ;
}





s8 SetUserAddress (cus_t * s_cus)
{
	char ** address = (char**)malloc(6*sizeof(char*));
	address[0] = (char*)malloc(15*sizeof(char));
	address[1] = (char*)malloc(15*sizeof(char));
	address[2] = (char*)malloc(15*sizeof(char));
	address[3] = (char*)malloc(15*sizeof(char));
	address[4] = (char*)malloc(15*sizeof(char));
	address[5] = (char*)malloc(15*sizeof(char));
	printf("enter the address in the following format \"country governorate city  streat building appartment\" :\n");
	scanf("%s",address[0]);
	scanf("%s",address[1]);
	scanf("%s",address[2]);
	scanf("%s",address[3]);
	scanf("%s",address[4]);
	scanf("%s",address[5]);
	
	for(int i = 0 ; i < 6 ; i++)
	{
		if(strlen(address[i])<=1	&&!((address[i][0]>='0')&&(address[i][0]<='9')))
		{
			free(address[0]  );
			free(address[1]  );
			free(address[2]  );
			free(address[3]  );
			free(address[4]  );
			free(address[5]  );
			free(address);
			
			printf("too short\n");
			return -1;
		}
		if (strlen(address[i])>=15)
		{
			free(address[0]  );
			free(address[1]  );
			free(address[2]  );
			free(address[3]  );
			free(address[4]  );
			free(address[5]  );
			free(address);

			printf("too long\n");
			return -1 ;
		}

	}
	
	

	s_cus->_ADDR=concat(address,6);
	free(address[0]  );
	free(address[1]  );
	free(address[2]  );
	free(address[3]  );
	free(address[4]  );
	free(address[5]  );
	free(address);
	
	return 1 ;
}

char * concat(char ** x, u8 size)
{
		u8 numofbytes  = 0 ; 
		for(int i=0 ; i  < size ; i ++)
		{
			numofbytes+=strlen(x[i]);
			numofbytes++;
			
		}
		char * g  = (char *)malloc(numofbytes * sizeof(char));
		int k = 0;
		int j = 0 ;

		for (int i = 0 ; i<size ; i++)
		{
			j = 0 ;
			while(x[i][j]!='\0')
			{
				g[k]=x[i][j];
				k++;
				j++;
			}
			g[k]='/';
			k++;	
			
		}
		g[k-1]='\0';
		
		
		return g ;
}




s8 SetAccBalance (cus_t * s_cus)
{
	char * BALANCE_ = (char*)malloc(16*sizeof(char));

	printf("enter the balance :\n");
	scanf("%s",BALANCE_);


	if(strlen(BALANCE_)>16)
	{
		free(BALANCE_);
		printf("un realistic\n");
		return -1;
	}
	u8 j = 0 ;
	while(BALANCE_[j]!='\0')
	{
		if(BALANCE_[j]>'9'||BALANCE_[j]<'0')
		{
			free(BALANCE_);
			printf("cant accept any but nums \n");
			return-1;
		}
		j++;
	}
	
	s_cus->_BAL=BALANCE_;
	return 1 ;
}



s8 SetUserAge (cus_t * s_cus)
{
	char * AGE_ = (char*)malloc(4*sizeof(char));
	printf("enter the Age :\n");
	scanf("%s",AGE_);


	if(strlen(AGE_)>4)
	{
		free(AGE_);
		printf("un realistic\n");
		return -1;
	}
	u8 j = 0 ;
	while(AGE_[j]!='\0')
	{
		if(AGE_[j]>'9'||AGE_[j]<'0')
		{
			free(AGE_);
			printf("cant accept any but nums \n");
			return-1;
		}
		j++;
	}
	
	s_cus->_AGE=AGE_;
	return 1 ;
}



s8 SetAccState (cus_t * s_cus , u8 op)
{
	if(op == 1 )
	{	
		s_cus->_S =(char*)malloc(15*sizeof(char));
		strcpy(s_cus->_S,"Active");
	}
	else
	{
		int state;
		printf("enter the state :: 1: active account / 2: restricted Account /3: closed Account:\n");
		scanf("\n");
		scanf("%d",&state);

		if (state==1)
		{	
			s_cus->_S =(char*)malloc(15*sizeof(char));
			strcpy(s_cus->_S,"Active");
			printf("%s\n",s_cus->_S);
		}
		else if (state==2)
		{
			s_cus->_S =(char*)malloc(15*sizeof(char));
			strcpy(s_cus->_S,"restricted");
		}
		else if (state==3)
		{
			s_cus->_S =(char*)malloc(15*sizeof(char));
			strcpy(s_cus->_S,"closed");
		}
		else
		{
			printf("wrong input\n");
			return -1 ;
		}
		
	}	
	
	return 1;	
}


s8 SetGARDIANNationalID (cus_t * s_cus)
{
	char * GID_ = (char*)malloc(14*sizeof(char));
	u32 age = strtoint(s_cus->_AGE);
	if(age<21)
	{

		printf("enter the national your Id :\n");
		scanf("%s",GID_);


		if(strlen(GID_)!=14)
		{
			free(GID_);
			printf("wrong Id\n");
			return -1;
		}
		u8 j = 0 ;
		while(GID_[j]!='\0')
		{
			if(GID_[j]>'9'||GID_[j]<'0')
			{
				free(GID_);
				printf("cant accept any but nums\n");
				return-1;
			}
			j++;
		}
	

		s_cus->_GnID=GID_;
	}
	else{
		s_cus->_GnID=(char*)malloc(15*sizeof(char));
		strcpy(s_cus->_GnID,"00000000000000");}

	return 1 ;
}



void CreatAcc ()
{
	cus_t s_cus={NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,100,1};s8 flag = 0 ;
	do{flag=SetAccUserName(&s_cus);}while(flag<1);
	flag = 0 ;
	do{flag=SetAccBalance(&s_cus);}while(flag<1);
	flag = 0 ;
	do{flag=SetNationalID(&s_cus);}while(flag<1);
	flag = 0 ;
	do{flag=SetUserAddress(&s_cus);}while(flag<1);
	flag = 0 ;
	do{flag=SetUserAge(&s_cus);}while(flag<1);
	flag = 0 ;
	do{flag=SetAccState(&s_cus,1);}while(flag<1);	
	flag = 0 ;
	do{flag=SetGARDIANNationalID(&s_cus);}while(flag<1);
	s_cus._P = (char*)malloc(10 * sizeof(char)) ;
	RandomPass(&s_cus);
	GETBID(&s_cus);
	printCusInfo(&s_cus);
	char ans ;
	do{printf("creat the new acc?  y / n \n");scanf("\n");scanf("%c",&ans);}while(ans!='y'&&ans!='n');
	if(ans=='y')
	{insertcusAtend(&s_cus);fhm(&s_cus);}
	else if(ans=='n')
	{fhm(&s_cus);}
		
}




void openexistingaccount ()
{
	
	u8 flag = 0 ;
	
	char ans = '1' ;
	cus_t s_cus={NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,100,1};
	do
	{
		s_cus = cusCHECK ();
		if(s_cus.state!=0)
		{
			flag = 0;
			printf("again / exit?  1 / 2 \n");
			scanf("\n");
			scanf("%c",&ans);
			if(ans == '1' )
			{flag = 0 ;}
			else
			{return;}
		
		
		}
		else
		{flag = 1 ;}
	}while(flag==0);
	
	
	printCusInfo(&s_cus);
	
	flag=0;
	do
	{
		flag=GetexistingaccOptions();
		if(flag==7)
		{
			fhm(&s_cus);
			printf("quit \n");
			return;
		}
	}while(flag==0);
	
	if(flag==1)
	{
		if(checkstatus (&s_cus)==0)
		{printf("accpont not active \n");}
		else
		{	trransop (&s_cus);
			fhm(&s_cus);
			return;
		}
	}
	
	
	else if (flag==2)
	{SetAccState(&s_cus,0); return;}


	else if (flag==3)
	{
		if(checkstatus (&s_cus)==0)
		{printf("accpont not active \n");}
		else
		{deposit(&s_cus);return;}
	}
	else if (flag==5)
	{
		if(checkstatus (&s_cus)==0)
		{printf("accpont not active \n");}
		else
		{getmony (&s_cus);return;}
	}


	
}


u8 trransop (cus_t * s_cus)
{
		cus_t s_2ndcus={NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,100,1};
		char * toACC =(char *) malloc(14*sizeof(char));
		do
		{
			printf("please enter the account id to tras to \n");
			scanf("%s",toACC);
			if(toACC[0]=='q')
			{
				fhm(s_cus);
				fhm(&s_2ndcus);
				printf("quit \n");
				return 0;
			}
			
			s_2ndcus=getcusbyBID(toACC);
		}while(s_2ndcus.state==1);
		
		free(toACC);
		u8 j ;
		u8 t =0;
		u32 trans=0 ;
		u32 bal =0;
		do
		{
			t=1;
			printf("please enter the amount u want to tras \n");
			toACC =(char *) malloc(15*sizeof(char));
			scanf("%s",toACC);
			if(toACC[0]=='q')
			{
				fhm(s_cus);
				fhm(&s_2ndcus);				
				printf("quit \n");
				return 0;
			
			
			}
			if(strlen(toACC)>14)
			{
				free(toACC);
				printf("un realistic\n");
				t=0;
			}
			j = 0 ;
			while(toACC[j]!='\0'&&t != 0)
			{
				if(toACC[j]>'9'||toACC[j]<'0')
				{
					free(toACC);
					printf("cant accept any but nums \n");
					t = 0 ;
					break;
				}
				j++;
			}
			u32 trans =strtoint(toACC);
			free(toACC);
			u32 bal =strtoint(s_cus->_BAL);
			u32 bal2 =strtoint(s_2ndcus._BAL);
			if(trans>bal && t!=0 )
			{
				printf("cant do trans u dont have enough in your acc \n");
				t=0;
			}
			else
			{
				bal-=trans;
				bal2+=trans;
				free(s_cus->_BAL);
				
				s_cus->_BAL=inttostr(bal);
				s_2ndcus._BAL=inttostr(bal2);
				
				insertEditedcus(s_cus);
				insertEditedcus(&s_2ndcus);
				
				fhm(s_cus);
				fhm(&s_2ndcus);
				t=1;
			}
		}while(t==0);
	return 1;
}






u8 GetexistingaccOptions ()
{
	char ans = '0';
	printf("choose the operation 1: transaction 	2: change account status	3:deposit 	4: return   5: get cash \n");
	scanf("\n");
	scanf("%c",&ans);
	if(ans=='1')
	{return 1 ;}
	else if(ans=='2')
	{return 2 ;}
	else if(ans=='3')
	{return 3 ;}
	else if(ans=='4')
	{return 4 ;}
	else if(ans=='5')
	{return 5 ;}
	
	else if (ans == 'q')
	{return 7 ;}
	else{printf("\nwrong op\n");return 0;}

		

	
}


u8 deposit (cus_t * s_cus)
{
	char * BALANCE_ = (char*)malloc(16*sizeof(char));
		u8 f=1;
	do
	{
		f =1;
		printf("enter the amount u want to deposit :\n");
		scanf("%s",BALANCE_);
		if(strlen(BALANCE_)>16)
		{
			free(BALANCE_);
			printf("un realistic\n");
			f=0;
		}
		u8 j = 0 ;
		while(BALANCE_[j]!='\0')
		{
			if(BALANCE_[j]>'9'||BALANCE_[j]<'0')
			{
				free(BALANCE_);
				printf("cant accept any but nums \n");
				f=0;
				break;
			}
			j++;
		}
		
	}while(BALANCE_[0]!='q'&&f==0);
	if(BALANCE_[0]=='q')
	{free(BALANCE_);return 0;}
	
	u32 trans =strtoint(BALANCE_);
	free(BALANCE_);
	u32 bal =strtoint(s_cus->_BAL);
	bal += trans ;
	s_cus->_BAL=inttostr(bal);
	insertEditedcus(s_cus);
	return 1 ;
}


u8 Getuser_adminOptions ()
{
		char op [5];
		printf("admin 1 : customer 2 \n");
		printf("your option is : \n");
		scanf("\n");
		scanf("%5s",op);
		if(op[0]=='1')
		{return 1 ;}
		else if(op[0]=='2')
		{return 2 ;}
		else{printf("\nwrong op\n");return 0;}

		

	
}

u8 GetuserOptions ()
{
		char op [5];
		printf("getcash 1 : getaccount info 2 :quit 3  :deposit 4 : change password 5 :transaction 6\n");
		printf("your option is : \n");
		scanf("\n");
		scanf("%5s",op);
		if(op[0]=='1')
		{return 1 ;}
		else if(op[0]=='2')
		{return 2 ;}
		else if(op[0]=='3')
		{return 3 ;}
		else if(op[0]=='4')
		{return 4 ;}
		else if(op[0]=='5')
		{return 5 ;}
		else if(op[0]=='6')
		{return 6 ;}
		else{printf("\nwrong op\n");return 0;}

		

	
}




u8 getmony (cus_t * s_cus)
{

	char * BALANCE_ = (char*)malloc(16*sizeof(char));
		u8 f=1;
		u32 trans;
		u32 bal ;
	do
	{
		f =1;
		printf("enter the amount u want to deposit :\n");
		scanf("%s",BALANCE_);
		if(strlen(BALANCE_)>16)
		{
			free(BALANCE_);
			printf("un realistic\n");
			f=0;
		}
		if(BALANCE_[0]=='q'){free(BALANCE_);return 0 ;}
		u8 j = 0 ;
		while(BALANCE_[j]!='\0')
		{
			if(BALANCE_[j]>'9'||BALANCE_[j]<'0')
			{
				free(BALANCE_);
				printf("cant accept any but nums \n");
				f=0;
				break;
			}
			j++;
		}
		if (f==1)
		{
			trans =strtoint(BALANCE_);
			free(BALANCE_);
			bal =strtoint(s_cus->_BAL);
			if(bal<trans)
			{
				printf("cant get more than ur balance \n");
				f=0;
			}

		}
		
	}while(f==0);
	

	bal -= trans ;
	s_cus->_BAL=inttostr(bal);
	insertEditedcus(s_cus);
	return 1 ;
}





u8 checkstatus (cus_t * s_cus)
{
	if(strcmp(s_cus->_S,"Active")==0)
	{return 1;}
	else
	{return 0;}
}

u8 changePass (cus_t * s_cus)
{
	
	
	
	char * newpass1 = (char*)malloc(15*sizeof(char));
	char * newpass2 = (char*)malloc(15*sizeof(char));
	scanf("%12s",newpass1);
	printf("enter the newPASS :\n");
	printf("enter the newPASS again :\n");
	scanf("%12s",newpass2);
	if(strcmp(newpass1,newpass2)==0)
	{
		s_cus->_P=newpass1;
		free(newpass2);
		insertEditedcus(s_cus);
		return 1 ;}
	else
	{
		free(newpass1);
		free(newpass2);
		printf("invalid: 2 passes dont match \n");
		return 0;

	}

}


void RandomPass (cus_t * s_cus)
{
	u32 pass = 0 ;
	while(pass<1000)
	{pass=rand();}
	s_cus->_P = inttostr(pass);
}