#include <string>
#include <iostream>
#include "TROOT.h"
#include "TFile.h"
#include "TTree.h"
#include "TDirectory.h"

using namespace std;

R__LOAD_LIBRARY(libDSelector)

void Run_Selector(string locInputFileName, string locTreeName, string locSelectorName, unsigned int locNThreads)
{  
  gROOT->ProcessLine(".x $(ROOT_ANALYSIS_HOME)/scripts/Load_DSelector.C");
  
  //tell it to compile selector (if user did not)
  if(locSelectorName[locSelectorName.size() - 1] != '+')
    locSelectorName += '+';
  
  cout << "file name, tree name, selector name, #threads = " << locInputFileName << ", " << locTreeName << ", " << locSelectorName << ", " << locNThreads << endl;

  TChain *chain = new TChain(locTreeName.c_str());
  chain->Add(locInputFileName.c_str());

  chain->Process(locSelectorName.c_str(),"");

  //DPROOFLiteManager *dproof = new DPROOFLiteManager();
  //dproof->Process_Chain(chain, "/work/halld2/home/jrpybus/analysis/rhoMinusSRC/analysis/DSelectors/DSelector_rhoMinus_p_p_classic.C+", locNThreads);

}

