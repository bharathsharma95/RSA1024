#include <stdio.h>
#include <ap_cint.h>
#include <math.h>
#include <math.h>


int my_rsa_1024()
{
/************************* Generating primes p & q ***************************/

	// p is a 150 digit prime number although a 2^512 bit prime has 155 digits, for calc purposes, chosen 150 digits
	uint4 p_rev[150] = {6,5,6,6,9,2,0,5,0,1,8,1,8,9,7,5,1,3,6,3,
			8,2,4,1,5,5,4,1,9,9,1,8,1,9,2,3,9,2,2,9,
			5,5,9,2,1,7,6,0,9,2,8,8,3,6,7,6,6,3,0,4,
			1,6,1,7,9,0,5,5,3,9,8,9,2,2,8,2,2,3,7,9,
			3,4,6,1,8,3,4,7,0,3,5,0,6,8,7,2,7,4,7,0,
			7,1,7,0,5,1,6,7,9,9,5,9,7,2,7,0,7,2,5,3,
			9,4,0,0,9,9,4,6,9,8,6,9,5,1,6,4,2,2,8,9,
			3,6,3,3,3,5,7,6,9,3};

	uint4 p_rev_1[150] = {6,5,6,6,9,2,0,5,0,1,8,1,8,9,7,5,1,3,6,3,
				8,2,4,1,5,5,4,1,9,9,1,8,1,9,2,3,9,2,2,9,
				5,5,9,2,1,7,6,0,9,2,8,8,3,6,7,6,6,3,0,4,
				1,6,1,7,9,0,5,5,3,9,8,9,2,2,8,2,2,3,7,9,
				3,4,6,1,8,3,4,7,0,3,5,0,6,8,7,2,7,4,7,0,
				7,1,7,0,5,1,6,7,9,9,5,9,7,2,7,0,7,2,5,3,
				9,4,0,0,9,9,4,6,9,8,6,9,5,1,6,4,2,2,8,9,
				3,6,3,3,3,5,7,6,9,2};

	uint4 p[150];
	for(int r=0; r<150; r++)
	{
		p[r] = p_rev[149-r];
	}

	uint4 p_1[150];
	for(int r1=0; r1<150; r1++)
	{
		p_1[r1] = p_rev_1[149-r1];
	}

	// q is a 150 digit prime number although a 2^512 bit prime has 155 digits, for calc purposes, chosen 150 digits
	uint4 q_rev[150] = {2,0,4,6,1,6,4,5,4,4,7,5,3,2,8,3,9,1,3,9,
			9,6,1,9,1,3,5,6,1,5,6,1,5,3,8,5,6,3,6,8,
			0,8,4,5,5,9,6,3,1,1,6,8,0,2,8,2,0,7,2,9,
			9,2,7,4,0,2,2,6,0,6,3,5,6,2,1,6,4,5,1,7,
			7,2,4,8,3,6,4,2,7,2,0,9,3,9,7,7,7,4,7,8,
			3,9,6,0,1,1,2,5,9,6,1,8,6,3,7,8,5,0,7,3,
			6,7,1,9,6,1,5,0,9,7,4,9,1,8,9,3,4,8,7,7,
			7,9,4,5,1,7,7,8,1,1};

	uint4 q_rev_1[150] = {2,0,4,6,1,6,4,5,4,4,7,5,3,2,8,3,9,1,3,9,
				9,6,1,9,1,3,5,6,1,5,6,1,5,3,8,5,6,3,6,8,
				0,8,4,5,5,9,6,3,1,1,6,8,0,2,8,2,0,7,2,9,
				9,2,7,4,0,2,2,6,0,6,3,5,6,2,1,6,4,5,1,7,
				7,2,4,8,3,6,4,2,7,2,0,9,3,9,7,7,7,4,7,8,
				3,9,6,0,1,1,2,5,9,6,1,8,6,3,7,8,5,0,7,3,
				6,7,1,9,6,1,5,0,9,7,4,9,1,8,9,3,4,8,7,7,
				7,9,4,5,1,7,7,8,1,0};

	// indexing is like q_rev[0]=2 and q_rev[149]= 1
	// and when we calculate the multiplication, since we start at LSB, we reverse p & q

	uint4 q[150];
		for(int s=0; s<150; s++)
		{
			q[s] = q_rev[149-s];
		}

	uint4 q_1[150];
		for(int s1=0; s1<150; s1++)
		{
			q_1[s1] = q_rev_1[149-s1];
		}

/************************* Generated primes p & q also (p-1), (q-1) ***************************/


/*************************** Calculate n=p*q ********************************/

		printf("\n*************************** Calculating n=p*q ********************************\n\n");

		uint4 temp[300][150]={0};
		uint4 carry[150]={0};

		for(int u=0; u<150; u++)
		{
			for(int t=0; t<=150; t++)
					{
						//if(t!=150 & u!=150)
						//{
							carry[148-t] = ((carry[149-t]) + (p[t]*q[u])) / 10;
							temp[299-t-u][u] = ((carry[149-t]) + (p[t]*q[u])) % 10;

							//printf("temp[%d][%d] = %d\t",299-t-u,u,temp[299-t-u][u]); //debugging statement to see what is the result
						//}

						/*else if (t == 150)
						{
							temp[299-t-u][u] = carry[149-t];
							printf("temp[%d][%d] = %d\t",299-t-u,u,temp[299-t-u][u]);
						}
						if(t == 150 & u == 150)
						{
							uint4 last_carry = (p[149]*q[149]) / 10;
							printf("\nCarry of the last multiplication is: %d\n", last_carry);
						}*/
					}
			printf("\n");

		}

		printf("\n***************************************************************\n");
		printf("printing the entire matrix of temp\n");
		printf("***************************************************************\n");

		for(int var1=0; var1<150; var1++)
		{
			for(int var2=0; var2<300; var2++)
			{
				printf("temp[%d][%d] = %d\t",299-var2,var1,temp[299-var2][var1]);//prints the entire matrix of temp
			}
			printf("\n");
		}


		printf("\n***************************************************************\n");

		uint4 result[301]={0};
		for(int var=0; var<300; var++)
		{
			result[299-var] = temp[299-var][0];
			// stores the first result of multiplication in result and keeps adding each row of the output multiplication to result
			//printf("res[%d]= %d\t", 299-var,result[299-var]);
		}
		printf("\n");
		printf("\n");
		printf("\n***************************************************************\n");
		printf("***************************************************************\n");
		printf("***************************************************************\n");
		printf("************** RESULT OF MULTIPLICATION n is : ******************\n");

		uint4 add_carry[300]={0};

		for(int x=1; x<150; x++)
		{
			for(int v=0; v<=300; v++)
			{
				add_carry[298-v] = (result[299-v] + temp[299-v][x] + add_carry[299-v]) / 10;
				result[299-v] = (result[299-v] + temp[299-v][x] + add_carry[299-v]) % 10;
				//printf("res[%d]= %d\t",299-v,result[299-v]);
			}
		}

		result[300] = result[-1];
		printf("\nFinal carry as result[300] = %d\n", result[300]);

		for(int x11=1; x11<150; x11++)
		{
			for(int v11=0; v11<=301; v11++)
			{
				printf("res[%d]= %d\t",300-v11,result[300-v11]);
			}
		}




		printf("\n***************************************************************\n");
		printf("***************************************************************\n");
		printf("***************************************************************\n");
		printf("\n*************************** Calculating phi_n=(p-1)*(q-1) ********************************\n\n");

		uint4 temp1[300][150]={0};
		uint4 carry1[150]={0};

		for(int u1=0; u1<150; u1++)
		{
			for(int t1=0; t1<=150; t1++)
			{
				//if(t!=150 & u!=150)
				//{
					carry1[148-t1] = ((carry1[149-t1]) + (p_1[t1]*q_1[u1])) / 10;
					temp1[299-t1-u1][u1] = ((carry1[149-t1]) + (p_1[t1]*q_1[u1])) % 10;
					//printf("temp_1[%d][%d] = %d\t",299-t1-u1,u1,temp1[299-t1-u1][u1]); //debugging statement to see what is the result
				//}

			}
			printf("\n");
		}

		printf("\n***************************************************************\n");
		printf("printing the entire matrix of temp_1\n");
		printf("***************************************************************\n");

		for(int var11=0; var11<150; var11++)
		{
			for(int var22=0; var22<300; var22++)
			{
				printf("temp_1[%d][%d] = %d\t",299-var22,var11,temp1[299-var22][var11]);//prints the entire matrix of temp_1
			}
			printf("\n");
		}


		printf("\n***************************************************************\n");

		uint4 result1[301]={0};
			for(int var_1=0; var_1<300; var_1++)
			{
				result1[299-var_1] = temp1[299-var_1][0];
				//printf("res[%d]= %d\t", 299-var_1,result1[299-var_1]);
			}
			printf("\n");
			printf("\n");

			printf("***************************************************************\n");
			printf("***************************************************************\n");
			printf("************** phi_n is : ******************\n");

			uint4 add_carry1[300]={0};

			for(int x1=1; x1<150; x1++)
			{
				for(int v1=0; v1<=300; v1++)
				{
					add_carry1[298-v1] = (result1[299-v1] + temp[299-v1][x1] + add_carry1[299-v1]) / 10;
					result1[299-v1] = (result1[299-v1] + temp[299-v1][x1] + add_carry1[299-v1]) % 10;
					//printf("result_1[%d]= %d\t",299-v1,result1[299-v1]);
				}
			}

			result1[300] = result1[-1];
			printf("\nFinal carry as result1[300] = %d\n", result1[300]);

			for(int x12=1; x12<150; x12++)
			{
				for(int v12=0; v12<=301; v12++)
				{
					printf("res[%d]= %d\t",300-v12,result[300-v12]);
				}
			}

			printf("\n***************************************************************\n");
			printf("***************************************************************\n");

		uint4 e[17] = {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1};
		uint8 message = 65;


		uint4 cipher = encrypt(message, e, result);


return 0;
}

