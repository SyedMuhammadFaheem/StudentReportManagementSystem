#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <process.h>
#include "pbPlots.c"
#include "supportLib.c"
#define ENTER 13 
#define BACKSPACE 8
#define NOGDICAPMASKS     // CC_*, LC_*, PC_*, CP_*, TC_*, RC_
#define NOVIRTUALKEYCODES // VK_*
#define NOWINMESSAGES     // WM_*, EM_*, LB_*, CB_*
#define NOWINSTYLES       // WS_*, CS_*, ES_*, LBS_*, SBS_*, CBS_*
#define NOSYSMETRICS      // SM_*
#define NOMENUS           // MF_*
#define NOICONS           // IDI_*
#define NOKEYSTATES       // MK_*
#define NOSYSCOMMANDS     // SC_*
#define NORASTEROPS       // Binary and Tertiary raster ops
#define NOSHOWWINDOW      // SW_*
#define OEMRESOURCE       // OEM Resource values
#define NOATOM            // Atom Manager routines
#define NOCLIPBOARD       // Clipboard routines
#define NOCOLOR           // Screen colors
#define NOCTLMGR          // Control and Dialog routines
#define NODRAWTEXT        // DrawText() and DT_*
#define NOGDI             // All GDI defines and routines
#define NOKERNEL          // All KERNEL defines and routines
#define NOUSER            // All USER defines and routines
/*#define NONLS             // All NLS defines and routines*/
#define NOMB              // MB_* and MessageBox()
#define NOMEMMGR          // GMEM_*, LMEM_*, GHND, LHND, associated routines
#define NOMETAFILE        // typedef METAFILEPICT
#define NOMINMAX          // Macros min(a,b) and max(a,b)
#define NOMSG             // typedef MSG and associated routines
#define NOOPENFILE        // OpenFile(), OemToAnsi, AnsiToOem, and OF_*
#define NOSCROLL          // SB_* and scrolling routines
#define NOSERVICE         // All Service Controller routines, SERVICE_ equates, etc.
#define NOSOUND           // Sound driver routines
#define NOTEXTMETRIC      // typedef TEXTMETRIC and associated routines
#define NOWH              // SetWindowsHook and WH_*
#define NOWINOFFSETS      // GWL_*, GCL_*, associated routines
#define NOCOMM            // COMM driver routines
#define NOKANJI           // Kanji support stuff.
#define NOHELP            // Help engine interface.
#define NOPROFILER        // Profiler interface.
#define NODEFERWINDOWPOS  // DeferWindowPos routines
#define NOMCX             // Modem Configuration Extensions


/* Type required before windows.h inclusion  */
typedef struct tagMSG *LPMSG;

#include <windows.h>

int bk;
int max=-99;

struct Academics
{
	double quiz;
	double midterm;
	double final;
	double attendance;
};

struct Involvement
{
	int screenTime;
	int replays;
	
}involvement[10];

struct Remarks
{
	int date[3];
	char comment[200];	
};

struct student
{
	char name[20];
	int id;
	char pass[20];
	struct Academics study[1];
	struct Involvement involve[1];
	struct Remarks remarks[10];

};

//Declarations Of Functions
void DisplayStudentList(struct student std[], int n);
void changingScreens(struct student *std,int *n);
void AddStudent(struct student *stdPtr,int *n);
void EditMode(struct student std[],int *n);
void RecordMode(struct student std[],int *n);
void academicScreen(struct student *stdPtr, int *n,int pos);
void DisplayAcademic(struct student *stdPtr, int *n,int pos);
void editAcademic(struct student *stdPtr, int *n, int i, int pos);
void AcademicModeHeading(struct student *stdPtr,int *n);
void involveScreen(struct student *stdPtr, int *n, int pos);
void DisplayInvolve(struct student *stdPtr, int *n, int pos);
void editInvolve(struct student *stdPtr, int *n, int i,int pos);
void InvolveModeHeading(struct student *stdPtr,int *n);
void remarkScreen(struct student *stdPtr, int *n, int pos);
void DisplayRemark(struct student *stdPtr, int *n, int pos);
void editRemark(struct student *stdPtr, int *n, int i,int pos);
void RemarkModeHeading(struct student *stdPtr,int *n);


void Graph(double x1,double x2,double x3);

void read(FILE *ptr,struct student std[],int n);
void recdelete(struct student std[],int del,int n);
void editid(struct student std[],int id,char chngname[20],int n);
void add(char name[20],int id,char pass[20]);
void totalStudents(int n);
void displayiddata(struct student std[],int id,int n);


void editQuiz(struct student std[],int id,double quiz,int n);
void editMid(struct student std[],int id,double mid,int n);
void editFinal(struct student std[],int id,double final,int n);
void editAttendance(struct student std[],int id,double attend,int n);
void editScreen(struct student std[],int id,int screen,int n);
void editReplay(struct student std[],int id,int replay,int n);


//--------------------------------------------------Mohsin Code---------------------------------------------------------
void DisplayStudentList(struct student std[], int n)
{
	int space,i;
	
	//Headings
	printf("\n\n\n\n\n\t\t\t\t*******************\n\n");
	printf("\t\t\t\t    STUDENT LIST\n\n");
	printf("\n\t\t\t\t*******************\n\n");
	printf("\t\t  -------------------------------------------------\n");
	printf("\t\t  |S.NO|\t  Name       |     ID    |  Pass  |\n");
	printf("\t\t  |----|-------------------------------------------\n");
	
	
	for(i=0;i<n;i++)
	{	
		//Displaying The List
		i<9?printf("\t\t  | %d  |",i+1):printf("\t\t  | %d |",i+1);
		printf("%s",std[i].name);
		for(space=0;space<=20-strlen(std[i].name);space++)
		{
			printf(" ");
		}
		printf("|   k200%d |",std[i].id);
		
		//Password Goes Here
		printf("  %s |",std[i].pass);
		printf("\n");
		
	}
	printf("\t\t  -------------------------------------------------");
	printf("\n\n\n");
	changingScreens(std,&n);	
}

void changingScreens(struct student *std,int *n)
{
	char choose;
	printf("\t\t\tA) ADD A STUDENT \n\n");
	printf("\t\t\tE) EDIT A STUDENT \n\n");
	printf("\t\t\tR) EDIT STUDENT'S RECORD\n\n");
	printf("\t\t\tB) BACK\n");
	printf("\n\n\t\tSELECT: ");
	scanf(" %c",&choose);
	switch(choose)
	{
		case 'a':
		case 'A':
			AddStudent(std,n);	
		break;
		
		case 'e':
		case 'E':
			printf("Edit Student");
			EditMode(std,n);
		break;
		
		case 'R':
		case 'r':
//			printf("Record Student");
			RecordMode(std,n);
		break;
		case 'b':
		case 'B':
			loadingmohsin();
			teacherslogin(std,n);
		default:
			system("cls");
			printf("Error!");
		break;
	}
}

