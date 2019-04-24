#include<stdio.h>

struct job{
	int id;
	int at,bt,ft,rbt;
}f[100], s[100], m[100];

int n, rc=0, sc=0, mc=0;
int quantum_time;

void round_robin(){
	int time= m[0].at, mark=0, cc=0, i, rc;
	while(time!=120 && cc!=mc){
		for(i=0; i<=mark; i++){
			if(m[i].rbt > quantum_time){
				time += quantum_time;
				m[i].rbt -= quantum_time;
			}
			else if(m[i].rbt <=quantum_time && m[i].rbt !=0){
				time += m[i].rbt;
				m[i].rbt =0;
				m[i].ft = time;
				cc++;
			}
			else;
		}
		int start = mark+1;
		for(rc= start; rc<mc; rc++){
			if(m[rc].at <= time){
				mark++;
			}
		}
	}	
}

void gant(){
	int isc=0, ifc= 0, min, flag;
	if( rc!=0  && sc!=0){
		while(isc<sc && ifc<rc){
			if(f[ifc].at == s[isc].at){
				m[mc] = f[ifc];
				mc++;
				ifc++;
				m[mc]= s[isc];
				mc++;
				isc++;
			}
			else if(f[ifc].at < s[isc].at){
				m[mc]= f[ifc];
				mc++;
				ifc++;
			}
			else if(f[ifc].at > s[isc].at){
				m[mc]= s[isc];
				mc++;
				isc++;
			}
			else;
		}
		if(mc != (rc+sc)){
			if(rc!=ifc){
				while(ifc!=rc){
					m[mc]= f[ifc];
					mc++;
					ifc++;
				}
			}
			else if(sc!=isc){
				while(isc!=sc){
					m[mc]= s[isc];
					mc++;
					isc++;
				}
			}
		}
	}
	else if(rc==0){
		while(isc!=sc){
			m[mc]= s[isc];
			mc++;
			isc++;
		}
	}
	else if(sc==0){
		while(ifc!=rc){
			m[mc]= f[ifc];
			mc++;
			ifc++;
		}
	}
	else {
		printf("\n No valid Jobs available\n");
	}
}

void dispaly_fun(){
	int i=0, total=0, sum=0; 
	double avg;
	printf("\n******************PROCESS TABLE*******************\n");
	printf("\nQuery ID\tArrival Time\tRessolving Time\tCompletion Time\tTurn Around Time\tWaiting Time");
	for(i; i<mc; i++){
		printf("\n%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t\t%d",
		m[i].id, (m[i].at+1000), m[i].bt, (m[i].ft+1000), (m[i].ft-m[i].at), ((m[i].ft-m[i].at)- m[i].bt));
		total= m[i].ft;
		sum+= (m[i].ft-m[i].at);
	}
	avg = sum/mc;
	printf("\n\ntotal time for query handeling: %d", total);
	printf("\nAverage query time: %lf", avg);

}

void input_fun(){
	int choice,  i, t;
	printf("Enter total no of queries: "); scanf("%d", &n);
	if(n==0) { printf("\n No queries\n"); }
	else{
		printf("\nEnter quantum_time for each Process: "); scanf("%d", &quantum_time);
		for(i=0; i<n; i++){
			printf("\nfaculty queue/student queue (1/2): "); scanf("%d", &choice);
			if(choice==1){
				printf("Query Id: "); scanf("%d", &f[rc].id);
				printf("Arrival Time: "); scanf("%d", &t);
				if(t<1000 || t>1200){
					printf("\nEnter Correct time");
					input_fun();
				}
				else{f[rc].at= t-1000;}
				printf("burst time: "); scanf("%d", &f[rc].bt);	 f[rc].rbt= f[rc].bt; 
				rc++;
			} else{
				printf("Query Id: "); scanf("%d", &s[sc].id);
				printf("Arrival Time: "); scanf("%d", &t); 
				if(t<1000 || t>1200){
					printf("\nEnter Correct time\n");
					input_fun();
				}
				else {s[sc].at= t-1000; }
				printf("burst time: "); scanf("%d", &s[sc].bt);	 s[sc].rbt= s[sc].bt;
				sc++;
			}
		}
	}
}


 main(){
printf("*****************************WELCOME TO QUERY HANDLING PLATFORM***********************\n\n\n");
printf("\nAll time entered are in minutes\n");
printf("enter arrival time in ascending order\n\n");
	input_fun();
	gant();
	round_robin();
	dispaly_fun();
}
