
// an implementation of modular exponentiation, it works.                 i think.


#include <iostream>
#include <vector>

#include <string>
#include <iomanip>

using namespace std;

typedef long long llong;

int get_input( int argc, const char** argv, llong& power, llong& base, llong& mod )
{
    constexpr int buflen = 150;
    char buff[buflen];
    const char *a = buff, *p = buff + 1*buflen/3, *m = buff + 2*buflen/3;
    if (argc > 3){
        a=argv[1];
        p=argv[2];
        m=argv[3];
    }
    else{
        cout << " enter integers in the form: [base] [power] [mod]\n meaning base^power%mod \n>";
        cin >> setw(buflen/3-1) >> buff+0 >> buff+1*buflen/3 >> buff+2*buflen/3;
        buff[buflen-1]='\0';
    }

    try {
        power = stoll(p);
        base = stoll(a);
        mod = stoll(m);
    } catch ( const std::invalid_argument& e ){
        cout << "std::invalid_argument\n";
        return 0;
    } catch ( const std::out_of_range& ){
        cout << "std::out_of_range\n";
        return 0;
    }
    
   if ( !base || !mod || power<=0 )
       return 0; //invalid input

   return 1;

}


constexpr llong LLONG_BITS = 64;

llong mod_exp( llong base, llong p, llong mod )
{
    int power_idx = LLONG_BITS;
    llong tmp_power = p;
    vector<llong> partials = {}; //storing them when they are relevant
    llong bitmask = 1;

    if (!mod)
        return -1;

    llong current_power_mod = base % mod;
    if (!current_power_mod)
        return 0;

    while ( --power_idx > 0 )
    {
        if(!tmp_power)
            break;

        if ( p & bitmask  ){
            partials.push_back( current_power_mod );
        }

        current_power_mod *= current_power_mod;
        current_power_mod %= mod;
        bitmask <<= 1;

    }

    llong result = 1;
    for ( llong part : partials ){
        result *= part;
        result %= mod;
    }
    return result;
}

int main( int argc, const char** argv )
{

llong power,base,mod,result=0;
    if ( !get_input( argc, argv, power, base, mod ) ){
        cout << "invalid input.\n";
        return 1;
    }
    cout << " base: " << base << endl;
    cout << " power: " << power << endl;
    cout << " mod: " << mod << endl;
    result = mod_exp( base, power, mod );

    cout << "\n  "<<base<<"^"<<power<<" = "<< result <<" (mod "<<mod<<")" << endl;


}