void AddStudent(struct student std[],int *n)
{
	int i;
	
	//For restoring the maximum number when an ID is deleted in the future
	for(i=0;i<*n;i++)
	{
		if(std[i].id>max)
		{
			max  = std[i].id;
		}
	}
	
	//Password Generator
	char num[6]={};
	int num1,k=0;
	srand(time(0));
	for(i=0;i>-1;i++)
	{
		num1=rand();
		if((num1>=97 && num1<=123) || (num1>=65 && num1<=91))
		{
			num[k]=num1;
			k++;
		}
		if(num[4]>0)
		break;
	}
	
	//Last Position
		system("cls");
		//Headings & Adding The Name
		printf("\t\t\t\t*******************\n\n");
		printf("\t\t\t\t      ADD MODE\n\n");
		printf("\n\t\t\t\t*******************\n\n\n\n");
		printf("\n\n\t\tEnter The Student's Name: ");
		fflush(stdin);
		gets(std[*n].name);
		
		//Allocating The Unique Roll Numbers To New Members	
		std[*n].id = max+1;
		
		//Allocating The Unique Passwords To New Members
		strcpy(std[*n].pass,num);
		
		//Allocating the value 0 to New Members
		std[*n].study[0].attendance=0;
		std[*n].study[0].final=0;
		std[*n].study[0].midterm=0;
		std[*n].study[0].quiz=0;
		
		//stdPtr->involve.replayed[0]=0;
		//stdPtr->involve.screenTime[0]=0;
		
		//stdPtr->
		
		//Adding The Student FILING
		add(std[*n].name,std[*n].id,std[*n].pass);
		printf("\nBEFORE:%d",*n);		
		(*n)++;
		printf("\nAFTER:%d",*n);
		//CHANGES
		totalStudents(*n);
		DisplayStudentList(std,*n);
}

void EditMode(struct student std[],int *n)
{
	int inputID;
	int check=0;
	int i,j,pos;
	
	
		system("cls");
		
		//Headings & Asking For Input
		printf("\t\t\t\t*******************\n\n");
		printf("\t\t\t\t      Edit Mode\n\n");
		printf("\n\t\t\t\t*******************\n\n\n\n");
		printf("Enter The Student's ID: ");
		fflush(stdin);
		scanf("k200%d",&inputID);
	
	//Checking Against The Database
	for(i=0;i<*n;i++)
		{
			if(inputID== std[i].id)
			{
				check = 1;
				pos=i;
				break;
			}	
			else
				check =0;
		}
		
	//If Found
	if(check)
	{
		printf("\n\nStudent:%s\t\tID:%d\n\n",std[pos].name,std[pos].id);
		char choose;
		printf("\n\n\t\t\tC) CHANGE A STUDENT \n\n");
		printf("\t\t\tD) DELETE A STUDENT \n");
		printf("\n\n\t\tSELECT: ");
		
		//Back
		bk=getch();
		if(bk==BACKSPACE)
		{
			loading();
			DisplayStudentList(std,*n);
		}
		scanf(" %c",&choose);
		
		if(choose == 'C' || choose == 'c')
		{
			printf("Enter The Student's Name: ");
			fflush(stdin);
			gets(std[pos].name);
			//strcpy(name,std[pos].name);
			//FILING EDIT
			editid(std,inputID,std[pos].name,*n);
		}
		else if(choose == 'D' || choose == 'd')
		{
			//FILING DELETE
			recdelete(std,inputID,*n);
			
			//CONTINUED
			printf("POSITION: %d\t",std[pos].id);
			printf("Delete The Student\n");	
			for(j=i;j<*n;j++)
			{
				if(std[j].id > max)
				{
					max = std[j].id;
				}
				strcpy(std[j].name,std[j+1].name);
				std[j].id = std[j+1].id;
				strcpy(std[j].pass,std[j+1].pass);
			}
			(*n)--;
			//CHANGES
			totalStudents(*n);
		}
	system("cls");
	DisplayStudentList(std,*n);	
	}
	
	//If Not Found
	else
	{
		printf("\nThe USER ID %d WAS NOT FOUND\n\n",inputID);
			//Back
		bk=getch();
		if(bk==BACKSPACE)
		{
			loading();
			DisplayStudentList(std,*n);
		}
	}
}

void RecordMode(struct student std[],int *n)
{
	int inputID,i,j,check=0;
	int pos;
	system("cls");
	printf("\t\t\t\t*******************\n\n");
	printf("\t\t\t\t    RECORD MODE\n\n");
	printf("\n\t\t\t\t*******************\n\n\n\n");
	
	printf("\t\t\t    Enter Student's ID: ");
	fflush(stdin);
	scanf("k200%d",&inputID);
	
	//Checking Against The Database
	for(i=0;i<*n;i++)
		{
			if(inputID == std[i].id)
			{
				check = 1;
				pos = i;
				break;
			}	
			else
				check =0;
		}
	
	if(check)
	{
		char choose;
		printf("\n\n\t\t\tA) ACADEMICS \n\n");
		printf("\t\t\tI) INVOLVEMENT \n\n");
		printf("\t\t\tR) REMRAKS\n");
		printf("\n\n\t\tSELECT: ");
		
		//Back
		bk=getch();
		if(bk==BACKSPACE)
		{
			loading();
			DisplayStudentList(std,*n);
		}
		fflush(stdin);
		scanf(" %c",&choose);
	
		switch(choose)
		{
			case 'a':
			case 'A':
			academicScreen(std,n,pos);
			break;
			
			case 'i':
			case 'I':
	
			involveScreen(std,n,pos);
			break;
			
			case 'r':
			case 'R':
				/*
				for(j=0;j<3;j++)
				{
					xs[j]=std[0].study[j].attendance;
					ys[j]=std[0].study[j].quiz;
					printf("\t\txs:%.lf\t\tys:%.lf",xs[j],ys[j]);
				}
		Graph(std,n,xs,ys);*/
			remarkScreen(std,n,pos);	
			break;
			
			default:
				printf("INVALID ENTRY!!");
			break;	
		}
	}
	else
	{
		printf("\nThe USER ID %d WAS NOT FOUND\n\n",inputID);
		//stdPtr-=*n;
				bk=getch();
		if(bk==BACKSPACE)
		{
			loading();
			DisplayStudentList(std,*n);
		}
	}
	
	

	//	system("cls");
}

void academicScreen(struct student *stdPtr, int *n, int pos)
{	
		stdPtr+=pos;
		DisplayAcademic(stdPtr,n,pos);	
}

void DisplayAcademic(struct student *stdPtr, int *n, int pos)
{
	//CHANGES
	//POOR
	int i,nA=10;
	int input;
	char choose;
	
	 AcademicModeHeading(stdPtr,n);
		
		
	printf("\t\t  ----------------------------------------\n");
	printf("\t\t  |S.NO| Attendance | Quiz | Mid | Final |\n");
	printf("\t\t  |----|----------------------------------\n");
	
	for(i=0;i<nA;i++)
	{
if(stdPtr->study[i].quiz == 0 && stdPtr->study[i].attendance == 0 && stdPtr->study[i].midterm == 0 && stdPtr->study[i].final ==0)
{
	printf("\t\t  ----------------------------------------\n\n");
	//CHANGES
	if(i<1)
	printf("\t\t\tA) ADD A STUDENT \n\n");
	printf("\t\t\tE) EDIT A STUDENT \n\n");
	printf("\n\n\t\tSELECT: ");
	
	//Back
	bk=getch();
	if(bk==BACKSPACE)
	{
		stdPtr-=pos;
		loading();
		RecordMode(stdPtr,n);
	}
	scanf(" %c",&choose);
	
	
	switch(choose)
		{
			//CHANGES
			if(i<1)
			{
				case 'A':
				case 'a':
				editAcademic(stdPtr,n,i,pos);
			break;
			}
			
			case 'E':
			case 'e':
				//CHANGES
				//printf("\n\t\tEnter The S.NO for the Edit: ");
				//scanf("%d",&input);
				input=1;
				editAcademic(stdPtr,n,input-1,pos);
				break;
				default:
					break;
		}	
		
	DisplayAcademic(stdPtr,n, pos);	
}
else
{
	//POOR
if(i<1)
{
	i<9?printf("\t\t  | %d  |",i+1):printf("\t\t  | %d |",i+1);
			
		
			//Attendance
			if(stdPtr->study[i].attendance <10)
			printf("     0%.lf     |",stdPtr->study[i].attendance);
			else
			printf("     %.lf     |",stdPtr->study[i].attendance);
			
			//Quiz
			if(stdPtr->study[i].quiz <10)
			printf("  0%.lf  |",stdPtr->study[i].quiz);
			else
			printf("  %.lf  |",stdPtr->study[i].quiz);
			
			//Mid
			if(stdPtr->study[i].midterm<10)
			printf("  0%.lf  |",stdPtr->study[i].midterm);
			else
			printf("  %.lf  |",stdPtr->study[i].midterm);
			
			//Final
			if(stdPtr->study[i].final<10)
			printf("  0%.lf  |",stdPtr->study[i].final);
			else
			printf("  %.lf  |",stdPtr->study[i].final);
			printf("\n");
}
			
}
	}
	printf("\n\t\t  ----------------------------------------\n");
}

