#include <iostream>
#include "TFile.h"
#include "TH1D.h"
#include "TVector3.h"
#include "TLorentzVector.h"
#include "TTree.h"
#include <math.h>
#include <vector>
//#include "helpers.hh"
//#include "constants.hh"
using namespace std;

double mN=0.93892;
double mrho0=0.77549;

double sq( double x ){return x*x ;};

void ppvsp_rho0(const char* infilename, const char* histname, const char* outfilename)
//void ppvsp_rho0(string infilename, string outfilename)
{
		// Open input files and trees
		TFile *f = new TFile(infilename);
		//TFile *f = new TFile(infilename.c_str());
		TTree *inputtree = (TTree *)f->Get("genT");

		TFile *outputfile = new TFile(histname,"RECREATE");
		//TFile *outputfile = new TFile(infilename"_analyzed.root","RECREATE");

		double Ephoton, pMeson[3], pBaryon[3], pRec[3], mMeson, mBaryon, weight;
		int meson_type, baryon_type, rec_type;

		inputtree->SetBranchAddress("Ephoton",&Ephoton);
		inputtree->SetBranchAddress("pMeson",pMeson);
		inputtree->SetBranchAddress("pBaryon",&pBaryon);
		inputtree->SetBranchAddress("pRec",&pRec);
		inputtree->SetBranchAddress("meson_type",&meson_type);
		inputtree->SetBranchAddress("mMeson",&mMeson);
		inputtree->SetBranchAddress("baryon_type",&baryon_type);
		inputtree->SetBranchAddress("mBaryon",&mBaryon);
		inputtree->SetBranchAddress("rec_type",&rec_type);
		inputtree->SetBranchAddress("weight",&weight);

		//histograms
		TH1D *h_pmiss_pp = new TH1D("h_pmiss_pp","Pmiss of pp pairs with various models; pmiss; Cross secion [nb]", 100,0.,1.0);
		TH1D *h_pmiss_p = new TH1D("h_pmiss_p","Pmiss of p pairs with various models; pmiss; Cross section [nb]", 100,0., 1.0);

		h_pmiss_pp->Sumw2();
		h_pmiss_p->Sumw2();
		//cout<<h_pmiss_pp<<"\n";

		//Loop over tree
		for (int i=0; i< inputtree->GetEntries(); i++)
		{
				inputtree->GetEvent(i);

				    TVector3 vEphoton(0, 0, Ephoton);
					TVector3 vpM(pMeson[0], pMeson[1], pMeson[2]);
					TVector3 vpB(pBaryon[0], pBaryon[1], pBaryon[2]);
					TVector3 vpR(pRec[0], pRec[1], pRec[2]);

					 double EM = sqrt(sq(mMeson) + vpM.Mag2());
					 double EB = sqrt(sq(mN) + vpB.Mag2());
					 double ER = sqrt(sq(mN) + vpR.Mag2());

					 TLorentzVector v4Ephoton (vEphoton, Ephoton);
					 TLorentzVector v4M(vpM, EM);
					 TLorentzVector v4B(vpB, EB);
					 TLorentzVector v4R(vpR, ER);

					 //cuts
					 //kinematic cuts (Lead)
					 TLorentzVector BeamMinusBaryon = v4Ephoton - v4B;
					 double u=BeamMinusBaryon.M2();

					 TLorentzVector BeamMinusMeson = v4Ephoton - v4M;
					 double t = BeamMinusMeson.M2();

					 if ((u > -2.0) or (t> -2.0))
							 continue ;
					 //t and u above 2 above defractive region

					 //Lead Baryon cuts
					 TLorentzVector v4pmiss = v4M + v4B - v4Ephoton;
					 //double ThetaPmiss = v4pmiss.Vect().Angle(v4Ephoton);
					 double ThetaPmiss = v4pmiss.Vect().Theta()*180/M_PI;
					 //double ThetaBaryon = v4B.Vect().Angle(v4M); 
					 double ThetaBaryon = v4B.Vect().Theta()*180/M_PI;

					 if ((ThetaBaryon< 1.5) or (v4pmiss.Vect().Mag() < 0.350) or (ThetaPmiss > 45.))
							 continue;

					 h_pmiss_p ->Fill(v4pmiss.Vect().Mag(),weight);
					 // above is denominator, any pair with a proton goes there
					 // below is numerator, any proton that passed above that was ALSO with another proton passes
					 if (rec_type !=2212)
							 continue;

					 //recoil type cuts
					 double ThetaRec = v4R.Vect().Theta()*180/M_PI;

					 if (ThetaRec < 1.5)
							 continue;
					 if (v4R.Vect().Mag() < 0.4)
							 continue;

					 h_pmiss_pp-> Fill(v4pmiss.Vect().Mag(),weight);

					 //threshold energy _> lead particles, not going to matter, recoils -> slow moving protons reduce, it better be greater than 400 MeV/c and be a proton 
		}

		ofstream rho0outputfile(outfilename);
		for (int i=1; i<=h_pmiss_pp->GetNbinsX(); i++)
		{
				rho0outputfile <<h_pmiss_pp->GetBinCenter(i)<<" "<<h_pmiss_pp->GetBinContent(i)<<" "<<h_pmiss_pp->GetBinError(i)<<" "
				<<h_pmiss_p->GetBinContent(i)<<" "<<h_pmiss_p->GetBinError(i)<<"\n";
		}
		rho0outputfile.close(); 

		

		outputfile->cd();
		h_pmiss_pp->Write();
		h_pmiss_p->Write();
		outputfile->Close();
}
