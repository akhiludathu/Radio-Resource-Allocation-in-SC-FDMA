#include<iostream>
#include<limits.h>
#include<stdlib.h>
#include<time.h>

using namespace std;

struct RB
{
   int match;
   int snr;
   int allocated;
};

struct UE
{
    int gbr;
    int num;
    int match;
    int allocated;
    int inlist;
};

RB arrrb[100];
UE arrue[50];
int U[50][100], R[50][100];

class prq
{
    int data[100], front, rear;

public: 
    int rb;

    prq()
    {
        front = -1;
        rear = -1;
    }
    
    void enqueue(int val)
    {
      if(front == -1)
      { front = 0; rear = 0;
        data[rear] = val;
      }
          else
          {
            rear = (rear+1)%100;
            data[rear] = val;
          }    
    }
    
    void print()
    {
    	for(int i =front;i<=rear;i++)
    	{
    		if(front!=-1)
    		{
    			cout<<data[i]<<"    ";
    		}
		}
		cout<<endl;
	}
    
    int dequeue()
    {
      if(front == -1)
        return -1;

          else
          {
            int i, pos=-1, min= INT_MAX;
            
            for(i=front; i<=rear; i++)
                {
                    if(min>R[data[i]][rb])
                    { min = R[data[i]][rb];
                      pos = i; 
                    }    
                }
            
            front = -1;
            rear = -1;
            
            return pos;
          }                
    }
    
    int isempty()
    {
        if(front == -1)
          return 1;
           
          else
              return 0;
    }      
}wl[100];
 
int getRB(int nrb, int ue)
{
   int i, pos= -1;
   int max = INT_MIN; 
   
   for(int i=0; i<nrb; i++)
       if(max<U[ue][i] && !arrrb[i].allocated)
          { max = U[ue][i];
            pos = i;
          }
           
    return pos;
}

int sum();

void matching(int nue, int nrb)
{
    int rb[nue],j,ue;
    
    for(int i=0;i<nue;i++) // for every ue, choose rb with highest and rb will add it to it's waiting list
    {
        rb[i] = getRB(nrb, i);
        wl[rb[i]].enqueue(i);
    }
    
    for(int i=0;i<nrb;i++)
    {
    	cout<<i<<": ";
    	wl[i].print();
	}
    
    while(sum()<nue && sum()!=nrb) //while there are somme UEs in waiting list 
    {
        for(int i=0;i<nrb;i++)
        {
            if(!wl[i].isempty())
            {
                ue = wl[i].dequeue();
                arrrb[i].match = ue;
                cout<<i<<"   "<<ue<<endl;
                arrrb[i].allocated = 1; 
            }
        }
        
        for(int i=0;i<nue;i++)
        {
            if(arrue[i].allocated==0)
            {
                rb[i] = getRB(nrb,i);
                wl[rb[i]].enqueue(i);
            }
        }   
    }
        
}

int sum()
{
    int s=0;
    for(int i=0;i<50;i++)
    {
        s = s+ arrue[i].allocated;
    }
    
    return s;
}
  
    
          
    
int main()
{ 
    srand(time(NULL));
    for(int i=0;i<100;i++)
    {
        arrrb[i].match =-1;
        arrrb[i].snr = rand()%100;
        arrrb[i].allocated = 0;
    }
    
    for(int i=0;i<50;i++)
    {
        arrue[i].allocated =0;
        arrue[i].num = rand()%5 + 1;
        arrue[i].match =-1;
        if(i<=20)
            arrue[i].gbr =1;
        else if(i<40)
            arrue[i].gbr =2;
        else
            arrue[i].gbr =3;
    }
    
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<10;j++)
           {
               U[i][j]= rand()%100;
               R[i][j] = rand()%100;
           }
    }
    
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<10;j++)
           {
               cout<<U[i][j]<<"\t";
           }
        cout<<endl;
    }
    cout<<endl<<endl;
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<10;j++)
           {
               cout<<R[i][j]<<"\t";
           }
        cout<<endl;
    }
    
    for(int i=0; i<50; i++)
    {
    	wl[i].rb = i;
	}
    matching(5,10);
    
    for(int i=0;i<5;i++)
    {
    	cout<<arrue[i].match;
	}
}    

   


