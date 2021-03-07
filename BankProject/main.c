#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

char *bank0 = "ISTANBUL BANK";
char *bank1 = "NEW YORK BANK";
char *bank2 = "SWISS BANK";
char *bank_name[3];
FILE *new_acc;
FILE *sign_details;
FILE *money;

void start();
void new_account();
void acc_view();
void transac();
void stay_or_left();
void sign_in();
void delete_pointers();

int main()
{
    printf("************HELLO, PLEASE CHOOSE YOUR BANK************\n");
    printf("  <<ISTANBUL BANK>>  <<NEW YORK BANK>>  <<SWISS BANK>>\n");
    printf("      -Press 1-          -Press 2-        -Press 3-\n>>");
    int Bank_number;
    scanf(" %d", &Bank_number);

    switch (Bank_number)
    {
        case 1:
            bank_name[0] = bank0;
            printf("%s  -  You Live. We'll Take Care of the Details\n", bank_name[0]);
            break;
        case 2:
            bank_name[1] = bank1;
            printf("%s  -  Banking in Your Best Interest\n ", bank_name[1]);
            break;
        case 3:
            bank_name[2] = bank2;
            printf("%s  -  The Company to Remember for Life\n", bank_name[2]);
        default:
            break;
    }

    start();
    
    return 0;
}

void start()
{
    printf("************WELCOME TO THE MAIN MENU************\n\n");
    printf("1 >> Sign In\n2 >> Create a New Account\n3 >> Exit\nEnter Your Choice >>");

    int choice, choice2 ;
    scanf("%d", &choice);

    switch (choice)
    {
        case 1:
            sign_in();
            printf("1 >> View the details of an Existing Account\n2 >> Account Transactions\n>> ");
            scanf("%d", &choice2);
            printf("\n");
            switch (choice2)
            {
            	case 1:
            		acc_view();
            		break;
            	case 2:
					transac();
					break;
				default:
					break;
			}
            break;
        case 2:
            new_account();
            break;
        case 3:
			printf("See You %c", 1);
			delete_pointers();
			exit(0);  
        default:
            break;
    }

}

void new_account()
{
    char name[50];
    char password[50];
    char c;
    int index = 0;
    int id;
	int money_acc = 0;
	
    new_acc = fopen("bank_acc.txt","w");
    sign_details = fopen("sign_in.txt", "w");
    money = fopen("money.txt", "w");

    printf("Enter Your Name and Surname : ");
    scanf(" %[^\n]", name);
    fprintf(new_acc,"Card Owners Name : %s\n", name);
    
    printf("Enter Your ID Number : ");
    scanf("%d", &id);
	fprintf(sign_details,"%d\n", id);

    printf("Enter Your Password : ");

    while((c = getch()) != 13)
    {
        if(index<0)
            index = 0;

        if(c == 8)
        {
            putch('\b');
            putch(NULL);
            putch('\b');
            index-- ;
            continue;
        }
        password[index++] = c;
        putch('*');
    }
    password[index] = '\0';
    printf("\n");

    int card_number[16];
    srand(time(0));

    fprintf(new_acc,"Card Number : ");

    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n%c",201,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,187,186);
    int j;
    int i;
	for (j = 0; j < 4; j++)
    {
        for(i = 0; i < 4; i++)
        {
            card_number[i]= ((rand()  %9) +0) ;
            printf("%d", card_number[i]);
            fprintf(new_acc,"%d", card_number[i]);
        }
        printf(" ");
        fprintf(new_acc," ");
    }
    printf("%c",186);

    int cvv[3];
    printf("\n%cCVV:",186);
    fprintf(new_acc,"\nCVV:");
    for (i = 0; i < 3; i++)
    {
        cvv[i] = ((rand()  %9) +0);
        printf("%d", cvv[i]);
        fprintf(new_acc,"%d", cvv[i]);
    }
    printf("\t     %c\n", 186);

    printf("%c%s\n", 186, name);
    printf("%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c%c\n",200,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,205,188);
	
	printf("ID NUMBER : %d\n", id);
    fprintf(new_acc,"\n%s's ID Number is : %d", name, id);

    printf("Your Password : %s\n\n", password);
    fprintf(new_acc,"\n%s's Password is : %s\n", name, password);
    fprintf(sign_details,"%s", password);
	
	printf("Amount of Money : %d\n\n", money_acc);    
    fprintf(money,"%d\n", money_acc);

    fclose(new_acc);
    fclose(sign_details);
    fclose(money);

    stay_or_left();

}

