#include<iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<iomanip>
using namespace std;

int index1[100],indexadd[100];
int nor;
void smi()
{
int temp,temp1;
int i,j;
for(i=0;i<nor;i++)
for(j=i+1;j<nor;j++)
if(index1[i]>index1[j])
{
temp=index1[i];
index1[i]=index1[j];
index1[j]=temp;
temp1=indexadd[i];
indexadd[i]=indexadd[j];
indexadd[j]=temp1;
}
}


class student{
public:
int tr_id;
char Name[15],Fr_add[50],To_add[50],bkdt[15],Status[15];
void add1();
void add1(int,char*,char*,char*,char*,char*);
void dis(int);
void unpack(int add);
void retrieve();
void search();
void search2();
void del();
void del(int);
void dis();
void mod();
void update();
void load();
};


void student::add1()
{
char buff[150];
fstream file("record.txt",ios::out|ios::app);
fstream file2("index.txt",ios::out|ios::app);
cout<<"Enter the tr_id ,Name , Fr_add , To_add , booking date and Status\n";
cin>>tr_id;

cin>>Name>>Fr_add>>To_add>>bkdt>>Status;
strcpy(buff,Name);
strcat(buff,"|");
strcat(buff,Fr_add);
strcat(buff,"|");
strcat(buff,To_add);
strcat(buff,"|");
strcat(buff,bkdt);
strcat(buff,"|");
strcat(buff,Status);
strcat(buff,"|");
std::string p;
index1[++nor]=tr_id;
file.seekg(0,ios::end);
indexadd[nor]=file.tellp();
file2<<tr_id<<"|"<<file.tellp()<<endl;
file<<tr_id<<buff;
fstream fil;
//cout<<"nor value in add function  is"<<nor<<endl;
 fil.open("nor.txt",ios::out); fil<<nor;	
smi();

}




///////////////////////retieve
void  student::retrieve(){
int ch;
student s;
cout<<"1.Parcels yet to be picked\n2.Shipment in Transit\n3.Delievered \n4.exit"<<endl;
cin>>ch;
switch(ch){
case 1:s.dis(ch);break;
case 2:s.dis(ch);break;
case 3:s.dis(ch);break;
case 4 :{exit(0);}
}
}


void student::dis(int q)
{
int i;
int add;
student s;
s.load();
for(i=0;i<nor;i++)
{
add=indexadd[i];
unpack(add);
if(q==1 && !strcmp(Status,"pickup"))
cout<<"tr_id: "<<tr_id<<"\tName: "<<Name<<"\tFr_add: "<<Fr_add<<"\tTo_add: "<<To_add<<"\t Bookind Date: "<<bkdt<<"\tStatus: "<<Status<<endl;
else if(q==2 && !strcmp(Status,"transit"))
cout<<"tr_id: "<<tr_id<<"\tName: "<<Name<<"\tFr_add: "<<Fr_add<<"\tTo_add: "<<To_add<<"\t Bookind Date: "<<bkdt<<"\tStatus: "<<Status<<endl;

else if(q==3 && !strcmp(Status,"delivered"))
cout<<"tr_id: "<<tr_id<<"\tName: "<<Name<<"\tFr_add: "<<Fr_add<<"\tTo_add: "<<To_add<<"\t Bookind Date: "<<bkdt<<"\tStatus: "<<Status<<endl;

}
}






void student::add1(int tr_id,char* Name,char* Fr_add,char* To_add,char* bkdt,char* ss)
{
char buff[150];
fstream file("record.txt",ios::out|ios::app);
fstream file2("index.txt",ios::out|ios::app);
strcpy(buff,Name);
strcat(buff,"|");
strcat(buff,Fr_add);
strcat(buff,"|");
strcat(buff,To_add);
strcat(buff,"|");
strcat(buff,bkdt);
strcat(buff,"|");
strcat(buff,ss);
strcat(buff,"|");
index1[++nor]=tr_id;
file.seekg(0,ios::end);
indexadd[nor]=file.tellp();
file2<<tr_id<<"|"<<file.tellp()<<endl;
file<<tr_id<<buff;
fstream fil;
//cout<<"nor value in add function  is"<<nor<<endl;
 fil.open("nor.txt",ios::out); fil<<nor;smi();
}





void student::unpack(int add)
{
fstream file("record.txt",ios::in);
file.seekg(add);
file>>tr_id;
file.getline(Name,15,'|');
file.getline(Fr_add,50,'|');
file.getline(To_add,50,'|');
file.getline(bkdt,15,'|');
file.getline(Status,15,'|');
}



