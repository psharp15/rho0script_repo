#include "DS_2p_v2.h"

void DS_2p_v2::Init(TTree *locTree)
{

    cerr << "I'm in the init! /n";
	//SET OUTPUT FILE NAME
	dOutputFileName        = ""; //"" for none
	dOutputTreeFileName    = ""; //"" for none
	dFlatTreeFileName      = "output.root"; //output flat tree (one combo per tree entry), "" for none
	dFlatTreeName          = ""; //if blank, default name will be chosen
	dSaveDefaultFlatBranches = true; // False: don't save default branches, reduce disk footprint.

	// INITIALIZE THE TREE INTERFACE AND WRAPPERS
	bool locInitializedPriorFlag = dInitializedFlag; //save whether have been initialized previously
	DSelector::Init(locTree); //Called to initialize wrappers for each new TTree
	if(locInitializedPriorFlag)
		return; //have already created histograms, etc. below: exit

	Get_ComboWrappers();
	dPreviousRunNumber = 0;

	// MC INFORMATION
	dIsMC = (dTreeInterface->Get_Branch("MCWeight") != NULL);

	//INITIALIZATION: ANALYSIS ACTIONS
	std::deque<Particle_t> MyRho;
	MyRho.push_back(PiPlus); MyRho.push_back(PiMinus);

	//ANALYSIS ACTIONS: //Executed in order if added to dAnalysisActions
	//false/true below: use measured/kinfit data

        //PID
        dAnalysisActions.push_back(new DHistogramAction_ParticleID(dComboWrapper, false));
        //below: value: +/- N ns, Unknown: All PIDs, SYS_NULL: all timing systems
        //dAnalysisActions.push_back(new DCutAction_PIDDeltaT(dComboWrapper, false, 0.5, KPlus, SYS_BCAL));

        //UNUSED TRACKS AND SHOWERS
        dAnalysisActions.push_back(new DCutAction_NumUnusedTracks(dComboWrapper, 0, ""));
             //CUT: 0 unused tracks
        //dAnalysisActions.push_back(new DCutAction_Energy_UnusedShowers(dComboWrapper, 0, ""));
        dAnalysisActions.push_back(new DCutAction_NumUnusedShowers(dComboWrapper, 0, ""));
             //CUT: 0 unused showers

        //PIDFOM (for charged tracks)
        dAnalysisActions.push_back(new DHistogramAction_PIDFOM(dComboWrapper));
        //dAnalysisActions.push_back(new DCutAction_PIDFOM(dComboWrapper, KPlus, 0.1));
        dAnalysisActions.push_back(new DCutAction_EachPIDFOM(dComboWrapper, 0.1));
             //CUT: CL of each PID based on the FOM is 0.1

        //KINFIT RESULTS
        dAnalysisActions.push_back(new DHistogramAction_KinFitResults(dComboWrapper));
        dAnalysisActions.push_back(new DCutAction_KinFitFOM(dComboWrapper, 0.01, ""));
            //CUT: CL of the Kin Fit based on the FOM is 0.01

        //BEAM ENERGY
        dAnalysisActions.push_back(new DHistogramAction_BeamEnergy(dComboWrapper, true));
        dAnalysisActions.push_back(new DCutAction_BeamEnergy(dComboWrapper, true, 6, 10.8));
            //CUT: Beam Energy between 6 and 10.8 GeV

        //KINEMATICS
        dAnalysisActions.push_back(new DHistogramAction_ParticleComboKinematics(dComboWrapper, true));

        // ANALYZE CUT ACTIONS
        dAnalyzeCutActions = new DHistogramAction_AnalyzeCutActions( dAnalysisActions, dComboWrapper, false, 0, MyRho, 1000, 0.9, 2.4, "CutActionEffect" );

	//INITIALIZE ACTIONS
	Initialize_Actions();
	dAnalyzeCutActions->Initialize(); // manual action, must call Initialize()

	// MANUAL HISTOGRAMS:
	    gDirectory->mkdir( "Combos & Event" )->cd();
            dHist_CombosperEvent_before = new TH1I("Combos per Event Before", "Combos per Event Before; Combos; Events", 10, -0.5, 9.5 );
            dHist_CombosperEvent_after = new TH1I("Combos per Event After", "Combos per Event After; Combos; Events", 10, -0.5, 9.5 );
        gDirectory->cd( ".." );

        gDirectory->mkdir( "Number_of_Particles" )->cd();
           dHist_ProtonNumber = new TH1D( "ProtonNumber", ";Number of Protons Candidates in an Event", 10, 0, 10);
           dHist_PipNumber = new TH1D( "PipNumber", ";Number of #pi^{+} Candidates in an Event", 10, 0, 10);
           dHist_PimNumber = new TH1D( "PimNumber", ";Number of #pi^{-} Candidates in an Event", 10, 0, 10);
           dHist_BeamNumber = new TH1D( "BeamNumber", ";Number of Beam Candidates in an Event", 10, 0, 10);
           gDirectory->cd( ".." );

	dHist_MissingMassSquared = new TH1I("MissingMassSquared", ";Missing Mass Squared (GeV/c^{2})^{2}", 600, -0.06, 0.06);
	dHist_BeamEnergy = new TH1I("BeamEnergy", ";Beam Energy (GeV)", 600, 0.0, 12.0);
	dHist_MissingEnergy = new TH1I("MissingEnergy",";Missing Energy (GeV)", 1000, -1,3);


	//OUTPUT BRACHES
	dFlatTreeInterface->Create_Branch_Fundamental<Double_t>("accidweight");
   	dFlatTreeInterface->Create_Branch_Fundamental<Double_t>("RF_time");
  /*  dFlatTreeInterface->Create_Branch_NoSplitTObject<TLorentzVector>("beam_p4_meas");
    dFlatTreeInterface->Create_Branch_NoSplitTObject<TLorentzVector>("pim_p4_meas");
    dFlatTreeInterface->Create_Branch_NoSplitTObject<TLorentzVector>("pip_p4_meas");
    dFlatTreeInterface->Create_Branch_NoSplitTObject<TLorentzVector>("p1_p4_meas");
    dFlatTreeInterface->Create_Branch_NoSplitTObject<TLorentzVector>("p2_p4_meas");
    dFlatTreeInterface->Create_Branch_NoSplitTObject<TLorentzVector>("miss_p4_meas");
    dFlatTreeInterface->Create_Branch_NoSplitTObject<TLorentzVector>("beam_p4_kin");
    dFlatTreeInterface->Create_Branch_NoSplitTObject<TLorentzVector>("pim_p4_kin");
    dFlatTreeInterface->Create_Branch_NoSplitTObject<TLorentzVector>("pip_p4_kin");
    dFlatTreeInterface->Create_Branch_NoSplitTObject<TLorentzVector>("p1_p4_kin");
    dFlatTreeInterface->Create_Branch_NoSplitTObject<TLorentzVector>("p2_p4_kin");*/
    dFlatTreeInterface->Create_Branch_NoSplitTObject<TLorentzVector>("miss_p4_kin");
    dFlatTreeInterface->Create_Branch_NoSplitTObject<TLorentzVector>("thrownBeam");
    dFlatTreeInterface->Create_Branch_NoSplitTObject<TLorentzVector>("thrownPiMinus");
    dFlatTreeInterface->Create_Branch_NoSplitTObject<TLorentzVector>("thrownPiPlus");
    dFlatTreeInterface->Create_Branch_NoSplitTObject<TLorentzVector>("thrownProton1");
    dFlatTreeInterface->Create_Branch_NoSplitTObject<TLorentzVector>("thrownProton2");

    cerr << "I'm out of the the init! On to process/n";
}

