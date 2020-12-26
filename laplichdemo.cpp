	
#include <stdio.h >
#include <conio.h >
#include <iostream >
#include <stdlib.h >
#include <string.h >
#include <windows.h >
using namespace std;
int totalTime = 0;
float totalTimePresence=0,timePresenceMedium=0; // thoi gian hien dien trong CPU
float totalTimeWait=0,timeWaitMedium=0; //thoi gian cho

struct data
{
	int appearTime; // Thoi gian xuat hien
	int executionTime; // Thoi gian thuc hien
	int timeEnd; //Moc thoi gian hoan thanh cong viec
	int presenceTime; //Thoi gian hien dien trong CPU
	int waitTime; // Thoi Gian choi doi CPU cap phat

	char name[20];
	float ntat; //Thoi gian hien dien/Thoi gian xu ly
	int priority; //priority Do uu tien - Dung cho thuat toan Priority
//	int remainTime; // thoi gian con lai de thuc hien not - Dung cho thuat toan SRT
} temp;

struct nameProcessGnatt 
{
	char name[20];
} temp2;

void input(struct data inputDataProcess[],int inputNumberProcess);
void FCFS(struct data inputDataProcess[],int inputNumberProcess);
void SJF(struct data inputDataProcess[],int inputNumberProcess);
void displayTable(struct data inputDataProcess[],int inputNumberProcess); // xai chung cho FCFS, SJF
void displayGantt(struct data inputDataProcess[],int inputNumberProcess); // xai chung cho FCFS, SJF, PRI

void priorityFinding(struct data inputDataProcess[],int inputNumberProcess);
void priorityDisplayTable(struct data inputDataProcess[],int inputNumberProcess);

void SRT(struct data inputDataProcess[],int inputNumberProcess); // bao gam table va gnatt

//varibble for round_bind
int timeCount = 0; 
int front = 0; //truoc
int rear = 0; // sau
int numberProcessQueue = 0; // so tien trinh trong hang doi
int m = 0, s = 0;
int queue[1000]; // hang doi
int stt;
//end variable for round bind

// function for round bind
void RR_finding(struct data inputDataProcess[],int inputNumberProcess);
void push(int q) ;
int pop();
void check(struct data inputDataProcess[],int inputNumberProcess);
//end function for round bind


void about();


