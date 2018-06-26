#include <iostream>
#define AP_INT_MAX_W 2048
#include <ap_int.h>

using namespace std;

ap_uint<1024> temp_arr[13] = {0};
ap_uint<1024> a_arr[13] = {0};
ap_uint<1024> b_arr[13] = {0};
ap_uint<1024> x_arr[13] = {0};
ap_uint<1024> y_arr[13] = {0};

int test();

ap_uint<1024> modinv(ap_uint<1024> a, ap_uint<1024> m);
ap_uint<1024> modexp(ap_uint<1024> base, ap_uint<1024> exp, ap_uint<1024> n_modulus);

int test()
{
	ap_uint<512> p = "656692050181897513638241554199181923922955921760928836766304161790553989228223793461834703506872747071705167995972707253940099469869516422893633357693";
	ap_uint<512> q = "204616454475328391399619135615615385636808455963116802820729927402260635621645177248364272093977747839601125961863785073671961509749189348777945177811";

	ap_uint<1024> n = p * q;							//n
	cout << "n is: " << n << "\n";

	ap_uint<512> p_1 = p-1;
	ap_uint<512> q_1 = q-1;

	ap_uint<1024> phi_n = p_1 * q_1;					//phi_n
	cout << "phi_n is: " << phi_n << "\n";

	ap_uint<1024> e = 65537;							//e
	cout << "e is: " << e << "\n";

	ap_uint<1024> m = 65;								//m
	cout << "m is: " << m << "\n";

	cout << "\n****************************************************************************\n";
	ap_uint<1024> d = modinv(e,phi_n);					//d
	cout << "d is: " << d << "\n";
	cout << "****************************************************************************\n";

	ap_uint<1024> C = modexp(m,e,n);					//Cipher  = m^e mod n
	cout << "C is: " << C << "\n";

	ap_uint<1024> M = modexp(C,d,n);					//Message = C^d mod n
	cout << "M is: " << M << "\n";

	cout << "\n\n";

	return 0;
}



ap_uint<1024> modinv(ap_uint<1024>a, ap_uint<1024>b)
{

	ap_uint<16> count = 0;
	ap_uint<1024> temp = 0;
	//cout<< "\n******************************************\n\n";

	a_arr[count] = a;
	b_arr[count] = b;
	ap_uint<1024> b_0 = b;
	//cout << "a_arr[" << count << "] : " << a_arr[count] << "\n";
	//cout << "b_arr[" << count << "] : " << b_arr[count] << "\n\n";
	//count++;


	while(a!=0)
	{
		temp = a;
		temp_arr[count] = temp;

		a = b%a;
		a_arr[count+1] = a;

		b = temp;
		b_arr[count+1] = b;

		//cout << "a_arr[" << count << "] : " << a_arr[count] << "\n";
		//cout << "b_arr[" << count << "] : " << b_arr[count] << "\n\n";
		count++;
	}

	b_arr[0] = b_0;
	//cout << "here b_arr[0] : " << b_arr[0] << "\n\n";

	//count is 13 until now

	// when a == 0; setting values of pointers '*x = 0' and '*y = 1'

	ap_uint<1024> gcd = b;
	x_arr[count] = 0; y_arr[count] = 1;

	//cout << "a_arr[" << count << "] : " << a_arr[count] << "\n";
	//cout << "b_arr[" << count << "] : " << b_arr[count] << "\n";
	cout << "returning b_arr[" << count << "] as gcd : " << gcd << "\n";

	count--;
	//cout << "after count-- , count is : " << count << "\n\n";


	// updating the values of pointers x & y from recursive calls (from while loop)

		while(count!=0)
		{

			ap_uint<1024> b_arr_temp = b_arr[count];
			ap_uint<1024> a_arr_temp = a_arr[count];

			ap_uint<1024> X_arr_count_plus1;
			ap_uint<1024> Y_arr_count_plus1;
			X_arr_count_plus1 = x_arr[count+1];
			Y_arr_count_plus1 = y_arr[count+1];

				//calculating *x= y1 - ((b/a) * x1);
				ap_uint<1024> X_arr_count_temp;
				ap_uint<1024> helper1 = (b_arr_temp/a_arr_temp);
				ap_uint<1024> helper2 = (helper1 * X_arr_count_plus1);
				X_arr_count_temp = Y_arr_count_plus1 - helper2;

					x_arr[count] = X_arr_count_temp;
					//cout << "x_arr[" << count << "] : " << x_arr[count] << "\n";

					//calculating *y=x1
				ap_uint<1024> Y_arr_count_temp;
				Y_arr_count_temp = x_arr[count+1];

					y_arr[count] = Y_arr_count_temp;
					//cout << "y_arr[" << count << "] : " << y_arr[count] << "\n";
					//cout << "a_arr[" << count << "] : " << a_arr[count] << "\n";
					//cout << "b_arr[" << count << "] : " << b_arr[count] << "\n\n";

			count--;
		}



	// When count == 0

			ap_uint<1024> b_arr_temp = b_arr[count];
			ap_uint<1024> a_arr_temp = a_arr[count];

			ap_uint<1024> X_arr_count_plus1;
			ap_uint<1024> Y_arr_count_plus1;

			X_arr_count_plus1 = x_arr[count+1];
			Y_arr_count_plus1 = y_arr[count+1];


				ap_uint<1024> X_arr_count_temp;
				ap_uint<1024> helper1 = (b_arr_temp/a_arr_temp);
				ap_uint<1024> helper2 = (helper1 * X_arr_count_plus1);
				X_arr_count_temp = Y_arr_count_plus1 - helper2;

					x_arr[count] = X_arr_count_temp;
					//cout << "x_arr[" << count << "] : " << x_arr[count] << "\n";

				ap_uint<1024> Y_arr_count_temp;
				Y_arr_count_temp = x_arr[count+1];

					y_arr[count] = Y_arr_count_temp;
					//cout << "y_arr[" << count << "] : " << y_arr[count] << "\n";
					//cout << "a_arr[" << count << "] : " << a_arr[count] << "\n";
					//cout << "b_arr[" << count << "] : " << b_arr[count] << "\n\n";


	// when count == 0 --> end




		ap_uint<1024> res;
		if (gcd != 1)
		        cout << "Inverse doesn't exist\n\n\n";
	    else
	    {
	        // phi_n is added to handle negative x
	    	ap_uint<1024> phi_n = "134369998990354300089952937559587535776969448542275036274354877139580565294709571734984987344659981049823868256870131654179172131661304459362060269619979448861355471525288293114690580693447255431404780065203686577811517411724345053044304720270314669616919153209303508163154216935023021982650271214520";
	    	ap_uint<1024> x_arr_temp = x_arr[count];
	    	//cout << "x_arr_temp : " << x_arr_temp << "\n";
	    	//cout << "phi_n : " << phi_n << "\n";
	    	//ap_uint<1024> helper1 = x_arr_temp % phi_n;
	    	//ap_uint<1024> helper2 = ((x_arr_temp % phi_n) + phi_n);

	        res = ((x_arr_temp % phi_n) + phi_n) % phi_n;
	        //cout << "Modular multiplicative inverse is " << res <<"\n\n\n";
	    }


		return res;
}



ap_uint<1024> modexp(ap_uint<1024> base, ap_uint<1024> exp, ap_uint<1024> n_modulus)
{
	ap_uint<1024> Res = 1;
	    while (exp > 0)
	    {
	        if (exp % 2 == 1)
	        	{
	            	Res = (Res * base) % n_modulus;
	        	}
	        exp = exp >> 1;
	        base = (base * base) % n_modulus;
	    }

	return Res;
}
