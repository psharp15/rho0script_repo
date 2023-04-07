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

void pp2p_throwntrees(const char* infilename, const char* histname)
//void pp2p_throwntrees(const char* infilename, const char* histname, const char* outfilename)
//void ppvsp_rho0(string infilename, string outfilename)
    //cerr << "Hello world\n";
		// Open input files and trees
		TFile *f = new TFile(infilename);
		//TFile *f = new TFile(infilename.c_str());
		TTree *inputtree = (TTree *)f->Get("genT");

		TFile *outputfile = new TFile(histname,"RECREATE");
		//TFile *outputfile = new TFile(infilename"_analyzed.root","RECREATE");

        double Ephoton, pMeson[3], pBaryon[3],pRec[3], weight;
        int mesonPID, baryonPID, recPID;
    
		inputtree->SetBranchAddress("Ephoton",&Ephoton);
    	inputtree->SetBranchAddress("pMeson",&pMeson);
        inputtree->SetBranchAddress("pBaryon",&pBaryon);
        inputtree->SetBranchAddress("pRec",&pRec);
		inputtree->SetBranchAddress("weight",&weight);
        inputtree->SetBranchAddress("recPID",&PID_recoil);
    
		//histograms
		TH1D *h_pmiss_pp = new TH1D("h_pmiss_pp","Pmiss of pp pairs with various models; pmiss; Cross section [nb]", 100,0., 1.0);
        TH1D *h_pmiss_p = new TH1D("h_pmiss_p","Pmiss of p pairs with various models; pmiss; Cross section [nb]", 100,0., 1.0);
        TH1D *h_v3pmiss_uncut = new TH1D("h_v3pmiss_uncut","Pmiss; pmiss; Cross section [nb]", 100,0., 1.0);
        TH1D *h_t = new TH1D("h_t","t; t; counts", 100,0.,10);
		TH1D *h_u = new TH1D("h_u","u; u; counts", 100,0., 100);
        TH1D *h_t_cut = new TH1D("h_t_cut","t_cut; t; counts", 100,0.,10);
		TH1D *h_u_cut = new TH1D("h_u_cut","u_cut; u; counts", 100,0., 100);
        TH1D *h_ThetaPmiss = new TH1D("h_ThetaPmiss","ThetaPmiss; ThetaPmiss; counts", 100,0, 180);
        TH1D *h_ThetaBaryon = new TH1D("h_ThetaBaryon","ThetaBaryon; ThetaBaryon; counts", 100,0, 180);
        TH1D *h_ThetaRec = new TH1D("h_ThetaRec","ThetaRec; ThetaRec; counts", 100,0, 180);
        TH1D *h_p3_prot_recoil_gen = new TH1D("h_p3_prot_recoil_thrown","p3_prot_recoil_thrown; p3_prot_recoil_thrown; counts", 100,0, 2);
        TH1D *h_thrownPID_2 = new TH1D("h_thrownPID_2","h_thrownPID[2];PID;counts",100,2205,2230);
        TH1D *h_thrownPID_3 = new TH1D("h_thrownPID_3","h_thrownPID[3];PID;counts",100,2205,2230);

		h_pmiss_pp->Sumw2();
		h_pmiss_p->Sumw2();
		//cout<<h_pmiss_pp<<"\n";

		//Loop over tree
		for (int i=0; i< inputtree->GetEntries(); i++)
		{
            inputtree->GetEvent(i);
            
            cerr << "Working on event " << i << "\n";
            
            TVector3 vEphoton(0, 0, Ephoton);
            TVector3 vpM(pMeson[0], pMeson[1], pMeson[2]);
            TVector3 vpB(pBaryon[0], pBaryon[1], pBaryon[2]);
            TVector3 vpR(pRec[0], pRec[1], pRec[2]);

            double EM = sqrt(sq(mMeson) + vpM.Mag2());
            double EB = sqrt(sq(mN) + vpB.Mag2());
            double ER = sqrt(sq(mN) + vpR.Mag2());

            TLorentzVector p4_beam_gen (vEphoton, Ephoton);
            TLorentzVector p4_rho0_gen(vpM, EM);
            TLorentzVector p4_prot_gen(vpB, EB);
            TLorentzVector p4_rec_gen(vpR, ER);

            //cuts
            //kinematic cuts (Lead)
			TVector3 BeamMinusBaryon = p4_beam_gen.Vect() - p4_prot_gen.Vect();
			double u = sq(BeamMinusBaryon.Mag());
			TLorentzVector BeamMinusMeson = pr_beam_gen.Vect() - p4_rho0_gen.Vect();
			double t = sq(BeamMinusMeson.Mag());
            
            h_t->Fill(t);
            h_u->Fill(u);
            if ((u < 1.0) or (t< 1.0))
                continue ;
            h_t_cut->Fill(t);
            h_u_cut->Fill(u);
			//t and u above 2 above defractive region 

			//Lead Baryon cuts
            TVector3 p3_prot_gen = p4_prot_gen.Vect();
            TLorentzVector p4_pmiss = p4_rho0_gen + p4_prot_gen - p4_beam_gen;
            TVector3 p3_pmiss = p4_pmiss.Vect();
            double ThetaPmiss = p3_pmiss.Theta()*180/M_PI;
            double ThetaBaryon = p3_prot_gen.Theta()*180/M_PI;
                    
            h_ThetaBaryon->Fill(ThetaBaryon);
            h_ThetaPmiss->Fill(ThetaPmiss);
            h_p3_pmiss_uncut->Fill(p3_pmiss.Mag());
					
            //if ((ThetaBaryon< 1.5) or (v3pmiss.Mag() < 0.350) or (ThetaPmiss > 45.))
            if ((ThetaBaryon< 1.5) or (p3_pmiss.Mag() < 0.350))
                continue;
                
            h_pmiss_p ->Fill(p3_pmiss.Mag());
			// above is denominator, any pair with a proton goes there
			// below is numerator, any proton that passed above that was ALSO with another proton passes

			//recoil type cuts
               if (PID_recoil !=2212)
                continue;
            cout << PID_recoil <<endl;
            TVector3 p3_rec_gen = p4_rec_gen.Vect();
			double ThetaRec = p3_rec_gen.Theta()*180/M_PI;

            h_ThetaRec->Fill(ThetaRec);
            
			if (ThetaRec < 1.5)
                continue;
            h_p3_prot_recoil_gen->Fill(p3_rec_gen.Mag()); 
            if (p3_rec_gen.Mag() < 0.4)
                continue;
            h_pmiss_pp->Fill(p3_pmiss.Mag());
            //cout << v3pmiss.Mag() << endl;
    
			//threshold energy _> lead particles, not going to matter, recoils -> slow moving protons reduce, it better be greater than 400 MeV/c and be a proton 
		}


		outputfile->cd();
        h_pmiss_pp->Write();
		h_pmiss_p->Write();
        h_v3pmiss_uncut->Write();
        h_t->Write();
        h_u->Write();
        h_t_cut->Write();
        h_u_cut->Write();
        h_ThetaPmiss->Write();
        h_ThetaBaryon->Write();
        h_ThetaRec->Write();
        h_p3_prot_recoil_gen->Write();
        h_thrownPID_2->Write();
        h_thrownPID_3->Write();
		outputfile->Close();
    
}
