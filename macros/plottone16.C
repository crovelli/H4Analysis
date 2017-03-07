#include "TFile.h"
#include "TStyle.h"
#include "TH1.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TColor.h"
#include "TLatex.h"
#include "TGraphAsymmErrors.h"
#include <iostream>
#include "FPCanvasStyle.C"
#include "setStyle.C"

void plottone16() {

  // inputs
  TFile *inputBinps = new TFile("myOutputFileBinps.root");  
  TFile *inputCamer = new TFile("myOutputFileCameroniBtf.root");  

  TGraphAsymmErrors *binp1 = (TGraphAsymmErrors*)inputBinps->Get("binp1");
  TGraphAsymmErrors *binp3 = (TGraphAsymmErrors*)inputBinps->Get("binp3");
  TGraphAsymmErrors *binp4 = (TGraphAsymmErrors*)inputBinps->Get("binp4");
  
  TGraphAsymmErrors *effMib25Corr_1200 = (TGraphAsymmErrors*)inputCamer->Get("effMib25Corr_1200");
  TGraphAsymmErrors *effRm8Corr_1200   = (TGraphAsymmErrors*)inputCamer->Get("effRm8Corr_1200");

  // cosmetics
  binp1->SetMarkerStyle(20);
  binp1->SetMarkerSize(1.1);
  binp1->SetMarkerColor(1);
  binp1->SetLineColor(1);
  binp1->SetLineStyle(1);
  binp1->SetLineWidth(2);
  binp3->SetMarkerStyle(21);
  binp3->SetMarkerColor(kRed+2);
  binp3->SetLineColor(kRed+2);
  binp3->SetLineStyle(2);
  binp3->SetLineWidth(2);
  binp4->SetMarkerStyle(22);
  binp4->SetMarkerSize(1.4);
  binp4->SetMarkerColor(kGreen+3);
  binp4->SetLineColor(kGreen+3);
  binp4->SetLineStyle(3);
  binp4->SetLineWidth(2);

  effMib25Corr_1200->SetMarkerStyle(23);
  effMib25Corr_1200->SetMarkerColor(kRed+3);
  effMib25Corr_1200->SetLineColor(kRed+3);
  effMib25Corr_1200->SetLineStyle(4);
  effMib25Corr_1200->SetLineWidth(2);
  effMib25Corr_1200->SetMarkerSize(1.4);
  effRm8Corr_1200->SetMarkerStyle(33);
  effRm8Corr_1200->SetMarkerColor(kCyan+2);
  effRm8Corr_1200->SetLineColor(kCyan+2);
  effRm8Corr_1200->SetLineStyle(5);
  effRm8Corr_1200->SetLineWidth(2);
  effRm8Corr_1200->SetMarkerSize(1.7);

  // plotting
  setStyle();

  TH2F* H2 = new TH2F("H2","",2800,0.,2800.,100,0.,1.5);
  H2->GetXaxis()->SetTitle("MCP-stack bias [V]");
  H2->GetYaxis()->SetTitle("Efficiency");
  TLine *line = new TLine(0,1,2800,1);

  TLegend *leg;
  leg = new TLegend(0.18,0.66,0.38,0.86);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->AddEntry(binp1, "40x2+40x2, Amp bias=2100V", "pl");
  leg->AddEntry(binp3, "90x1+40x2, Amp bias=2100V", "pl");
  leg->AddEntry(binp4, "90x2+40x2, Amp bias=2100V", "pl");

  TLegend *legA;
  legA = new TLegend(0.58,0.66,0.78,0.86);
  legA->SetFillStyle(0);
  legA->SetBorderSize(0);
  legA->SetTextSize(0.03);
  legA->SetFillColor(0);
  legA->AddEntry(effMib25Corr_1200, "80x2+40x1, Amp bias=1200V", "pl");
  legA->AddEntry(effRm8Corr_1200,   "80x1+40x1, Amp bias=1200V", "pl");

  TCanvas* c1 = new TCanvas("c1","c",1);
  FPCanvasStyle(c1);

  H2->Draw();
  line->Draw();
  binp1->Draw("PCsame");
  binp3->Draw("PCsame");
  binp4->Draw("PCsame");
  effMib25Corr_1200->Draw("PCsame");
  effRm8Corr_1200->Draw("PCsame");
  leg->Draw();
  legA->Draw();

  TLatex latex(0.2,0.95,"#it{Preliminary}");;
  latex.SetTextSize(0.05);
  latex.SetNDC(kTRUE);
  latex.Draw();

  TLatex latex2(0.2,0.87,"#bf{#bf{Electron 491 MeV}}");;
  latex2.SetTextSize(0.03);
  latex2.SetNDC(kTRUE);
  latex2.Draw();

  c1->SaveAs("summaryEff.png");
  c1->SaveAs("summaryEff.pdf");


}
