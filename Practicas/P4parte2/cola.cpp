/* STL queue and priority queue examples */

#include <iostream>
#include <queue>

using namespace std;

/* define a Height class */
class Height{
  public:
    Height() {};                                      //default constructor
    Height(int x, vector<int> y) { cota = x; ciudades = y; }    //constructor
    bool operator<(const Height&) const;              //overloaded < operator

    int cota() const { return cota; }             //accessor methods
    vector<int> ciudades() const { return ciudades; }

  private:
    int cota;
    vector<int> ciudades;                                 //data fields
};

/* overload the less-than operator so priority queues know how to compare two Height objects */
bool Height::operator<(const Height& right) const{
  return cota<right.cota;
}

/* example of a priority queue using the Height class */
void functionD(){
  priority_queue <Height> pq;      //pq is a priority queue of Height objects

  Height x;

  x = Height(10,20);               //put 10'20", 11'0", 8'25", and 9'4" into the priority queue
  pq.push(x);
  x = Height(11,0);
  pq.push(x);
  x = Height(8,25);
  pq.push(x);
  x = Height(9,4);
  pq.push(x);

  cout<<"pq contains " << pq.size() << " elements.\n";

  while (!pq.empty()) {
    cout << pq.top().get_feet()                             //print out the feet and inches of the highest
         << "' " << pq.top().get_inches() << "\"" << endl;  //priority Height object in the priority queue
    pq.pop();                                               //remove the highest priority element
  }
}

int main()
{

  cout << "calling functionD...\n";
  functionD();

  return 0;
}


