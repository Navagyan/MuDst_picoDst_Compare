#include <iostream>
#include "TFile.h"
#include "TNtuple.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"

class StMuDstMaker;
class StMuDebug;
class StSpinDbMaker;
class StChain;
class StMaker;

// StMaker *spinDbMaker;
StMuDstMaker *maker;
// StSpinDbMaker* spDbMaker = dynamic_cast<StSpinDbMaker*>(spinDbMaker);

// void run17pp510MuDst_P(const char* list, const char* oFile, const char* jobid)
void run17pp510MuDst_GP(const char *list, const char *oFile) // interactive mode
{
  // char *filePath="/home/starlib/home/starreco/reco/pp500_production_2011/ReversedFullField/P11id/2011/043/12043045/st_physics_adc_12043045_raw_1510001.MuDst.root";
  // char * fout = "run11pp500.root";
  //  char *filePath="/star/data46/reco/productionMinBias/ReversedFullField/P05ia/2004/024/st_physics_5024*.MuDst.root";
  // char * fout = "Au200_xxx.root";

  gROOT->LoadMacro("$STAR/StRoot/StMuDSTMaker/COMMON/macros/loadSharedLibraries.C");
  loadSharedLibraries();
  gSystem->Load("StSpinDbMaker");
  gSystem->Load("StDbBroker");
  gSystem->Load("St_db_Maker");

  // some definitions
  // Float_t->F, Int_t->I,Double_t->D, UShort_t ->s,Short_t ->S
  // Define in /StRoot/StMuDSTMaker/COMMON/StMuTrack.h
  const int fMaxHit = 3000;

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
  //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ Tree Branch Declearation @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@

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

  cout << "OutPut File name is : " << oFile << endl;
  //  char file2[512]="";char krappy[256]="valami";

  chain = new StChain("StChain");
  chain->SetDebug(0);

  // StMuDebug::setLevel(0);  // switch of some debug output

  char theFilter[80];
  sprintf(theFilter, ".MuDst.root:MuDst.root");
  maker = new StMuDstMaker(0, 0, "", list, theFilter, 1000); // set up maker in read mode

  St_db_Maker *stDb = new St_db_Maker("StarDb", "MySQL:StarDb");
  StSpinDbMaker *spindb = new StSpinDbMaker;
  // open database connection for spin configuration
  const char *database = "mysql://db04.star.bnl.gov:3416/RunLog?timeout=60";
  const char *user = "nghimire";
  const char *pass = "";
  TMySQLServer *mysql = TMySQLServer::Connect(database, user, pass);

  float dca;
  int blue = 1;
  Int_t i = 0;

  chain->Init();

  // while(!maker->Make())
  while (!chain->Make())
  {

    StMuDst *mu = maker->muDst();
    StMuEvent *ev = maker->muDst()->event();
    if (!ev)
      continue;
    StEventInfo &evInfo = ev->eventInfo();
    // Adding ranking cut=============
    StMuPrimaryVertex *vertex = mu->primaryVertex();
    if (!vertex)
      continue;
    Float_t ranking = vertex->ranking();
    if (ranking < 1e6)
      continue;
    // Adding ranking cut=============
    unsigned int fevTime = evInfo.time();
    ;
    StThreeVectorF vertexPos = ev->primaryVertexPosition();
    if (fabs(vertexPos.x()) > 1. || fabs(vertexPos.y()) > 1.)
      continue;
    Int_t bx48 = ev->l0Trigger().bunchCrossingId();
    fspinconfig = spindb->spin8usingBX48(bx48);
    if (fspinconfig != 51 && fspinconfig != 53 && fspinconfig != 83 && fspinconfig != 85)
      continue;

    for (int trig = 0; trig < 34; trig++)
    {
      if ((ev->triggerIdCollection().nominal().isTrigger(trigid[trig])))
        int ftrigger = trigid[trig];
    }
    if (ftrigger == 0)
      continue;
    // cout << ftrigger << "  ftrigger  "<< endl;
    int frunId = ev->runId();
    StRunInfo &runInfo = ev->runInfo();
    fill = (int)(runInfo.beamFillNumber(blue));
    int ffillNum = fill;
    int frunNum = ev->runNumber();
    int fevtNum = ev->eventNumber();
    fVZ = vertexPos.z();

    Double_t fvzVpd1 = mu->btofHeader()->vpdVz();
    if (fvzVpd1 != -999)
    {
      fvzVpd = mu->btofHeader()->vpdVz();
      // cout << fvzVpd << "  fvzVpd " << endl;
    }

    int ntrk = mu->primaryTracks()->GetEntries();
    fTrackCounter = 0;
    for (int j = 0; j < ntrk; j++)
    {
      StMuTrack *track = mu->primaryTracks(j);
      assert(track);
      // can't pass the argument on the globaTrack calling from track as well from mu
      // const StMuTrack *gTrk = mu->globalTrack(j);
      // const StMuTrack *gTrk = track->globalTrack(j);
      StMuTrack *gTrk = track->globalTrack();
      // if(!gTrk) continue;
      if (!gTrk)
      {
        gTrk = track;
      }

      //	  if(track->flag() < 0) continue;
      //	  if (fabs(track->eta())<4.0 && track->nHitsFit()>5 && fabs(track->dcaGlobal().mag())< 3.)
      {
        fpT[fTrackCounter] = track->p().perp();
        fp[fTrackCounter] = track->p().mag();
        feta[fTrackCounter] = track->eta();
        fphi[fTrackCounter] = track->phi();
        fnSigmaPion[fTrackCounter] = track->nSigmaPion();
        fnSigmaKaon[fTrackCounter] = track->nSigmaKaon();
        fnSigmaProton[fTrackCounter] = track->nSigmaProton();
        fnSigmaElectron[fTrackCounter] = track->nSigmaElectron();
        fcharge[fTrackCounter] = track->charge();
        fdEdx[fTrackCounter] = ((track->dEdx()) * pow(10, 6));
        fdca[fTrackCounter] = track->dcaGlobal().mag();
        // ffitPts[fTrackCounter]     =  track->nHitsFit();
        // fhitsdedx[fTrackCounter]     = track->nHitsDedx();
        // ffitPtsPoss[fTrackCounter]     = track->nHitsPoss();
        ffitPts[fTrackCounter] = gTrk->nHitsFit();
        fhitsdedx[fTrackCounter] = gTrk->nHitsDedx();
        ffitPtsPoss[fTrackCounter] = gTrk->nHitsPoss();

        // cout << track->nHitsFit() << " nHitsFit form Primary "<< gTrk->nHitsFit()<< " nHitsFit form Global"<< endl;
        // cout << track->nHitsDedx() << " nHitsFitDedx form Primary "<< gTrk->nHitsDedx()<< " nHitsFitDedx form Global"<< endl;
        // if ((track->nHitsPoss() - gTrk->nHitsPoss()) != 0)
        //{
        //  int diff = track->nHitsPoss() - gTrk->nHitsPoss();
        // cout << diff << "\t Difference in nHitsPoss\t" << endl;
        // cout << track->nHitsPoss() << " nHitsFitPoss form Primary " << gTrk->nHitsPoss() << " nHitsFitPoss form Global" << endl;
        //}
        Double_t beta = track->btofPidTraits().beta();
        if (beta != -999)
        {

          fBetaToF[fTrackCounter] = track->btofPidTraits().beta();
        }
        fTrackCounter++;
      } // If condition close
    }   // for track loop close
    fmaxpar = fTrackCounter;
    if (fmaxpar > 1)
      ftree->Fill();
    ftrigger = 0;
  } // event loop
  fout->cd();
  ftree->Write();
  fout->Close();
  cout << "done" << endl;
  flush(cout);
  mysql->Close();

  cout << "-----------Time to Close the Shop---------------" << endl;

} // run17pp510MuDst_P function
