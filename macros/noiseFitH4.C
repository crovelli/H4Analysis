#include "TMath.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TH1F.h"
#include "TF1.h"
#include "TGraph.h"
#include "TFile.h"

#include <iostream>

void noiseFitH4() {
  
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1);
  gStyle->SetOptStat(0);  
  gStyle->SetOptFit(111110); 
  gStyle->SetOptFile(1); 
  
  TFile *file = new TFile("h42014_50GeV_scan6_757.root");
  TTree *T1 = (TTree*)file->Get("h4");
  
  TH1F *histo  = new TH1F("histo", "histo", 80,-40.,40.);
  histo->Sumw2();

  T1->Project("histo", "amp_max[SEE]");
  //T1->Project("histo", "amp_max[ZS1]");
  //T1->Project("histo", "amp_max[ZS2]");
  //T1->Project("histo", "amp_max[MiB3]");

  TF1 *gausa = new TF1 ("gausa","[0]*exp(-1*(x-[1])*(x-[1])/2/[2]/[2])");

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

