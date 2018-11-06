#include <iostream>
#include <fstream>
using namespace std;
void print(int a[3][3]){
  for (int x=0;x<3;x++){
    for (int y=0;y<3;y++){
      cout<<a[x][y]<<" ";
    }
    cout<<endl;
  }
  cout<<endl;
}
int main(int argc,char *argv[]){

  int x0,y0;
  int table[3][3];
  int seed=stoi(argv[1]);
  int move=stoi(argv[2]);
  for (int x=0;x<3;x++){
    for (int y=0;y<3;y++){
      cin>>table[x][y];
      if (table[x][y]==0){
        x0=x;
        y0=y;
      }
    }
  }
  srandom(seed);
  int count=0;
  int action;
  while (count<move){
    action=int((4.0*random()) / (RAND_MAX + 1.0));
    if (action==0){
      if (x0>0){
        table[x0][y0]=table[x0-1][y0];
        table[x0-1][y0]=0;
      }
    }
    else if(action==1){
      if (x0<2){
    		table[x0][y0]=table[x0+1][y0];
    		table[x0+1][y0]=0;
    	}
    }
    else if (action==2){
      if (y0>0){
    		table[x0][y0]=table[x0][y0-1];
    		table[x0][y0-1]=0;
    	}
    }
    else if (action==3){
      if (y0<2){
    		table[x0][y0]=table[x0][y0+1];
    		table[x0][y0+1]=0;
    	}
    }
    for (int x=0;x<3;x++){
      for (int y=0;y<3;y++){
        if (table[x][y]==0){
          x0=x;
          y0=y;
        }
      }
    }

    count++;
  }
  print(table);
  return 0;
}
