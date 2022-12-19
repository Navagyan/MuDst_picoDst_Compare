// void ReadTree_Data(const char *tree, const char *ofile,const char* jobid) //xml (or grid mode)
void ReadTree_Data(const char *tree = "/star/u/nghimire/GPFS/Embed_Run17_New/Data_RawTree_Test/AddedTree/RawDataTree_iff.root", const char *ofile = "ReadTree_Data_SL22b.root") // Interactive

{

    TChain *fChain = new TChain("ftree");
    fChain->Add(tree);
    TFile *outfile = new TFile(ofile, "recreate");
    cout << fChain->GetEntries() << endl;

    const int fMaxHit = 3000;
    int fmaxpar;
    double fVZ;
    double fvzVpd;

    double fpT[fMaxHit];
    double fp[fMaxHit];
    double feta[fMaxHit];
    double fphi[fMaxHit];
    double fdca[fMaxHit];

    Short_t fcharge[fMaxHit];

    Double_t fdEdx[fMaxHit];
    Double_t fnSigmaPion[fMaxHit];
    Double_t fnSigmaKaon[fMaxHit];
    Double_t fnSigmaProton[fMaxHit];
    Double_t fnSigmaElectron[fMaxHit];

    UShort_t ffitPts[fMaxHit];
    UShort_t ffitPtsPoss[fMaxHit];
    UShort_t fhitsdedx[fMaxHit];

    vector<int> *ftrigger;

    ofstream trigfile("TrigFile_Data.txt");
    fChain->SetBranchAddress("fmaxpar", &fmaxpar);

    fChain->SetBranchAddress("fVZ", &fVZ);
    fChain->SetBranchAddress("fvzVpd", &fvzVpd);

    fChain->SetBranchAddress("fpT", fpT);
    fChain->SetBranchAddress("fp", fp);
    fChain->SetBranchAddress("feta", feta);
    fChain->SetBranchAddress("fphi", fphi);
    fChain->SetBranchAddress("fdca", fdca);

    fChain->SetBranchAddress("fdEdx", fdEdx);
    fChain->SetBranchAddress("fnSigmaPion", fnSigmaPion);
    fChain->SetBranchAddress("fnSigmaKaon", fnSigmaKaon);
    fChain->SetBranchAddress("fnSigmaProton", fnSigmaProton);
    fChain->SetBranchAddress("fnSigmaElectron", fnSigmaElectron);

    fChain->SetBranchAddress("fcharge", fcharge);
    fChain->SetBranchAddress("ffitPts", ffitPts);
    fChain->SetBranchAddress("ffitPtsPoss", ffitPtsPoss);
    fChain->SetBranchAddress("fhitsdedx", fhitsdedx);

    fChain->SetBranchAddress("ftrigger", &ftrigger);

    TH1D *hVZ = new TH1D("hVZ", "hVZ", 125, -90, 90);
    TH1D *hvzVpd = new TH1D("vzVpd", "vzVpd", 125, -90, 90);

    TH1F *hdca = new TH1F("Dca", "Dca", 100, 0, 3.5);
    TH1F *hcharge = new TH1F("charge", "charge", 100, -2, 2);

    TH1D *hpT = new TH1D("pT", "pT", 100, 0, 40);
    TH1D *hp = new TH1D("p", "p", 100, 0, 40);

    TH1D *heta = new TH1D("h_eta", "h_eta", 100, -1.4, 1.4);
    TH1D *hphi = new TH1D("h_phi", "h_phi", 100, -3.4, 3.4);

    TH1D *hfitPts = new TH1D("h_fitPts", "h_fitPts", 60, 0, 60);
    TH1D *hfitPtsPoss = new TH1D("h_fitPtsPoss", "h_fitPtsPoss", 60, 0, 60);
    TH1D *hhitsdedx = new TH1D("h_hitsdedx", "h_hitsdedx", 60, 0, 60);

    TH1D *hdEdx = new TH1D("dEdx", "dEdx", 100, 0, 20);
    TH1F *hnSigmaPion = new TH1F("nSigmaPion", "nSigmaPion", 100, -10, 10);
    TH1F *hnSigmaKaon = new TH1F("nSigmaKaon", "nSigmaKaon", 100, -10, 10);
    TH1F *hnSigmaProton = new TH1F("nSigmaProton", "nSigmaProton", 100, -10, 10);
    TH1F *hnSigmaElectron = new TH1F("nSigmaElectron", "nSigmaElectron", 100, -10, 10);

    TH2D *h_dEdx_p = new TH2D("dEdx_Vs_p", "dEdx_Vs_p; log10(p)[GeV/c]; log10(dEdx)[GeV/cm]", 100, -0.35, 1.55, 100, -0.120, 1.30);

    // Trigger Seperated:
    TH1D *hpT_pos_JP0 = new TH1D("hpT_pos_JP0", "hpT_pos_JP0", 400, 0, 40);
    TH1D *hpT_neg_JP0 = new TH1D("hpT_neg_JP0", "hpT_neg_JP0", 400, 0, 40);
    TH1D *hpT_pos_JP1 = new TH1D("hpT_pos_JP1", "hpT_pos_JP1", 400, 0, 40);
    TH1D *hpT_neg_JP1 = new TH1D("hpT_neg_JP1", "hpT_neg_JP1", 400, 0, 40);
    TH1D *hpT_pos_JP2 = new TH1D("hpT_pos_JP2", "hpT_pos_JP2", 400, 0, 40);
    TH1D *hpT_neg_JP2 = new TH1D("hpT_neg_JP2", "hpT_neg_JP2", 400, 0, 40);
    TH1D *hpT_pos_JP2L2 = new TH1D("hpT_pos_JP2L2", "hpT_pos_JP2L2", 400, 0, 40);
    TH1D *hpT_neg_JP2L2 = new TH1D("hpT_neg_JP2L2", "hpT_neg_JP2L2", 400, 0, 40);
    TH1D *hpT_pos_BHT1_VPD100 = new TH1D("hpT_pos_BHT1_VPD100", "hpT_pos_BHT1_VPD100", 400, 0, 40);
    TH1D *hpT_neg_BHT1_VPD100 = new TH1D("hpT_neg_BHT1_VPD100", "hpT_neg_BHT1_VPD100", 400, 0, 40);
    TH1D *hpT_pos_BHT1_VPD30 = new TH1D("hpT_pos_BHT1_VPD30", "hpT_pos_BHT1_VPD30", 400, 0, 40);
    TH1D *hpT_neg_BHT1_VPD30 = new TH1D("hpT_neg_BHT1_VPD30", "hpT_neg_BHT1_VPD30", 400, 0, 40);
    TH1D *hpT_pos_BHT2_BBCMB = new TH1D("hpT_pos_BHT2_BBCMB", "hpT_pos_BHT2_BBCMB", 400, 0, 40);
    TH1D *hpT_neg_BHT2_BBCMB = new TH1D("hpT_neg_BHT2_BBCMB", "hpT_neg_BHT2_BBCMB", 400, 0, 40);
    TH1D *hpT_pos_BHT2_BBCMB1 = new TH1D("hpT_pos_BHT2_BBCMB1", "hpT_pos_BHT2_BBCMB1", 400, 0, 40);
    TH1D *hpT_neg_BHT2_BBCMB1 = new TH1D("hpT_neg_BHT2_BBCMB1", "hpT_neg_BHT2_BBCMB1", 400, 0, 40);
    TH1D *hpT_pos_BHT3 = new TH1D("hpT_pos_BHT3", "hpT_pos_BHT3", 400, 0, 40);
    TH1D *hpT_neg_BHT3 = new TH1D("hpT_neg_BHT3", "hpT_neg_BHT3", 400, 0, 40);
    TH1D *hpT_pos_Else = new TH1D("hpT_pos_Else", "hpT_pos_Else", 400, 0, 40);
    TH1D *hpT_neg_Else = new TH1D("hpT_neg_Else", "hpT_neg_Else", 400, 0, 40);

    int ntry = fChain->GetEntries();
    cout << ntry << "\t to Entries in the Tree" << endl;

    // Event loop started
    for (int i = 0; i < ntry; i++)
    {

        fChain->GetEntry(i);

        if (fabs(fVZ) > 90)
            continue;

        hVZ->Fill(fVZ);
        hvzVpd->Fill(fvzVpd);

        // Track Loop started
        for (int tr = 0; tr < fmaxpar; tr++)
        {

            // if (fp[tr] < 2.0)
            //     continue;
            // if (feta[tr] >= 1 || feta[tr] <= -1)
            //     continue;
            // if (fdca[tr] > 1.0)
            //     continue;

            if (fp[tr] > 0.0 && fdca[tr] < 1. && ffitPts[tr] > 15 && fhitsdedx[tr] > 20 && feta[tr] <= 1. && feta[tr] >= -1. && fitPtsRatio_tr > .51)

            {
                double log_fp = log10(fp[tr]);
                double log_fdEdx = log10(fdEdx[tr]);
                // h_dEdx_p->Fill(fp[tr], fdEdx[tr]);
                h_dEdx_p->Fill(log_fp, log_fdEdx);
            }

            double fitPtsRatio_tr = static_cast<double>(ffitPts[tr]) / (static_cast<double>(ffitPtsPoss[tr]));

            if (fp[tr] > 2 && fnSigmaPion[tr] >= -15. && fnSigmaPion[tr] <= 15. && fdca[tr] < 1. && ffitPts[tr] > 15 && fhitsdedx[tr] > 20 && feta[tr] < = 1. && feta[tr] >= -1. && fitPtsRatio_tr > .51)
            {

                hdca->Fill(fdca[tr]);
                hcharge->Fill(fcharge[tr]);

                hpT->Fill(fpT[tr]);
                hp->Fill(fp[tr]);

                heta->Fill(feta[tr]);
                hphi->Fill(fphi[tr]);

                hfitPts->Fill(ffitPts[tr]);
                hfitPtsPoss->Fill(ffitPtsPoss[tr]);
                hhitsdedx->Fill(fhitsdedx[tr]);

                hdEdx->Fill(fdEdx[tr]);
                hnSigmaPion->Fill(fnSigmaPion[tr]);
                hnSigmaKaon->Fill(fnSigmaKaon[tr]);
                hnSigmaProton->Fill(fnSigmaProton[tr]);
                hnSigmaElectron->Fill(fnSigmaElectron[tr]);

                // Trigger Seperated
                for (int trig = 0; trig < ftrigger->size(); trig++)

                {

                    if (ftrigger->at(trig) == 570001) // Just for test VPDMB_30 570001

                    {

                        if (fcharge[tr] > 0)
                        {
                            hpT_pos_JP0->Fill(fpT[tr]);
                        }
                        if (fcharge[tr] < 0)
                        {
                            hpT_neg_JP0->Fill(fpT[tr]);
                        }
                    }
                    else if (ftrigger->at(trig) == 570403)

                    {
                        if (fcharge[tr] > 0)
                        {
                            hpT_pos_JP1->Fill(fpT[tr]);
                        }
                        if (fcharge[tr] < 0)
                        {
                            hpT_neg_JP1->Fill(fpT[tr]);
                        }
                    }
                    else if (ftrigger->at(trig) == 570401)
                    {
                        if (fcharge[tr] > 0)
                        {
                            hpT_pos_JP2->Fill(fpT[tr]);
                        }
                        if (fcharge[tr] < 0)
                        {
                            hpT_neg_JP2->Fill(fpT[tr]);
                        }
                    }
                    else if (ftrigger->at(trig) == 570402)
                    {
                        if (fcharge[tr] > 0)
                        {
                            hpT_pos_JP2L2->Fill(fpT[tr]);
                        }
                        if (fcharge[tr] < 0)
                        {
                            hpT_neg_JP2L2->Fill(fpT[tr]);
                        }
                    }
                    else if (ftrigger->at(trig) == 570204)
                    {
                        if (fcharge[tr] > 0)
                        {
                            hpT_pos_BHT1_VPD100->Fill(fpT[tr]);
                        }
                        if (fcharge[tr] < 0)
                        {
                            hpT_neg_BHT1_VPD100->Fill(fpT[tr]);
                        }
                    }
                    else if (ftrigger->at(trig) == 570214)
                    {

                        if (fcharge[tr] > 0)
                        {
                            hpT_pos_BHT1_VPD30->Fill(fpT[tr]);
                        }
                        if (fcharge[tr] < 0)
                        {
                            hpT_neg_BHT1_VPD30->Fill(fpT[tr]);
                        }
                    }
                    else if (ftrigger->at(trig) == 570215)
                    {

                        if (fcharge[tr] > 0)
                        {
                            hpT_pos_BHT2_BBCMB->Fill(fpT[tr]);
                        }
                        if (fcharge[tr] < 0)
                        {
                            hpT_neg_BHT2_BBCMB->Fill(fpT[tr]);
                        }
                    }
                    else if (ftrigger->at(trig) == 570205)
                    {
                        if (fcharge[tr] > 0)
                        {
                            hpT_pos_BHT2_BBCMB1->Fill(fpT[tr]);
                        }
                        if (fcharge[tr] < 0)
                        {
                            hpT_neg_BHT2_BBCMB1->Fill(fpT[tr]);
                        }
                    }
                    else if (ftrigger->at(trig) == 570201)
                    {
                        if (fcharge[tr] > 0)
                        {
                            hpT_pos_BHT3->Fill(fpT[tr]);
                        }
                        if (fcharge[tr] < 0)
                        {
                            hpT_neg_BHT3->Fill(fpT[tr]);
                        }
                    }
                    else
                    {
                        if (fcharge[tr] > 0)
                        {
                            hpT_pos_Else->Fill(fpT[tr]);
                        }
                        if (fcharge[tr] < 0)
                        {
                            hpT_neg_Else->Fill(fpT[tr]);
                        }
                    }
                } // Trigger Loop
            }     // Track quality cut
        }         // Track loop
    }             // Event loop
    outfile->Write();
    outfile->Close();
    trigfile.close();
}