void editAcademic(struct student *stdPtr, int *n, int i,int pos)
{
	 AcademicModeHeading(stdPtr,n);
	
	char choose;
	printf("\n\n\t\t\tQ) QUIZ \n\n");
	printf("\t\t\tA) ATTENDANCE \n\n");
	printf("\t\t\tM) MIDTERM \n\n");
	printf("\t\t\tF) FINAL \n");
	printf("\n\n\t\tSELECT: ");
		//Back
	bk=getch();
	if(bk==BACKSPACE)
	{
		loading();
		DisplayAcademic(stdPtr,n,pos);
	}
	scanf(" %c",&choose);
		
	 AcademicModeHeading(stdPtr,n);
	
	switch(choose)
		{
			case 'Q':
			case 'q':
				printf("\t\t\tQUIZ:%.lf Marks\n\n",stdPtr->study[i].quiz);
				printf("Edit The Quiz's Marks: ");
				scanf("%lf",&(stdPtr->study[i].quiz));
				editQuiz(stdPtr,pos,stdPtr->study[i].quiz,*n);
			break;
			case 'A':
			case 'a':
				printf("\t\tATTENDANCE:%.lf \n\n",stdPtr->study[i].attendance);
				printf("Edit The ATTENDANCE: ");
				scanf("%lf",&(stdPtr->study[i].attendance));
				editAttendance(stdPtr,pos,stdPtr->study[i].attendance,*n);
				break;
			case 'M':
			case 'm':
				printf("\t\tMIDTERM:%.lf Marks\n\n",stdPtr->study[i].midterm);
				printf("Edit The Midterm Marks: ");
				scanf("%lf",&(stdPtr->study[i].midterm));
				editMid(stdPtr,pos,stdPtr->study[i].midterm,*n);
				break;
			case 'F':
			case 'f':
				printf("\t\tFINAL:%lf Marks\n\n",stdPtr->study[i].final);
				printf("Edit The Final's Marks: ");
				scanf("%lf",&(stdPtr->study[i].final));
				editFinal(stdPtr,pos,stdPtr->study[i].final,*n);
				break;
				default:
					break;
	}
	
}

void AcademicModeHeading(struct student *stdPtr,int *n)
{
	system("cls");
	printf("\t\t\t\t*******************\n\n");
	printf("\t\t\t\t    ACADEMIC MODE\n\n");
	printf("\n\t\t\t\t*******************\n\n\n\n");
	printf("\t\t\tStudent:%s\t\tID:%d\n\n",stdPtr->name,stdPtr->id);
}

void involveScreen(struct student *stdPtr, int *n, int pos)
{	
		stdPtr+=pos;
		DisplayInvolve(stdPtr,n,pos);		
}

void DisplayInvolve(struct student *stdPtr, int *n, int pos)
{
	//CHANGES
	//POOR
	int i,nA=10;
	int input;
	char choose;
	
	 InvolveModeHeading(stdPtr,n);
		
		
	printf("\t\t  -----------------------------------\n");
	printf("\t\t  |S.NO| SCREEN TIME | # OF REPLAYS |\n");
	printf("\t\t  |----|-----------------------------\n");
	
	for(i=0;i<nA;i++)
	{
if(stdPtr->involve[i].screenTime == 0 && stdPtr->involve[i].replays == 0)
{
	printf("\t\t  -----------------------------------\n\n");
	//CHANGES
	if(i<1)
	printf("\t\t\tA) ADD A STUDENT \n\n");
	printf("\t\t\tE) EDIT A STUDENT \n\n");
	printf("\n\n\t\tSELECT: ");
	
	//Back
	bk=getch();
	if(bk==BACKSPACE)
	{
		stdPtr-=pos;
		loading();
		RecordMode(stdPtr,n);
	}
	scanf(" %c",&choose);
	
	
	switch(choose)
		{
			//CHANGES
			if(i<1)
			{
				case 'A':
				case 'a':
					editInvolve(stdPtr,n,i,pos);
				break;
			}
		
			case 'E':
			case 'e':
				//CHANGES
				//printf("\n\t\tEnter The S.NO for the Edit: ");
				//scanf("%d",&input);
				input=1;
				editInvolve(stdPtr,n,input-1,pos);
				break;
				default:
					break;
		}	
	DisplayInvolve(stdPtr,n, pos);	
}
else
{

if(i<1)
{
				i<9?printf("\t\t  | %d  |",i+1):printf("\t\t  | %d |",i+1);
			
		
			// SCREEN TIME
			if(stdPtr->involve[i].screenTime<10)
			printf("    0%d       |",stdPtr->involve[i].screenTime);
			else if(stdPtr->involve[i].screenTime<99)
			printf("    %d       |",stdPtr->involve[i].screenTime);
			else if(stdPtr->involve[i].screenTime<999)
			printf("   %d       |",stdPtr->involve[i].screenTime);
			
			//# OF REPLAYS
			if(stdPtr->involve[i].replays<10)
			printf("       0%d     |",stdPtr->involve[i].replays);
			else 
			printf("      %d      |",stdPtr->involve[i].replays);
			
			printf("\n");
}

}
	}
			printf("\n\t\t  -----------------------------------\n");
}

void editInvolve(struct student *stdPtr, int *n, int i,int pos)
{
	 InvolveModeHeading(stdPtr,n);
	
	char choose;
	printf("\n\n\t\t\tS) SCREEN TIME \n\n");
	printf("\t\t\tR) REPLAYS \n\n");
	printf("\n\n\t\tSELECT: ");
		//Back
	bk=getch();
	if(bk==BACKSPACE)
	{
		loading();
		DisplayInvolve(stdPtr,n,pos);
	}
	scanf(" %c",&choose);
		
	 InvolveModeHeading(stdPtr,n);
	
	switch(choose)
		{
			case 'S':
			case 's':
				printf("\t\tSCREEN TIME:%.2f Mins\n\n",stdPtr->involve[i].screenTime);
				printf("Edit The Screen Time (in Mins): ");
				scanf("%d",&(stdPtr->involve[i].screenTime));
				editScreen(stdPtr,pos,stdPtr->involve[i].screenTime,*n);
			break;
			case 'R':
			case 'r':
				printf("\t\tREPLAYS:%d \n\n",stdPtr->involve[i].replays);
				printf("Edit The Number Of Replays: ");
				scanf("%d",&(stdPtr->involve[i].replays));
				editReplay(stdPtr,pos,stdPtr->involve[i].screenTime,*n);
				break;
				
				default:
					break;
		}	
	
}