int main(){
	 cout<< "------------------------------------------------------------------------------------------------------------------\n";
	 cout<< "       Chuong Trinh Mo Phong Cac Giai Thuat Dinh Thoi Cho CPU by Khanh Noi - FrontDev (info: khanhnoi.mobie.in)    \n";
	 cout<< "------------------------------------------------------------------------------------------------------------------\n\n";

  int numberProcess;// so tien trinh
  char checkOption;// kiem tra lua chon
  
  int flagOpt = true;
//  label1:
  	cout<< "+ Nhap So Luong Ten Trinh: ";
  	cin>>numberProcess;
//	if(numberProcess == 0) goto label1;
  
  struct data dataProcess[numberProcess];
  cout<<"\n+ Nhap Thong Tin Cac Tien Trinh:\n";
  
  //Ham nhap cac thong tin tien trinh
  input(dataProcess,numberProcess); 
  
  //Tong thoi gian tat cac cac tien tinh hoan thanh - totalTime
    totalTime += dataProcess[0].appearTime + dataProcess[0].executionTime;
    for(int i=1;i<numberProcess;i++)
    {
    	//neu qua trinh tiep theo den sau mot luc  sau khi qua trinh truoc da hoan thanh roi
   	 	if( dataProcess[i].appearTime > totalTime ) totalTime = dataProcess[i].appearTime;
    	totalTime += dataProcess[i].executionTime;
    }
  //END totalTime

    label:
    int flag = true;
    do
	{
   		cout << "\n\tChon Thuat Toan Mo Phong :";
    	cout << "\n\t-[1].\t\t Thuat Toan FCFS (Test ok)";
    	cout << "\n\t-[2].\t\t Thuat Toan SJF (Test ok)";
    	cout << "\n\t-[3].\t\t Thuat Toan Priority (Test ok)";
    	cout << "\n\t-[4].\t\t Thuat Toan SRT (Test ok)";
    	cout << "\n\t-[5].\t\t Thuat Toan RR (Test Ok)";
    	cout << "\n\t-[Other].\t Thoat chuong trinh";

    	cout << "\n\t ==> Ban chon: ";
    	cin >> checkOption;
    	if(checkOption != '1' || checkOption != '2' || checkOption != '3' || checkOption != '4' || checkOption != '5') flag = false;
 	 } 
	 while (flag);
  
  if (checkOption != '1' && checkOption != '2' && checkOption != '3' && checkOption != '4' && checkOption != '5') 
  {
  	about();
  	exit(0);
  }
  
  if (checkOption > 0) {
  	
    if (checkOption == '1') {
      cout<<"\n+ Thong Tin Lap Lich Theo Thuat Toan FCFS: \n\n";
      FCFS(dataProcess,numberProcess);
    } 
	else if (checkOption == '2') {
       	cout<<"\n+ Thong tin lap lich theo thuat toan SJF: \n\n";
    	SJF(dataProcess,numberProcess);
    } 
	else if (checkOption == '3') {
		cout<<"Note: Do Uu Tien '1' se dc uu tien hon Do Uu Tien '2'\n";
        for(int i = 0;i<numberProcess;i++){
            printf("+ Nhap Do Uu Tien Cua Tien Trinh %s: ", dataProcess[i].name);
            scanf("%d",&dataProcess[i].priority);
        }
        priorityFinding(dataProcess,numberProcess);
    }
    else if (checkOption == '4') {
      cout<<"\n+ Thong Tin Lap Lich Theo Thuat Toan SRT: \n\n";
      SRT(dataProcess,numberProcess);
    } 
	else if (checkOption == '5') {

      RR_finding(dataProcess,numberProcess);
    } 
	else {
    	exit(0);
    }
  }
   //FCFS, SJF, PRI
   if(checkOption != '4' && checkOption != '5')
   {
	    cout << endl;
	    cout<< "+So Do Gantt:\t ";
	    displayGantt(dataProcess,numberProcess);
   }
   cout << endl << endl << "+ Ban Co Muon Mo Phong Bang Giai Thuat Khac? \n( Nhan 'Y' de dong y hoac [Phim Bat Ki] khac de thoat chuong trinh  roi [ENTER])\n";
   char checkOtherOption;
   cin >> checkOtherOption;
   if(checkOtherOption == 'y' || checkOtherOption == 'Y')
   {
	    totalTimePresence=0,timePresenceMedium=0;
	    totalTimeWait=0,timeWaitMedium=0;
	    goto label;
   }
  about(); 
  cout << endl << endl;
  return 0;
}


//setup cac ham

//Ham nhap thong tin cac tien trinh va sap xep lai thu tu
void input(struct data inputDataProcess[],int inputNumberProcess)
{
    struct data temp;
    cout<<"------------------------------------\n";
    cout << "Note: Thong Tin Nhap bao gom: [Ten Tien Trinh] + [Thoi Gian Xuat Hien] + [Thoi Gian Thuc Hien] \n";
    cout << "VD: ( p1 0 24 ) ( p2 1 3) (p3 2 3)\n";
    cout << "VD: ( p1 0 11 ) ( p2 3 7) (p3 8 19) (p4 13 4) (p5 17 9)\n";
     cout<<"------------------------------------\n";
    for(int i=0;i<inputNumberProcess;i++)
    {
        printf("+ Nhap Thong Tin Tien Trinh %d :\n", i+1);
        scanf("%s",&inputDataProcess[i].name);
        scanf("%d",&inputDataProcess[i].appearTime);
        scanf("%d",&inputDataProcess[i].executionTime);
//        inputDataProcess[i].remainTime = inputDataProcess[i].executionTime; // ban dau [thoi gian con lai de lam] bang [thoi gian thuc thi]
        cout<<"------------------------------------\n";
    }
//sap xep thu tu time xuat hien tang dan
	for(int i=0;i<inputNumberProcess;i++)
	{
		for(int j=i;j>=1;j--)
		{
			if(inputDataProcess[j].appearTime < inputDataProcess[j-1].appearTime)
			{
				temp=inputDataProcess[j-1];
				inputDataProcess[j-1]=inputDataProcess[j];
				inputDataProcess[j]=temp;
			}
		}
	}
}

