#include "DS_2p.h"

void DS_2p::Init(TTree *locTree)
{
	//SET OUTPUT FILE NAME //can be overriden by user in PROOF
	dOutputFileName = ""; //"" for none
	dOutputTreeFileName = ""; //"" for none
	
    /******************* SIMULATION FLATTREES *********************/
    //dFlatTreeFileName = "flattree_gc12__protprot_AV18_inc_0bg.root"; //output flat tree (one combo per tree entry), "" for none
    //dFlatTreeFileName = "flattree_gc12__protprot_AV4_inc_0bg.root";
    //dFlatTreeFileName = "flattree_gc12__protprot_N2LO_inc_0bg.root";
    
    /******************* DATA FLATTREES *********************/
     dFlatTreeFileName = "flattree_C12_2p_data_inc.root";
    
    
    dFlatTreeName = ""; //if blank, default name will be chosen
	dSaveDefaultFlatBranches = true; // False: don't save default branches, reduce disk footprint.
	
    //INITIALIZE THE TREE INTERFACE AND WRAPPERS
	bool locInitializedPriorFlag = dInitializedFlag; //save whether have been initialized previously
	DSelector::Init(locTree); //This must be called to initialize wrappers for each new TTree
	//gDirectory now points to the output file with name dOutputFileName (if any)
	if(locInitializedPriorFlag)
		return; //have already created histograms, etc. below: exit
	Get_ComboWrappers();
	dPreviousRunNumber = 0;

    
	//INITIALIZATION: ANALYSIS ACTIONS *********************************************************************************************

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
        dAnalyzeCutActions = new DHistogramAction_AnalyzeCutActions( dAnalysisActions, dComboWrapper, true, 0, MyRho, 1000, 0.0, 4.0, "Rho_Mass" );

	//INITIALIZE ACTIONS
	Initialize_Actions();
	dAnalyzeCutActions->Initialize(); 
    
    ///MANUAL HISTOGRAMS:
        dHist_MissingMassSquared = new TH1I("MissingMassSquared", ";Missing Mass Squared (GeV/c^{2})^{2}", 1000, -5, 5);
        dHist_MissingEnergy = new TH1I("MissingEnergy",";Missing Energy (GeV)", 1000, -1,3);
        dHist_BeamEnergy = new TH1I("BeamEnergy", ";Beam Energy (GeV)", 600, 0.0, 12.0);
             
        gDirectory->mkdir( "Combos & Event" )->cd();
        dHist_CombosperEvent_before = new TH1I("Combos per Event Before", "Combos per Event Before; Combos; Events", 10, -0.5, 9.5 );
        dHist_CombosperEvent_after = new TH1I("Combos per Event After", "Combos per Event After; Combos; Events", 10, -0.5, 9.5 );
        gDirectory->cd( ".." );	
    
        dHist_RFTiming = new TH1F("RF timing plot", "RF Timing plot;x-axis; y-axis", 80, -30, 30);
    
    	gDirectory->mkdir( "Number_of_Particles" )->cd();
        dHist_ProtonNumber = new TH1D( "ProtonNumber", ";Number of Protons Candidates in an Event", 10, 0, 10);
        dHist_PipNumber = new TH1D( "PipNumber", ";Number of #pi^{+} Candidates in an Event", 10, 0, 10);
        dHist_PimNumber = new TH1D( "PimNumber", ";Number of #pi^{-} Candidates in an Event", 10, 0, 10);
        dHist_BeamNumber = new TH1D( "BeamNumber", ";Number of Beam Candidates in an Event", 10, 0, 10);
        gDirectory->cd( ".." );
    
	/************************** CUSTOM OUTPUT BRANCHES - FLAT TREE *************************/

	//CREATE ACCIDENTAL WEIGHT BRANCH
	 dFlatTreeInterface->Create_Branch_Fundamental<Double_t>("accidweight");
    
    dFlatTreeInterface->Create_Branch_NoSplitTObject<TLorentzVector>("thrownBeam");
    dFlatTreeInterface->Create_Branch_NoSplitTObject<TLorentzVector>("thrownPiPlus");
    dFlatTreeInterface->Create_Branch_NoSplitTObject<TLorentzVector>("thrownPiMinus");
    dFlatTreeInterface->Create_Branch_NoSplitTObject<TLorentzVector>("thrownProton1");
    dFlatTreeInterface->Create_Branch_NoSplitTObject<TLorentzVector>("thrownProton2");

    dFlatTreeInterface->Create_Branch_Fundamental<Double_t>("thrownS");
    dFlatTreeInterface->Create_Branch_Fundamental<Double_t>("thrownT");
    dFlatTreeInterface->Create_Branch_Fundamental<Double_t>("thrownU");
	/************************************* CHOOSE BRANCHES TO READ ************************************/

	//TO SAVE PROCESSING TIME
		//If you know you don't need all of the branches/data, but just a subset of it, you can speed things up
		//By default, for each event, the data is retrieved for all branches
		//If you know you only need data for some branches, you can skip grabbing data from the branches you don't need
		//Do this by doing something similar to the commented code below

	//dTreeInterface->Clear_GetEntryBranches(); //now get none
	//dTreeInterface->Register_GetEntryBranch("Proton__P4"); //manually set the branches you want

	/************************************** DETERMINE IF ANALYZING SIMULATED DATA *************************************/

	dIsMC = (dTreeInterface->Get_Branch("MCWeight") != NULL);

}

