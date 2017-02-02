#include "TMath.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TH1F.h"
#include "TF1.h"
#include "TGraph.h"
#include "TFile.h"

#include <iostream>

#define mcp 1          // da cambiare: 1 -> 9

void noiseFitCam() {
  
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1);
  gStyle->SetOptStat(0);  
  gStyle->SetOptFit(111110); 
  gStyle->SetOptFile(1); 
  
  TFile *file;
  if (mcp==1) file = new TFile("/cmsrm/pc28_2/crovelli/data/imcp/cameroni/newRecoWindowV4/btf2016_HVscanMib25_MID1000.root");
  if (mcp==2) file = new TFile("/cmsrm/pc28_2/crovelli/data/imcp/cameroni/newRecoWindowV4/btf2016_HVscanMib25_MID1200.root");
  if (mcp==3) file = new TFile("/cmsrm/pc28_2/crovelli/data/imcp/cameroni/newRecoWindowV4/btf2016_HVscanMib25_MID700.root");
  if (mcp==4) file = new TFile("/cmsrm/pc28_2/crovelli/data/imcp/cameroni/newRecoWindowV4/btf2016_HVscanRm8_MID1000.root");
  if (mcp==5) file = new TFile("/cmsrm/pc28_2/crovelli/data/imcp/cameroni/newRecoWindowV4/btf2016_HVscanRm8_MID1200.root");
  if (mcp==6) file = new TFile("/cmsrm/pc28_2/crovelli/data/imcp/cameroni/newRecoWindowV4/btf2016_HVscanRm8_MID700.root");
  if (mcp==7) file = new TFile("/cmsrm/pc28_2/crovelli/data/imcp/cameroni/newRecoWindowV4/btf2016_HVscanRm5_MID1000.root");
  if (mcp==8) file = new TFile("/cmsrm/pc28_2/crovelli/data/imcp/cameroni/newRecoWindowV4/btf2016_HVscanRm5_MID1200.root");
  if (mcp==9) file = new TFile("/cmsrm/pc28_2/crovelli/data/imcp/cameroni/newRecoWindowV4/btf2016_HVscanRm5_MID700.root");

  TTree *T1 = (TTree*)file->Get("h4");
  
  TH1F *histo  = new TH1F("histo", "histo", 80,-20.,20.);
  histo->Sumw2();

  if (mcp==1) T1->Project("histo", "amp_max[M25]",  "HVAMP==1000 && HV25==3500 && adc_data<150");
  if (mcp==2) T1->Project("histo", "amp_max[M25]",  "HVAMP==1200 && HV25==3600 && adc_data<150");
  if (mcp==3) T1->Project("histo", "amp_max[M25]",  "HVAMP==700  && HV25==3200 && adc_data<150");
  //
  if (mcp==4) T1->Project("histo", "amp_max[M8]",   "HVAMP==1000 && HV8==2600 && adc_data<150");
  if (mcp==5) T1->Project("histo", "amp_max[M8]",   "HVAMP==1200 && HV8==2800 && adc_data<150");
  if (mcp==6) T1->Project("histo", "amp_max[M8]",   "HVAMP==700  && HV8==2300 && adc_data<150");
  //
  if (mcp==7) T1->Project("histo", "amp_max[M5]",   "HVAMP==1000 && HV5==2600 && adc_data<150");
  if (mcp==8) T1->Project("histo", "amp_max[M5]",   "HVAMP==1200 && HV5==2800 && adc_data<150");
  if (mcp==9) T1->Project("histo", "amp_max[M5]",   "HVAMP==700  && HV5==2300 && adc_data<150");

  TF1 *gausa = new TF1 ("gausa","[0]*exp(-1*(x-[1])*(x-[1])/2/[2]/[2])");
  histo->Fit("gausa");

  // Fit initialization
  int peakBin   = histo->GetMaximumBin();
  double h_norm = histo->GetMaximum();
  double h_rms  = histo->GetRMS();
  double h_peak = histo->GetBinCenter(peakBin);
  gausa->SetParameters(h_norm,h_peak,h_rms);

  // Fit
  histo->Fit("gausa");
  float meanAmpMax  = gausa->GetParameter(1);
  float sigmaAmpMax = fabs(gausa->GetParameter(2));
  float chi2AmpMax  = gausa->GetChisquare()/gausa->GetNDF();

  cout << endl;
  cout << "-------------------------------" << endl;
  cout << "mu = " << meanAmpMax << ", sigma = " << sigmaAmpMax << ", chi2 = " << chi2AmpMax << endl; 
  cout << "mu + 5sigma = " << meanAmpMax + 5.*sigmaAmpMax << endl; 
}