// FSFS - first come, first served
void FCFS(struct data inputDataProcess[],int inputNumberProcess)
{
	// calc timeEnd
	int stt = inputDataProcess[0].appearTime, tempi;
	inputDataProcess[0].timeEnd = stt + inputDataProcess[0].executionTime;
	stt=inputDataProcess[0].timeEnd;
	for(int i=1;i<inputNumberProcess;i++)
	{
		tempi=inputDataProcess[i].appearTime; // check thoi gian xuat hien cua tien trinh tiep theo
		if(tempi > stt) stt=tempi; // khi nhap cac tien trinh cung da dc sap xep ngay trong ham input roi			
		inputDataProcess[i].timeEnd = stt + inputDataProcess[i].executionTime;
		stt=inputDataProcess[i].timeEnd;
	}
	// End calc timeEnd
	displayTable(inputDataProcess,inputNumberProcess);
}

//display table ( tinh cac chi so Tien Trinh hien thi dang bang )
void displayTable(struct data inputDataProcess[],int inputNumberProcess)
{
	int i,j;
	for( i=0;i<inputNumberProcess;i++)
	{
    	inputDataProcess[i].presenceTime = inputDataProcess[i].timeEnd - inputDataProcess[i].appearTime; // thoi gian hien dien tren CPU 
    	inputDataProcess[i].waitTime = inputDataProcess[i].presenceTime - inputDataProcess[i].executionTime; // thoi gian cho doi
    	inputDataProcess[i].ntat = (float)inputDataProcess[i].presenceTime / inputDataProcess[i].executionTime;
    	totalTimePresence += inputDataProcess[i].presenceTime;
    	totalTimeWait += inputDataProcess[i].waitTime;
    }
    
	timePresenceMedium = totalTimePresence/inputNumberProcess; //thoi gian hien dien CPU trung binh cua cac tien trinh
	timeWaitMedium = totalTimeWait/inputNumberProcess; //thoi gian cho trung binh cua cac tien trinh
	cout << "Note:\t [Name] \t: [Ten Tien Trinh] \n";
	cout << "\t [timeXH] \t: [Moc Thoi Gian Xuat Hien] \n";
	cout << "\t [totalTimeTH] \t: [Thoi Gian Thuc Hien, Xu Ly] \n";
	cout << "\t [timeEnd] \t: [Moc Thoi Gian Hoan Thanh Xong Cong Viec] \n";
	cout << "\t [timeCPU] \t: [Thoi Gian Hien Dien Trong CPU] \n";
	cout << "\t [waitTime] \t: [Thoi Gian Cho Doi CPU Cap Phat] \n";
	cout << "\t [ntat] \t: [Thoi gian hien dien/Thoi gian xu li] \n";
	cout << "---------------------------------------------------------------------------------------------------\n";
    
	printf("Name \t timeXH \t totalTimeTH \t timeEnd \t timeCPU  \t waitTime \t ntat \n");
	for(i=0;i<inputNumberProcess;i++)
	{
		printf("%s \t %d \t\t %d \t\t %d \t\t %d \t\t %d \t\t %f \n",inputDataProcess[i].name,inputDataProcess[i].appearTime,inputDataProcess[i].executionTime,inputDataProcess[i].timeEnd,inputDataProcess[i].presenceTime,inputDataProcess[i].waitTime,inputDataProcess[i].ntat);
	}
	cout << "---------------------------------------------------------------------------------------------------\n";
		
    printf("+ Thoi Gian Hien Dien trong CPU Trung Binh cua cac Tien Trinh : %f \n",timePresenceMedium);
    printf("+ Thoi Gian Cho Trung Binh cua cac Tien Trinh : %f \n",timeWaitMedium);
}


