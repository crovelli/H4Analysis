{
  TFile *fileBinp1    = new TFile ("noiseOnBinps/HistosBinp1.root");
  TFile *fileBinp2    = new TFile ("noiseOnBinps/HistosBinp2.root");
  TFile *fileBinp3    = new TFile ("noiseOnBinps/HistosBinp3.root");
  TFile *fileBinp4    = new TFile ("noiseOnBinps/HistosBinp4_onlyGoodRuns.root");
  TFile *fileBinp4all = new TFile ("noiseOnBinps/HistosBinp4.root");

  TGraph *ampMaxMeanBinp1   = (TGraph*)fileBinp1->Get("ampMaxMean");
  TGraph *ampMaxMeanBinp2   = (TGraph*)fileBinp2->Get("ampMaxMean");
  TGraph *ampMaxMeanBinp3   = (TGraph*)fileBinp3->Get("ampMaxMean");
  TGraph *ampMaxMeanBinp4   = (TGraph*)fileBinp4->Get("ampMaxMean");
  //
  TGraph *ampMaxSigmaBinp1  = (TGraph*)fileBinp1->Get("ampMaxSigma");
  TGraph *ampMaxSigmaBinp2  = (TGraph*)fileBinp2->Get("ampMaxSigma");
  TGraph *ampMaxSigmaBinp3  = (TGraph*)fileBinp3->Get("ampMaxSigma");
  TGraph *ampMaxSigmaBinp4  = (TGraph*)fileBinp4->Get("ampMaxSigma");
  //
  TGraph *ampMaxChi2Binp1   = (TGraph*)fileBinp1->Get("ampMaxChi2");
  TGraph *ampMaxChi2Binp2   = (TGraph*)fileBinp2->Get("ampMaxChi2");
  TGraph *ampMaxChi2Binp3   = (TGraph*)fileBinp3->Get("ampMaxChi2");
  TGraph *ampMaxChi2Binp4a  = (TGraph*)fileBinp4all->Get("ampMaxChi2");

  TGraph *chargeMeanBinp1   = (TGraph*)fileBinp1->Get("chargeMean");
  TGraph *chargeMeanBinp2   = (TGraph*)fileBinp2->Get("chargeMean");
  TGraph *chargeMeanBinp3   = (TGraph*)fileBinp3->Get("chargeMean");
  TGraph *chargeMeanBinp4   = (TGraph*)fileBinp4->Get("chargeMean");
  //
  TGraph *chargeSigmaBinp1  = (TGraph*)fileBinp1->Get("chargeSigma");
  TGraph *chargeSigmaBinp2  = (TGraph*)fileBinp2->Get("chargeSigma");
  TGraph *chargeSigmaBinp3  = (TGraph*)fileBinp3->Get("chargeSigma");
  TGraph *chargeSigmaBinp4  = (TGraph*)fileBinp4->Get("chargeSigma");
  //
  TGraph *chargeChi2Binp1   = (TGraph*)fileBinp1->Get("chargeChi2");
  TGraph *chargeChi2Binp2   = (TGraph*)fileBinp2->Get("chargeChi2");
  TGraph *chargeChi2Binp3   = (TGraph*)fileBinp3->Get("chargeChi2");
  TGraph *chargeChi2Binp4a  = (TGraph*)fileBinp4all->Get("chargeChi2");

  ampMaxMeanBinp1->SetMarkerColor(1);
  ampMaxMeanBinp1->SetMarkerStyle(20);
  ampMaxMeanBinp2->SetMarkerColor(2);
  ampMaxMeanBinp2->SetMarkerStyle(21);
  ampMaxMeanBinp3->SetMarkerColor(3);
  ampMaxMeanBinp3->SetMarkerStyle(22);
  ampMaxMeanBinp4->SetMarkerColor(4);
  ampMaxMeanBinp4->SetMarkerStyle(23);

  ampMaxSigmaBinp1->SetMarkerColor(1);
  ampMaxSigmaBinp1->SetMarkerStyle(20);
  ampMaxSigmaBinp2->SetMarkerColor(2);
  ampMaxSigmaBinp2->SetMarkerStyle(21);
  ampMaxSigmaBinp3->SetMarkerColor(3);
  ampMaxSigmaBinp3->SetMarkerStyle(22);
  ampMaxSigmaBinp4->SetMarkerColor(4);
  ampMaxSigmaBinp4->SetMarkerStyle(23);

  ampMaxChi2Binp1->SetMarkerColor(1);
  ampMaxChi2Binp1->SetMarkerStyle(20);
  ampMaxChi2Binp2->SetMarkerColor(2);
  ampMaxChi2Binp2->SetMarkerStyle(21);
  ampMaxChi2Binp3->SetMarkerColor(3);
  ampMaxChi2Binp3->SetMarkerStyle(22);
  ampMaxChi2Binp4a->SetMarkerColor(4);
  ampMaxChi2Binp4a->SetMarkerStyle(23);

  chargeMeanBinp1->SetMarkerColor(1);
  chargeMeanBinp1->SetMarkerStyle(20);
  chargeMeanBinp2->SetMarkerColor(2);
  chargeMeanBinp2->SetMarkerStyle(21);
  chargeMeanBinp3->SetMarkerColor(3);
  chargeMeanBinp3->SetMarkerStyle(22);
  chargeMeanBinp4->SetMarkerColor(4);
  chargeMeanBinp4->SetMarkerStyle(23);

  chargeSigmaBinp1->SetMarkerColor(1);
  chargeSigmaBinp1->SetMarkerStyle(20);
  chargeSigmaBinp2->SetMarkerColor(2);
  chargeSigmaBinp2->SetMarkerStyle(21);
  chargeSigmaBinp3->SetMarkerColor(3);
  chargeSigmaBinp3->SetMarkerStyle(22);
  chargeSigmaBinp4->SetMarkerColor(4);
  chargeSigmaBinp4->SetMarkerStyle(23);

  chargeChi2Binp1->SetMarkerColor(1);
  chargeChi2Binp1->SetMarkerStyle(20);
  chargeChi2Binp2->SetMarkerColor(2);
  chargeChi2Binp2->SetMarkerStyle(21);
  chargeChi2Binp3->SetMarkerColor(3);
  chargeChi2Binp3->SetMarkerStyle(22);
  chargeChi2Binp4a->SetMarkerColor(4);
  chargeChi2Binp4a->SetMarkerStyle(23);

  gStyle->SetOptStat(0);

  TLegend *leg;
  leg = new TLegend(0.5,0.6,0.8,0.9);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.05);
  leg->SetFillColor(0);
  leg->AddEntry(ampMaxMeanBinp1, "40x2+40x2 (Binp1)", "p");
  leg->AddEntry(ampMaxMeanBinp2, "40x1+40x2 (Binp2)", "p");
  leg->AddEntry(ampMaxMeanBinp3, "90x1+40x2 (Binp3)", "p");
  leg->AddEntry(ampMaxMeanBinp4, "90x2+40x2 (Binp4)", "p");

  TH2F *myHamm = new TH2F("myHamm","amp_max mean",100,2320,2375,100,4.,6.5);
  myHamm->GetXaxis()->SetTitle("run");
  myHamm->GetYaxis()->SetTitle("gauss mean");
  TCanvas c1("c1","amp_max mean value",1);
  myHamm->Draw();
  ampMaxMeanBinp1->Draw("Psame");
  ampMaxMeanBinp2->Draw("Psame");
  ampMaxMeanBinp3->Draw("Psame");
  ampMaxMeanBinp4->Draw("Psame");
  leg->Draw();
  c1.SaveAs("ampMaxMeanValue.pdf");

  TH2F *myHams = new TH2F("myHams","amp_max sigma",100,2320,2375,100,1.4,3.4);
  myHams->GetXaxis()->SetTitle("run");
  myHams->GetYaxis()->SetTitle("gauss sigma");
  TCanvas c2("c2","amp_max sigma value",1);
  myHams->Draw();
  ampMaxSigmaBinp1->Draw("Psame");
  ampMaxSigmaBinp2->Draw("Psame");
  ampMaxSigmaBinp3->Draw("Psame");
  ampMaxSigmaBinp4->Draw("Psame");
  leg->Draw();
  c2.SaveAs("ampMaxSigmaValue.pdf");

  TH2F *myHamc = new TH2F("myHamc","amp_max #chi2",100,2320,2375,100,0.,100.);
  myHamc->GetXaxis()->SetTitle("run");
  myHamc->GetYaxis()->SetTitle("gauss chi2");
  TCanvas c3("c3","amp_max chi2 value",1);
  myHamc->Draw();
  ampMaxChi2Binp1->Draw("Psame");
  ampMaxChi2Binp2->Draw("Psame");
  ampMaxChi2Binp3->Draw("Psame");
  ampMaxChi2Binp4a->Draw("Psame");
  leg->Draw();
  c3.SaveAs("ampMaxChi2Value.pdf");

  TH2F *myHcm = new TH2F("myHcm","charge_sig mean",100,2320,2375,100,12.,32.);
  myHcm->GetXaxis()->SetTitle("run");
  myHcm->GetYaxis()->SetTitle("gauss mean");
  TCanvas c1b("c1b","charge_sig mean value",1);
  myHcm->Draw();
  chargeMeanBinp1->Draw("Psame");
  chargeMeanBinp2->Draw("Psame");
  chargeMeanBinp3->Draw("Psame");
  chargeMeanBinp4->Draw("Psame");
  leg->Draw();
  c1b.SaveAs("chargeMeanValue.pdf");

  TH2F *myHcs = new TH2F("myHcs","charge_sig sigma",100,2320,2375,100,15.,45.);
  myHcs->GetXaxis()->SetTitle("run");
  myHcs->GetYaxis()->SetTitle("gauss sigma");
  TCanvas c2b("c2b","charge_sig sigma value",1);
  myHcs->Draw();
  chargeSigmaBinp1->Draw("Psame");
  chargeSigmaBinp2->Draw("Psame");
  chargeSigmaBinp3->Draw("Psame");
  chargeSigmaBinp4->Draw("Psame");
  leg->Draw();
  c2b.SaveAs("chargeSigmaValue.pdf");

  TH2F *myHcc = new TH2F("myHcc","charge_sig #chi2",100,2320,2375,100,0.,100.);
  myHcc->GetXaxis()->SetTitle("run");
  myHcc->GetYaxis()->SetTitle("gauss chi2");
  TCanvas c3b("c3b","charge_sig chi2 value",1);
  myHcc->Draw();
  chargeChi2Binp1->Draw("Psame");
  chargeChi2Binp2->Draw("Psame");
  chargeChi2Binp3->Draw("Psame");
  chargeChi2Binp4a->Draw("Psame");
  leg->Draw();
  c3b.SaveAs("chargeChi2Value.pdf");
}
