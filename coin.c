#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 14
#define long_size 4782969

typedef struct PATTERN{
  unsigned long hash;
  int now[SIZE];
  int from;
  char how[2];
}pattern;

pattern *history;
int  *hash_table;
int history_cnt = 0;
int queue_bottom;
int Start[SIZE];
int Goal_pattern[SIZE];
char Base[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N'};
int cal[] = {1,3,9,27,81,243,729,2187,6561,19683,59049,177147,531441,1594323};

void save_history(int *p,int from,int empty,int fill);
unsigned long make_hash(int *p);
void exchange_item(int *data,int i,int j);
int solve();
void initialize(char **args,int *Start,int *Goal);



/*//////////////////////////////////////////////////////////////////////////
  function main
//////////////////////////////////////////////////////////////////////////*/
int main(int argn,char *args[])
{
  int last, i,j,cnt=-1;
  hash_table= (int*)calloc(long_size,sizeof(int));
  if(hash_table == NULL)printf("error\n");
  history = NULL;
  initialize(args,Start,Goal_pattern);

  save_history(Start,-1,50,50);
  clock_t start,end;
  start = clock();
  if(solve() == 0)
    {
      puts("no answer");
    }else{
    last = -1;
    while(last != queue_bottom){
      cnt++;
      // printf("%d\n",queue_bottom);
      for(i=queue_bottom; history[i].from != last;)
	{
	  i = history[i].from;  
	}
      last = i;
      if(last != 0){
		printf("%c -> %c\n",history[last].how[0],history[last].how[1]);
      }
    }
  }
  end = clock();
  printf("%d(times)\n%.2lf(sec)\n",cnt,(double)(end-start)/CLOCKS_PER_SEC);
  return 0;
}


/*//////////////////////////////////////////////////////////////////////////
  function save_history
//////////////////////////////////////////////////////////////////////////*/
void save_history(int *p,int from,int empty,int fill)
{
  int i;
  unsigned long hash;
  
  hash = make_hash(p);
  
  if(hash_table[hash] != 1){
    history_cnt++;
    history = (pattern*)realloc(history,sizeof(pattern)*history_cnt);
    history[history_cnt - 1].hash = hash;
    for(i=0;i<SIZE;i++)history[history_cnt - 1].now[i] = p[i];
    history[history_cnt - 1].from  = from;			
    if(empty==50&&fill==50){}
    else{
      history[history_cnt - 1].how[0] = Base[fill];
      history[history_cnt - 1].how[1] = Base[empty];
    }
    hash_table[hash] = 1 ;
    
  }else{return;}
 
  
  
}
/*//////////////////////////////////////////////////////////////////////////
  function make_hash
//////////////////////////////////////////////////////////////////////////*/
unsigned long make_hash(int *p)
{
  unsigned long hash;
  int i;
  double k;
  hash =0;
  for(i=0;i<SIZE;i++)
    {
      hash += p[i]*cal[i];
    }
 
  return hash;
}

/*//////////////////////////////////////////////////////////////////////////
  function exchange_item
//////////////////////////////////////////////////////////////////////////*/
void exchange_item(int *data,int i,int j)
{
  int num,k;
  
  num = data[i];
  data[i] = data[j];
  data[j] = num;

}



/*//////////////////////////////////////////////////////////////////////////
  function solve
//////////////////////////////////////////////////////////////////////////*/
int solve()
{
  int empty;
  unsigned long hash,GOAL;
  int p[SIZE],temp[SIZE],i;


  for(i=0;i<SIZE;i++)p[i]=Start[i];
  
  GOAL = make_hash(Goal_pattern);
  
  queue_bottom = 0;
  while(queue_bottom != history_cnt)
    {
      hash = history[queue_bottom].hash;
      
      if(hash == GOAL)return 1;
      for(i=0;i<SIZE;i++)p[i] = history[queue_bottom].now[i];
      for(empty=0;empty<SIZE;empty++)
	{
	  if(p[empty] == 0)
	    {
	      if(empty==0||empty==7){
		if(p[empty+1]!=0){
		  for(i=0;i<SIZE;i++)temp[i] = p[i];
		  exchange_item(p,empty,empty+1);
		  save_history(p,queue_bottom,empty,empty+1);
		  for(i=0;i<SIZE;i++)p[i] = temp[i];
		}
	      }else if(empty==2||empty==11){
		if(p[empty-1]!=0){
		  for(i=0;i<SIZE;i++)temp[i] = p[i];
		  exchange_item(p,empty,empty-1);
		  save_history(p,queue_bottom,empty,empty+1);
		  for(i=0;i<SIZE;i++)p[i] = temp[i];
		}
		if(p[empty+1]!=0){
		  for(i=0;i<SIZE;i++)temp[i] = p[i];
		  exchange_item(p,empty,empty+1);
		  save_history(p,queue_bottom,empty,empty+1);
		  for(i=0;i<SIZE;i++)p[i] = temp[i];
		}
		if(empty==2){
		  if(p[empty+9]!=0){
		    for(i=0;i<SIZE;i++)temp[i] = p[i];
		    exchange_item(p,empty,empty+9);
		    save_history(p,queue_bottom,empty,empty+1);
		    for(i=0;i<SIZE;i++)p[i] = temp[i];
		  }
		}else{
		  if(p[empty-9]!=0){
		    for(i=0;i<SIZE;i++)temp[i] = p[i];
		    exchange_item(p,empty,empty-9);
		    save_history(p,queue_bottom,empty,empty+1);
		    for(i=0;i<SIZE;i++)p[i] = temp[i];
		  }
		}
	      }else if(empty==6||empty==13){
		if(p[empty-1]!=0){
		  for(i=0;i<SIZE;i++)temp[i] = p[i];
		  exchange_item(p,empty,empty-1);
		  save_history(p,queue_bottom,empty,empty-1);
		  for(i=0;i<SIZE;i++)p[i] = temp[i];
		}
	      }else {
		if(p[empty-1]!=0){
		  for(i=0;i<SIZE;i++)temp[i] = p[i];
		  exchange_item(p,empty,empty-1);
		  save_history(p,queue_bottom,empty,empty+1);
		  for(i=0;i<SIZE;i++)p[i] = temp[i];
		}
		if(p[empty+1]!=0){
		  for(i=0;i<SIZE;i++)temp[i] = p[i];
		  exchange_item(p,empty,empty+1);
		  save_history(p,queue_bottom,empty,empty+1);
		  for(i=0;i<SIZE;i++)p[i] = temp[i];
		}
	      }
      
	    }
	}
      queue_bottom++;
    }
  
  return 0;
}



void initialize(char **args,int *Start,int *Goal)
{
  char *moji = args[1];
  int i,j,k;
  // initialize array
  for(i =0 ;i<SIZE ;i++)
    {
      Start[i] = 0;
      Goal[i] = 0;
    }


  for(i=1;i<5;i++)
    {
      for(j=0;j<SIZE;j++)
	{
	  for(k=0;k<5;k++){
	    if( moji[k-1] == Base[j])
	      {
		if(i%2 !=0){
		  if(i==1){
		    Start[j]=2;
		  }else{
		    Goal[j]=2;
		  }
	       
		}else{
		  if(i==2){
		    Start[j]=1;
		  }else{
		    Goal[j]=1;
		  }
	      
		}
	     
	      }
	  }
	}
      moji = args[i+1];
    }

}