//display_gantt - FCFS , SJT, PRI
void displayGantt(struct data inputDataProcess[],int inputNumberProcess)
{
    int i,j;
    struct data newDataProcess[inputNumberProcess] ;
    struct data tg;
    for( i = 0;i<inputNumberProcess;i++){
        newDataProcess[i] = inputDataProcess[i]; // sao chep lai
    }
    // Sap xep theo [moc time hoan thanh cong viec] tang dan - sort EndTime
    for (i = 0; i < inputNumberProcess-1; i++) 
    {
          int min = i;
          for (j = i+1; j < inputNumberProcess; j++)
            {
                if (newDataProcess[j].timeEnd < newDataProcess[min].timeEnd)  min = j;

            }
         if(min != i){
              tg = newDataProcess[i];
              newDataProcess[i] = newDataProcess[min];
              newDataProcess[min] = tg;
         }
    }
    // End sort EndTime
    
    //display ra man hinh
    for(int i = 0;i < inputNumberProcess; i++)
    {
        if(i == 0) printf("\n\n[Start--(%d)--",newDataProcess[i].appearTime);
        else printf("--(%d)--",newDataProcess[i-1].timeEnd);
        printf("[%s]",newDataProcess[i].name);
    }
    printf("--(%d)--End]\n\n",newDataProcess[inputNumberProcess-1].timeEnd);

}
//SJF - Shortest-Job-First Scheduling 
void SJF(struct data inputDataProcess[],int inputNumberProcess)
{
	int timeCount=0,c; //c,timeCount la bo dem time tang dan va qua trinh la de luu tru cac qua trinh da xuat hien
	int i =0, maxProgressOccurred = 0; // [tien trinh gan nhat da xuat hien] se luu vao day
//	cout << "+ Test Thuc Thi Thuat Toan SJF";
//	printf("+ timeCount=%d , totalTime=%d \n",timeCount, totalTime); // check xem da co dung tong thoi gian cua cac tien trinh chua ?
	while(timeCount < totalTime)
	{
//		printf("+ timeCount=%d < totalTime=%d \n",timeCount, totalTime); //check timeCount
        c=0;
        maxProgressOccurred = 0; 
        for(i=0;i < inputNumberProcess; i++)
        {	
    		//luu tru danh sach cac tien trinh da xuat hien - hay dung hon chi can tim ra tienTrinh lon nhat da xuat hien
			if(inputDataProcess[i].appearTime <= timeCount)
            {
                maxProgressOccurred=i+1;
            }
        }
        // luc nay maxProgressOccurred chinh la tien trinh gan nhat da xuat hien
        if(maxProgressOccurred > 0)
         {
            int sttProcessMin=0; // So thu tu cua tien trinh có time thuc hien ngan nhat se dc luu vao day
            int minExecutionTime = inputDataProcess[0].executionTime; //time thuc hien ngan nhat do
            
            // tim ra [tien trinh co thoi gian thuc hien ngan nhat] trong tat cac tien trinh da xuat hien
            for(i=1;i<maxProgressOccurred;i++)
            {
                if(minExecutionTime > inputDataProcess[i].executionTime)
                {
                    sttProcessMin=i;
                    minExecutionTime = inputDataProcess[i].executionTime;
                }
            }
            printf("+ sttProcessMin=%d, minExecutionTime=%d \n", sttProcessMin, minExecutionTime);
            //end vong lap - Tim dc [tien trinh co thoi gian thuc hien ngan nhat]
            
            timeCount += inputDataProcess[sttProcessMin].executionTime; //sttProcessMin la qua trinh voi thoi gian phuc vu toi thieu
            inputDataProcess[sttProcessMin].timeEnd = timeCount;
            inputDataProcess[sttProcessMin].executionTime += 999; //thiet lap [thoi gian thuc thi] lon de no khong duoc lua chon de so sanh nua
         }
        else
          {
            timeCount++;
          }
	}
	 // Khoi phuc lai gia tri thoi gian thuc hien ban dau cua tien trinh
	for(i=0;i<inputNumberProcess;i++)
      {
        inputDataProcess[i].executionTime -= 999;
      }
    displayTable(inputDataProcess,inputNumberProcess);
}

