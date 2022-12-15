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

	const int fMaxHit = 30000;
	Int_t ffillNum;
	Int_t fevtNum;
	Int_t frunNum;
	Int_t fspinconfig;
	Int_t ftrigger;
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

	TFile *fout = new TFile(oFile, "recreate");
	TTree *ftree = new TTree("ftree", "dihadron ");
	ftree->Branch("fevtNum", &fevtNum, "fevtNum/I");
	ftree->Branch("ffillNum", &ffillNum, "ffillNum/I");
	ftree->Branch("frunNum", &frunNum, "frunNum/I");
	ftree->Branch("fspinconfig", &fspinconfig, "fspinconfig/I");
	ftree->Branch("ftrigger", &ftrigger, "ftrigger/I");
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
	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ Trigger Ids @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	int trigid[34];
	trigid[0] = 16;
	trigid[1] = 18;
	trigid[2] = 20;
	trigid[3] = 21;
	trigid[4] = 22;
	trigid[5] = 23;
	trigid[6] = 24;
	trigid[7] = 29;
	trigid[8] = 30;
	trigid[9] = 31;
	trigid[10] = 32;
	trigid[11] = 34;
	trigid[12] = 35;
	trigid[13] = 55;
	trigid[14] = 56;
	trigid[15] = 57;
	trigid[16] = 570001;
	trigid[17] = 570004;
	trigid[18] = 570005;
	trigid[19] = 570006;
	trigid[20] = 570007;
	trigid[21] = 570008;
	trigid[22] = 570015;
	trigid[23] = 570201;
	trigid[24] = 570203;
	trigid[25] = 570204;
	trigid[26] = 570205;
	trigid[27] = 570209;
	trigid[28] = 570214;
	trigid[29] = 570215;
	trigid[30] = 570401;
	trigid[31] = 570402;
	trigid[32] = 570403;
	trigid[33] = 570204;

	cout << "----------------OUTPUT File name is------------- : " << oFile << endl;
	// char file2[512]= "" ; char krappy[216]= "valami";

	chain = new StChain("StChain");
	chain->SetDebug(0);

	char theFilter[80];
	sprintf(theFilter, ".PicoDst.root:PicoDst.root");

	StPicoDstMaker *maker = new StPicoDstMaker(2, list, "picoDst");

	St_db_Maker *stDb = new St_db_Maker("StarDb", "MySQL:StarDb");
	StSpinDbMaker *spindb = new StSpinDbMaker;

	// Int_t nevents = maker->chain()->GetEntries();

	//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ Open DataBase Connection for Spin Configuration @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

	const char *database = "mysql://db04.star.bnl.gov:3416/RunLog?timeout=60";
	const char *user = "nghimire";
	const char *pass = "";
	TMySQLServer *mysql = TMySQLServer::Connect(database, user, pass);

	float dca;
	Int_t i = 0;

	chain->Init();
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
		// if (!ev) continue;
		if (fabs(ev->primaryVertex().X() > 1. || fabs(ev->primaryVertex().Y() > 1.)))
			continue;
		Int_t bx48 = ev->bunchId();
		int fspinconfig = spindb->spin8usingBX48(bx48);
		if (fspinconfig != 51 && fspinconfig != 53 && fspinconfig != 83 && fspinconfig != 85)
			continue;
		for (int trig = 0; trig < 34; trig++)
		{
			if ((ev->isTrigger(trigid[trig])))
				int ftrigger = trigid[trig];
		} // diffrent in pico and Mudst format

		if (ftrigger == 0)
			continue;
		Int_t frunId = ev->runId();
		Int_t ffillNum = ev->fillId();
		int frunNum = ev->runId();
		int fevtNum = ev->eventId();
		Double_t fVZ = ev->primaryVertex().Z();
		Double_t fvzVpd1 = ev->vzVpd();
		if (fvzVpd1 != -999)
		{
			fvzVpd = ev->vzVpd();
			// cout << fvzVpd << "  fvzVpd " << endl;
		}

		int ntrk = pico->numberOfTracks();
		fTrackCounter = 0;
		for (int j = 0; j < ntrk; j++)
		{
			StPicoEvent *ev = maker->picoDst()->event();
			StPicoTrack *track = pico->track(j);
			if (!track->isPrimary())
				continue;
			// float Eta = track->pMom().Eta();
			n = n + 1;
			Double_t Vx = ev->primaryVertex().X();
			Double_t Vy = ev->primaryVertex().Y();
			Double_t Vz = ev->primaryVertex().Z();

			float trackDCA = track->gDCA(Vx, Vy, Vz);
			//	if (fabs(Eta)<4.0 && track->nHitsFit()>5 && fabs(trackDCA)<3.)
			//	{
			// if (track->pPt()>50) continue ;
			// if (track->pMom().Mag()>50) continue;

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

			//	}//if statement close

		} // for loop close(Track)

		fmaxpar = fTrackCounter;
		// cout << fmaxpar << "fmaxpar"<< endl;
		if (fmaxpar > 1)
			ftree->Fill();
		ftrigger = 0;
	} // while loop  loop close
	  // event loop
	fout->cd();
	ftree->Write();
	fout->Close();
	cout << "done" << endl;
	flush(cout);
	mysql->Close();
	cout << n << "Total track with isPrimary() working" << endl;
	cout << "-----------Time to Close the Shop---------------" << endl;
} // run17pp510 function
