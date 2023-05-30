using namespace std;


R__LOAD_LIBRARY(libDSelector)


int protons, target, potential;

void makeTree_input()
{
	int NThreads = 32;
	gROOT->ProcessLine(".x $(ROOT_ANALYSIS_HOME)/scripts/Load_DSelector.C");
 
	cin >> protons;
	switch (protons){
	case 1:
		cin >> target;
		switch (target){
			case AV18;
}
}
 
///Deuterium (AV18)
//	missing neutron
/*	TChain *chain = new TChain("gd_pippimprotmissn__F4_B4_T2_S4_Tree");
	chain->Add("/lustre19/expphy/volatile/halld/home/psharp/halld_1p_swif/AV18_D2/0bg/root/trees/tree_gd_pippimprotmissn__F4_B4_T2_S4_gen_gcf_090207_*.root");
 	chain->Process("./DS_1p.C++","flattree_gd__prot_AV18_missn_0bg.root"); 
*/
// 	missing unknown
/* 	TChain *chain = new TChain("gd_pippimprotinc__F4_B4_T2_S4_Tree");
 	chain->Add("/volatile/halld/home/psharp/simulation/halld_sim_swif/AV18_D2/0bg/root/trees/tree_gd_pippimprotinc__F4_B4_T2_S4_gen_gcf_090207_*.root");
  //  	chain->Process("./DS_1p.C++","flattree_gd__prot_AV18_inc_0bg.root"); 
*/

///Helium (AV18)
//	missing neutron
/*  TChain *chain = new TChain("ghe_pippimprotmissn__F4_B4_T2_S4_Tree");
    chain->Add("/lustre19/expphy/volatile/halld/home/psharp/halld_1p_swif/AV18_He4/0bg/root/trees/tree_ghe_pippimprotmissn__F4_B4_T2_S4_gen_gcf_090091_*.root");
//    chain->Process("./DS_1p.C++","flattree_ghe__prot_AV18_missn_0bg.root"); 
 */

//	missing unknown
/*	 TChain *chain = new TChain("ghe_pippimprotinc__F4_B4_T2_S4_Tree");
    chain->Add("/volatile/halld/home/psharp/simulation/halld_sim_swif/AV18_He4/0bg/root/trees/tree_ghe_pippimprotinc__F4_B4_T2_S4_gen_gcf_090091_*.root");
    //chain->Process("./DS_1p.C++","flattree_ghe__prot_AV18_inc_0bg.root"); 
*/

///Carbon
// AV18    
    //	missing neutron
/*  TChain *chain = new TChain("gc12_pippimprotmissn__F4_B4_T2_S4_Tree");
    chain->Add("/lustre19/expphy/volatile/halld/home/psharp/halld_1p_swif/AV18_C12/0bg/root/trees/tree_gc12_pippimprotmissn__F4_B4_T2_S4_gen_gcf_090306_*.root");
    chain->Process("./DS_1p.C++","flattree_gc12__prot_AV18_missn_0bg.root"); 
 */

    //	missing unknown
/*  TChain *chain = new TChain("gc12_pippimprotinc__F4_B4_Tree");
    chain->Add("/volatile/halld/home/psharp/simulation/halld_sim_swif/AV18_C12/0bg/root/trees/tree_gc12_pippimprotinc__F4_B4_gen_gcf_090306_*.root");
//    chain->Process("./DS_1p.C++","flattree_gc12__prot_AV18_inc_0bg.root"); 
*/
// AV4    
    //	missing neutron
/*  TChain *chain = new TChain("gc12_pippimprotmissn__F4_B4_T2_S4_Tree");
    chain->Add("/lustre19/expphy/volatile/halld/home/psharp/halld_1p_swif/AV4_C12/0bg/root/trees/tree_gc12_pippimprotinc__F4_B4_gen_gcf_090306_*.root");
    chain->Process("./DS_1p.C++","flattree_gc12__prot_AV4_missn_0bg.root"); 
 */

    //	missing unknown
/*  TChain *chain = new TChain("gc12_pippimprotinc__F4_B4_Tree");
    chain->Add("/lustre19/expphy/volatile/halld/home/psharp/halld_1p_swif/AV4_C12/0bg/root/trees/tree_gc12_pippimprotinc__F4_B4_gen_gcf_090306_*.root");
    chain->Process("./DS_1p.C++","flattree_gc12__prot_AV4_inc_0bg.root"); 
 */
    
    
// N2LO
    //	missing neutron
/*  TChain *chain = new TChain("gc12_pippimprotmissn__F4_B4_T2_S4_Tree");
    chain->Add("/lustre19/expphy/volatile/halld/home/psharp/halld_1p_swif/N2LO_C12/0bg/root/trees/tree_gc12_pippimprotinc__F4_B4_gen_gcf_090306_*.root");
    chain->Process("./DS_1p.C++","flattree_gc12__prot_N2LO_missn_0bg.root"); 
 */

    //	missing unknown
  TChain *chain = new TChain("gc12_pippimprotinc__F4_B4_Tree");
    chain->Add("/volatile/halld/home/psharp/simulation/halld_sim_swif/N2LO_C12/0bg/root/trees/tree_gc12_pippimprotinc__F4_B4_gen_gcf_090306_*.root");
//    chain->Process("./DS_1p.C++","flattree_gc12__prot_N2LO_inc_0bg.root"); 
 


/*	DPROOFLiteManager *dproof = new DPROOFLiteManager();
  	dproof->Process_Chain(chain, "./DS_1p.C++", NThreads, "hist_helium.root", "test_helium.root"); // multi-threaded using dproof -> faster
  	chain->Process("./DS_1p.C++","flattree_ghe__prot_AV18_inc_0bg.root"); 
*/
/*
	DPROOFLiteManager *dproof = new DPROOFLiteManager();
        dproof->Process_Chain(chain, "./DS_1p.C++", NThreads, "hist_deut.root", "test_deut.root"); // multi-threaded using dproof -> faster
        chain->Process("./DS_1p.C++","flattree_gd__prot_AV18_inc_0bg.root");  
*/

        DPROOFLiteManager *dproof = new DPROOFLiteManager();
        dproof->Process_Chain(chain, "./DS_1p.C++", NThreads, "hist_carbon_N2LO.root", "test_carbon_N2LO.root"); // multi-threaded using dproof -> faster
        chain->Process("./DS_1p.C++","flattree_gc12__prot_N2LO_inc_0bg.root");
 
}