//PRI_finding
void priorityFinding(struct data inputDataProcess[],int inputNumberProcess) {

  int timeCount = 0; //Bien dem thoi gian, chay tu  0 den totalTime-1, tang len 1

  int i,j;
  while (timeCount < totalTime) {
    j = 0;// Thiet lap lai j = 0
    for (i = 0; i < inputNumberProcess; i++) {
    	//luu danh sach cac tien trinh da xuat hien - hay tim ra TienTrinh xuat hien gan nhat
      if (inputDataProcess[i].appearTime <= timeCount) {
        j = i + 1;
      } 

    }
    if (j > 0) {
      int minPriorityProcess = 0; // stt TienTrinh co do uu tien cao nhat se luu o day
	  int min_pr = inputDataProcess[minPriorityProcess].priority; //min priority - do uu tien nhat
	  
	  // vong lap kiem tra cac tien trinh da xuat hien
      for (i = 1; i < j; i++) {
      	//Kiem tra xe tien trinh sau co do uu tien cao hon ko ?
        if (min_pr > inputDataProcess[i].priority) {
          minPriorityProcess = i; //luu tien trinh dang co [do uu tien] cao hon
          min_pr = inputDataProcess[i].priority; // Thiet lap do uu tien cao nhat
        } 
		else if (min_pr == inputDataProcess[i].priority)
		{
			// neu do uu tien bang nhau thi check xem TienTrinh nap xuat hien truoc
			 if (inputDataProcess[minPriorityProcess].appearTime > inputDataProcess[i].appearTime) 
			 {
	            minPriorityProcess = i; //luu tien trinh dang co [do uu tien] cao hon
	            min_pr = inputDataProcess[i].priority;//Neu cung do uu tien thi tien trinh nao den som hon thi min_pr = do uu tien cua tien trinh do
         	 } 
		    else if (inputDataProcess[minPriorityProcess].appearTime == inputDataProcess[i].appearTime) 
			{
				//neu [do uu tien] va [time xuat hien] deu bang nhau thi check [time thuc thi]
	            if (inputDataProcess[minPriorityProcess].executionTime > inputDataProcess[i].executionTime) 
				{
		            minPriorityProcess = i;
		            min_pr = inputDataProcess[i].priority;// Neu cung thoi gian den luon thi min_pr = do uu tien cua tien trinh co [thoi gian xu li] nho hon
            }
          }
		}
         

        }//end for, ket thuc vong for nay, tien trinh nao dat 3 tieu chi: do uu tien, thoi gian den som, thoi gian xu ly it nhat
        
       //Trong cac tien trinh da den duoc lua chon de cap CPU
      timeCount += inputDataProcess[minPriorityProcess].executionTime; //time += thoi gian thuc thi cua tien trinh da chon o tren
      inputDataProcess[minPriorityProcess].timeEnd = timeCount; // [Thoi gian hoan thanh tien trinh] vua chon = timeCount dang chay den
      inputDataProcess[minPriorityProcess].priority += 999; //thiet lap do uu tien de ko chon lai khi lap lai vong lap, loai bo tien trinh nay, ko so sanh nua
      inputDataProcess[minPriorityProcess].appearTime += 999; //thiet lap thoi gian den lon de ko dua vao thoi gian den cua no de lua chon nua

    }
	else 
	{
      timeCount++; // Khi cac tien trinh chua den thi tang time len 1 don vi
    }

  }
  for (i = 0; i < inputNumberProcess; i++) {
    inputDataProcess[i].priority -= 999;
    inputDataProcess[i].appearTime -= 999;
  } // Thiet lap lai gia tri ban dau cua cac tien trinh
  priorityDisplayTable(inputDataProcess,inputNumberProcess);
}



//PRI_display_Table
void priorityDisplayTable(struct data inputDataProcess[],int inputNumberProcess) {
   cout<<endl<<endl<<"+ Thong tin lap lich theo thuat toan Do uu tien: \n\n";
  int i =0,j = 0;
  for (i = 0; i < inputNumberProcess; i++) {
    inputDataProcess[i].presenceTime = inputDataProcess[i].timeEnd - inputDataProcess[i].appearTime;
    inputDataProcess[i].waitTime = inputDataProcess[i].presenceTime - inputDataProcess[i].executionTime;
    inputDataProcess[i].ntat = (float) inputDataProcess[i].presenceTime / inputDataProcess[i].executionTime;    
    totalTimePresence += inputDataProcess[i].presenceTime;
    totalTimeWait += inputDataProcess[i].waitTime;
  }

	timePresenceMedium = totalTimePresence/inputNumberProcess; //thoi gian hien dien CPU trung binh cua cac tien trinh
	timeWaitMedium = totalTimeWait/inputNumberProcess; //thoi gian cho trung binh cua cac tien trinh
  
 	cout << "Note:\t [Priority] \t: [Do Uu Tien] \n";
 	cout << "\t [Name] \t: [Ten Tien Trinh] \n";
	cout << "\t [timeXH] \t: [Moc Thoi Gian Xuat Hien] \n";
	cout << "\t [totalTimeTH] \t: [Thoi Gian Thuc Hien, Xu Ly] \n";
	cout << "\t [timeEnd] \t: [Moc Thoi Gian Hoan Thanh Xong Cong Viec] \n";
	cout << "\t [timeCPU] \t: [Thoi Gian Hien Dien Trong CPU] \n";
	cout << "\t [waitTime] \t: [Thoi Gian Cho Doi CPU Cap Phat] \n";
	cout << "\t [ntat] \t: [Thoi gian hien dien/Thoi gian xu li] \n";
	cout << "---------------------------------------------------------------------------------------------------------------\n";
    
	printf("Priority \t Name \t timeXH \t totalTimeTH \t timeEnd \t timeCPU  \t waitTime \t ntat \n");
	for(i=0;i<inputNumberProcess;i++)
	{
		printf("%d \t\t %s \t %d \t\t %d \t\t %d \t\t %d \t\t %d \t\t %f \n", inputDataProcess[i].priority, inputDataProcess[i].name,inputDataProcess[i].appearTime,inputDataProcess[i].executionTime,inputDataProcess[i].timeEnd,inputDataProcess[i].presenceTime,inputDataProcess[i].waitTime,inputDataProcess[i].ntat);
	}
	cout << "---------------------------------------------------------------------------------------------------------------\n";
	printf("+ Thoi Gian Hien Dien trong CPU Trung Binh cua cac Tien Trinh : %f \n",timePresenceMedium);
	printf("+ Thoi Gian Cho Trung Binh cua cac Tien Trinh : %f \n",timeWaitMedium);
}

