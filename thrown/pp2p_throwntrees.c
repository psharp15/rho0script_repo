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
		TTree *inputtree = (TTree *)f->Get("Thrown_Tree");

		TFile *outputfile = new TFile(histname,"RECREATE");
		//TFile *outputfile = new TFile(infilename"_analyzed.root","RECREATE");

        TClonesArray *thrownparticles = new TClonesArray();
		TLorentzVector *p4_beam_thrown=0;
        float weight;
        int thrownPID[4];
    
		inputtree->SetBranchAddress("ThrownBeam__P4",&p4_beam_thrown);
    	inputtree->SetBranchAddress("Thrown__PID",&thrownPID);
        inputtree->SetBranchAddress("Thrown__P4",&thrownparticles);
		inputtree->SetBranchAddress("MCWeight",&weight);
    
        TLorentzVector p4_pip_thrown, p4_pim_thrown, p4_prot1_thrown, p4_prot2_thrown;

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
        TH1D *h_p3_prot_recoil_thrown = new TH1D("h_p3_prot_recoil_thrown","p3_prot_recoil_thrown; p3_prot_recoil_thrown; counts", 100,0, 2);
        TH1D *h_thrownPID_2 = new TH1D("h_thrownPID_2","h_thrownPID[2];PID;counts",100,2205,2230);
        TH1D *h_thrownPID_3 = new TH1D("h_thrownPID_3","h_thrownPID[3];PID;counts",100,2205,2230);

		h_pmiss_pp->Sumw2();
		h_pmiss_p->Sumw2();
		//cout<<h_pmiss_pp<<"\n";

		//Loop over tree
		for (int i=0; i< inputtree->GetEntries(); i++)
		{
            inputtree->GetEvent(i);
            Int_t nlines = thrownparticles->GetEntriesFast(); 
            TLorentzVector *p4_pip_thrown = (TLorentzVector*)thrownparticles->At(0);
            TLorentzVector *p4_pim_thrown = (TLorentzVector*)thrownparticles->At(1);
            TLorentzVector *p4_prot1_thrown = (TLorentzVector*)thrownparticles->At(2);
            TLorentzVector *p4_prot2_thrown = (TLorentzVector*)thrownparticles->At(3);
            //cout<<thrownPID[2] <<endl;
           
            //h_thrownPID_2->Fill(thrownPID[2]);
            //h_thrownPID_3->Fill(thrownPID[3]);
            
            h_thrownPID_2->Fill(thrownPID[2]);
            h_thrownPID_3->Fill(thrownPID[3]);
            
            cerr << "Working on event " << i << "\n";
            
            TLorentzVector p4_prot_lead_thrown;
            TLorentzVector p4_prot_recoil_thrown;
            TLorentzVector p4_rho0_thrown =(*p4_pip_thrown)+(*p4_pim_thrown);
            int PID_lead, PID_recoil;
            
            if (p4_prot1_thrown->P() > 1.2 && p4_prot2_thrown->P() < 1)
            {
                PID_lead = thrownPID[2];
                p4_prot_lead_thrown = *p4_prot1_thrown;
                PID_recoil = thrownPID[3];
                p4_prot_recoil_thrown = *p4_prot2_thrown;
            }
            else if (p4_prot1_thrown->P() < 1 && p4_prot2_thrown->P() > 1.2)
            {
                PID_lead = thrownPID[3];
                p4_prot_lead_thrown = *p4_prot2_thrown;
                PID_recoil = thrownPID[2];
                p4_prot_recoil_thrown = *p4_prot1_thrown;
            }
            else
                continue;
            cout << PID_recoil <<endl;
         
            //cuts
            //kinematic cuts (Lead)
            TVector3 p3_beam_thrown = p4_beam_thrown->Vect();
            TVector3 p3_prot_lead_thrown = p4_prot_lead_thrown.Vect();
			TVector3 BeamMinusBaryon = p3_beam_thrown - p3_prot_lead_thrown;
			double u = sq(BeamMinusBaryon.Mag());
			TLorentzVector BeamMinusMeson = *p4_beam_thrown - p4_rho0_thrown;
			double t = sq(BeamMinusMeson.Mag());
            
            h_t->Fill(t);
            h_u->Fill(u);
            if ((u < 1.0) or (t< 1.0))
                continue ;
            h_t_cut->Fill(t);
            h_u_cut->Fill(u);
			//t and u above 2 above defractive region 

			//Lead Baryon cuts
            TLorentzVector v4pmiss = p4_rho0_thrown + p4_prot_lead_thrown - *p4_beam_thrown;
            TVector3 v3pmiss = v4pmiss.Vect();
            double ThetaPmiss = v3pmiss.Theta()*180/M_PI;
            double ThetaBaryon = p3_prot_lead_thrown.Theta()*180/M_PI;
                    
            h_ThetaBaryon->Fill(ThetaBaryon);
            h_ThetaPmiss->Fill(ThetaPmiss);
            h_v3pmiss_uncut->Fill(v3pmiss.Mag());
					
            //if ((ThetaBaryon< 1.5) or (v3pmiss.Mag() < 0.350) or (ThetaPmiss > 45.))
            if ((ThetaBaryon< 1.5) or (v3pmiss.Mag() < 0.350))
                continue;
                
            TVector3 v3pmiss_p = v3pmiss;
            h_pmiss_p ->Fill(v3pmiss_p.Mag());
			// above is denominator, any pair with a proton goes there
			// below is numerator, any proton that passed above that was ALSO with another proton passes

			//recoil type cuts
               if (PID_recoil !=2212)
                continue;
            cout << PID_recoil <<endl;
            TVector3 p3_prot_recoil_thrown = p4_prot_recoil_thrown.Vect();
			double ThetaRec = p3_prot_recoil_thrown.Theta()*180/M_PI;

            h_ThetaRec->Fill(ThetaRec);
            
			if (ThetaRec < 1.5)
                continue;
            h_p3_prot_recoil_thrown->Fill(p3_prot_recoil_thrown.Mag()); 
            if (p3_prot_recoil_thrown.Mag() < 0.4)
                continue;
            TVector3 v3pmiss_pp = v3pmiss;
            h_pmiss_pp->Fill(v3pmiss.Mag());
            //cout << v3pmiss.Mag() << endl;
    
			//threshold energy _> lead particles, not going to matter, recoils -> slow moving protons reduce, it better be greater than 400 MeV/c and be a proton 
		}

/*		ofstream rho0outputfile(outfilename);
		for (int i=1; i<=h_pmiss_pp->GetNbinsX(); i++)
		{
				rho0outputfile <<h_pmiss_pp->GetBinCenter(i)<<" "<<h_pmiss_pp->GetBinContent(i)<<" "<<h_pmiss_pp->GetBinError(i)<<" "
				<<h_pmiss_p->GetBinContent(i)<<" "<<h_pmiss_p->GetBinError(i)<<"\n"; 
		}
		rho0outputfile.close(); */

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
        h_p3_prot_recoil_thrown->Write();
        h_thrownPID_2->Write();
        h_thrownPID_3->Write();
		outputfile->Close();
    
}
