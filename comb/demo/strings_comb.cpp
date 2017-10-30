#include <iostream>
#include <string>
#include <vector>
#include "../src/combi.h"
using namespace std;

int main()
{

    std::vector<std::string> mystrings = {"AB","CD","EF","GH", "HI","JK","LM","NO" };
    // N is mystrings.size()
    int r=5;
    combinations<string> comb_obj (mystrings,r);
    while ( comb_obj.has_next() ){
	const std::string* stuple = comb_obj.next_combination();
	for (int i=0; i<r; i++){
	    cout << stuple[i] << " ";
	}
	cout << endl;
    }

    cout <<"\tpossibilities: " << comb_obj.get_count() << endl;


}


//	    OUTPUT: 
/*

AB CD EF GH HI 
AB CD EF GH JK 
AB CD EF GH LM 
AB CD EF GH NO 
AB CD EF HI JK 
AB CD EF HI LM 
AB CD EF HI NO 
AB CD EF JK LM 
AB CD EF JK NO 
AB CD EF LM NO 
AB CD GH HI JK 
AB CD GH HI LM 
AB CD GH HI NO 
AB CD GH JK LM 
AB CD GH JK NO 
AB CD GH LM NO 
AB CD HI JK LM 
AB CD HI JK NO 
AB CD HI LM NO 
AB CD JK LM NO 
AB EF GH HI JK 
AB EF GH HI LM 
AB EF GH HI NO 
AB EF GH JK LM 
AB EF GH JK NO 
AB EF GH LM NO 
AB EF HI JK LM 
AB EF HI JK NO 
AB EF HI LM NO 
AB EF JK LM NO 
AB GH HI JK LM 
AB GH HI JK NO 
AB GH HI LM NO 
AB GH JK LM NO 
AB HI JK LM NO 
CD EF GH HI JK 
CD EF GH HI LM 
CD EF GH HI NO 
CD EF GH JK LM 
CD EF GH JK NO 
CD EF GH LM NO 
CD EF HI JK LM 
CD EF HI JK NO 
CD EF HI LM NO 
CD EF JK LM NO 
CD GH HI JK LM 
CD GH HI JK NO 
CD GH HI LM NO 
CD GH JK LM NO 
CD HI JK LM NO 
EF GH HI JK LM 
EF GH HI JK NO 
EF GH HI LM NO 
EF GH JK LM NO 
EF HI JK LM NO 
GH HI JK LM NO 
	possibilities: 56

*/

