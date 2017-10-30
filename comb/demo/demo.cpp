#include <string>
#include <iostream>

#include "../src/combi.h"
using std::cout;
using std::endl;
using std::vector;
using std::string;


// INTEGERS DEMO

int main(int argc, const char **argv);
void usage()
{
cout << " usage: ./comb [min] [max] [choose] \n";
cout << "   eg: ./comb 1 3 2 \n";
    const char* help_args[] = {"k", "1","3","2" };
    main(3, help_args);
}


int main(int argc, const char **argv)
{
    if (argc<3){
    usage();
    return 1;
    }
    
    int min_d, max_d, choose;
    
    try {

	min_d = stoi(string(argv[1]));
	max_d = stoi(string(argv[2]));
	choose = stoi(string(argv[3]));

    } catch (...) {
    cout << "invalid input.\n";
    usage();
    return 1;
    }

    vector<int> iset; //input set 
    for (int i=0; i<(max_d-min_d+1); i++){

        iset.push_back(min_d+i); //fill the input set
    }


    try{
	combinations<int> comb_obj(iset, choose);
	
	while ( comb_obj.has_next() ){
	    const int* current_tuple = comb_obj.next_combination();
	    cout << "\t";
	    for (int i=0; i<choose; i++){
		if (i)
		    cout << ", ";
		cout << current_tuple[i];
	    }
	    cout << endl;
	}

	cout << iset.size() << " C " << choose
	 << " combinations: " << comb_obj.get_count()<<endl;
    
    } catch (int e){
	
	if (e==-7)
	    cout << "error, can't choose more elements than in the set.\n";
	else
	    cout << "error, something went slightly wrong.\n";
	return 1;
    } catch (...){

        cout << "error, something went really wrong.\n";
	return 1;
    }

return 0;

}
