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

void HodoH4() {

  gStyle->SetOptStat(0);

  // inputs
  //TFile* inFilePlateauScan = new TFile("/cmsrm/pc28_2/crovelli/data/imcp/H4/H4_scan5_SEE.root");
  //TFile* inFilePlateauScan = new TFile("/cmsrm/pc28_2/crovelli/data/imcp/H4/H4_scan6_MCP2.root");
  //TFile* inFilePlateauScan = new TFile("/cmsrm/pc28_2/crovelli/data/imcp/H4/H4_scan7_MCP5.root");
  TFile* inFilePlateauScan = new TFile("/cmsrm/pc28_2/crovelli/data/imcp/H4/H4_scan8_MCP4.root");
  TTree* h4PlateauScan  = (TTree*)inFilePlateauScan->Get("h4");

  // Selection
  //TString sden0 = "X[0]>-20 && Y[0]>-20 && run==738";  
  //TString sden1 = "X[1]>-20 && Y[1]>-20 && run==738";  
  //TString sden0 = "X[0]>-20 && Y[0]>-20 && run==749";  
  //TString sden1 = "X[1]>-20 && Y[1]>-20 && run==749";  
  //TString sden0 = "X[0]>-20 && Y[0]>-20 && run==772";  
  //TString sden1 = "X[1]>-20 && Y[1]>-20 && run==772";  
  TString sden0 = "X[0]>-20 && Y[0]>-20 && run==773";  
  TString sden1 = "X[1]>-20 && Y[1]>-20 && run==773";  
  TString snum0 = sden0 + " && amp_max[MiB2]>200";  
  TString snum1 = sden1 + " && amp_max[MiB2]>200";  

  // Efficiencies
  TH1F *HdenX0 = new TH1F("HdenX0", "HdenX0", 41,-20.5,20.5);  
  TH1F *HnumX0 = new TH1F("HnumX0", "HnumX0", 41,-20.5,20.5);  
  TH1F *HdenY0 = new TH1F("HdenY0", "HdenY0", 41,-20.5,20.5);  
  TH1F *HnumY0 = new TH1F("HnumY0", "HnumY0", 41,-20.5,20.5);  
  TH1F *HdenX1 = new TH1F("HdenX1", "HdenX1", 41,-20.5,20.5);  
  TH1F *HnumX1 = new TH1F("HnumX1", "HnumX1", 41,-20.5,20.5);  
  TH1F *HdenY1 = new TH1F("HdenY1", "HdenY1", 41,-20.5,20.5);  
  TH1F *HnumY1 = new TH1F("HnumY1", "HnumY1", 41,-20.5,20.5);  
  h4PlateauScan->Project("HdenX0", "X", sden0);
  h4PlateauScan->Project("HdenY0", "Y", sden0);
  h4PlateauScan->Project("HnumX0", "X", snum0);
  h4PlateauScan->Project("HnumY0", "Y", snum0);
  h4PlateauScan->Project("HdenX1", "X", sden1);
  h4PlateauScan->Project("HdenY1", "Y", sden1);
  h4PlateauScan->Project("HnumX1", "X", snum1);
  h4PlateauScan->Project("HnumY1", "Y", snum1);

  TGraphAsymmErrors* effX0 = new TGraphAsymmErrors(HnumX0,HdenX0);
  effX0->SetMarkerStyle(20);
  effX0->SetMarkerColor(1);
  effX0->SetLineColor(1);

  TGraphAsymmErrors* effY0 = new TGraphAsymmErrors(HnumY0,HdenY0);
  effY0->SetMarkerStyle(21);
  effY0->SetMarkerColor(2);
  effY0->SetLineColor(2);

  TGraphAsymmErrors* effX1 = new TGraphAsymmErrors(HnumX1,HdenX1);
  effX1->SetMarkerStyle(20);
  effX1->SetMarkerColor(1);
  effX1->SetLineColor(1);

  TGraphAsymmErrors* effY1 = new TGraphAsymmErrors(HnumY1,HdenY1);
  effY1->SetMarkerStyle(21);
  effY1->SetMarkerColor(2);
  effY1->SetLineColor(2);

  TH2F *myBaseX0 = new TH2F ("myBaseX0","", 100, -20.5, 20.5, 100, 0., 1.);
  myBaseX0->GetXaxis()->SetTitle("X - 1st plane");
  myBaseX0->GetYaxis()->SetTitle("Efficiency");

  TH2F *myBaseY0 = new TH2F ("myBaseY0","", 100, -20.5, 20.5, 100, 0., 1.);
  myBaseY0->GetXaxis()->SetTitle("Y - 1st plane");
  myBaseY0->GetYaxis()->SetTitle("Efficiency");

  TH2F *myBaseX1 = new TH2F ("myBaseX1","", 100, -20.5, 20.5, 100, 0., 1.);
  myBaseX1->GetXaxis()->SetTitle("X - 2nd plane");
  myBaseX1->GetYaxis()->SetTitle("Efficiency");

  TH2F *myBaseY1 = new TH2F ("myBaseY1","", 100, -20.5, 20.5, 100, 0., 1.);
  myBaseY1->GetXaxis()->SetTitle("Y - 2nd plane");
  myBaseY1->GetYaxis()->SetTitle("Efficiency");

  TCanvas* c10 = new TCanvas("c10","c",1);
  c10->Divide(2,1);
  c10->cd(1); myBaseX0->Draw(); effX0->Draw("Psame");
  c10->cd(2); myBaseY0->Draw(); effY0->Draw("Psame");
  c10->SaveAs("Eff1dim_plane0.png");  

  TCanvas* c11 = new TCanvas("c11","c",1);
  c11->Divide(2,1);
  c11->cd(1); myBaseX1->Draw(); effX1->Draw("Psame");
  c11->cd(2); myBaseY1->Draw(); effY1->Draw("Psame");
  c11->SaveAs("Eff1dim_plane1.png");  


  // 2dim
  TH2F *Hden2D0 = new TH2F("Hden2D0", "Hden2D0", 41,-20.5,20.5,41,-20.5,20.5);
  TH2F *Hnum2D0 = new TH2F("Hnum2D0", "Hnum2D0", 41,-20.5,20.5,41,-20.5,20.5);
  h4PlateauScan->Project("Hden2D0", "Y[0]:X[0]", sden0);
  h4PlateauScan->Project("Hnum2D0", "Y[0]:X[0]", snum0);

  TH2F *Hden2D1 = new TH2F("Hden2D1", "Hden2D1", 41,-20.5,20.5,41,-20.5,20.5);
  TH2F *Hnum2D1 = new TH2F("Hnum2D1", "Hnum2D1", 41,-20.5,20.5,41,-20.5,20.5);
  h4PlateauScan->Project("Hden2D1", "Y[1]:X[1]", sden1);
  h4PlateauScan->Project("Hnum2D1", "Y[1]:X[1]", snum1);

  TH2F *eff2D0 = (TH2F*)Hnum2D0->Clone();
  eff2D0->GetXaxis()->SetTitle("X - 1st plane");
  eff2D0->GetYaxis()->SetTitle("Y - 1st plane");
  eff2D0->Divide(Hden2D0);
  eff2D0->SetMinimum(0.9);

  TH2F *eff2D1 = (TH2F*)Hnum2D1->Clone();
  eff2D1->GetXaxis()->SetTitle("X - 2nd plane");
  eff2D1->GetYaxis()->SetTitle("Y - 2nd plane");
  eff2D1->Divide(Hden2D1);
  eff2D1->SetMinimum(0.9);

  TCanvas* c2 = new TCanvas("c2","c",1);
  c2->Divide(2,1);
  c2->cd(1); eff2D0->Draw("colz");
  c2->cd(2); eff2D1->Draw("colz");
  c2->SaveAs("Eff2D.png");    


}
	

//  LocalWords:  endl
