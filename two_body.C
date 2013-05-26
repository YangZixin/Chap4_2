#include <iostream>
#include <math.h>

const double PI = 3.1415926;
const double vint = 2 * PI;
const int STEP = 500000;

const double M_MvsM_S = 0.00000033;
const double M_JvsM_S = 0.00095;
double *x_sun = NULL;
double *y_sun = NULL;
double *x_planet = NULL;
double *y_planet = NULL;
double *x_jupiter = NULL;
double *y_jupiter = NULL;

using namespace std;

void evolv()
{
	double delta_t = 0.0002;
	double x_p, y_p, x_s, y_s, x_j, y_j, rps, rjs, rpj;
	double vx_p, vy_p, vx_s, vy_s, vx_j, vy_j;

	x_p = 1;
	vy_p = vint;
	vy_j = vint/2;
	x_j = 5.2;

	// x_sun =new double[STEP];
	// y_sun =new double[STEP];
	x_planet =new double[STEP];
	y_planet =new double[STEP];
	x_jupiter =new double[STEP];
	y_jupiter =new double[STEP];


	for (int i = 0; i < STEP; ++i)
	{
		rps = sqrt((x_p-x_s) * (x_p-x_s) + (y_p-y_s) * (y_p-y_s));
		rjs = sqrt((x_j-x_s) * (x_j-x_s) + (y_j-y_s) * (y_j-y_s));
		rpj = sqrt((x_p-x_j) * (x_p-x_j) + (y_p-y_j) * (y_p-y_j));
		
		// x_sun[i] = x_s;
		// y_sun[i] = y_s;
		x_planet[i] = x_p;
		y_planet[i] = y_p;
		x_jupiter[i] = x_j;
		y_jupiter[i] = y_j;

		vx_p -= 4 * PI * PI * (x_p - x_s) * delta_t / pow(rps,3) + 4 * PI * PI * M_JvsM_S *(x_p - x_j) * delta_t / pow(rpj,3);
		vy_p -= 4 * PI * PI * (y_p - y_s) * delta_t / pow(rps,3) + 4 * PI * PI * M_JvsM_S *(y_p - y_j) * delta_t / pow(rpj,3);
		vx_j -= 4 * PI * PI * (x_j - x_s) * delta_t / pow(rjs,3) + 4 * PI * PI * M_JvsM_S *(x_j - x_p) * delta_t / pow(rpj,3);
		vy_j -= 4 * PI * PI * (y_j - y_s) * delta_t / pow(rjs,3) + 4 * PI * PI * M_JvsM_S *(y_j - y_p) * delta_t / pow(rpj,3);
	
		x_p += vx_p * delta_t;
		y_p += vy_p * delta_t;
		x_j += vx_j * delta_t;
		y_j += vy_j * delta_t;
		// x_s = - M_JvsM_S * x_j - M_MvsM_S * x_p;
		// y_s = - M_JvsM_S * y_j - M_MvsM_S * y_p;
		// cout<<x_jupiter[i]<<"   "<<y_jupiter[i]<<endl;
		// cout<<x_planet[i]<<"   "<<y_planet[i]<<endl;
	}
}
/*int main()
{
	evolv(500);
	return 0;
}*/

void two_body()
{
	// gSystem->Unlink("GRanim.gif"); // delete old file
	
	// c1 = new TCanvas("c1","The Special Solar System",200,10,600,400);

	// for (int i = 0; i < 100; ++i)
	// {
 	evolv();

	TGraph* gr1 = new TGraph(STEP, x_jupiter, y_jupiter);
	TGraph* gr2 = new TGraph(STEP, x_planet, y_planet);
	gr1->GetXaxis()->SetTitle("X (AU/yr)");
	gr1->GetYaxis()->SetTitle("Y (AU/yr");
	gr1->SetTitle("The Special Solar System");
	// gr1->GetXaxis()->SetLimits(-20,20);
	// gr1->GetYaxis()->SetRangeUser(-20,20);
	gr1->SetMarkerStyle(1);
	gr1->SetMarkerSize(1);
	gr1->SetMarkerColor(2);
	gr1->Draw("AP");

	gr2->SetLineWidth(3);
	gr2->SetMarkerStyle(1);
	gr2->SetLineColor(2);
	gr2->SetMarkerColor(30);
	gr2->Draw("P");

	// //c1->Modified();
 //    c1->Update();
 //    if (gROOT->IsBatch()) 
 //    {
 //        c1->Print("GRanim.gif+");
 //       // printf("i = %d\n", i);
 //    }

	// }
 //  c1->Modified();
 //  // make infinite animation by adding "++" to the file name
 //  if (gROOT->IsBatch()) 
 //  c1->Print("GRanim.gif++");




}