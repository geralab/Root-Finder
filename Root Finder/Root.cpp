/* Gerald Blake
 * Iterative Methods

 *
 * Aitkens and Dynamic 
 * CS 3513
 */
#include<iostream>
#include<fstream>
#include<cmath>
#include <iomanip>
#include <vector>
using namespace std;
double f(double x);
double fprime(double x);
double fprime(double x, int f);
double f(double x, int f);
void bisection(double a, double b, double atol);
void newtonsMethod(double guess, double atol, vector<double> &data);
void newtonsMethod(double guess, vector<double> &data, int iter);
void secantMethod(double x0, double x1, double atol);
void whichFunction();
void repeatedAitken(vector<double> &data);
void dynamicAitken(double guess , vector<double> &data, int iter);
ofstream out("out.txt");
ifstream inFile("in.txt");
int func = 0;
int main()
{
	//out << fixed;
	vector<double> data;
	out << setprecision(40);
	double atol = 0.00000001;
	double a, b,guess ,guess2;
	int select,opt;
	cout << "Bisection: 0\nNewton: 1\nSecant: 2\nAitken: 3\nDynamic Aitken: 4\n ";
	cin >> select;
	switch(select)
	{
		case 0:
			out << "Bisection" << endl;
			cout << " Enter an a value [a,b]: " << endl;
			cin >> a >> b ;
			cout << "Which fuction would you like to use: " << endl;
			cout << "1 for f(x) = x^3 - 30x^2 + 2552 = 0" << endl;
			cout << "2 for f(x) = e^(-x) - 0.2x = 0" << endl;
			cout << "3 for f (x) = cos(x) - x^3 = 0" << endl;
			cout << "4 for f(x) = 2x^3 - 3x - 1 = 0" << endl;
			cin >> func;
		    whichFunction();
			bisection(a,b,atol);
			break;
		case 1:
			out << "Newtons Method" <<endl;
			cout << " Enter an a guess: " << endl;
			cin >> guess;
			cout << "Which fuction would you like to use: " << endl;
			cout << "1 for f(x) = x^3 - 30x^2 + 2552 = 0" << endl;
			cout << "2 for f(x) = e^(-x) - 0.2x = 0" << endl;
			cout << "3 for f (x) = cos(x) - x^3 = 0" << endl;
			cout << "4 for f(x) = 2x^3 - 3x - 1 = 0" << endl;
			cout << "5 for f(x) = x^12 = 0 " << endl;
			cin >> func;
			whichFunction();
		    newtonsMethod(guess, atol,data);
			break;
		case 2:
			out << "Secant Method " << endl;
			cout << " Enter an a x0 and x1: " << endl;

			cin >> guess >> guess2;
			cout << "Which fuction would you like to use: " << endl;
			cout << "1 for f(x) = x^3 - 30x^2 + 2552 = 0" << endl;
			cout << "2 for f(x) = e^(-x) - 0.2x = 0" << endl;
			cout << "3 for f (x) = cos(x) - x^3 = 0" << endl;
			cout << "4 for f(x) = 2x^3 - 3x - 1 = 0" << endl;
			cin >> func;
			whichFunction();
			secantMethod(guess, guess2,atol);
			break;

		case 3: 
			cout << "Press 0 to perform Aitken's Method\n on a function and press 1\n to perform it on file data " ;
			cin >> opt;
			switch(opt)
			{
				case 0:
					out << "Aitken's Method" <<endl;
					cout << "Which fuction would you like to use: " << endl;
					cout << "1 for f(x) = x^3 - 30x^2 + 2552 = 0" << endl;
					cout << "2 for f(x) = e^(-x) - 0.2x = 0" << endl;
					cout << "3 for f (x) = cos(x) - x^3 = 0" << endl;
					cout << "4 for f(x) = 2x^3 - 3x - 1 = 0" << endl;
					cout << "5 for f(x) = x^12 = 0 " << endl;
					cout << "6 for f(x) = x^20 + x^5 = 0" << endl;
					cout << "7 for f(x) = (x-2)*(x-0.99)^20 = 0" << endl;
					cin >> func;
					whichFunction();
					cout << " Enter an a guess: " << endl;
					cin >> guess;
					newtonsMethod(guess, atol,data);
					repeatedAitken(data);
					break;
				case 1:
					
					while(inFile)
					{
						double fileValue;
						inFile >> fileValue ;
						data.push_back(fileValue);
						
					}
					repeatedAitken(data);
					break;
			}
			break;
		case 4:
			cout << "Press 0 to perform Dynamic Aitken's Method\non a function and press 1\nto perform it on file data: " ;
			cin >> opt;
			switch(opt)
			{
				case 0:
					out << "Dyanamic Aitken's Method" <<endl;
					cout << "Which fuction would you like to use: " << endl;
					cout << "1 for f(x) = x^3 - 30x^2 + 2552 = 0" << endl;
					cout << "2 for f(x) = e^(-x) - 0.2x = 0" << endl;
					cout << "3 for f (x) = cos(x) - x^3 = 0" << endl;
					cout << "4 for f(x) = 2x^3 - 3x - 1 = 0" << endl;
					cout << "5 for f(x) = x^12 = 0 " << endl;
					cout << "6 for f(x) = x^20 + x^5 = 0" << endl;
					cout << "7 for f(x) = (x-2)*(x-0.99)^20 = 0" << endl;
					cin >> func;
					whichFunction();
					cout << "Enter an a guess: " << endl;
					cin >> guess;
					dynamicAitken(guess,data,2);
					break;
				case 1:
					
			break;
		
	}
	
}
	return 0;
}