Bool_t DS_2p_v2::Process(Long64_t locEntry)
{
    cerr << "I'm in process with locEntry value:" << locEntry << "\n";
	//CALL THIS FIRST
	DSelector::Process(locEntry); //Gets the data from the tree for the entry
	//cout << "RUN " << Get_RunNumber() << ", EVENT " << Get_EventNumber() << endl;
	//TLorentzVector locProductionX4 = Get_X4_Production();

	// GET POLARIZATION ORIENTATION
	UInt_t locRunNumber = Get_RunNumber();
	if(locRunNumber != dPreviousRunNumber)
	{
		dIsPolarizedFlag = dAnalysisUtilities.Get_IsPolarizedBeam(locRunNumber, dIsPARAFlag);
		dPreviousRunNumber = locRunNumber;
	}

	// SETUP UNIQUENESS TRACKING
	Reset_Actions_NewEvent();
	dAnalyzeCutActions->Reset_NewEvent(); // manual action, must call Reset_NewEvent()

	//EXAMPLE 1: Particle-specific info:
	set<Int_t> locUsedSoFar_BeamEnergy; //Int_t: Unique ID for beam particles. set: easy to use, fast to search

	//EXAMPLE 2: Combo-specific info:
	set<map<Particle_t, set<Int_t> > > locUsedSoFar_MissingMass;
    set<Int_t> NumberOfProtons;
    set<Int_t> NumberOfPiPlus;
    set<Int_t> NumberOfPiMinus;
    set<Int_t> NumberOfBeam;


   	int NumComboSurvived_after = 0;
	int NumComboSurvived_weighted = 0;
	//LOOP OVER COMBOS
	for(UInt_t loc_i = 0; loc_i < Get_NumCombos(); ++loc_i)
	{
		//INITIALIZE THE COMBO
	   dComboWrapper->Set_ComboIndex(loc_i);
		if(dComboWrapper->Get_IsComboCut())    // check whether the combo has been cut
		continue;                          // combo has been cut previously

		//GET PARTICLE INDICES
		Int_t locBeamID = dComboBeamWrapper->Get_BeamID();
		Int_t locPiPlusTrackID = dPiPlusWrapper->Get_TrackID();
		Int_t locPiMinusTrackID = dPiMinusWrapper->Get_TrackID();
		Int_t locProton1TrackID = dProton1Wrapper->Get_TrackID();
		Int_t locProton2TrackID = dProton2Wrapper->Get_TrackID();

		//GET Kin Fit P4's'
		TLorentzVector locBeamP4 = dComboBeamWrapper->Get_P4();
		TLorentzVector locPiPlusP4 = dPiPlusWrapper->Get_P4();
		TLorentzVector locPiMinusP4 = dPiMinusWrapper->Get_P4();
		TLorentzVector locProton1P4 = dProton1Wrapper->Get_P4();
		TLorentzVector locProton2P4 = dProton2Wrapper->Get_P4();

		// Get Measured P4's:
		TLorentzVector locBeamP4_Measured = dComboBeamWrapper->Get_P4_Measured();
		TLorentzVector locPiPlusP4_Measured = dPiPlusWrapper->Get_P4_Measured();
		TLorentzVector locPiMinusP4_Measured = dPiMinusWrapper->Get_P4_Measured();
		TLorentzVector locProton1P4_Measured = dProton1Wrapper->Get_P4_Measured();
		TLorentzVector locProton2P4_Measured = dProton2Wrapper->Get_P4_Measured();

		//GET COMBO RF TIMING INFO
		TLorentzVector    locBeamX4_Measured = dComboBeamWrapper->Get_X4_Measured();
		Double_t          locBunchPeriod = dAnalysisUtilities.Get_BeamBunchPeriod(Get_RunNumber());
		Double_t          locDeltaT_RF = dAnalysisUtilities.Get_DeltaT_RF(Get_RunNumber(), locBeamX4_Measured, dComboWrapper);
		Int_t             locRelBeamBucket = dAnalysisUtilities.Get_RelativeBeamBucket(Get_RunNumber(), locBeamX4_Measured, dComboWrapper); // 0 for in-time events, non-zero integer for out-of-time photons
		Int_t             locNumOutOfTimeBunchesInTree = 4; //YOU need to specify this number (on a single side, so that total number out-of-time bunches accepted is 2 times this number for left + right bunches)
		Bool_t            locSkipNearestOutOfTimeBunch = true; // True: skip events from nearest out-of-time bunch on either side (recommended).
		Int_t             locNumOutOfTimeBunchesToUse = locSkipNearestOutOfTimeBunch ? locNumOutOfTimeBunchesInTree-1:locNumOutOfTimeBunchesInTree;
		Double_t          locAccidentalScalingFactor = dAnalysisUtilities.Get_AccidentalScalingFactor(Get_RunNumber(), locBeamP4.E(), dIsMC); // Ideal value would be 1, but deviations require added factor, which is different for data and MC.
		Double_t          locAccidentalScalingFactorError = dAnalysisUtilities.Get_AccidentalScalingFactorError(Get_RunNumber(), locBeamP4.E()); // Ideal value would be 1, but deviations observed, need added factor.
		Double_t          locHistAccidWeightFactor = locRelBeamBucket==0 ? 1 : -locAccidentalScalingFactor/(2*locNumOutOfTimeBunchesToUse) ; // Weight by 1 for in-time events, ScalingFactor*(1/NBunches) for out-of-time
		if(locSkipNearestOutOfTimeBunch && abs(locRelBeamBucket)==1) {
		 	dComboWrapper->Set_IsComboCut(true);
		 	continue;
		 }    // Skip nearest out-of-time bunch: tails of in-time distribution also leak in


		// Combine 4-vectors
		TLorentzVector locMissingP4_Measured = locBeamP4_Measured + dTargetP4;
		locMissingP4_Measured -= locPiPlusP4_Measured + locPiMinusP4_Measured + locProton1P4_Measured + locProton2P4_Measured;

		/******************************************** EXECUTE ANALYSIS ACTIONS *******************************************/

		// Loop through the analysis actions, executing them in order for the active particle combo
		dAnalyzeCutActions->Perform_Action(); // Must be executed before Execute_Actions()
		if(!Execute_Actions()) //if the active combo fails a cut, IsComboCutFlag automatically set
			continue;

		//BEAM ENERGY
		if(locUsedSoFar_BeamEnergy.find(locBeamID) == locUsedSoFar_BeamEnergy.end())
		{
			//dHist_BeamEnergy->Fill(locBeamP4.E()); // Fills in-time and out-of-time beam photon combos
			dHist_BeamEnergy->Fill(locBeamP4.E(),locHistAccidWeightFactor); // Alternate version with accidental subtraction
			locUsedSoFar_BeamEnergy.insert(locBeamID);
		}

		//MISSING MASS SQUARED

		//Missing Mass Squared
		double locMissingMassSquared = locMissingP4_Measured.M2();

		map<Particle_t, set<Int_t> > locUsedThisCombo_MissingMass;
		locUsedThisCombo_MissingMass[Unknown].insert(locBeamID); //beam
		locUsedThisCombo_MissingMass[PiPlus].insert(locPiPlusTrackID);
		locUsedThisCombo_MissingMass[PiMinus].insert(locPiMinusTrackID);
		locUsedThisCombo_MissingMass[Proton].insert(locProton1TrackID);
		locUsedThisCombo_MissingMass[Proton].insert(locProton2TrackID);

		//compare to what's been used so far
		if(locUsedSoFar_MissingMass.find(locUsedThisCombo_MissingMass) == locUsedSoFar_MissingMass.end())
		{
			//unique missing mass combo: histogram it, and register this combo of particles
			//dHist_MissingMassSquared->Fill(locMissingMassSquared); // Fills in-time and out-of-time beam photon combos
			dHist_MissingMassSquared->Fill(locMissingMassSquared,locHistAccidWeightFactor); // Alternate version with accidental subtraction
			locUsedSoFar_MissingMass.insert(locUsedThisCombo_MissingMass);
		}

		//FILL ACCIDENTAL WEIGHT
		dFlatTreeInterface->Fill_Fundamental<Double_t>("accidweight",locHistAccidWeightFactor);
		dFlatTreeInterface->Fill_Fundamental<Double_t>("RF_time",locDeltaT_RF);
        NumberOfProtons.insert(locProton1TrackID+locProton2TrackID);
		NumberOfPiPlus.insert(locPiPlusTrackID);
		NumberOfPiMinus.insert(locPiMinusTrackID);
		NumberOfBeam.insert(locBeamID);

		TLorentzVector locMyThrownBeam(0.,0.,0.,0.);
		TLorentzVector locMyThrownPiPlus(0.,0.,0.,0.);
		TLorentzVector locMyThrownPiMinus(0.,0.,0.,0.);
		TLorentzVector locMyThrownProton1(0.,0.,0.,0.);
		TLorentzVector locMyThrownProton2(0.,0.,0.,0.);

		// GET THROWN P4
        TLorentzVector locBeamP4_Thrown, locPiMinusP4_Thrown, locMissingP4_Thrown;
        if(dThrownBeam != NULL)
            locBeamP4_Thrown = dThrownBeam->Get_P4();
            //Loop over throwns
            bool firstProton = true;
            for(UInt_t loc_i = 0; loc_i < Get_NumThrown(); ++loc_i)
            {
		    //Set branch array indices corresponding to this particle
		    dThrownWrapper->Set_ArrayIndex(loc_i);
		    switch(dThrownWrapper->Get_PID())
		      {
		      case PiPlus:
								locMyThrownPiPlus = dThrownWrapper->Get_P4();
								break;
		      case PiMinus:
								locMyThrownPiMinus = dThrownWrapper->Get_P4();
								break;
		      case Proton:
								if (firstProton)
						          {
									locMyThrownProton1 = dThrownWrapper->Get_P4();
									firstProton = false;
									}
									else
									{
									locMyThrownProton2 = dThrownWrapper->Get_P4();
									}
									break;
		      default:
								break;
		      }
            }

		if (locMyThrownProton1.T() < locMyThrownProton2.T())
		  {
		    TLorentzVector tmp = locMyThrownProton1;
		    locMyThrownProton1 = locMyThrownProton2;
		    locMyThrownProton2 = tmp;
				}
        locMissingP4_Thrown = locMyThrownPiPlus + locMyThrownPiMinus + locMyThrownProton2+ locMyThrownProton1 - locBeamP4_Thrown;

        //FILL THROWN FLAT TREE BRANCHES
        dFlatTreeInterface->Fill_TObject<TLorentzVector>("thrownBeam", locBeamP4_Thrown);
		dFlatTreeInterface->Fill_TObject<TLorentzVector>("p4_pip_thrown", locMyThrownPiPlus);
		dFlatTreeInterface->Fill_TObject<TLorentzVector>("thrownPiMinus", locMyThrownPiMinus);
		dFlatTreeInterface->Fill_TObject<TLorentzVector>("thrownProton1", locMyThrownProton1);
		dFlatTreeInterface->Fill_TObject<TLorentzVector>("thrownProton2", locMyThrownProton2);

		//FILL FLAT TREE
		Fill_FlatTree(); //for the active combo
		//end of combo loop

		if(!dComboWrapper->Get_IsComboCut())
            NumComboSurvived_weighted += locHistAccidWeightFactor;
			NumComboSurvived_after += 1;
            dHist_RFTiming->Fill(locDeltaT_RF);
		}

	//FILL HISTOGRAMS: Num combos / events surviving actions
	Fill_NumCombosSurvivedHists();
	dHist_CombosperEvent_before->Fill(Get_NumCombos());
	dHist_CombosperEvent_after->Fill(NumComboSurvived_after);

    dHist_ProtonNumber->Fill( NumberOfProtons.size() );
	dHist_PipNumber->Fill( NumberOfPiPlus.size() );
	dHist_PimNumber->Fill( NumberOfPiMinus.size() );
	dHist_BeamNumber->Fill( NumberOfBeam.size() );

	return kTRUE;
}

void DS_2p_v2::Finalize(void)
{
	//CALL THIS LAST
	DSelector::Finalize(); //Saves results to the output file
}
