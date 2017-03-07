#include "TFile.h"
#include "TStyle.h"
#include "TH1.h"
#include "TH2.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TColor.h"
#include "TGraphAsymmErrors.h"
#include <iostream>
#include "FPCanvasStyle.C"
#include "setStyle.C"

void effVsXo() {

  // inputs
  TFile *inputZs1  = new TFile("ZStack1_X0_scanX0_HVHigh20GeV.root");  
  TFile *inputMib3 = new TFile("MiB3_X0_scanX0_HVHigh20GeV.root");

  TGraph *gZs1  = (TGraph*)inputZs1->Get("eff");
  TGraph *gMib3 = (TGraph*)inputMib3->Get("eff");

  // cosmetics
  gZs1->SetMarkerStyle(24);
  gZs1->SetMarkerColor(kMagenta+3);
  gZs1->SetLineColor(kMagenta+3);
  gZs1->SetLineStyle(6);
  gZs1->SetLineWidth(2);
  gZs1->SetMarkerSize(1.1);
  gMib3->SetMarkerStyle(25);
  gMib3->SetMarkerColor(kBlue-1);
  gMib3->SetLineColor(kBlue-1);
  gMib3->SetLineStyle(7);
  gMib3->SetLineWidth(2);

  // plotting
  setStyle();

  TH2F* H2 = new TH2F("H2","",7,0.,7.1,100,0.,1.3);
  H2->GetXaxis()->SetTitle("Randiation lengths (X_{0})");
  H2->GetYaxis()->SetTitle("Efficiency");
  TLine *line = new TLine(0,1,7,1);

  TLegend *leg;
  leg = new TLegend(0.18,0.75,0.38,0.85);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.03);
  leg->SetFillColor(0);
  leg->AddEntry(gZs1,  "40x3", "pl");
  leg->AddEntry(gMib3, "40x2", "pl");

  TCanvas* c1 = new TCanvas("c1","c",1);
  FPCanvasStyle(c1);
  H2->Draw();
  line->Draw();
  gZs1->Draw("PCsame");
  gMib3->Draw("PCsame");
  leg->Draw();
  TLatex latex2(0.2,0.87,"#bf{#bf{Electrons 20 GeV}}");;
  latex2.SetTextSize(0.03);
  latex2.SetNDC(kTRUE);
  latex2.Draw();

  c1->SaveAs("effVsXo.png");
  c1->SaveAs("effVsXo.pdf");


}
