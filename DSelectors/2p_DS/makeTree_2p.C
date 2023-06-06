R__LOAD_LIBRARY(libDSelector)
void makeTree_2p()
{
	int NThreads = 32;
	gROOT->ProcessLine(".x $(ROOT_ANALYSIS_HOME)/scripts/Load_DSelector.C");
    
///Carbon PROTON PROTON
// AV18    
    //	missing unknown
/*  TChain *chain = new TChain("gc12_pippimprotprotinc__F4_B4_Tree");
    chain->Add("/volatile/halld/home/psharp/simulation/halld_sim_swif/AV18_C12/0bg/root/trees/tree_gc12_pippimprotprotinc__F4_B4_gen_gcf_090306_*.root");
//   chain->Process("./DS_2p.C++","flattree_gc12__protprot_AV18_inc_0bg.root"); 
*/ 
// AV4    
   //	missing unknown
/*  TChain *chain = new TChain("gc12_pippimprotprotinc__F4_B4_Tree");
    chain->Add("/volatile/halld/home/psharp/simulation/halld_sim_swif/AV4_C12/0bg/root/trees/tree_gc12_pippimprotprotinc__F4_B4_gen_gcf_090306_*.root");
//    chain->Process("./DS_2p.C++","flattree_gc12__protprot_AV4_inc_0bg.root"); 
*/
// N2LO
     //	missing unknown
  TChain *chain = new TChain("gc12_pippimprotprotinc__F4_B4_Tree");
    chain->Add("/volatile/halld/home/psharp/simulation/halld_sim_swif/N2LO_C12/0bg/root/trees/tree_gc12_pippimprotprotinc__F4_B4_gen_gcf_090306_*.root");
//    chain->Process("./DS_2p.C++","flattree_gc12__protprot_N2LO_inc_0bg.root"); 
 

	 DPROOFLiteManager *dproof = new DPROOFLiteManager();
        dproof->Process_Chain(chain, "./DS_2p.C++", NThreads, "hist_carbon_N2LO_2p.root", "test_carbon_N2LO_2p.root"); // multi-threaded using dproof -> faster
        chain->Process("./DS_2p.C++","flattree_gc12__protprot_N2LO_inc_0bg.root");
    
}