void InvolveModeHeading(struct student *stdPtr,int *n)
{
		system("cls");
		printf("\t\t\t\t*******************\n\n");
		printf("\t\t\t\t  INVOLVEMENT MODE\n\n");
		printf("\n\t\t\t\t*******************\n\n\n\n");
		printf("\t\t\tStudent:%s\t\tID:%d\n\n",stdPtr->name,stdPtr->id);
}

void remarkScreen(struct student *stdPtr, int *n, int pos)
{	
		stdPtr+=pos;
		DisplayRemark(stdPtr,n,pos);		
}

void DisplayRemark(struct student *stdPtr, int *n, int pos)
{
	//CHANGES
	int i,nA=2;
	int input;
	char choose;
	
	 //RemarkModeHeading(stdPtr,n);
		//printf("\t\t%d\t\t%d\t\t%d\t\t",stdPtr->remarks[i].date[0]==0 && stdPtr->remarks[i].date[1]==0 && stdPtr->remarks[i].date[2]==0);
		//{
		//	printf("WOHOO!! NO MESSAGES!!");
		//}
	//printf("%d/%d/%d:\t%s",stdPtr->remarks[i].date[0],stdPtr->remarks[i].date[1],stdPtr->remarks[i].date[2],stdPtr->remarks[i].comment);
	for(i=0;i<nA;i++)
	{
		
if(stdPtr->remarks[i].date[0] == 0 && stdPtr->remarks[i].date[1] == 0 && stdPtr->remarks[i].date[2] == 0)
{
	printf("\t\t  -----------------------------------\n\n");
	//CHANGES
	if(i<1)
	printf("\t\t\tA) ADD A COMMENT \n\n");
	printf("\t\t\tE) EDIT A COMMENT \n\n");
	printf("\n\n\t\tSELECT: ");
	
	//Back
	bk=getch();
	if(bk==BACKSPACE)
	{
		stdPtr-=pos;
		loading();
		RecordMode(stdPtr,n);
	}
	scanf(" %c",&choose);
	
	
	switch(choose)
		{
			if(i<1)
			{
				case 'A':
				case 'a':
					editRemark(stdPtr,n,i,pos);
				break;
			}
			case 'E':
			case 'e':
				//CHANGES
			//	printf("\n\t\tEnter The S.NO for the Edit: ");
			//	scanf("%d",&input);
				input=1;
				editRemark(stdPtr,n,input-1,pos);
				break;
				default:
					break;
		}	
	DisplayRemark(stdPtr,n, pos);	
}
else
{
	printf("%d. %d/%d/%d:\t%s",i+1,stdPtr->remarks[i].date[0],stdPtr->remarks[i].date[1],stdPtr->remarks[i].date[2],stdPtr->remarks[i].comment);
	printf("\n");			
		
}
	}
			printf("\n\t\t  -----------------------------------\n");
}

void editRemark(struct student *stdPtr, int *n, int i,int pos)
{
	 RemarkModeHeading(stdPtr,n);
	
	char choose;
	printf("\n\n\t\t\tD) DATE \n\n");
	printf("\t\t\tC) COMMENT \n\n");
	printf("\n\n\t\tSELECT: ");
		//Back
	bk=getch();
	if(bk==BACKSPACE)
	{
		loading();
		DisplayInvolve(stdPtr,n,pos);
	}
	scanf(" %c",&choose);
		
	 RemarkModeHeading(stdPtr,n);
	
	switch(choose)
		{
			case 'D':
			case 'd':
				printf("\t\tDATE:%d %d %d \n\n",stdPtr->remarks[i].date[0],stdPtr->remarks[i].date[1],stdPtr->remarks[i].date[2]);
				printf("Edit The DATE (in mm dd yy): ");
				scanf("%d %d %d",&stdPtr->remarks[i].date[0],&stdPtr->remarks[i].date[1],&stdPtr->remarks[i].date[2]);
			 	if(stdPtr->remarks[i].date[0]>12)
			 	{
			 		printf("Please enter a month b/w 1 and 12:");
			 		scanf("%d",&stdPtr->remarks[i].date[0]);
				}
			
				else if(stdPtr->remarks[i].date[1]>31)
				{
					printf("Please enter valid day of the month: \n");
					scanf("%d",&stdPtr->remarks[i].date[1]);
				}
				
				else if(stdPtr->remarks[i].date[1]==31&&(stdPtr->remarks[i].date[0]==4||stdPtr->remarks[i].date[0]==6||stdPtr->remarks[i].date[0]==9||stdPtr->remarks[i].date[0]==12))
				{
					printf("Month %d has only 30 days\nPlease enter correct day of month: ",stdPtr->remarks[i].date[0]);
					scanf("%d",stdPtr->remarks[i].date[1]);
				}
			
					else if(stdPtr->remarks[i].date[0]==30&&(stdPtr->remarks[i].date[0]==1||stdPtr->remarks[i].date[0]==3||stdPtr->remarks[i].date[0]==5||stdPtr->remarks[i].date[0]==7||stdPtr->remarks[i].date[0]==8||stdPtr->remarks[i].date[0]==10||stdPtr->remarks[i].date[0]==12))
				{
					printf("Month %d has 31 days\nPlease enter correct day of month: ",stdPtr->remarks[i].date[0]);
					scanf("%d",stdPtr->remarks[i].date[1]);
				}
				
				else if(stdPtr->remarks[i].date[1]!=28&&stdPtr->remarks[i].date[0]==2&&stdPtr->remarks[i].date[1]<32)
				{
					printf("This month has only 28 days\nPlease enter correct day: ");
					scanf("%d",stdPtr->remarks[i].date[1]);
				}
				else
				{
					printf("\n");
				}
	
			break;
			case 'C':
			case 'c':
				printf("\t\tCOMMENTS:%s \n\n",stdPtr->remarks[i].comment);
				printf("Edit The COMMENT: ");
				fflush(stdin);
				gets(stdPtr->remarks[i].comment);
				break;
				
				default:
					break;
		}	
	
}

void RemarkModeHeading(struct student *stdPtr,int *n)
{
		system("cls");
		printf("\t\t\t\t*******************\n\n");
		printf("\t\t\t\t  REMARKS MODE\n\n");
		printf("\n\t\t\t\t*******************\n\n\n\n");
		printf("\t\t\tStudent:%s\t\tID:%d\n\n",stdPtr->name,stdPtr->id);
}


