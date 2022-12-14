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
    double fpT[fMaxHit];
    double fp[fMaxHit];
    double feta[fMaxHit];
    double fphi[fMaxHit];
    double fdca[fMaxHit];
    UShort_t ffitPts[fMaxHit];
    UShort_t ffitPtsPoss[fMaxHit];

    vector<int> *ftrigger;

    ofstream trigfile("TrigFile_Data.txt");
    fChain->SetBranchAddress("fmaxpar", &fmaxpar);
    fChain->SetBranchAddress("fVZ", &fVZ);
    fChain->SetBranchAddress("fpT", fpT);
    fChain->SetBranchAddress("fp", fp);
    fChain->SetBranchAddress("feta", feta);
    fChain->SetBranchAddress("fphi", fphi);
    fChain->SetBranchAddress("ffitPts", ffitPts);
    fChain->SetBranchAddress("ffitPtsPoss", ffitPtsPoss);
    fChain->SetBranchAddress("fdca", fdca);
    fChain->SetBranchAddress("ftrigger", &ftrigger);

    TH1D *hVZ = new TH1D("hVZ", "hVZ", 125, -90, 90);

    TH1D *hpT = new TH1D("pT", "pT", 100, 0, 40);

    TH1D *heta = new TH1D("h_eta", "h_eta", 100, -1.4, 1.4);

    TH1D *hphi = new TH1D("h_phi", "h_phi", 100, -3.4, 3.4);

    TH1D *hfitPts = new TH1D("h_fitPts", "h_fitPts", 60, 0, 60);

    TH1D *hfitPtsPoss = new TH1D("h_fitPtsPoss", "h_fitPtsPoss", 60, 0, 60);

    int ntry = fChain->GetEntries();
    cout << ntry << "\t to Entries in the Tree" << endl;

    // Event loop started
    for (int i = 0; i < ntry; i++)
    {

        fChain->GetEntry(i);

       // if (fabs(fVZ) > 90)
       //     continue;

        hVZ->Fill(fVZ);

        // Track Loop started
        for (int k = 0; k < fmaxpar; k++)
        {

            //if (fp[k] < 2.0)
            //    continue;
            //if (feta[k] >= 1 || feta[k] <= -1)
            //    continue;
            //if (fdca[k] > 1.0)
            //    continue;

            hpT->Fill(fpT[k]);
            heta->Fill(feta[k]);
            hphi->Fill(fphi[k]);
            hfitPts->Fill(ffitPts[k]);
            hfitPtsPoss->Fill(ffitPtsPoss[k]);
        } // Track loop
    }     // Event loop
    outfile->Write();
    outfile->Close();
    trigfile.close();
}
