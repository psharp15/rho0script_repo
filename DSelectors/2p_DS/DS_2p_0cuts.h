#ifndef DS_2p_0cuts_h
#define DS_2p_0cuts_h

#include <iostream>

#include "DSelector/DSelector.h"
#include "DSelector/DHistogramActions.h"
#include "DSelector/DCutActions.h"
#include "TH1I.h"
#include "TH2I.h"

class DS_2p_0cuts : public DSelector
{
	public:

		DS_2p_0cuts(TTree* locTree = NULL) : DSelector(locTree){}
		virtual ~DS_2p_0cuts(){}

		void Init(TTree *tree);
		Bool_t Process(Long64_t entry);

	private:

		void Get_ComboWrappers(void);
		void Finalize(void);

		// BEAM POLARIZATION INFORMATION
		UInt_t dPreviousRunNumber;
		bool dIsPolarizedFlag; //else is AMO
		bool dIsPARAFlag; //else is PERP or AMO

		bool dIsMC;

		// ANALYZE CUT ACTIONS
		// // Automatically makes mass histograms where one cut is missing
		DHistogramAction_AnalyzeCutActions* dAnalyzeCutActions;

		//CREATE REACTION-SPECIFIC PARTICLE ARRAYS

		//Step 0
		DParticleComboStep* dStep0Wrapper;
		DBeamParticle* dComboBeamWrapper;
		DChargedTrackHypothesis* dPiPlusWrapper;
		DChargedTrackHypothesis* dPiMinusWrapper;
		DChargedTrackHypothesis* dProton1Wrapper;
		DChargedTrackHypothesis* dProton2Wrapper;

		// DEFINE YOUR HISTOGRAMS HERE
		// EXAMPLES:
		TH1I* dHist_MissingMassSquared;
		TH1I* dHist_MissingEnergy;
		TH1I* dHist_BeamEnergy;
		TH1I* dHist_CombosperEvent_before;
		TH1I* dHist_CombosperEvent_after;
        
        TH1F* dHist_RFTiming;
        TH1D* dHist_ProtonNumber;
        TH1D* dHist_PipNumber;
        TH1D* dHist_PimNumber;
        TH1D* dHist_BeamNumber;
	
	ClassDef(DS_2p_0cuts, 0);
};

void DS_2p_0cuts::Get_ComboWrappers(void)
{
	//Step 0
	dStep0Wrapper = dComboWrapper->Get_ParticleComboStep(0);
	dComboBeamWrapper = static_cast<DBeamParticle*>(dStep0Wrapper->Get_InitialParticle());
	dPiPlusWrapper = static_cast<DChargedTrackHypothesis*>(dStep0Wrapper->Get_FinalParticle(0));
	dPiMinusWrapper = static_cast<DChargedTrackHypothesis*>(dStep0Wrapper->Get_FinalParticle(1));
	dProton1Wrapper = static_cast<DChargedTrackHypothesis*>(dStep0Wrapper->Get_FinalParticle(2));
	dProton2Wrapper = static_cast<DChargedTrackHypothesis*>(dStep0Wrapper->Get_FinalParticle(3));
}

#endif // DS_2p_0cuts.h