void Graph(double y1,double y2,double y3)
{
	int i;
	int j;
	
	double xs [] = {0, 5, 10};
	double ys [] = {y1, y2, y3};

	RGBABitmapImageReference *canvasReference = CreateRGBABitmapImageReference();
	DrawScatterPlot(canvasReference, 600, 800, xs, 3, ys, 3);

	size_t length;
	double *pngdata = ConvertToPNG(&length, canvasReference->image);
	WriteToFile(pngdata, length, "MarksVsTime.png");
	DeleteImage(canvasReference->image);
}
void idk (struct student std[], int n)
{
	

	
		DisplayStudentList(std,n);
	
	
}
//--------------------------------------------------Mohsin Code end-------------------------------------------------------
//--------------------------------------------------Faheem Code-----------------------------------------------------------
void loadingpos(int x,int y)
{
	COORD coord;
	coord.X=x;
 	coord.Y=y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
void display(struct student std[], int n)
{
	char intro[]="WELCOME TO MINI FLEX",star[]="****************************************************";
	int num,a,j,i,num1=35;
	loadingpos(num1,0);
	for(i=0;i<52;i++)
	{
		loadingpos(num1++,0);
		for(j=1;j<10000000;j++)
		a=j;
		printf("%c",star[i]);
	}
	num1=50;
	loadingpos(num1,2);
	for(i=0;i<20;i++)
	{
		loadingpos(num1++,2);
		for(j=1;j<10000000;j++)
		a=j;
		printf("%c",intro[i]);
	}
	num1=35;
	loadingpos(num1,5);
	for(i=0;i<52;i++)
	{
		loadingpos(num1++,5
		);
		for(j=1;j<10000000;j++)
		a=j;
		printf("%c",star[i]);
	}										//textanimation
	loadingpos(25,24);
	printf("DEVELOPED BY:");
	loadingpos(25,25);
	printf("SYED MUHAMMAD FAHEEM (20K-1054)");
	loadingpos(25,26);
	printf("MOHSIN ALI MIRZA (20K-0353)");
	loadingpos(25,27);
	printf("AHMAD ALEEM (20K-0169)");
	getch();
	system("cls");
	printf("\t\t\t\t****************************************************\n\n");
	printf("\t\t\t\t\t\tWELCOME TO MINI FLEX\n\n");
	printf("\n\t\t\t\t****************************************************\n\n\n\n\n\n");

	printf("\n\n\n\n\t\t\t\t1) PROCEED");
	printf("\n\n\t\t\t\t2) EXIT");
	printf("\n\n\t\t    SELECT: ");
	scanf("%d",&num);
	switch(num)
	{
		case 1:
			 loading();
			 choose(std,n);
			 break;
 		 case 2:
 		 	exit(0);
	}
	}
int loadingmohsin()
{
	int i,j,a;
	loadingpos(90,22);
	printf("LOADING ");
 	loadingpos(98,22);
	 for(i=0;i<=10;i++)
 	{
 		for(j=0;j<10000000;j++)
 		a=j;
 		printf("%c",219);
 	}
 	system("cls");
}
	
int loading()
{
	int i,j,a;
	loadingpos(50,22);
	printf("LOADING ");
 	loadingpos(58,22);
	 for(i=0;i<=10;i++)
 	{
 		for(j=0;j<10000000;j++)
 		a=j;
 		printf("%c",219);
 	}
 	system("cls");
}
int choose(struct student std[], int n)
{
	int num;
	printf("\n\n\n\n\n\t\t\t1) STUDENT'S PORTAL \n\n");
	printf("\t\t\t2) TEACHER'S PORTAL ");
	int sel;
	num=getch();
	if(num==BACKSPACE)
	{
		loading();
		display(std, n);
	}
	printf("\n\n\t\tSELECT: ");
	scanf("%d",&sel);
	if(sel==1)
	{
	loading();
	studentportal(std, n);
	}
	else if (sel==2)
	{
	loading();
	teacherportal(std,n);
	}
	else
	printf("\n\n\t\tINVALID SELECTION");
	
}
int studentportal(struct student std[], int n)
{
	int choice;
	char ch;
	char intro[]="WELCOME TO STUDENT'S PORTAL",star[]="****************************************************";
	int a,j,i,b=35;
	loadingpos(b,0);
	for(i=0;i<52;i++)
	{
		loadingpos(b++,0);
		for(j=1;j<10000000;j++)
		a=j;
		printf("%c",star[i]);
	}
	b=47;
	loadingpos(b,2);
	for(i=0;i<27;i++)
	{
		loadingpos(b++,2);
		for(j=1;j<10000000;j++)
		a=j;
		printf("%c",intro[i]);
	}
	b=35;
	loadingpos(b,5);
	for(i=0;i<52;i++)
	{
		loadingpos(b++,5
		);
		for(j=1;j<10000000;j++)
		a=j;
		printf("%c",star[i]);
	}
	ch=getch();
	if(ch==BACKSPACE)
	{
		loading();
	 	choose(std, n);	
	}
	printf("\n\n\n\n\t\t\t1) LOGIN TO YOUR PERSONAL PROFILE ");
	printf("\n\n\t\t\t2) ANALYSE YOUR PERSONAL PERFORMANCE ");
	printf("\n\n\t\t\t3) BACK \n\n");
	printf("\t\t\t4) EXIT ");
	printf("\n\n\t\tSELECT: ");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:
			loading();
			login(std,n);
			break;
		case 2:
			loading();
			studentgraph(std,n);
			break;
		case 3:
			loading();
			choose(std, n);
			break;
		case 4:
			exit(0);
	}	
}
int teacherportal(struct student std[],int n)
{
	char ch;
 	int choice;
	char intro[]="WELCOME TO TEACHER'S PORTAL",star[]="****************************************************";
	int a,j,i,b=35;
	loadingpos(b,0);
	for(i=0;i<52;i++)
	{
		loadingpos(b++,0);
		for(j=1;j<10000000;j++)
		a=j;
		printf("%c",star[i]);
	}
	b=47;
	loadingpos(b,2);
	for(i=0;i<27;i++)
	{
		loadingpos(b++,2);
		for(j=1;j<10000000;j++)
		a=j;
		printf("%c",intro[i]);
	}
	b=35;
	loadingpos(b,5);
	for(i=0;i<52;i++)
	{
		loadingpos(b++,5
		);
		for(j=1;j<10000000;j++)
		a=j;
		printf("%c",star[i]);
	}
	ch=getch();
	if(ch==BACKSPACE)
	{
		loading();
	 	system("cls");
		choose(std,n);	
	}
	printf("\n\n\n\n\t\t\t1) LOGIN TO TEACHER'S ACCOUNT ");
	printf("\n\n\t\t\t2) BACK \n\n");
	printf("\t\t\t3) EXIT ");
	printf("\n\n\t\tSELECT: ");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:
			loading();
			teacherslogin(std,n);
			break;
		case 2:
			loading();
			choose(std, n);
			break;
		case 3:
			exit(0);
	}
	
}
int studentgraph(struct student std[],int n)
{
	int num[6]={0,0,0,0,0,0},num1,i,j=0,k=0,id,pos,check=0,t;
	char ch,ch1,pass[100],captcha[100];
	char intro[]="WELCOME TO PERFORMANCE GRAPH PORTAL",star[]="****************************************************";
	int a,b=35;
	loadingpos(b,0);
	for(i=0;i<52;i++)
	{
		loadingpos(b++,0);
		for(j=1;j<10000000;j++)
		a=j;
		printf("%c",star[i]);
	}
	b=43;
	loadingpos(b,2);
	for(i=0;i<35;i++)
	
	{
		loadingpos(b++,2);
		for(j=1;j<10000000;j++)
		a=j;
		printf("%c",intro[i]);
	}
	b=35;
	loadingpos(b,5);
	for(i=0;i<52;i++)
	{
		loadingpos(b++,5
		);
		for(j=1;j<10000000;j++)
		a=j;
		printf("%c",star[i]);
	}	
	t=getch();
	if(t==BACKSPACE)
	{
		loading();
		studentportal(std,n);
	}
	j=0;
	k=0;
	fflush(stdin);
	printf("\n\n\n\t\t\tENTER YOUR STUDENT ID: ");
	scanf("k200%d",&id);
	for(i=0;i<n;i++)
	{
		if(id==std[i].id)
		{
			check=1;
			pos=i;
			break;
		} 
		
	}
	if(check!=1)
	{
		printf("\n\n\t\t\tINVALID ID");
		getch();
		loading();
		studentgraph(std,n);
		}	
	printf("\n\n\t\t\tENTER YOUR PASSWORD: ");
	for(i=0;i>-1;i++)
	{
		ch=getch();
		if(ch==ENTER)
		{
			pass[i]='\0';
			break;
		}
		else if (ch==BACKSPACE)
		{
			if(j>0)
			{
				j--;
				printf("\b \b");
			}
		}
		else 
		{
			pass[j++]=ch;
			printf("*");
		}
	}
	if(strcmp(pass,std[pos].pass)!=0)
	check=0;
	printf("\n\n\t\t\t\t****************************************************\n\n");
	printf("\t\t\t\t\t     PROVE YOU ARE NOT A ROBOT!!\n\n");
	printf("\n\t\t\t\t****************************************************\n\n\n\n");
	printf("\t\tWRITE THIS PATTERN TO PROCEED: \n\n\n");
	srand(time(0));
	printf("\t\t\t");
	for(i=0;i>-1;i++)
	{
		num1=rand();
		
		if((num1>=97 && num1<=123) || (num1>=65 && num1<=91))
		{
			num[k]=num1;
			printf("%c",num[k]);
			k++;
		}
		
		if(num[5]>0)
		break;
	}
	
	printf("\n\n\n\t\tENTER THE PATTERN: ");
	fflush(stdin);
	gets(captcha);
	checkcaptchagraph(&captcha,&num,std,n,pos,check);
	
}