//SRT 
void SRT(struct data inputDataProcess[],int inputNumberProcess)
{
	// noi luu lai gia tri de dung xay dung bieu do gantt
	int timeGnatt[100], countGnatt=0; // luu lai cac moc time
	int processGnattArr[100]; //stt cua cac tienTrinh
	int saveProcess; ////stt cua tienTrinh hien tai
	
	timeGnatt[countGnatt] = inputDataProcess[0].appearTime;
    processGnattArr[countGnatt] = 0;
    saveProcess = 0;
//    printf("+ %s, Time=%d \n", inputDataProcess[saveProcess].name, timeGnatt[countGnatt]); //check gnatt 1
    countGnatt++;
    
	//srt
	int remainTimeArr[inputNumberProcess]; // Thoi gian con lai cua cac tien trinh
	int TimeLandmarkArr[inputNumberProcess + 1]; // moc thoi gian de check lai [time thuc thi con lai] cua cac tien trinh
	for(int i = 0; i<inputNumberProcess; i++)
	{
		remainTimeArr[i]=inputDataProcess[i].executionTime;
		TimeLandmarkArr[i]=inputDataProcess[i].appearTime;
//		printf("remainTime[%d]=%d ; TimeLandmarkArr[%d]=%d\n",i+1, inputDataProcess[i].executionTime,i+1, inputDataProcess[i].appearTime);
	}
	TimeLandmarkArr[inputNumberProcess] = totalTime; // moc time lon nhat
	int saveSttTimeLandmark=0; //Ban dau moc tai vi tri dau tien
//	int timeLandmark = TimeLandmarkArr[saveSttTimeLandmark]; // moc thoi gian xet
	
	
	int timeCount=0,c; //c,timeCount la bo dem time tang dan va qua trinh la de luu tru cac qua trinh da xuat hien
	int i =0, maxProgressOccurred = 0; // [tien trinh gan nhat da xuat hien] se luu vao day
//	cout << "+ Test Thuc Thi Thuat Toan SRT\n";

	while(timeCount < totalTime && timeCount <= TimeLandmarkArr[saveSttTimeLandmark])
	{
//		printf("\n------ timeCount=%d <= timeLandmark=%d -----\n",timeCount, TimeLandmarkArr[saveSttTimeLandmark]); //check timeCount
        c=0;
        maxProgressOccurred = 0;
        for(i=0;i < inputNumberProcess; i++)
        {	
    		//luu tru danh sach cac tien trinh da xuat hien - hay dung hon chi can tim ra tienTrinh lon nhat da xuat hien
			if(inputDataProcess[i].appearTime <= timeCount)
            {
                maxProgressOccurred=i+1;
            }
        }
        // luc nay maxProgressOccurred chinh la tien trinh gan nhat da xuat hien
        if(maxProgressOccurred > 0)
         {
            int sttProcessMin=0; // So thu tu cua tien trinh có [time thuc hien con lai] ngan nhat se dc luu vao day
            int minRemainTime = remainTimeArr[0]; //[time thuc hien con lai] ngan nhat do
            
            // tim ra [tien trinh co thoi gian thuc hien con lai ngan nhat] trong tat cac tien trinh da xuat hien
            for(i=1;i<maxProgressOccurred;i++)
            {
                if(minRemainTime > remainTimeArr[i])
                {
                    sttProcessMin=i;
                    minRemainTime = remainTimeArr[i];
                }
            }
//            printf("+ %s, minRemainTime=%d \n", inputDataProcess[sttProcessMin].name, minRemainTime);
            //end vong lap - Tim dc [tien trinh co thoi gian thuc hien ngan nhat]
            
            //gantt
            if(saveProcess != sttProcessMin)
            {
            	timeGnatt[countGnatt] = timeCount; // moc thoi gian
   				processGnattArr[countGnatt] = sttProcessMin; // tien trinh moi
    			saveProcess = processGnattArr[countGnatt];
//    			printf("+ %s, Time=%d \n", inputDataProcess[saveProcess].name, timeCount); //check gnatt 2
    			countGnatt++;
			} 
			//end gantt          
            
            remainTimeArr[sttProcessMin]--; // chay dc 1s nen time con lai giam
//            printf("+ remainTime[%d]=%d\n", sttProcessMin, remainTimeArr[sttProcessMin]);
            timeCount++;
            //kiem tra xem TienTRinh da xong chua
            if(remainTimeArr[sttProcessMin] == 0) 
            {
            	inputDataProcess[sttProcessMin].timeEnd = timeCount;
//            	inputDataProcess[sttProcessMin].executionTime += 999; //thiet lap [thoi gian thuc thi] lon de no khong duoc lua chon de so sanh nua
				remainTimeArr[sttProcessMin]=999; ////thiet lap [thoi gian thuc thi con lai] lon de no khong duoc lua chon de so sanh nua
			}
            	           
         }
        else
          {
            timeCount++;
          }
        //kiem tra moc time
        if(timeCount > TimeLandmarkArr[saveSttTimeLandmark] )
        {
        	saveSttTimeLandmark++; // tang len moc time tiep theo
//        	printf("+ saveSttTimeLandmark=%d\n", saveSttTimeLandmark);
		}
	}
	//show table
    displayTable(inputDataProcess,inputNumberProcess);
    
    //show gnatt
    timeGnatt[countGnatt]=totalTime; //time ket thuc
    cout << "\n[Start--";
    printf("(%d)", timeGnatt[0] );
    for(int i=0; i<countGnatt; i++)
    {
    	printf("--[%s]--(%d)", inputDataProcess[processGnattArr[i]].name, timeGnatt[i+1] );
    	
	}
	 cout << "--End]";
	 //end show gantt
    
}



