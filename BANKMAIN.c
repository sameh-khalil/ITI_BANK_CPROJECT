
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "empDB.h"


int main (int argc , char * argv[])
{
		emp_DB_t DB_ = DB_INIT ();
		char name [30];
		char password [30];
		printf("pls enter username \n");
		scanf("%s",name);
		printf("pls enter password \n");
		scanf("%s",password);
		int thereis = empsearch(&DB_,name,password);
		if(thereis==1)
		{printf("welcome %s \n",name);}
		else if (thereis==-1)
		{printf("wrong username \n");}
		else if (thereis==-2)
		{printf("wrong password \n");}
	

	#if 0
	while (1)
	{
			/* if employee is chosen then he need to enter user name and password */
			/*search if the username and password is correct in the database we need to handel the data base*/
			//show a list of options 
				//option 1 creat new account 
					//-ask for full name --check its at least first 4 names (else ask him again )
					//-ask 4 full address 
					//-ask 4 age 
					//ask 4 national id check for 14 digit(else ask him again)
					//-if age < 21 -ask 4 gaurdian national id check for 14 digit(else ask him again)
					//-ask for balance
					//send the new account information and default password 
					//name address nID age bankid accountstatus balance (if age <21)gaurdian nationalid
				
				//option 2 open existing account 
					//showlist of options 
						//1- transaction --bankid
						//2-change account status --bankid
						//3-deposit
						//return to employee options
				
				//option 3 exit
		
		
		
	}
	
	#endif
	
	
	
}