uint4 encrypt(uint8 msg, uint64 enc, uint4 res)
{

	uint4 Ciph = 1, iter=0;

	while(iter<17)
	{
		if(enc[iter] == 1)
		{
			basicmodmult(msg, Ciph, res);
		}
	basicmodmult(msg, msg, res);
	}


return Ciph; // return the result m^e mod(n) to Cipher
}

uint4 basicmodmult(uint4 base, uint64 exponent, uint4 N)
{
	uint4 C = 0;
	uint4 T = base;
	uint4 iter = 0;
	double n = sizeof(exponent);

	while(iter < n)
	{
		if (exponent[iter] == 1)
		{
			C = C + T;
		}
		T = 2 * T;
		iter = iter + 1;
	}

	while(C<N)
	{
		C = C - N;
	}

return C; // return Cipher later
}


/*uint4 modmult(uint8 base, uint64 exponent, uint4 N)
{

	double n = sizeof(exponent);
	uint4 S = pow(2,n) % N;
	uint4 C = 0;
	uint4 T = base;
	uint4 i = 0;

	while (i<n)
	{
		if(exponent[i] == 1)
		{
			C = C + T;
			while(Carry(C))
			{
				C = C + S;
			}
		}

		T = 2 * T;

		while(Carry(T))
		{
			T = T + S;
		}

		i = i + 1;
	}

	if (C>N)
	{
		C = C - N;
	}

return C; // return Ciph later
}
*/

void dummy()
{
	printf("Does nothing");
}
