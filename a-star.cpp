#include <iostream>
#include <iterator>
#include <stdlib.h>
#include <cstdlib>
#include <set>
#include <math.h>
using namespace std;
int goal[3][3]={{0,1,2},{3,4,5},{6,7,8}};
struct Node{
  int table[3][3];
  int id;
  int g;//Path cost
  int score;
  int x0,y0;
  bool goal_reach;
  Node* parent;
  Node* child_left;
  Node* child_right;
  Node* child_up;
  Node* child_down;

  Node(int a[3][3] ,int heu_mode,int g_new,int new_id, Node* parent_p){
    g=g_new;
    id=new_id;
    goal_reach=true;
    //copy table and check goal
    for (int x=0;x<3;x++){
      for (int y=0;y<3;y++){
        table[x][y]=a[x][y];
        if (table[x][y]==0){
          x0=x;
          y0=y;
        }
        if(table[x][y]!=goal[x][y]){
          goal_reach=false;
        }
      }
    }
    //Calculate the heuristic value
    int h;
    if (heu_mode==0){
      h=0;
    }
    else if (heu_mode==1){
      h=0;
      for (int x=0;x<3;x++){
        for (int y=0;y<3;y++){
          if (table[x][y]!=goal[x][y]){
            h=h+1;
          }
        }
      }
    }
    else if (heu_mode==2){
      h=0;
      int goal_x,goal_y;
  		for (int x=0;x<3;x++){
  			for (int y=0;y<3;y++){
  				goal_x=table[x][y]/3;
  				goal_y=table[x][y]%3;
  				h= h + abs(goal_x-x)+abs(goal_y-y);
  			}
  		}
    }
    else if (heu_mode==3){
      h=0;
      int goal_x;
      for (int x=0;x<3;x++){
        for (int y=0;y<3;y++){
          goal_x=table[x][y]/3;
          if (table[x][y]!=goal[x][y]){
            h=h+1+abs(goal_x-x);
          }
        }
      }
    }
    score=h+g;
    parent=parent_p;

    child_down=NULL;
    child_up=NULL;
    child_left=NULL;
    child_right=NULL;
  }
  void print() const{
    for (int x=0;x<3;x++){
  		for (int y=0;y<3;y++){
  			cout<<table[x][y]<<" ";
  		}
  		cout<<endl;
  	}
  	cout<<endl;
  }
};
struct nodecomp {
  bool operator() (const Node* lhs, const Node* rhs) const
  {
    if (lhs->score!=rhs->score){
      return lhs->score<rhs->score;
    }
    else{
      return rhs->id<lhs->id;
    }
  }

};
struct nodecomp2 {
  bool operator() (const Node* lhs, const Node* rhs) const
  {
      return lhs->g<rhs->g;
  }
};
void print(int a[3][3]){
  for (int x=0;x<3;x++){
    for (int y=0;y<3;y++){
      cout<<a[x][y]<<" ";
    }
    cout<<endl;
  }
  cout<<endl;
}
void printSet(set<Node*, nodecomp2> closed_list){
  for (set<Node*,nodecomp>::iterator it=closed_list.begin();it!=closed_list.end();it++){
    (*it)->print();
  }
}

bool isInList(set<Node*, nodecomp> closed_list,int table[3][3]){
  for (set<Node*,nodecomp>::iterator it=closed_list.begin();it!=closed_list.end();it++){
    bool table_equal=true;
    for (int x=0;x<3;x++){
      for (int y=0;y<3;y++){
        if ((*(it))->table[x][y]!=table[x][y]){
          table_equal=false;
        }
      }
    }
    if (table_equal==true){
      return true;
    }
  }
  return false;
}
int main(int argc,char *argv[]){
  int v,d,n;
  set <Node*, nodecomp> closed_list;
  set <Node*, nodecomp> frontier;
  int heu_mode=stoi(argv[1]);
  int id=0;
  int init_table[3][3];
  cin>>init_table[0][0];
  cin>>init_table[0][1];
  cin>>init_table[0][2];
  cin>>init_table[1][0];
  cin>>init_table[1][1];
  cin>>init_table[1][2];
  cin>>init_table[2][0];
  cin>>init_table[2][1];
  cin>>init_table[2][2];

  //Node new_node(init_table,heu_mode,0,id,NULL);
  Node *new_node=new Node(init_table,heu_mode,0,id,NULL);
  id++;
  frontier.insert(new_node);
  v=0;
  while (!(*frontier.begin())->goal_reach){
    v++;
    Node* currentNode;
    currentNode=*(frontier.begin());
    int x0=currentNode->x0;
    int y0=currentNode->y0;

    //Move exploring node to closed list
    closed_list.insert(*(frontier.begin()));
    frontier.erase(frontier.begin());
    //Expanded children
    int left[3][3];
    int right[3][3];
    int up[3][3];
    int down[3][3];
    for (int x=0;x<3;x++){
      for (int y=0;y<3;y++){
        left[x][y]=(currentNode->table)[x][y];
        right[x][y]=(currentNode->table)[x][y];
        up[x][y]=(currentNode->table)[x][y];
        down[x][y]=(currentNode->table)[x][y];
      }
    }


    //----------------------------------------------
    if (x0>0){
      up[x0][y0]=up[x0-1][y0];
      up[x0-1][y0]=0;
    }
    if (x0<2){
  		down[x0][y0]=down[x0+1][y0];
  		down[x0+1][y0]=0;
  	}
    if (y0>0){
  		left[x0][y0]=left[x0][y0-1];
  		left[x0][y0-1]=0;
  	}
    if (y0<2){
  		right[x0][y0]=right[x0][y0+1];
  		right[x0][y0+1]=0;
  	}
    Node* child_left= new Node(left,heu_mode,(currentNode->g)+1,id,currentNode);
    id++;
    Node* child_right= new Node(right,heu_mode,(currentNode->g)+1,id,currentNode);
    id++;
    Node* child_up= new Node(up,heu_mode,(currentNode->g)+1,id,currentNode);
    id++;
    Node* child_down= new Node(down,heu_mode,(currentNode->g)+1,id,currentNode);
    id++;
    currentNode->child_left=child_left;
    currentNode->child_right=child_right;
    currentNode->child_up=child_up;
    currentNode->child_down=child_down;
    //Add apropriate children to frontier
    if (!isInList(closed_list,left)){
      frontier.insert(child_left);
    }
    if(!isInList(closed_list,right)){
      frontier.insert(child_right);
    }
    if (!isInList(closed_list,up)){
      frontier.insert(child_up);
    }
    if (!isInList(closed_list,down)){
      frontier.insert(child_down);
    }
    if (frontier.empty()){
      cout<<"No solution, break"<<endl;
      break;
    }
  }
  Node* temp;
  temp=(*frontier.begin());
  d=temp->g;
  n=closed_list.size()+frontier.size();
  float b;
  b=pow(n,1.0/d);
  cout<<"V="<<v<<endl;
  cout<<"N="<<n<<endl;
  cout<<"d="<<d<<endl;
  cout<<"b="<<b<<endl;
  set <Node*, nodecomp2> answer;
  print(init_table);
  while (temp->parent!=NULL){
    answer.insert(temp);
    temp=temp->parent;
  };
  printSet(answer);

  return 0;
}