// Outpust desired function
void whichFunction()
{
	if(func == 1){
		
		out << "f(x) = x^3 - 30x^2 + 2552 = 0" << endl;
			
	}
	else if(func ==2)
	{
		out << "f(x) = e^(-x) - 0.2x = 0" << endl;
	
	}
	else if( func == 3)
	{

		out << "f(x) = cos(x) - x^3 = 0" << endl;
			

	}
	else if( func == 4){
		out << "f(x) = 2x^3 - 3x - 1 = 0" << endl;
	}
	else if (func == 5)
	{
		out << "f(x) = x^12 = 0 " << endl;
	
	}
	else if (func ==6 )
	{
	 out << "f(x) = x^20 + x^5 = 0" << endl;
	}
	else if(func == 7)
	{
		out <<"f(x) = (x-2)*(x-0.99)^20 = 0" << endl;
	
	}

	

}
double f(double x)
{
	// x^3 - 30x^2 + 2552
	return pow(x,3) - 30 * pow(x,2) + 2552;
}

//returns y value of function
double f(double x, int f)
{
	// x^3 - 30x^2 + 2552
	if(f == 1)
	{
		return pow(x,3) - 30 * pow(x,2) + 2552;
	}else if(f ==2){
			return pow(-x,2.718281828) - 0.2*x;
	}else if(f == 3){
		return cos(x) - pow(x,3);		
	}else if(f == 4){
		return 2 * pow (x,3) - 3 *x - 1;
	
	}else if (f == 5){
		return pow (x,12);
	}else if(f == 6)
	{
		return pow(x,20) + pow(x,5);
	}else if(f == 7)
	{
		return (x-1)*pow((x-0.99),20);
	}
	
}
double fprime(double x)
{
	//3x^2 - 60x
	return 3 * pow(x,2) - 60 * x;
}
//returns y value of derivative
double fprime(double x, int f)
{
	//3x^2 - 60x
	if(f == 1)
	{
		return 3 * pow(x,2) - 60 * x;
	} else if(f ==2){
			return pow(-x,-2.718281828) - 0.2;
	}else if(f == 3){
			return -sin(x) - 3*pow(x,2);		
	}else if(f == 4){
			return 6 * pow (x,2) - 3;
	}else if(f == 5)
	{
		return 12*pow(x,11);
	}else if(f == 6)
	{
		return 20 * pow(x,19) + 5*pow(x,4);
	}else if(f == 7)
	{
	
		return pow((x-.99),20) + (x-1)*20*pow((x-0.99),19);
	
	}

	
}
void bisection(double a, double b, double atol)
{
	double fb = f(b,func);
	double fa = f(a,func);
	double fp;
	if(a >=b || (fa * fb >= 0) || atol <=0)
	{
		cout << "Invalid input" << endl;
		out << "Invalid input" << endl;
		return;
	}
	double n = ceil(log((b-a) / (2*atol)) / log(2.0)) ;
	double p;
	for(int i = 1; i <= n; i++)
	{
		p = (a + b) / 2;
		fp = f(p,func);

		if( f(a,func) * f(p,func)  < 0)
		{
			b = p;
			fb = p;
		}
		else
		{
			a = p;
			fa = fp;
		}
		out <<"fa: " << fa << endl;
		out <<"fb: " << fb << endl;
		out <<"fp: " << fp << endl;
		out <<"a: " << a << endl;
		out <<"b: " << b << endl;
		out <<"p: " << p << endl;
		out <<"n: " << n << endl;
		out <<"i: " << i << endl;
	}
	p = (a + b) / 2;
	out <<"p: " << p << endl;
}

