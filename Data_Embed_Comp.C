void Data_Embed_Comp()
{
    // TFile *mu_file = new TFile("/star/u/nghimire/pp500/IFF_Run17/PID/triggerBias/TreeProduction/PionPairStudy_NewTest/ReadTree_Test.root");
    TFile *mu_file = new TFile("./MuDst_ReadTree.root");
    TFile *pico_file = new TFile("./picoDst_ReadTree.root");

    TH1D *hmu_vz = (TH1D *)mu_file->Get("hVZ");
    TH1D *hpico_vz = (TH1D *)pico_file->Get("hVZ");
    TH1D *hmu_vzVpd = (TH1D *)mu_file->Get("vzVpd");
    TH1D *hpico_vzVpd = (TH1D *)pico_file->Get("vzVpd");

    TH1D *hmu_pT = (TH1D *)mu_file->Get("pT");
    TH1D *hpico_pT = (TH1D *)pico_file->Get("pT");
    TH1D *hmu_p = (TH1D *)mu_file->Get("p");
    TH1D *hpico_p = (TH1D *)pico_file->Get("p");

    TH1D *hmu_dca = (TH1D *)mu_file->Get("Dca");
    TH1D *hpico_dca = (TH1D *)pico_file->Get("Dca");

    TH1D *hmu_eta = (TH1D *)mu_file->Get("h_eta");
    TH1D *hpico_eta = (TH1D *)pico_file->Get("h_eta");

    TH1D *hmu_phi = (TH1D *)mu_file->Get("h_phi");
    TH1D *hpico_phi = (TH1D *)pico_file->Get("h_phi");

    TH1D *hmu_fitPts = (TH1D *)mu_file->Get("h_fitPts");
    TH1D *hpico_fitPts = (TH1D *)pico_file->Get("h_fitPts");

    TH1D *hmu_fitPtsPoss = (TH1D *)mu_file->Get("h_fitPtsPoss");
    TH1D *hpico_fitPtsPoss = (TH1D *)pico_file->Get("h_fitPtsPoss");

    TH1D *hmu_fitPtsPoss = (TH1D *)mu_file->Get("h_fitPtsPoss");
    TH1D *hpico_fitPtsPoss = (TH1D *)pico_file->Get("h_fitPtsPoss");

    TH1D *hmu_hitsdedx = (TH1D *)mu_file->Get("h_hitsdedx");
    TH1D *hpico_hitsdedx = (TH1D *)pico_file->Get("h_hitsdedx");

    TH1D *h_dEdx_p = (TH1D *)mu_file->Get("h_dEdx_p");

    TH1D *hmupT_pos_JP0 = (TH1D *)mu_file->Get("hpT_pos_JP0");
    TH1D *hpicopT_pos_JP0 = (TH1D *)pico_file->Get("hpT_pos_JP0");

    TH1D *hmupT_pos_JP1 = (TH1D *)mu_file->Get("hpT_pos_JP1");
    TH1D *hpicopT_pos_JP1 = (TH1D *)pico_file->Get("hpT_pos_JP1");

    TH1D *hmupT_pos_JP2 = (TH1D *)mu_file->Get("hpT_pos_JP2");
    TH1D *hpicopT_pos_JP2 = (TH1D *)pico_file->Get("hpT_pos_JP2");

    TH1D *hmupT_pos_BHT1_VPD30 = (TH1D *)mu_file->Get("hpT_pos_BHT1_VPD30");
    TH1D *hpicopT_pos_BHT1_VPD30 = (TH1D *)pico_file->Get("hpT_pos_BHT1_VPD30");

    TH1D *hmupT_pos_BHT3 = (TH1D *)mu_file->Get("hpT_pos_BHT3");
    TH1D *hpicopT_pos_BHT3 = (TH1D *)pico_file->Get("hpT_pos_BHT3");
    TH1D *hmupT_pos_Else = (TH1D *)mu_file->Get("hpT_pos_Else");
    TH1D *hpicopT_pos_Else = (TH1D *)pico_file->Get("hpT_pos_Else");

    void plot_diff(TH1D *, TH1D *); // declearation of Function

    plot_diff(hmu_vz, hpico_vz);
    plot_diff(hmu_vzVpd, hpico_vzVpd);

    plot_diff(hmu_dca, hpico_dca);
    plot_diff(hmu_pT, hpico_pT);
    plot_diff(hmu_p, hpico_p);
    plot_diff(hmu_eta, hpico_eta);
    plot_diff(hmu_phi, hpico_phi);

    plot_diff(hmu_fitPts, hpico_fitPts);
    plot_diff(hmu_fitPtsPoss, hpico_fitPtsPoss);
    plot_diff(hmu_hitsdedx, hpico_hitsdedx);
    plot_diff(hmu_hitsdedx, hpico_hitsdedx);

    plot_diff(hmupT_pos_JP0, hpicopT_pos_JP0);
    plot_diff(hmupT_pos_JP1, hpicopT_pos_JP1);
    plot_diff(hmupT_pos_JP2, hpicopT_pos_JP2);
    plot_diff(hmupT_pos_BHT1_VPD30, hpicopT_pos_BHT1_VPD30);
    plot_diff(hmupT_pos_BHT3, hpicopT_pos_BHT3);
    plot_diff(hmupT_pos_Else, hpicopT_pos_Else);
}

