#include <iostream>
#define AP_INT_MAX_W 4096
#include <ap_int.h>

using namespace std;

int test();

ap_uint<1024> modinv(ap_uint<1024> a, ap_uint<1024> m);
ap_uint<1024> gcdExtended(ap_uint<1024> a, ap_uint<1024> b, ap_uint<1024> *x, ap_uint<1024> *y);
ap_uint<1024> modexp(ap_uint<1024> base, ap_uint<1024> exp, ap_uint<1024> n_modulus);

int test()
{
	ap_uint<512> p = "656692050181897513638241554199181923922955921760928836766304161790553989228223793461834703506872747071705167995972707253940099469869516422893633357693";
	ap_uint<512> q = "204616454475328391399619135615615385636808455963116802820729927402260635621645177248364272093977747839601125961863785073671961509749189348777945177811";

	ap_uint<1024> n = p * q;							//n
	cout << "n is: " << n << "\n";

	ap_uint<512> p_1 = p-1;
	ap_uint<512> q_1 = q-1;

	ap_uint<1024> phi_n = p_1 * q_1;						//phi_n
	cout << "phi_n is: " << phi_n << "\n";

	ap_uint<1024> e = 65537;							//e
	cout << "e is: " << e << "\n";

	ap_uint<1024> m = 65;								//m
	cout << "m is: " << m << "\n";

	ap_uint<1024> d = modinv(e,phi_n);						//d
	cout << "d is: " << d << "\n";

	ap_uint<1024> C = modexp(m,e,n);						//Cipher  = m^e mod n
	cout << "C is: " << C << "\n";

	ap_uint<1024> M = modexp(C,d,n);						//Message = C^d mod n
	cout << "M is: " << M << "\n";

	cout << "\n\n";

	return 0;
}



ap_uint<1024> modinv(ap_uint<1024> a, ap_uint<1024> phi_n)
{
	ap_uint<1024> x, y;
	ap_uint<1024> g = gcdExtended(a, phi_n, &x, &y);
	ap_uint<1024> res;
	if (g != 1)
	        cout << "Inverse doesn't exist";
	    else
	    {
	        // phi_n is added to handle negative x
	    	ap_uint<1024> helper1 = x % phi_n;
	    	ap_uint<1024> helper2 = helper1 + phi_n;
	        res = helper2 % phi_n;
	        //cout << "Modular multiplicative inverse is " << res <<"\n";
	    }

	return res;
}


ap_uint<1024> gcdExtended(ap_uint<1024> a, ap_uint<1024> b, ap_uint<1024> *x, ap_uint<1024> *y)
{
    // Base Case
    if (a == 0)
    {
        *x = 0, *y = 1;
        return b;
    }

    ap_uint<1024> x1, y1; // To store results of recursive call
    ap_uint<1024> b_mod_a = b%a;
    ap_int<1024> gcd = gcdExtended(b_mod_a, a, &x1, &y1);

    // Update x and y using results of recursive
    // call
    ap_uint<1024> b_div_a = b/a;
    ap_uint<1024> helper = (b_div_a) * x1;
    *x = y1 - helper;
    *y = x1;

    return gcd;
}



ap_uint<1024> modexp(ap_uint<1024> base, ap_uint<1024> exp, ap_uint<1024> n_modulus)
{
	ap_uint<1024> C = 1;
	    while (exp > 0)
	    {
	        if (exp % 2 == 1)
	        	{
	            	C = (C * base) % n_modulus;
	        	}
	        exp = exp >> 1;
	        base = (base * base) % n_modulus;
	    }

	    //comment this section out later
	    /*
	    cout << "\n*****************************\n";
	    cout << "base = (base * base) % n_modulus\n is \n" << base;
	    cout << "\n*****************************\n";
	    */

	return C;
}
