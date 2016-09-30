#include "TMath.h"
#include "TTree.h"
#include "TStyle.h"
#include "TROOT.h"
#include "TH1F.h"
#include "TF1.h"
#include "TGraph.h"
#include "TFile.h"

#include <iostream>

#define NRUNS 4        // binp3:7, binp4:3, binp1:3, binp2:4
#define NVARIABLES 2
#define mcp 3          // 0=BNP3, 1=BNP4, 2=BNP1, 3=BINP2  

void noiseFit() {

  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1);
  gStyle->SetOptStat(0);  
  gStyle->SetOptFit(111110); 
  gStyle->SetOptFile(1); 

  float runsF[NRUNS];
  TString runs[NRUNS];
  TString path[NRUNS];
  if (mcp==0) {
    runsF[0]=2339;  path[0]="RU1";
    runsF[1]=2340;  path[1]="RU1";
    runsF[2]=2341;  path[2]="RU2"; 
    runsF[3]=2363;  path[3]="RU4";
    runsF[4]=2364;  path[4]="RU4";
    runsF[5]=2365;  path[5]="RU4";
    runsF[6]=2366;  path[6]="RU4";
  }
  if (mcp==1) {
    runsF[0]=2339;  path[0]="RU1";    // only good run
    runsF[1]=2341;  path[1]="RU2"; 
    runsF[2]=2352;  path[2]="RU3";
  }
  if (mcp==2) {
    runsF[0]=2341;  path[0]="RU2"; 
    runsF[1]=2352;  path[1]="RU3";
    runsF[2]=2363;  path[2]="RU4";
  }
  if (mcp==3) {
    runsF[0]=2339;  path[0]="RU1"; 
    runsF[1]=2340;  path[1]="RU1";
    runsF[2]=2352;  path[2]="RU3";
    runsF[3]=2363;  path[3]="RU4";
  }
  for (int ii=0; ii<NRUNS; ii++) runs[ii] = Form("%d",(int)runsF[ii]);

  TString files[NRUNS];
  for (int ii=0; ii<NRUNS; ii++) files[ii]="btf2016_"+path[ii]+"_"+runs[ii]+".root";  

  TFile* fOut=new TFile("Histos.root","RECREATE");  
  TH1F* histos[NRUNS][NVARIABLES];    
  
  // ---------------------------------------------------
  TString variables[NVARIABLES];
  if (mcp==0) { 
    variables[0]="amp_max[BINP3]";   
    variables[1]="charge_sig[BINP3]";   
  }
  if (mcp==1) { 
    variables[0]="amp_max[BINP4]";   
    variables[1]="charge_sig[BINP4]";   
  }
  if (mcp==2) { 
    variables[0]="amp_max[BINP1]";   
    variables[1]="charge_sig[BINP1]";   
  }
  if (mcp==3) { 
    variables[0]="amp_max[BINP2]";   
    variables[1]="charge_sig[BINP2]";   
  }

  int nbins[NVARIABLES];
  nbins[0]=20;
  nbins[1]=125;  

  float range[NVARIABLES][2]; 
  range[0][0]=-5.;
  range[0][1]=15.;
  range[1][0]=-100.;
  range[1][1]=150.;

  for (int z=0;z<NVARIABLES;++z) {
    for (int i=0;i<NRUNS;++i) {
      histos[i][z]=new TH1F(variables[z]+"_"+runs[i],variables[z]+"_"+runs[i],nbins[z],range[z][0],range[z][1]);
      histos[i][z]->Sumw2();
    }
  }

  TFile *_file[NRUNS];
  TTree *T1[NRUNS];
  cout << endl;
  for (int i=0;i<NRUNS;++i) {
    _file[i]=TFile::Open(files[i]);
    cout << "reading file " << files[i] << endl;
    T1[i] = (TTree*)_file[i]->Get("h4");
  }

  // Fit results
  float meanAmpMax[NRUNS], meanCharge[NRUNS];
  float sigmaAmpMax[NRUNS], sigmaCharge[NRUNS];
  float chi2AmpMax[NRUNS], chi2Charge[NRUNS];

  TF1 *gausa = new TF1 ("gausa","[0]*exp(-1*(x-[1])*(x-[1])/2/[2]/[2])");
  for (int z=0;z<NVARIABLES;++z) {
    for (int i=0;i<NRUNS;++i) {

      // Histos
      fOut->cd();
      TString histoName=variables[z]+"_"+runs[i];
      std::cout << "Producing " << histoName << std::endl;
      if (T1[i]==0) {
	std::cout << "Species " << i << " Tree not found" << std::endl;
	return;
      }
      T1[i]->Project(histoName,variables[z],"adc_data<150");

      // Fit initialization
      int peakBin   = histos[i][z]->GetMaximumBin();
      double h_norm = histos[i][z]->GetMaximum();
      double h_rms  = histos[i][z]->GetRMS();
      double h_peak = histos[i][z]->GetBinCenter(peakBin);
      gausa->SetParameters(h_norm,h_peak,h_rms);

      // Fit
      histos[i][z]->Fit("gausa");
      if (z==0){
	meanAmpMax[i]  = gausa->GetParameter(1);
	sigmaAmpMax[i] = fabs(gausa->GetParameter(2));
        chi2AmpMax[i]  = gausa->GetChisquare()/gausa->GetNDF();
      } else if (z==1) {
	meanCharge[i]  = gausa->GetParameter(1);
	sigmaCharge[i] = fabs(gausa->GetParameter(2));
        chi2Charge[i]  = gausa->GetChisquare()/gausa->GetNDF();
      }
    }
  }
  delete gausa;

  cout << endl;
  cout << endl;
  cout << "-------------------------------" << endl;
  for (int i=0;i<NRUNS;++i) {
    cout << "Run " << runs[i] << " : " << endl;
    cout << "meanAmp: mu = " << meanAmpMax[i] << ", sigma = " << sigmaAmpMax[i] << ", chi2 = " << chi2AmpMax[i] << endl; 
    cout << "charge:  mu = " << meanCharge[i] << ", sigma = " << sigmaCharge[i] << ", chi2 = " << chi2Charge[i] << endl; 
  }
  cout << "-------------------------------" << endl;

  TGraph *ampMaxMean  = new TGraph(NRUNS,runsF,meanAmpMax);
  TGraph *ampMaxSigma = new TGraph(NRUNS,runsF,sigmaAmpMax);
  TGraph *ampMaxChi2  = new TGraph(NRUNS,runsF,chi2AmpMax);
  TGraph *chargeMean  = new TGraph(NRUNS,runsF,meanCharge);
  TGraph *chargeSigma = new TGraph(NRUNS,runsF,sigmaCharge);
  TGraph *chargeChi2  = new TGraph(NRUNS,runsF,chi2Charge);
  ampMaxMean ->SetMarkerStyle(20); 
  ampMaxSigma->SetMarkerStyle(20); 
  ampMaxChi2 ->SetMarkerStyle(20); 
  chargeMean ->SetMarkerStyle(20); 
  chargeSigma->SetMarkerStyle(20); 
  chargeChi2 ->SetMarkerStyle(20); 
  
  ampMaxMean  -> Write("ampMaxMean");
  ampMaxSigma -> Write("ampMaxSigma");
  ampMaxChi2  -> Write("ampMaxChi2");
  chargeMean  -> Write("chargeMean");
  chargeSigma -> Write("chargeSigma");
  chargeChi2  -> Write("chargeChi2");

  fOut->Write();
  fOut->Close();


  // Study of efficiency on 1 particle events, passing mib2 and rm2 selection. Done on selected runs
  cout << endl;
  cout << endl;
  cout << "-------------------------------------------- 1 particle efficiency " << endl;
  TFile *fileRefBinp124 = new TFile("btf2016_RU5_2378.root");
  TFile *fileRefBinp3   = new TFile("btf2016_RU2_2341.root");
  TTree *TrefBinp;
  TString myMCP;
  if (mcp==0) { TrefBinp = (TTree*)fileRefBinp3->Get("h4");   myMCP= Form("BINP3");}
  if (mcp==1) { TrefBinp = (TTree*)fileRefBinp124->Get("h4"); myMCP= Form("BINP4");}
  if (mcp==2) { TrefBinp = (TTree*)fileRefBinp124->Get("h4"); myMCP= Form("BINP1");}
  if (mcp==3) { TrefBinp = (TTree*)fileRefBinp124->Get("h4"); myMCP= Form("BINP2");}
  TH1F *H_den   = new TH1F("H_den","H_den",    1,-50000,50000);
  TH1F *H_numAM = new TH1F("H_numAM","H_numAM",1,-50000,50000);
  TH1F *H_numCS = new TH1F("H_numCS","H_numCS",1,-50000,50000);
  TrefBinp->Project("H_den",  "amp_max["+myMCP+"]","adc_data>200 && adc_data<700 && amp_max[MiB2]>200 && amp_max[Rm2]>200 && amp_max[Rm2]<1200");
  TrefBinp->Project("H_numAM","amp_max["+myMCP+"]","adc_data>200 && adc_data<700 && amp_max[MiB2]>200 && amp_max[Rm2]>200 && amp_max[Rm2]<1200 && amp_max["+myMCP+"]>16.");         
  TrefBinp->Project("H_numCS","amp_max["+myMCP+"]","adc_data>200 && adc_data<700 && amp_max[MiB2]>200 && amp_max[Rm2]>200 && amp_max[Rm2]<1200 && charge_sig["+myMCP+"]>170");    
  cout << "amp_max = " << H_numAM->Integral()/H_den->Integral() << ", charge_sig = " << H_numCS->Integral()/H_den->Integral() << endl;
  delete H_den;
  delete H_numAM;
  delete H_numCS;
}