Bool_t DS_2p::Process(Long64_t locEntry)
{
	//CALL THIS FIRST
	DSelector::Process(locEntry); //Gets the data from the tree for the entry
	cout << "RUN " << Get_RunNumber() << ", EVENT " << Get_EventNumber() << endl;

	/******************************************** GET POLARIZATION ORIENTATION ******************************************/

	UInt_t locRunNumber = Get_RunNumber();
	if(locRunNumber != dPreviousRunNumber)
	{
		dIsPolarizedFlag = dAnalysisUtilities.Get_IsPolarizedBeam(locRunNumber, dIsPARAFlag);
		dPreviousRunNumber = locRunNumber;
	}

	//SETUP UNIQUENESS TRACKING

	//For any actions that you are executing manually, be sure to call Reset_NewEvent() on them here
	Reset_Actions_NewEvent();
	dAnalyzeCutActions->Reset_NewEvent(); // manual action, must call Reset_NewEvent()

    //EXAMPLE 1: Particle-specific info:
	set<Int_t> locUsedSoFar_BeamEnergy; //Int_t: Unique ID for beam particles. set: easy to use, fast to search

	//EXAMPLE 2: Combo-specific info:
		//In general: Could have multiple particles with the same PID: Use a set of Int_t's
		//In general: Multiple PIDs, so multiple sets: Contain within a map
		//Multiple combos: Contain maps within a set (easier, faster to search)
	set<map<Particle_t, set<Int_t> > > locUsedSoFar_MissingMass;
        set<Int_t> NumberOfProtons;
        set<Int_t> NumberOfPiPlus;
        set<Int_t> NumberOfPiMinus;
        set<Int_t> NumberOfBeam;

	//INSERT USER ANALYSIS UNIQUENESS TRACKING HERE

	/**************************************** EXAMPLE: FILL CUSTOM OUTPUT BRANCHES **************************************/

	/*
	Int_t locMyInt = 7;
	dTreeInterface->Fill_Fundamental<Int_t>("my_int", locMyInt);

	TLorentzVector locMyP4(4.0, 3.0, 2.0, 1.0);
	dTreeInterface->Fill_TObject<TLorentzVector>("my_p4", locMyP4);

	for(int loc_i = 0; loc_i < locMyInt; ++loc_i)
		dTreeInterface->Fill_Fundamental<Int_t>("my_int_array", 3*loc_i, loc_i); //2nd argument = value, 3rd = array index
	*/

	/************************************************* LOOP OVER COMBOS *************************************************/

	int NumComboSurvived_after = 0;
	int NumComboSurvived_weighted = 0;	
	//Loop over combos
	for(UInt_t loc_i = 0; loc_i < Get_NumCombos(); ++loc_i)
	{
		dComboWrapper->Set_ComboIndex(loc_i); //Set branch array indices
		if(dComboWrapper->Get_IsComboCut()) // Checks if combo has been cut
			continue; // Combo has been cut previously

		//GET PARTICLE INDICES 
		Int_t locBeamID = dComboBeamWrapper->Get_BeamID();
		Int_t locPiPlusTrackID = dPiPlusWrapper->Get_TrackID();
		Int_t locPiMinusTrackID = dPiMinusWrapper->Get_TrackID();
		Int_t locProton1TrackID = dProton1Wrapper->Get_TrackID();
		Int_t locProton2TrackID = dProton2Wrapper->Get_TrackID();

		//GET FOUR-MOMENTUM 
		TLorentzVector locBeamP4 = dComboBeamWrapper->Get_P4();
		TLorentzVector locPiPlusP4 = dPiPlusWrapper->Get_P4();
		TLorentzVector locPiMinusP4 = dPiMinusWrapper->Get_P4();
		TLorentzVector locProton1P4 = dProton1Wrapper->Get_P4();
		TLorentzVector locProton2P4 = dProton2Wrapper->Get_P4();

		// Get Measured P4's
		TLorentzVector locBeamP4_Measured = dComboBeamWrapper->Get_P4_Measured();
		TLorentzVector locPiPlusP4_Measured = dPiPlusWrapper->Get_P4_Measured();
		TLorentzVector locPiMinusP4_Measured = dPiMinusWrapper->Get_P4_Measured();
		TLorentzVector locProton1P4_Measured = dProton1Wrapper->Get_P4_Measured();
		TLorentzVector locProton2P4_Measured = dProton2Wrapper->Get_P4_Measured();

		//GET COMBO RF TIMING INFO

		TLorentzVector locBeamX4_Measured = dComboBeamWrapper->Get_X4_Measured();
		Double_t locBunchPeriod = dAnalysisUtilities.Get_BeamBunchPeriod(Get_RunNumber());
		Double_t locDeltaT_RF = dAnalysisUtilities.Get_DeltaT_RF(Get_RunNumber(), locBeamX4_Measured, dComboWrapper);
		Int_t locRelBeamBucket = dAnalysisUtilities.Get_RelativeBeamBucket(Get_RunNumber(), locBeamX4_Measured, dComboWrapper); // 0 for in-time events, non-zero integer for out-of-time photons
		Int_t locNumOutOfTimeBunchesInTree = 4; //YOU need to specify this number (on a single side, so that total number out-of-time bunches accepted is 2 times this number for left + right bunches)
		Bool_t locSkipNearestOutOfTimeBunch = true; // True: skip events from nearest out-of-time bunch on either side (recommended).
		Int_t locNumOutOfTimeBunchesToUse = locSkipNearestOutOfTimeBunch ? locNumOutOfTimeBunchesInTree-1:locNumOutOfTimeBunchesInTree;
		Double_t locAccidentalScalingFactor = dAnalysisUtilities.Get_AccidentalScalingFactor(Get_RunNumber(), locBeamP4.E(), dIsMC); // Ideal value would be 1, but deviations require added factor, which is different for data and MC.
		Double_t locAccidentalScalingFactorError = dAnalysisUtilities.Get_AccidentalScalingFactorError(Get_RunNumber(), locBeamP4.E()); // Ideal value would be 1, but deviations observed, need added factor.
		Double_t locHistAccidWeightFactor = locRelBeamBucket==0 ? 1 : -locAccidentalScalingFactor/(2*locNumOutOfTimeBunchesToUse) ; // Weight by 1 for in-time events, ScalingFactor*(1/NBunches) for out-of-time
		if(locSkipNearestOutOfTimeBunch && abs(locRelBeamBucket)==1) { // Skip nearest out-of-time bunch: tails of in-time distribution also leak in
		 	dComboWrapper->Set_IsComboCut(true);
		 	continue;
		 }

		//COMBINE FOUR-MOMENTUM 
		TLorentzVector locMissingP4_Measured = locBeamP4_Measured + dTargetP4;
		locMissingP4_Measured -= locPiPlusP4_Measured + locPiMinusP4_Measured + locProton1P4_Measured + locProton2P4_Measured;

		/******************************************** EXECUTE ANALYSIS ACTIONS *******************************************/
        dAnalyzeCutActions->Perform_Action(); // Must be executed before Execute_Actions()
		if(!Execute_Actions()) //if the active combo fails a cut, IsComboCutFlag automatically set
			continue;

		//HISTOGRAM BEAM ENERGY
		if(locUsedSoFar_BeamEnergy.find(locBeamID) == locUsedSoFar_BeamEnergy.end())
		{
			//dHist_BeamEnergy->Fill(locBeamP4.E()); // Fills in-time and out-of-time beam photon combos
			dHist_BeamEnergy->Fill(locBeamP4.E(),locHistAccidWeightFactor); // Alternate version with accidental subtraction
			locUsedSoFar_BeamEnergy.insert(locBeamID);
		}

		//Missing Mass Squared
		double locMissingMassSquared = locMissingP4_Measured.M2();
		double locMissingEnergy = locMissingP4_Measured.E();

		//Uniqueness tracking: Build the map of particles used for the missing mass
		map<Particle_t, set<Int_t> > locUsedThisCombo_MissingMass;
		locUsedThisCombo_MissingMass[Unknown].insert(locBeamID); //beam
		locUsedThisCombo_MissingMass[PiPlus].insert(locPiPlusTrackID);
		locUsedThisCombo_MissingMass[PiMinus].insert(locPiMinusTrackID);
		locUsedThisCombo_MissingMass[Proton].insert(locProton1TrackID);
		locUsedThisCombo_MissingMass[Proton].insert(locProton2TrackID);

		//compare to what's been used so far
		if(locUsedSoFar_MissingMass.find(locUsedThisCombo_MissingMass) == locUsedSoFar_MissingMass.end())
		{
			//dHist_MissingMassSquared->Fill(locMissingMassSquared); // Fills in-time and out-of-time beam photon combos
			dHist_MissingMassSquared->Fill(locMissingMassSquared,locHistAccidWeightFactor); // Alternate version with accidental subtraction
			dHist_MissingEnergy->Fill(locMissingEnergy,locHistAccidWeightFactor);
			locUsedSoFar_MissingMass.insert(locUsedThisCombo_MissingMass);
		}

		//FILL ACCIDENTAL WEIGHT
		dFlatTreeInterface->Fill_Fundamental<Double_t>("accidweight",locHistAccidWeightFactor);

        NumberOfProtons.insert(locProton1TrackID+locProton2TrackID);
		NumberOfPiPlus.insert(locPiPlusTrackID);
		NumberOfPiMinus.insert(locPiMinusTrackID);
		NumberOfBeam.insert(locBeamID);

		TLorentzVector locMyThrownBeam(0.,0.,0.,0.);
		TLorentzVector locMyThrownPiPlus(0.,0.,0.,0.);
		TLorentzVector locMyThrownPiMinus(0.,0.,0.,0.);
		TLorentzVector locMyThrownProton1(0.,0.,0.,0.);
		TLorentzVector locMyThrownProton2(0.,0.,0.,0.);

		//Thrown beam: just use directly 	       
		if(dThrownBeam != NULL)
		  locMyThrownBeam = dThrownBeam->Get_P4();
		
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

		double locMyThrownS = (locMyThrownProton1 + locMyThrownPiPlus + locMyThrownPiMinus).M2();
		double locMyThrownT = (locMyThrownBeam - locMyThrownPiPlus - locMyThrownPiMinus).M2();
		double locMyThrownU = (locMyThrownBeam - locMyThrownProton1).M2();

		dFlatTreeInterface->Fill_TObject<TLorentzVector>("thrownBeam", locMyThrownBeam);
		dFlatTreeInterface->Fill_TObject<TLorentzVector>("thrownPiPlus", locMyThrownPiPlus);
		dFlatTreeInterface->Fill_TObject<TLorentzVector>("thrownPiMinus", locMyThrownPiMinus);
		dFlatTreeInterface->Fill_TObject<TLorentzVector>("thrownProton1", locMyThrownProton1);
		dFlatTreeInterface->Fill_TObject<TLorentzVector>("thrownProton2", locMyThrownProton2);

		dFlatTreeInterface->Fill_Fundamental<Double_t>("thrownS", locMyThrownS);
		dFlatTreeInterface->Fill_Fundamental<Double_t>("thrownT", locMyThrownT);
		dFlatTreeInterface->Fill_Fundamental<Double_t>("thrownU", locMyThrownU);

		//FILL FLAT TREE
		Fill_FlatTree(); //for the active combo
	// // end of combo loop
    
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
//END OF PROCESSING

void DS_2p::Finalize(void)
{
	//CALL THIS LAST
	DSelector::Finalize(); //Saves results to the output file
}
//END OF FINALIZATION