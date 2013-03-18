// tuple sorting
#include <iostream>     // std::cout
#include <tuple>        // std::tuple, std::get, std::tie, std::ignore
#include <random>
#include <functional>
#include <time.h>
#include <algorithm>
#include <array>
using namespace std;

typedef tuple<double, double, int> coord_type;

struct co_struct {
  double x;
  double y;
  int idx;
};

bool mycomp(coord_type a,coord_type b)
{
  if(get<0>(a) == get<0>(b))
    return (get<1>(a) == get<1>(b));
  return (get<0>(a) < get<0>(b));
}

bool struct_comp(co_struct l, co_struct r)
{
  if (l.x == r.x)
    return (l.y < r.y);
  return (l.x < r.x);
}

int main()
{
  double lower_bound = 0;
  double upper_bound = 1;
  uniform_real_distribution<double> unif(lower_bound,upper_bound);
  default_random_engine re;
  default_random_engine::result_type const seedval = time(NULL);
  re.seed(seedval);
  const int nInput = 5;
  double aa;
  double bb;
  array<tuple<double,double,int>,nInput> coord2;
  array<int,nInput> cpparr;
  array<co_struct,nInput> coord1;
  aa = unif(re);
  bb = unif(re);
  for(int i=0; i<nInput; i++){
    aa = unif(re);
    bb =1+ unif(re);
    get<0>(coord2[i])=aa;
    get<1>(coord2[i])=bb;
    get<2>(coord2[i])=i;
    coord1[i].x=aa;
    coord1[i].y=bb;
    coord1[i].idx=i;
    cpparr.at(i)=3-i;
  }
  //cout << get<2>(coord2[0]) << endl;
  cout << cpparr.size() << endl;
  cout << coord2.begin()<<endl;
  for( int i=0; i< nInput; i++)
    {
      cout << "The coordinates in struct are: " << coord1[i].x << " and " 
       << coord1[i].y << " The index is: " << coord1[i].idx << endl;
    }
  cout << "The first coordinates are: " << get<0>(coord2[0]) << " and " 
       << get<1>(coord2[0]) << " The index is: " << get<2>(coord2[0]) << endl;

  cout << struct_comp(coord1[0],coord1[1])<<endl;
  sort(cpparr.begin(),cpparr.end());
  sort(coord1.begin(),coord1.end(),struct_comp);
  sort(coord2.begin(),coord2.end(),mycomp);

 for( int i=0; i< nInput; i++)
    {
      cout << "The coordinates in struct after sort are: " << coord1[i].x << " and " 
       << coord1[i].y << " The index is: " << coord1[i].idx << endl;
    }

 cout << "Now Let's see the tuple sort:" << endl;

 for( int i=0; i< nInput; i++)
    {
      cout << "The coordinates in struct after sort are: " << get<0>(coord2[i]) << " and " 
	   << get<1>(coord2[i]) << " The index is: " << get<2>(coord2[i]) << endl;
    }


  // cout << "The first coordinates after sort are: " << get<0>(coord2[0]) << " and " 
  //      << get<1>(coord2[0]) << " The index is: " << get<2>(coord2[0]) << endl;
   
}
