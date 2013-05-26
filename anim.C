#include <iostream>
#include <math.h>
#include <stdlib.h>
#include <fstream>

const double PI = 3.1415926;
const int STEP = 10000;
const double M_EvsM_S = 0.000003;
double M_JvsM_S0 = 0.00095;
const double vint = 2 * PI;



using namespace std;

int main()
{
	ofstream OutputFile;
	OutputFile.open("./coordinate.dat", ios::out);
	
	for (double ijj = 0; ijj <= 3; ijj=ijj+0.05)
	{
		double MultiMassJu = pow(10,ijj);
	 	// evolv(MultiMassJu);
	 	double M_JvsM_S = M_JvsM_S0 * MultiMassJu;
	 	cout<<M_JvsM_S<<endl;
		struct CoorNVel
		{
			double x;
			double y;
			double vx;
			double vy;
		};
		CoorNVel Sun;
		CoorNVel Earth={1.5,0,0,2*PI};
		CoorNVel Jupiter={-2.7,0,0,-PI*0.4};
		
		Sun.x = -M_EvsM_S * Earth.x - M_JvsM_S * Jupiter.x;
		Sun.y = -M_EvsM_S * Earth.y - M_JvsM_S * Jupiter.y;

		double delta_t = 0.002;
		double r_ES, r_JS, r_EJ;


		for (int i = 0; i < STEP; ++i)
		{
			Sun.x = -M_EvsM_S * Earth.x - M_JvsM_S * Jupiter.x;
			Sun.y = -M_EvsM_S * Earth.y - M_JvsM_S * Jupiter.y;
			r_EJ = sqrt((Earth.x - Jupiter.x) * (Earth.x - Jupiter.x) + (Earth.y - Jupiter.y) * (Earth.y - Jupiter.y));
			r_JS = sqrt((Sun.x - Jupiter.x) * (Sun.x - Jupiter.x) + (Sun.y - Jupiter.y) * (Sun.y - Jupiter.y));
			r_ES = sqrt((Earth.x - Sun.x) * (Earth.x - Sun.x) + (Earth.y - Sun.y) * (Earth.y - Sun.y));


			Earth.vx -= 4 * PI * PI * (Earth.x - Sun.x) * delta_t / pow(r_ES,3) + 4 * PI * PI * (Earth.x - Jupiter.x) * M_JvsM_S * delta_t / pow(r_EJ,3);
			Earth.vy -= 4 * PI * PI * (Earth.y - Sun.y) * delta_t / pow(r_ES,3) + 4 * PI * PI * (Earth.y - Jupiter.y) * M_JvsM_S * delta_t / pow(r_EJ,3);
			Jupiter.vx -= 4 * PI * PI * (Jupiter.x - Sun.x) * delta_t / pow(r_JS,3) + 4 * PI * PI * (Jupiter.x - Earth.x) * M_EvsM_S * delta_t / pow(r_EJ,3);
			Jupiter.vy -= 4 * PI * PI * (Jupiter.y - Sun.y) * delta_t / pow(r_JS,3) + 4 * PI * PI * (Jupiter.y - Earth.y) * M_EvsM_S * delta_t / pow(r_EJ,3);

			// Sun.vx = -M_EvsM_S * Earth.vx - M_JvsM_S * Jupiter.vx;
			// Sun.vy = -M_EvsM_S * Earth.vy - M_JvsM_S * Jupiter.vy;

			Earth.x += Earth.vx * delta_t;
			Earth.y += Earth.vy * delta_t;
			Jupiter.x += Jupiter.vx * delta_t;
			Jupiter.y += Jupiter.vy * delta_t;
	
			OutputFile<<Earth.x<<"   "<<Earth.y<<endl;


		}
		OutputFile<<"   A    "<<endl;
 	}
	

	OutputFile.close();


 	return 0;
}

