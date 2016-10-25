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

void HodoCam() {

  gStyle->SetOptStat(0);

  // inputs
  TFile* inFileMib10_700  = new TFile("/cmsrm/pc28_2/crovelli/data/imcp/cameroni/btf2016_HVscanMib10_MID700.root");
  TFile* inFileMib10_1000 = new TFile("/cmsrm/pc28_2/crovelli/data/imcp/cameroni/btf2016_HVscanMib10_MID1000.root");

  TFile* inFileMib25_700  = new TFile("/cmsrm/pc28_2/crovelli/data/imcp/cameroni/btf2016_HVscanMib25_MID700.root");
  TFile* inFileMib25_1000 = new TFile("/cmsrm/pc28_2/crovelli/data/imcp/cameroni/btf2016_HVscanMib25_MID1000.root");
  TFile* inFileMib25_1200 = new TFile("/cmsrm/pc28_2/crovelli/data/imcp/cameroni/btf2016_HVscanMib25_MID1200.root");

  TFile* inFileRm5_700  = new TFile("/cmsrm/pc28_2/crovelli/data/imcp/cameroni/btf2016_HVscanRm5_MID700.root");
  TFile* inFileRm5_1000 = new TFile("/cmsrm/pc28_2/crovelli/data/imcp/cameroni/btf2016_HVscanRm5_MID1000.root");
  TFile* inFileRm5_1200 = new TFile("/cmsrm/pc28_2/crovelli/data/imcp/cameroni/btf2016_HVscanRm5_MID1200.root");

  TFile* inFileRm8_700  = new TFile("/cmsrm/pc28_2/crovelli/data/imcp/cameroni/btf2016_HVscanRm8_MID700.root");
  TFile* inFileRm8_1000 = new TFile("/cmsrm/pc28_2/crovelli/data/imcp/cameroni/btf2016_HVscanRm8_MID1000.root");
  TFile* inFileRm8_1200 = new TFile("/cmsrm/pc28_2/crovelli/data/imcp/cameroni/btf2016_HVscanRm8_MID1200.root");

  TTree* h4Mib10_700  = (TTree*)inFileMib10_700->Get("h4");
  TTree* h4Mib10_1000 = (TTree*)inFileMib10_1000->Get("h4");

  TTree* h4Mib25_700  = (TTree*)inFileMib25_700->Get("h4");
  TTree* h4Mib25_1000 = (TTree*)inFileMib25_1000->Get("h4");
  TTree* h4Mib25_1200 = (TTree*)inFileMib25_1200->Get("h4");

  TTree* h4Rm5_700  = (TTree*)inFileRm5_700->Get("h4");
  TTree* h4Rm5_1000 = (TTree*)inFileRm5_1000->Get("h4");
  TTree* h4Rm5_1200 = (TTree*)inFileRm5_1200->Get("h4");

  TTree* h4Rm8_700  = (TTree*)inFileRm8_700->Get("h4");
  TTree* h4Rm8_1000 = (TTree*)inFileRm8_1000->Get("h4");
  TTree* h4Rm8_1200 = (TTree*)inFileRm8_1200->Get("h4");


  // all runs
  float runsMib10_700[10]  = { 2409, 2410, 2411, 2412, 2413, 2414, 2415, 2432, 2433, 2434 };
  float runsMib10_1000[12] = { 2416, 2417, 2418, 2419, 2420, 2421, 2422, 2423, 2424, 2425, 2435, 2436 };

  float runsMib25_700[12]  = { 2386, 2387, 2388, 2389, 2392, 2393, 2394, 2395, 2396, 2426, 2427, 2428 };
  float runsMib25_1000[15] = { 2391, 2397, 2398, 2399, 2401, 2402, 2403, 2404, 2405, 2406, 2407, 2408, 2429, 2430, 2431 };
  float runsMib25_1200[13] = { 2517, 2518, 2519, 2520, 2521, 2522, 2523, 2524, 2525, 2526, 2527, 2528, 2529 };

  float runsRm5_700[8]  = { 2470, 2471, 2472, 2473, 2474, 2491, 2492, 2493 };
  float runsRm5_1000[8] = { 2475, 2476, 2477, 2478, 2479, 2488, 2489, 2490 };
  float runsRm5_1200[8] = { 2480, 2481, 2482, 2483, 2484, 2485, 2486, 2487 };

  float runsRm8_700[8]  = { 2455, 2456, 2457, 2458, 2459, 2494, 2495, 2496 };
  float runsRm8_1000[8] = { 2460, 2461, 2462, 2463, 2464, 2497, 2498, 2499 };
  float runsRm8_1200[8] = { 2465, 2466, 2467, 2468, 2469, 2500, 2501, 2502 };


  // histos with the two coordinates: MiBs
  TH1F* xMib10_700[10];  
  for (int ii=0; ii<10; ii++) {
    TString histoS;
    histoS.Form("xMib10_700[%d]",ii);
    xMib10_700[ii] = new TH1F(histoS, histoS, 32, -1.5, 30.5);
  }

  TH1F* yMib10_700[10];  
  for (int ii=0; ii<10; ii++) {
    TString histoS;
    histoS.Form("yMib10_700[%d]",ii);
    yMib10_700[ii] = new TH1F(histoS, histoS, 32, -1.5, 30.5);
  }

  TH1F* xMib10_1000[12];
  for (int ii=0; ii<12; ii++) {
    TString histoS;
    histoS.Form("xMib10_1000[%d]",ii);
    xMib10_1000[ii] = new TH1F(histoS, histoS, 32, -1.5, 30.5);
  }

  TH1F* yMib10_1000[12];
  for (int ii=0; ii<12; ii++) {
    TString histoS;
    histoS.Form("yMib10_1000[%d]",ii);
    yMib10_1000[ii] = new TH1F(histoS, histoS, 32, -1.5, 30.5);
  }

  TH1F* xMib25_700[12];  
  for (int ii=0; ii<12; ii++) {
    TString histoS;
    histoS.Form("xMib25_700[%d]",ii);
    xMib25_700[ii] = new TH1F(histoS, histoS, 32, -1.5, 30.5);
  }

  TH1F* yMib25_700[12];  
  for (int ii=0; ii<12; ii++) {
    TString histoS;
    histoS.Form("yMib25_700[%d]",ii);
    yMib25_700[ii] = new TH1F(histoS, histoS, 32, -1.5, 30.5);
  }

  TH1F* xMib25_1000[15];
  for (int ii=0; ii<15; ii++) {
    TString histoS;
    histoS.Form("xMib25_1000[%d]",ii);
    xMib25_1000[ii] = new TH1F(histoS, histoS, 32, -1.5, 30.5);
  }

  TH1F* yMib25_1000[15];
  for (int ii=0; ii<15; ii++) {
    TString histoS;
    histoS.Form("yMib25_1000[%d]",ii);
    yMib25_1000[ii] = new TH1F(histoS, histoS, 32, -1.5, 30.5);
  }

  TH1F* xMib25_1200[13];
  for (int ii=0; ii<13; ii++) {
    TString histoS;
    histoS.Form("xMib25_1200[%d]",ii);
    xMib25_1200[ii] = new TH1F(histoS, histoS, 32, -1.5, 30.5);
  }

  TH1F* yMib25_1200[13];
  for (int ii=0; ii<13; ii++) {
    TString histoS;
    histoS.Form("yMib25_1200[%d]",ii);
    yMib25_1200[ii] = new TH1F(histoS, histoS, 32, -1.5, 30.5);
  }

  // histos with the two coordinates: Rms
  TH1F* xRm5_700[8];  
  for (int ii=0; ii<8; ii++) {
    TString histoS;
    histoS.Form("xRm5_700[%d]",ii);
    xRm5_700[ii] = new TH1F(histoS, histoS, 32, -1.5, 30.5);
  }

  TH1F* yRm5_700[8];  
  for (int ii=0; ii<8; ii++) {
    TString histoS;
    histoS.Form("yRm5_700[%d]",ii);
    yRm5_700[ii] = new TH1F(histoS, histoS, 32, -1.5, 30.5);
  }

  TH1F* xRm5_1000[8];
  for (int ii=0; ii<8; ii++) {
    TString histoS;
    histoS.Form("xRm5_1000[%d]",ii);
    xRm5_1000[ii] = new TH1F(histoS, histoS, 32, -1.5, 30.5);
  }

  TH1F* yRm5_1000[8];
  for (int ii=0; ii<8; ii++) {
    TString histoS;
    histoS.Form("yRm5_1000[%d]",ii);
    yRm5_1000[ii] = new TH1F(histoS, histoS, 32, -1.5, 30.5);
  }

  TH1F* xRm5_1200[8];
  for (int ii=0; ii<8; ii++) {
    TString histoS;
    histoS.Form("xRm5_1200[%d]",ii);
    xRm5_1200[ii] = new TH1F(histoS, histoS, 32, -1.5, 30.5);
  }

  TH1F* yRm5_1200[8];
  for (int ii=0; ii<8; ii++) {
    TString histoS;
    histoS.Form("yRm5_1200[%d]",ii);
    yRm5_1200[ii] = new TH1F(histoS, histoS, 32, -1.5, 30.5);
  }

  TH1F* xRm8_700[8];  
  for (int ii=0; ii<8; ii++) {
    TString histoS;
    histoS.Form("xRm8_700[%d]",ii);
    xRm8_700[ii] = new TH1F(histoS, histoS, 32, -1.5, 30.5);
  }

  TH1F* yRm8_700[8];  
  for (int ii=0; ii<8; ii++) {
    TString histoS;
    histoS.Form("yRm8_700[%d]",ii);
    yRm8_700[ii] = new TH1F(histoS, histoS, 32, -1.5, 30.5);
  }

  TH1F* xRm8_1000[8];
  for (int ii=0; ii<8; ii++) {
    TString histoS;
    histoS.Form("xRm8_1000[%d]",ii);
    xRm8_1000[ii] = new TH1F(histoS, histoS, 32, -1.5, 30.5);
  }

  TH1F* yRm8_1000[8];
  for (int ii=0; ii<8; ii++) {
    TString histoS;
    histoS.Form("yRm8_1000[%d]",ii);
    yRm8_1000[ii] = new TH1F(histoS, histoS, 32, -1.5, 30.5);
  }

  TH1F* xRm8_1200[8];
  for (int ii=0; ii<8; ii++) {
    TString histoS;
    histoS.Form("xRm8_1200[%d]",ii);
    xRm8_1200[ii] = new TH1F(histoS, histoS, 32, -1.5, 30.5);
  }

  TH1F* yRm8_1200[8];
  for (int ii=0; ii<8; ii++) {
    TString histoS;
    histoS.Form("yRm8_1200[%d]",ii);
    yRm8_1200[ii] = new TH1F(histoS, histoS, 32, -1.5, 30.5);
  }

  // denominators
  TString commonDen = "adc_data>200 && adc_data<700 && amp_max[MiB2]>200 && amp_max[Rm2]>200 && amp_max[Rm2]<1200";
  TString commonDen700  = commonDen + " && HVAMP==700";
  TString commonDen1000 = commonDen + " && HVAMP==1000";
  TString commonDen1200 = commonDen + " && HVAMP==1200";

  float xMeanMib10_700[10], xRmsMib10_700[10];
  for (int ii=0; ii<10; ii++) {
    TString histoS;
    histoS.Form("xMib10_700[%d]",ii);
    TString theRunCut;
    theRunCut.Form(" && run==%d",(int)runsMib10_700[ii]);
    TString theCut = commonDen700+theRunCut;
    h4Mib10_700 ->Project(histoS, "X",theCut);
    xMeanMib10_700[ii] = xMib10_700[ii] -> GetMean();
    xRmsMib10_700[ii]  = xMib10_700[ii] -> GetRMS();
  }

  float yMeanMib10_700[10], yRmsMib10_700[10];
  for (int ii=0; ii<10; ii++) {
    TString histoS;
    histoS.Form("yMib10_700[%d]",ii);
    TString theRunCut;
    theRunCut.Form(" && run==%d",(int)runsMib10_700[ii]);
    TString theCut = commonDen700+theRunCut;
    h4Mib10_700 ->Project(histoS, "Y",theCut);
    yMeanMib10_700[ii] = yMib10_700[ii] -> GetMean();
    yRmsMib10_700[ii]  = yMib10_700[ii] -> GetRMS();
  }

  float xMeanMib10_1000[12], xRmsMib10_1000[12];
  for (int ii=0; ii<12; ii++) {
    TString histoS;
    histoS.Form("xMib10_1000[%d]",ii);
    TString theRunCut;
    theRunCut.Form(" && run==%d",(int)runsMib10_1000[ii]);
    TString theCut = commonDen1000+theRunCut;
    h4Mib10_1000 ->Project(histoS, "X",theCut);
    xMeanMib10_1000[ii] = xMib10_1000[ii] -> GetMean();
    xRmsMib10_1000[ii]  = xMib10_1000[ii] -> GetRMS();
  }

  float yMeanMib10_1000[12], yRmsMib10_1000[12];
  for (int ii=0; ii<12; ii++) {
    TString histoS;
    histoS.Form("yMib10_1000[%d]",ii);
    TString theRunCut;
    theRunCut.Form(" && run==%d",(int)runsMib10_1000[ii]);
    TString theCut = commonDen1000+theRunCut;
    h4Mib10_1000 ->Project(histoS, "Y",theCut);
    yMeanMib10_1000[ii] = yMib10_1000[ii] -> GetMean();
    yRmsMib10_1000[ii]  = yMib10_1000[ii] -> GetRMS();
  }

  float xMeanMib25_700[12], xRmsMib25_700[12];
  for (int ii=0; ii<12; ii++) {
    TString histoS;
    histoS.Form("xMib25_700[%d]",ii);
    TString theRunCut;
    theRunCut.Form(" && run==%d",(int)runsMib25_700[ii]);
    TString theCut = commonDen700+theRunCut;
    h4Mib25_700 ->Project(histoS, "X",theCut);
    xMeanMib25_700[ii] = xMib25_700[ii] -> GetMean();
    xRmsMib25_700[ii]  = xMib25_700[ii] -> GetRMS();
  }

  float yMeanMib25_700[12], yRmsMib25_700[12];
  for (int ii=0; ii<12; ii++) {
    TString histoS;
    histoS.Form("yMib25_700[%d]",ii);
    TString theRunCut;
    theRunCut.Form(" && run==%d",(int)runsMib25_700[ii]);
    TString theCut = commonDen700+theRunCut;
    h4Mib25_700 ->Project(histoS, "Y",theCut);
    yMeanMib25_700[ii] = yMib25_700[ii] -> GetMean();
    yRmsMib25_700[ii]  = yMib25_700[ii] -> GetRMS();
  }

  float xMeanMib25_1000[15], xRmsMib25_1000[15];
  for (int ii=0; ii<15; ii++) {
    TString histoS;
    histoS.Form("xMib25_1000[%d]",ii);
    TString theRunCut;
    theRunCut.Form(" && run==%d",(int)runsMib25_1000[ii]);
    TString theCut = commonDen1000+theRunCut;
    h4Mib25_1000 ->Project(histoS, "X",theCut);
    xMeanMib25_1000[ii] = xMib25_1000[ii] -> GetMean();
    xRmsMib25_1000[ii]  = xMib25_1000[ii] -> GetRMS();
  }

  float yMeanMib25_1000[15], yRmsMib25_1000[15];
  for (int ii=0; ii<15; ii++) {
    TString histoS;
    histoS.Form("yMib25_1000[%d]",ii);
    TString theRunCut;
    theRunCut.Form(" && run==%d",(int)runsMib25_1000[ii]);
    TString theCut = commonDen1000+theRunCut;
    h4Mib25_1000 ->Project(histoS, "Y",theCut);
    yMeanMib25_1000[ii] = yMib25_1000[ii] -> GetMean();
    yRmsMib25_1000[ii]  = yMib25_1000[ii] -> GetRMS();
  }

  float xMeanMib25_1200[13], xRmsMib25_1200[13];
  for (int ii=0; ii<13; ii++) {
    TString histoS;
    histoS.Form("xMib25_1200[%d]",ii);
    TString theRunCut;
    theRunCut.Form(" && run==%d",(int)runsMib25_1200[ii]);
    TString theCut = commonDen1200+theRunCut;
    h4Mib25_1200 ->Project(histoS, "X",theCut);
    xMeanMib25_1200[ii] = xMib25_1200[ii] -> GetMean();
    xRmsMib25_1200[ii]  = xMib25_1200[ii] -> GetRMS();
  }

  float yMeanMib25_1200[13], yRmsMib25_1200[13];
  for (int ii=0; ii<13; ii++) {
    TString histoS;
    histoS.Form("yMib25_1200[%d]",ii);
    TString theRunCut;
    theRunCut.Form(" && run==%d",(int)runsMib25_1200[ii]);
    TString theCut = commonDen1200+theRunCut;
    h4Mib25_1200 ->Project(histoS, "Y",theCut);
    yMeanMib25_1200[ii] = yMib25_1200[ii] -> GetMean();
    yRmsMib25_1200[ii]  = yMib25_1200[ii] -> GetRMS();
  }

  float xMeanRm5_700[8], xRmsRm5_700[8];
  for (int ii=0; ii<8; ii++) {
    TString histoS;
    histoS.Form("xRm5_700[%d]",ii);
    TString theRunCut;
    theRunCut.Form(" && run==%d",(int)runsRm5_700[ii]);
    TString theCut = commonDen700+theRunCut;
    h4Rm5_700 ->Project(histoS, "X",theCut);
    xMeanRm5_700[ii] = xRm5_700[ii] -> GetMean();
    xRmsRm5_700[ii]  = xRm5_700[ii] -> GetRMS();
  }

  float yMeanRm5_700[8], yRmsRm5_700[8];
  for (int ii=0; ii<8; ii++) {
    TString histoS;
    histoS.Form("yRm5_700[%d]",ii);
    TString theRunCut;
    theRunCut.Form(" && run==%d",(int)runsRm5_700[ii]);
    TString theCut = commonDen700+theRunCut;
    h4Rm5_700 ->Project(histoS, "Y",theCut);
    yMeanRm5_700[ii] = yRm5_700[ii] -> GetMean();
    yRmsRm5_700[ii]  = yRm5_700[ii] -> GetRMS();
  }

  float xMeanRm5_1000[8], xRmsRm5_1000[8];
  for (int ii=0; ii<8; ii++) {
    TString histoS;
    histoS.Form("xRm5_1000[%d]",ii);
    TString theRunCut;
    theRunCut.Form(" && run==%d",(int)runsRm5_1000[ii]);
    TString theCut = commonDen1000+theRunCut;
    h4Rm5_1000 ->Project(histoS, "X",theCut);
    xMeanRm5_1000[ii] = xRm5_1000[ii] -> GetMean();
    xRmsRm5_1000[ii]  = xRm5_1000[ii] -> GetRMS();
  }

  float yMeanRm5_1000[8], yRmsRm5_1000[8];
  for (int ii=0; ii<8; ii++) {
    TString histoS;
    histoS.Form("yRm5_1000[%d]",ii);
    TString theRunCut;
    theRunCut.Form(" && run==%d",(int)runsRm5_1000[ii]);
    TString theCut = commonDen1000+theRunCut;
    h4Rm5_1000 ->Project(histoS, "Y",theCut);
    yMeanRm5_1000[ii] = yRm5_1000[ii] -> GetMean();
    yRmsRm5_1000[ii]  = yRm5_1000[ii] -> GetRMS();
  }

  float xMeanRm5_1200[8], xRmsRm5_1200[8];
  for (int ii=0; ii<8; ii++) {
    TString histoS;
    histoS.Form("xRm5_1200[%d]",ii);
    TString theRunCut;
    theRunCut.Form(" && run==%d",(int)runsRm5_1200[ii]);
    TString theCut = commonDen1200+theRunCut;
    h4Rm5_1200 ->Project(histoS, "X",theCut);
    xMeanRm5_1200[ii] = xRm5_1200[ii] -> GetMean();
    xRmsRm5_1200[ii]  = xRm5_1200[ii] -> GetRMS();
  }

  float yMeanRm5_1200[8], yRmsRm5_1200[8];
  for (int ii=0; ii<8; ii++) {
    TString histoS;
    histoS.Form("yRm5_1200[%d]",ii);
    TString theRunCut;
    theRunCut.Form(" && run==%d",(int)runsRm5_1200[ii]);
    TString theCut = commonDen1200+theRunCut;
    h4Rm5_1200 ->Project(histoS, "Y",theCut);
    yMeanRm5_1200[ii] = yRm5_1200[ii] -> GetMean();
    yRmsRm5_1200[ii]  = yRm5_1200[ii] -> GetRMS();
  }

  float xMeanRm8_700[8], xRmsRm8_700[8];
  for (int ii=0; ii<8; ii++) {
    TString histoS;
    histoS.Form("xRm8_700[%d]",ii);
    TString theRunCut;
    theRunCut.Form(" && run==%d",(int)runsRm8_700[ii]);
    TString theCut = commonDen700+theRunCut;
    h4Rm8_700 ->Project(histoS, "X",theCut);
    xMeanRm8_700[ii] = xRm8_700[ii] -> GetMean();
    xRmsRm8_700[ii]  = xRm8_700[ii] -> GetRMS();
  }

  float yMeanRm8_700[8], yRmsRm8_700[8];
  for (int ii=0; ii<8; ii++) {
    TString histoS;
    histoS.Form("yRm8_700[%d]",ii);
    TString theRunCut;
    theRunCut.Form(" && run==%d",(int)runsRm8_700[ii]);
    TString theCut = commonDen700+theRunCut;
    h4Rm8_700 ->Project(histoS, "Y",theCut);
    yMeanRm8_700[ii] = yRm8_700[ii] -> GetMean();
    yRmsRm8_700[ii]  = yRm8_700[ii] -> GetRMS();
  }

  float xMeanRm8_1000[8], xRmsRm8_1000[8];
  for (int ii=0; ii<8; ii++) {
    TString histoS;
    histoS.Form("xRm8_1000[%d]",ii);
    TString theRunCut;
    theRunCut.Form(" && run==%d",(int)runsRm8_1000[ii]);
    TString theCut = commonDen1000+theRunCut;
    h4Rm8_1000 ->Project(histoS, "X",theCut);
    xMeanRm8_1000[ii] = xRm8_1000[ii] -> GetMean();
    xRmsRm8_1000[ii]  = xRm8_1000[ii] -> GetRMS();
  }

  float yMeanRm8_1000[8], yRmsRm8_1000[8];
  for (int ii=0; ii<8; ii++) {
    TString histoS;
    histoS.Form("yRm8_1000[%d]",ii);
    TString theRunCut;
    theRunCut.Form(" && run==%d",(int)runsRm8_1000[ii]);
    TString theCut = commonDen1000+theRunCut;
    h4Rm8_1000 ->Project(histoS, "Y",theCut);
    yMeanRm8_1000[ii] = yRm8_1000[ii] -> GetMean();
    yRmsRm8_1000[ii]  = yRm8_1000[ii] -> GetRMS();
  }

  float xMeanRm8_1200[8], xRmsRm8_1200[8];
  for (int ii=0; ii<8; ii++) {
    TString histoS;
    histoS.Form("xRm8_1200[%d]",ii);
    TString theRunCut;
    theRunCut.Form(" && run==%d",(int)runsRm8_1200[ii]);
    TString theCut = commonDen1200+theRunCut;
    h4Rm8_1200 ->Project(histoS, "X",theCut);
    xMeanRm8_1200[ii] = xRm8_1200[ii] -> GetMean();
    xRmsRm8_1200[ii]  = xRm8_1200[ii] -> GetRMS();
  }

  float yMeanRm8_1200[8], yRmsRm8_1200[8];
  for (int ii=0; ii<8; ii++) {
    TString histoS;
    histoS.Form("yRm8_1200[%d]",ii);
    TString theRunCut;
    theRunCut.Form(" && run==%d",(int)runsRm8_1200[ii]);
    TString theCut = commonDen1200+theRunCut;
    h4Rm8_1200 ->Project(histoS, "Y",theCut);
    yMeanRm8_1200[ii] = yRm8_1200[ii] -> GetMean();
    yRmsRm8_1200[ii]  = yRm8_1200[ii] -> GetRMS();
  }



  // history plots
  TGraph* G_xMeanMib10_700 = new TGraph(10, runsMib10_700, xMeanMib10_700);
  TGraph* G_yMeanMib10_700 = new TGraph(10, runsMib10_700, yMeanMib10_700);
  TGraph* G_xRmsMib10_700  = new TGraph(10, runsMib10_700, xRmsMib10_700);
  TGraph* G_yRmsMib10_700  = new TGraph(10, runsMib10_700, yRmsMib10_700);
  G_xMeanMib10_700->SetMarkerStyle(20);
  G_xMeanMib10_700->SetMarkerColor(1);
  G_yMeanMib10_700->SetMarkerStyle(21);
  G_yMeanMib10_700->SetMarkerColor(2);
  G_xRmsMib10_700->SetMarkerStyle(20);
  G_xRmsMib10_700->SetMarkerColor(1);
  G_yRmsMib10_700->SetMarkerStyle(21);
  G_yRmsMib10_700->SetMarkerColor(2);

  TGraph* G_xMeanMib10_1000 = new TGraph(12, runsMib10_1000, xMeanMib10_1000);
  TGraph* G_yMeanMib10_1000 = new TGraph(12, runsMib10_1000, yMeanMib10_1000);
  TGraph* G_xRmsMib10_1000  = new TGraph(12, runsMib10_1000, xRmsMib10_1000);
  TGraph* G_yRmsMib10_1000  = new TGraph(12, runsMib10_1000, yRmsMib10_1000);
  G_xMeanMib10_1000->SetMarkerStyle(20);
  G_xMeanMib10_1000->SetMarkerColor(1);
  G_yMeanMib10_1000->SetMarkerStyle(21);
  G_yMeanMib10_1000->SetMarkerColor(2);
  G_xRmsMib10_1000->SetMarkerStyle(20);
  G_xRmsMib10_1000->SetMarkerColor(1);
  G_yRmsMib10_1000->SetMarkerStyle(21);
  G_yRmsMib10_1000->SetMarkerColor(2);

  TGraph* G_xMeanMib25_700 = new TGraph(12, runsMib25_700, xMeanMib25_700);
  TGraph* G_yMeanMib25_700 = new TGraph(12, runsMib25_700, yMeanMib25_700);
  TGraph* G_xRmsMib25_700  = new TGraph(12, runsMib25_700, xRmsMib25_700);
  TGraph* G_yRmsMib25_700  = new TGraph(12, runsMib25_700, yRmsMib25_700);
  G_xMeanMib25_700->SetMarkerStyle(20);
  G_xMeanMib25_700->SetMarkerColor(1);
  G_yMeanMib25_700->SetMarkerStyle(21);
  G_yMeanMib25_700->SetMarkerColor(2);
  G_xRmsMib25_700->SetMarkerStyle(20);
  G_xRmsMib25_700->SetMarkerColor(1);
  G_yRmsMib25_700->SetMarkerStyle(21);
  G_yRmsMib25_700->SetMarkerColor(2);

  TGraph* G_xMeanMib25_1000 = new TGraph(15, runsMib25_1000, xMeanMib25_1000);
  TGraph* G_yMeanMib25_1000 = new TGraph(15, runsMib25_1000, yMeanMib25_1000);
  TGraph* G_xRmsMib25_1000  = new TGraph(15, runsMib25_1000, xRmsMib25_1000);
  TGraph* G_yRmsMib25_1000  = new TGraph(15, runsMib25_1000, yRmsMib25_1000);
  G_xMeanMib25_1000->SetMarkerStyle(20);
  G_xMeanMib25_1000->SetMarkerColor(1);
  G_yMeanMib25_1000->SetMarkerStyle(21);
  G_yMeanMib25_1000->SetMarkerColor(2);
  G_xRmsMib25_1000->SetMarkerStyle(20);
  G_xRmsMib25_1000->SetMarkerColor(1);
  G_yRmsMib25_1000->SetMarkerStyle(21);
  G_yRmsMib25_1000->SetMarkerColor(2);

  TGraph* G_xMeanMib25_1200 = new TGraph(13, runsMib25_1200, xMeanMib25_1200);
  TGraph* G_yMeanMib25_1200 = new TGraph(13, runsMib25_1200, yMeanMib25_1200);
  TGraph* G_xRmsMib25_1200  = new TGraph(13, runsMib25_1200, xRmsMib25_1200);
  TGraph* G_yRmsMib25_1200  = new TGraph(13, runsMib25_1200, yRmsMib25_1200);
  G_xMeanMib25_1200->SetMarkerStyle(20);
  G_xMeanMib25_1200->SetMarkerColor(1);
  G_yMeanMib25_1200->SetMarkerStyle(21);
  G_yMeanMib25_1200->SetMarkerColor(2);
  G_xRmsMib25_1200->SetMarkerStyle(20);
  G_xRmsMib25_1200->SetMarkerColor(1);
  G_yRmsMib25_1200->SetMarkerStyle(21);
  G_yRmsMib25_1200->SetMarkerColor(2);

  TGraph* G_xMeanRm5_700 = new TGraph(8, runsRm5_700, xMeanRm5_700);
  TGraph* G_yMeanRm5_700 = new TGraph(8, runsRm5_700, yMeanRm5_700);
  TGraph* G_xRmsRm5_700  = new TGraph(8, runsRm5_700, xRmsRm5_700);
  TGraph* G_yRmsRm5_700  = new TGraph(8, runsRm5_700, yRmsRm5_700);
  G_xMeanRm5_700->SetMarkerStyle(20);
  G_xMeanRm5_700->SetMarkerColor(1);
  G_yMeanRm5_700->SetMarkerStyle(21);
  G_yMeanRm5_700->SetMarkerColor(2);
  G_xRmsRm5_700->SetMarkerStyle(20);
  G_xRmsRm5_700->SetMarkerColor(1);
  G_yRmsRm5_700->SetMarkerStyle(21);
  G_yRmsRm5_700->SetMarkerColor(2);

  TGraph* G_xMeanRm5_1000 = new TGraph(8, runsRm5_1000, xMeanRm5_1000);
  TGraph* G_yMeanRm5_1000 = new TGraph(8, runsRm5_1000, yMeanRm5_1000);
  TGraph* G_xRmsRm5_1000  = new TGraph(8, runsRm5_1000, xRmsRm5_1000);
  TGraph* G_yRmsRm5_1000  = new TGraph(8, runsRm5_1000, yRmsRm5_1000);
  G_xMeanRm5_1000->SetMarkerStyle(20);
  G_xMeanRm5_1000->SetMarkerColor(1);
  G_yMeanRm5_1000->SetMarkerStyle(21);
  G_yMeanRm5_1000->SetMarkerColor(2);
  G_xRmsRm5_1000->SetMarkerStyle(20);
  G_xRmsRm5_1000->SetMarkerColor(1);
  G_yRmsRm5_1000->SetMarkerStyle(21);
  G_yRmsRm5_1000->SetMarkerColor(2);

  TGraph* G_xMeanRm5_1200 = new TGraph(8, runsRm5_1200, xMeanRm5_1200);
  TGraph* G_yMeanRm5_1200 = new TGraph(8, runsRm5_1200, yMeanRm5_1200);
  TGraph* G_xRmsRm5_1200  = new TGraph(8, runsRm5_1200, xRmsRm5_1200);
  TGraph* G_yRmsRm5_1200  = new TGraph(8, runsRm5_1200, yRmsRm5_1200);
  G_xMeanRm5_1200->SetMarkerStyle(20);
  G_xMeanRm5_1200->SetMarkerColor(1);
  G_yMeanRm5_1200->SetMarkerStyle(21);
  G_yMeanRm5_1200->SetMarkerColor(2);
  G_xRmsRm5_1200->SetMarkerStyle(20);
  G_xRmsRm5_1200->SetMarkerColor(1);
  G_yRmsRm5_1200->SetMarkerStyle(21);
  G_yRmsRm5_1200->SetMarkerColor(2);

  TGraph* G_xMeanRm8_700 = new TGraph(8, runsRm8_700, xMeanRm8_700);
  TGraph* G_yMeanRm8_700 = new TGraph(8, runsRm8_700, yMeanRm8_700);
  TGraph* G_xRmsRm8_700  = new TGraph(8, runsRm8_700, xRmsRm8_700);
  TGraph* G_yRmsRm8_700  = new TGraph(8, runsRm8_700, yRmsRm8_700);
  G_xMeanRm8_700->SetMarkerStyle(20);
  G_xMeanRm8_700->SetMarkerColor(1);
  G_yMeanRm8_700->SetMarkerStyle(21);
  G_yMeanRm8_700->SetMarkerColor(2);
  G_xRmsRm8_700->SetMarkerStyle(20);
  G_xRmsRm8_700->SetMarkerColor(1);
  G_yRmsRm8_700->SetMarkerStyle(21);
  G_yRmsRm8_700->SetMarkerColor(2);

  TGraph* G_xMeanRm8_1000 = new TGraph(8, runsRm8_1000, xMeanRm8_1000);
  TGraph* G_yMeanRm8_1000 = new TGraph(8, runsRm8_1000, yMeanRm8_1000);
  TGraph* G_xRmsRm8_1000  = new TGraph(8, runsRm8_1000, xRmsRm8_1000);
  TGraph* G_yRmsRm8_1000  = new TGraph(8, runsRm8_1000, yRmsRm8_1000);
  G_xMeanRm8_1000->SetMarkerStyle(20);
  G_xMeanRm8_1000->SetMarkerColor(1);
  G_yMeanRm8_1000->SetMarkerStyle(21);
  G_yMeanRm8_1000->SetMarkerColor(2);
  G_xRmsRm8_1000->SetMarkerStyle(20);
  G_xRmsRm8_1000->SetMarkerColor(1);
  G_yRmsRm8_1000->SetMarkerStyle(21);
  G_yRmsRm8_1000->SetMarkerColor(2);

  TGraph* G_xMeanRm8_1200 = new TGraph(8, runsRm8_1200, xMeanRm8_1200);
  TGraph* G_yMeanRm8_1200 = new TGraph(8, runsRm8_1200, yMeanRm8_1200);
  TGraph* G_xRmsRm8_1200  = new TGraph(8, runsRm8_1200, xRmsRm8_1200);
  TGraph* G_yRmsRm8_1200  = new TGraph(8, runsRm8_1200, yRmsRm8_1200);
  G_xMeanRm8_1200->SetMarkerStyle(20);
  G_xMeanRm8_1200->SetMarkerColor(1);
  G_yMeanRm8_1200->SetMarkerStyle(21);
  G_yMeanRm8_1200->SetMarkerColor(2);
  G_xRmsRm8_1200->SetMarkerStyle(20);
  G_xRmsRm8_1200->SetMarkerColor(1);
  G_yRmsRm8_1200->SetMarkerStyle(21);
  G_yRmsRm8_1200->SetMarkerColor(2);


  // -------------------------------- Plots ----------------------------
  TLegend *legA;
  legA = new TLegend(0.1,0.6,0.4,0.9);
  legA->SetFillStyle(0);
  legA->SetBorderSize(0);
  legA->SetTextSize(0.05);
  legA->SetFillColor(0);
  legA->AddEntry(G_xMeanMib10_1000,  "X", "p");
  legA->AddEntry(G_yMeanMib10_1000,  "Y", "p");


  // Mib10
  TCanvas* c1a = new TCanvas("c1a","c",1);
  c1a->SetGrid();
  TH2F *myHM10700 = new TH2F("myHM10700","",100,2400, 2445,100,10,20);
  myHM10700->GetXaxis()->SetTitle("run");
  myHM10700->GetYaxis()->SetTitle("mean X");
  myHM10700->Draw();
  G_xMeanMib10_700->Draw("Psame");
  G_yMeanMib10_700->Draw("Psame");
  legA->Draw();
  c1a->SaveAs("historyMean_mib10_700.png");

  TCanvas* c1b = new TCanvas("c1b","c",1);
  c1b->SetGrid();
  TH2F *myHR10700 = new TH2F("myHx10700","",100,2400, 2445,100,0,10);
  myHR10700->GetXaxis()->SetTitle("run");
  myHR10700->GetYaxis()->SetTitle("RMS X");
  myHR10700->Draw();
  G_xRmsMib10_700->Draw("Psame");
  G_yRmsMib10_700->Draw("Psame");
  legA->Draw();
  c1b->SaveAs("historyRms_mib10_700.png");

  TCanvas* c2a = new TCanvas("c2a","c",1);
  c2a->SetGrid();
  TH2F *myHM101000 = new TH2F("myHM101000","",100,2406, 2446,100,10,20);
  myHM101000->GetXaxis()->SetTitle("run");
  myHM101000->GetYaxis()->SetTitle("mean X");
  myHM101000->Draw();
  G_xMeanMib10_1000->Draw("Psame");
  G_yMeanMib10_1000->Draw("Psame");
  legA->Draw();
  c2a->SaveAs("historyMean_mib10_1000.png");

  TCanvas* c2b = new TCanvas("c2b","c",1);
  c2b->SetGrid();
  TH2F *myHR101000 = new TH2F("myHx101000","",100,2406, 2446,100,0,10);
  myHR101000->GetXaxis()->SetTitle("run");
  myHR101000->GetYaxis()->SetTitle("RMS X");
  myHR101000->Draw();
  G_xRmsMib10_1000->Draw("Psame");
  G_yRmsMib10_1000->Draw("Psame");
  legA->Draw();
  c2b->SaveAs("historyRms_mib10_1000.png");

  // Mib25
  TCanvas* c3a = new TCanvas("c3a","c",1);
  c3a->SetGrid();
  TH2F *myHM25700 = new TH2F("myHM25700","",100,2376, 2438,100,10,20);
  myHM25700->GetXaxis()->SetTitle("run");
  myHM25700->GetYaxis()->SetTitle("mean X");
  myHM25700->Draw();
  G_xMeanMib25_700->Draw("Psame");
  G_yMeanMib25_700->Draw("Psame");
  legA->Draw();
  c3a->SaveAs("historyMean_mib25_700.png");

  TCanvas* c3b = new TCanvas("c3b","c",1);
  c3b->SetGrid();
  TH2F *myHR25700 = new TH2F("myHx25700","",100,2376, 2438,100,0,10);
  myHR25700->GetXaxis()->SetTitle("run");
  myHR25700->GetYaxis()->SetTitle("RMS X");
  myHR25700->Draw();
  G_xRmsMib25_700->Draw("Psame");
  G_yRmsMib25_700->Draw("Psame");
  legA->Draw();
  c3b->SaveAs("historyRms_mib25_700.png");

  TCanvas* c4a = new TCanvas("c4a","c",1);
  c4a->SetGrid();
  TH2F *myHM251000 = new TH2F("myHM251000","",100,2381, 2441,100,10,20);
  myHM251000->GetXaxis()->SetTitle("run");
  myHM251000->GetYaxis()->SetTitle("mean X");
  myHM251000->Draw();
  G_xMeanMib25_1000->Draw("Psame");
  G_yMeanMib25_1000->Draw("Psame");
  legA->Draw();
  c4a->SaveAs("historyMean_mib25_1000.png");

  TCanvas* c4b = new TCanvas("c4b","c",1);
  c4b->SetGrid();
  TH2F *myHR251000 = new TH2F("myHx251000","",100,2381, 2441,100,0,10);
  myHR251000->GetXaxis()->SetTitle("run");
  myHR251000->GetYaxis()->SetTitle("RMS X");
  myHR251000->Draw();
  G_xRmsMib25_1000->Draw("Psame");
  G_yRmsMib25_1000->Draw("Psame");
  legA->Draw();
  c4b->SaveAs("historyRms_mib25_1000.png");

  TCanvas* c5a = new TCanvas("c5a","c",1);
  c5a->SetGrid();
  TH2F *myHM251200 = new TH2F("myHM251200","",100,2507,2539,100,10,20);
  myHM251200->GetXaxis()->SetTitle("run");
  myHM251200->GetYaxis()->SetTitle("mean X");
  myHM251200->Draw();
  G_xMeanMib25_1200->Draw("Psame");
  G_yMeanMib25_1200->Draw("Psame");
  legA->Draw();
  c5a->SaveAs("historyMean_mib25_1200.png");

  TCanvas* c5b = new TCanvas("c5b","c",1);
  c5b->SetGrid();
  TH2F *myHR251200 = new TH2F("myHx251200","",100,2507,2539,100,0,10);
  myHR251200->GetXaxis()->SetTitle("run");
  myHR251200->GetYaxis()->SetTitle("RMS X");
  myHR251200->Draw();
  G_xRmsMib25_1200->Draw("Psame");
  G_yRmsMib25_1200->Draw("Psame");
  legA->Draw();
  c5b->SaveAs("historyRms_mib25_1200.png");

  // Rm5
  TCanvas* c6a = new TCanvas("c6a","c",1);
  c6a->SetGrid();

  TH2F *myHM5700 = new TH2F("myHM5700","",100,2460, 2503,100,5,20);
  myHM5700->GetXaxis()->SetTitle("run");
  myHM5700->GetYaxis()->SetTitle("mean X");
  myHM5700->Draw();
  G_xMeanRm5_700->Draw("Psame");
  G_yMeanRm5_700->Draw("Psame");
  legA->Draw();
  c6a->SaveAs("historyMean_rm5_700.png");

  TCanvas* c6b = new TCanvas("c6b","c",1);
  c6b->SetGrid();
  TH2F *myHR5700 = new TH2F("myHx5700","",100,2460, 2503,100,0,10);
  myHR5700->GetXaxis()->SetTitle("run");
  myHR5700->GetYaxis()->SetTitle("RMS X");
  myHR5700->Draw();
  G_xRmsRm5_700->Draw("Psame");
  G_yRmsRm5_700->Draw("Psame");
  legA->Draw();
  c6b->SaveAs("historyRms_rm5_700.png");

  TCanvas* c7a = new TCanvas("c7a","c",1);
  c7a->SetGrid();
  TH2F *myHM51000 = new TH2F("myHM51000","",100,2465,2500,100,5,20);
  myHM51000->GetXaxis()->SetTitle("run");
  myHM51000->GetYaxis()->SetTitle("mean X");
  myHM51000->Draw();
  G_xMeanRm5_1000->Draw("Psame");
  G_yMeanRm5_1000->Draw("Psame");
  legA->Draw();
  c7a->SaveAs("historyMean_rm5_1000.png");

  TCanvas* c7b = new TCanvas("c7b","c",1);
  c7b->SetGrid();
  TH2F *myHR51000 = new TH2F("myHx51000","",100,2465,2500,100,0,10);
  myHR51000->GetXaxis()->SetTitle("run");
  myHR51000->GetYaxis()->SetTitle("RMS X");
  myHR51000->Draw();
  G_xRmsRm5_1000->Draw("Psame");
  G_yRmsRm5_1000->Draw("Psame");
  legA->Draw();
  c7b->SaveAs("historyRms_rm5_1000.png");

  TCanvas* c8a = new TCanvas("c8a","c",1);
  c8a->SetGrid();
  TH2F *myHM51200 = new TH2F("myHM51200","",100,2470,2497,100,5,20);
  myHM51200->GetXaxis()->SetTitle("run");
  myHM51200->GetYaxis()->SetTitle("mean X");
  myHM51200->Draw();
  G_xMeanRm5_1200->Draw("Psame");
  G_yMeanRm5_1200->Draw("Psame");
  legA->Draw();
  c8a->SaveAs("historyMean_rm5_1200.png");
  
  TCanvas* c8b = new TCanvas("c8b","c",1);
  c8b->SetGrid();
  TH2F *myHR51200 = new TH2F("myHx51200","",100,2470,2497,100,0,10);
  myHR51200->GetXaxis()->SetTitle("run");
  myHR51200->GetYaxis()->SetTitle("RMS X");
  myHR51200->Draw();
  G_xRmsRm5_1200->Draw("Psame");
  G_yRmsRm5_1200->Draw("Psame");
  legA->Draw();
  c8b->SaveAs("historyRms_rm5_1200.png");

  // Rm8
  TCanvas* c9a = new TCanvas("c9a","c",1);
  c9a->SetGrid();
  TH2F *myHM8700 = new TH2F("myHM8700","",100,2445,2506,100,5,20);
  myHM8700->GetXaxis()->SetTitle("run");
  myHM8700->GetYaxis()->SetTitle("mean X");
  myHM8700->Draw();
  G_xMeanRm8_700->Draw("Psame");
  G_yMeanRm8_700->Draw("Psame");
  legA->Draw();
  c9a->SaveAs("historyMean_rm8_700.png");

  TCanvas* c9b = new TCanvas("c9b","c",1);
  c9b->SetGrid();
  TH2F *myHR8700 = new TH2F("myHx8700","",100,2445,2506,100,0,10);
  myHR8700->GetXaxis()->SetTitle("run");
  myHR8700->GetYaxis()->SetTitle("RMS X");
  myHR8700->Draw();
  G_xRmsRm8_700->Draw("Psame");
  G_yRmsRm8_700->Draw("Psame");
  legA->Draw();
  c9b->SaveAs("historyRms_rm8_700.png");

  TCanvas* c10a = new TCanvas("c10a","c",1);
  c10a->SetGrid();
  TH2F *myHM81000 = new TH2F("myHM81000","",100,2450,2509,100,5,20);
  myHM81000->GetXaxis()->SetTitle("run");
  myHM81000->GetYaxis()->SetTitle("mean X");
  myHM81000->Draw();
  G_xMeanRm8_1000->Draw("Psame");
  G_yMeanRm8_1000->Draw("Psame");
  legA->Draw();
  c10a->SaveAs("historyMean_rm8_1000.png");

  TCanvas* c10b = new TCanvas("c10b","c",1);
  c10b->SetGrid();
  TH2F *myHR81000 = new TH2F("myHx81000","",100,2450,2509,100,0,10);
  myHR81000->GetXaxis()->SetTitle("run");
  myHR81000->GetYaxis()->SetTitle("RMS X");
  myHR81000->Draw();
  G_xRmsRm8_1000->Draw("Psame");
  G_yRmsRm8_1000->Draw("Psame");
  legA->Draw();
  c10b->SaveAs("historyRms_rm8_1000.png");

  TCanvas* c11a = new TCanvas("c11a","c",1);
  c11a->SetGrid();
  TH2F *myHM81200 = new TH2F("myHM81200","",100,2455,2512,100,5,20);
  myHM81200->GetXaxis()->SetTitle("run");
  myHM81200->GetYaxis()->SetTitle("mean X");
  myHM81200->Draw();
  G_xMeanRm8_1200->Draw("Psame");
  G_yMeanRm8_1200->Draw("Psame");
  legA->Draw();
  c11a->SaveAs("historyMean_rm8_1200.png");
  
  TCanvas* c11b = new TCanvas("c11b","c",1);
  c11b->SetGrid();
  TH2F *myHR81200 = new TH2F("myHx81200","",100,2455,2512,100,0,10);
  myHR81200->GetXaxis()->SetTitle("run");
  myHR81200->GetYaxis()->SetTitle("RMS X");
  myHR81200->Draw();
  G_xRmsRm8_1200->Draw("Psame");
  G_yRmsRm8_1200->Draw("Psame");
  legA->Draw();
  c11b->SaveAs("historyRms_rm8_1200.png");



  // ==========================================================
  // Now: only for runs at plateau, Eff vs X and vs Y
  TH2F *myHx = new TH2F("myHx","",16,-1.5,30.5,100,0.,1.);
  TH2F *myHy = new TH2F("myHy","",16,-1.5,30.5,100,0.,1.);
  myHx->GetXaxis()->SetTitle("X");
  myHy->GetXaxis()->SetTitle("Y");
  myHx->GetYaxis()->SetTitle("Efficiency");
  myHy->GetYaxis()->SetTitle("Efficiency");


  // Mib10, Mid=700
  TString denMib10700 = "adc_data>200 && adc_data<700 && HVAMP==700 && run==2434";
  TString numMib10700_mib2  = denMib10700 + " && amp_max[MiB2]>20";
  TString numMib10700_rm2   = denMib10700 + " && amp_max[Rm2]>20";
  TString numMib10700_mib10 = denMib10700 + " && amp_max[M10]>20";

  TH1F *denX_RunMib10700       = new TH1F("denX_RunMib10700",      "denX_RunMib10700",      16,-1.5,30.5);  
  TH1F *denY_RunMib10700       = new TH1F("denY_RunMib10700",      "denY_RunMib10700",      16,-1.5,30.5);
  TH1F *numX_Mib2_RunMib10700  = new TH1F("numX_Mib2_RunMib10700", "numX_Mib2_RunMib10700", 16,-1.5,30.5);  
  TH1F *numY_Mib2_RunMib10700  = new TH1F("numY_Mib2_RunMib10700", "numY_Mib2_RunMib10700", 16,-1.5,30.5);  
  TH1F *numX_Rm2_RunMib10700   = new TH1F("numX_Rm2_RunMib10700",  "numX_Rm2_RunMib10700",  16,-1.5,30.5);  
  TH1F *numY_Rm2_RunMib10700   = new TH1F("numY_Rm2_RunMib10700",  "numY_Rm2_RunMib10700",  16,-1.5,30.5);  
  TH1F *numX_Mib10_RunMib10700 = new TH1F("numX_Mib10_RunMib10700","numX_Mib10_RunMib10700",16,-1.5,30.5);  
  TH1F *numY_Mib10_RunMib10700 = new TH1F("numY_Mib10_RunMib10700","numY_Mib10_RunMib10700",16,-1.5,30.5);  

  h4Mib10_700 ->Project("denX_RunMib10700",       "X", denMib10700);
  h4Mib10_700 ->Project("denY_RunMib10700",       "Y", denMib10700);
  h4Mib10_700 ->Project("numX_Mib2_RunMib10700",  "X", numMib10700_mib2);
  h4Mib10_700 ->Project("numY_Mib2_RunMib10700",  "Y", numMib10700_mib2);
  h4Mib10_700 ->Project("numX_Rm2_RunMib10700",   "X", numMib10700_rm2);
  h4Mib10_700 ->Project("numY_Rm2_RunMib10700",   "Y", numMib10700_rm2);
  h4Mib10_700 ->Project("numX_Mib10_RunMib10700", "X", numMib10700_mib10);
  h4Mib10_700 ->Project("numY_Mib10_RunMib10700", "Y", numMib10700_mib10);

  TGraphAsymmErrors* effX_Mib2_RunMib10700 = new TGraphAsymmErrors(numX_Mib2_RunMib10700, denX_RunMib10700);
  TGraphAsymmErrors* effY_Mib2_RunMib10700 = new TGraphAsymmErrors(numY_Mib2_RunMib10700, denY_RunMib10700);
  effX_Mib2_RunMib10700->SetMarkerStyle(20);
  effX_Mib2_RunMib10700->SetMarkerColor(1);
  effX_Mib2_RunMib10700->SetLineColor(1);
  effY_Mib2_RunMib10700->SetMarkerStyle(21);
  effY_Mib2_RunMib10700->SetMarkerColor(2);
  effY_Mib2_RunMib10700->SetLineColor(2);

  TGraphAsymmErrors* effX_Rm2_RunMib10700 = new TGraphAsymmErrors(numX_Rm2_RunMib10700, denX_RunMib10700);
  TGraphAsymmErrors* effY_Rm2_RunMib10700 = new TGraphAsymmErrors(numY_Rm2_RunMib10700, denY_RunMib10700);
  effX_Rm2_RunMib10700->SetMarkerStyle(20);
  effX_Rm2_RunMib10700->SetMarkerColor(1);
  effX_Rm2_RunMib10700->SetLineColor(1);
  effY_Rm2_RunMib10700->SetMarkerStyle(21);
  effY_Rm2_RunMib10700->SetMarkerColor(2);
  effY_Rm2_RunMib10700->SetLineColor(2);

  TGraphAsymmErrors* effX_Mib10_RunMib10700 = new TGraphAsymmErrors(numX_Mib10_RunMib10700, denX_RunMib10700);
  TGraphAsymmErrors* effY_Mib10_RunMib10700 = new TGraphAsymmErrors(numY_Mib10_RunMib10700, denY_RunMib10700);
  effX_Mib10_RunMib10700->SetMarkerStyle(20);
  effX_Mib10_RunMib10700->SetMarkerColor(1);
  effX_Mib10_RunMib10700->SetLineColor(1);
  effY_Mib10_RunMib10700->SetMarkerStyle(21);
  effY_Mib10_RunMib10700->SetMarkerColor(2);
  effY_Mib10_RunMib10700->SetLineColor(2);

  TCanvas* c110a = new TCanvas("c110a","c",1);
  c110a->Divide(2,1);
  c110a->cd(1); myHx->Draw(); effX_Mib2_RunMib10700->Draw("Psame");
  c110a->cd(2); myHy->Draw(); effY_Mib2_RunMib10700->Draw("Psame");
  c110a->SaveAs("EffMib2_VsCoord_runMib10at700.png");  

  TCanvas* c110b = new TCanvas("c110b","c",1);
  c110b->Divide(2,1);
  c110b->cd(1); myHx->Draw(); effX_Rm2_RunMib10700->Draw("Psame");
  c110b->cd(2); myHy->Draw(); effY_Rm2_RunMib10700->Draw("Psame");
  c110b->SaveAs("EffRm2_VsCoord_runMib10at700.png");  

  TCanvas* c110c = new TCanvas("c110c","c",1);
  c110c->Divide(2,1);
  c110c->cd(1); myHx->Draw(); effX_Mib10_RunMib10700->Draw("Psame");
  c110c->cd(2); myHy->Draw(); effY_Mib10_RunMib10700->Draw("Psame");
  c110c->SaveAs("EffMib10_VsCoord_runMib10at700.png");  


  // Mib10, Mid=1000
  TString denMib101000 = "adc_data>200 && adc_data<700 && HVAMP==1000 && run==2436";
  TString numMib101000_mib2  = denMib101000 + " && amp_max[MiB2]>20";
  TString numMib101000_rm2   = denMib101000 + " && amp_max[Rm2]>20";
  TString numMib101000_mib10 = denMib101000 + " && amp_max[M10]>20";

  TH1F *denX_RunMib101000       = new TH1F("denX_RunMib101000",      "denX_RunMib101000",      16,-1.5,30.5);  
  TH1F *denY_RunMib101000       = new TH1F("denY_RunMib101000",      "denY_RunMib101000",      16,-1.5,30.5);
  TH1F *numX_Mib2_RunMib101000  = new TH1F("numX_Mib2_RunMib101000", "numX_Mib2_RunMib101000", 16,-1.5,30.5);  
  TH1F *numY_Mib2_RunMib101000  = new TH1F("numY_Mib2_RunMib101000", "numY_Mib2_RunMib101000", 16,-1.5,30.5);  
  TH1F *numX_Rm2_RunMib101000   = new TH1F("numX_Rm2_RunMib101000",  "numX_Rm2_RunMib101000",  16,-1.5,30.5);  
  TH1F *numY_Rm2_RunMib101000   = new TH1F("numY_Rm2_RunMib101000",  "numY_Rm2_RunMib101000",  16,-1.5,30.5);  
  TH1F *numX_Mib10_RunMib101000 = new TH1F("numX_Mib10_RunMib101000","numX_Mib10_RunMib101000",16,-1.5,30.5);  
  TH1F *numY_Mib10_RunMib101000 = new TH1F("numY_Mib10_RunMib101000","numY_Mib10_RunMib101000",16,-1.5,30.5);  

  h4Mib10_1000 ->Project("denX_RunMib101000",       "X", denMib101000);
  h4Mib10_1000 ->Project("denY_RunMib101000",       "Y", denMib101000);
  h4Mib10_1000 ->Project("numX_Mib2_RunMib101000",  "X", numMib101000_mib2);
  h4Mib10_1000 ->Project("numY_Mib2_RunMib101000",  "Y", numMib101000_mib2);
  h4Mib10_1000 ->Project("numX_Rm2_RunMib101000",   "X", numMib101000_rm2);
  h4Mib10_1000 ->Project("numY_Rm2_RunMib101000",   "Y", numMib101000_rm2);
  h4Mib10_1000 ->Project("numX_Mib10_RunMib101000", "X", numMib101000_mib10);
  h4Mib10_1000 ->Project("numY_Mib10_RunMib101000", "Y", numMib101000_mib10);

  TGraphAsymmErrors* effX_Mib2_RunMib101000 = new TGraphAsymmErrors(numX_Mib2_RunMib101000, denX_RunMib101000);
  TGraphAsymmErrors* effY_Mib2_RunMib101000 = new TGraphAsymmErrors(numY_Mib2_RunMib101000, denY_RunMib101000);
  effX_Mib2_RunMib101000->SetMarkerStyle(20);
  effX_Mib2_RunMib101000->SetMarkerColor(1);
  effX_Mib2_RunMib101000->SetLineColor(1);
  effY_Mib2_RunMib101000->SetMarkerStyle(21);
  effY_Mib2_RunMib101000->SetMarkerColor(2);
  effY_Mib2_RunMib101000->SetLineColor(2);

  TGraphAsymmErrors* effX_Rm2_RunMib101000 = new TGraphAsymmErrors(numX_Rm2_RunMib101000, denX_RunMib101000);
  TGraphAsymmErrors* effY_Rm2_RunMib101000 = new TGraphAsymmErrors(numY_Rm2_RunMib101000, denY_RunMib101000);
  effX_Rm2_RunMib101000->SetMarkerStyle(20);
  effX_Rm2_RunMib101000->SetMarkerColor(1);
  effX_Rm2_RunMib101000->SetLineColor(1);
  effY_Rm2_RunMib101000->SetMarkerStyle(21);
  effY_Rm2_RunMib101000->SetMarkerColor(2);
  effY_Rm2_RunMib101000->SetLineColor(2);

  TGraphAsymmErrors* effX_Mib10_RunMib101000 = new TGraphAsymmErrors(numX_Mib10_RunMib101000, denX_RunMib101000);
  TGraphAsymmErrors* effY_Mib10_RunMib101000 = new TGraphAsymmErrors(numY_Mib10_RunMib101000, denY_RunMib101000);
  effX_Mib10_RunMib101000->SetMarkerStyle(20);
  effX_Mib10_RunMib101000->SetMarkerColor(1);
  effX_Mib10_RunMib101000->SetLineColor(1);
  effY_Mib10_RunMib101000->SetMarkerStyle(21);
  effY_Mib10_RunMib101000->SetMarkerColor(2);
  effY_Mib10_RunMib101000->SetLineColor(2);

  TCanvas* c120a = new TCanvas("c120a","c",1);
  c120a->Divide(2,1);
  c120a->cd(1); myHx->Draw(); effX_Mib2_RunMib101000->Draw("Psame");
  c120a->cd(2); myHy->Draw(); effY_Mib2_RunMib101000->Draw("Psame");
  c120a->SaveAs("EffMib2_VsCoord_runMib10at1000.png");  

  TCanvas* c120b = new TCanvas("c120b","c",1);
  c120b->Divide(2,1);
  c120b->cd(1); myHx->Draw(); effX_Rm2_RunMib101000->Draw("Psame");
  c120b->cd(2); myHy->Draw(); effY_Rm2_RunMib101000->Draw("Psame");
  c120b->SaveAs("EffRm2_VsCoord_runMib10at1000.png");  

  TCanvas* c120c = new TCanvas("c120c","c",1);
  c120c->Divide(2,1);
  c120c->cd(1); myHx->Draw(); effX_Mib10_RunMib101000->Draw("Psame");
  c120c->cd(2); myHy->Draw(); effY_Mib10_RunMib101000->Draw("Psame");
  c120c->SaveAs("EffMib10_VsCoord_runMib10at1000.png"); 



  // Mib25, Mid=700
  TString denMib25700 = "adc_data>200 && adc_data<700 && HVAMP==700 && run==2428";
  TString numMib25700_mib2  = denMib25700 + " && amp_max[MiB2]>20";
  TString numMib25700_rm2   = denMib25700 + " && amp_max[Rm2]>20";
  TString numMib25700_mib25 = denMib25700 + " && amp_max[M25]>20";

  TH1F *denX_RunMib25700       = new TH1F("denX_RunMib25700",      "denX_RunMib25700",      16,-1.5,30.5);  
  TH1F *denY_RunMib25700       = new TH1F("denY_RunMib25700",      "denY_RunMib25700",      16,-1.5,30.5);
  TH1F *numX_Mib2_RunMib25700  = new TH1F("numX_Mib2_RunMib25700", "numX_Mib2_RunMib25700", 16,-1.5,30.5);  
  TH1F *numY_Mib2_RunMib25700  = new TH1F("numY_Mib2_RunMib25700", "numY_Mib2_RunMib25700", 16,-1.5,30.5);  
  TH1F *numX_Rm2_RunMib25700   = new TH1F("numX_Rm2_RunMib25700",  "numX_Rm2_RunMib25700",  16,-1.5,30.5);  
  TH1F *numY_Rm2_RunMib25700   = new TH1F("numY_Rm2_RunMib25700",  "numY_Rm2_RunMib25700",  16,-1.5,30.5);  
  TH1F *numX_Mib25_RunMib25700 = new TH1F("numX_Mib25_RunMib25700","numX_Mib25_RunMib25700",16,-1.5,30.5);  
  TH1F *numY_Mib25_RunMib25700 = new TH1F("numY_Mib25_RunMib25700","numY_Mib25_RunMib25700",16,-1.5,30.5);  

  h4Mib25_700 ->Project("denX_RunMib25700",       "X", denMib25700);
  h4Mib25_700 ->Project("denY_RunMib25700",       "Y", denMib25700);
  h4Mib25_700 ->Project("numX_Mib2_RunMib25700",  "X", numMib25700_mib2);
  h4Mib25_700 ->Project("numY_Mib2_RunMib25700",  "Y", numMib25700_mib2);
  h4Mib25_700 ->Project("numX_Rm2_RunMib25700",   "X", numMib25700_rm2);
  h4Mib25_700 ->Project("numY_Rm2_RunMib25700",   "Y", numMib25700_rm2);
  h4Mib25_700 ->Project("numX_Mib25_RunMib25700", "X", numMib25700_mib25);
  h4Mib25_700 ->Project("numY_Mib25_RunMib25700", "Y", numMib25700_mib25);

  TGraphAsymmErrors* effX_Mib2_RunMib25700 = new TGraphAsymmErrors(numX_Mib2_RunMib25700, denX_RunMib25700);
  TGraphAsymmErrors* effY_Mib2_RunMib25700 = new TGraphAsymmErrors(numY_Mib2_RunMib25700, denY_RunMib25700);
  effX_Mib2_RunMib25700->SetMarkerStyle(20);
  effX_Mib2_RunMib25700->SetMarkerColor(1);
  effX_Mib2_RunMib25700->SetLineColor(1);
  effY_Mib2_RunMib25700->SetMarkerStyle(21);
  effY_Mib2_RunMib25700->SetMarkerColor(2);
  effY_Mib2_RunMib25700->SetLineColor(2);

  TGraphAsymmErrors* effX_Rm2_RunMib25700 = new TGraphAsymmErrors(numX_Rm2_RunMib25700, denX_RunMib25700);
  TGraphAsymmErrors* effY_Rm2_RunMib25700 = new TGraphAsymmErrors(numY_Rm2_RunMib25700, denY_RunMib25700);
  effX_Rm2_RunMib25700->SetMarkerStyle(20);
  effX_Rm2_RunMib25700->SetMarkerColor(1);
  effX_Rm2_RunMib25700->SetLineColor(1);
  effY_Rm2_RunMib25700->SetMarkerStyle(21);
  effY_Rm2_RunMib25700->SetMarkerColor(2);
  effY_Rm2_RunMib25700->SetLineColor(2);

  TGraphAsymmErrors* effX_Mib25_RunMib25700 = new TGraphAsymmErrors(numX_Mib25_RunMib25700, denX_RunMib25700);
  TGraphAsymmErrors* effY_Mib25_RunMib25700 = new TGraphAsymmErrors(numY_Mib25_RunMib25700, denY_RunMib25700);
  effX_Mib25_RunMib25700->SetMarkerStyle(20);
  effX_Mib25_RunMib25700->SetMarkerColor(1);
  effX_Mib25_RunMib25700->SetLineColor(1);
  effY_Mib25_RunMib25700->SetMarkerStyle(21);
  effY_Mib25_RunMib25700->SetMarkerColor(2);
  effY_Mib25_RunMib25700->SetLineColor(2);

  TCanvas* c130a = new TCanvas("c130a","c",1);
  c130a->Divide(2,1);
  c130a->cd(1); myHx->Draw(); effX_Mib2_RunMib25700->Draw("Psame");
  c130a->cd(2); myHy->Draw(); effY_Mib2_RunMib25700->Draw("Psame");
  c130a->SaveAs("EffMib2_VsCoord_runMib25at700.png");  

  TCanvas* c130b = new TCanvas("c130b","c",1);
  c130b->Divide(2,1);
  c130b->cd(1); myHx->Draw(); effX_Rm2_RunMib25700->Draw("Psame");
  c130b->cd(2); myHy->Draw(); effY_Rm2_RunMib25700->Draw("Psame");
  c130b->SaveAs("EffRm2_VsCoord_runMib25at700.png");  

  TCanvas* c130c = new TCanvas("c130c","c",1);
  c130c->Divide(2,1);
  c130c->cd(1); myHx->Draw(); effX_Mib25_RunMib25700->Draw("Psame");
  c130c->cd(2); myHy->Draw(); effY_Mib25_RunMib25700->Draw("Psame");
  c130c->SaveAs("EffMib25_VsCoord_runMib25at700.png");   


  // Mib25, Mid=1000
  TString denMib251000 = "adc_data>200 && adc_data<700 && HVAMP==1000 && run==2431";
  TString numMib251000_mib2  = denMib251000 + " && amp_max[MiB2]>20";
  TString numMib251000_rm2   = denMib251000 + " && amp_max[Rm2]>20";
  TString numMib251000_mib25 = denMib251000 + " && amp_max[M25]>20";

  TH1F *denX_RunMib251000       = new TH1F("denX_RunMib251000",      "denX_RunMib251000",      16,-1.5,30.5);  
  TH1F *denY_RunMib251000       = new TH1F("denY_RunMib251000",      "denY_RunMib251000",      16,-1.5,30.5);
  TH1F *numX_Mib2_RunMib251000  = new TH1F("numX_Mib2_RunMib251000", "numX_Mib2_RunMib251000", 16,-1.5,30.5);  
  TH1F *numY_Mib2_RunMib251000  = new TH1F("numY_Mib2_RunMib251000", "numY_Mib2_RunMib251000", 16,-1.5,30.5);  
  TH1F *numX_Rm2_RunMib251000   = new TH1F("numX_Rm2_RunMib251000",  "numX_Rm2_RunMib251000",  16,-1.5,30.5);  
  TH1F *numY_Rm2_RunMib251000   = new TH1F("numY_Rm2_RunMib251000",  "numY_Rm2_RunMib251000",  16,-1.5,30.5);  
  TH1F *numX_Mib25_RunMib251000 = new TH1F("numX_Mib25_RunMib251000","numX_Mib25_RunMib251000",16,-1.5,30.5);  
  TH1F *numY_Mib25_RunMib251000 = new TH1F("numY_Mib25_RunMib251000","numY_Mib25_RunMib251000",16,-1.5,30.5);  

  h4Mib25_1000 ->Project("denX_RunMib251000",       "X", denMib251000);
  h4Mib25_1000 ->Project("denY_RunMib251000",       "Y", denMib251000);
  h4Mib25_1000 ->Project("numX_Mib2_RunMib251000",  "X", numMib251000_mib2);
  h4Mib25_1000 ->Project("numY_Mib2_RunMib251000",  "Y", numMib251000_mib2);
  h4Mib25_1000 ->Project("numX_Rm2_RunMib251000",   "X", numMib251000_rm2);
  h4Mib25_1000 ->Project("numY_Rm2_RunMib251000",   "Y", numMib251000_rm2);
  h4Mib25_1000 ->Project("numX_Mib25_RunMib251000", "X", numMib251000_mib25);
  h4Mib25_1000 ->Project("numY_Mib25_RunMib251000", "Y", numMib251000_mib25);

  TGraphAsymmErrors* effX_Mib2_RunMib251000 = new TGraphAsymmErrors(numX_Mib2_RunMib251000, denX_RunMib251000);
  TGraphAsymmErrors* effY_Mib2_RunMib251000 = new TGraphAsymmErrors(numY_Mib2_RunMib251000, denY_RunMib251000);
  effX_Mib2_RunMib251000->SetMarkerStyle(20);
  effX_Mib2_RunMib251000->SetMarkerColor(1);
  effX_Mib2_RunMib251000->SetLineColor(1);
  effY_Mib2_RunMib251000->SetMarkerStyle(21);
  effY_Mib2_RunMib251000->SetMarkerColor(2);
  effY_Mib2_RunMib251000->SetLineColor(2);

  TGraphAsymmErrors* effX_Rm2_RunMib251000 = new TGraphAsymmErrors(numX_Rm2_RunMib251000, denX_RunMib251000);
  TGraphAsymmErrors* effY_Rm2_RunMib251000 = new TGraphAsymmErrors(numY_Rm2_RunMib251000, denY_RunMib251000);
  effX_Rm2_RunMib251000->SetMarkerStyle(20);
  effX_Rm2_RunMib251000->SetMarkerColor(1);
  effX_Rm2_RunMib251000->SetLineColor(1);
  effY_Rm2_RunMib251000->SetMarkerStyle(21);
  effY_Rm2_RunMib251000->SetMarkerColor(2);
  effY_Rm2_RunMib251000->SetLineColor(2);

  TGraphAsymmErrors* effX_Mib25_RunMib251000 = new TGraphAsymmErrors(numX_Mib25_RunMib251000, denX_RunMib251000);
  TGraphAsymmErrors* effY_Mib25_RunMib251000 = new TGraphAsymmErrors(numY_Mib25_RunMib251000, denY_RunMib251000);
  effX_Mib25_RunMib251000->SetMarkerStyle(20);
  effX_Mib25_RunMib251000->SetMarkerColor(1);
  effX_Mib25_RunMib251000->SetLineColor(1);
  effY_Mib25_RunMib251000->SetMarkerStyle(21);
  effY_Mib25_RunMib251000->SetMarkerColor(2);
  effY_Mib25_RunMib251000->SetLineColor(2);

  TCanvas* c140a = new TCanvas("c140a","c",1);
  c140a->Divide(2,1);
  c140a->cd(1); myHx->Draw(); effX_Mib2_RunMib251000->Draw("Psame");
  c140a->cd(2); myHy->Draw(); effY_Mib2_RunMib251000->Draw("Psame");
  c140a->SaveAs("EffMib2_VsCoord_runMib25at1000.png");  

  TCanvas* c140b = new TCanvas("c140b","c",1);
  c140b->Divide(2,1);
  c140b->cd(1); myHx->Draw(); effX_Rm2_RunMib251000->Draw("Psame");
  c140b->cd(2); myHy->Draw(); effY_Rm2_RunMib251000->Draw("Psame");
  c140b->SaveAs("EffRm2_VsCoord_runMib25at1000.png");  

  TCanvas* c140c = new TCanvas("c140c","c",1);
  c140c->Divide(2,1);
  c140c->cd(1); myHx->Draw(); effX_Mib25_RunMib251000->Draw("Psame");
  c140c->cd(2); myHy->Draw(); effY_Mib25_RunMib251000->Draw("Psame");
  c140c->SaveAs("EffMib25_VsCoord_runMib25at1000.png");   



  // Mib25, Mid=1200
  TString denMib251200 = "adc_data>200 && adc_data<700 && HVAMP==1200 && run==2529";
  TString numMib251200_mib2  = denMib251200 + " && amp_max[MiB2]>20";
  TString numMib251200_rm2   = denMib251200 + " && amp_max[Rm2]>20";
  TString numMib251200_mib25 = denMib251200 + " && amp_max[M25]>20";

  TH1F *denX_RunMib251200       = new TH1F("denX_RunMib251200",      "denX_RunMib251200",      16,-1.5,30.5);  
  TH1F *denY_RunMib251200       = new TH1F("denY_RunMib251200",      "denY_RunMib251200",      16,-1.5,30.5);
  TH1F *numX_Mib2_RunMib251200  = new TH1F("numX_Mib2_RunMib251200", "numX_Mib2_RunMib251200", 16,-1.5,30.5);  
  TH1F *numY_Mib2_RunMib251200  = new TH1F("numY_Mib2_RunMib251200", "numY_Mib2_RunMib251200", 16,-1.5,30.5);  
  TH1F *numX_Rm2_RunMib251200   = new TH1F("numX_Rm2_RunMib251200",  "numX_Rm2_RunMib251200",  16,-1.5,30.5);  
  TH1F *numY_Rm2_RunMib251200   = new TH1F("numY_Rm2_RunMib251200",  "numY_Rm2_RunMib251200",  16,-1.5,30.5);  
  TH1F *numX_Mib25_RunMib251200 = new TH1F("numX_Mib25_RunMib251200","numX_Mib25_RunMib251200",16,-1.5,30.5);  
  TH1F *numY_Mib25_RunMib251200 = new TH1F("numY_Mib25_RunMib251200","numY_Mib25_RunMib251200",16,-1.5,30.5);  

  h4Mib25_1200 ->Project("denX_RunMib251200",       "X", denMib251200);
  h4Mib25_1200 ->Project("denY_RunMib251200",       "Y", denMib251200);
  h4Mib25_1200 ->Project("numX_Mib2_RunMib251200",  "X", numMib251200_mib2);
  h4Mib25_1200 ->Project("numY_Mib2_RunMib251200",  "Y", numMib251200_mib2);
  h4Mib25_1200 ->Project("numX_Rm2_RunMib251200",   "X", numMib251200_rm2);
  h4Mib25_1200 ->Project("numY_Rm2_RunMib251200",   "Y", numMib251200_rm2);
  h4Mib25_1200 ->Project("numX_Mib25_RunMib251200", "X", numMib251200_mib25);
  h4Mib25_1200 ->Project("numY_Mib25_RunMib251200", "Y", numMib251200_mib25);

  TGraphAsymmErrors* effX_Mib2_RunMib251200 = new TGraphAsymmErrors(numX_Mib2_RunMib251200, denX_RunMib251200);
  TGraphAsymmErrors* effY_Mib2_RunMib251200 = new TGraphAsymmErrors(numY_Mib2_RunMib251200, denY_RunMib251200);
  effX_Mib2_RunMib251200->SetMarkerStyle(20);
  effX_Mib2_RunMib251200->SetMarkerColor(1);
  effX_Mib2_RunMib251200->SetLineColor(1);
  effY_Mib2_RunMib251200->SetMarkerStyle(21);
  effY_Mib2_RunMib251200->SetMarkerColor(2);
  effY_Mib2_RunMib251200->SetLineColor(2);

  TGraphAsymmErrors* effX_Rm2_RunMib251200 = new TGraphAsymmErrors(numX_Rm2_RunMib251200, denX_RunMib251200);
  TGraphAsymmErrors* effY_Rm2_RunMib251200 = new TGraphAsymmErrors(numY_Rm2_RunMib251200, denY_RunMib251200);
  effX_Rm2_RunMib251200->SetMarkerStyle(20);
  effX_Rm2_RunMib251200->SetMarkerColor(1);
  effX_Rm2_RunMib251200->SetLineColor(1);
  effY_Rm2_RunMib251200->SetMarkerStyle(21);
  effY_Rm2_RunMib251200->SetMarkerColor(2);
  effY_Rm2_RunMib251200->SetLineColor(2);

  TGraphAsymmErrors* effX_Mib25_RunMib251200 = new TGraphAsymmErrors(numX_Mib25_RunMib251200, denX_RunMib251200);
  TGraphAsymmErrors* effY_Mib25_RunMib251200 = new TGraphAsymmErrors(numY_Mib25_RunMib251200, denY_RunMib251200);
  effX_Mib25_RunMib251200->SetMarkerStyle(20);
  effX_Mib25_RunMib251200->SetMarkerColor(1);
  effX_Mib25_RunMib251200->SetLineColor(1);
  effY_Mib25_RunMib251200->SetMarkerStyle(21);
  effY_Mib25_RunMib251200->SetMarkerColor(2);
  effY_Mib25_RunMib251200->SetLineColor(2);

  TCanvas* c150a = new TCanvas("c150a","c",1);
  c150a->Divide(2,1);
  c150a->cd(1); myHx->Draw(); effX_Mib2_RunMib251200->Draw("Psame");
  c150a->cd(2); myHy->Draw(); effY_Mib2_RunMib251200->Draw("Psame");
  c150a->SaveAs("EffMib2_VsCoord_runMib25at1200.png");  

  TCanvas* c150b = new TCanvas("c150b","c",1);
  c150b->Divide(2,1);
  c150b->cd(1); myHx->Draw(); effX_Rm2_RunMib251200->Draw("Psame");
  c150b->cd(2); myHy->Draw(); effY_Rm2_RunMib251200->Draw("Psame");
  c150b->SaveAs("EffRm2_VsCoord_runMib25at1200.png");  

  TCanvas* c150c = new TCanvas("c150c","c",1);
  c150c->Divide(2,1);
  c150c->cd(1); myHx->Draw(); effX_Mib25_RunMib251200->Draw("Psame");
  c150c->cd(2); myHy->Draw(); effY_Mib25_RunMib251200->Draw("Psame");
  c150c->SaveAs("EffMib25_VsCoord_runMib25at1200.png");   



  // Rm5, Mid=700
  TString denRm5700 = "adc_data>200 && adc_data<700 && HVAMP==700 && run==2493";
  TString numRm5700_mib2 = denRm5700 + " && amp_max[MiB2]>20";
  TString numRm5700_rm2  = denRm5700 + " && amp_max[Rm2]>20";
  TString numRm5700_rm5  = denRm5700 + " && amp_max[M5]>20";

  TH1F *denX_RunRm5700      = new TH1F("denX_RunRm5700",      "denX_RunRm5700",      16,-1.5,30.5);  
  TH1F *denY_RunRm5700      = new TH1F("denY_RunRm5700",      "denY_RunRm5700",      16,-1.5,30.5);
  TH1F *numX_Mib2_RunRm5700 = new TH1F("numX_Mib2_RunRm5700", "numX_Mib2_RunRm5700", 16,-1.5,30.5);  
  TH1F *numY_Mib2_RunRm5700 = new TH1F("numY_Mib2_RunRm5700", "numY_Mib2_RunRm5700", 16,-1.5,30.5);  
  TH1F *numX_Rm2_RunRm5700  = new TH1F("numX_Rm2_RunRm5700",  "numX_Rm2_RunRm5700",  16,-1.5,30.5);  
  TH1F *numY_Rm2_RunRm5700  = new TH1F("numY_Rm2_RunRm5700",  "numY_Rm2_RunRm5700",  16,-1.5,30.5);  
  TH1F *numX_Rm5_RunRm5700  = new TH1F("numX_Rm5_RunRm5700",  "numX_Rm5_RunRm5700",  16,-1.5,30.5);  
  TH1F *numY_Rm5_RunRm5700  = new TH1F("numY_Rm5_RunRm5700",  "numY_Rm5_RunRm5700",  16,-1.5,30.5);  

  h4Rm5_700 ->Project("denX_RunRm5700",      "X", denRm5700);
  h4Rm5_700 ->Project("denY_RunRm5700",      "Y", denRm5700);
  h4Rm5_700 ->Project("numX_Mib2_RunRm5700", "X", numRm5700_mib2);
  h4Rm5_700 ->Project("numY_Mib2_RunRm5700", "Y", numRm5700_mib2);
  h4Rm5_700 ->Project("numX_Rm2_RunRm5700",  "X", numRm5700_rm2);
  h4Rm5_700 ->Project("numY_Rm2_RunRm5700",  "Y", numRm5700_rm2);
  h4Rm5_700 ->Project("numX_Rm5_RunRm5700",  "X", numRm5700_rm5);
  h4Rm5_700 ->Project("numY_Rm5_RunRm5700",  "Y", numRm5700_rm5);

  TGraphAsymmErrors* effX_Mib2_RunRm5700 = new TGraphAsymmErrors(numX_Mib2_RunRm5700, denX_RunRm5700);
  TGraphAsymmErrors* effY_Mib2_RunRm5700 = new TGraphAsymmErrors(numY_Mib2_RunRm5700, denY_RunRm5700);
  effX_Mib2_RunRm5700->SetMarkerStyle(20);
  effX_Mib2_RunRm5700->SetMarkerColor(1);
  effX_Mib2_RunRm5700->SetLineColor(1);
  effY_Mib2_RunRm5700->SetMarkerStyle(21);
  effY_Mib2_RunRm5700->SetMarkerColor(2);
  effY_Mib2_RunRm5700->SetLineColor(2);

  TGraphAsymmErrors* effX_Rm2_RunRm5700 = new TGraphAsymmErrors(numX_Rm2_RunRm5700, denX_RunRm5700);
  TGraphAsymmErrors* effY_Rm2_RunRm5700 = new TGraphAsymmErrors(numY_Rm2_RunRm5700, denY_RunRm5700);
  effX_Rm2_RunRm5700->SetMarkerStyle(20);
  effX_Rm2_RunRm5700->SetMarkerColor(1);
  effX_Rm2_RunRm5700->SetLineColor(1);
  effY_Rm2_RunRm5700->SetMarkerStyle(21);
  effY_Rm2_RunRm5700->SetMarkerColor(2);
  effY_Rm2_RunRm5700->SetLineColor(2);

  TGraphAsymmErrors* effX_Rm5_RunRm5700 = new TGraphAsymmErrors(numX_Rm5_RunRm5700, denX_RunRm5700);
  TGraphAsymmErrors* effY_Rm5_RunRm5700 = new TGraphAsymmErrors(numY_Rm5_RunRm5700, denY_RunRm5700);
  effX_Rm5_RunRm5700->SetMarkerStyle(20);
  effX_Rm5_RunRm5700->SetMarkerColor(1);
  effX_Rm5_RunRm5700->SetLineColor(1);
  effY_Rm5_RunRm5700->SetMarkerStyle(21);
  effY_Rm5_RunRm5700->SetMarkerColor(2);
  effY_Rm5_RunRm5700->SetLineColor(2);

  TCanvas* c160a = new TCanvas("c160a","c",1);
  c160a->Divide(2,1);
  c160a->cd(1); myHx->Draw(); effX_Mib2_RunRm5700->Draw("Psame");
  c160a->cd(2); myHy->Draw(); effY_Mib2_RunRm5700->Draw("Psame");
  c160a->SaveAs("EffMib2_VsCoord_runRm5at700.png");  

  TCanvas* c160b = new TCanvas("c160b","c",1);
  c160b->Divide(2,1);
  c160b->cd(1); myHx->Draw(); effX_Rm2_RunRm5700->Draw("Psame");
  c160b->cd(2); myHy->Draw(); effY_Rm2_RunRm5700->Draw("Psame");
  c160b->SaveAs("EffRm2_VsCoord_runRm5at700.png");  

  TCanvas* c160c = new TCanvas("c160c","c",1);
  c160c->Divide(2,1);
  c160c->cd(1); myHx->Draw(); effX_Rm5_RunRm5700->Draw("Psame");
  c160c->cd(2); myHy->Draw(); effY_Rm5_RunRm5700->Draw("Psame");
  c160c->SaveAs("EffRm5_VsCoord_runRm5at700.png");   


  // Rm5, Mid=1000
  TString denRm51000 = "adc_data>200 && adc_data<700 && HVAMP==1000 && run==2490";
  TString numRm51000_mib2 = denRm51000 + " && amp_max[MiB2]>20";
  TString numRm51000_rm2  = denRm51000 + " && amp_max[Rm2]>20";
  TString numRm51000_rm5  = denRm51000 + " && amp_max[M5]>20";

  TH1F *denX_RunRm51000      = new TH1F("denX_RunRm51000",      "denX_RunRm51000",      16,-1.5,30.5);  
  TH1F *denY_RunRm51000      = new TH1F("denY_RunRm51000",      "denY_RunRm51000",      16,-1.5,30.5);
  TH1F *numX_Mib2_RunRm51000 = new TH1F("numX_Mib2_RunRm51000", "numX_Mib2_RunRm51000", 16,-1.5,30.5);  
  TH1F *numY_Mib2_RunRm51000 = new TH1F("numY_Mib2_RunRm51000", "numY_Mib2_RunRm51000", 16,-1.5,30.5);  
  TH1F *numX_Rm2_RunRm51000  = new TH1F("numX_Rm2_RunRm51000",  "numX_Rm2_RunRm51000",  16,-1.5,30.5);  
  TH1F *numY_Rm2_RunRm51000  = new TH1F("numY_Rm2_RunRm51000",  "numY_Rm2_RunRm51000",  16,-1.5,30.5);  
  TH1F *numX_Rm5_RunRm51000  = new TH1F("numX_Rm5_RunRm51000",  "numX_Rm5_RunRm51000",  16,-1.5,30.5);  
  TH1F *numY_Rm5_RunRm51000  = new TH1F("numY_Rm5_RunRm51000",  "numY_Rm5_RunRm51000",  16,-1.5,30.5);  

  h4Rm5_1000 ->Project("denX_RunRm51000",      "X", denRm51000);
  h4Rm5_1000 ->Project("denY_RunRm51000",      "Y", denRm51000);
  h4Rm5_1000 ->Project("numX_Mib2_RunRm51000", "X", numRm51000_mib2);
  h4Rm5_1000 ->Project("numY_Mib2_RunRm51000", "Y", numRm51000_mib2);
  h4Rm5_1000 ->Project("numX_Rm2_RunRm51000",  "X", numRm51000_rm2);
  h4Rm5_1000 ->Project("numY_Rm2_RunRm51000",  "Y", numRm51000_rm2);
  h4Rm5_1000 ->Project("numX_Rm5_RunRm51000",  "X", numRm51000_rm5);
  h4Rm5_1000 ->Project("numY_Rm5_RunRm51000",  "Y", numRm51000_rm5);

  TGraphAsymmErrors* effX_Mib2_RunRm51000 = new TGraphAsymmErrors(numX_Mib2_RunRm51000, denX_RunRm51000);
  TGraphAsymmErrors* effY_Mib2_RunRm51000 = new TGraphAsymmErrors(numY_Mib2_RunRm51000, denY_RunRm51000);
  effX_Mib2_RunRm51000->SetMarkerStyle(20);
  effX_Mib2_RunRm51000->SetMarkerColor(1);
  effX_Mib2_RunRm51000->SetLineColor(1);
  effY_Mib2_RunRm51000->SetMarkerStyle(21);
  effY_Mib2_RunRm51000->SetMarkerColor(2);
  effY_Mib2_RunRm51000->SetLineColor(2);

  TGraphAsymmErrors* effX_Rm2_RunRm51000 = new TGraphAsymmErrors(numX_Rm2_RunRm51000, denX_RunRm51000);
  TGraphAsymmErrors* effY_Rm2_RunRm51000 = new TGraphAsymmErrors(numY_Rm2_RunRm51000, denY_RunRm51000);
  effX_Rm2_RunRm51000->SetMarkerStyle(20);
  effX_Rm2_RunRm51000->SetMarkerColor(1);
  effX_Rm2_RunRm51000->SetLineColor(1);
  effY_Rm2_RunRm51000->SetMarkerStyle(21);
  effY_Rm2_RunRm51000->SetMarkerColor(2);
  effY_Rm2_RunRm51000->SetLineColor(2);

  TGraphAsymmErrors* effX_Rm5_RunRm51000 = new TGraphAsymmErrors(numX_Rm5_RunRm51000, denX_RunRm51000);
  TGraphAsymmErrors* effY_Rm5_RunRm51000 = new TGraphAsymmErrors(numY_Rm5_RunRm51000, denY_RunRm51000);
  effX_Rm5_RunRm51000->SetMarkerStyle(20);
  effX_Rm5_RunRm51000->SetMarkerColor(1);
  effX_Rm5_RunRm51000->SetLineColor(1);
  effY_Rm5_RunRm51000->SetMarkerStyle(21);
  effY_Rm5_RunRm51000->SetMarkerColor(2);
  effY_Rm5_RunRm51000->SetLineColor(2);

  TCanvas* c170a = new TCanvas("c170a","c",1);
  c170a->Divide(2,1);
  c170a->cd(1); myHx->Draw(); effX_Mib2_RunRm51000->Draw("Psame");
  c170a->cd(2); myHy->Draw(); effY_Mib2_RunRm51000->Draw("Psame");
  c170a->SaveAs("EffMib2_VsCoord_runRm5at1000.png");  

  TCanvas* c170b = new TCanvas("c170b","c",1);
  c170b->Divide(2,1);
  c170b->cd(1); myHx->Draw(); effX_Rm2_RunRm51000->Draw("Psame");
  c170b->cd(2); myHy->Draw(); effY_Rm2_RunRm51000->Draw("Psame");
  c170b->SaveAs("EffRm2_VsCoord_runRm5at1000.png");  

  TCanvas* c170c = new TCanvas("c170c","c",1);
  c170c->Divide(2,1);
  c170c->cd(1); myHx->Draw(); effX_Rm5_RunRm51000->Draw("Psame");
  c170c->cd(2); myHy->Draw(); effY_Rm5_RunRm51000->Draw("Psame");
  c170c->SaveAs("EffRm5_VsCoord_runRm5at1000.png");  


  // Rm5, Mid=1200
  TString denRm51200 = "adc_data>200 && adc_data<700 && HVAMP==1200 && run==2487";
  TString numRm51200_mib2 = denRm51200 + " && amp_max[MiB2]>20";
  TString numRm51200_rm2  = denRm51200 + " && amp_max[Rm2]>20";
  TString numRm51200_rm5  = denRm51200 + " && amp_max[M5]>20";

  TH1F *denX_RunRm51200      = new TH1F("denX_RunRm51200",      "denX_RunRm51200",      16,-1.5,30.5);  
  TH1F *denY_RunRm51200      = new TH1F("denY_RunRm51200",      "denY_RunRm51200",      16,-1.5,30.5);
  TH1F *numX_Mib2_RunRm51200 = new TH1F("numX_Mib2_RunRm51200", "numX_Mib2_RunRm51200", 16,-1.5,30.5);  
  TH1F *numY_Mib2_RunRm51200 = new TH1F("numY_Mib2_RunRm51200", "numY_Mib2_RunRm51200", 16,-1.5,30.5);  
  TH1F *numX_Rm2_RunRm51200  = new TH1F("numX_Rm2_RunRm51200",  "numX_Rm2_RunRm51200",  16,-1.5,30.5);  
  TH1F *numY_Rm2_RunRm51200  = new TH1F("numY_Rm2_RunRm51200",  "numY_Rm2_RunRm51200",  16,-1.5,30.5);  
  TH1F *numX_Rm5_RunRm51200  = new TH1F("numX_Rm5_RunRm51200",  "numX_Rm5_RunRm51200",  16,-1.5,30.5);  
  TH1F *numY_Rm5_RunRm51200  = new TH1F("numY_Rm5_RunRm51200",  "numY_Rm5_RunRm51200",  16,-1.5,30.5);  

  h4Rm5_1200 ->Project("denX_RunRm51200",      "X", denRm51200);
  h4Rm5_1200 ->Project("denY_RunRm51200",      "Y", denRm51200);
  h4Rm5_1200 ->Project("numX_Mib2_RunRm51200", "X", numRm51200_mib2);
  h4Rm5_1200 ->Project("numY_Mib2_RunRm51200", "Y", numRm51200_mib2);
  h4Rm5_1200 ->Project("numX_Rm2_RunRm51200",  "X", numRm51200_rm2);
  h4Rm5_1200 ->Project("numY_Rm2_RunRm51200",  "Y", numRm51200_rm2);
  h4Rm5_1200 ->Project("numX_Rm5_RunRm51200",  "X", numRm51200_rm5);
  h4Rm5_1200 ->Project("numY_Rm5_RunRm51200",  "Y", numRm51200_rm5);

  TGraphAsymmErrors* effX_Mib2_RunRm51200 = new TGraphAsymmErrors(numX_Mib2_RunRm51200, denX_RunRm51200);
  TGraphAsymmErrors* effY_Mib2_RunRm51200 = new TGraphAsymmErrors(numY_Mib2_RunRm51200, denY_RunRm51200);
  effX_Mib2_RunRm51200->SetMarkerStyle(20);
  effX_Mib2_RunRm51200->SetMarkerColor(1);
  effX_Mib2_RunRm51200->SetLineColor(1);
  effY_Mib2_RunRm51200->SetMarkerStyle(21);
  effY_Mib2_RunRm51200->SetMarkerColor(2);
  effY_Mib2_RunRm51200->SetLineColor(2);

  TGraphAsymmErrors* effX_Rm2_RunRm51200 = new TGraphAsymmErrors(numX_Rm2_RunRm51200, denX_RunRm51200);
  TGraphAsymmErrors* effY_Rm2_RunRm51200 = new TGraphAsymmErrors(numY_Rm2_RunRm51200, denY_RunRm51200);
  effX_Rm2_RunRm51200->SetMarkerStyle(20);
  effX_Rm2_RunRm51200->SetMarkerColor(1);
  effX_Rm2_RunRm51200->SetLineColor(1);
  effY_Rm2_RunRm51200->SetMarkerStyle(21);
  effY_Rm2_RunRm51200->SetMarkerColor(2);
  effY_Rm2_RunRm51200->SetLineColor(2);

  TGraphAsymmErrors* effX_Rm5_RunRm51200 = new TGraphAsymmErrors(numX_Rm5_RunRm51200, denX_RunRm51200);
  TGraphAsymmErrors* effY_Rm5_RunRm51200 = new TGraphAsymmErrors(numY_Rm5_RunRm51200, denY_RunRm51200);
  effX_Rm5_RunRm51200->SetMarkerStyle(20);
  effX_Rm5_RunRm51200->SetMarkerColor(1);
  effX_Rm5_RunRm51200->SetLineColor(1);
  effY_Rm5_RunRm51200->SetMarkerStyle(21);
  effY_Rm5_RunRm51200->SetMarkerColor(2);
  effY_Rm5_RunRm51200->SetLineColor(2);

  TCanvas* c180a = new TCanvas("c180a","c",1);
  c180a->Divide(2,1);
  c180a->cd(1); myHx->Draw(); effX_Mib2_RunRm51200->Draw("Psame");
  c180a->cd(2); myHy->Draw(); effY_Mib2_RunRm51200->Draw("Psame");
  c180a->SaveAs("EffMib2_VsCoord_runRm5at1200.png");  

  TCanvas* c180b = new TCanvas("c180b","c",1);
  c180b->Divide(2,1);
  c180b->cd(1); myHx->Draw(); effX_Rm2_RunRm51200->Draw("Psame");
  c180b->cd(2); myHy->Draw(); effY_Rm2_RunRm51200->Draw("Psame");
  c180b->SaveAs("EffRm2_VsCoord_runRm5at1200.png");  

  TCanvas* c180c = new TCanvas("c180c","c",1);
  c180c->Divide(2,1);
  c180c->cd(1); myHx->Draw(); effX_Rm5_RunRm51200->Draw("Psame");
  c180c->cd(2); myHy->Draw(); effY_Rm5_RunRm51200->Draw("Psame");
  c180c->SaveAs("EffRm5_VsCoord_runRm5at1200.png");    


  // Rm8, Mid=700
  TString denRm8700 = "adc_data>200 && adc_data<700 && HVAMP==700 && run==2496";
  TString numRm8700_mib2 = denRm8700 + " && amp_max[MiB2]>20";
  TString numRm8700_rm2  = denRm8700 + " && amp_max[Rm2]>20";
  TString numRm8700_rm8  = denRm8700 + " && amp_max[M8]>20";

  TH1F *denX_RunRm8700      = new TH1F("denX_RunRm8700",      "denX_RunRm8700",      16,-1.5,30.5);  
  TH1F *denY_RunRm8700      = new TH1F("denY_RunRm8700",      "denY_RunRm8700",      16,-1.5,30.5);
  TH1F *numX_Mib2_RunRm8700 = new TH1F("numX_Mib2_RunRm8700", "numX_Mib2_RunRm8700", 16,-1.5,30.5);  
  TH1F *numY_Mib2_RunRm8700 = new TH1F("numY_Mib2_RunRm8700", "numY_Mib2_RunRm8700", 16,-1.5,30.5);  
  TH1F *numX_Rm2_RunRm8700  = new TH1F("numX_Rm2_RunRm8700",  "numX_Rm2_RunRm8700",  16,-1.5,30.5);  
  TH1F *numY_Rm2_RunRm8700  = new TH1F("numY_Rm2_RunRm8700",  "numY_Rm2_RunRm8700",  16,-1.5,30.5);  
  TH1F *numX_Rm8_RunRm8700  = new TH1F("numX_Rm8_RunRm8700",  "numX_Rm8_RunRm8700",  16,-1.5,30.5);  
  TH1F *numY_Rm8_RunRm8700  = new TH1F("numY_Rm8_RunRm8700",  "numY_Rm8_RunRm8700",  16,-1.5,30.5);  

  h4Rm8_700 ->Project("denX_RunRm8700",      "X", denRm8700);
  h4Rm8_700 ->Project("denY_RunRm8700",      "Y", denRm8700);
  h4Rm8_700 ->Project("numX_Mib2_RunRm8700", "X", numRm8700_mib2);
  h4Rm8_700 ->Project("numY_Mib2_RunRm8700", "Y", numRm8700_mib2);
  h4Rm8_700 ->Project("numX_Rm2_RunRm8700",  "X", numRm8700_rm2);
  h4Rm8_700 ->Project("numY_Rm2_RunRm8700",  "Y", numRm8700_rm2);
  h4Rm8_700 ->Project("numX_Rm8_RunRm8700",  "X", numRm8700_rm8);
  h4Rm8_700 ->Project("numY_Rm8_RunRm8700",  "Y", numRm8700_rm8);

  TGraphAsymmErrors* effX_Mib2_RunRm8700 = new TGraphAsymmErrors(numX_Mib2_RunRm8700, denX_RunRm8700);
  TGraphAsymmErrors* effY_Mib2_RunRm8700 = new TGraphAsymmErrors(numY_Mib2_RunRm8700, denY_RunRm8700);
  effX_Mib2_RunRm8700->SetMarkerStyle(20);
  effX_Mib2_RunRm8700->SetMarkerColor(1);
  effX_Mib2_RunRm8700->SetLineColor(1);
  effY_Mib2_RunRm8700->SetMarkerStyle(21);
  effY_Mib2_RunRm8700->SetMarkerColor(2);
  effY_Mib2_RunRm8700->SetLineColor(2);

  TGraphAsymmErrors* effX_Rm2_RunRm8700 = new TGraphAsymmErrors(numX_Rm2_RunRm8700, denX_RunRm8700);
  TGraphAsymmErrors* effY_Rm2_RunRm8700 = new TGraphAsymmErrors(numY_Rm2_RunRm8700, denY_RunRm8700);
  effX_Rm2_RunRm8700->SetMarkerStyle(20);
  effX_Rm2_RunRm8700->SetMarkerColor(1);
  effX_Rm2_RunRm8700->SetLineColor(1);
  effY_Rm2_RunRm8700->SetMarkerStyle(21);
  effY_Rm2_RunRm8700->SetMarkerColor(2);
  effY_Rm2_RunRm8700->SetLineColor(2);

  TGraphAsymmErrors* effX_Rm8_RunRm8700 = new TGraphAsymmErrors(numX_Rm8_RunRm8700, denX_RunRm8700);
  TGraphAsymmErrors* effY_Rm8_RunRm8700 = new TGraphAsymmErrors(numY_Rm8_RunRm8700, denY_RunRm8700);
  effX_Rm8_RunRm8700->SetMarkerStyle(20);
  effX_Rm8_RunRm8700->SetMarkerColor(1);
  effX_Rm8_RunRm8700->SetLineColor(1);
  effY_Rm8_RunRm8700->SetMarkerStyle(21);
  effY_Rm8_RunRm8700->SetMarkerColor(2);
  effY_Rm8_RunRm8700->SetLineColor(2);

  TCanvas* c190a = new TCanvas("c190a","c",1);
  c190a->Divide(2,1);
  c190a->cd(1); myHx->Draw(); effX_Mib2_RunRm8700->Draw("Psame");
  c190a->cd(2); myHy->Draw(); effY_Mib2_RunRm8700->Draw("Psame");
  c190a->SaveAs("EffMib2_VsCoord_runRm8at700.png");  

  TCanvas* c190b = new TCanvas("c190b","c",1);
  c190b->Divide(2,1);
  c190b->cd(1); myHx->Draw(); effX_Rm2_RunRm8700->Draw("Psame");
  c190b->cd(2); myHy->Draw(); effY_Rm2_RunRm8700->Draw("Psame");
  c190b->SaveAs("EffRm2_VsCoord_runRm8at700.png");  

  TCanvas* c190c = new TCanvas("c190c","c",1);
  c190c->Divide(2,1);
  c190c->cd(1); myHx->Draw(); effX_Rm8_RunRm8700->Draw("Psame");
  c190c->cd(2); myHy->Draw(); effY_Rm8_RunRm8700->Draw("Psame");
  c190c->SaveAs("EffRm8_VsCoord_runRm8at700.png");   


  // Rm8, Mid=1000
  TString denRm81000 = "adc_data>200 && adc_data<700 && HVAMP==1000 && run==2499";
  TString numRm81000_mib2 = denRm81000 + " && amp_max[MiB2]>20";
  TString numRm81000_rm2  = denRm81000 + " && amp_max[Rm2]>20";
  TString numRm81000_rm8  = denRm81000 + " && amp_max[M8]>20";

  TH1F *denX_RunRm81000      = new TH1F("denX_RunRm81000",      "denX_RunRm81000",      16,-1.5,30.5);  
  TH1F *denY_RunRm81000      = new TH1F("denY_RunRm81000",      "denY_RunRm81000",      16,-1.5,30.5);
  TH1F *numX_Mib2_RunRm81000 = new TH1F("numX_Mib2_RunRm81000", "numX_Mib2_RunRm81000", 16,-1.5,30.5);  
  TH1F *numY_Mib2_RunRm81000 = new TH1F("numY_Mib2_RunRm81000", "numY_Mib2_RunRm81000", 16,-1.5,30.5);  
  TH1F *numX_Rm2_RunRm81000  = new TH1F("numX_Rm2_RunRm81000",  "numX_Rm2_RunRm81000",  16,-1.5,30.5);  
  TH1F *numY_Rm2_RunRm81000  = new TH1F("numY_Rm2_RunRm81000",  "numY_Rm2_RunRm81000",  16,-1.5,30.5);  
  TH1F *numX_Rm8_RunRm81000  = new TH1F("numX_Rm8_RunRm81000",  "numX_Rm8_RunRm81000",  16,-1.5,30.5);  
  TH1F *numY_Rm8_RunRm81000  = new TH1F("numY_Rm8_RunRm81000",  "numY_Rm8_RunRm81000",  16,-1.5,30.5);  

  h4Rm8_1000 ->Project("denX_RunRm81000",      "X", denRm81000);
  h4Rm8_1000 ->Project("denY_RunRm81000",      "Y", denRm81000);
  h4Rm8_1000 ->Project("numX_Mib2_RunRm81000", "X", numRm81000_mib2);
  h4Rm8_1000 ->Project("numY_Mib2_RunRm81000", "Y", numRm81000_mib2);
  h4Rm8_1000 ->Project("numX_Rm2_RunRm81000",  "X", numRm81000_rm2);
  h4Rm8_1000 ->Project("numY_Rm2_RunRm81000",  "Y", numRm81000_rm2);
  h4Rm8_1000 ->Project("numX_Rm8_RunRm81000",  "X", numRm81000_rm8);
  h4Rm8_1000 ->Project("numY_Rm8_RunRm81000",  "Y", numRm81000_rm8);

  TGraphAsymmErrors* effX_Mib2_RunRm81000 = new TGraphAsymmErrors(numX_Mib2_RunRm81000, denX_RunRm81000);
  TGraphAsymmErrors* effY_Mib2_RunRm81000 = new TGraphAsymmErrors(numY_Mib2_RunRm81000, denY_RunRm81000);
  effX_Mib2_RunRm81000->SetMarkerStyle(20);
  effX_Mib2_RunRm81000->SetMarkerColor(1);
  effX_Mib2_RunRm81000->SetLineColor(1);
  effY_Mib2_RunRm81000->SetMarkerStyle(21);
  effY_Mib2_RunRm81000->SetMarkerColor(2);
  effY_Mib2_RunRm81000->SetLineColor(2);

  TGraphAsymmErrors* effX_Rm2_RunRm81000 = new TGraphAsymmErrors(numX_Rm2_RunRm81000, denX_RunRm81000);
  TGraphAsymmErrors* effY_Rm2_RunRm81000 = new TGraphAsymmErrors(numY_Rm2_RunRm81000, denY_RunRm81000);
  effX_Rm2_RunRm81000->SetMarkerStyle(20);
  effX_Rm2_RunRm81000->SetMarkerColor(1);
  effX_Rm2_RunRm81000->SetLineColor(1);
  effY_Rm2_RunRm81000->SetMarkerStyle(21);
  effY_Rm2_RunRm81000->SetMarkerColor(2);
  effY_Rm2_RunRm81000->SetLineColor(2);

  TGraphAsymmErrors* effX_Rm8_RunRm81000 = new TGraphAsymmErrors(numX_Rm8_RunRm81000, denX_RunRm81000);
  TGraphAsymmErrors* effY_Rm8_RunRm81000 = new TGraphAsymmErrors(numY_Rm8_RunRm81000, denY_RunRm81000);
  effX_Rm8_RunRm81000->SetMarkerStyle(20);
  effX_Rm8_RunRm81000->SetMarkerColor(1);
  effX_Rm8_RunRm81000->SetLineColor(1);
  effY_Rm8_RunRm81000->SetMarkerStyle(21);
  effY_Rm8_RunRm81000->SetMarkerColor(2);
  effY_Rm8_RunRm81000->SetLineColor(2);

  TCanvas* c200a = new TCanvas("c200a","c",1);
  c200a->Divide(2,1);
  c200a->cd(1); myHx->Draw(); effX_Mib2_RunRm81000->Draw("Psame");
  c200a->cd(2); myHy->Draw(); effY_Mib2_RunRm81000->Draw("Psame");
  c200a->SaveAs("EffMib2_VsCoord_runRm8at1000.png");  

  TCanvas* c200b = new TCanvas("c200b","c",1);
  c200b->Divide(2,1);
  c200b->cd(1); myHx->Draw(); effX_Rm2_RunRm81000->Draw("Psame");
  c200b->cd(2); myHy->Draw(); effY_Rm2_RunRm81000->Draw("Psame");
  c200b->SaveAs("EffRm2_VsCoord_runRm8at1000.png");  

  TCanvas* c200c = new TCanvas("c200c","c",1);
  c200c->Divide(2,1);
  c200c->cd(1); myHx->Draw(); effX_Rm8_RunRm81000->Draw("Psame");
  c200c->cd(2); myHy->Draw(); effY_Rm8_RunRm81000->Draw("Psame");
  c200c->SaveAs("EffRm8_VsCoord_runRm8at1000.png");   


  // Rm8, Mid=1200
  TString denRm81200 = "adc_data>200 && adc_data<700 && HVAMP==1200 && run==2502";
  TString numRm81200_mib2 = denRm81200 + " && amp_max[MiB2]>20";
  TString numRm81200_rm2  = denRm81200 + " && amp_max[Rm2]>20";
  TString numRm81200_rm8  = denRm81200 + " && amp_max[M8]>20";

  TH1F *denX_RunRm81200      = new TH1F("denX_RunRm81200",      "denX_RunRm81200",      16,-1.5,30.5);  
  TH1F *denY_RunRm81200      = new TH1F("denY_RunRm81200",      "denY_RunRm81200",      16,-1.5,30.5);
  TH1F *numX_Mib2_RunRm81200 = new TH1F("numX_Mib2_RunRm81200", "numX_Mib2_RunRm81200", 16,-1.5,30.5);  
  TH1F *numY_Mib2_RunRm81200 = new TH1F("numY_Mib2_RunRm81200", "numY_Mib2_RunRm81200", 16,-1.5,30.5);  
  TH1F *numX_Rm2_RunRm81200  = new TH1F("numX_Rm2_RunRm81200",  "numX_Rm2_RunRm81200",  16,-1.5,30.5);  
  TH1F *numY_Rm2_RunRm81200  = new TH1F("numY_Rm2_RunRm81200",  "numY_Rm2_RunRm81200",  16,-1.5,30.5);  
  TH1F *numX_Rm8_RunRm81200  = new TH1F("numX_Rm8_RunRm81200",  "numX_Rm8_RunRm81200",  16,-1.5,30.5);  
  TH1F *numY_Rm8_RunRm81200  = new TH1F("numY_Rm8_RunRm81200",  "numY_Rm8_RunRm81200",  16,-1.5,30.5);  

  h4Rm8_1200 ->Project("denX_RunRm81200",      "X", denRm81200);
  h4Rm8_1200 ->Project("denY_RunRm81200",      "Y", denRm81200);
  h4Rm8_1200 ->Project("numX_Mib2_RunRm81200", "X", numRm81200_mib2);
  h4Rm8_1200 ->Project("numY_Mib2_RunRm81200", "Y", numRm81200_mib2);
  h4Rm8_1200 ->Project("numX_Rm2_RunRm81200",  "X", numRm81200_rm2);
  h4Rm8_1200 ->Project("numY_Rm2_RunRm81200",  "Y", numRm81200_rm2);
  h4Rm8_1200 ->Project("numX_Rm8_RunRm81200",  "X", numRm81200_rm8);
  h4Rm8_1200 ->Project("numY_Rm8_RunRm81200",  "Y", numRm81200_rm8);

  TGraphAsymmErrors* effX_Mib2_RunRm81200 = new TGraphAsymmErrors(numX_Mib2_RunRm81200, denX_RunRm81200);
  TGraphAsymmErrors* effY_Mib2_RunRm81200 = new TGraphAsymmErrors(numY_Mib2_RunRm81200, denY_RunRm81200);
  effX_Mib2_RunRm81200->SetMarkerStyle(20);
  effX_Mib2_RunRm81200->SetMarkerColor(1);
  effX_Mib2_RunRm81200->SetLineColor(1);
  effY_Mib2_RunRm81200->SetMarkerStyle(21);
  effY_Mib2_RunRm81200->SetMarkerColor(2);
  effY_Mib2_RunRm81200->SetLineColor(2);

  TGraphAsymmErrors* effX_Rm2_RunRm81200 = new TGraphAsymmErrors(numX_Rm2_RunRm81200, denX_RunRm81200);
  TGraphAsymmErrors* effY_Rm2_RunRm81200 = new TGraphAsymmErrors(numY_Rm2_RunRm81200, denY_RunRm81200);
  effX_Rm2_RunRm81200->SetMarkerStyle(20);
  effX_Rm2_RunRm81200->SetMarkerColor(1);
  effX_Rm2_RunRm81200->SetLineColor(1);
  effY_Rm2_RunRm81200->SetMarkerStyle(21);
  effY_Rm2_RunRm81200->SetMarkerColor(2);
  effY_Rm2_RunRm81200->SetLineColor(2);

  TGraphAsymmErrors* effX_Rm8_RunRm81200 = new TGraphAsymmErrors(numX_Rm8_RunRm81200, denX_RunRm81200);
  TGraphAsymmErrors* effY_Rm8_RunRm81200 = new TGraphAsymmErrors(numY_Rm8_RunRm81200, denY_RunRm81200);
  effX_Rm8_RunRm81200->SetMarkerStyle(20);
  effX_Rm8_RunRm81200->SetMarkerColor(1);
  effX_Rm8_RunRm81200->SetLineColor(1);
  effY_Rm8_RunRm81200->SetMarkerStyle(21);
  effY_Rm8_RunRm81200->SetMarkerColor(2);
  effY_Rm8_RunRm81200->SetLineColor(2);

  TCanvas* c210a = new TCanvas("c210a","c",1);
  c210a->Divide(2,1);
  c210a->cd(1); myHx->Draw(); effX_Mib2_RunRm81200->Draw("Psame");
  c210a->cd(2); myHy->Draw(); effY_Mib2_RunRm81200->Draw("Psame");
  c210a->SaveAs("EffMib2_VsCoord_runRm8at1200.png");  

  TCanvas* c210b = new TCanvas("c210b","c",1);
  c210b->Divide(2,1);
  c210b->cd(1); myHx->Draw(); effX_Rm2_RunRm81200->Draw("Psame");
  c210b->cd(2); myHy->Draw(); effY_Rm2_RunRm81200->Draw("Psame");
  c210b->SaveAs("EffRm2_VsCoord_runRm8at1200.png");  

  TCanvas* c210c = new TCanvas("c210c","c",1);
  c210c->Divide(2,1);
  c210c->cd(1); myHx->Draw(); effX_Rm8_RunRm81200->Draw("Psame");
  c210c->cd(2); myHy->Draw(); effY_Rm8_RunRm81200->Draw("Psame");
  c210c->SaveAs("EffRm8_VsCoord_runRm8at1200.png");   




  // ==========================================================
  // Now2: fraction of events passing the standard selection with 0hits
  cout << endl;
  TString den0hits  = "adc_data>200 && adc_data<700 && amp_max[MiB2]>200 && amp_max[Rm2]>200 && amp_max[Rm2]<1200";
  TString num0hitsX = den0hits + " && n_hitsX==0";
  TString num0hitsY = den0hits + " && n_hitsY==0";
  for (int ii=0; ii<11; ii++) {
    TH1F *Hden0hits  = new TH1F("Hden0hits",   "Hden0hits",      16,-1.5,30.5);  
    TH1F *Hnum0hitsX = new TH1F("Hnum0hitsX",  "Hnum0hitsX",     16,-1.5,30.5);
    TH1F *Hnum0hitsY = new TH1F("Hnum0hitsY",  "Hnum0hitsY",     16,-1.5,30.5);
    TTree* theTree;
    if (ii==0)  theTree = h4Mib10_700;
    if (ii==1)  theTree = h4Mib10_1000;
    if (ii==2)  theTree = h4Mib25_700;
    if (ii==3)  theTree = h4Mib25_1000;
    if (ii==4)  theTree = h4Mib25_1200;
    if (ii==5)  theTree = h4Rm5_700;
    if (ii==6)  theTree = h4Rm5_1000;
    if (ii==7)  theTree = h4Rm5_1200;
    if (ii==8)  theTree = h4Rm8_700;
    if (ii==9)  theTree = h4Rm8_1000;
    if (ii==10) theTree = h4Rm8_1200;
    theTree ->Project("Hden0hits",  "X", den0hits);
    theTree ->Project("Hnum0hitsX", "X", num0hitsX);
    theTree ->Project("Hnum0hitsY", "Y", num0hitsY);
    cout << "Runs " << ii << ": fraction of events with 0 hits in X = " << Hnum0hitsX->Integral()/Hden0hits->Integral() 
	 << ", in Y = " << Hnum0hitsY->Integral()/Hden0hits->Integral() << endl;
    delete Hden0hits;
    delete Hnum0hitsX;
    delete Hnum0hitsY;
  }

  // ==========================================================
  // Now3: hits vs scintillator
  cout << endl;
  for (int ii=0; ii<11; ii++) {

    TTree* theTree;
    if (ii==0)  theTree = h4Mib10_700;
    if (ii==1)  theTree = h4Mib10_1000;
    if (ii==2)  theTree = h4Mib25_700;
    if (ii==3)  theTree = h4Mib25_1000;
    if (ii==4)  theTree = h4Mib25_1200;
    if (ii==5)  theTree = h4Rm5_700;
    if (ii==6)  theTree = h4Rm5_1000;
    if (ii==7)  theTree = h4Rm5_1200;
    if (ii==8)  theTree = h4Rm8_700;
    if (ii==9)  theTree = h4Rm8_1000;
    if (ii==10) theTree = h4Rm8_1200;

    TH1F *Hscint = new TH1F("Hscint", "Hscint", 400,0.,4000.);  
    theTree ->Project("Hscint",  "adc_data", "");
    TCanvas *c30 = new TCanvas("c30","",1);
    Hscint->Draw();
    c30->SetLogy();
    TString plotS = TString::Format("scint_runs%d.png",ii);
    c30->SaveAs(plotS);

    delete c30;
    delete Hscint;


    TH2F *HNYvsNx_0pc = new TH2F("HNYvsNx_0pc",   "HNYvsNx_0pc",   10,-0.5,9.5,10,-0.5,9.5);  
    TString string0pc = "adc_data<150";
    theTree ->Project("HNYvsNx_0pc", "n_hitsY:n_hitsX", string0pc);
    TCanvas *c30a = new TCanvas("c30a","",1);
    HNYvsNx_0pc->Draw("colz");
    TString plotSa = TString::Format("NhitsYvsNhitsX_0pc_runs%d.png",ii);
    c30a->SetLogz();
    c30a->SaveAs(plotSa);
    delete c30a; 
    delete HNYvsNx_0pc;

    TH2F *HNYvsNx_1pc = new TH2F("HNYvsNx_1pc",   "HNYvsNx_1pc",   10,-0.5,9.5,10,-0.5,9.5);  
    TString string1pc = "adc_data>200 && adc_data<700";
    theTree ->Project("HNYvsNx_1pc",   "n_hitsY:n_hitsX", string1pc);
    TCanvas *c30b = new TCanvas("c30b","",1);
    HNYvsNx_1pc->Draw("colz");
    TString plotSb = TString::Format("NhitsYvsNhitsX_1pc_runs%d.png",ii);
    c30b->SetLogz();
    c30b->SaveAs(plotSb);
    delete c30b; 
    delete HNYvsNx_1pc;

    TH2F *HNYvsNx_2pc = new TH2F("HNYvsNx_2pc",   "HNYvsNx_2pc",   10,-0.5,9.5,10,-0.5,9.5);  
    TString string2pc   = "adc_data>900 && adc_data<1400";
    theTree ->Project("HNYvsNx_2pc",   "n_hitsY:n_hitsX", string2pc);
    TCanvas *c30c = new TCanvas("c30c","",1);
    HNYvsNx_2pc->Draw("colz");
    TString plotSc = TString::Format("NhitsYvsNhitsX_2pc_runs%d.png",ii);
    c30c->SetLogz();
    c30c->SaveAs(plotSc);
    delete c30c; 
    delete HNYvsNx_2pc;

    TH2F *HNYvsNx_gt2pc = new TH2F("HNYvsNx_gt2pc", "HNYvsNx_gt2pc",   10,-0.5,9.5,10,-0.5,9.5);  
    TString stringGt2pc = "adc_data>1600";
    theTree ->Project("HNYvsNx_gt2pc", "n_hitsY:n_hitsX", stringGt2pc);
    cout << HNYvsNx_gt2pc->Integral() << endl;
    TCanvas *c30d = new TCanvas("c30d","",1);
    HNYvsNx_gt2pc->Draw("colz");
    TString plotSd = TString::Format("NhitsYvsNhitsX_gt2pc_runs%d.png",ii);
    c30d->SetLogz();
    c30d->SaveAs(plotSd);
    delete c30d; 
    delete HNYvsNx_gt2pc;
  }




}
	

//  LocalWords:  endl
