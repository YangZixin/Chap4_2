#include <iostream>
#include <math.h>

const double PI = 3.1415926;
const int STEP = 10000;
const double M_EvsM_S = 0.000003;
double M_JvsM_S = 0.00095;
const double vint = 2 * PI;


double *x_Earth = NULL;
double *y_Earth = NULL;
double *x_Jupiter = NULL;
double *y_Jupiter = NULL;
double *x_Sun = NULL;
double *y_Sun = NULL;

using namespace std;



void evolv(double MultiMassJu)
{
	double M_JvsM_S = M_JvsM_S * MultiMassJu;
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

	x_Earth =new double[STEP];
	y_Earth =new double[STEP];
	x_Jupiter =new double[STEP];
	y_Jupiter =new double[STEP];
	x_Sun =new double[STEP];
	y_Sun =new double[STEP];


	for (int i = 0; i < STEP; ++i)
	{
		Sun.x = -M_EvsM_S * Earth.x - M_JvsM_S * Jupiter.x;
		Sun.y = -M_EvsM_S * Earth.y - M_JvsM_S * Jupiter.y;
		r_EJ = sqrt((Earth.x - Jupiter.x) * (Earth.x - Jupiter.x) + (Earth.y - Jupiter.y) * (Earth.y - Jupiter.y));
		r_JS = sqrt((Sun.x - Jupiter.x) * (Sun.x - Jupiter.x) + (Sun.y - Jupiter.y) * (Sun.y - Jupiter.y));
		r_ES = sqrt((Earth.x - Sun.x) * (Earth.x - Sun.x) + (Earth.y - Sun.y) * (Earth.y - Sun.y));

		x_Earth[i] = Earth.x;
		y_Earth[i] = Earth.y;
		x_Jupiter[i] = Jupiter.x;
		y_Jupiter[i] = Jupiter.y;
		x_Sun[i] = Sun.x;
		y_Sun[i] = Sun.y;


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


	}



}
/*int main()
{
	evolv();
	return 0;
}*/

void three_body()
{
	gSystem->Unlink("BasicSJE.gif"); // delete old file
	
	c1 = new TCanvas("c1","Three Body System--Earth",200,1,600,400);

	for (double i = 0; i <= 3; i=i+0.06)
	{
	double MultiMassJu = pow(10,i);
 	evolv(MultiMassJu);

	// TGraph* gr1 = new TGraph(STEP, x_Sun, y_Sun);
	// TGraph* gr2 = new TGraph(STEP, x_Jupiter, y_Jupiter);
	TGraph* gr1 = new TGraph(STEP, x_Earth, y_Earth);
	gr1->GetXaxis()->SetTitle("X (AU/yr)");
	gr1->GetYaxis()->SetTitle("Y (AU/yr");
	gr1->SetTitle("Three Body System--Earth");
	// gr1->GetXaxis()->SetLimits(-2,2);
	// gr1->GetYaxis()->SetRangeUser(-2,2);
	gr1->SetMarkerStyle(1);
	gr1->SetMarkerSize(6);
	gr1->SetMarkerColor(4);
	gr1->Draw("AP");

	// gr2->SetMarkerStyle(1);
	// gr2->SetMarkerColor(3);
	// gr2->Draw("P");

	// gr3->SetMarkerStyle(1);
	// gr3->SetMarkerColor(38);
	// gr3->Draw("P");

	//c1->Modified();
    c1->Update();
    if (gROOT->IsBatch()) 
    {
        c1->Print("BasicSJE.gif+");
       // printf("i = %d\n", i);
    }

	}
  c1->Modified();
  // make infinite animation by adding "++" to the file name
  if (gROOT->IsBatch()) 
  c1->Print("BasicSJE.gif++");




}