plot_diff(TH1D *hdata, TH1D *hembed)
{
    TCanvas *c_comp = new TCanvas("canv_comp", "canv_comp", 900, 700);
    c_comp->cd()->SetLogy();
    gStyle->SetOptStat(0);
    // hdata->Sumw2();
    // hembed->Sumw2();
    // hdata->Rebin(5);
    // hembed->Rebin(5);
    hdata->Scale(1 / hdata->Integral());
    hembed->Scale(1 / hembed->Integral());
    hembed->SetMarkerStyle(20);
    hembed->SetMarkerColor(kRed);
    hembed->SetLineColor(kRed);
    TPad *pad1 = new TPad("pad1", "pad1", 0.0, 0.3, 1.0, 1.0);
    pad1->SetBottomMargin(0);
    pad1->Draw();
    pad1->cd()->SetLogy();
    hembed->Draw("P");
    hdata->Draw("same");
    TLegend *leg = new TLegend(0.8, 0.7, 0.9, 0.9);
    leg->AddEntry(hdata, "MuDst");
    leg->AddEntry(hembed, "picoDst");
    leg->Draw();
    c_comp->Update();

    c_comp->cd();
    TPad *pad2 = new TPad("pad2", "pad2", 0.0, 0.0, 1.0, 0.3);
    pad2->SetTopMargin(0);
    pad2->SetBottomMargin(0.2);
    pad2->Draw();
    pad2->cd();

    TH1D *h_Ratio = (TH1D *)hdata->Clone();
    /*for (int nbin = 0; nbin < hdata->GetNbinsX(); nbin++)
    {
        double N_data = hdata->GetBinContent(nbin);
        double N_embed = hembed->GetBinContent(nbin);
        if (N_data == 0 || N_embed == 0)
            continue;
        double N_Ratio = (N_data - N_embed) / (N_data);
        h_Ratio->SetBinContent(nbin, N_Ratio);
        double err = sqrt((pow(N_embed, 2) / pow(N_data, 3)) + (N_embed / (pow(N_data, 2))));
        cout << N_data << "\t Data"<<endl;
        cout << N_embed << "\t Embed"<<endl;
        cout << err << "\t Data Embed Error"<<endl;
        h_Ratio->SetBinError(nbin, err);
    }
*/

    h_Ratio->Add(hembed, -1);
    h_Ratio->Divide(hdata);
    h_Ratio->GetYaxis()->SetTitle("#frac{Data-Embed}{Data}");
    h_Ratio->GetYaxis()->CenterTitle();
    h_Ratio->Fit("pol0");
    h_Ratio->GetYaxis()->SetRangeUser(-0.5, 0.5);
    h_Ratio->Draw();
    string name;
    name = h_Ratio->GetName();
    cout << name << endl;
    /*if(name == "hVZ"){
     //TH1D *h_Ratio = (TH1D*)hdata->Clone();
     //h_Ratio->Divide(hembed);
     TH1D *h_Ratio = (TH1D*)hdata->Clone();
     h_Ratio->Divide(hembed);
     //TF1 *verfit = new TF1("verfit","gaus(0)+gaus(3)",-90,90);
    //verfit->SetParLimits(2,10,40);
     //verfit->SetParLimits(5,40,60);
     TF1 *verfit = new TF1("verfit","pol10",-90,90);
     h_Ratio->Fit(verfit,"R");
     cout << "Hellow"<<endl;
     }
     */

    c_comp->SaveAs(Form("%s.pdf", name));
    hdata->Clear();
    hembed->Clear();
}