void newtonsMethod(double guess, double atol, vector<double> &data)
{
	out << "NEWTON" << endl;
	double xCurrent = 0.0;;
	double xPrev;
	data.push_back(guess);
	xPrev = guess;
	do
	{
		//out << "XCurrent: " << xCurrent << endl;
		//out << "XPrev: " << xPrev << endl;
		//out << "guess: " << guess << endl;
		//out << "f(x): " << f(xCurrent,func) << endl;
		xCurrent = (xPrev - (f(xPrev,func) / fprime(xPrev,func)));
		xPrev = xCurrent;
		data.push_back(xCurrent);
		//out << "XCurrent: " << xCurrent << endl;
		//out << "XPrev: " << xPrev << endl;
		//out << "guess: " << guess << endl;
		//out << "f(x): " << f(xCurrent,func) << endl;
	}while(f(xCurrent,func) >= atol );

}

void newtonsMethod(double guess, vector<double> &data, int iter)
{
	out << "NEWTON" << endl;
	double xCurrent = 0.0;;
	double xPrev;
	data.push_back(guess);
	xPrev = guess;
	int i = 0;
	do
	{
		//out << "XCurrent: " << xCurrent << endl;
		//out << "XPrev: " << xPrev << endl;
		//out << "guess: " << guess << endl;
		//out << "f(x): " << f(xCurrent,func) << endl;
		xCurrent = (xPrev - (f(xPrev,func) / fprime(xPrev,func)));
		xPrev = xCurrent;
		data.push_back(xCurrent);
		//out << "XCurrent: " << xCurrent << endl;
		//out << "XPrev: " << xPrev << endl;
		//out << "guess: " << guess << endl;
		//out << "f(x): " << f(xCurrent,func) << endl;
		i++;
	}while(i < iter);

}
	void secantMethod(double x0, double x1, double atol)
	{

		double xCurrent = 0;
		double xPrev = x1;
		double xPrevMinusOne = x0;
		out << "Guess 1 " << x0 <<" and 2 " << x1 << endl;
		do
		{

			out << "XCurrent: " << xCurrent << endl;
			out << "XPrev: " << xPrev << endl;
			out << "xPrevMinusOne: " << xPrevMinusOne << endl;
			out << "f(x): " << f(xCurrent,func) << endl;
			xCurrent = (xPrev - (f(xPrev,func)*(xPrev - xPrevMinusOne)) / (f(xPrev,func) - f(xPrevMinusOne,func)));
			xPrevMinusOne = xPrev;
			xPrev = xCurrent;
			out << "XCurrent: " << xCurrent << endl;
			out << "XPrev: " << xPrev << endl;
			out << "xPrevMinusOne: " << xPrevMinusOne << endl;
			out << "f(x): " << f(xCurrent,func) << endl;
		}while(f(xCurrent,func) >= atol);
	}



	void repeatedAitken(vector<double> &data)
	{
		
		double xn = 0;
		double xMin1 = 0;
		double xMin2 = 0;
		double xNp1 = 0;
		bool done = false;
		out << "NEWTON ITERATIONS: " << endl;
		vector<double> third;
		vector<double> fourth;

		for(unsigned int k = 0; k < data.size(); k++)
		{
			out << k << " :"<< data[k]<< endl;
		}
		out << "SECOND" << endl;
		for(unsigned int i = 0 ; i < data.size() && !done; i++)
		{
			//prevent out of bounds error
			if((i+2) < data.size() && (i+1) < data.size())
			{
				 xn =  i + 2;
				 xMin1 = i + 1 ;
			}else {
				done = true;
			}
			/*out << "x"<<i<<" = "<<data[xn]<<" - " <<"("<<data[xn] << " - " << data[xMin1]<<")^2 / ((" << data[xn] << " - " << data[xMin1] << ") - (" 
			<<data[xMin1]<< " - " << data[i] << "))";*/

			// get value of delta squared formula
			xNp1 = data[xn] -
			pow(data[xn] - data[xMin1],2) /

			((data[xn] - data[xMin1]) - (data[xMin1] - data[i] ));
			third.push_back(xNp1);
			out << i <<" : " << xNp1 << endl;


		}
		done = false;
		out << "THIRD" << endl;
		for(unsigned int i = 0 ; i < third.size() && !done; i++)
		{
			if((i+2) < third.size() && (i+1) < third.size())
			{
				 xn =  i + 2;
				 xMin1 = i + 1 ;
			}else {
				done = true;
			}
			/*out << "x"<<i<<" = "<<data[xn]<<" - " <<"("<<data[xn] << " - " << data[xMin1]<<")^2 / ((" << data[xn] << " - " << data[xMin1] << ") - (" 
			<<data[xMin1]<< " - " << data[i] << "))";*/
			// get value of delta squared formula
			xNp1 = third[xn] -
			pow(third[xn] - third[xMin1],2) /

			((third[xn] - third[xMin1]) - (third[xMin1] - third[i] ));
			fourth.push_back(xNp1);
			out <<i<< " : " << xNp1 << endl;


		}


		out << "FOURTH" << endl;
		done = false;
		for(unsigned int i = 0 ; i < fourth.size() && !done; i++)
		{
			if((i+2) < fourth.size() && (i+1) < fourth.size())
			{
				 xn =  i + 2;
				 xMin1 = i + 1 ;
			}else {
				done = true;
			}
			/*out << "x"<<i<<" = "<<data[xn]<<" - " <<"("<<data[xn] << " - " << data[xMin1]<<")^2 / ((" << data[xn] << " - " << data[xMin1] << ") - (" 
			<<data[xMin1]<< " - " << data[i] << "))";*/

			// get value of delta squared formula
			xNp1 = fourth[xn] -
			pow(fourth[xn] - fourth[xMin1],2) /

			((fourth[xn] - fourth[xMin1]) - (fourth[xMin1] - fourth[i] ));
			//fourth.push_back(xNp1);
			out <<i<< " : " << xNp1 << endl;


		}


	}



	void dynamicAitken(double guess, vector<double> &data, int iter)
	{
	
	

		
		double xn = 0;
		double xMin1 = 0;
		double xMin2 = 0;
		double xNp1 = guess;
		bool done = false;
		int p = 0;
		newtonsMethod(xNp1,data,iter);
		for(unsigned int i = 0; i < (iter + 2);i++)
		{
			
			for(unsigned int k = 0; k < data.size(); k++)
			{
				out << k << " :"<< data[k]<< endl;
			}
			out << "AITKEN" << endl;
			//for(unsigned int i = 0 ; i < data.size() && !done; i++)
			//{

				//if((i+2) < data.size() && (i+1) < data.size())
				//{
					 xn =  p + 2;
					 xMin1 = p + 1 ;
				//}else {
				//	done = true;
				//}
				/*out << "x"<<i<<" = "<<data[xn]<<" - " <<"("<<data[xn] << " - " << data[xMin1]<<")^2 / ((" << data[xn] << " - " << data[xMin1] << ") - (" 
				<<data[xMin1]<< " - " << data[i] << "))";*/

				// get value of delta squared formula
				xNp1 = data[xn] -
				pow(data[xn] - data[xMin1],2) /

				((data[xn] - data[xMin1]) - (data[xMin1] - data[p] ));
				
				out << i <<" : " << xNp1 << endl;


			//}
			
			data.resize(0);
			data.clear();
			newtonsMethod(xNp1,data,iter);
			p = 0;
		}
	}