void acc_view()
{
	
    new_acc = fopen("bank_acc.txt", "r");
    money = fopen("money.txt", "r");
    
    int money_acc;
    int id;
    char details[5000];
    if(new_acc == NULL || money == NULL)
    {
        printf("Please Create an Account!!\n\a");
        start();
    }

    while(fgets(details, sizeof(details), new_acc))
    printf("%s\n", details);

	fscanf(money,"%d", &money_acc);
	printf("Amount of Money = %d\n\n", money_acc);
	
    fclose(new_acc);
    fclose(money);
    
    stay_or_left();
}

void transac()
{
	money = fopen("money.txt", "r");
	
	int money_acc;
	fscanf(money," %d ", &money_acc);
	fclose(money);
	
	printf("Money in the account : %d\n", money_acc);
	
	int choose, how_much;
	printf("Choose a banking operation\n\n1 >> Deposit Money\n2 >> Withdraw Money\n>> ");
	scanf("%d", &choose);
	
	switch(choose)
	{
		case 1:
			printf("Enter an amount of money >> ");
			scanf("%d", &how_much);
			money_acc += how_much;
			break;
		case 2:
			printf("Enter an amount of money >> ");
			scanf("%d", &how_much);
			money_acc -= how_much;
			break;
		default:
			break;
	}
	
	if(money_acc < 0)
	{
		printf("You haven't got enough money\n");
		money_acc += how_much;
	}
	
	money = fopen("money.txt", "w");
	
	printf("Your Money is now = %d\n", money_acc);
	fprintf(money,"%d", money_acc);
	
	fclose(money);
	stay_or_left();
}

void sign_in()
{
	char c, password[50];
	char spassword[50];
	int sid;
	int id, index = 0;
	printf("Enter Your ID NUMBER >> ");
	scanf("%d", &id);
	printf("Enter Your Password >> ");
	
	while((c = getch()) != 13)
    {
        if(index<0)
            index = 0;

        if(c == 8)
        {
            putch('\b');
            putch(NULL);
            putch('\b');
            index-- ;
            continue;
        }
        password[index++] = c;
        putch('*');
    }
    password[index] = '\0';
    printf("\n");
	
	sign_details = fopen("sign_in.txt", "r");
	
	fscanf(sign_details,"%d", &sid);
	
	int line_p = 0;
	while(fgets(spassword,sizeof(spassword),sign_details))
	{
		line_p++;
		
		if(line_p == 2)
		printf(" ");
	}	
	
	int compare;
	compare = strcmp(spassword, password);
	
	if(sid == id && compare == 0)
	{
		printf("\n");
	}
	
	else if(sid != id || compare != 0)
	{
		int choose;
		printf("Wrong ID or Password!!\n\n1 >> Try Again\n2 >> Create an Account\n3 >> Main Menu\n>> ");
		scanf("%d", &choose);
		
		switch(choose)
		{
			case 1:
				sign_in();
				break;
			case 2:
				new_account();
				break;
			case 3:
				start();
				break;
			default:
				break;					
		}	
	}
		
	fclose(sign_details);
}

void stay_or_left()
{
    printf("1 >> Return to Main Menu\n2 >> Exit\n");
    int re;
    scanf("%d", &re);
    switch (re)
    {
        case 1:
            start();
            break;
        case 2:
            printf("See You %c", 1);
            delete_pointers();
            exit(0);
        default:
            break;
    }
}

void delete_pointers()
{
	free (bank0);
	free (bank1);
	free (bank2);
	free (bank_name[0]);
	free (bank_name[1]);
	free (bank_name[2]);
	free (new_acc);
	free (sign_details);
	free (money);
}

