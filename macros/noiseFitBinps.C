#include "TMath.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TH1F.h"
#include "TF1.h"
#include "TGraph.h"
#include "TFile.h"

#include <iostream>

#define mcp 4          // da cambiare: 1 -> 4

void noiseFitBinps() {
  
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1);
  gStyle->SetOptStat(0);  
  gStyle->SetOptFit(111110); 
  gStyle->SetOptFile(1); 
  
  TFile *file;
  if (mcp==1) file = new TFile("/cmsrm/pc28_2/crovelli/data/imcp/binps/newRecoWindowV4/btf2016_HVscanBinp1.root");
  if (mcp==2) file = new TFile("/cmsrm/pc28_2/crovelli/data/imcp/binps/newRecoWindowV4/btf2016_HVscanBinp4.root");
  if (mcp==3) file = new TFile("/cmsrm/pc28_2/crovelli/data/imcp/binps/newRecoWindowV4/btf2016_HVscanBinp3.root");
  if (mcp==4) file = new TFile("/cmsrm/pc28_2/crovelli/data/imcp/binps/newRecoWindowV4/btf2016_HVscanBinp4.root");

  TTree *T1 = (TTree*)file->Get("h4");
  
  TH1F *histo  = new TH1F("histo", "histo", 80,-20.,20.);
  histo->Sumw2();

  if (mcp==1) T1->Project("histo", "amp_max[BINP1]","run==2363 && HVBINP1==2400 && adc_data<150");
  if (mcp==2) T1->Project("histo", "amp_max[BINP2]","run==2352 && HVBINP2==1400 && adc_data<150");
  if (mcp==3) T1->Project("histo", "amp_max[BINP3]","run==2341 && HVBINP3==1400 && adc_data<150");
  if (mcp==4) T1->Project("histo", "amp_max[BINP4]","run==2352 && HVBINP4==2400 && adc_data<150");

  TF1 *gausa = new TF1 ("gausa","[0]*exp(-1*(x-[1])*(x-[1])/2/[2]/[2])");

  // Fit initialization
  int peakBin   = histo->GetMaximumBin();
  double h_norm = histo->GetMaximum();
  double h_rms  = histo->GetRMS();
  double h_peak = histo->GetBinCenter(peakBin);
  gausa->SetParameters(h_norm,h_peak,h_rms);

  // Fit
  if (mcp<4)
    histo->Fit("gausa");
  else
    histo->Fit("gausa","","",-20.,8.);
  float meanAmpMax  = gausa->GetParameter(1);
  float sigmaAmpMax = fabs(gausa->GetParameter(2));
  float chi2AmpMax  = gausa->GetChisquare()/gausa->GetNDF();

  cout << endl;
  cout << "-------------------------------" << endl;
  cout << "mu = " << meanAmpMax << ", sigma = " << sigmaAmpMax << ", chi2 = " << chi2AmpMax << endl; 
  cout << "mu + 5sigma = " << meanAmpMax + 5.*sigmaAmpMax << endl; 
}