//round bind
void push(int stt) {
  queue[rear++] = stt;
  //rear%=n;
  m++;
}
int pop() 
{
  s++;
  int x;
  x = queue[front++];
  return x;
}

void check(struct data inputDataProcess[],int inputNumberProcess) 
{
	//khi tien moi xuat hien thi no de day vao hang doi
  while (inputDataProcess[stt].appearTime <= timeCount && stt < inputNumberProcess) //tat ca qua trinh phai duoc kiem tra  day qua trinh duoc thuc hien hien tai vao hang doi
  {
    numberProcessQueue++;
    push(stt++);
  }
}

void RR_finding(struct data inputDataProcess[],int inputNumberProcess) 
{
	// noi luu lai gia tri de dung xay dung bieu do gantt
	int timeGnatt[100], countGnatt=0; // luu lai cac moc time
	int processGnattArr[100]; //stt cua cac tienTrinh
	int saveProcess; ////stt cua tienTrinh hien tai
	
	timeGnatt[countGnatt] = inputDataProcess[0].appearTime;
    processGnattArr[countGnatt] = 0;
    saveProcess = 0;
//    printf("+ %s, Time=%d \n", inputDataProcess[saveProcess].name, timeGnatt[countGnatt]); //check gnatt 1
    countGnatt++;

//  int temp_st[inputNumberProcess];
  int remainTimeArr[inputNumberProcess]; // Thoi gian thuc thi con lai cua cac tien trinh 
  int countQ = 0; // dem xem time tien trinh moi <= quantum chua?
  int p_process; //p_process la stt tien trinh hien tai
  int flag = 0; //flag de danh dau tien trinh do da duoc chon
  stt = 0;
  int quantum;//quantum
  printf("Nhap Gia Tri quantum (q):\n");
  scanf("%d", & quantum);
  
  for (int i = 0; i < inputNumberProcess; i++) {
    remainTimeArr[i] = inputDataProcess[i].executionTime;// Mang remainTimeArr chua thoi gian thuc hien cua cac tien trinh
  }

  timeCount = inputDataProcess[0].appearTime; //varibble for round_bind

  numberProcessQueue = 1;
  push(stt++);
//	  void push(int q) 
//	  	{
//		  queue[rear++] = q;
//		  m++;
//		}
  while (timeCount <= totalTime) {
  	//ie i enetrs if a process is already selected or a new process can be selected
    if (flag == 1 || numberProcessQueue != 0) //flag de danh dau tien trinh do da duoc chon , 0 la chua
    {
      if (flag == 0 && countQ == 0) 
	  {
        p_process = pop(); //queue[front] - lay tien trinh dang hang doi
				//        int pop() 
				//			{
				//			  s++;
				//			  int x;
				//			  x = queue[front++];
				//			  return x;
				//			}
        //p_process=i;
        countQ = 0; // La tien trinh moi nen reset quatum = 0
        flag = 1; //flag de danh dau tien trinh do da duoc chon, 1 la roi

      }
      remainTimeArr[p_process]--; //Thoi gian thuc thi con lai cua TienTrinh duoc chon giam 1
      
      //Check xem [[Thoi gian thuc thi con lai cua TienTrinh]=0 thi TienTinh da Hoan Thanh
      if (remainTimeArr[p_process] == 0) {
        timeCount++; // timeCount tiep tuc tang
        countQ = 0; //Reset quatum lai
        inputDataProcess[p_process].timeEnd = timeCount; //Tien trinh ket thuc tai timeCount nay
        flag = 0;//flag de danh dau tien trinh do da duoc chon, 0 la chua
        numberProcessQueue--; 
        check(inputDataProcess,inputNumberProcess);
        
        //gantt
            if(saveProcess != p_process)
            {
            	timeGnatt[countGnatt] = timeCount; // moc thoi gian
   				processGnattArr[countGnatt] = p_process; // tien trinh moi
    			saveProcess = processGnattArr[countGnatt];
//    			printf("+ %s, Time=%d \n", inputDataProcess[saveProcess].name, timeCount); //check gnatt 2
    			countGnatt++;
			} 
			//end gantt  
			
        continue;
      }
      countQ++;
      //count=count%quantum;
      
      //checj xem countQ da max = quantum
      if (countQ == quantum) 
	  {
        countQ = 0; //reset
        timeCount++; //timeCount tiep tuc tang
        check(inputDataProcess,inputNumberProcess);
        push(p_process); //cho vao hang doi
        flag = 0; //flag de danh dau tien trinh do da duoc chon, 0 la chua
//        printf("+ %s: timeCount=%d, So tien trinh trong hang doi=%d \n",inputDataProcess[p_process].name, timeCount, numberProcessQueue );

        //gantt
            if(saveProcess != p_process)
            {
            	timeGnatt[countGnatt] = timeCount; // moc thoi gian
   				processGnattArr[countGnatt] = p_process; // tien trinh moi
    			saveProcess = processGnattArr[countGnatt];
//    			printf("+ %s, Time=%d \n", inputDataProcess[saveProcess].name, timeCount); //check gnatt 3
    			countGnatt++;
			} 
			//end gantt    
      } 
	  else 
	  {
        timeCount++;
        check(inputDataProcess,inputNumberProcess);
      }
    } 
	else 
	{
      timeCount++;
      check(inputDataProcess,inputNumberProcess);
    }

  } //end of while loop
  cout<<endl<<endl<<"Thong tin lap lich theo thuat toan Round robin: \n\n";
//  printf("+ timeCount=%d, numberProcessQueue=%d \n", timeCount, numberProcessQueue ); //check
  
  //displayTable
  displayTable(inputDataProcess,inputNumberProcess);
  //show gnatt
    timeGnatt[countGnatt]=totalTime; //time ket thuc
    cout << "\n[Start--";
    printf("(%d)", timeGnatt[0] );
    for(int i=0; i<countGnatt; i++)
    {
    	printf("--[%s]--(%d)", inputDataProcess[processGnattArr[i]].name, timeGnatt[i+1] );
    	
	}
	 cout << "--End]";
	 //end show gantt
}

// end round bind

void about ()
{
	cout << "\nSimple Code by Nguyen Quoc Khanh - BKDN. <3 \n";
  	cout << "CV: khanhnoi.mobie.in\n";
  	cout << "FB: fb.com/khanhnoiIT\n";
}






