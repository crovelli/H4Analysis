#include "TFile.h"
#include "TStyle.h"
#include "TH1.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TGraphAsymmErrors.h"
#include <iostream>

void plottone() {

  // inputs
  TFile *inputBinps = new TFile("myOutputFileBinps.root");  
  TFile *inputCamer = new TFile("myOutputFileCameroniBtf.root");  
  TFile *inputH4    = new TFile("myOutputFileH4.root");  

  TGraphAsymmErrors *binp1 = (TGraphAsymmErrors*)inputBinps->Get("binp1");
  TGraphAsymmErrors *binp3 = (TGraphAsymmErrors*)inputBinps->Get("binp3");
  TGraphAsymmErrors *binp4 = (TGraphAsymmErrors*)inputBinps->Get("binp4");
  
  TGraphAsymmErrors *effMib25Corr_1200 = (TGraphAsymmErrors*)inputCamer->Get("effMib25Corr_1200");
  TGraphAsymmErrors *effRm8Corr_1200   = (TGraphAsymmErrors*)inputCamer->Get("effRm8Corr_1200");

  TGraphAsymmErrors *effZS2Corr  = (TGraphAsymmErrors*)inputH4->Get("effZS2Corr");
  TGraphAsymmErrors *effMib3Corr = (TGraphAsymmErrors*)inputH4->Get("effMib3Corr");

  // cosmetics
  binp1->SetMarkerStyle(20);
  binp1->SetMarkerColor(1);
  binp1->SetLineColor(1);
  binp1->SetLineStyle(1);
  binp3->SetMarkerStyle(20);
  binp3->SetMarkerColor(2);
  binp3->SetLineColor(2);
  binp3->SetLineStyle(1);
  binp4->SetMarkerStyle(20);
  binp4->SetMarkerColor(3);
  binp4->SetLineColor(3);
  binp4->SetLineStyle(1);

  effMib25Corr_1200->SetMarkerStyle(20);
  effMib25Corr_1200->SetMarkerColor(4);
  effMib25Corr_1200->SetLineColor(4);
  effMib25Corr_1200->SetLineStyle(1);
  effRm8Corr_1200->SetMarkerStyle(20);
  effRm8Corr_1200->SetMarkerColor(5);
  effRm8Corr_1200->SetLineColor(5);
  effRm8Corr_1200->SetLineStyle(1);

  effZS2Corr->SetMarkerStyle(20);
  effZS2Corr->SetMarkerColor(6);
  effZS2Corr->SetLineColor(6);
  effZS2Corr->SetLineStyle(2);
  effMib3Corr->SetMarkerStyle(20);
  effMib3Corr->SetMarkerColor(7);
  effMib3Corr->SetLineColor(7);
  effMib3Corr->SetLineStyle(2);

  // plotting
  gStyle->SetOptStat(0);

  TH2F* H2 = new TH2F("H2","",3200,0.,3200.,100,0.,1.);
  H2->GetXaxis()->SetTitle("MCP-stack bias [V]");
  H2->GetYaxis()->SetTitle("Efficiency");

  /*
  TLegend *leg;
  leg = new TLegend(0.1,0.5,0.4,0.8);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.05);
  leg->SetFillColor(0);
  leg->AddEntry(binp1, "40x2+40x2, e- 0.5GeV", "pl");
  leg->AddEntry(binp3, "90x1+40x2, e- 0.5GeV", "pl");
  leg->AddEntry(binp4, "90x2+40x2, e- 0.5GeV", "pl");
  leg->AddEntry(effMib25Corr_1200, "80x2+40x1, e- 0.5GeV", "pl");
  leg->AddEntry(effRm8Corr_1200,   "80x1+40x1, e- 0.5GeV", "pl");
  leg->AddEntry(effZS2Corr, "40x3, e- 50GeV", "pl");
  leg->AddEntry(effMib3Corr, "40x2, e- 50GeV", "pl");
  */

  TLegend *leg;
  leg = new TLegend(0.1,0.55,0.4,0.85);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.05);
  leg->SetFillColor(0);
  leg->AddEntry(binp1, "40x2+40x2", "pl");
  leg->AddEntry(binp3, "90x1+40x2", "pl");
  leg->AddEntry(binp4, "90x2+40x2", "pl");
  leg->AddEntry(effMib25Corr_1200, "80x2+40x1", "pl");
  leg->AddEntry(effRm8Corr_1200,   "80x1+40x1", "pl");
  leg->AddEntry(effZS2Corr,  "40x3", "pl");
  leg->AddEntry(effMib3Corr, "40x2", "pl");

  TLegend *leg2;
  leg2 = new TLegend(0.1,0.35,0.4,0.50);
  leg2->SetFillStyle(0);
  leg2->SetBorderSize(0);
  leg2->SetTextSize(0.05);
  leg2->SetFillColor(0);
  leg2->AddEntry(binp1,      "e- 491MeV", "l");
  leg2->AddEntry(effZS2Corr, "e- 50GeV",  "l");

  TCanvas* c1 = new TCanvas("c1","c",1);
  c1->SetGrid();
  H2->Draw();
  binp1->Draw("Plsame");
  binp3->Draw("Plsame");
  binp4->Draw("Plsame");
  effMib25Corr_1200->Draw("Plsame");
  effRm8Corr_1200->Draw("Plsame");
  effZS2Corr->Draw("Plsame");
  effMib3Corr->Draw("Plsame");
  leg->Draw();
  leg2->Draw();
  c1->SaveAs("summaryEff.png");
  c1->SaveAs("summaryEff.pdf");


}