//Mohsingraph
int checkcaptchagraph(char captcha[0],int num[0],struct student *stdPtr,int n,int pos,int check)
{
	stdPtr+=pos;
	int i,count=0,ch;
	for(i=0;captcha[i]!='\0';i++)
	{
		if(captcha[i]==num[i])
		count++;
	}
	
	if(count==6)
	{
		system("cls");
		loading();
		char intro[]="PERSONAL PERFORMANCE GRAPH GENERATOR",star[]="****************************************************";
	int a,j,b=35;
	loadingpos(b,0);
	for(i=0;i<52;i++)
	{
		loadingpos(b++,0);
		for(j=1;j<10000000;j++)
		a=j;
		printf("%c",star[i]);
	}
	b=42;
	loadingpos(b,2);
	for(i=0;i<36;i++)
	{
		loadingpos(b++,2);
		for(j=1;j<10000000;j++)
		a=j;
		printf("%c",intro[i]);
	}
	b=35;
	loadingpos(b,5);
	for(i=0;i<52;i++)
	{
		loadingpos(b++,5
		);
		for(j=1;j<10000000;j++)
		a=j;
		printf("%c",star[i]);
	}
		if(check==1)
		{
		printf("\n\n\n\n\n\t\t     YOUR GRAPH HAS BEEN PRINTED SUCCESSFULLY. OPEN YOUR FILE TO VIEW YOUR ANALYTICS");
		getch();
		loading();
		
		Graph(stdPtr->study[0].quiz,stdPtr->study[0].midterm,stdPtr->study[0].final);
		stdPtr-=pos;
		studentgraph(stdPtr,n);
		}
	 	 		 
	}
	else
	{
		printf("\n\t\t\t\t\t\tINCORRECT CAPTCHA");
		ch=getch();
		if(ch==BACKSPACE)
		{
			system("cls");
			loading();
			stdPtr-=pos;
			studentgraph(stdPtr,n);
		}

		system("cls");
		stdPtr-=pos;
		studentgraph(stdPtr, n);
	}
	int c;
	c=getch();
		if(c==BACKSPACE)
		{
			loading();
			stdPtr-=pos;
			studentgraph(stdPtr,n);
		}

}
int teacherregister(struct student std[],int n)
{
	printf("N:%d",n);
	printf("NAME:%s ID:%d\tNAME:%s ID:%d",std[0].name,std[0].id,std[1].name,std[1].id);
	int ch;
	char user[100],key[100];
	char intro[]="REGISTER YOURSELF AS A TEACHER",star[]="****************************************************";
	int a,j,i,b=35;
	loadingpos(b,0);
	for(i=0;i<52;i++)
	{
		loadingpos(b++,0);
		for(j=1;j<10000000;j++)
		a=j;
		printf("%c",star[i]);
	}
	b=45;
	loadingpos(b,2);
	for(i=0;i<30;i++)
	{
		loadingpos(b++,2);
		for(j=1;j<10000000;j++)
		a=j;
		printf("%c",intro[i]);
	}
	b=35;
	loadingpos(b,5);
	for(i=0;i<52;i++)
	{
		loadingpos(b++,5
		);
		for(j=1;j<10000000;j++)
		a=j;
		printf("%c",star[i]);
	}
	ch=getch();
	if(ch==BACKSPACE)
	{
		loading();
		teacherportal(std, n);
	}
	fflush(stdin);
	printf("\n\n\n\n\t\t\tCREATE YOUR OFFICIAL USERNAME: ");
	gets(user);
	fflush(stdin);
	printf("\n\n\t\t\tCREATE YOUR PASSWORD: ");
	gets(key);
	char prof[]="YOUR PROFILE HAS BEEN CREATED";
	b=35;
	loadingpos(b,15);
	for(i=0;i<52;i++)
	{
		loadingpos(b++,15);
		for(j=1;j<10000000;j++)
		a=j;
		printf("%c",star[i]);
	}
	b=46;
	loadingpos(b,17);
	for(i=0;i<29;i++)
	{
		loadingpos(b++,17);
		for(j=1;j<10000000;j++)
		a=j;
		printf("%c",prof[i]);
	}
	b=35;
	loadingpos(b,20);
	for(i=0;i<52;i++)
	{
		loadingpos(b++,20);
		for(j=1;j<10000000;j++)
		a=j;
		printf("%c",star[i]);
	}
}
int teacherslogin(struct student std[],int n)
{
	char username[50],pass[50],encrypt[50];
	int count=0,ch=0;
	char intro[]="WELCOME TO TEACHER'S LOGIN PORTAL",star[]="****************************************************";
	int a,j,i,b=35;
	loadingpos(b,0);
	
	for(i=0;i<52;i++)
	{
		loadingpos(b++,0);
		for(j=1;j<10000000;j++)
		a=j;
		printf("%c",star[i]);
	}
	b=45;
	loadingpos(b,2);
	for(i=0;i<33;i++)
	{
		loadingpos(b++,2);
		for(j=1;j<10000000;j++)
		a=j;
		printf("%c",intro[i]);
	}
	b=35;
	loadingpos(b,5);
	for(i=0;i<52;i++)
	{
		loadingpos(b++,5);
		for(j=1;j<10000000;j++)
		a=j;
		printf("%c",star[i]);
	}
	
	ch=getch();
	if(ch==BACKSPACE)
	{
 loading();
	   teacherportal(std, n);
	}
	
	j=0;
	fflush(stdin);
	printf("\n\n\n\n\t\t\tENTER YOUR OFFICIAL USERNAME: ");
	gets(username);
	printf("\n\n\t\t\tENTER YOUR PASSWORD: ");
	for(i=0;i>-1;i++)
	{
		ch=getch();
		if(ch==ENTER)
		{
			pass[i]='\0';
			break;
		}
		
		else if (ch==BACKSPACE)
		{
			if(j>0)
			{
				j--;
				printf("\b \b");
			}
		}
		
		else 
		{
			pass[j++]=ch;
			printf("*");
		}
	}
	for(i=0;pass[i]!='\0';i++)
	{
		encrypt[i]=pass[i];
		if(pass[i]==' ')
		continue;
		encrypt[i]=encrypt[i]+3;
	}
	for(i=0;encrypt[i]!='\0';i++)
	{
	 	pass[i]=encrypt[i];		
	}

	printf("\n\n\t\tThe encrypted password is:  %s",encrypt);
	getch();
	if(strcmp(username,"Atiya Jokhio")==0)
	{
 	count++;
	}
	
	if(strcmp(pass,encrypt)==0)
	{
		count++;
	}	
	if(count==2)
	{
		loading();
		teacherwork(std,n);
	}
	else
	{
		printf("\n\n\t\t\tINVALID CREDENTIALS!");
		ch=getch();
		if(ch==BACKSPACE)
		{
            loading();
  			choose(std, n);
		}
		loading();
		return teacherslogin(std,n);
	}	
}

