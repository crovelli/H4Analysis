#include "TFile.h" 
#include "TTree.h" 
#include "TStyle.h" 
#include "TH1.h" 
#include "TH2.h" 
#include "TF1.h" 
#include "TCanvas.h"
#include "TLegend.h"
#include "TGraphAsymmErrors.h" 
#include <iostream>

using namespace std;

void ComputeEfficiencyH4() {

  gStyle->SetOptStat(0);

  // inputs - here each mcp is in 1st position (for 2corr it is not)
  TFile* inFileSee  = new TFile("/cmsrm/pc28_2/crovelli/data/imcp/H4/H4_scan5_SEE.root"); 
  TFile* inFileMcp2 = new TFile("/cmsrm/pc28_2/crovelli/data/imcp/H4/H4_scan6_MCP2.root");
  TFile* inFileMcp5 = new TFile("/cmsrm/pc28_2/crovelli/data/imcp/H4/H4_scan7_MCP5.root"); 
  TFile* inFileMcp4 = new TFile("/cmsrm/pc28_2/crovelli/data/imcp/H4/H4_scan8_MCP4.root"); 
  //
  TTree* h4binpSee  = (TTree*)inFileSee->Get("h4");
  TTree* h4binpMcp2 = (TTree*)inFileMcp2->Get("h4");
  TTree* h4binpMcp5 = (TTree*)inFileMcp5->Get("h4");
  TTree* h4binpMcp4 = (TTree*)inFileMcp4->Get("h4");

  // ----------------------------------------
  TH1F* numSee  = new TH1F("numSee", "",3500,0.,3500.);
  TH1F* numMcp2 = new TH1F("numMcp2","",3500,0.,3500.);
  TH1F* numMcp5 = new TH1F("numMcp5","",3500,0.,3500.);
  TH1F* numMcp4 = new TH1F("numMcp4","",3500,0.,3500.);
  TH1F* denSee  = new TH1F("denSee", "",3500,0.,3500.);
  TH1F* denMcp2 = new TH1F("denMcp2","",3500,0.,3500.);
  TH1F* denMcp5 = new TH1F("denMcp5","",3500,0.,3500.);
  TH1F* denMcp4 = new TH1F("denMcp4","",3500,0.,3500.);

  // Nominal denominator: selection based on ref-mcp amplitudes and hodo
  TString commonDen = "amp_max[MiB2]>200 && fabs(time_max[MiB2])<150 && X[0]>-800 && X[1]>-800 && Y[0]>-800 && Y[0]>-800";
  h4binpSee ->Project("denSee", "HVSEE", commonDen);
  h4binpMcp2->Project("denMcp2","HVZS2", commonDen+" && HVZS2>0");
  h4binpMcp5->Project("denMcp5","HVMiB3",commonDen);
  h4binpMcp4->Project("denMcp4","HVZS1", commonDen);

  // Nominal numerators
  TString snumSee  = commonDen + " && amp_max[SEE]>20";
  TString snumMcp2 = commonDen + " && HVZS2>0 && amp_max[ZS2]>20";
  TString snumMcp5 = commonDen + " && amp_max[MiB3]>20";
  TString snumMcp4 = commonDen + " && amp_max[ZS1]>20";
  h4binpSee ->Project("numSee", "HVSEE", snumSee);
  h4binpMcp2->Project("numMcp2","HVZS2", snumMcp2);
  h4binpMcp5->Project("numMcp5","HVMiB3",snumMcp5);
  h4binpMcp4->Project("numMcp4","HVZS1", snumMcp4);

  cout << endl;
  cout << "-------------------------------------" << endl;
  cout << "check chiara: nominal " << endl;
  cout << "den = " << commonDen << endl;
  cout << "numSee  = " << snumSee  << endl;
  cout << "numMcp2 = " << snumMcp2 << endl;
  cout << "numMcp5 = " << snumMcp5 << endl;
  cout << "numMcp4 = " << snumMcp4 << endl;
  cout << "-------------------------------------" << endl;
  cout << endl;
  cout << endl;

  // efficiencies
  TGraphAsymmErrors* effSee  = new TGraphAsymmErrors(numSee, denSee);
  TGraphAsymmErrors* effMcp2 = new TGraphAsymmErrors(numMcp2,denMcp2);
  TGraphAsymmErrors* effMcp5 = new TGraphAsymmErrors(numMcp5,denMcp5);
  TGraphAsymmErrors* effMcp4 = new TGraphAsymmErrors(numMcp4,denMcp4);
  effSee->SetMarkerStyle(20);
  effSee->SetMarkerColor(6);
  effSee->SetLineColor(6);
  effMcp2->SetMarkerStyle(21);
  effMcp2->SetMarkerColor(2);
  effMcp2->SetLineColor(2);
  effMcp5->SetMarkerStyle(22);
  effMcp5->SetMarkerColor(3);
  effMcp5->SetLineColor(3);
  effMcp4->SetMarkerStyle(23);
  effMcp4->SetMarkerColor(4);
  effMcp4->SetLineColor(4);

  TLegend *leg;
  leg = new TLegend(0.1,0.5,0.4,0.8);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.05);
  leg->SetFillColor(0);
  leg->AddEntry(effSee,  "See",  "pl");
  leg->AddEntry(effMcp2, "ZS2",  "pl");
  leg->AddEntry(effMcp5, "MiB3", "pl");
  leg->AddEntry(effMcp4, "ZS1",  "pl");

  TCanvas* c1c = new TCanvas("c1c","c",1);
  c1c->SetGrid();
  TH2F* H2 = new TH2F("H2","",3500,0.,3500.,100,0.,1.);
  H2->GetXaxis()->SetTitle("Bias voltage [V]");
  H2->GetYaxis()->SetTitle("Efficiency");
  H2->Draw();
  effSee->Draw("Plsame"); 
  effMcp2->Draw("Plsame"); 
  effMcp5->Draw("Plsame"); 
  effMcp4->Draw("Plsame");
  leg->Draw();
  c1c->SaveAs("effH4.png");
  c1c->SaveAs("effH4.pdf");
}
	
