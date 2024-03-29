//#include TCanvas.hy
using namespace std;

double mN = 0.983;

void analysis_rho0_2p(const char *inputfilename, const char *inputTreename, const char *outfilename)
{
  cerr << "Hello world\n";


  TFile *inputFile = new TFile(inputfilename);
  TTree *inputTree = (TTree*) inputFile-> Get(inputTreename);


  TFile *fout=new TFile(outfilename,"RECREATE");
  TTree *outputTree = new TTree("analyzed_helium_2p_inc_data",  "analyzed_helium_2p_inc_data");

  float kin_chisq;
  UInt_t kin_ndf;
  ULong64_t event;
  double CL;
  TLorentzVector *p4_prot1_meas=0;
  TLorentzVector *p4_prot2_meas=0;
  TLorentzVector *p4_pip_meas=0;
  TLorentzVector *p4_pim_meas=0;
  TLorentzVector *x4_prot1_meas=0;
  TLorentzVector *x4_prot2_meas=0;
  TLorentzVector *x4_pip_meas=0;
  TLorentzVector *x4_pim_meas=0;
  TLorentzVector *p4_beam_meas=0;
  TLorentzVector *x4_beam_meas=0;
  TLorentzVector *p4_prot1_kin=0;
  TLorentzVector *p4_prot2_kin=0;
  TLorentzVector *p4_pip_kin=0;
  TLorentzVector *p4_pim_kin=0;
  TLorentzVector *x4_prot1_kin=0;
  TLorentzVector *x4_prot2_kin=0;
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
  TLorentzVector *p4_prot1_thrown=0;
  TLorentzVector *p4_prot2_thrown=0;
  double thrownS;
  double thrownT;
  double thrownU;

  TLorentzVector *p4_prot_lead_kin=0;
  TLorentzVector *p4_prot_recoil_kin=0;
  TLorentzVector *x4_prot_lead_kin=0;
  TLorentzVector *x4_prot_recoil_kin=0;
  TLorentzVector *p4_prot_lead_thrown=0;
  TLorentzVector *p4_prot_recoil_thrown=0;

if (!inputTree)
{cout<< "Couldn't get the inputTree. Check spelling"<<endl;}

  inputTree->SetBranchAddress("kin_chisq",&kin_chisq);
  inputTree->SetBranchAddress("kin_ndf",&kin_ndf);
  inputTree->SetBranchAddress("pip_p4_meas",&p4_pip_meas);
  inputTree->SetBranchAddress("pim_p4_meas",&p4_pim_meas);
  inputTree->SetBranchAddress("p1_p4_meas",&p4_prot1_meas);
  inputTree->SetBranchAddress("p2_p4_meas",&p4_prot2_meas);
  inputTree->SetBranchAddress("pip_x4_meas",&x4_pip_meas);
  inputTree->SetBranchAddress("pim_x4_meas",&x4_pim_meas);
  inputTree->SetBranchAddress("p1_x4_meas",&x4_prot1_meas);
  inputTree->SetBranchAddress("p2_x4_meas",&x4_prot2_meas);
  inputTree->SetBranchAddress("pim_x4_meas",&x4_pim_meas);
  inputTree->SetBranchAddress("beam_p4_meas",&p4_beam_meas);
  inputTree->SetBranchAddress("beam_x4_meas",&x4_beam_meas);
  inputTree->SetBranchAddress("pip_p4_kin",&p4_pip_kin);
  inputTree->SetBranchAddress("pim_p4_kin",&p4_pim_kin);
  inputTree->SetBranchAddress("p1_p4_kin",&p4_prot1_kin);
  inputTree->SetBranchAddress("p2_p4_kin",&p4_prot2_kin);
  inputTree->SetBranchAddress("pip_x4_kin",&x4_pip_kin);
  inputTree->SetBranchAddress("pim_x4_kin",&x4_pim_kin);
  inputTree->SetBranchAddress("p1_x4_kin",&x4_prot1_kin);
  inputTree->SetBranchAddress("p2_x4_kin",&x4_prot2_kin);
  inputTree->SetBranchAddress("pim_x4_kin",&x4_pim_kin);
  inputTree->SetBranchAddress("beam_p4_kin",&p4_beam_kin);
  inputTree->SetBranchAddress("beam_x4_kin",&x4_beam_kin);
  inputTree->SetBranchAddress("accidweight",&weight);
  inputTree->SetBranchAddress("RF_time",&RF_time);
  inputTree->SetBranchAddress("event",&event);
  inputTree->SetBranchAddress("thrownS",&thrownS);
  inputTree->SetBranchAddress("thrownT",&thrownT);
  inputTree->SetBranchAddress("thrownU",&thrownU);
  inputTree->SetBranchAddress("thrownBeam",&p4_beam_thrown);
  inputTree->SetBranchAddress("thrownPiPlus",&p4_pip_thrown);
  inputTree->SetBranchAddress("thrownPiMinus",&p4_pim_thrown);
  inputTree->SetBranchAddress("thrownProton1",&p4_prot1_thrown);
  inputTree->SetBranchAddress("thrownProton2",&p4_prot2_thrown);

/********************************************** Filling OutputTree **********************************************/

  outputTree->Branch("p4_prot_lead",&p4_prot_lead_kin);
  outputTree->Branch("p4_prot_recoil",&p4_prot_recoil_kin);
  outputTree->Branch("x4_prot_lead",&x4_prot_lead_kin);
  outputTree->Branch("x4_prot_recoil",&x4_prot_recoil_kin);
  outputTree->Branch("pip_p4_kin",&p4_pip_kin);
  outputTree->Branch("pim_p4_kin",&p4_pim_kin);
  outputTree->Branch("beam_p4_kin",&p4_beam_kin);
  outputTree->Branch("accidweight",&weight);
  outputTree->Branch("RF_time",&RF_time);
  outputTree->Branch("event",&event);

  outputTree->Branch("thrownBeam",&p4_beam_thrown);
  outputTree->Branch("thrownPiPlus",&p4_pip_thrown);
  outputTree->Branch("thrownPiMinus",&p4_pim_thrown);
  outputTree->Branch("thrownProton1",&p4_prot1_thrown);
  outputTree->Branch("thrownProton2",&p4_prot2_thrown);
  outputTree->Branch("p4_prot_lead_thrown",&p4_prot_lead_thrown);
  outputTree->Branch("p4_prot_recoil_thrown",&p4_prot_recoil_thrown);


/********************************************** Defining Histograms **********************************************/

  vector<TH1 *> hist_list;
  TDirectory * dir_UnCut = fout->mkdir("UnCut");
  TDirectory * dir_TCut = fout->mkdir("TCut");
  TDirectory * dir_EnergyBalance = fout->mkdir("Energy Balance");
  TDirectory * dir_protmisrecon = fout->mkdir("protmisrecon");

  /****** Confidence Level ******/
    TH1D *h_CL_uncut = new TH1D ("ConfidenceLevel_UNCUT","Confidence Level UNCUT;Confidence Level;Counts",200,0,1);
    hist_list.push_back(h_CL_uncut);
    TH1D *h_CL_cut = new TH1D ("ConfidenceLevel_CUT","Confidence Level CUT;Confidence Level;Counts",200,0,1);
    hist_list.push_back(h_CL_cut);

  /****** Vert ******/
  TH1D *h_zprot1vertex = new TH1D ("prot1 Zvertex","prot1 Zvertex;Vertex z [cm];Counts",50,0,100);
    hist_list.push_back(h_zprot1vertex);
  TH1D *h_zprot2vertex = new TH1D ("prot2 Zvertex","prot2 Zvertex;Vertex z [cm];Counts",50,0,100);
    hist_list.push_back(h_zprot2vertex);
  TH1D *h_zprot_lead_vertex = new TH1D ("prot lead Zvertex","protlead Zvertex;Vertex z [cm];Counts",50,0,100);
    hist_list.push_back(h_zprot2vertex);
  TH2D *h_XYvertex = new TH2D("XYvertex","XYvertex;Vertex x [cm];Vertex y [cm]",50,-5,5,50,-5,5);
    hist_list.push_back(h_XYvertex);
  TH2D *h_XYvertex_thrown = new TH2D("XYvertex_THROWN","XYvertex;Vertex x [cm];Vertex y [cm]",50,-5,5,50,-5,5);
    hist_list.push_back(h_XYvertex_thrown);
  TH1D *h_coplanarity = new TH1D("Coplanarity","Coplanarity; rho Angle [Degrees]; prot Angle [Degrees];Counts",300,90, 270);
    hist_list.push_back(h_coplanarity);

  /****** PiPlus ******/
  TH2D *h_pip_p_theta_uncut = new TH2D ("pip_p_theta_uncut","Pip_PVSTheta_uncut; theta [degree];p [GeV]; Counts",200,0,140,200,0,10);
    hist_list.push_back(h_pip_p_theta_uncut);
  TH2D *h_pip_p_theta_eb = new TH2D ("pip_p_theta_eb","Pip_PVSTheta_eb ; theta [degree];p [GeV]; Counts",200,0,140,200,0,10);
    hist_list.push_back(h_pip_p_theta_eb);
  TH1D *h_pip_from_Beam_uncut = new TH1D("pip_from_Beam_uncut","pip_from_Beam; Angle [Degrees];Counts",300,0,180);
    hist_list.push_back(h_pip_from_Beam_uncut);
  TH1D *h_pip_from_Beam_eb = new TH1D("pip_from_Beam_eb","pip_from_Beam; Angle [Degrees];Counts",300,0,180);
    hist_list.push_back(h_pip_from_Beam_eb);
  TH2D *h_pip_p_theta_THROWN_uncut = new TH2D ("pip_p_theta_THROWN_uncut","Prot_PVSTheta ; theta [degree];p [GeV]; Counts",200,0,140,200,0,10);
    hist_list.push_back(h_pip_p_theta_THROWN_uncut);
  TH2D *h_pip_p_theta_THROWN_eb = new TH2D ("pip_p_theta_THROWN_eb","Prot_PVSTheta_eb; theta [degree];p [GeV]; Counts",200,0,140,200,0,10);
    hist_list.push_back(h_pip_p_theta_THROWN_eb);

  /****** PiMinus ******/

  /****** Protons ******/
  TH2D *h_prot_p_theta_uncut = new TH2D ("prot_p_theta_uncut","Prot_PVSTheta ; theta [degree];p [GeV]; Counts",200,0,140,200,0,10);
    hist_list.push_back(h_prot_p_theta_uncut);
  TH2D *h_prot_p_theta_eb = new TH2D ("prot_p_theta_eb","Prot_PVSTheta_eb ; theta [degree];p [GeV]; Counts",200,0,140,200,0,10);
   hist_list.push_back(h_prot_p_theta_eb);
  TH1D *h_prot_from_Beam_uncut = new TH1D("prot_from_Beam_uncut","prot_from_Beam; Angle [Degrees];Counts",300,0,180);
    hist_list.push_back(h_prot_from_Beam_uncut);
  TH2D *h_prot_p_theta_THROWN_uncut = new TH2D ("prot_p_theta_THROWN_uncut","Prot_PVSTheta ; theta [degree];p [GeV]; Counts",200,0,140,200,0,10);
    hist_list.push_back(h_prot_p_theta_THROWN_uncut);
  TH2D *h_prot_p_theta_THROWN_eb = new TH2D ("prot_p_theta_THROWN_eb","Prot_PVSTheta_eb; theta [degree];p [GeV]; Counts",200,0,140,200,0,10);
    hist_list.push_back(h_prot_p_theta_THROWN_eb);
  TH3D *h_prot_duplicate_tracks_presort = new TH3D("prot_duplicate_tracks_presort","prot_duplicate_tracks PRE SORTING;p1.pX-p2.X[GeV];p1.pY-p2.pY[GeV];p1.pZ-p2.pZ[GeV]",100,-2,2,100,-2,2,100,-2,2);
    hist_list.push_back(h_prot_duplicate_tracks_presort);
  TH3D *h_prot_duplicate_tracks_uncut = new TH3D("prot_duplicate_tracks_uncut","prot_duplicate_tracks;p1.pX-p2.X[GeV];p1.pY-p2.pY[GeV];p1.pZ-p2.pZ[GeV]",50,-2,2,50,-2,2,50,-2,2);
    hist_list.push_back(h_prot_duplicate_tracks_uncut);
  TH3D *h_prot_duplicate_tracks_protmisrecon = new TH3D("prot_duplicate_tracks_protmisrecon","prot_duplicate_tracks CUT;p1.pX-p2.X[GeV];p1.pY-p2.pY[GeV];p1.pZ-p2.pZ[GeV]",100,-2,2,100,-2,2,100,-2,2);
    hist_list.push_back(h_prot_duplicate_tracks_protmisrecon);


  /****** PiPlus vs Protons ******/
  TH2D *h_pip_prot_from_Beam_uncut = new TH2D("pip_prot_from_Beam_uncut","pip and prot _from_Beam; Pip Angle [Degrees]; Prot Angle [Degrees];Counts",300,0,180,300,0,180);
    hist_list.push_back(h_pip_prot_from_Beam_uncut);

  /****** PMiss ******/
  TH1D *h_pmissVSbeam = new TH1D("pmissVSbeam","pmissVSbeam;pmiss;beam", 200, -1, 1);
    hist_list.push_back(h_pmissVSbeam);
  TH1D *h_pmissVSbeam_eb = new TH1D("pmissVSbeam_eb","h_pmissVSbeam_eb;pmiss Angle to beam ;counts", 200, -1, 1);
    hist_list.push_back(h_pmissVSbeam_eb);
  TH1D *h_pmissZ_uncut = new TH1D ("pmissZ_uncut","hmissZ;z_pmiss;counts", 200, -10,10);
    hist_list.push_back(h_pmissZ_uncut);
  TH1D *h_pmissZ_eb = new TH1D ("pmissZ_eb","pmissZ_eb;z_pmiss;counts", 200, -10,10);
    hist_list.push_back(h_pmissZ_eb);
  TH2D *h_pmissZ_s_uncut = new TH2D ("pmiss_s_uncut","pmiss_s_uncut;z_pmiss;s;counts", 200, -10,10,20,0,20);
    hist_list.push_back(h_pmissZ_s_uncut);
  TH2D *h_pmissAngle_s_uncut = new TH2D ("pmissAngle_s","pmissAngle_s;pmissAngle;s;counts", 200, -10,10,20,0,20);
    hist_list.push_back(h_pmissAngle_s_uncut);
  TH2D *h_pmissZ_perp_uncut = new TH2D ("pmissZ_perp_uncut","pmissZ_vs_perp;pmiss.Z;pmiss_perp;counts", 200, -2,2, 200, 0,2);
    hist_list.push_back(h_pmissZ_perp_uncut);
  TH2D *h_pmissZ_perp_eb = new TH2D ("pmissZ_perp_eb","pmissZ_vs_t_eb;pmiss;pmiss_perp;counts", 200, -2,2, 200, 0,2);
    hist_list.push_back(h_pmissZ_perp_eb);
  TH2D *h_pmiss_Mag_Angle_uncut = new TH2D ("pmiss_Mag_Angle_uncut","pmiss_Mag_Angl_uncut;pmiss angle;pmiss mag", 200, -1,1, 200, 0,3);
    hist_list.push_back(h_pmiss_Mag_Angle_uncut);
  TH2D *h_pmiss_Mag_Angle_eb = new TH2D ("pmiss_Mag_Angle_eb","pmiss_Mag_Angle_eb;pmiss angle;pmiss mag", 200, -1,1, 200, 0,3);
    hist_list.push_back(h_pmiss_Mag_Angle_eb);

  TH1D *h_pmiss_uncut = new TH1D("pmiss_uncut", "Missing Momentum [GeV];Counts",200,0.,2.);
    hist_list.push_back(h_pmiss_uncut);
  TH1D *h_pmiss_tcut = new TH1D("pmiss_tcut", "Missing Momentum [GeV];pmiss[GeV];Counts",200,0.,2.);
    hist_list.push_back(h_pmiss_tcut);
  TH1D *h_pmiss_eb = new TH1D("pmiss_eb", "Missing Momentum [GeV];pmiss[GeV];Counts",200,0.,2.);
    hist_list.push_back(h_pmiss_eb);
  TH1D *h_pmiss_THROWN_uncut = new TH1D("pmiss_THROWN_uncut", "Missing Momentum [GeV];pmiss[GeV];Counts",200,0.,2.);
    hist_list.push_back(h_pmiss_THROWN_uncut);
  TH1D *h_pmiss_THROWN_eb = new TH1D("pmiss_THROWN_eb", "Missing Momentum [GeV];pmiss[GeV];Counts",200,0.,2.);
    hist_list.push_back(h_pmiss_THROWN_eb);

  /****** Rho0 Mass ******/
  TH1D *h_rho0counts_uncut = new TH1D("Rho0_Counts_uncut","Rho0Counts_before;Mass [GeV];Counts",90,0,3);
    hist_list.push_back(h_rho0counts_uncut);
  TH1D *h_rho0counts_pre_prot_sorting = new TH1D("Rho0_Counts_PRE_prot_sorting","Rho0Counts_PRE_prot_sorting;Mass [GeV];Counts",90,0,5);
    hist_list.push_back(h_rho0counts_pre_prot_sorting);
  TH1D *h_rho0counts_tcut = new TH1D("Rho0_Counts_tcut","Rho0Counts_tcut;Mass [GeV];Counts",90,0,5);
    hist_list.push_back(h_rho0counts_tcut);
    TH1D *h_rho0counts_eb = new TH1D("Rho0_Counts_eb","Rho0Counts_eb;Mass [GeV];Counts",90,0,5);
    hist_list.push_back(h_rho0counts_eb);
  TH1D *h_rho0counts_THROWN_uncut = new TH1D("Rho0_Counts_THROWN_funcut","Rho0Counts_before;Mass [GeV];Counts",300,0,3);
    hist_list.push_back(h_rho0counts_THROWN_uncut);
  TH1D *h_rho0counts_THROWN_tcut = new TH1D("Rho0Counts_THROWN_tcut","Rho0Counts_tcut;Mass [GeV];Counts",100,0,5);
    hist_list.push_back(h_rho0counts_THROWN_tcut);
    TH1D *h_rho0counts_THROWN_eb = new TH1D("Rho0Counts_THROWN_eb","Rho0Counts_eb;Mass [GeV];Counts",100,0,5);
      hist_list.push_back(h_rho0counts_THROWN_eb);

  /****** PMiss vs Rho0 Mass ******/
  TH2D *h_pmiss_vs_rho0counts_uncut = new TH2D("rho0counts_vs_Pmiss_uncut","rho0 vs pmiss before;rho0_before[GeV];PMiss;Counts_after",100,0,5,200,0.,2.);
    hist_list.push_back(h_pmiss_vs_rho0counts_uncut);
  TH2D *h_pmiss_vs_rho0counts_tcut = new TH2D("rho0counts_tcut vs Pmiss_tcut","rho0 vs pmiss tcut;rho0_tcut[GeV];PMiss_tcut;Counts",100,0,5,200,0.,2.);
    hist_list.push_back(h_pmiss_vs_rho0counts_tcut);
    TH2D *h_pmiss_vs_rho0counts_eb = new TH2D("rho0counts_eb vs Pmiss_eb","rho0 vs pmiss eb;rho0_ev[GeV];PMiss_ev;Counts",100,0,5,200,0.,2.);
    hist_list.push_back(h_pmiss_vs_rho0counts_eb);

  /****** T ******/
  TH1D *h_t_uncut = new TH1D("t_uncut","t;-t [GeV^2]",20,0,20);
    hist_list.push_back(h_t_uncut);
  TH1D *h_t_tcut = new TH1D("t_tcut","t;-t [GeV^2]",20,0,20);
    hist_list.push_back(h_t_tcut);
    TH1D *h_t_eb = new TH1D("t_eb","t;-t [GeV^2]",20,0,20);
 hist_list.push_back(h_t_eb);

  /****** PMinus ******/
  TH1D *h_pminus_pmiss_uncut = new TH1D("pminus_Pmiss","pminus_pmiss;pminus",50,0,2);
    hist_list.push_back(h_pminus_pmiss_uncut);
    TH1D *h_pminus_pmiss_eb = new TH1D("pminus_Pmiss_eb","pminus_pmiss;pminus",50,0,2);     hist_list.push_back(h_pminus_pmiss_eb);

  /****** Energy Balance ******/
  TH1D *h_energy_balance = new TH1D ("energy_balance","Energy Balance; Final energy- initial energy ;counts",50,-10,10);
    hist_list.push_back(h_energy_balance);
    TH1D *h_energy_balance_eb = new TH1D ("energy_balance_eb","Energy Balance CUT; Final energy- initial energy ;counts",50,-10,10);
      hist_list.push_back(h_energy_balance_eb);
      //TH1D *h_energy_balance = new TH1D ("energy_balance","Energy Balance; Final energy- initial energy ;counts",50,-10,10);
    //hist_list.push_back(h_energy_balance);

 /******Beam energy *****/
    TH1D *h_beamenergy_uncut_unweighted = new TH1D("beamenergy_uncut_unweighted","beamenergy_uncut;beam energry [GeV]; counts", 120,0,12);
	hist_list.push_back(h_beamenergy_uncut_unweighted);
	TH1D *h_beamenergy_uncut = new TH1D("beamenergy_uncut","beamenergy_uncut;beam energry [GeV]; counts", 120,0,12);
	hist_list.push_back(h_beamenergy_uncut);
	TH1D *h_beamenergy_tcut = new TH1D("beamenergy_tcut","beamenergy_tcut;beam energry [GeV]; counts", 120,0,12);
	hist_list.push_back(h_beamenergy_tcut);
	TH1D *h_beamenergy_eb = new TH1D("beamenergy_eb","beamenergy_eb;beam energry [GeV]; counts", 120,0,12);
	hist_list.push_back(h_beamenergy_eb);


/********************************************** Event Loop **********************************************/
for( int event=0; event < inputTree-> GetEntries(); event++){

  if (event%10000==0)
  cerr << "Working on event " << event << "\n";

  inputTree-> GetEvent(event);

  h_CL_uncut->Fill(TMath::Prob(kin_chisq,kin_ndf),weight);

  if (TMath::Prob(kin_chisq,kin_ndf)<0.02)
    continue;

  h_prot_duplicate_tracks_presort->Fill(p4_prot1_kin->X()-p4_prot2_kin->X(),p4_prot1_kin->Y()-p4_prot2_kin->Y(),p4_prot1_kin->Z()-p4_prot2_kin->Z());
  h_beamenergy_uncut_unweighted ->Fill(p4_beam_kin->E());
  h_beamenergy_uncut->Fill(p4_beam_kin->E(),weight);

  /********************************************** Defining Variables **********************************************/

    TLorentzVector p4_rho0_meas = (*p4_pip_meas)+(*p4_pim_meas);
    TLorentzVector p4_rho0_kin = (*p4_pip_kin)+(*p4_pim_kin);
    TLorentzVector p4_pmiss = (*p4_prot_lead_kin+(*p4_pip_kin + *p4_pim_kin) - *p4_beam_kin);
    TVector3 p3_pmiss = p4_pmiss.Vect();
    //TVector3 p3_pmiss = (p4_prot_lead_kin.Vect() + (p4_pip_kin->Vect() + p4_pim_kin->Vect()) - p4_beam_kin->Vect() ); //pmiss = lead + rho - beam
    TLorentzVector p4_pmiss_thrown = (*p4_prot_lead_thrown + (*p4_pip_thrown + *p4_pim_thrown) - *p4_beam_thrown ); //pmiss = lead + rho - beam
    TVector3 p3_pmiss_thrown = p4_pmiss_thrown.Vect();
    TVector3 v3_prot_lead = p4_prot_lead_kin->Vect();
    TVector3 v3_prot_lead_thrown = p4_prot_lead_thrown->Vect();
    TVector3 beam_mom = p4_beam_meas->Vect();
    TVector3 v3_pip = p4_pip_meas->Vect();
    TVector3 v3_rho = p4_rho0_meas.Vect();

    TLorentzVector p4_rho0_thrown =(*p4_pip_thrown)+(*p4_pim_thrown);
    TVector3 v3_pip_thrown = p4_pip_thrown->Vect();

    double t_mandel = (*p4_beam_kin - p4_rho0_kin).M2();
    double s_mandel = (*p4_prot_lead_kin + p4_rho0_kin).M2();

    TLorentzVector delta4mom = (*p4_pip_kin + *p4_pim_kin + *p4_prot1_kin + *p4_prot2_kin - TLorentzVector( 0,0,0,2*mN) - *p4_beam_kin);


/********************************************** Sorting Protons **********************************************/
h_rho0counts_pre_prot_sorting->Fill(p4_rho0_kin.M(),weight);

const double pleadcutoff = 1;

  if (p4_prot1_kin->P() > pleadcutoff && p4_prot2_kin->P() < pleadcutoff)
  {
    p4_prot_lead_kin = p4_prot1_kin;
    p4_prot_recoil_kin = p4_prot2_kin;
    x4_prot_lead_kin = x4_prot1_kin;
    x4_prot_recoil_kin = x4_prot2_kin;

    p4_prot_lead_thrown = p4_prot1_thrown;
    p4_prot_recoil_thrown = p4_prot2_thrown;
  }

  else if (p4_prot1_kin->P() < pleadcutoff && p4_prot2_kin->P() > pleadcutoff)
  {
    p4_prot_lead_kin = p4_prot2_kin;
    p4_prot_recoil_kin = p4_prot1_kin;
    x4_prot_lead_kin = x4_prot2_kin;
    x4_prot_recoil_kin = x4_prot1_kin;

    p4_prot_lead_thrown = p4_prot2_thrown;
    p4_prot_recoil_thrown = p4_prot1_thrown;
  }

  else
    continue;

  if (p4_prot_recoil_kin->P() < 0.3)
    continue;

/********************************************** Fill Uncut Histograms **********************************************/
  h_CL_cut->Fill(TMath::Prob(kin_chisq,kin_ndf),weight);
  h_zprot1vertex->Fill(x4_prot1_meas->Z(),weight);
  h_zprot2vertex->Fill(x4_prot2_meas->Z(),weight);
  h_XYvertex->Fill(p4_prot2_meas->X(),p4_prot2_meas->Y(),weight);

  h_pmiss_uncut->Fill((p3_pmiss).Mag(),weight);
  h_pmiss_THROWN_uncut -> Fill(p3_pmiss_thrown.Mag(),weight);
  h_rho0counts_uncut->Fill(p4_rho0_kin.M(),weight);
  h_rho0counts_THROWN_uncut->Fill(p4_rho0_thrown.M());
  h_t_uncut->Fill(-t_mandel,weight);
  h_pmiss_vs_rho0counts_uncut->Fill((p4_rho0_kin).M(),p3_pmiss.Mag(),weight);
  h_prot_from_Beam_uncut->Fill(180./M_PI*v3_prot_lead.Angle(beam_mom));
  h_pip_from_Beam_uncut->Fill(180./M_PI*v3_pip.Angle(beam_mom));
  h_pip_prot_from_Beam_uncut->Fill(180./M_PI*v3_pip.Angle(beam_mom),180./M_PI*v3_prot_lead.Angle(beam_mom));  h_coplanarity -> Fill(fabs(v3_rho.Phi()-v3_prot_lead.Phi())*180/TMath::Pi());
  h_pip_p_theta_uncut->Fill(180./M_PI*p4_pip_meas->Theta(),v3_pip.Mag());
  h_prot_p_theta_uncut->Fill(180./M_PI*p4_prot_lead_kin->Theta(),v3_prot_lead.Mag());
  h_prot_duplicate_tracks_uncut->Fill(p4_prot1_kin->X()-p4_prot2_kin->X(),p4_prot1_kin->Y()-p4_prot2_kin->Y(),p4_prot1_kin->Z()-p4_prot2_kin->Z());

  h_prot_p_theta_THROWN_uncut->Fill(180./M_PI*v3_prot_lead_thrown.Theta(),v3_prot_lead_thrown.Mag());
  h_pip_p_theta_THROWN_uncut->Fill(180./M_PI*v3_pip_thrown.Theta(),v3_pip_thrown.Mag());

  h_pmissZ_uncut->Fill(p3_pmiss.Z(),weight);
  h_pmissZ_s_uncut->Fill(p3_pmiss.Z(),s_mandel,weight);
  h_pmissAngle_s_uncut->Fill(p4_pmiss.Vect().Mag(),s_mandel,weight);
  h_pmissZ_perp_uncut->Fill(p4_pmiss.Z(),p3_pmiss.Perp(),weight);
  h_pminus_pmiss_uncut->Fill(p4_pmiss.Minus(),weight);
  h_pmiss_Mag_Angle_uncut->Fill(p4_pmiss.CosTheta(),p4_pmiss.Vect().Mag(),weight);

  h_energy_balance->Fill(delta4mom.E(), weight);

/********************************************** T - Cut **********************************************/
if (-t_mandel < 1.5)
    continue;

/********************************************** Fill T - Cut Histograms **********************************************/

    h_t_tcut -> Fill(-t_mandel,weight);
    h_pmiss_tcut -> Fill(p3_pmiss.Mag(),weight);
    h_rho0counts_tcut -> Fill(p4_rho0_kin.M(),weight);
    h_rho0counts_THROWN_tcut->Fill(p4_rho0_thrown.M());
    h_pmiss_vs_rho0counts_tcut -> Fill((p4_rho0_kin).M(),p3_pmiss.Mag(),weight);
    h_beamenergy_tcut->Fill(p4_beam_kin->E(),weight);


/********************************************** Energy Balance - Cut **********************************************/
   if (delta4mom.E() < -3 || delta4mom.E() >3)
       continue;

/********************************************** Fill Energy Balance Cut Histograms **********************************************/
h_energy_balance_eb->Fill(delta4mom.E(), weight);

h_t_eb -> Fill(-t_mandel,weight);
h_pip_from_Beam_uncut->Fill(180./M_PI*v3_pip.Angle(beam_mom));
h_pmiss_eb -> Fill(p3_pmiss.Mag(),weight);
h_pmiss_THROWN_eb -> Fill(p3_pmiss_thrown.Mag(),weight);
h_rho0counts_eb -> Fill(p4_rho0_kin.M());
h_rho0counts_THROWN_eb->Fill(p4_rho0_thrown.M());
h_pmiss_vs_rho0counts_eb -> Fill((p4_rho0_kin).M(),p3_pmiss.Mag(),weight);
h_pmissVSbeam_eb -> Fill(p3_pmiss.CosTheta(),weight);
h_pip_p_theta_eb -> Fill(180./M_PI*v3_pip.Theta(),v3_pip.Mag());

h_pmissZ_eb ->Fill(p3_pmiss.Z(),weight);
h_pmissZ_perp_eb ->Fill(p4_pmiss.Z(),p3_pmiss.Perp(),weight);
h_pminus_pmiss_eb ->Fill(p4_pmiss.Minus(),weight);
h_pmiss_Mag_Angle_eb ->Fill(p4_pmiss.CosTheta(),p4_pmiss.Vect().Mag(),weight);

h_beamenergy_eb->Fill(p4_beam_kin->E(),weight);

h_prot_p_theta_THROWN_eb->Fill(180./M_PI*v3_prot_lead_thrown.Theta(),v3_prot_lead_thrown.Mag());
h_pip_p_theta_THROWN_eb->Fill(180./M_PI*v3_pip_thrown.Theta(),v3_pip_thrown.Mag());



/********************************************** Cutting on Duplicate Track Protons **********************************************/
  if ((fabs(p4_prot1_kin->X() - p4_prot2_kin->X()) == 0.01) && (fabs(p4_prot1_kin->Y() - p4_prot2_kin->Y()) == 0.01) && (fabs(p4_prot1_kin->Z() - p4_prot2_kin->Z()) == 0.01))
    continue;
/********************************************** Fill Duplicate Track Protons, Missed PID, and T - Cut Histograms *********************/
h_prot_duplicate_tracks_protmisrecon->Fill(p4_prot1_kin->X()-p4_prot2_kin->X(),p4_prot1_kin->Y()-p4_prot2_kin->Y(),p4_prot1_kin->Z()-p4_prot2_kin->Z());

 outputTree->Fill();

}

inputFile->Close();

/********************************************** WRITE OUT HISTOGRAMS **********************************************/

fout->cd();

h_CL_uncut->Write();
h_CL_cut->Write();
h_zprot1vertex->Write();
h_zprot2vertex->Write();
h_zprot_lead_vertex->Write();
h_XYvertex->Write();

h_beamenergy_uncut_unweighted->Write();
h_beamenergy_uncut->Write();

fout->cd("UnCut");
h_rho0counts_pre_prot_sorting->Write();
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
h_beamenergy_uncut_unweighted->Write();
h_beamenergy_uncut->Write();
h_energy_balance->Write();

fout->cd();

fout->cd("TCut");
h_t_tcut->Write();
h_pmiss_tcut->Write();
h_rho0counts_tcut->Write();
h_rho0counts_THROWN_tcut->Write();
h_pmiss_vs_rho0counts_tcut->Write();
h_beamenergy_tcut->Write();
fout->cd();

fout->cd("Energy Balance");
h_energy_balance_eb->Write();
h_t_eb->Write();
h_pmiss_eb->Write();
h_pmiss_THROWN_eb->Write();
h_pmiss_vs_rho0counts_eb->Write();
h_rho0counts_eb->Write();
//h_rho0counts_THROWN_eb->Write();
h_pmissVSbeam_eb->Write();
h_pip_p_theta_eb->Write();
h_pip_p_theta_THROWN_eb->Write();
h_prot_p_theta_eb->Write();
h_prot_p_theta_THROWN_eb->Write();
h_pmissZ_eb->Write();
h_pmissZ_perp_eb->Write();
//h_pminus_pmiss_eb->Write();
h_pmiss_Mag_Angle_eb->Write();
h_beamenergy_eb->Write();
fout->cd();

fout->cd("protmisrecon");
h_prot_duplicate_tracks_presort->Write();
h_prot_duplicate_tracks_uncut->Write();
h_prot_duplicate_tracks_protmisrecon->Write();
fout->cd();

outputTree->Write();
fout->Close();

}