int teacherwork(struct student std[],int n)
{
	int ch;
	char intro[]="WELCOME TO PERSONAL PROFILE",star[]="****************************************************";
	int a,j,i,b=35;
	loadingpos(b,0);
	for(i=0;i<52;i++)
	{
		loadingpos(b++,0);
		for(j=1;j<10000000;j++)
		a=j;
		printf("%c",star[i]);
	}
	b=47;
	loadingpos(b,2);
	for(i=0;i<32;i++)
	{
		loadingpos(b++,2);
		for(j=1;j<10000000;j++)
		a=j;
		printf("%c",intro[i]);
	}
	b=35;
	loadingpos(b,5);
	for(i=0;i<52;i++)
	{
		loadingpos(b++,5
		);
		for(j=1;j<10000000;j++)
		a=j;
		printf("%c",star[i]);
	}
	ch=getch();
	if(ch==BACKSPACE)
	{
		loading();
		teacherslogin(std,n);
	}
	loading();
	idk(std,n);

}
int login(struct student std[],int n)
{
	int num[6]={0,0,0,0,0,0},num1,i,j=0,k=0,id,pos,check=0;
	char ch,ch1,pass[100],captcha[100];
	fflush(stdin);
	printf("\n\n\t\t\tENTER YOUR STUDENT ID: ");
	scanf("k200%d",&id);
	for(i=0;i<n;i++)
	{
		if(id==std[i].id)
		{
			check=1;
			pos=i;
			break;
		} 
		
	}
	if(check!=1)
	{
		printf("\n\n\t\t\tINVALID ID");
		getch();
		loading();
		login(std,n);
		}	
	printf("\n\n\t\t\tENTER YOUR PASSWORD: ");
	for(i=0;i>-1;i++)
	{
		ch=getch();
		if(ch==ENTER)
		{
			pass[i]='\0';
			break;
		}
		else if (ch==BACKSPACE)
		{
			if(j>0)
			{
				j--;
				printf("\b \b");
			}
		}
		else 
		{
			pass[j++]=ch;
			printf("*");
		}
	}
	if(strcmp(pass,std[pos].pass)!=0)
	check=0;
	printf("\n\n\t\t\t\t****************************************************\n\n");
	printf("\t\t\t\t\t\tPROVE YOU ARE NOT A ROBOT!!\n\n");
	printf("\n\t\t\t\t****************************************************\n\n\n\n");
	printf("\t\tWRITE THIS PATTERN TO PROCEED: \n\n\n");
	srand(time(0));
	printf("\t\t\t");
	for(i=0;i>-1;i++)
	{
		num1=rand();
		
		if((num1>=97 && num1<=123) || (num1>=65 && num1<=91))
		{
			num[k]=num1;
			printf("%c",num[k]);
			k++;
		}
		
		if(num[5]>0)
		break;
	}
	
	printf("\n\n\n\t\tENTER THE PATTERN: ");
	fflush(stdin);
	gets(captcha);
	checkcaptcha(&captcha,&num,std,n,pos,check);
}

int checkcaptcha(char captcha[0],int num[0],struct student std[],int n,int pos,int check)
{
	int i,count=0,ch;
	for(i=0;captcha[i]!='\0';i++)
	{
		if(captcha[i]==num[i])
		count++;
	}
	
	if(count==6)
	{
		system("cls");
		loading();
		char intro[]="WELCOME TO YOUR PERSONAL PROFILE",star[]="****************************************************";
	int a,j,b=35;
	loadingpos(b,0);
	for(i=0;i<52;i++)
	{
		loadingpos(b++,0);
		for(j=1;j<10000000;j++)
		a=j;
		printf("%c",star[i]);
	}
	b=46;
	loadingpos(b,2);
	for(i=0;i<32;i++)
	
	{
		loadingpos(b++,2);
		for(j=1;j<10000000;j++)
		a=j;
		printf("%c",intro[i]);
	}
	b=35;
	loadingpos(b,5);
	for(i=0;i<52;i++)
	{
		loadingpos(b++,5
		);
		for(j=1;j<10000000;j++)
		a=j;
		printf("%c",star[i]);
	}
		if(check==1)
		{
		printf("\n\n\n\n");
		displayiddata(std,std[pos].id,n);
		getch();
		loading();
		studentportal(std,n);
		}
	 	 		 
	}
	else
	{
		printf("\n\t\t\t\t\t\tINCORRECT CAPTCHA");
		ch=getch();
		if(ch==BACKSPACE)
		{
			system("cls");
			loading();
			studentportal(std,n);
		}

		system("cls");
		login(std, n);
	}
	ch=getch();
		if(ch==BACKSPACE)
		{
			loading();
			login(std,n);
		}

}

//READ AND WRITE DATA
void read(FILE *ptr,struct student std[],int n)
{
	char temp[20];
	char *token;
	int key=1;
	int count=0;
	int i=0, tempID,tempatt,tempdate,tempst;
	double tempfinal,tempmid,tempquiz,temprep;
	
	while(!feof(ptr))
	{
		fscanf(ptr,"%s,",&temp);
		token=strtok(temp,",");
		while(token!=NULL && !feof(ptr))
		{
			if(key==1 && i!=0)
			{
				strcpy(std[i-1].name,token);
			//	printf("%s",std[i-1]);
			}
				
		
			else if(key==2 && i!=0)
			{
				tempID=atoi(token);
				std[i-1].id=tempID;
			}
			
			
			else if(key==3 && i!=0)
			{
				strcpy(std[i-1].pass,token);
			}
			
			else if(key==4 && i!=0)
			{
				tempquiz=atof(token);
				std[i-1].study[0].quiz=tempquiz;
			}
			
			else if(key==5 && i!=0)
			{
				tempmid=atof(token);
				std[i-1].study[0].midterm=tempmid;	
			}
			else if(key==6 && i!=0)
			{
				tempfinal=atof(token);
				std[i-1].study[0].final=tempfinal;
				
			}
			else if(key==7 && i!=0)
			{
				tempatt=atoi(token);
				std[i-1].study[0].attendance=tempatt;	
			}
			
			else if(key==8 && i!=0)
			{
				tempst=atoi(token);
				std[i-1].involve[0].screenTime=tempst;
			}
			
			else if(key==9)
			{
				if(i!=0)
				{
					temprep=atoi(token);
					std[i-1].involve[0].replays=temprep;
				}
				key=0;
			}	
			
			else
			{
			}
		
			//if(key!=9 && i!=1)
			token=strtok(NULL,",");
			key++;
			
		}
		i++;
		
		
	}
}
void recdelete(struct student std[],int del,int n)
{
	FILE *ftemp=fopen("read.csv","w");
	int i,line=0;
	
	fflush(stdin);
	fprintf(ftemp,"Name,ID,Pass,Quiz,Mid,Final,Attend,Screen,Replays\n");
	for(i=0;i<n;i++)
	{
		if(std[i].id!=del)
		{
			fprintf(ftemp,"%s,%d,%s,%.1lf,%.1lf,%.1lf,%.lf,%d,%d\n",std[i].name,std[i].id,std[i].pass,std[i].study[0].quiz,std[i].study[0].midterm,std[i].study[0].final,std[i].study[0].attendance,std[i].involve[0].screenTime,std[i].involve[0].replays);
		}
		line++;
	}
	fclose(ftemp);
}

