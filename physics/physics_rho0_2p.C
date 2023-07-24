#include <iostream>
using namespace std;

double mN = 0.983;

double rhoyield(TH1D* rhomass_hist)
{
    double yleft = rhomass_hist->GetBinContent(19);
    double yright = rhomass_hist->GetBinContent(28);

    double integral = rhomass_hist->Integral(19,28);
    return integral - 0.5*(yright-yleft);
}

double rhoyield_anderror(TH1D* rhomass_hist, double &error)
{
    double yleft = rhomass_hist->GetBinContent(19);
    double yright = rhomass_hist->GetBinContent(28);

    double integral = rhomass_hist->Integral(19,28);
    error = sqrt(integral);
    return integral - 0.5*(yright-yleft);
}

void physics_rho0_2p(const char *inputfilename, const char *inputTreename, const char *outfilename, const char *outfileCSVname)
{
  cerr << "Hello world\n";
  cerr << "Trying to get " << inputfilename << "\n";

  TFile *inputFile = new TFile(inputfilename);
  cerr << "Got the file. and the pointer is:  " << inputFile << "\n";
  if (inputFile->IsZombie()){
      cerr << "The file is not good! Check file name.\n";
      return;
  }
  cerr <<"Trying to get tree with name: " << inputTreename << "\n";
  TTree *inputTree = (TTree*) inputFile-> Get(inputTreename);
  if (!inputTree){
      cerr << "Failed to grab tree. Check tree name!\n";
      return;
  }
  cerr << "Got it! " << inputTreename << "\n";
  TFile *fout=new TFile(outfilename,"RECREATE");

  ULong64_t event;
  TLorentzVector *p4_pip_kin=0;
  TLorentzVector *p4_pim_kin=0;
  TLorentzVector *x4_prot_lead_kin=0;
  TLorentzVector *x4_prot_recoil_kin=0;
  TLorentzVector *x4_pip_kin=0;
  TLorentzVector *x4_pim_kin=0;
  TLorentzVector *p4_beam_kin=0;
  TLorentzVector *x4_beam_kin=0;
  double weight;
  double RF_time;
  double t;
  TLorentzVector *p4_beam_thrown=0;
  TLorentzVector *p4_pip_thrown=0;
  TLorentzVector *p4_pim_thrown=0;
  double thrownS;
  double thrownT;
  double thrownU;
  TLorentzVector *p4_prot_lead_kin=0;
  TLorentzVector *p4_prot_recoil_kin=0;
  TLorentzVector *p4_prot_lead_thrown=0;
  TLorentzVector *p4_prot_recoil_thrown=0;

  if (!inputTree)
      {cout<< "Couldn't get the inputTree. Check spelling"<<endl;}

  inputTree->SetBranchAddress("pip_p4_kin",&p4_pip_kin);
  inputTree->SetBranchAddress("pim_p4_kin",&p4_pim_kin);
  inputTree->SetBranchAddress("p4_prot_lead",&p4_prot_lead_kin);
  inputTree->SetBranchAddress("p4_prot_recoil",&p4_prot_recoil_kin);
  inputTree->SetBranchAddress("x4_prot_lead",&x4_prot_lead_kin);
  inputTree->SetBranchAddress("x4_prot_recoil",&x4_prot_recoil_kin);
  inputTree->SetBranchAddress("beam_p4_kin",&p4_beam_kin);
  inputTree->SetBranchAddress("accidweight",&weight);
  inputTree->SetBranchAddress("RF_time",&RF_time);
  inputTree->SetBranchAddress("event",&event);
  inputTree->SetBranchAddress("thrownBeam",&p4_beam_thrown);
  inputTree->SetBranchAddress("thrownPiPlus",&p4_pip_thrown);
  inputTree->SetBranchAddress("thrownPiMinus",&p4_pim_thrown);
  inputTree->SetBranchAddress("p4_prot_recoil_thrown",&p4_prot_recoil_thrown);
  inputTree->SetBranchAddress("p4_prot_lead_thrown",&p4_prot_lead_thrown);


/********************************************** Defining Histograms **********************************************/

  TDirectory * dir_UnCut = fout->mkdir("UnCut");
  TDirectory * dir_ZVertCut = fout->mkdir("ZVert-Cut");
  TDirectory * dir_MisID = fout->mkdir("MisID-Cut");
  TDirectory * dir_Dalitz = fout->mkdir("Dalitz_1.3-Cut");
  TDirectory * dir_kmiss_TCut = fout->mkdir("KMiss_vs_t-distributions");
  TDirectory * dir_pCMperp_TCut = fout->mkdir("pCMperp_vs_t-distributions");

  /****** Vert ******/
  TH1D *h_zprotleadvertex = new TH1D ("protLead Zvertex","protLead Zvertex;Vertex z [cm];Counts",50,0,100);
  TH1D *h_zprotleadvertex_zcut = new TH1D ("protLead Zvertex CUT","protLead Zvertex;Vertex z [cm];Counts",50,0,100);

  /****** Rho0 Mass ******/
  TH1D *h_rho0counts_uncut = new TH1D("Rho0_Counts_uncut","Rho0Counts_uncut;Mass [GeV];Counts",90,0,3);
  TH1D *h_rho0counts_zcut = new TH1D("Rho0_Counts_Zcut","Rho0Counts_ZCut;Mass [GeV];Counts",90,0,3);
  TH1D *h_rho0counts_misid = new TH1D("Rho0_Counts_MisId","Rho0Counts_ZCut;Mass [GeV];Counts",90,0,3);
  TH1D *h_rho0counts_lowerpcut = new TH1D("Rho0_Counts_LowerMomCut","Rho0Counts_lowerpcut;Mass [GeV];Counts",90,0,3);
  TH1D *h_rho0counts_t_1_15 = new TH1D("Rho0_Counts_t_1_15","Rho0Counts_t_1_15;Mass [GeV];Counts",90,0,3);
  TH1D *h_rho0counts_t_15_2 = new TH1D("Rho0_Counts_t_15_2","Rho0Counts_t_1_15;Mass [GeV];Counts",90,0,3);
  TH1D *h_rho0counts_t_2_25 = new TH1D("Rho0_Counts_t_2_25","Rho0Counts_t_1_15;Mass [GeV];Counts",90,0,3);
  TH1D *h_rho0counts_t_25_3 = new TH1D("Rho0_Counts_t_25_3","Rho0Counts_t_1_15;Mass [GeV];Counts",90,0,3);
  TH1D *h_rho0counts_t_3_4 = new TH1D("Rho0_Counts_t_3_4","Rho0Counts_t_1_15;Mass [GeV];Counts",90,0,3);

  /****** Pi+ Mom vs Angle ******/
  TH2D *h_pip_p_theta_uncut = new TH2D ("pip_p_theta_uncut","Pip_PVSTheta_UNCUT ; theta [degree];p [GeV]; Counts",200,0,140,200,0,10);
  TH2D *h_pip_p_theta_misid = new TH2D ("pip_p_theta_misid","Pip_PVSTheta_misid ; theta [degree];p [GeV]; Counts",200,0,140,200,0,10);


  /****** Pi- Mom vs Angle ******/
  TH2D *h_pim_p_theta_uncut = new TH2D ("pim_p_theta_uncut","Pim_PVSTheta_UNCUT ; theta [degree];p [GeV]; Counts",200,0,140,200,0,10);
  TH2D *h_pim_p_theta_misid = new TH2D ("pim_p_theta_misid","Pim_PVSTheta_misid ; theta [degree];p [GeV]; Counts",200,0,140,200,0,10);

  /****** ProtLead Mom vs Angle ******/
  TH2D *h_protL_p_theta_uncut = new TH2D ("h_protL_p_theta_uncut","ProtL_PVSTheta_uncut ; theta [degree];p [GeV]; Counts",200,0,140,200,0,10);
  TH2D *h_protL_p_theta_misid = new TH2D ("h_protL_p_theta_misid","ProtL_PVSTheta_misid ; theta [degree];p [GeV]; Counts",200,0,140,200,0,10);

  /****** ProtRecoil Mom vs Angle ******/
  TH2D *h_protR_p_theta_uncut = new TH2D ("h_protR_p_theta_uncut","ProtR_PVSTheta_uncut ; theta [degree];p [GeV]; Counts",200,0,140,200,0,10);
  //TH2D *h_protR_p_theta_misid = new TH2D ("h_protR_p_theta_misid","ProtL_PVSTheta_misid ; theta [degree];p [GeV]; Counts",200,0,140,200,0,10);

  /****** Dalitz Analysis ******/
  TH2D *h_pippim_VS_pipprotL = new TH2D ("h_pippim_VS_pipprotL","PipProt Dalitz; Mom(pi+ & pi-);Mom(pip & prot);counts",100, 0, 3, 100, 0, 5);
  TH2D *h_pippim_VS_pimprotL = new TH2D ("h_pippim_VS_pimprotL","PimProt Dalitz; Mom(pi+ & pi-);Mom(pi- & prot);counts",100, 0, 3, 100, 0, 5);
  TH2D *h_pipprot_VS_pimprotL = new TH2D ("h_pipprot_VS_pimprotL","PipProt vs PimProt Dalitz; Mom(pi+ & prot);Mom(pi- & prot);counts",100, 0, 5, 100, 0, 5);
  TH2D *h_pippim_VS_pipprotL_lowerpcut = new TH2D ("h_pippim_VS_pipprotL_lowerpcut","PipProt Dalitz; Mom(pi+ & pi-);Mom(pip & prot);counts",100, 0, 3, 100, 0, 5);
  TH2D *h_pippim_VS_pimprotL_lowerpcut = new TH2D ("h_pippim_VS_pimprotL_lowerpcut","PimProt Dalitz; Mom(pi+ & pi-);Mom(pi- & prot);counts",100, 0, 3, 100, 0, 5);

  /****** Recoil Momentum ******/
  TH1D *h_precoil = new TH1D("P Recoil","Momentum of Recoil ;precoil[GeV];Counts",14,0.3,1);
  TH2D *h_rho_vs_precoil = new TH2D("h_rho_vs_precoil", "h_rho_vs_precoil;rho mass; precoil; counts",90,0,3,7,0.3,1);


  /****** COM Motion  Plots ******/
  TH1D *h_pCMperp = new TH1D("h_pCMperp","pCMperp;pCMperp[GeV];Counts",20,-1,1);
  TH2D *h_rho_vs_pCMperp = new TH2D("h_rho_vs_pCMperp", "rho_vs_pCMperp;rho mass; pCMperp; counts",90,0,3,20,-0.5,0.5);
  TH1D *h_pCMperp_1_15 = new TH1D("h_pCMperp_1_15","pCMperp 1_15;pCMperp[GeV];Counts",40,-1,1);
  TH2D *h_rho_vs_pCMperp_1_15 = new TH2D("h_rho_vs_pCMperp_1_15", "rho_vs_pCMperp_1_15;rho mass; pCMperp; counts",90,0,3,40,-1,1);
  TH1D *h_pCMperp_15_2 = new TH1D("h_pCMperp_15_2","pCMperp 15_2;pCMperp[GeV];Counts",40,-1,1);
  TH2D *h_rho_vs_pCMperp_15_2 = new TH2D("h_rho_vs_pCMperp_15_2", "rho_vs_pCMperp_15_2;rho mass; pCMperp; counts",90,0,3,40,-1,1);
  TH1D *h_pCMperp_2_25 = new TH1D("h_pCMperp_2_25","pCMperp 2_25;pCMperp[GeV];Counts",40,-1,1);
  TH2D *h_rho_vs_pCMperp_2_25 = new TH2D("h_rho_vs_pCMperp_2_25", "rho_vs_pCMperp_2_25;rho mass; pCMperp; counts",90,0,3,40,-1,1);
  TH1D *h_pCMperp_25_3 = new TH1D("h_pCMperp_25_3","pCMperp 25_3;pCMperp[GeV];Counts",40,-1,1);
  TH2D *h_rho_vs_pCMperp_25_3 = new TH2D("h_rho_vs_pCMperp_25_3", "rho_vs_pCMperp_25_3;rho mass; pCMperp; counts",90,0,3,40,-1,1);
  TH1D *h_pCMperp_3_4 = new TH1D("h_pCMperp_3_4","pCMperp 3_4;pCMperp[GeV];Counts",40,-1,1);
  TH2D *h_rho_vs_pCMperp_3_4 = new TH2D("h_rho_vs_pCMperp_3_4", "rho_vs_pCMperp_3_4;rho mass; pCMperp; counts",90,0,3,40,-1,1);

  /*** KMISS t-Dist ***/
  TH1D *h_kmiss = new TH1D("KMiss","KMiss;KMiss[GeV];Counts",12,0.4,1);
  TH2D *h_rho_vs_kmiss = new TH2D("h_rho_vs_kmiss", "h_rho_vs_kmiss;rho mass; kmiss; counts",90,0,3,6,0.4,1);
  TH1D *h_kmiss_1_15 = new TH1D("KMiss1_15","KMiss1_15;KMiss[GeV];Counts",12,0.4,1);
  TH2D *h_rho_vs_kmiss_1_15 = new TH2D("h_rho_vs_kmiss_1_15", "h_rho_vs_kmiss_1_15;rho mass; kmiss; counts",90,0,3,6,0.4,1);
  TH1D *h_kmiss_15_2 = new TH1D("KMiss15_2","KMiss15_2;KMiss[GeV];Counts",12,0.4,1);
  TH2D *h_rho_vs_kmiss_15_2 = new TH2D("h_rho_vs_kmiss_15_2", "h_rho_vs_kmiss_15_2;rho mass; kmiss; counts",90,0,3,6,0.4,1);
  TH1D *h_kmiss_2_25 = new TH1D("KMiss2_25","KMiss2_25;KMiss[GeV];Counts",12,0.4,1);
  TH2D *h_rho_vs_kmiss_2_25 = new TH2D("h_rho_vs_kmiss_2_25", "h_rho_vs_kmiss_2_25;rho mass; kmiss; counts",90,0,3,6,0.4,1);
  TH1D *h_kmiss_25_3 = new TH1D("KMiss25_3","KMiss25_3;KMiss[GeV];Counts",12,0.4,1);
  TH2D *h_rho_vs_kmiss_25_3 = new TH2D("h_rho_vs_kmiss_25_3", "h_rho_vs_kmiss_25_3;rho mass; kmiss; counts",90,0,3,6,0.4,1);
  TH1D *h_kmiss_3_4 = new TH1D("KMiss3_4","KMiss3_4;KMiss[GeV];Counts",12,0.4,1);
  TH2D *h_rho_vs_kmiss_3_4 = new TH2D("h_rho_vs_kmiss_3_4", "h_rho_vs_kmiss_3_4;rho mass; kmiss; counts",90,0,3,6,0.4,1);

  /*** Opening Angle ***/
  TH1D *h_pairangle = new TH1D("h_pairangle","Pair Angle; angle; counts",90,-1,0);
  h_pairangle->Sumw2();
  TH2D *h_rho_vs_pairangle = new TH2D("h_rho_vs_pairangle", "h_rho_vs_pairangle;rho mass; pair angle [cos[angle]]; counts",90,0,3,90,-1,0);
  h_rho_vs_pairangle->Sumw2();


/********************************************** Event Loop **********************************************/
for( int event=0; event < inputTree-> GetEntries(); event++){

  if (event%10000==0)
  cerr << "Working on event " << event << "\n";

  inputTree-> GetEvent(event);

/********************************************** Defining Variables **********************************************/

    //cerr << "Defining variables " << "\n";

  TLorentzVector p4_rho0_kin = (*p4_pip_kin)+(*p4_pim_kin);
  double Mpipi = p4_rho0_kin.M();
  TLorentzVector p4_pmiss = (*p4_prot_lead_kin+ p4_rho0_kin - *p4_beam_kin);
  TVector3 p3_pmiss = p4_pmiss.Vect();
  double pmiss = p3_pmiss.Mag();
  TLorentzVector p4_rho0_thrown =(*p4_pip_thrown)+(*p4_pim_thrown);
  TLorentzVector p4_pmiss_thrown = (*p4_prot_lead_thrown + (*p4_pip_thrown + *p4_pim_thrown) - *p4_beam_thrown ); //pmiss = lead + rho - beam
  TVector3 p3_pmiss_thrown = p4_pmiss_thrown.Vect();
  TVector3 v3_prot_lead = p4_prot_lead_kin->Vect();
  TVector3 v3_prot_recoil = p4_prot_recoil_kin->Vect();

  TVector3 v3_prot_lead_thrown = p4_prot_lead_thrown->Vect();
  TVector3 beam_mom = p4_beam_kin->Vect();
  TVector3 v3_pim = p4_pim_kin->Vect();
  TVector3 v3_pip = p4_pip_kin->Vect();
  TVector3 v3_pip_thrown = p4_pip_thrown->Vect();
  TVector3 v3_rho = p4_rho0_kin.Vect();
  double t_mandel = (*p4_beam_kin - p4_rho0_kin).M2();
  double s_mandel = (*p4_prot_lead_kin + p4_rho0_kin).M2();

  TLorentzVector p4_pip_protL = *p4_prot_lead_kin + *p4_pip_kin;
  TLorentzVector p4_pim_protL = *p4_prot_lead_kin + *p4_pim_kin;

  TLorentzVector delta4mom = (p4_rho0_kin + *p4_prot_lead_kin + *p4_prot_recoil_kin - TLorentzVector( 0,0,0,2*mN) - *p4_beam_kin);
  double pmissT = (p3_pmiss.Pt()); //also perp works
  double pmiss_minus = (p4_pmiss.E()-p4_pmiss.Z());
  double kmiss = (mN*sqrt((mN*mN + pmissT*pmissT)/(pmiss_minus*(2*mN-pmiss_minus)) - 1));

  TLorentzVector p4_COM= p4_pmiss + *p4_prot_recoil_kin;
  double pCMX = p4_COM.X(); //left in the hall
  double pCMY = p4_COM.Y(); // up in the hall
  TVector3 perphat = p4_beam_kin->Vect().Cross(p4_pmiss.Vect()).Unit(); //physics left and right // should be the same as X and Y in the hall vs gcf
  double pCMperp = p4_COM.Vect().Dot(perphat);

  if (p4_COM.Minus()/(2.4*mN) + 2./M_PI*v3_prot_lead.Theta() < 1.){
      continue;
  }

/********************************************** Filling Un Cut Histograms **********************************************/
    //cerr << "Filling uncut hists " << "\n";

  h_rho0counts_uncut->Fill(p4_rho0_kin.M(),weight);

  //cerr << "Filled h_rho0counts_uncut hists " << "\n";
  h_zprotleadvertex->Fill(x4_prot_lead_kin->Z(),weight);

  //cerr << "Filled h_zprotleadvertex hists " << "\n";
  h_pip_p_theta_uncut->Fill(180./M_PI*v3_pip.Theta(),v3_pip.Mag(),weight);
  //cerr << "Filled h_pip_p_theta_uncut hists " << "\n";
  h_pim_p_theta_uncut->Fill(180./M_PI*v3_pim.Theta(),v3_pim.Mag(),weight);
  //cerr << "Filled h_pim_p_theta_uncut hists " << "\n";
  h_protL_p_theta_uncut->Fill(180./M_PI*v3_prot_lead.Theta(),v3_prot_lead.Mag(),weight);
  h_protR_p_theta_uncut->Fill(180./M_PI*v3_prot_recoil.Theta(),v3_prot_recoil.Mag(),weight);
   //cerr << "Filled h_protL_p_theta_uncut hists " << "\n";

  //cerr << "Filled uncut hists " << "\n";

/********************************************** Z-Vertex Cut **********************************************/
  if (x4_prot_lead_kin->Z()< 50 || x4_prot_lead_kin->Z()>80){
      continue;
  }
  //cerr << "z-vertex cuts " << "\n";

  h_zprotleadvertex_zcut->Fill(x4_prot_lead_kin->Z(),weight);
  h_rho0counts_zcut->Fill(p4_rho0_kin.M(),weight);

/********************************************** Missed PID - Cut **********************************************/

    if (v3_pip.Mag() > exp (-0.08* (180./M_PI*v3_pip.Theta()) +2.85) -0.1)
      continue;

   // cerr << "mis-id of pi+ and prot" << "\n";

  h_pip_p_theta_misid->Fill(180./M_PI*v3_pip.Theta(),v3_pip.Mag(),weight);
  h_pim_p_theta_misid->Fill(180./M_PI*v3_pim.Theta(),v3_pim.Mag(),weight);
  h_protL_p_theta_misid->Fill(180./M_PI*v3_prot_lead.Theta(),v3_prot_lead.Mag(),weight);
  h_rho0counts_misid->Fill(p4_rho0_kin.M(),weight);

/********************************************** Dalitz Analysis **********************************************/
    h_pippim_VS_pipprotL->Fill(p4_rho0_kin.M(),(p4_pip_protL.M()),weight);
    h_pippim_VS_pimprotL->Fill(p4_rho0_kin.M(),(p4_pim_protL.M()),weight);
    h_pipprot_VS_pimprotL->Fill(p4_pip_protL.M(),(p4_pim_protL.M()),weight);

    if (p4_pip_protL.M() < 1.3){
        continue;
    }
    if (p4_pim_protL.M() < 1.3){
        continue;
    }

    h_pippim_VS_pipprotL_lowerpcut->Fill(p4_rho0_kin.M(),(p4_pip_protL.M()),weight);
    h_pippim_VS_pimprotL_lowerpcut->Fill(p4_rho0_kin.M(),(p4_pim_protL.M()),weight);
    h_rho0counts_lowerpcut->Fill(p4_rho0_kin.M(),weight);


/********************************************** Money Plots **********************************************/
    //Abs t >1
    h_kmiss->Fill(kmiss,weight);
    h_rho_vs_kmiss->Fill(p4_rho0_kin.M(),kmiss,weight);

    h_pCMperp->Fill(pCMperp,weight);
    h_rho_vs_pCMperp->Fill(p4_rho0_kin.M(),pCMperp,weight);

    double pairangle = p4_pmiss.Vect().Angle(v3_prot_recoil);


    if (t_mandel > -1.5){
        //h_kmiss_1_15->Fill(kmiss,weight);
        //h_rho_vs_kmiss_1_15->Fill(p4_rho0_kin.M(),kmiss,weight);
    continue;
    }
    if (kmiss>0.4){
    if (TMath::Abs(Mpipi - 0.77)<0.13){
    h_pairangle->Fill(TMath::Cos(pairangle),weight);
    h_rho_vs_pairangle->Fill(p4_rho0_kin.M(),TMath::Cos(pairangle),weight);
    h_rho_vs_pCMperp->Fill(p4_rho0_kin.M(),pCMperp,weight);
    }
    h_precoil->Fill(v3_prot_recoil.Mag(),weight);
    h_rho_vs_precoil->Fill(p4_rho0_kin.M(),v3_prot_recoil.Mag(),weight);
    }
/********************************************** T-Cuts **********************************************/

    if (kmiss>0.4){
    if (TMath::Abs(Mpipi - 0.77)<0.13){
    h_pCMperp_1_15->Fill(pCMperp,weight);
    }
    h_rho_vs_pCMperp_1_15->Fill(p4_rho0_kin.M(),pCMperp,weight);
    }
    h_rho0counts_t_1_15->Fill(p4_rho0_kin.M(),weight);

    if (t_mandel > -2){
        h_kmiss_15_2->Fill(kmiss,weight);
        h_rho_vs_kmiss_15_2->Fill(p4_rho0_kin.M(),kmiss,weight);
        if (kmiss>0.4){
        if (TMath::Abs(Mpipi - 0.77)<0.13){
        h_pCMperp_15_2->Fill(pCMperp,weight);
        }
        h_rho_vs_pCMperp_15_2->Fill(p4_rho0_kin.M(),pCMperp,weight);
        }
        h_rho0counts_t_15_2->Fill(p4_rho0_kin.M(),weight);
        continue;
    }

    if (t_mandel > -2.5){
        h_kmiss_2_25->Fill(kmiss,weight);
        h_rho_vs_kmiss_2_25->Fill(p4_rho0_kin.M(),kmiss,weight);

        if (kmiss>0.4){
        if (TMath::Abs(Mpipi - 0.77)<0.13){
        h_pCMperp_2_25->Fill(pCMperp,weight);
        }
        h_rho_vs_pCMperp_2_25->Fill(p4_rho0_kin.M(),pCMperp,weight);
        }
        h_rho0counts_t_2_25->Fill(p4_rho0_kin.M(),weight);

        continue;
    }

    if (t_mandel > -3){
        h_kmiss_25_3->Fill(kmiss,weight);
        h_rho_vs_kmiss_25_3->Fill(p4_rho0_kin.M(),kmiss,weight);

        if (kmiss>0.4){
        if (TMath::Abs(Mpipi - 0.77)<0.13){
        h_pCMperp_25_3->Fill(pCMperp,weight);
        }
        h_rho_vs_pCMperp_25_3->Fill(p4_rho0_kin.M(),pCMperp,weight);
        }
        h_rho0counts_t_25_3->Fill(p4_rho0_kin.M(),weight);
        continue;
    }



    if (t_mandel > -4){
        h_kmiss_3_4->Fill(kmiss,weight);
        h_rho_vs_kmiss_3_4->Fill(p4_rho0_kin.M(),kmiss,weight);

        if (kmiss>0.4){
        if (TMath::Abs(Mpipi - 0.77)<0.13){
        h_pCMperp_3_4->Fill(pCMperp,weight);
         }
        h_rho_vs_pCMperp_3_4->Fill(p4_rho0_kin.M(),pCMperp,weight);
        }
        h_rho0counts_t_3_4->Fill(p4_rho0_kin.M(),weight);
        continue;
    }


    }
cerr << "closing inputfile" << "\n";

inputFile->Close();

/********************************************** Count the Rho0s **********************************************/


    ofstream rho0outputfile(outfileCSVname);
    //kmiss
    cout << "#Yield vs Kmiss\n"
        << "#[left edge] [bin center] [right edge] [uncertainty] [yield] \n";
        rho0outputfile <<"#Total Yield vs Kmiss\n"<< "#[left edge] , #[bin center] , #[right edge] ,#[uncertainty] ,#[yield] \n";
        for (int i=1; i<= 6; i++){
        cout << h_rho_vs_kmiss->GetYaxis()->GetBinLowEdge(i)<< " " <<
         h_rho_vs_kmiss->GetYaxis()->GetBinCenter(i)<< " " <<
         h_rho_vs_kmiss->GetYaxis()->GetBinUpEdge(i)<< " "<<
         h_rho_vs_kmiss->GetBinError(i)<< " ";
         char temp[50];
    //projections
        sprintf(temp,"kmiss_bin%d",i);
        TH1D* thismass_spectrum = h_rho_vs_kmiss->ProjectionX(temp,i,i);
        double error;
        double yield = rhoyield_anderror(thismass_spectrum,error);
        cout << yield << endl;
        rho0outputfile<< h_rho_vs_kmiss->GetYaxis()->GetBinLowEdge(i)<<","<<h_rho_vs_kmiss->GetYaxis()->GetBinCenter(i)<<","<<h_rho_vs_kmiss->GetYaxis()->GetBinUpEdge(i)<<","<< yield <<"," << error <<endl;
        }
/*         //kmiss h_rho_vs_kmiss_1_15
        cout << "#Yield vs h_rho_vs_kmiss_1_15\n"
            << "#[left edge] [bin center] [right edge] [uncertainty] [yield] \n";
            //rho0outputfile <<"1 to 1.5 Yield vs Kmiss\n"<< "[left edge] " <<","<< "[bin center] " <<","<< "[right edge] " <<","<< "[uncertainty] " <<","<< "[yield] \n";
            for (int i=1; i<= 6; i++){
            cout << h_rho_vs_kmiss_1_15->GetYaxis()->GetBinLowEdge(i)<< " " <<
             h_rho_vs_kmiss_1_15->GetYaxis()->GetBinCenter(i)<< " " <<
             h_rho_vs_kmiss_1_15->GetYaxis()->GetBinUpEdge(i)<< " "<<
             h_rho_vs_kmiss_1_15->GetBinError(i)<< " ";
             char temp[50];
        //projections
            sprintf(temp,"kmiss_bin%d",i);
            TH1D* thismass_spectrum = h_rho_vs_kmiss_1_15->ProjectionX(temp,i,i);
            double error;
            double yield = rhoyield_anderror(thismass_spectrum,error);
            cout << yield << endl;
            rho0outputfile<< h_rho_vs_kmiss_1_15->GetYaxis()->GetBinLowEdge(i)<<","<<h_rho_vs_kmiss_1_15->GetYaxis()->GetBinCenter(i)<<","<<h_rho_vs_kmiss_1_15->GetYaxis()->GetBinUpEdge(i)<<","<< yield <<"," << error <<endl;
            }
     //kmiss-> 1 to 1.5
     cout << "#1 to 1.5 Yield vs Kmiss\n"
          << "#[left edge] [bin center] [right edge] [uncertainty] [yield] \n";
          rho0outputfile <<"1 to 1.5 Yield vs Kmiss\n"<< "[left edge] " <<","<< "[bin center] " <<","<< "[right edge] " <<","<< "[uncertainty] " <<","<< "[yield] \n";
      for (int i=1; i<= 6; i++){
         cout << h_rho_vs_kmiss_1_15->GetYaxis()->GetBinLowEdge(i)<< " " <<
           h_rho_vs_kmiss_1_15->GetYaxis()->GetBinCenter(i)<< " " <<
           h_rho_vs_kmiss_1_15->GetYaxis()->GetBinUpEdge(i)<< " "<<
           h_rho_vs_kmiss_1_15->GetBinError(i)<< " ";
          char temp[50];
     //projections
         sprintf(temp,"kmiss_bin%d",i);
         TH1D* thismass_spectrum = h_rho_vs_kmiss_1_15->ProjectionX(temp,i,i);
           double error;
           double yield = rhoyield_anderror(thismass_spectrum,error);
          cout << yield << endl;
          rho0outputfile<< h_rho_vs_kmiss_1_15->GetYaxis()->GetBinLowEdge(i)<<","<<h_rho_vs_kmiss_1_15->GetYaxis()->GetBinCenter(i)<<","<<h_rho_vs_kmiss_1_15->GetYaxis()->GetBinUpEdge(i)<< ","<< yield <<"," << error <<endl;
      }*/
 /*   //kmiss-> 1.5 to 2
          cout << "#1.5 to 2 Yield vs Kmiss\n"
               << "#[left edge] [bin center] [right edge] [uncertainty] [yield] \n";
               //rho0outputfile <<"1.5 to 2 Yield vs Kmiss\n"<<  "[left edge] " <<","<< "[bin center] " <<","<< "[right edge] " <<","<< "[uncertainty] " <<","<< "[yield] \n";
           for (int i=1; i<= 6; i++){
              cout << h_rho_vs_kmiss_15_2->GetYaxis()->GetBinLowEdge(i)<< " " <<
                h_rho_vs_kmiss_15_2->GetYaxis()->GetBinCenter(i)<< " " <<
                h_rho_vs_kmiss_15_2->GetYaxis()->GetBinUpEdge(i)<< " " <<
                h_rho_vs_kmiss_15_2->GetYaxis()->GetBinUpEdge(i)<< " "<<
                h_rho_vs_kmiss_15_2->GetBinError(i)<< " ";
               char temp[50];
          //projections
              sprintf(temp,"kmiss_bin%d",i);
              TH1D* thismass_spectrum = h_rho_vs_kmiss_15_2->ProjectionX(temp,i,i);
                double yield = rhoyield(thismass_spectrum);
               cout << yield << endl;
               rho0outputfile<< h_rho_vs_kmiss_15_2->GetYaxis()->GetBinLowEdge(i)<<","<<h_rho_vs_kmiss_15_2->GetYaxis()->GetBinCenter(i)<<"," << h_rho_vs_kmiss_15_2->GetYaxis()->GetBinUpEdge(i)<< ","<<h_rho_vs_kmiss_15_2->GetBinError(i)<<","<< yield <<endl;
           }
    //kmiss-> 2 to 2.5
         cout << "#2 to 2.5 Yield vs Kmiss\n"
            << "#[left edge] [bin center] [right edge] [uncertainty] [yield] \n";
            //rho0outputfile <<"2 to 2.5 Yield vs Kmiss\n"<<  "[left edge] " <<","<< "[bin center] " <<","<< "[right edge] " <<","<< "[uncertainty] " <<","<< "[yield] \n";
        for (int i=1; i<= 6; i++){
                cout << h_rho_vs_kmiss_2_25->GetYaxis()->GetBinLowEdge(i)<< " " <<
                h_rho_vs_kmiss_2_25->GetYaxis()->GetBinCenter(i)<< " " <<
                h_rho_vs_kmiss_2_25->GetYaxis()->GetBinUpEdge(i)<< " " <<
                h_rho_vs_kmiss_2_25->GetBinError(i)<< " ";
         char temp[50];
         //projections
             sprintf(temp,"kmiss_bin%d",i);
             TH1D* thismass_spectrum = h_rho_vs_kmiss_2_25->ProjectionX(temp,i,i);
             double yield = rhoyield(thismass_spectrum);
            cout << yield << endl;
             rho0outputfile<< h_rho_vs_kmiss_2_25->GetYaxis()->GetBinLowEdge(i)<<","<<h_rho_vs_kmiss_2_25->GetYaxis()->GetBinCenter(i)<<","<<h_rho_vs_kmiss_2_25->GetYaxis()->GetBinUpEdge(i)<< "," << h_rho_vs_kmiss_2_25->GetBinError(i)<<","<< yield <<endl;
        }

    //kmiss-> 2.5 to 3
          cout << "#2.5 to 3 Yield vs Kmiss\n"
          << "#[left edge] [bin center] [right edge] [uncertainty] [yield] \n";
          //rho0outputfile <<"2.5 to 3 Yield vs Kmiss\n" << "[left edge] " <<","<< "[bin center] " <<","<< "[right edge] " <<","<< "[uncertainty] " <<","<< "[yield] \n";
             for (int i=1; i<= 6; i++){
               cout << h_rho_vs_kmiss_25_3->GetYaxis()->GetBinLowEdge(i)<< " " <<
                h_rho_vs_kmiss_25_3->GetYaxis()->GetBinCenter(i)<< " " <<
                 h_rho_vs_kmiss_25_3->GetYaxis()->GetBinUpEdge(i)<< " "<<
                  h_rho_vs_kmiss_25_3->GetBinError(i)<< " ";
           char temp[50];
           //projections
           sprintf(temp,"kmiss_bin%d",i);
             TH1D* thismass_spectrum = h_rho_vs_kmiss_25_3->ProjectionX(temp,i,i);
             double yield = rhoyield(thismass_spectrum);
              cout << yield << endl;

               rho0outputfile<< h_rho_vs_kmiss_25_3->GetYaxis()->GetBinLowEdge(i)<<","<<h_rho_vs_kmiss_25_3->GetYaxis()->GetBinCenter(i)<<","<<h_rho_vs_kmiss_25_3->GetYaxis()->GetBinUpEdge(i)<<","<< h_rho_vs_kmiss_25_3->GetBinError(i)<<"," << yield <<endl;
             }

    //kmiss-> 3 to 4
      cout << "#3 to 4 Yield vs Kmiss\n"
      << "#[left edge] [bin center] [right edge] [uncertainty] [yield] \n";
      //rho0outputfile << "#3 to 4 Yield vs Kmiss\n"<< "[left edge] " <<","<< "[bin center] " <<","<< "[right edge] " <<","<< "[uncertainty] " <<","<< "[yield] \n";
       for (int i=1; i<= 6; i++){
       cout << h_rho_vs_kmiss_3_4->GetYaxis()->GetBinLowEdge(i)<< " " <<
       h_rho_vs_kmiss_3_4->GetYaxis()->GetBinCenter(i)<< " " <<
       h_rho_vs_kmiss_3_4->GetYaxis()->GetBinUpEdge(i)<< " "<<
       h_rho_vs_kmiss_3_4->GetBinError(i) << " ";
       char temp[50];
      //projections
        sprintf(temp,"kmiss_bin%d",i);
        TH1D* thismass_spectrum = h_rho_vs_kmiss_3_4->ProjectionX(temp,i,i);
        double yield = rhoyield(thismass_spectrum);
        cout << yield << endl;
        rho0outputfile<< h_rho_vs_kmiss_3_4->GetYaxis()->GetBinLowEdge(i)<<","<<h_rho_vs_kmiss_3_4->GetYaxis()->GetBinCenter(i)<<","<<h_rho_vs_kmiss_3_4->GetYaxis()->GetBinUpEdge(i)<<","<< h_rho_vs_kmiss_3_4->GetBinError(i) << "," << yield <<endl;
       }
*/
    //pair angle
       cout << "#Yield vs Pair Angle\n"
           << "#[left edge] [bin center] [right edge] [uncertainty] [yield] \n";
        rho0outputfile <<"#Total Yield vs Pair Angle\n"<< "#[left edge] ,#[bin center] ,#[right edge]  ,#[yield],#[uncertainty]  \n";
       for (int i=1; i<= h_pairangle->GetNbinsX(); i++){
           cout << h_pairangle->GetBinLowEdge(i)<< " " <<
            h_pairangle->GetBinCenter(i)<< " " <<
            h_pairangle->GetXaxis()->GetBinUpEdge(i)<< " " <<
            h_pairangle->GetBinContent(i)<< " " <<
            h_pairangle->GetBinError(i)<< " \n";

           rho0outputfile<< h_pairangle->GetBinLowEdge(i)<< "," <<
            h_pairangle->GetBinCenter(i)<< "," <<
            h_pairangle->GetXaxis()->GetBinUpEdge(i)<< "," <<
            h_pairangle->GetBinContent(i)<< "," <<
            h_pairangle->GetBinError(i)<< "\n";
    }
    // precoil
       cout << "#Yield vs P_recoil kmiss > 0.4 and |t|>1.5\n"
           << "#[left edge] [bin center] [right edge]  [uncertainty]  [yield] \n";
           rho0outputfile <<"#Total Yield vs P_recoil, kmiss > 0.4 and |t|>1.5\n"<< "#[left edge] ,#[bin center] ,#[right edge] ,#[yield],#[uncertainty]  \n";
       for (int i=1; i<= 7; i++){
           cout << h_rho_vs_precoil->GetYaxis()->GetBinLowEdge(i)<< " " <<
            h_rho_vs_precoil->GetYaxis()->GetBinCenter(i)<< " " <<
            h_rho_vs_precoil->GetYaxis()->GetBinUpEdge(i)<< " " <<
            h_rho_vs_precoil->GetBinError(i)<< " ";
            char temp[50];
       //projections
           sprintf(temp,"prec_bin%d",i);
           TH1D* thismass_spectrum = h_rho_vs_precoil->ProjectionX(temp,i,i);
           double error;
           double yield = rhoyield_anderror(thismass_spectrum,error);
           cout << yield << endl;
           rho0outputfile<< h_rho_vs_precoil->GetYaxis()->GetBinLowEdge(i)<<","<<h_rho_vs_precoil->GetYaxis()->GetBinCenter(i)<<","<<h_rho_vs_precoil->GetYaxis()->GetBinUpEdge(i)<<","<< yield <<"," << error <<endl;
    }
       // pCMperp
       cout << "#Yield vs pCMperp kmiss > 0.4 and |t|>1.5\n"
           << "#[left edge] [bin center] [right edge]  [uncertainty]  [yield] \n";
           rho0outputfile <<"#Total Yield vs pCMperp, kmiss > 0.4 and |t|>1.5\n"<< "#[left edge] ,#[bin center] ,#[right edge] ,#[yield], #[uncertainty] \n";
       for (int i=1; i<= h_pCMperp->GetNbinsX(); i++){
           cout << h_rho_vs_pCMperp->GetYaxis()->GetBinLowEdge(i)<< " " <<
            h_rho_vs_pCMperp->GetYaxis()->GetBinCenter(i)<< " " <<
            h_rho_vs_pCMperp->GetYaxis()->GetBinUpEdge(i)<< " " <<
            h_rho_vs_pCMperp->GetBinError(i)<< " ";
            char temp[50];
       //projections
           sprintf(temp,"ppCMperpn%d",i);
           TH1D* thismass_spectrum = h_rho_vs_pCMperp->ProjectionX(temp,i,i);
           double error;
           double yield = rhoyield_anderror(thismass_spectrum,error);
           cout << yield << endl;
           rho0outputfile<< h_rho_vs_pCMperp->GetYaxis()->GetBinLowEdge(i)<<","<<h_rho_vs_pCMperp->GetYaxis()->GetBinCenter(i)<<","<<h_rho_vs_pCMperp->GetYaxis()->GetBinUpEdge(i)<<","<< yield <<"," << error <<endl;
       }
		rho0outputfile.close();

/***************************************** FIT COM MOTION THING **********************************************/
    h_pCMperp_1_15->Fit("gaus");
    TF1 *fitresult=h_pCMperp_1_15->GetFunction("gaus");
    double sigmaCMperp_1_15 = fitresult->GetParameter(2); //0 indexing
    cout << sigmaCMperp_1_15 <<endl;

/********************************************** WRITE OUT HISTOGRAMS **********************************************/

fout->cd();
//cerr << "writing histograms " << "\n";

h_precoil->Write();
h_rho_vs_precoil->Write();
h_pairangle->Write();
h_rho_vs_pairangle->Write();

fout->cd("UnCut");
h_rho0counts_uncut->Write();
h_zprotleadvertex->Write();
h_pip_p_theta_uncut->Write();
h_pim_p_theta_uncut->Write();
h_protL_p_theta_uncut->Write();
h_protR_p_theta_uncut->Write();
h_pippim_VS_pipprotL->Write();
h_pippim_VS_pimprotL->Write();
h_pipprot_VS_pimprotL->Write();

fout->cd("ZVert-Cut");
h_zprotleadvertex_zcut->Write();
h_rho0counts_zcut->Write();

fout->cd("MisID-Cut");
h_pip_p_theta_misid->Write();
h_pim_p_theta_misid->Write();
h_protL_p_theta_misid->Write();
h_rho0counts_misid->Write();

fout->cd("Dalitz_1.3-Cut");
h_rho0counts_lowerpcut->Write();
h_pippim_VS_pipprotL_lowerpcut->Write();
h_pippim_VS_pimprotL_lowerpcut->Write();

fout->cd("pCMperp_vs_t-distributions");
h_pCMperp->Write();
h_rho_vs_pCMperp->Write();
h_pCMperp_1_15->Write();
h_rho_vs_pCMperp_1_15->Write();
h_pCMperp_15_2->Write();
h_rho_vs_pCMperp_15_2->Write();
h_pCMperp_2_25->Write();
h_rho_vs_pCMperp_2_25->Write();
h_pCMperp_25_3->Write();
h_rho_vs_pCMperp_25_3->Write();
h_pCMperp_3_4->Write();
h_rho_vs_pCMperp_3_4->Write();

fout->cd("KMiss_vs_t-distributions");
h_kmiss->Write();
h_rho_vs_kmiss->Write();
/*h_kmiss_1_15->Write();
h_rho_vs_kmiss_1_15->Write();
h_kmiss_15_2->Write();
h_rho_vs_kmiss_15_2->Write();
h_kmiss_2_25->Write();
h_rho_vs_kmiss_2_25->Write();
h_kmiss_25_3->Write();
h_rho_vs_kmiss_25_3->Write();
h_kmiss_3_4->Write();*/
h_rho_vs_kmiss_3_4->Write();
h_rho0counts_t_1_15->Write();
h_rho0counts_t_15_2->Write();
h_rho0counts_t_2_25->Write();
h_rho0counts_t_25_3->Write();
h_rho0counts_t_3_4->Write();
fout->Close();


cerr << "Did all of the physics! " << "\n";


}
