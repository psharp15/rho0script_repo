//#include TCanvas.hy
using namespace std;

double mN = 0.983;
TLorentzVector p4_u(0,0,0,0.9315);
TLorentzVector p4_d2 = 2.0136 * p4_u;
TLorentzVector p4_he4 = 4.003 * p4_u;
TLorentzVector p4_c12 = 12. * p4_u;

void analysis_rho0_1p(const char *inputfilename, const char *outfilename)
{
  cerr << "Hello world\n";


  TFile *inputFile = new TFile(inputfilename);
  //TTree *inputTree = (TTree*) inputFile-> Get("gd_pippimprotmissn__F4_B4_T2_S4");
  //TTree *inputTree = (TTree*) inputFile-> Get("gd_pippimprotinc__F4_B4_T2_S4");
  //TTree *inputTree = (TTree*) inputFile-> Get("ghe_pippimprotinc__F4_B4_T2_S4");
  TTree *inputTree = (TTree*) inputFile-> Get("gc12_pippimprotinc__F4_B4");

  TFile *fout=new TFile(outfilename,"RECREATE");

  float kin_chisq;
  UInt_t kin_ndf;
  ULong64_t event;
  double CL;
  TLorentzVector *p4_prot_meas=0;
  TLorentzVector *p4_pip_meas=0;
  TLorentzVector *p4_pim_meas=0;
  TLorentzVector *x4_prot_meas=0;
  TLorentzVector *x4_pip_meas=0;
  TLorentzVector *x4_pim_meas=0;
  TLorentzVector *p4_beam_meas=0;
  TLorentzVector *x4_beam_meas=0;
  TLorentzVector *p4_prot_kin=0;
  TLorentzVector *p4_pip_kin=0;
  TLorentzVector *p4_pim_kin=0;
  TLorentzVector *x4_prot_kin=0;
  TLorentzVector *x4_pip_kin=0;
  TLorentzVector *x4_pim_kin=0;
  TLorentzVector *p4_beam_kin=0;
  TLorentzVector *x4_beam_kin=0;
  double weight;
  double t;
  TLorentzVector *p4_beam_thrown=0;
  TLorentzVector *p4_pip_thrown=0;
  TLorentzVector *p4_pim_thrown=0;
  TLorentzVector *p4_prot_thrown=0;
  double thrownS;
  double thrownT;
  double thrownU;

if (!inputTree)
{cout<< "Couldn't get the inputTree. Check spelling"<<endl;}

  inputTree->SetBranchAddress("kin_chisq",&kin_chisq);
  inputTree->SetBranchAddress("kin_ndf",&kin_ndf);
  inputTree->SetBranchAddress("pip_p4_meas",&p4_pip_meas);
  inputTree->SetBranchAddress("pim_p4_meas",&p4_pim_meas);
  inputTree->SetBranchAddress("p_p4_meas",&p4_prot_meas);
  inputTree->SetBranchAddress("pip_x4_meas",&x4_pip_meas);
  inputTree->SetBranchAddress("pim_x4_meas",&x4_pim_meas);
  inputTree->SetBranchAddress("p_x4_meas",&x4_prot_meas);
  inputTree->SetBranchAddress("pim_x4_meas",&x4_pim_meas);
  inputTree->SetBranchAddress("beam_p4_meas",&p4_beam_meas);
  inputTree->SetBranchAddress("beam_x4_meas",&x4_beam_meas);
  inputTree->SetBranchAddress("pip_p4_kin",&p4_pip_kin);
  inputTree->SetBranchAddress("pim_p4_kin",&p4_pim_kin);
  inputTree->SetBranchAddress("p_p4_kin",&p4_prot_kin);
  inputTree->SetBranchAddress("pip_x4_kin",&x4_pip_kin);
  inputTree->SetBranchAddress("pim_x4_kin",&x4_pim_kin);
  inputTree->SetBranchAddress("p_x4_kin",&x4_prot_kin);
  inputTree->SetBranchAddress("pim_x4_kin",&x4_pim_kin);
  inputTree->SetBranchAddress("beam_p4_kin",&p4_beam_kin);
  inputTree->SetBranchAddress("beam_x4_kin",&x4_beam_kin);
  inputTree->SetBranchAddress("accidweight",&weight);
  inputTree->SetBranchAddress("event",&event);
  inputTree->SetBranchAddress("thrownS",&thrownS);
  inputTree->SetBranchAddress("thrownT",&thrownT);
  inputTree->SetBranchAddress("thrownU",&thrownU);
  inputTree->SetBranchAddress("thrownBeam",&p4_beam_thrown);
  inputTree->SetBranchAddress("thrownPiPlus",&p4_pip_thrown);
  inputTree->SetBranchAddress("thrownPiMinus",&p4_pim_thrown);
  inputTree->SetBranchAddress("thrownProton",&p4_prot_thrown);

  vector<TH1 *> hist_list;
  TDirectory * dir_UnCut = fout->mkdir("UnCut");
  TDirectory * dir_TCut = fout->mkdir("TCut");
  TDirectory * dir_MisId_TCut = fout->mkdir("MisId_TCut");

///****** Defining Histograms ******//

  /****** Confidence Level ******/
  TH1D *h_CL_uncut = new TH1D ("ConfidenceLevel_UNCUT","Confidence Level UNCUT;Confidence Level;Counts",200,0,1);
    hist_list.push_back(h_CL_uncut);
  TH1D *h_CL_cut = new TH1D ("ConfidenceLevel_CUT","Confidence Level CUT;Confidence Level;Counts",200,0,1);
    hist_list.push_back(h_CL_cut);

  /****** Vert ******/
  TH1D *h_zprotvertex = new TH1D ("prot Zvertex","prot Zvertex;Vertex z [cm];Counts",1000,0,100);
    hist_list.push_back(h_zprotvertex);
  TH2D *h_XYvertex = new TH2D("XYvertex","XYvertex;Vertex x [cm];Vertex y [cm]",50,-5,5,50,-5,5);
    hist_list.push_back(h_XYvertex);
  TH1D *h_coplanarity = new TH1D("Coplanarity","Coplanarity; rho Angle [Degrees]; prot Angle [Degrees];Counts",300,90, 270);
    hist_list.push_back(h_coplanarity);

  /****** PiPlus ******/
  TH2D *h_pip_p_theta_uncut = new TH2D ("pip_p_theta_uncut","Pip_PVSTheta_uncut; theta [degree];p [GeV]; Counts",200,0,140,200,0,10);
    hist_list.push_back(h_pip_p_theta_uncut);
  TH2D *h_pip_p_theta_tcut_misid = new TH2D ("pip_p_theta_tcut_misid","Pip_PVSThetatcut_misid ; theta [degree];p [GeV]; Counts",200,0,140,200,0,10);
    hist_list.push_back(h_pip_p_theta_tcut_misid);
  TH1D *h_pip_from_Beam_uncut = new TH1D("pip_from_Beam_uncut","pip_from_Beam; Angle [Degrees];Counts",300,0,180);
    hist_list.push_back(h_pip_from_Beam_uncut);
  TH1D *h_pip_from_Beam_tcut_misid = new TH1D("pip_from_Beam_tcut_misid","pip_from_Beam; Angle [Degrees];Counts",300,0,180);
    hist_list.push_back(h_pip_from_Beam_tcut_misid);
  TH2D *h_pip_p_theta_THROWN_uncut = new TH2D ("pip_p_theta_THROWN_uncut","Prot_PVSTheta ; theta [degree];p [GeV]; Counts",200,0,140,200,0,10);
    hist_list.push_back(h_pip_p_theta_THROWN_uncut);
  TH2D *h_pip_p_theta_THROWN_tcut_misid = new TH2D ("pip_p_theta_THROWN_tcut_misid","Prot_PVSTheta_tcut_misid; theta [degree];p [GeV]; Counts",200,0,140,200,0,10);
    hist_list.push_back(h_pip_p_theta_THROWN_tcut_misid);

  /****** PiMinus ******/

  /****** Protons ******/
  TH2D *h_prot_p_theta_uncut = new TH2D ("prot_p_theta_uncut","Prot_PVSTheta ; theta [degree];p [GeV]; Counts",200,0,140,200,0,10);
    hist_list.push_back(h_prot_p_theta_uncut);
  TH2D *h_prot_p_theta_tcut_misid = new TH2D ("prot_p_theta_tcut_misid","Prot_PVSTheta_tcut_misid ; theta [degree];p [GeV]; Counts",200,0,140,200,0,10);
    hist_list.push_back(h_prot_p_theta_tcut_misid);
  TH1D *h_prot_from_Beam_uncut = new TH1D("prot_from_Beam_uncut","prot_from_Beam; Angle [Degrees];Counts",300,0,180);
    hist_list.push_back(h_prot_from_Beam_uncut);
  TH2D *h_prot_p_theta_THROWN_uncut = new TH2D ("prot_p_theta_THROWN_uncut","Prot_PVSTheta ; theta [degree];p [GeV]; Counts",200,0,140,200,0,10);
    hist_list.push_back(h_prot_p_theta_THROWN_uncut);
  TH2D *h_prot_p_theta_THROWN_tcut_misid = new TH2D ("prot_p_theta_THROWN_tcut_misid","Prot_PVSTheta_tcut_misid; theta [degree];p [GeV]; Counts",200,0,140,200,0,10);
    hist_list.push_back(h_prot_p_theta_THROWN_tcut_misid);

  /****** PiPlus vs Protons ******/
  TH2D *h_pip_prot_from_Beam_uncut = new TH2D("pip_prot_from_Beam_uncut","pip and prot _from_Beam; Pip Angle [Degrees]; Prot Angle [Degrees];Counts",300,0,180,300,0,180);
    hist_list.push_back(h_pip_prot_from_Beam_uncut);

  /****** PMiss ******/
  TH1D *h_pmissVSbeam = new TH1D("pmissVSbeam","pmissVSbeam;pmiss;beam", 200, -1, 1);
    hist_list.push_back(h_pmissVSbeam);
  TH1D *h_pmissVSbeam_tcut_misid = new TH1D("pmissVSbeam_tcut_misid","h_pmissVSbeam_tcut_misid;pmiss Angle to beam ;counts", 200, -1, 1);
    hist_list.push_back(h_pmissVSbeam_tcut_misid);
  TH1D *h_pmissZ_uncut = new TH1D ("pmissZ_uncut","hmissZ;z_pmiss;counts", 200, -10,10);
    hist_list.push_back(h_pmissZ_uncut);
  TH1D *h_pmissZ_tcut_misid = new TH1D ("pmissZ_tcut_misid","pmissZ_tcut_misid;z_pmiss;counts", 200, -10,10);
    hist_list.push_back(h_pmissZ_tcut_misid);
  TH2D *h_pmissZ_s_uncut = new TH2D ("pmiss_s_uncut","pmiss_s_uncut;z_pmiss;s;counts", 200, -10,10,20,0,20);
    hist_list.push_back(h_pmissZ_s_uncut);
  TH2D *h_pmissAngle_s_uncut = new TH2D ("pmissAngle_s","pmissAngle_s;pmissAngle;s;counts", 200, -10,10,20,0,20);
    hist_list.push_back(h_pmissAngle_s_uncut);
  TH2D *h_pmissZ_perp_uncut = new TH2D ("pmissZ_perp_uncut","pmissZ_vs_perp;pmiss.Z;pmiss_perp;counts", 200, -2,2, 200, 0,2);
    hist_list.push_back(h_pmissZ_perp_uncut);
  TH2D *h_pmissZ_perp_tcut_misid = new TH2D ("pmissZ_perp_tcut_misid","pmissZ_vs_t_tcut_misid;pmiss;pmiss_perp;counts", 200, -2,2, 200, 0,2);
    hist_list.push_back(h_pmissZ_perp_tcut_misid);
  TH2D *h_pmiss_Mag_Angle_uncut = new TH2D ("pmiss_Mag_Angle_uncut","pmiss_Mag_Angl_uncut;pmiss angle;pmiss mag", 200, -1,1, 200, 0,3);
    hist_list.push_back(h_pmiss_Mag_Angle_uncut);
  TH2D *h_pmiss_Mag_Angle_tcut_misid = new TH2D ("pmiss_Mag_Angle_tcut_misid","pmiss_Mag_Angle_tcut_misid;pmiss angle;pmiss mag", 200, -1,1, 200, 0,3);
    hist_list.push_back(h_pmiss_Mag_Angle_tcut_misid);
  
  TH1D *h_pmiss_uncut = new TH1D("pmiss_uncut", "Missing Momentum [GeV];Counts",200,0.,2.);
    hist_list.push_back(h_pmiss_uncut);
  TH1D *h_pmiss_tcut = new TH1D("pmiss_tcut", "Missing Momentum [GeV];pmiss[GeV];Counts",200,0.,2.);
    hist_list.push_back(h_pmiss_tcut);
  TH1D *h_pmiss_tcut_misid = new TH1D("pmiss_tcut_misid", "Missing Momentum [GeV];pmiss[GeV];Counts",200,0.,2.);
    hist_list.push_back(h_pmiss_tcut_misid);
  TH1D *h_pmiss_THROWN_uncut = new TH1D("pmiss_THROWN_uncut", "Missing Momentum [GeV];pmiss[GeV];Counts",200,0.,2.);
    hist_list.push_back(h_pmiss_THROWN_uncut);
  TH1D *h_pmiss_THROWN_tcut_misid = new TH1D("pmiss_THROWN_tcut_misid", "Missing Momentum [GeV];pmiss[GeV];Counts",200,0.,2.);
    hist_list.push_back(h_pmiss_THROWN_tcut_misid);
  TH1D *h_p3_pmiss_d2_tcut_misid = new TH1D("DEUTERIUM pmiss_tcut_misid", "Missing Momentum [GeV];pmiss[GeV];Counts",200,0.,2.);
    hist_list.push_back(h_p3_pmiss_d2_tcut_misid);
  TH1D *h_p3_pmiss_d2_THROWN_tcut_misid = new TH1D("DEUTERIUM pmiss_THROWN_tcut_misid", "Missing Momentum [GeV];pmiss[GeV];Counts",200,0.,2.);
    hist_list.push_back(h_p3_pmiss_d2_THROWN_tcut_misid);
  TH1D *h_p3_pmiss_he4_tcut_misid = new TH1D("HELIUM pmiss_tcut_misid", "Missing Momentum [GeV];pmiss[GeV];Counts",200,0.,2.);
    hist_list.push_back(h_p3_pmiss_he4_tcut_misid);
  TH1D *h_p3_pmiss_he4_THROWN_tcut_misid = new TH1D("HELIUM pmiss_THROWN_tcut_misid", "Missing Momentum [GeV];pmiss[GeV];Counts",200,0.,2.);
    hist_list.push_back(h_p3_pmiss_he4_THROWN_tcut_misid);
  TH1D *h_p3_pmiss_c12_tcut_misid = new TH1D("CARBON pmiss_tcut_misid", "Missing Momentum [GeV];pmiss[GeV];Counts",200,0.,2.);
    hist_list.push_back(h_p3_pmiss_c12_tcut_misid);
  TH1D *h_p3_pmiss_c12_THROWN_tcut_misid = new TH1D("CARBON pmiss_THROWN_tcut_misid", "Missing Momentum [GeV];pmiss[GeV];Counts",200,0.,2.);
    hist_list.push_back(h_p3_pmiss_c12_THROWN_tcut_misid);
    

  /****** Rho0 Mass ******/
  TH1D *h_rho0counts_uncut = new TH1D("Rho0_Counts_uncut","Rho0Counts_before;Mass [GeV];Counts",300,0,3);
    hist_list.push_back(h_rho0counts_uncut);
  TH1D *h_rho0counts_tcut = new TH1D("Rho0 Counts_tcut","Rho0Counts_tcut;Mass [GeV];Counts",100,0,2);
    hist_list.push_back(h_rho0counts_tcut);
  TH1D *h_rho0counts_tcut_misid = new TH1D("Rho0 Counts_tcut_misid","Rho0Counts_tcut_misid;Mass [GeV];Counts",100,0,2);
    hist_list.push_back(h_rho0counts_tcut_misid);
  TH1D *h_rho0counts_THROWN_uncut = new TH1D("Rho0_Counts_THROWN_uncut","Rho0Counts_before;Mass [GeV];Counts",300,0,3);
    hist_list.push_back(h_rho0counts_THROWN_uncut);
  TH1D *h_rho0counts_THROWN_tcut = new TH1D("Rho0Counts_THROWN_tcut","Rho0Counts_tcut;Mass [GeV];Counts",100,0,5);
    hist_list.push_back(h_rho0counts_THROWN_tcut);
  TH1D *h_rho0counts_THROWN_tcut_misid = new TH1D("Rho0_Counts_THROWN_tcut_misid","Rho0Counts_tcut_misid;Mass [GeV];Counts",100,0,5);
    hist_list.push_back(h_rho0counts_THROWN_tcut_misid);

  /****** PMiss vs Rho0 Mass ******/
  TH2D *h_pmiss_vs_rho0counts_uncut = new TH2D("rho0counts_vs_Pmiss_uncut","rho0 vs pmiss before;rho0_before[GeV];PMiss;Counts_after",100,0,5,200,0.,2.);
    hist_list.push_back(h_pmiss_vs_rho0counts_uncut);
  TH2D *h_pmiss_vs_rho0counts_tcut = new TH2D("rho0counts_during vs Pmiss_during","rho0 vs pmiss after;rho0_during[GeV];PMiss_during;Counts",100,0,5,200,0.,2.);
    hist_list.push_back(h_pmiss_vs_rho0counts_tcut);
  TH2D *h_pmiss_vs_rho0counts_tcut_misid = new TH2D("rho0counts_tcut_misid vs Pmiss_tcut_misid","rho0 vs pmiss after;rho0_after [GeV];PMiss_after;Counts",100,0,5,200,0.,2.);
    hist_list.push_back(h_pmiss_vs_rho0counts_tcut_misid);

  /****** T ******/
  TH1D *h_t_uncut = new TH1D("t_uncut","t;-t [GeV^2]",20,0,20);
    hist_list.push_back(h_t_uncut);
  TH1D *h_t_tcut = new TH1D("t_tcut","t;-t [GeV^2]",20,0,20);
    hist_list.push_back(h_t_tcut);
  TH1D *h_t_tcut_misid = new TH1D("t_tcut_misid","t;-t [GeV^2]",20,0,20);
    hist_list.push_back(h_t_tcut_misid);

  /****** PMinus ******/
  TH1D *h_pminus_pmiss_uncut = new TH1D("pminus_Pmiss","pminus_pmiss;pminus",50,0,2);
    hist_list.push_back(h_pminus_pmiss_uncut);
  TH1D *h_pminus_pmiss_tcut_misid = new TH1D("pminus_Pmiss_tcut_misid","pminus_pmiss;pminus",50,0,2);
    hist_list.push_back(h_pminus_pmiss_tcut_misid);

/********************************************** Event Loop **********************************************/
for( int event=0; event < inputTree-> GetEntries(); event++){

  if (event%10000==0)
  cerr << "Working on event " << event << "\n";

  inputTree-> GetEvent(event);

  h_CL_uncut->Fill(TMath::Prob(kin_chisq,kin_ndf),weight);

  if (TMath::Prob(kin_chisq,kin_ndf)<0.02)
    continue;

  TLorentzVector p4_rho0_meas = (*p4_pip_meas)+(*p4_pim_meas);
  TLorentzVector p4_rho0_kin = (*p4_pip_kin)+(*p4_pim_kin);
  TLorentzVector p4_pmiss = (*p4_prot_kin+(*p4_pip_kin + *p4_pim_kin) - *p4_beam_kin);
  TVector3 p3_pmiss = (p4_prot_kin->Vect() + (p4_pip_kin->Vect() + p4_pim_kin->Vect()) - p4_beam_kin->Vect() ); //pmiss = lead + rho - beam
  TVector3 p3_pmiss_thrown = (p4_prot_thrown->Vect() + (p4_pip_thrown->Vect() + p4_pim_thrown->Vect()) - p4_beam_thrown->Vect() ); //pmiss = lead + rho - beam
  TVector3 v3_prot = p4_prot_meas->Vect();
  TVector3 beam_mom = p4_beam_meas->Vect();
  TVector3 v3_pip = p4_pip_meas->Vect();
  TVector3 v3_rho = p4_rho0_meas.Vect();

  TLorentzVector p4_pmiss_d2_kin = (p4_d2 + *p4_beam_kin - *p4_prot_kin - (*p4_pip_kin + *p4_pim_kin));
  TLorentzVector p4_pmiss_d2_thrown = (p4_d2 + *p4_beam_thrown - *p4_prot_thrown - *p4_pip_thrown - *p4_pim_thrown);
  double p3_pmiss_d2_kin = p4_pmiss_d2_kin.P();
  double p3_pmiss_d2_thrown = p4_pmiss_d2_thrown.P();

  TLorentzVector p4_pmiss_he4_kin = (p4_he4 + *p4_beam_kin - *p4_prot_kin - (*p4_pip_kin + *p4_pim_kin));
  TLorentzVector p4_pmiss_he4_thrown = (p4_he4 + *p4_beam_thrown - *p4_prot_thrown - *p4_pip_thrown - *p4_pim_thrown);
  double p3_pmiss_he4_kin = p4_pmiss_he4_kin.P();
  double p3_pmiss_he4_thrown = p4_pmiss_he4_thrown.P();

  TLorentzVector p4_pmiss_c12_kin = (p4_c12 + *p4_beam_kin - *p4_prot_kin - (*p4_pip_kin + *p4_pim_kin));
  TLorentzVector p4_pmiss_c12_thrown = (p4_c12 + *p4_beam_thrown - *p4_prot_thrown - *p4_pip_thrown - *p4_pim_thrown);
  double p3_pmiss_c12_kin = p4_pmiss_c12_kin.P();
  double p3_pmiss_c12_thrown = p4_pmiss_c12_thrown.P();


  TLorentzVector p4_rho0_thrown =(*p4_pip_thrown)+(*p4_pim_thrown);
  TVector3 v3_prot_thrown = p4_prot_thrown->Vect();
  TVector3 v3_pip_thrown = p4_pip_thrown->Vect();

  double t_mandel = (*p4_beam_kin - p4_rho0_kin).M2();
  double s_mandel = (*p4_prot_kin + p4_rho0_kin).M2();
  //double p3_com = ()/();


/********************************************** Fill Uncut Histograms **********************************************/
  h_CL_cut->Fill(TMath::Prob(kin_chisq,kin_ndf),weight);
  h_zprotvertex->Fill(x4_prot_kin->Z(),weight);
  h_XYvertex->Fill(x4_prot_kin->X(),x4_prot_kin->Y(),weight);
  
  h_pmiss_uncut->Fill((p3_pmiss).Mag(),weight);
  h_pmiss_THROWN_uncut -> Fill(p3_pmiss_thrown.Mag(),weight);
  h_rho0counts_uncut->Fill(p4_rho0_kin.M());
  h_rho0counts_THROWN_uncut->Fill(p4_rho0_thrown.M());
  h_t_uncut->Fill(-t_mandel,weight);
  h_pmiss_vs_rho0counts_uncut->Fill((p4_rho0_kin).M(),p3_pmiss.Mag(),weight);
  h_prot_from_Beam_uncut->Fill(180./M_PI*v3_prot.Angle(beam_mom));
  h_pip_from_Beam_uncut->Fill(180./M_PI*v3_pip.Angle(beam_mom));
  h_pip_prot_from_Beam_uncut->Fill(180./M_PI*v3_pip.Angle(beam_mom),180./M_PI*v3_prot.Angle(beam_mom));  h_coplanarity -> Fill(fabs(v3_rho.Phi()-v3_prot.Phi())*180/TMath::Pi());
  h_pip_p_theta_uncut->Fill(180./M_PI*p4_pip_meas->Theta(),v3_pip.Mag());
  h_prot_p_theta_uncut->Fill(180./M_PI*p4_prot_meas->Theta(),v3_prot.Mag());

  h_prot_p_theta_THROWN_uncut->Fill(180./M_PI*v3_prot_thrown.Theta(),v3_prot_thrown.Mag());
  h_pip_p_theta_THROWN_uncut->Fill(180./M_PI*v3_pip_thrown.Theta(),v3_pip_thrown.Mag());

  h_pmissZ_uncut->Fill(p3_pmiss.Z(),weight);
  h_pmissZ_s_uncut->Fill(p3_pmiss.Z(),s_mandel,weight);
  h_pmissAngle_s_uncut->Fill(p4_pmiss.Vect().Mag(),s_mandel,weight);
  h_pmissZ_perp_uncut->Fill(p4_pmiss.Z(),p3_pmiss.Perp(),weight);
  h_pminus_pmiss_uncut->Fill(p4_pmiss.Minus(),weight);
  h_pmiss_Mag_Angle_uncut->Fill(p4_pmiss.CosTheta(),p4_pmiss.Vect().Mag(),weight);


/********************************************** T - Cut **********************************************/
if (-t_mandel < 1)
    continue;

/********************************************** Fill T - Cut Histograms **********************************************/

h_t_tcut -> Fill(-t_mandel,weight);
h_pmiss_tcut -> Fill(p3_pmiss.Mag(),weight);
h_rho0counts_tcut -> Fill(p4_rho0_kin.M());
h_rho0counts_THROWN_tcut->Fill(p4_rho0_thrown.M());
h_pmiss_vs_rho0counts_tcut -> Fill((p4_rho0_kin).M(),p3_pmiss.Mag(),weight);

/********************************************** Missed PID - Cut **********************************************/
if (v3_pip.Mag() > exp (-0.08* (180./M_PI*v3_pip.Theta()) +2.85) -0.1)
    continue;
  
/********************************************** Fill Missed PID AND T - Cut Histograms **********************************************/
h_prot_p_theta_tcut_misid->Fill(180./M_PI*p4_prot_meas->Theta(),v3_prot.Mag());
h_t_tcut_misid -> Fill(-t_mandel,weight);
h_pip_from_Beam_uncut->Fill(180./M_PI*v3_pip.Angle(beam_mom));
h_pmiss_tcut_misid -> Fill(p3_pmiss.Mag(),weight);
h_pmiss_THROWN_tcut_misid -> Fill(p3_pmiss_thrown.Mag(),weight);
h_p3_pmiss_d2_tcut_misid -> Fill(p3_pmiss_d2_kin,weight);
h_p3_pmiss_d2_THROWN_tcut_misid -> Fill(p3_pmiss_d2_thrown,weight);
h_p3_pmiss_he4_tcut_misid -> Fill(p3_pmiss_he4_kin,weight);
h_p3_pmiss_he4_THROWN_tcut_misid -> Fill(p3_pmiss_he4_thrown,weight);
h_p3_pmiss_c12_tcut_misid -> Fill(p3_pmiss_c12_kin,weight);
h_p3_pmiss_c12_THROWN_tcut_misid -> Fill(p3_pmiss_c12_thrown,weight);
h_rho0counts_tcut_misid -> Fill(p4_rho0_kin.M());
h_rho0counts_THROWN_tcut_misid->Fill(p4_rho0_thrown.M());
h_pmiss_vs_rho0counts_tcut_misid -> Fill((p4_rho0_kin).M(),p3_pmiss.Mag(),weight);
h_pmissVSbeam_tcut_misid -> Fill(p3_pmiss.CosTheta(),weight);
h_pip_p_theta_tcut_misid -> Fill(180./M_PI*v3_pip.Theta(),v3_pip.Mag());

h_pmissZ_tcut_misid ->Fill(p3_pmiss.Z(),weight);
h_pmissZ_perp_tcut_misid ->Fill(p4_pmiss.Z(),p3_pmiss.Perp(),weight);
h_pminus_pmiss_tcut_misid ->Fill(p4_pmiss.Minus(),weight);
h_pmiss_Mag_Angle_tcut_misid ->Fill(p4_pmiss.CosTheta(),p4_pmiss.Vect().Mag(),weight);

h_prot_p_theta_THROWN_tcut_misid->Fill(180./M_PI*v3_prot_thrown.Theta(),v3_prot_thrown.Mag());

//h_commom_tcut_misid->Fill();

}

inputFile->Close();

/********************************************** WRITE OUT HISTOGRAMS **********************************************/

fout->cd();

h_CL_uncut->Write();
h_CL_cut->Write();
h_zprotvertex->Write();
h_XYvertex->Write();

fout->cd("UnCut");
h_pmiss_uncut->Write();
h_pmiss_THROWN_uncut->Write();
h_rho0counts_uncut->Write();
h_rho0counts_THROWN_uncut->Write();
h_t_uncut->Write();
h_pmiss_vs_rho0counts_uncut->Write();
h_prot_from_Beam_uncut->Write();
h_pip_from_Beam_uncut->Write();
h_pip_prot_from_Beam_uncut->Write();
h_pip_p_theta_uncut->Write();
h_pip_p_theta_THROWN_uncut->Write();
h_prot_p_theta_uncut->Write();
h_prot_p_theta_THROWN_uncut->Write();

h_pmissZ_uncut->Write();
h_pmissZ_s_uncut->Write();
h_pmissAngle_s_uncut->Write();
h_pmissZ_perp_uncut->Write();
h_pminus_pmiss_uncut->Write();
h_pmiss_Mag_Angle_uncut->Write();
fout->cd();

fout->cd("TCut");
h_t_tcut->Write();
h_pmiss_tcut->Write();
h_rho0counts_tcut->Write();
h_rho0counts_THROWN_tcut->Write();
h_pmiss_vs_rho0counts_tcut->Write();
fout->cd();

fout->cd("MisId_TCut");
h_t_tcut_misid->Write();
h_pmiss_tcut_misid->Write();
h_pmiss_THROWN_tcut_misid->Write();
h_pmiss_vs_rho0counts_tcut_misid->Write();
h_p3_pmiss_d2_tcut_misid->Write();
h_p3_pmiss_d2_THROWN_tcut_misid->Write();
h_p3_pmiss_he4_tcut_misid->Write();
h_p3_pmiss_he4_THROWN_tcut_misid->Write();
h_p3_pmiss_c12_tcut_misid->Write();
h_p3_pmiss_c12_THROWN_tcut_misid->Write();
h_rho0counts_tcut_misid->Write();
h_rho0counts_THROWN_tcut_misid->Write();
h_pmissVSbeam_tcut_misid->Write();
h_pip_p_theta_tcut_misid->Write();
h_pip_p_theta_THROWN_tcut_misid->Write();
h_prot_p_theta_tcut_misid->Write();
h_prot_p_theta_THROWN_tcut_misid->Write();

h_pmissZ_tcut_misid->Write();
h_pmissZ_perp_tcut_misid->Write();
h_pminus_pmiss_tcut_misid->Write();
h_pmiss_Mag_Angle_tcut_misid->Write();
fout->cd();
}
