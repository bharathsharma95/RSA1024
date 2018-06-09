#include <iostream>
#include <ap_int.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

using namespace std;

ap_uint<1024> modexp(ap_uint<1024> base, ap_uint<1024> exp, ap_uint<1024> n_modulus);
ap_uint<1024> modinv(ap_uint<1024> a, ap_uint<1024> m);
ap_int<1024> gcdExtended(ap_uint<1024> a, ap_uint<1024> b, ap_uint<1024> *x, ap_uint<1024> *y);


int test();


int test()
{
cout << "\n\n";

	ap_uint<512> p = "656692050181897513638241554199181923922955921760928836766304161790553989228223793461834703506872747071705167995972707253940099469869516422893633357693";
	ap_uint<512> q = "204616454475328391399619135615615385636808455963116802820729927402260635621645177248364272093977747839601125961863785073671961509749189348777945177811";

	ap_uint<1024> n = p * q;
	cout << "n is: " << n << "\n";

	ap_uint<1024> phi_n = (p-1) * (q-1);
	cout << "phi_n is: " << phi_n << "\n";

	ap_uint<1024> e = 65521;
	cout << "e is: " << e << "\n";

	ap_uint<1024> m = 4;
	cout << "m is: " << m << "\n";

	ap_uint<1024> d = modinv(e,phi_n);
	cout << "d is: " << d << "\n";

	ap_uint<1024> C = modexp(m,e,n);
	cout << "C is: " << C << "\n";

	//ap_uint<1024> check1 = (d * e) % phi_n;
	//cout << "check1=" << check1 << "\n";
	//ap_uint<1024> dummy = m % n;
	//cout<< "dummy value is:" << dummy << "\n";

cout << "\n\n";
return 0;
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
	    cout << "\n*****************************\n";
	    cout << "base = (base * base) % n_modulus\n is \n" << base;
	    cout << "\n*****************************\n";

return C;
}


ap_uint<1024> modinv(ap_uint<1024> a, ap_uint<1024> phi_n)
{
	ap_uint<1024> x, y;
	ap_int<1024> g = gcdExtended(a, phi_n, &x, &y);

	        // phi_n is added to handle negative x
	    	ap_int<1024> res = (x % phi_n + phi_n) % phi_n;
	        cout << "Modular multiplicative inverse is " << res;


return res;
}

ap_int<1024> gcdExtended(ap_int<1024> a, ap_int<1024> b, ap_uint<1024> *x, ap_uint<1024> *y)
{
    // Base Case
    if (a == 0)
    {
        *x = 0, *y = 1;
        return b;
    }

    ap_uint<1024> x1, y1; // To store results of recursive call
    ap_int<1024> gcd = gcdExtended(b%a, a, &x1, &y1);

    // Update x and y using results of recursive
    // call
    *x = y1 - (b/a) * x1;
    *y = x1;

return gcd;
}

/* Redundant/trial code
 *
 *
 * double m = 1.1;
	cout << "m is: " << m << "\n";

	long double pow_m_e = pow(m,e);
	cout << "pow_m_e is:" << pow_m_e << "\n";

	*/