void student::search()
{student s;
s.load();
cout<<"Enter the tracking id\n";
int min=0;
int max=nor-1;
int flag=0;
int key;
int mid;
int add;
cin>>key;
while(min<=max && flag==0)
{
mid=(min+max)/2;
if(index1[mid]==key)
{
flag=1;
add=indexadd[mid];
s.unpack(add);
cout<<"tr_id:"<<s.tr_id<<"  Name:  "<<s.Name<<"  Fr_add:  "<<s.Fr_add<<"  To_add  "<<s.To_add<<"  booking Date:  "<<bkdt<<"  Status:  "<<s.Status<<endl;
break;
}
else if(key>index1[mid])
min=mid+1;
else
max=mid-1;
}
if(flag==0)
cout<<"Record not found\n";
}




void student::search2()
{student s;
s.load();
cout<<"Enter the tracking id\n";
int min=0;
int max=nor-1;
int flag=0;
int key;
int mid;
int add;
cin>>key;
while(min<=max && flag==0)
{
mid=(min+max)/2;
if(index1[mid]==key)
{
flag=1;
add=indexadd[mid];
s.unpack(add);
int a=s.tr_id;
char b[15];
strcpy(b,s.Name);
char c[50];
strcpy(c,s.Fr_add);
char e[15];
strcpy(e,s.bkdt);
char d[50];
strcpy(d,s.To_add);
del(a);
char ss[15];
cout<<"Status of Delivery: ";
	cin>>ss;
s.add1(a,b,c,d,e,ss);
break;
}
else if(key>index1[mid])
min=mid+1;
else
max=mid-1;
}
if(flag==0)
cout<<"Record not found\n";
}


void student::del()
{student s;
s.load();
int key;
cout<<"Enter the tr_id for Changes\n";
cin>>key;
int j,i;
for(j=0;j<nor;j++){
if(index1[j]==key)
{
for(i=j;i<nor;i++)
{
index1[i]=index1[i+1];
indexadd[i]=indexadd[i+1];
}
nor--;
}

}
fstream fil;
 fil.open("nor.txt",ios::out); fil<<nor;
fstream fs("index.txt",ios::out);
for(i=0;i<nor;i++)
fs<<index1[i]<<"|"<<indexadd[i]<<endl;
fs.close();
}


void student::del(int tr_id)
{student s;	
s.load();
int key;
key=tr_id;
int j,i;
for(j=0;j<nor;j++){
if(index1[j]==key)
{
for(i=j;i<nor;i++)
{
index1[i]=index1[i+1];
indexadd[i]=indexadd[i+1];
}
nor--;
}
}
fstream fil;
//cout<<"nor value in add function  is"<<nor<<endl;
 fil.open("nor.txt",ios::out); fil<<nor;
fstream fs("index.txt",ios::out);
for(i=0;i<nor;i++)
fs<<index1[i]<<"|"<<indexadd[i]<<endl;
fs.close();
}


void student::dis()
{
int i;
int add;
student s;
s.load();
cout<<"Tr_Id"<<setw(3)<<"|"<<"Name"<<setw(16)<<"|"<<"From_address"<<setw(28)<<"|"<<"To_address"<<setw(30)<<"|"<<"Booked_On"<<setw(6)<<"|"<<"Status"<<endl;
cout<<"-----------------------------------------------------------------------------------------------------------------------------"<<endl;
for(i=0;i<nor;i++)
{
add=indexadd[i];
unpack(add);
cout<<tr_id<<setw(5)<<"|"<<Name<<setw(20-strlen(Name))<<"|"<<Fr_add<<setw(40-strlen(Fr_add))<<"|"<<To_add<<setw(40-strlen(To_add))<<"|"<<bkdt<<setw(15-strlen(bkdt))<<"|"<<Status<<endl;
}
}


void student::load(){
ifstream fil1;
std::string p;
fil1.open("nor.txt");
 while(getline(fil1,p)){/*cout<<p;*/}
nor=atoi(p.c_str());//getting prev no of records
fil1.close();
char a,b;
ifstream fil;
 fil.open("index.txt");
  std::string line;
 std::string token;
 int i=0;
 while (   getline(fil, line,'|')
         && getline(fil, token, '\n')
        ){
 	index1[i]=atoi(line.c_str());
 	indexadd[i]=atoi(token.c_str());
 	i++;

 }
smi();
}


void student::mod()
{
 student s;
	s.del();
	cout<<"Enter the new values;"<<endl;
	s.add1();
}


void student::update(){
student s;
s.search2();
}


int main()
{
int ch;
student s;
s.load();
for(;;)
{
cout<<"\n\n\n1.New Entry \n2.Search Courier \n3.Display \n4.Delete \n5.Modify \n6.Upadate status \n7.Retrieve Records \n8.EXIT\n";
cout<<"Enter your choice\n";
cin>>ch;
switch(ch)
{
case 1:s.add1();break;
case 2:s.search();break;
case 3:s.dis();break;
case 4:s.del();break;
case 5:s.mod();break;
case 6:s.update();break;
case 7:s.retrieve();break;
case 8 :{exit(0);}
}
}
return 0;
}