void editid(struct student std[],int id,char chngname[20],int n)
{
	FILE *ftemp=fopen("read.csv","w");
	int i,line=0;
	fflush(stdin);
	fprintf(ftemp,"Name,ID,Pass,Quiz,Mid,Final,Attend,Screen,Replays\n");
	for(i=0;i<n;i++){
			if(std[i].id==id){
				strcpy(std[i].name,chngname);
			}		
			fprintf(ftemp,"%s,%d,%s,%.1lf,%.1lf,%.1lf,%.lf,%d,%d\n",std[i].name,std[i].id,std[i].pass,std[i].study[0].quiz,std[i].study[0].midterm,std[i].study[0].final,std[i].study[0].attendance,std[i].involve[0].screenTime,std[i].involve[0].replays);
	}
	fclose(ftemp);
	}	

void add(char name[20],int id,char pass[20])
{
	//POOR
	FILE *idk;
	if((idk=fopen("read.csv","a"))!=NULL)
	fprintf(idk,"%s,%d,%s,%lf,%lf,%lf,%lf,%d,%d\n",name,id,pass,0,0,0,0,0,0);
	fclose(idk);
}

void totalStudents(int n)
{
	FILE *total;
	
	if((total=fopen("Total.txt","w"))!=NULL)
	fprintf(total,"%d",n);
	
	fclose(total);
}
void displayiddata(struct student std[],int id,int n)
{
	int i;
	printf("%s\t%s\t%s\t%s\t%s\t%s\t\%s\t%s\t%s\n","Name","ID","Pass","Quiz","Mid","Final","Attend","Screen","Replays");
	
	for(i=0;i<n;i++)
	{
		if(std[i].id==id)
		printf("%s\t%d\t%s\t%.1lf\t%.1lf\t%.1lf\t%.lf\t%d\t%d\n",std[i].name,std[i].id,std[i].pass,std[i].study[0].quiz,std[i].study[0].midterm,std[i].study[0].final,std[i].study[0].attendance,std[i].involve[0].screenTime,std[i].involve[0].replays);
		
	}
	
}

void editQuiz(struct student std[],int id,double quiz,int n)
{
	FILE *ftemp=fopen("read.csv","w");
	int i,line=0;
	fflush(stdin);
	fprintf(ftemp,"Name,ID,Pass,Quiz,Mid,Final,Attend,Screen,Replays\n");
	for(i=0;i<n;i++){
			if(std[i].id==id){
				std[i].study[0].quiz=quiz;
			}		
			fprintf(ftemp,"%s,%d,%s,%.1lf,%.1lf,%.1lf,%.lf,%d,%d\n",std[i].name,std[i].id,std[i].pass,std[i].study[0].quiz,std[i].study[0].midterm,std[i].study[0].final,std[i].study[0].attendance,std[i].involve[0].screenTime,std[i].involve[0].replays);
	}
	fclose(ftemp);
}

void editMid(struct student std[],int id,double mid,int n)
{
	FILE *ftemp=fopen("read.csv","w");
	int i,line=0;
	fflush(stdin);
	fprintf(ftemp,"Name,ID,Pass,Quiz,Mid,Final,Attend,Screen,Replays\n");
	for(i=0;i<n;i++){
			if(std[i].id==id){
				std[i].study[0].midterm=mid;
			}		
			fprintf(ftemp,"%s,%d,%s,%.1lf,%.1lf,%.1lf,%.lf,%d,%d\n",std[i].name,std[i].id,std[i].pass,std[i].study[0].quiz,std[i].study[0].midterm,std[i].study[0].final,std[i].study[0].attendance,std[i].involve[0].screenTime,std[i].involve[0].replays);
	}
	fclose(ftemp);
}

void editFinal(struct student std[],int id,double final,int n)
{
	FILE *ftemp=fopen("read.csv","w");
	int i,line=0;
	fflush(stdin);
	fprintf(ftemp,"Name,ID,Pass,Quiz,Mid,Final,Attend,Screen,Replays\n");
	for(i=0;i<n;i++){
			if(std[i].id==id){
				std[i].study[0].final=final;
			}		
			fprintf(ftemp,"%s,%d,%s,%.1lf,%.1lf,%.1lf,%.lf,%d,%d\n",std[i].name,std[i].id,std[i].pass,std[i].study[0].quiz,std[i].study[0].midterm,std[i].study[0].final,std[i].study[0].attendance,std[i].involve[0].screenTime,std[i].involve[0].replays);
	}
	fclose(ftemp);
}

void editAttendance(struct student std[],int id,double attend,int n)
{
	FILE *ftemp=fopen("read.csv","w");
	int i,line=0;
	fflush(stdin);
	fprintf(ftemp,"Name,ID,Pass,Quiz,Mid,Final,Attend,Screen,Replays\n");
	for(i=0;i<n;i++){
			if(std[i].id==id){
				std[i].study[0].attendance=attend;
			}		
			fprintf(ftemp,"%s,%d,%s,%.1lf,%.1lf,%.1lf,%.lf,%d,%d\n",std[i].name,std[i].id,std[i].pass,std[i].study[0].quiz,std[i].study[0].midterm,std[i].study[0].final,std[i].study[0].attendance,std[i].involve[0].screenTime,std[i].involve[0].replays);
	}
	fclose(ftemp);
}

void editScreen(struct student std[],int id,int screen,int n)
{
	FILE *ftemp=fopen("read.csv","w");
	int i,line=0;
	fflush(stdin);
	fprintf(ftemp,"Name,ID,Pass,Quiz,Mid,Final,Attend,Screen,Replays\n");
	for(i=0;i<n;i++){
			if(std[i].id==id){
				std[i].involve[0].screenTime=screen;
			}		
			fprintf(ftemp,"%s,%d,%s,%.1lf,%.1lf,%.1lf,%.lf,%d,%d\n",std[i].name,std[i].id,std[i].pass,std[i].study[0].quiz,std[i].study[0].midterm,std[i].study[0].final,std[i].study[0].attendance,std[i].involve[0].screenTime,std[i].involve[0].replays);
	}
	fclose(ftemp);
}

void editReplay(struct student std[],int id,int replay,int n)
{
	FILE *ftemp=fopen("read.csv","w");
	int i,line=0;
	fflush(stdin);
	fprintf(ftemp,"Name,ID,Pass,Quiz,Mid,Final,Attend,Screen,Replays\n");
	for(i=0;i<n;i++){
			if(std[i].id==id){
				std[i].involve[0].replays=replay;
			}		
			fprintf(ftemp,"%s,%d,%s,%.1lf,%.1lf,%.1lf,%.lf,%d,%d\n",std[i].name,std[i].id,std[i].pass,std[i].study[0].quiz,std[i].study[0].midterm,std[i].study[0].final,std[i].study[0].attendance,std[i].involve[0].screenTime,std[i].involve[0].replays);
	}
	fclose(ftemp);
}



int main()
{
	system("color 6");
	int n;
	FILE *ptr;
	FILE *total;
	
	//CHANGES
	if((total=fopen("Total.txt","r"))!=NULL)
	fscanf(total,"%d",&n);
	fclose(total);
	
	struct student std[10]={};
	if((ptr=fopen("read.csv","r"))!=NULL)
	read(ptr,std,n);
	else
	{
		printf("ERROR IN READING!");
	}

	//	struct student std[10]=
	//{
	//	{"Mohsin", 100,"calop", { {10,20,30,0},{11,21,31,41},{12,22,32,42},{0,0,0,0} } , {{50,5}}  },
	//	{"Faheem", 101,"dalop", {9,23,53,22}  , {40,3}  },
	//	{"Ahmad",  102,"malop",  {8,24,54,23} , {30,2}  },
	//};
	//
	//
	//
	//
	
	system("color 6");
	display(std, n);
	getch();
}
