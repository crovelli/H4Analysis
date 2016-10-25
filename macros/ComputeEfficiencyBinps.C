#include "TFile.h" 
#include "TTree.h" 
#include "TStyle.h" 
#include "TH1.h" 
#include "TH2.h" 
#include "TCanvas.h"
#include "TLegend.h"
#include "TGraphAsymmErrors.h" 
#include <iostream>

using namespace std;

void ComputeEfficiency() {

  gStyle->SetOptStat(0);

  // inputs - here each mcp is in 1st position
  TFile* inFileBinp1 = new TFile("btf2016_HVscanBinp1.root");
  TFile* inFileBinp2 = new TFile("btf2016_HVscanBinp2.root");
  TFile* inFileBinp3 = new TFile("btf2016_HVscanBinp3.root");
  TFile* inFileBinp4 = new TFile("btf2016_HVscanBinp4.root");
  TFile* inFileBinp2hv3700 = new TFile("btf2016_RU1_2339.root");
  TFile* inFileBinp2corr = new TFile("btf2016_HVscanBinp4.root");
  TFile* inFileTiming124 = new TFile("btf2016_RU5_2378.root");
  TFile* inFileTiming3   = new TFile("btf2016_RU4_2364.root");
  
  TTree* h4binp1 = (TTree*)inFileBinp1->Get("h4");
  TTree* h4binp2 = (TTree*)inFileBinp2->Get("h4");
  TTree* h4binp3 = (TTree*)inFileBinp3->Get("h4");
  TTree* h4binp4 = (TTree*)inFileBinp4->Get("h4");
  TTree* h4binp2hv3700 = (TTree*)inFileBinp2hv3700->Get("h4");
  TTree* h4binp2corr = (TTree*)inFileBinp2corr->Get("h4");
  TTree* h4timing124 = (TTree*)inFileTiming124->Get("h4");
  TTree* h4timing3   = (TTree*)inFileTiming3->Get("h4");

  // histos
  TH1F* num1 = new TH1F("num1","",2500,0.,2500.);
  TH1F* num2 = new TH1F("num2","",2500,0.,2500.);
  TH1F* num2corr = new TH1F("num2corr","",2500,0.,2500.);
  TH1F* num3 = new TH1F("num3","",2500,0.,2500.);
  TH1F* num4 = new TH1F("num4","",2500,0.,2500.);
  TH1F* den1 = new TH1F("den1","",2500,0.,2500.);
  TH1F* den2 = new TH1F("den2","",2500,0.,2500.);
  TH1F* den2corr = new TH1F("den2corr","",2500,0.,2500.);
  TH1F* den3 = new TH1F("den3","",2500,0.,2500.);
  TH1F* den4 = new TH1F("den4","",2500,0.,2500.);
  
  // denominators
  TString commonDen = "adc_data>200 && adc_data<700 && amp_max[MiB2]>200";
  TString commonDenAndRm2 = commonDen + " && amp_max[Rm2]>200 && amp_max[Rm2]<1200";
  TString denBinp2 = commonDenAndRm2 + " && (run<2336 || (run==2336 && (spill<9 || spill>20) ))";
  h4binp1->Project("den1","HVBINP1",commonDen);
  h4binp2->Project("den2","HVBINP2",denBinp2);
  h4binp2corr->Project("den2corr","HVBINP2",commonDenAndRm2);
  h4binp3->Project("den3","HVBINP3",commonDenAndRm2);
  h4binp4->Project("den4","HVBINP4",commonDenAndRm2);

  // numerators
  TString snum1 = commonDen + " && amp_max[BINP1]>20";
  TString snum2 = denBinp2 + " && amp_max[BINP2]>20";
  TString snum2corr = commonDenAndRm2 + " && amp_max[BINP2]>20";
  TString snum3 = commonDenAndRm2 + " && amp_max[BINP3]>20";
  TString snum4 = commonDenAndRm2 + " && amp_max[BINP4]>20";
  h4binp1->Project("num1","HVBINP1",snum1); 
  h4binp2->Project("num2","HVBINP2",snum2); 
  h4binp2corr->Project("num2corr","HVBINP2",snum2corr); 
  h4binp3->Project("num3","HVBINP3",snum3); 
  h4binp4->Project("num4","HVBINP4",snum4); 

 // efficiencies
  TGraphAsymmErrors* eff1 = new TGraphAsymmErrors(num1,den1);
  TGraphAsymmErrors* eff2 = new TGraphAsymmErrors(num2,den2);
  TGraphAsymmErrors* eff2corr = new TGraphAsymmErrors(num2corr,den2corr);
  TGraphAsymmErrors* eff3 = new TGraphAsymmErrors(num3,den3);
  TGraphAsymmErrors* eff4 = new TGraphAsymmErrors(num4,den4);
  eff1->SetMarkerStyle(20);
  eff1->SetMarkerColor(1);
  eff1->SetLineColor(1);
  eff2->SetMarkerStyle(21);
  eff2->SetMarkerColor(2);
  eff2->SetLineColor(2);
  eff2corr->SetMarkerStyle(21);
  eff2corr->SetMarkerColor(2);
  eff2corr->SetLineColor(2);
  eff3->SetMarkerStyle(22);
  eff3->SetMarkerColor(3);
  eff3->SetLineColor(3);
  eff4->SetMarkerStyle(23);
  eff4->SetMarkerColor(4);
  eff4->SetLineColor(4);

  TLegend *leg;
  leg = new TLegend(0.1,0.5,0.4,0.8);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.05);
  leg->SetFillColor(0);
  leg->AddEntry(eff1, "40x2+40x2 (Binp1)", "pl");
  leg->AddEntry(eff2, "40x1+40x2 (Binp2)", "pl");
  leg->AddEntry(eff3, "90x1+40x2 (Binp3)", "pl");
  leg->AddEntry(eff4, "90x2+40x2 (Binp4)", "pl");

  TCanvas* c1 = new TCanvas("c","c",1);
  c1->SetGrid();
  TH2F* H2 = new TH2F("H2","",2500,0.,2500.,100,0.,1.);
  H2->GetXaxis()->SetTitle("Bias voltage [V]");
  H2->GetYaxis()->SetTitle("Efficiency");
  H2->Draw();
  eff1->Draw("Plsame"); 
  eff2->Draw("Plsame"); 
  eff3->Draw("Plsame"); 
  eff4->Draw("Plsame");
  leg->Draw();
  c1->SaveAs("eff.png");

  TCanvas* c1c = new TCanvas("c1c","c",1);
  c1c->SetGrid();
  H2->Draw();
  eff1->Draw("Plsame"); 
  eff2corr->Draw("Plsame"); 
  eff3->Draw("Plsame"); 
  eff4->Draw("Plsame");
  leg->Draw();
  c1c->SaveAs("eff_binp2corr.png");



  // Spectra comparison
  TH1F *amp1 = new TH1F("amp1","amp1",100,0.,4000);
  TH1F *amp2 = new TH1F("amp2","amp2",100,0.,4000);
  TH1F *amp3 = new TH1F("amp3","amp3",100,0.,4000);
  TH1F *amp4 = new TH1F("amp4","amp4",100,0.,4000);
  amp1->SetLineColor(1);
  amp2->SetLineColor(2);
  amp3->SetLineColor(3);
  amp4->SetLineColor(4);
  amp1->SetLineWidth(2);
  amp2->SetLineWidth(2);
  amp3->SetLineWidth(2);
  amp4->SetLineWidth(2);
  h4binp1      ->Project("amp1","amp_max[BINP1]",commonDen+" && HVBINP1==2400");
  //h4binp2hv3700->Project("amp2","amp_max[BINP2]",commonDenAndRm2+" && HVBINP2==1400"); 
  h4binp2corr  ->Project("amp2","amp_max[BINP2]",commonDenAndRm2+" && HVBINP2==1400"); 
  h4binp3      ->Project("amp3","amp_max[BINP3]",commonDenAndRm2+" && HVBINP3==1400");
  h4binp4      ->Project("amp4","amp_max[BINP4]",commonDenAndRm2+" && HVBINP4==2400");

  TCanvas* c1b = new TCanvas("cb","c",1);
  c1b->SetGrid();
  amp1->DrawNormalized(); 
  amp2->DrawNormalized("same"); 
  amp3->DrawNormalized("same"); 
  amp4->DrawNormalized("same"); 
  leg->Draw();
  c1b->SetLogy();
  c1b->SaveAs("amplitude.png");


  // Spectra comparison on timing runs
  TH1F *amp1T = new TH1F("amp1T","amp1T",100,0.,4000);
  TH1F *amp2T = new TH1F("amp2T","amp2T",100,0.,4000);
  TH1F *amp3T = new TH1F("amp3T","amp3T",100,0.,4000);
  TH1F *amp4T = new TH1F("amp4T","amp4T",100,0.,4000);
  amp1T->SetLineColor(1);
  amp2T->SetLineColor(2);
  amp3T->SetLineColor(3);
  amp4T->SetLineColor(4);
  amp1T->SetLineWidth(2);
  amp2T->SetLineWidth(2);
  amp3T->SetLineWidth(2);
  amp4T->SetLineWidth(2);
  h4timing124 ->Project("amp1T","amp_max[BINP1]",commonDenAndRm2);
  h4timing124 ->Project("amp2T","amp_max[BINP2]",commonDenAndRm2);
  h4timing3   ->Project("amp3T","amp_max[BINP3]",commonDen);
  h4timing124 ->Project("amp4T","amp_max[BINP4]",commonDenAndRm2);

  TCanvas* c2a = new TCanvas("c2a","c",1);
  c2a->SetGrid();
  amp1T->DrawNormalized(); 
  amp2T->DrawNormalized("same"); 
  amp3T->DrawNormalized("same"); 
  amp4T->DrawNormalized("same"); 
  leg->Draw();
  c2a->SetLogy();
  c2a->SaveAs("amplitude_timingRuns.png");

  // Efficiency in timing runs
  float denT1 = amp1T->Integral();
  float denT2 = amp2T->Integral();
  float denT3 = amp3T->Integral();
  float denT4 = amp4T->Integral();
  h4timing124 ->Project("amp1T","amp_max[BINP1]",commonDenAndRm2 + " && amp_max[BINP1]>20");
  h4timing124 ->Project("amp2T","amp_max[BINP2]",commonDenAndRm2 + " && amp_max[BINP2]>20"); 
  h4timing3   ->Project("amp3T","amp_max[BINP3]",commonDen + " && amp_max[BINP3]>20");
  h4timing124 ->Project("amp4T","amp_max[BINP4]",commonDenAndRm2 + " && amp_max[BINP4]>20");
  float numT1 = amp1T->Integral();
  float numT2 = amp2T->Integral();
  float numT3 = amp3T->Integral();
  float numT4 = amp4T->Integral();
  cout << "Efficiencies in timing runs: " << endl;
  cout << "Binp1 = " << numT1/denT1 << endl;
  cout << "Binp2 = " << numT2/denT2 << endl;
  cout << "Binp3 = " << numT3/denT3 << endl;
  cout << "Binp4 = " << numT4/denT4 << endl;
}
	
