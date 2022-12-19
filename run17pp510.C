#include <iostream>
#include "TFile.h"
#include "TNtuple.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TTree.h"
#include <TSystem>

class StPicoDstMaker;
class StSpinDbMaker;
class StChain;
class StMaker;
class StPicoDstMaker;
class StPicoDst;
class StPicoEvent;
class St_db_Maker;

StPicoDstMaker *maker;

int n = 0;
// void run17pp510(const char* list, const char* oFile, const char* jobid)
void run17pp510(const char *list, const char *oFile) // interactive mode
{
	gROOT->LoadMacro("$STAR/StRoot/StMuDSTMaker/COMMON/macros/loadSharedLibraries.C");
	loadSharedLibraries();
	gSystem->Load("StPicoEvent");
	gSystem->Load("StPicoDstMaker");
	gSystem->Load("StSpinDbMaker");
	gSystem->Load("StDbBroker");
	gSystem->Load("St_db_Maker");
	// Float_t->F, Int_t->I,Double_t->D, UShort_t ->s,Short_t ->S
	// Define in /StRoot/StMuDSTMaker/COMMON/StMuTrack.h
	const int fMaxHit = 3000;
	Int_t ffillNum;
	Int_t fevtNum;
	Int_t frunNum;
	Int_t fspinconfig;
	// Int_t ftrigger;
	vector<int> ftrigger;
	Int_t fmaxpar;
	Int_t fTrackCounter;
	Double_t fVZ;
	Double_t fvzVpd;
	Double_t fpT[fMaxHit];
	Double_t fp[fMaxHit];
	Double_t feta[fMaxHit];
	Double_t fphi[fMaxHit];
	Double_t fnSigmaPion[fMaxHit];
	Double_t fnSigmaKaon[fMaxHit];
	Double_t fnSigmaProton[fMaxHit];
	Double_t fnSigmaElectron[fMaxHit];
	Short_t fcharge[fMaxHit];
	Double_t fdEdx[fMaxHit];
	Double_t fdca[fMaxHit];
	UShort_t ffitPts[fMaxHit];
	UShort_t ffitPtsPoss[fMaxHit];
	UShort_t fhitsdedx[fMaxHit];
	Double_t fBetaToF[fMaxHit];
	unsigned int fevTime;
	unsigned int frunTime;
	Int_t triggerIds[34];
	Int_t fMaxTrig;
	Int_t bunchId;
	//======================= Tree Branch Declearation ===========================
	TFile *fout = new TFile(oFile, "recreate");
	TTree *ftree = new TTree("ftree", "dihadron ");

	ftree->Branch("fevtNum", &fevtNum, "fevtNum/I");
	ftree->Branch("ffillNum", &ffillNum, "ffillNum/I");
	ftree->Branch("frunNum", &frunNum, "frunNum/I");
	ftree->Branch("fspinconfig", &fspinconfig, "fspinconfig/I");
	// ftree->Branch("ftrigger", &ftrigger, "ftrigger/I");
	ftree->Branch("ftrigger", &ftrigger);
	ftree->Branch("fmaxpar", &fmaxpar, "fmaxpar/I");
	ftree->Branch("fVZ", &fVZ, "fVZ/D");
	ftree->Branch("fvzVpd", &fvzVpd, "fvzVpd/D");
	ftree->Branch("fpT", fpT, "fpT[fmaxpar]/D");
	ftree->Branch("fp", fp, "fp[fmaxpar]/D");
	ftree->Branch("feta", feta, "feta[fmaxpar]/D");
	ftree->Branch("fphi", fphi, "fphi[fmaxpar]/D");
	ftree->Branch("fcharge", fcharge, "fcharge[fmaxpar]/S");
	ftree->Branch("fnSigmaPion", fnSigmaPion, "fnSigmaPion[fmaxpar]/D");
	ftree->Branch("fnSigmaKaon", fnSigmaKaon, "fnSigmaKaon[fmaxpar]/D");
	ftree->Branch("fnSigmaProton", fnSigmaProton, "fnSigmaProton[fmaxpar]/D");
	ftree->Branch("fnSigmaElectron", fnSigmaElectron, "fnSigmaElectron[fmaxpar]/D");
	ftree->Branch("fdEdx", fdEdx, "fdEdx[fmaxpar]/D");
	ftree->Branch("fdca", fdca, "fdca[fmaxpar]/D");
	ftree->Branch("ffitPts", ffitPts, "ffitPts[fmaxpar]/s");
	ftree->Branch("ffitPtsPoss", ffitPtsPoss, "ffitPtsPoss[fmaxpar]/s");
	ftree->Branch("fhitsdedx", fhitsdedx, "fhitsdedx[fmaxpar]/s");
	ftree->Branch("fBetaToF", fBetaToF, "fBetaToF[fmaxpar]/D");
	ftree->Branch("fevTime", &fevTime, "fevTime/I");

	cout << "----------------OUTPUT File name is------------- : " << oFile << endl;
	// char file2[512]= "" ; char krappy[216]= "valami";
	chain = new StChain("StChain");
	chain->SetDebug(0);

	StPicoDstMaker *maker = new StPicoDstMaker(2, list, "picoDst");

	St_db_Maker *stDb = new St_db_Maker("StarDb", "MySQL:StarDb");
	StSpinDbMaker *spindb = new StSpinDbMaker;

	//=====================open database connection for spin configuration===================

	const char *database = "mysql://db04.star.bnl.gov:3416/RunLog?timeout=60";
	const char *user = "nghimire";
	const char *pass = "";
	TMySQLServer *mysql = TMySQLServer::Connect(database, user, pass);

	float dca;
	Int_t i = 0;

	chain->Init();
	Int_t nevents = maker->chain()->GetEntries();
	cout << nevents << "-------nevents-----------" << endl;
	// while (!maker->Make())
	while (!chain->Make())
	{
		StPicoDst *pico = maker->picoDst();
		StPicoEvent *ev = pico->event();
		if (!ev)
			continue;
		// Adding ranking cut=============
		Float_t ranking = ev->ranking();
		if (ranking < 1e6)
			continue;
		// Adding ranking cut=============
		unsigned int fevTime = ev->time();
		if (fabs(ev->primaryVertex().X() > 1. || fabs(ev->primaryVertex().Y() > 1.)))
			continue;
		Int_t bx48 = ev->bunchId();
		fspinconfig = spindb->spin8usingBX48(bx48);
		if (fspinconfig != 51 && fspinconfig != 53 && fspinconfig != 83 && fspinconfig != 85)
			continue;
		Int_t frunId = ev->runId();
		Int_t ffillNum = ev->fillId();
		int frunNum = ev->runId();
		int fevtNum = ev->eventId();
		Double_t fVZ = ev->primaryVertex().Z();
		Double_t fvzVpd = -999; // This step is crucial, not using this would give largely increased weired distribution around zero.
		fvzVpd = ev->vzVpd();
		vector<unsigned int> TriggerIds = ev->triggerIds(); // Had trouble when define Vector TriggerIds in the top and try to run the code so I declare it here.
		// cout << TriggerIds.size()<< " Size of Trigger id "<< endl;
		int fTrigCounter = 0;
		ftrigger.clear();
		for (int i = 0; i < TriggerIds.size(); i++)
		{
			triggerIds[fTrigCounter] = TriggerIds.at(i);
			ftrigger.push_back(TriggerIds.at(i));
			// cout << ftrigger.at(i) << " TriggerId"<< endl;
			fTrigCounter++;
		}
		fMaxTrig = fTrigCounter;

		int ntrk = pico->numberOfTracks();
		fTrackCounter = 0;
		for (int j = 0; j < ntrk; j++)
		{
			StPicoEvent *ev = maker->picoDst()->event();
			StPicoTrack *track = pico->track(j);
			if (!track->isPrimary())
				continue;
			n = n + 1;
			float Eta = track->pMom().Eta();
			Double_t Vx = ev->primaryVertex().X();
			Double_t Vy = ev->primaryVertex().Y();
			Double_t Vz = ev->primaryVertex().Z();

			float trackDCA = track->gDCA(Vx, Vy, Vz);

			if (fabs(Eta) < 1.5 && track->nHitsFit() > 12 && fabs(trackDCA) < 3.)
			{
				fpT[fTrackCounter] = track->pPt();
				fp[fTrackCounter] = track->pMom().Mag();
				feta[fTrackCounter] = track->pMom().Eta();
				fphi[fTrackCounter] = track->pMom().Phi();
				fnSigmaPion[fTrackCounter] = track->nSigmaPion();
				fnSigmaKaon[fTrackCounter] = track->nSigmaKaon();
				fnSigmaProton[fTrackCounter] = track->nSigmaProton();
				fnSigmaElectron[fTrackCounter] = track->nSigmaElectron();
				fcharge[fTrackCounter] = track->charge();
				fdEdx[fTrackCounter] = track->dEdx();
				fdca[fTrackCounter] = trackDCA;
				ffitPts[fTrackCounter] = track->nHitsFit();
				fhitsdedx[fTrackCounter] = track->nHitsDedx();
				ffitPtsPoss[fTrackCounter] = track->nHitsPoss();
				float trackBeta = -999.;
				int trackTofIndex = track->bTofPidTraitsIndex();
				if (trackTofIndex >= 0)
					fBetaToF[fTrackCounter] = pico->btofPidTraits(trackTofIndex)->btofBeta();
				fTrackCounter++;

			} // if statement close

		} // for loop close(Track)

		fmaxpar = fTrackCounter;
		// cout << fmaxpar << "fmaxpar"<< endl;
		if (fmaxpar > 1)
			ftree->Fill();
	} // while loop  loop close // event loop
	fout->cd();
	ftree->Write();
	fout->Close();
	cout << "done" << endl;
	flush(cout);
	mysql->Close();
	cout << n << "Total track with isPrimary() working" << endl;
	cout << "-----------Time to Close the Shop---------------" << endl;
} // run17pp510 function
