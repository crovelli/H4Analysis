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

void HodoBinps() {

  gStyle->SetOptStat(0);

  // inputs
  TFile* inFileBinp1Hv  = new TFile("/cmsrm/pc28_2/crovelli/data/imcp/binps/btf2016_HVscanBinp1.root");
  TFile* inFileBinp24Hv = new TFile("/cmsrm/pc28_2/crovelli/data/imcp/binps/btf2016_HVscanBinp4.root");   
  TFile* inFileBinp3Hv  = new TFile("/cmsrm/pc28_2/crovelli/data/imcp/binps/btf2016_HVscanBinp3.root");
  //
  TFile* inFileBinp124Timing = new TFile("/cmsrm/pc28_2/crovelli/data/imcp/binps/btf2016_RU5_2378.root");
  TFile* inFileBinp3Timing   = new TFile("/cmsrm/pc28_2/crovelli/data/imcp/binps/btf2016_RU4_2364.root");

  TTree* h4Binp1Hv  = (TTree*)inFileBinp1Hv->Get("h4");
  TTree* h4Binp24Hv = (TTree*)inFileBinp24Hv->Get("h4");
  TTree* h4Binp3Hv  = (TTree*)inFileBinp3Hv->Get("h4");
  //
  TTree* h4Binp124Timing = (TTree*)inFileBinp124Timing->Get("h4");
  TTree* h4Binp3Timing   = (TTree*)inFileBinp3Timing->Get("h4");

  // all runs
  float runsBinp1Hv[9]   = { 2363, 2364, 2365, 2366, 2367, 2368, 2369, 2370, 2371 };
  float runsBinp24Hv[11] = { 2352, 2353, 2354, 2355, 2356, 2357, 2358, 2359, 2360, 2361, 2362 };
  float runsBinp3Hv[11]  = { 2341, 2342, 2343, 2344, 2345, 2346, 2347, 2348, 2349, 2350, 2351 };
  float runsBinp124Timing[1] = { 2378 };
  float runsBinp3Timing[1]   = { 2364 };
  float runsBinp1[10]  = { 2363, 2364, 2365, 2366, 2367, 2368, 2369, 2370, 2371, 2378 };
  float runsBinp24[12] = { 2352, 2353, 2354, 2355, 2356, 2357, 2358, 2359, 2360, 2361, 2362, 2378 };
  float runsBinp3[12]  = { 2341, 2342, 2343, 2344, 2345, 2346, 2347, 2348, 2349, 2350, 2351, 2364 };


  // histos with the two coordinates: Binp1
  TH1F* xBinp1[10];  
  for (int ii=0; ii<10; ii++) {
    TString histoS;
    histoS.Form("xBinp1[%d]",ii);
    xBinp1[ii] = new TH1F(histoS, histoS, 32, -1.5, 30.5);
  }
  TH1F* yBinp1[10];  
  for (int ii=0; ii<10; ii++) {
    TString histoS;
    histoS.Form("yBinp1[%d]",ii);
    yBinp1[ii] = new TH1F(histoS, histoS, 32, -1.5, 30.5);
  }

  TH1F* xBinp24[12];  
  for (int ii=0; ii<12; ii++) {
    TString histoS;
    histoS.Form("xBinp24[%d]",ii);
    xBinp24[ii] = new TH1F(histoS, histoS, 32, -1.5, 30.5);
  }
  TH1F* yBinp24[12];  
  for (int ii=0; ii<12; ii++) {
    TString histoS;
    histoS.Form("yBinp24[%d]",ii);
    yBinp24[ii] = new TH1F(histoS, histoS, 32, -1.5, 30.5);
  }

  TH1F* xBinp3[12];  
  for (int ii=0; ii<12; ii++) {
    TString histoS;
    histoS.Form("xBinp3[%d]",ii);
    xBinp3[ii] = new TH1F(histoS, histoS, 32, -1.5, 30.5);
  }
  TH1F* yBinp3[12];  
  for (int ii=0; ii<12; ii++) {
    TString histoS;
    histoS.Form("yBinp3[%d]",ii);
    yBinp3[ii] = new TH1F(histoS, histoS, 32, -1.5, 30.5);
  }

  // denominator
  TString commonDen  = "adc_data>200 && adc_data<700 && amp_max[MiB2]>200 && amp_max[Rm2]>200 && amp_max[Rm2]<1200 && n_hitsX>0 && n_hitsX<3 && n_hitsY>0 && n_hitsY<3";
  TString commonDen1 = "adc_data>200 && adc_data<700 && amp_max[MiB2]>200 && n_hitsX>0 && n_hitsX<3 && n_hitsY>0 && n_hitsY<3";

  float xMeanBinp1[10], xRmsBinp1[10];
  for (int ii=0; ii<10; ii++) {
    TString histoS;
    histoS.Form("xBinp1[%d]",ii);
    TString theRunCut;
    if (ii<9)  theRunCut.Form(" && run==%d",(int)runsBinp1Hv[ii]);
    if (ii==9) theRunCut.Form(" && run==%d",(int)runsBinp124Timing[0]);
    TString theCut;
    if (ii<9)  theCut = commonDen1+theRunCut;
    if (ii==9) theCut = commonDen+theRunCut;
    if (ii<9)  h4Binp1Hv ->Project(histoS, "X",theCut);
    if (ii==9) h4Binp124Timing ->Project(histoS, "X",theCut);
    xMeanBinp1[ii] = xBinp1[ii] -> GetMean();
    xRmsBinp1[ii]  = xBinp1[ii] -> GetRMS();
  }
  float yMeanBinp1[10], yRmsBinp1[10];
  for (int ii=0; ii<10; ii++) {
    TString histoS;
    histoS.Form("yBinp1[%d]",ii);
    TString theRunCut;
    if (ii<9)  theRunCut.Form(" && run==%d",(int)runsBinp1Hv[ii]);
    if (ii==9) theRunCut.Form(" && run==%d",(int)runsBinp124Timing[0]);
    TString theCut;
    if (ii<9)  theCut = commonDen1+theRunCut;
    if (ii==9) theCut = commonDen+theRunCut;
    if (ii<9)  h4Binp1Hv ->Project(histoS, "Y",theCut);
    if (ii==9) h4Binp124Timing ->Project(histoS, "Y",theCut);
    yMeanBinp1[ii] = yBinp1[ii] -> GetMean();
    yRmsBinp1[ii]  = yBinp1[ii] -> GetRMS();
  }

  float xMeanBinp24[12], xRmsBinp24[12];
  for (int ii=0; ii<12; ii++) {
    TString histoS;
    histoS.Form("xBinp24[%d]",ii);
    TString theRunCut;
    if (ii<11)  theRunCut.Form(" && run==%d",(int)runsBinp24Hv[ii]);
    if (ii==11) theRunCut.Form(" && run==%d",(int)runsBinp124Timing[0]);
    TString theCut = commonDen+theRunCut;
    if (ii<11)  h4Binp24Hv ->Project(histoS, "X",theCut);
    if (ii==11) h4Binp124Timing ->Project(histoS, "X",theCut);
    xMeanBinp24[ii] = xBinp24[ii] -> GetMean();
    xRmsBinp24[ii]  = xBinp24[ii] -> GetRMS();
  }
  float yMeanBinp24[12], yRmsBinp24[12];
  for (int ii=0; ii<12; ii++) {
    TString histoS;
    histoS.Form("yBinp24[%d]",ii);
    TString theRunCut;
    if (ii<11)  theRunCut.Form(" && run==%d",(int)runsBinp24Hv[ii]);
    if (ii==11) theRunCut.Form(" && run==%d",(int)runsBinp124Timing[0]);
    TString theCut = commonDen+theRunCut;
    if (ii<11)  h4Binp24Hv ->Project(histoS, "Y",theCut);
    if (ii==11) h4Binp124Timing ->Project(histoS, "Y",theCut);
    yMeanBinp24[ii] = yBinp24[ii] -> GetMean();
    yRmsBinp24[ii]  = yBinp24[ii] -> GetRMS();
  }

  float xMeanBinp3[12], xRmsBinp3[12];
  for (int ii=0; ii<12; ii++) {
    TString histoS;
    histoS.Form("xBinp3[%d]",ii);
    TString theRunCut;
    if (ii<11)  theRunCut.Form(" && run==%d",(int)runsBinp3Hv[ii]);
    if (ii==11) theRunCut.Form(" && run==%d",(int)runsBinp3Timing[0]);
    TString theCut;
    if (ii<11)  theCut = commonDen+theRunCut;
    if (ii==11) theCut = commonDen1+theRunCut;
    if (ii<11)  h4Binp3Hv ->Project(histoS, "X",theCut);
    if (ii==11) h4Binp3Timing ->Project(histoS, "X",theCut);
    xMeanBinp3[ii] = xBinp3[ii] -> GetMean();
    xRmsBinp3[ii]  = xBinp3[ii] -> GetRMS();
  }
  float yMeanBinp3[12], yRmsBinp3[12];
  for (int ii=0; ii<12; ii++) {
    TString histoS;
    histoS.Form("yBinp3[%d]",ii);
    TString theRunCut;
    if (ii<11)  theRunCut.Form(" && run==%d",(int)runsBinp3Hv[ii]);
    if (ii==11) theRunCut.Form(" && run==%d",(int)runsBinp3Timing[0]);
    TString theCut;
    if (ii<11)  theCut = commonDen+theRunCut;
    if (ii==11) theCut = commonDen1+theRunCut;
    if (ii<11)  h4Binp3Hv ->Project(histoS, "Y",theCut);
    if (ii==11) h4Binp3Timing ->Project(histoS, "Y",theCut);
    yMeanBinp3[ii] = yBinp3[ii] -> GetMean();
    yRmsBinp3[ii]  = yBinp3[ii] -> GetRMS();
  }


  // history plots
  TGraph* G_xMeanBinp1 = new TGraph(10, runsBinp1, xMeanBinp1);
  TGraph* G_yMeanBinp1 = new TGraph(10, runsBinp1, yMeanBinp1);
  TGraph* G_xRmsBinp1  = new TGraph(10, runsBinp1, xRmsBinp1);
  TGraph* G_yRmsBinp1  = new TGraph(10, runsBinp1, yRmsBinp1);
  G_xMeanBinp1->SetMarkerStyle(20);
  G_xMeanBinp1->SetMarkerColor(1);
  G_yMeanBinp1->SetMarkerStyle(21);
  G_yMeanBinp1->SetMarkerColor(2);
  G_xRmsBinp1->SetMarkerStyle(20);
  G_xRmsBinp1->SetMarkerColor(1);
  G_yRmsBinp1->SetMarkerStyle(21);
  G_yRmsBinp1->SetMarkerColor(2);

  TGraph* G_xMeanBinp24 = new TGraph(12, runsBinp24, xMeanBinp24);
  TGraph* G_yMeanBinp24 = new TGraph(12, runsBinp24, yMeanBinp24);
  TGraph* G_xRmsBinp24  = new TGraph(12, runsBinp24, xRmsBinp24);
  TGraph* G_yRmsBinp24  = new TGraph(12, runsBinp24, yRmsBinp24);
  G_xMeanBinp24->SetMarkerStyle(20);
  G_xMeanBinp24->SetMarkerColor(1);
  G_yMeanBinp24->SetMarkerStyle(21);
  G_yMeanBinp24->SetMarkerColor(2);
  G_xRmsBinp24->SetMarkerStyle(20);
  G_xRmsBinp24->SetMarkerColor(1);
  G_yRmsBinp24->SetMarkerStyle(21);
  G_yRmsBinp24->SetMarkerColor(2);

  TGraph* G_xMeanBinp3 = new TGraph(12, runsBinp3, xMeanBinp3);
  TGraph* G_yMeanBinp3 = new TGraph(12, runsBinp3, yMeanBinp3);
  TGraph* G_xRmsBinp3  = new TGraph(12, runsBinp3, xRmsBinp3);
  TGraph* G_yRmsBinp3  = new TGraph(12, runsBinp3, yRmsBinp3);
  G_xMeanBinp3->SetMarkerStyle(20);
  G_xMeanBinp3->SetMarkerColor(1);
  G_yMeanBinp3->SetMarkerStyle(21);
  G_yMeanBinp3->SetMarkerColor(2);
  G_xRmsBinp3->SetMarkerStyle(20);
  G_xRmsBinp3->SetMarkerColor(1);
  G_yRmsBinp3->SetMarkerStyle(21);
  G_yRmsBinp3->SetMarkerColor(2);


  // -------------------------------- Plots ----------------------------
  TLegend *legA;
  legA = new TLegend(0.1,0.6,0.4,0.9);
  legA->SetFillStyle(0);
  legA->SetBorderSize(0);
  legA->SetTextSize(0.05);
  legA->SetFillColor(0);
  legA->AddEntry(G_xMeanBinp3,  "X", "p");
  legA->AddEntry(G_yMeanBinp3,  "Y", "p");


  // Binp1
  TCanvas* c1a = new TCanvas("c1a","c",1);
  c1a->SetGrid();
  TH2F *myHbinp1 = new TH2F("myHbinp1","",100,2353, 2388,100,10,20);
  myHbinp1->GetXaxis()->SetTitle("run");
  myHbinp1->GetYaxis()->SetTitle("mean");
  myHbinp1->Draw();
  G_xMeanBinp1->Draw("Psame");
  G_yMeanBinp1->Draw("Psame");
  legA->Draw();
  c1a->SaveAs("historyMeanBinp1.png");

  TCanvas* c1b = new TCanvas("c1b","c",1);
  c1b->SetGrid();
  TH2F *myHRbinp1 = new TH2F("myHRbinp1","",100,2353, 2388,100,0,10);
  myHRbinp1->GetXaxis()->SetTitle("run");
  myHRbinp1->GetYaxis()->SetTitle("RMS");
  myHRbinp1->Draw();
  G_xRmsBinp1->Draw("Psame");
  G_yRmsBinp1->Draw("Psame");
  legA->Draw();
  c1b->SaveAs("historyRmsBinp1.png");

  TCanvas* c2a = new TCanvas("c2a","c",1);
  c2a->SetGrid();
  TH2F *myHbinp24 = new TH2F("myHbinp24","",100,2342, 2388,100,10,20);
  myHbinp24->GetXaxis()->SetTitle("run");
  myHbinp24->GetYaxis()->SetTitle("mean");
  myHbinp24->Draw();
  G_xMeanBinp24->Draw("Psame");
  G_yMeanBinp24->Draw("Psame");
  legA->Draw();
  c2a->SaveAs("historyMeanBinp24.png");

  TCanvas* c2b = new TCanvas("c2b","c",1);
  c2b->SetGrid();
  TH2F *myHRbinp24 = new TH2F("myHRbinp24","",100,2342, 2388,100,0,10);
  myHRbinp24->GetXaxis()->SetTitle("run");
  myHRbinp24->GetYaxis()->SetTitle("RMS");
  myHRbinp24->Draw();
  G_xRmsBinp24->Draw("Psame");
  G_yRmsBinp24->Draw("Psame");
  legA->Draw();
  c2b->SaveAs("historyRmsBinp24.png");

  TCanvas* c3a = new TCanvas("c3a","c",1);
  c3a->SetGrid();
  TH2F *myHbinp3 = new TH2F("myHbinp3","",100,2331, 2374,100,10,20);
  myHbinp3->GetXaxis()->SetTitle("run");
  myHbinp3->GetYaxis()->SetTitle("mean");
  myHbinp3->Draw();
  G_xMeanBinp3->Draw("Psame");
  G_yMeanBinp3->Draw("Psame");
  legA->Draw();
  c3a->SaveAs("historyMeanBinp3.png");

  TCanvas* c3b = new TCanvas("c3b","c",1);
  c3b->SetGrid();
  TH2F *myHRbinp3 = new TH2F("myHRbinp3","",100,2331, 2374,100,0,10);
  myHRbinp3->GetXaxis()->SetTitle("run");
  myHRbinp3->GetYaxis()->SetTitle("RMS");
  myHRbinp3->Draw();
  G_xRmsBinp3->Draw("Psame");
  G_yRmsBinp3->Draw("Psame");
  legA->Draw();
  c3b->SaveAs("historyRmsBinp3.png");


  // ==========================================================
  // Now: only for runs at plateau + timing, Eff vs X and vs Y
  TH2F *myHx = new TH2F("myHx","",16,-1.5,30.5,100,0.,1.);
  TH2F *myHy = new TH2F("myHy","",16,-1.5,30.5,100,0.,1.);
  myHx->GetXaxis()->SetTitle("X");
  myHy->GetXaxis()->SetTitle("Y");
  myHx->GetYaxis()->SetTitle("Efficiency");
  myHy->GetYaxis()->SetTitle("Efficiency");


  // Binp1 HV
  TString denBinp1Hv_ref   = "adc_data>200 && adc_data<700 && run==2363 && n_hitsX>0 && n_hitsX<3 && n_hitsY>0 && n_hitsY<3";  
  TString denBinp1Hv_binp  = denBinp1Hv_ref  + " && amp_max[MiB2]>200";
  TString numBinp1Hv_mib2  = denBinp1Hv_ref  + " && amp_max[MiB2]>20";
  TString numBinp1Hv_binp1 = denBinp1Hv_binp + " && amp_max[BINP1]>20";

  TH1F *denX_Mib2_RunBinp1Hv  = new TH1F("denX_Mib2_RunBinp1Hv",  "denX_Mib2_RunBinp1Hv",  16,-1.5,30.5);  
  TH1F *denY_Mib2_RunBinp1Hv  = new TH1F("denY_Mib2_RunBinp1Hv",  "denY_Mib2_RunBinp1Hv",  16,-1.5,30.5);
  TH1F *denX_Binp1_RunBinp1Hv = new TH1F("denX_Binp1_RunBinp1Hv", "denX_Binp1_RunBinp1Hv", 16,-1.5,30.5);  
  TH1F *denY_Binp1_RunBinp1Hv = new TH1F("denY_Binp1_RunBinp1Hv", "denY_Binp1_RunBinp1Hv", 16,-1.5,30.5);
  TH1F *numX_Mib2_RunBinp1Hv  = new TH1F("numX_Mib2_RunBinp1Hv",  "numX_Mib2_RunBinp1Hv",  16,-1.5,30.5);  
  TH1F *numY_Mib2_RunBinp1Hv  = new TH1F("numY_Mib2_RunBinp1Hv",  "numY_Mib2_RunBinp1Hv",  16,-1.5,30.5);  
  TH1F *numX_Binp1_RunBinp1Hv = new TH1F("numX_Binp1_RunBinp1Hv", "numX_Binp1_RunBinp1Hv", 16,-1.5,30.5);  
  TH1F *numY_Binp1_RunBinp1Hv = new TH1F("numY_Binp1_RunBinp1Hv", "numY_Binp1_RunBinp1Hv", 16,-1.5,30.5);  

  h4Binp1Hv ->Project("denX_Mib2_RunBinp1Hv",  "X", denBinp1Hv_ref);
  h4Binp1Hv ->Project("denY_Mib2_RunBinp1Hv",  "Y", denBinp1Hv_ref);
  h4Binp1Hv ->Project("denX_Binp1_RunBinp1Hv", "X", denBinp1Hv_binp);
  h4Binp1Hv ->Project("denY_Binp1_RunBinp1Hv", "Y", denBinp1Hv_binp);
  h4Binp1Hv ->Project("numX_Mib2_RunBinp1Hv",  "X", numBinp1Hv_mib2);
  h4Binp1Hv ->Project("numY_Mib2_RunBinp1Hv",  "Y", numBinp1Hv_mib2);
  h4Binp1Hv ->Project("numX_Binp1_RunBinp1Hv", "X", numBinp1Hv_binp1);
  h4Binp1Hv ->Project("numY_Binp1_RunBinp1Hv", "Y", numBinp1Hv_binp1);

  TGraphAsymmErrors* effX_Mib2_RunBinp1Hv = new TGraphAsymmErrors(numX_Mib2_RunBinp1Hv, denX_Mib2_RunBinp1Hv);
  TGraphAsymmErrors* effY_Mib2_RunBinp1Hv = new TGraphAsymmErrors(numY_Mib2_RunBinp1Hv, denY_Mib2_RunBinp1Hv);
  effX_Mib2_RunBinp1Hv->SetMarkerStyle(20);
  effX_Mib2_RunBinp1Hv->SetMarkerColor(1);
  effX_Mib2_RunBinp1Hv->SetLineColor(1);
  effY_Mib2_RunBinp1Hv->SetMarkerStyle(21);
  effY_Mib2_RunBinp1Hv->SetMarkerColor(2);
  effY_Mib2_RunBinp1Hv->SetLineColor(2);

  TGraphAsymmErrors* effX_Binp1_RunBinp1Hv = new TGraphAsymmErrors(numX_Binp1_RunBinp1Hv, denX_Binp1_RunBinp1Hv);
  TGraphAsymmErrors* effY_Binp1_RunBinp1Hv = new TGraphAsymmErrors(numY_Binp1_RunBinp1Hv, denY_Binp1_RunBinp1Hv);
  effX_Binp1_RunBinp1Hv->SetMarkerStyle(20);
  effX_Binp1_RunBinp1Hv->SetMarkerColor(1);
  effX_Binp1_RunBinp1Hv->SetLineColor(1);
  effY_Binp1_RunBinp1Hv->SetMarkerStyle(21);
  effY_Binp1_RunBinp1Hv->SetMarkerColor(2);
  effY_Binp1_RunBinp1Hv->SetLineColor(2);

  TCanvas* c110a = new TCanvas("c110a","c",1);
  c110a->Divide(2,1);
  c110a->cd(1); myHx->Draw(); effX_Mib2_RunBinp1Hv->Draw("Psame");
  c110a->cd(2); myHy->Draw(); effY_Mib2_RunBinp1Hv->Draw("Psame");
  c110a->SaveAs("EffMib2_VsCoord_runHvBinp1.png");  

  TCanvas* c110c = new TCanvas("c110c","c",1);
  c110c->Divide(2,1);
  c110c->cd(1); myHx->Draw(); effX_Binp1_RunBinp1Hv->Draw("Psame");
  c110c->cd(2); myHy->Draw(); effY_Binp1_RunBinp1Hv->Draw("Psame");
  c110c->SaveAs("EffBinp1_VsCoord_runHvBinp1.png");  

  TH2F *den_Mib2_RunBinp1Hv  = new TH2F("den_Mib2_RunBinp1Hv",  "den_Mib2_RunBinp1Hv",  16,-1.5,30.5, 16,-1.5,30.5);
  TH2F *den_Binp1_RunBinp1Hv = new TH2F("den_Binp1_RunBinp1Hv", "den_Binp1_RunBinp1Hv", 16,-1.5,30.5, 16,-1.5,30.5);
  TH2F *num_Mib2_RunBinp1Hv  = new TH2F("num_Mib2_RunBinp1Hv",  "num_Mib2_RunBinp1Hv",  16,-1.5,30.5, 16,-1.5,30.5);
  TH2F *num_Binp1_RunBinp1Hv = new TH2F("num_Binp1_RunBinp1Hv", "num_Binp1_RunBinp1Hv", 16,-1.5,30.5, 16,-1.5,30.5);

  h4Binp1Hv ->Project("den_Mib2_RunBinp1Hv",  "Y:X", denBinp1Hv_ref);
  h4Binp1Hv ->Project("den_Binp1_RunBinp1Hv", "Y:X", denBinp1Hv_binp);
  h4Binp1Hv ->Project("num_Mib2_RunBinp1Hv",  "Y:X", numBinp1Hv_mib2);
  h4Binp1Hv ->Project("num_Binp1_RunBinp1Hv", "Y:X", numBinp1Hv_binp1);
  
  TH2F *eff2dim_Mib2_RunBinp1Hv = (TH2F*)num_Mib2_RunBinp1Hv->Clone();
  eff2dim_Mib2_RunBinp1Hv->Divide(den_Mib2_RunBinp1Hv);
  TH2F *eff2dim_Binp1_RunBinp1Hv = (TH2F*)num_Binp1_RunBinp1Hv->Clone();
  eff2dim_Binp1_RunBinp1Hv->Divide(den_Binp1_RunBinp1Hv);

  TCanvas* c110a2 = new TCanvas("c110a2","c",1);
  eff2dim_Mib2_RunBinp1Hv->Draw("colz");
  c110a2->SaveAs("EffMib2_2dim_runHvBinp1.png");  

  TCanvas* c110b2 = new TCanvas("c110b2","c",1);
  eff2dim_Binp1_RunBinp1Hv->Draw("colz");
  c110b2->SaveAs("Effbinp1_2dim_runHvBinp1.png");  


  // Binp24 HV
  TString denBinp24Hv_ref   = "adc_data>200 && adc_data<700 && run==2352 && n_hitsX>0 && n_hitsX<3 && n_hitsY>0 && n_hitsY<3";  
  TString denBinp24Hv_binp  = denBinp24Hv_ref + " && amp_max[MiB2]>200 && amp_max[Rm2]>200";
  TString numBinp24Hv_mib2  = denBinp24Hv_ref + " && amp_max[MiB2]>20";
  TString numBinp24Hv_rm2   = denBinp24Hv_ref + " && amp_max[Rm2]>20";
  TString numBinp24Hv_binp2 = denBinp24Hv_binp + " && amp_max[BINP2]>20";
  TString numBinp24Hv_binp4 = denBinp24Hv_binp + " && amp_max[BINP4]>20";

  TH1F *denX_Mib2_RunBinp24Hv  = new TH1F("denX_Mib2_RunBinp24Hv", "denX_Mib2_RunBinp24Hv", 16,-1.5,30.5);  
  TH1F *denY_Mib2_RunBinp24Hv  = new TH1F("denY_Mib2_RunBinp24Hv", "denY_Mib2_RunBinp24Hv", 16,-1.5,30.5);  
  TH1F *denX_Rm2_RunBinp24Hv   = new TH1F("denX_Rm2_RunBinp24Hv",  "denX_Rm2_RunBinp24Hv",  16,-1.5,30.5);  
  TH1F *denY_Rm2_RunBinp24Hv   = new TH1F("denY_Rm2_RunBinp24Hv",  "denY_Rm2_RunBinp24Hv",  16,-1.5,30.5);  
  TH1F *denX_Binp2_RunBinp24Hv = new TH1F("denX_Binp2_RunBinp24Hv","denX_Binp2_RunBinp24Hv",16,-1.5,30.5);  
  TH1F *denY_Binp2_RunBinp24Hv = new TH1F("denY_Binp2_RunBinp24Hv","denY_Binp2_RunBinp24Hv",16,-1.5,30.5);  
  TH1F *denX_Binp4_RunBinp24Hv = new TH1F("denX_Binp4_RunBinp24Hv","denX_Binp4_RunBinp24Hv",16,-1.5,30.5);  
  TH1F *denY_Binp4_RunBinp24Hv = new TH1F("denY_Binp4_RunBinp24Hv","denY_Binp4_RunBinp24Hv",16,-1.5,30.5);  
  TH1F *numX_Mib2_RunBinp24Hv  = new TH1F("numX_Mib2_RunBinp24Hv", "numX_Mib2_RunBinp24Hv", 16,-1.5,30.5);  
  TH1F *numY_Mib2_RunBinp24Hv  = new TH1F("numY_Mib2_RunBinp24Hv", "numY_Mib2_RunBinp24Hv", 16,-1.5,30.5);  
  TH1F *numX_Rm2_RunBinp24Hv   = new TH1F("numX_Rm2_RunBinp24Hv",  "numX_Rm2_RunBinp24Hv",  16,-1.5,30.5);  
  TH1F *numY_Rm2_RunBinp24Hv   = new TH1F("numY_Rm2_RunBinp24Hv",  "numY_Rm2_RunBinp24Hv",  16,-1.5,30.5);  
  TH1F *numX_Binp2_RunBinp24Hv = new TH1F("numX_Binp2_RunBinp24Hv","numX_Binp2_RunBinp24Hv",16,-1.5,30.5);  
  TH1F *numY_Binp2_RunBinp24Hv = new TH1F("numY_Binp2_RunBinp24Hv","numY_Binp2_RunBinp24Hv",16,-1.5,30.5);  
  TH1F *numX_Binp4_RunBinp24Hv = new TH1F("numX_Binp4_RunBinp24Hv","numX_Binp4_RunBinp24Hv",16,-1.5,30.5);  
  TH1F *numY_Binp4_RunBinp24Hv = new TH1F("numY_Binp4_RunBinp24Hv","numY_Binp4_RunBinp24Hv",16,-1.5,30.5);  

  h4Binp24Hv ->Project("denX_Mib2_RunBinp24Hv",  "X", denBinp24Hv_ref);
  h4Binp24Hv ->Project("denY_Mib2_RunBinp24Hv",  "Y", denBinp24Hv_ref);
  h4Binp24Hv ->Project("denX_Rm2_RunBinp24Hv",   "X", denBinp24Hv_ref);
  h4Binp24Hv ->Project("denY_Rm2_RunBinp24Hv",   "Y", denBinp24Hv_ref);
  h4Binp24Hv ->Project("denX_Binp2_RunBinp24Hv", "X", denBinp24Hv_binp);
  h4Binp24Hv ->Project("denY_Binp2_RunBinp24Hv", "Y", denBinp24Hv_binp);
  h4Binp24Hv ->Project("denX_Binp4_RunBinp24Hv", "X", denBinp24Hv_binp);
  h4Binp24Hv ->Project("denY_Binp4_RunBinp24Hv", "Y", denBinp24Hv_binp);
  h4Binp24Hv ->Project("numX_Mib2_RunBinp24Hv",  "X", numBinp24Hv_mib2);
  h4Binp24Hv ->Project("numY_Mib2_RunBinp24Hv",  "Y", numBinp24Hv_mib2);
  h4Binp24Hv ->Project("numX_Rm2_RunBinp24Hv",   "X", numBinp24Hv_rm2);
  h4Binp24Hv ->Project("numY_Rm2_RunBinp24Hv",   "Y", numBinp24Hv_rm2);
  h4Binp24Hv ->Project("numX_Binp2_RunBinp24Hv", "X", numBinp24Hv_binp2);
  h4Binp24Hv ->Project("numY_Binp2_RunBinp24Hv", "Y", numBinp24Hv_binp2);
  h4Binp24Hv ->Project("numX_Binp4_RunBinp24Hv", "X", numBinp24Hv_binp4);
  h4Binp24Hv ->Project("numY_Binp4_RunBinp24Hv", "Y", numBinp24Hv_binp4);

  TGraphAsymmErrors* effX_Mib2_RunBinp24Hv = new TGraphAsymmErrors(numX_Mib2_RunBinp24Hv, denX_Mib2_RunBinp24Hv);
  TGraphAsymmErrors* effY_Mib2_RunBinp24Hv = new TGraphAsymmErrors(numY_Mib2_RunBinp24Hv, denY_Mib2_RunBinp24Hv);
  effX_Mib2_RunBinp24Hv->SetMarkerStyle(20);
  effX_Mib2_RunBinp24Hv->SetMarkerColor(1);
  effX_Mib2_RunBinp24Hv->SetLineColor(1);
  effY_Mib2_RunBinp24Hv->SetMarkerStyle(21);
  effY_Mib2_RunBinp24Hv->SetMarkerColor(2);
  effY_Mib2_RunBinp24Hv->SetLineColor(2);

  TGraphAsymmErrors* effX_Rm2_RunBinp24Hv = new TGraphAsymmErrors(numX_Rm2_RunBinp24Hv, denX_Rm2_RunBinp24Hv);
  TGraphAsymmErrors* effY_Rm2_RunBinp24Hv = new TGraphAsymmErrors(numY_Rm2_RunBinp24Hv, denY_Rm2_RunBinp24Hv);
  effX_Rm2_RunBinp24Hv->SetMarkerStyle(20);
  effX_Rm2_RunBinp24Hv->SetMarkerColor(1);
  effX_Rm2_RunBinp24Hv->SetLineColor(1);
  effY_Rm2_RunBinp24Hv->SetMarkerStyle(21);
  effY_Rm2_RunBinp24Hv->SetMarkerColor(2);
  effY_Rm2_RunBinp24Hv->SetLineColor(2);

  TGraphAsymmErrors* effX_Binp2_RunBinp24Hv = new TGraphAsymmErrors(numX_Binp2_RunBinp24Hv, denX_Binp2_RunBinp24Hv);
  TGraphAsymmErrors* effY_Binp2_RunBinp24Hv = new TGraphAsymmErrors(numY_Binp2_RunBinp24Hv, denY_Binp2_RunBinp24Hv);
  effX_Binp2_RunBinp24Hv->SetMarkerStyle(20);
  effX_Binp2_RunBinp24Hv->SetMarkerColor(1);
  effX_Binp2_RunBinp24Hv->SetLineColor(1);
  effY_Binp2_RunBinp24Hv->SetMarkerStyle(21);
  effY_Binp2_RunBinp24Hv->SetMarkerColor(2);
  effY_Binp2_RunBinp24Hv->SetLineColor(2);

  TGraphAsymmErrors* effX_Binp4_RunBinp24Hv = new TGraphAsymmErrors(numX_Binp4_RunBinp24Hv, denX_Binp4_RunBinp24Hv);
  TGraphAsymmErrors* effY_Binp4_RunBinp24Hv = new TGraphAsymmErrors(numY_Binp4_RunBinp24Hv, denY_Binp4_RunBinp24Hv);
  effX_Binp4_RunBinp24Hv->SetMarkerStyle(20);
  effX_Binp4_RunBinp24Hv->SetMarkerColor(1);
  effX_Binp4_RunBinp24Hv->SetLineColor(1);
  effY_Binp4_RunBinp24Hv->SetMarkerStyle(21);
  effY_Binp4_RunBinp24Hv->SetMarkerColor(2);
  effY_Binp4_RunBinp24Hv->SetLineColor(2);

  TCanvas* c210a = new TCanvas("c210a","c",1);
  c210a->Divide(2,1);
  c210a->cd(1); myHx->Draw(); effX_Mib2_RunBinp24Hv->Draw("Psame");
  c210a->cd(2); myHy->Draw(); effY_Mib2_RunBinp24Hv->Draw("Psame");
  c210a->SaveAs("EffMib2_VsCoord_runHvBinp24.png");  

  TCanvas* c210b = new TCanvas("c210b","c",1);
  c210b->Divide(2,1);
  c210b->cd(1); myHx->Draw(); effX_Rm2_RunBinp24Hv->Draw("Psame");
  c210b->cd(2); myHy->Draw(); effY_Rm2_RunBinp24Hv->Draw("Psame");
  c210b->SaveAs("EffRm2_VsCoord_runHvBinp24.png");  

  TCanvas* c210c = new TCanvas("c210c","c",1);
  c210c->Divide(2,1);
  c210c->cd(1); myHx->Draw(); effX_Binp2_RunBinp24Hv->Draw("Psame");
  c210c->cd(2); myHy->Draw(); effY_Binp2_RunBinp24Hv->Draw("Psame");
  c210c->SaveAs("EffBinp2_VsCoord_runHvBinp24.png");  

  TCanvas* c210d = new TCanvas("c210d","c",1);
  c210d->Divide(2,1);
  c210d->cd(1); myHx->Draw(); effX_Binp4_RunBinp24Hv->Draw("Psame");
  c210d->cd(2); myHy->Draw(); effY_Binp4_RunBinp24Hv->Draw("Psame");
  c210d->SaveAs("EffBinp4_VsCoord_runHvBinp24.png");  

  TH2F *den_Mib2_RunBinp24Hv  = new TH2F("den_Mib2_RunBinp24Hv", "den_Mib2_RunBinp24Hv", 16,-1.5,30.5, 16,-1.5,30.5);  
  TH2F *den_Rm2_RunBinp24Hv   = new TH2F("den_Rm2_RunBinp24Hv",  "den_Rm2_RunBinp24Hv",  16,-1.5,30.5, 16,-1.5,30.5);  
  TH2F *den_Binp2_RunBinp24Hv = new TH2F("den_Binp2_RunBinp24Hv","den_Binp2_RunBinp24Hv",16,-1.5,30.5, 16,-1.5,30.5);  
  TH2F *den_Binp4_RunBinp24Hv = new TH2F("den_Binp4_RunBinp24Hv","den_Binp4_RunBinp24Hv",16,-1.5,30.5, 16,-1.5,30.5);  
  TH2F *num_Mib2_RunBinp24Hv  = new TH2F("num_Mib2_RunBinp24Hv", "num_Mib2_RunBinp24Hv", 16,-1.5,30.5, 16,-1.5,30.5);  
  TH2F *num_Rm2_RunBinp24Hv   = new TH2F("num_Rm2_RunBinp24Hv",  "num_Rm2_RunBinp24Hv",  16,-1.5,30.5, 16,-1.5,30.5);  
  TH2F *num_Binp2_RunBinp24Hv = new TH2F("num_Binp2_RunBinp24Hv","num_Binp2_RunBinp24Hv",16,-1.5,30.5, 16,-1.5,30.5);  
  TH2F *num_Binp4_RunBinp24Hv = new TH2F("num_Binp4_RunBinp24Hv","num_Binp4_RunBinp24Hv",16,-1.5,30.5, 16,-1.5,30.5);  
  h4Binp24Hv ->Project("den_Mib2_RunBinp24Hv",  "Y:X", denBinp24Hv_ref);
  h4Binp24Hv ->Project("den_Rm2_RunBinp24Hv",   "Y:X", denBinp24Hv_ref);
  h4Binp24Hv ->Project("den_Binp2_RunBinp24Hv", "Y:X", denBinp24Hv_binp);
  h4Binp24Hv ->Project("den_Binp4_RunBinp24Hv", "Y:X", denBinp24Hv_binp);
  h4Binp24Hv ->Project("num_Mib2_RunBinp24Hv",  "Y:X", numBinp24Hv_mib2);
  h4Binp24Hv ->Project("num_Rm2_RunBinp24Hv",   "Y:X", numBinp24Hv_rm2);
  h4Binp24Hv ->Project("num_Binp2_RunBinp24Hv", "Y:X", numBinp24Hv_binp2);
  h4Binp24Hv ->Project("num_Binp4_RunBinp24Hv", "Y:X", numBinp24Hv_binp4);

  TH2F *eff2dim_Mib2_RunBinp24Hv = (TH2F*)num_Mib2_RunBinp24Hv->Clone();
  eff2dim_Mib2_RunBinp24Hv->Divide(den_Mib2_RunBinp24Hv);
  TH2F *eff2dim_Rm2_RunBinp24Hv = (TH2F*)num_Rm2_RunBinp24Hv->Clone();
  eff2dim_Rm2_RunBinp24Hv->Divide(den_Rm2_RunBinp24Hv);
  TH2F *eff2dim_Binp2_RunBinp24Hv = (TH2F*)num_Binp2_RunBinp24Hv->Clone();
  eff2dim_Binp2_RunBinp24Hv->Divide(den_Binp2_RunBinp24Hv);
  TH2F *eff2dim_Binp4_RunBinp24Hv = (TH2F*)num_Binp4_RunBinp24Hv->Clone();
  eff2dim_Binp4_RunBinp24Hv->Divide(den_Binp4_RunBinp24Hv);

  TCanvas* c210a2 = new TCanvas("c210a2","c",1);
  eff2dim_Mib2_RunBinp24Hv->Draw("colz");
  c210a2->SaveAs("EffMib2_2dim_runHvBinp24.png");  
  TCanvas* c210b2 = new TCanvas("c210b2","c",1);
  eff2dim_Rm2_RunBinp24Hv->Draw("colz");
  c210b2->SaveAs("EffRm2_2dim_runHvBinp24.png");  
  TCanvas* c210c2 = new TCanvas("c210c2","c",1);
  eff2dim_Binp2_RunBinp24Hv->Draw("colz");
  c210c2->SaveAs("EffBinp2_2dim_runHvBinp24.png");  
  TCanvas* c210d2 = new TCanvas("c210d2","c",1);
  eff2dim_Binp4_RunBinp24Hv->Draw("colz");
  c210d2->SaveAs("EffBinp4_2dim_runHvBinp24.png");  


  // Binp3 HV
  TString denBinp3Hv_ref   = "adc_data>200 && adc_data<700 && run==2341 && n_hitsX>0 && n_hitsX<3 && n_hitsY>0 && n_hitsY<3";  
  TString denBinp3Hv_binp  = denBinp3Hv_ref + " && amp_max[MiB2]>200 && amp_max[Rm2]>200";
  TString numBinp3Hv_mib2  = denBinp3Hv_ref + " && amp_max[MiB2]>20";
  TString numBinp3Hv_rm2   = denBinp3Hv_ref + " && amp_max[Rm2]>20";
  TString numBinp3Hv_binp3 = denBinp3Hv_binp + " && amp_max[BINP3]>20";

  TH1F *denX_Mib2_RunBinp3Hv  = new TH1F("denX_Mib2_RunBinp3Hv", "denX_Mib2_RunBinp3Hv", 16,-1.5,30.5);  
  TH1F *denY_Mib2_RunBinp3Hv  = new TH1F("denY_Mib2_RunBinp3Hv", "denY_Mib2_RunBinp3Hv", 16,-1.5,30.5);  
  TH1F *denX_Rm2_RunBinp3Hv   = new TH1F("denX_Rm2_RunBinp3Hv",  "denX_Rm2_RunBinp3Hv",  16,-1.5,30.5);  
  TH1F *denY_Rm2_RunBinp3Hv   = new TH1F("denY_Rm2_RunBinp3Hv",  "denY_Rm2_RunBinp3Hv",  16,-1.5,30.5);  
  TH1F *denX_Binp3_RunBinp3Hv = new TH1F("denX_Binp3_RunBinp3Hv","denX_Binp3_RunBinp3Hv",16,-1.5,30.5);  
  TH1F *denY_Binp3_RunBinp3Hv = new TH1F("denY_Binp3_RunBinp3Hv","denY_Binp3_RunBinp3Hv",16,-1.5,30.5);  
  TH1F *numX_Mib2_RunBinp3Hv  = new TH1F("numX_Mib2_RunBinp3Hv", "numX_Mib2_RunBinp3Hv", 16,-1.5,30.5);  
  TH1F *numY_Mib2_RunBinp3Hv  = new TH1F("numY_Mib2_RunBinp3Hv", "numY_Mib2_RunBinp3Hv", 16,-1.5,30.5);  
  TH1F *numX_Rm2_RunBinp3Hv   = new TH1F("numX_Rm2_RunBinp3Hv",  "numX_Rm2_RunBinp3Hv",  16,-1.5,30.5);  
  TH1F *numY_Rm2_RunBinp3Hv   = new TH1F("numY_Rm2_RunBinp3Hv",  "numY_Rm2_RunBinp3Hv",  16,-1.5,30.5);  
  TH1F *numX_Binp3_RunBinp3Hv = new TH1F("numX_Binp3_RunBinp3Hv","numX_Binp3_RunBinp3Hv",16,-1.5,30.5);  
  TH1F *numY_Binp3_RunBinp3Hv = new TH1F("numY_Binp3_RunBinp3Hv","numY_Binp3_RunBinp3Hv",16,-1.5,30.5);  

  h4Binp3Hv ->Project("denX_Mib2_RunBinp3Hv",  "X", denBinp3Hv_ref);
  h4Binp3Hv ->Project("denY_Mib2_RunBinp3Hv",  "Y", denBinp3Hv_ref);
  h4Binp3Hv ->Project("denX_Rm2_RunBinp3Hv",   "X", denBinp3Hv_ref);
  h4Binp3Hv ->Project("denY_Rm2_RunBinp3Hv",   "Y", denBinp3Hv_ref);
  h4Binp3Hv ->Project("denX_Binp3_RunBinp3Hv", "X", denBinp3Hv_binp);
  h4Binp3Hv ->Project("denY_Binp3_RunBinp3Hv", "Y", denBinp3Hv_binp);
  h4Binp3Hv ->Project("numX_Mib2_RunBinp3Hv",  "X", numBinp3Hv_mib2);
  h4Binp3Hv ->Project("numY_Mib2_RunBinp3Hv",  "Y", numBinp3Hv_mib2);
  h4Binp3Hv ->Project("numX_Rm2_RunBinp3Hv",   "X", numBinp3Hv_rm2);
  h4Binp3Hv ->Project("numY_Rm2_RunBinp3Hv",   "Y", numBinp3Hv_rm2);
  h4Binp3Hv ->Project("numX_Binp3_RunBinp3Hv", "X", numBinp3Hv_binp3);
  h4Binp3Hv ->Project("numY_Binp3_RunBinp3Hv", "Y", numBinp3Hv_binp3);

  TGraphAsymmErrors* effX_Mib2_RunBinp3Hv = new TGraphAsymmErrors(numX_Mib2_RunBinp3Hv, denX_Mib2_RunBinp3Hv);
  TGraphAsymmErrors* effY_Mib2_RunBinp3Hv = new TGraphAsymmErrors(numY_Mib2_RunBinp3Hv, denY_Mib2_RunBinp3Hv);
  effX_Mib2_RunBinp3Hv->SetMarkerStyle(20);
  effX_Mib2_RunBinp3Hv->SetMarkerColor(1);
  effX_Mib2_RunBinp3Hv->SetLineColor(1);
  effY_Mib2_RunBinp3Hv->SetMarkerStyle(21);
  effY_Mib2_RunBinp3Hv->SetMarkerColor(2);
  effY_Mib2_RunBinp3Hv->SetLineColor(2);

  TGraphAsymmErrors* effX_Rm2_RunBinp3Hv = new TGraphAsymmErrors(numX_Rm2_RunBinp3Hv, denX_Rm2_RunBinp3Hv);
  TGraphAsymmErrors* effY_Rm2_RunBinp3Hv = new TGraphAsymmErrors(numY_Rm2_RunBinp3Hv, denY_Rm2_RunBinp3Hv);
  effX_Rm2_RunBinp3Hv->SetMarkerStyle(20);
  effX_Rm2_RunBinp3Hv->SetMarkerColor(1);
  effX_Rm2_RunBinp3Hv->SetLineColor(1);
  effY_Rm2_RunBinp3Hv->SetMarkerStyle(21);
  effY_Rm2_RunBinp3Hv->SetMarkerColor(2);
  effY_Rm2_RunBinp3Hv->SetLineColor(2);

  TGraphAsymmErrors* effX_Binp3_RunBinp3Hv = new TGraphAsymmErrors(numX_Binp3_RunBinp3Hv, denX_Binp3_RunBinp3Hv);
  TGraphAsymmErrors* effY_Binp3_RunBinp3Hv = new TGraphAsymmErrors(numY_Binp3_RunBinp3Hv, denY_Binp3_RunBinp3Hv);
  effX_Binp3_RunBinp3Hv->SetMarkerStyle(20);
  effX_Binp3_RunBinp3Hv->SetMarkerColor(1);
  effX_Binp3_RunBinp3Hv->SetLineColor(1);
  effY_Binp3_RunBinp3Hv->SetMarkerStyle(21);
  effY_Binp3_RunBinp3Hv->SetMarkerColor(2);
  effY_Binp3_RunBinp3Hv->SetLineColor(2);

  TCanvas* c310a = new TCanvas("c310a","c",1);
  c310a->Divide(2,1);
  c310a->cd(1); myHx->Draw(); effX_Mib2_RunBinp3Hv->Draw("Psame");
  c310a->cd(2); myHy->Draw(); effY_Mib2_RunBinp3Hv->Draw("Psame");
  c310a->SaveAs("EffMib2_VsCoord_runHvBinp3.png");  

  TCanvas* c310b = new TCanvas("c310b","c",1);
  c310b->Divide(2,1);
  c310b->cd(1); myHx->Draw(); effX_Rm2_RunBinp3Hv->Draw("Psame");
  c310b->cd(2); myHy->Draw(); effY_Rm2_RunBinp3Hv->Draw("Psame");
  c310b->SaveAs("EffRm2_VsCoord_runHvBinp3.png");  

  TCanvas* c310c = new TCanvas("c310c","c",1);
  c310c->Divide(2,1);
  c310c->cd(1); myHx->Draw(); effX_Binp3_RunBinp3Hv->Draw("Psame");
  c310c->cd(2); myHy->Draw(); effY_Binp3_RunBinp3Hv->Draw("Psame");
  c310c->SaveAs("EffBinp3_VsCoord_runHvBinp3.png");  

  TH2F *den_Mib2_RunBinp3Hv  = new TH2F("den_Mib2_RunBinp3Hv", "den_Mib2_RunBinp3Hv", 16,-1.5,30.5, 16,-1.5,30.5);  
  TH2F *den_Rm2_RunBinp3Hv   = new TH2F("den_Rm2_RunBinp3Hv",  "den_Rm2_RunBinp3Hv",  16,-1.5,30.5, 16,-1.5,30.5);  
  TH2F *den_Binp3_RunBinp3Hv = new TH2F("den_Binp3_RunBinp3Hv","den_Binp3_RunBinp3Hv",16,-1.5,30.5, 16,-1.5,30.5);  
  TH2F *num_Mib2_RunBinp3Hv  = new TH2F("num_Mib2_RunBinp3Hv", "num_Mib2_RunBinp3Hv", 16,-1.5,30.5, 16,-1.5,30.5);  
  TH2F *num_Rm2_RunBinp3Hv   = new TH2F("num_Rm2_RunBinp3Hv",  "num_Rm2_RunBinp3Hv",  16,-1.5,30.5, 16,-1.5,30.5);  
  TH2F *num_Binp3_RunBinp3Hv = new TH2F("num_Binp3_RunBinp3Hv","num_Binp3_RunBinp3Hv",16,-1.5,30.5, 16,-1.5,30.5);  

  h4Binp3Hv ->Project("den_Mib2_RunBinp3Hv",  "Y:X", denBinp3Hv_ref);
  h4Binp3Hv ->Project("den_Rm2_RunBinp3Hv",   "Y:X", denBinp3Hv_ref);
  h4Binp3Hv ->Project("den_Binp3_RunBinp3Hv", "Y:X", denBinp3Hv_binp);
  h4Binp3Hv ->Project("num_Mib2_RunBinp3Hv",  "Y:X", numBinp3Hv_mib2);
  h4Binp3Hv ->Project("num_Rm2_RunBinp3Hv",   "Y:X", numBinp3Hv_rm2);
  h4Binp3Hv ->Project("num_Binp3_RunBinp3Hv", "Y:X", numBinp3Hv_binp3);

  TH2F *eff2dim_Mib2_RunBinp3Hv = (TH2F*)num_Mib2_RunBinp3Hv->Clone();
  eff2dim_Mib2_RunBinp3Hv->Divide(den_Mib2_RunBinp3Hv);
  TH2F *eff2dim_Rm2_RunBinp3Hv = (TH2F*)num_Rm2_RunBinp3Hv->Clone();
  eff2dim_Rm2_RunBinp3Hv->Divide(den_Rm2_RunBinp3Hv);
  TH2F *eff2dim_Binp3_RunBinp3Hv = (TH2F*)num_Binp3_RunBinp3Hv->Clone();
  eff2dim_Binp3_RunBinp3Hv->Divide(den_Binp3_RunBinp3Hv);

  TCanvas* c310a2 = new TCanvas("c310a2","c",1);
  eff2dim_Mib2_RunBinp3Hv->Draw("colz");
  c310a2->SaveAs("EffMib2_2dim_runHvBinp3.png");  
  TCanvas* c310b2 = new TCanvas("c310b2","c",1);
  eff2dim_Rm2_RunBinp3Hv->Draw("colz");
  c310b2->SaveAs("EffRm2_2dim_runHvBinp3.png");  
  TCanvas* c310c2 = new TCanvas("c310c2","c",1);
  eff2dim_Binp3_RunBinp3Hv->Draw("colz");
  c310c2->SaveAs("EffBinp3_2dim_runHvBinp3.png");  


  // Binp124 Timing
  TString denBinp124Timing_ref   = "adc_data>200 && adc_data<700 && n_hitsX>0 && n_hitsX<3 && n_hitsY>0 && n_hitsY<3";  
  TString denBinp124Timing_binp  = denBinp124Timing_ref + " && amp_max[MiB2]>200 && amp_max[Rm2]>200";
  TString numBinp124Timing_mib2  = denBinp124Timing_ref + " && amp_max[MiB2]>20";
  TString numBinp124Timing_rm2   = denBinp124Timing_ref + " && amp_max[Rm2]>20";
  TString numBinp124Timing_binp1 = denBinp124Timing_binp + " && amp_max[BINP1]>20";
  TString numBinp124Timing_binp2 = denBinp124Timing_binp + " && amp_max[BINP2]>20";
  TString numBinp124Timing_binp4 = denBinp124Timing_binp + " && amp_max[BINP4]>20";

  TH1F *denX_Mib2_RunBinp124Timing  = new TH1F("denX_Mib2_RunBinp124Timing", "denX_Mib2_RunBinp124Timing", 16,-1.5,30.5);  
  TH1F *denY_Mib2_RunBinp124Timing  = new TH1F("denY_Mib2_RunBinp124Timing", "denY_Mib2_RunBinp124Timing", 16,-1.5,30.5);  
  TH1F *denX_Rm2_RunBinp124Timing   = new TH1F("denX_Rm2_RunBinp124Timing",  "denX_Rm2_RunBinp124Timing",  16,-1.5,30.5);  
  TH1F *denY_Rm2_RunBinp124Timing   = new TH1F("denY_Rm2_RunBinp124Timing",  "denY_Rm2_RunBinp124Timing",  16,-1.5,30.5);  
  TH1F *denX_Binp1_RunBinp124Timing = new TH1F("denX_Binp1_RunBinp124Timing","denX_Binp1_RunBinp124Timing",16,-1.5,30.5);  
  TH1F *denY_Binp1_RunBinp124Timing = new TH1F("denY_Binp1_RunBinp124Timing","denY_Binp1_RunBinp124Timing",16,-1.5,30.5);  
  TH1F *denX_Binp2_RunBinp124Timing = new TH1F("denX_Binp2_RunBinp124Timing","denX_Binp2_RunBinp124Timing",16,-1.5,30.5);  
  TH1F *denY_Binp2_RunBinp124Timing = new TH1F("denY_Binp2_RunBinp124Timing","denY_Binp2_RunBinp124Timing",16,-1.5,30.5);  
  TH1F *denX_Binp4_RunBinp124Timing = new TH1F("denX_Binp4_RunBinp124Timing","denX_Binp4_RunBinp124Timing",16,-1.5,30.5);  
  TH1F *denY_Binp4_RunBinp124Timing = new TH1F("denY_Binp4_RunBinp124Timing","denY_Binp4_RunBinp124Timing",16,-1.5,30.5);  
  TH1F *numX_Mib2_RunBinp124Timing  = new TH1F("numX_Mib2_RunBinp124Timing", "numX_Mib2_RunBinp124Timing", 16,-1.5,30.5);  
  TH1F *numY_Mib2_RunBinp124Timing  = new TH1F("numY_Mib2_RunBinp124Timing", "numY_Mib2_RunBinp124Timing", 16,-1.5,30.5);  
  TH1F *numX_Rm2_RunBinp124Timing   = new TH1F("numX_Rm2_RunBinp124Timing",  "numX_Rm2_RunBinp124Timing",  16,-1.5,30.5);  
  TH1F *numY_Rm2_RunBinp124Timing   = new TH1F("numY_Rm2_RunBinp124Timing",  "numY_Rm2_RunBinp124Timing",  16,-1.5,30.5);  
  TH1F *numX_Binp1_RunBinp124Timing = new TH1F("numX_Binp1_RunBinp124Timing","numX_Binp1_RunBinp124Timing",16,-1.5,30.5);  
  TH1F *numY_Binp1_RunBinp124Timing = new TH1F("numY_Binp1_RunBinp124Timing","numY_Binp1_RunBinp124Timing",16,-1.5,30.5);  
  TH1F *numX_Binp2_RunBinp124Timing = new TH1F("numX_Binp2_RunBinp124Timing","numX_Binp2_RunBinp124Timing",16,-1.5,30.5);  
  TH1F *numY_Binp2_RunBinp124Timing = new TH1F("numY_Binp2_RunBinp124Timing","numY_Binp2_RunBinp124Timing",16,-1.5,30.5);  
  TH1F *numX_Binp4_RunBinp124Timing = new TH1F("numX_Binp4_RunBinp124Timing","numX_Binp4_RunBinp124Timing",16,-1.5,30.5);  
  TH1F *numY_Binp4_RunBinp124Timing = new TH1F("numY_Binp4_RunBinp124Timing","numY_Binp4_RunBinp124Timing",16,-1.5,30.5);  

  h4Binp124Timing ->Project("denX_Mib2_RunBinp124Timing",  "X", denBinp124Timing_ref);
  h4Binp124Timing ->Project("denY_Mib2_RunBinp124Timing",  "Y", denBinp124Timing_ref);
  h4Binp124Timing ->Project("denX_Rm2_RunBinp124Timing",   "X", denBinp124Timing_ref);
  h4Binp124Timing ->Project("denY_Rm2_RunBinp124Timing",   "Y", denBinp124Timing_ref);
  h4Binp124Timing ->Project("denX_Binp1_RunBinp124Timing", "X", denBinp124Timing_binp);
  h4Binp124Timing ->Project("denY_Binp1_RunBinp124Timing", "Y", denBinp124Timing_binp);
  h4Binp124Timing ->Project("denX_Binp2_RunBinp124Timing", "X", denBinp124Timing_binp);
  h4Binp124Timing ->Project("denY_Binp2_RunBinp124Timing", "Y", denBinp124Timing_binp);
  h4Binp124Timing ->Project("denX_Binp4_RunBinp124Timing", "X", denBinp124Timing_binp);
  h4Binp124Timing ->Project("denY_Binp4_RunBinp124Timing", "Y", denBinp124Timing_binp);
  h4Binp124Timing ->Project("numX_Mib2_RunBinp124Timing",  "X", numBinp124Timing_mib2);
  h4Binp124Timing ->Project("numY_Mib2_RunBinp124Timing",  "Y", numBinp124Timing_mib2);
  h4Binp124Timing ->Project("numX_Rm2_RunBinp124Timing",   "X", numBinp124Timing_rm2);
  h4Binp124Timing ->Project("numY_Rm2_RunBinp124Timing",   "Y", numBinp124Timing_rm2);
  h4Binp124Timing ->Project("numX_Binp1_RunBinp124Timing", "X", numBinp124Timing_binp1);
  h4Binp124Timing ->Project("numY_Binp1_RunBinp124Timing", "Y", numBinp124Timing_binp1);
  h4Binp124Timing ->Project("numX_Binp2_RunBinp124Timing", "X", numBinp124Timing_binp2);
  h4Binp124Timing ->Project("numY_Binp2_RunBinp124Timing", "Y", numBinp124Timing_binp2);
  h4Binp124Timing ->Project("numX_Binp4_RunBinp124Timing", "X", numBinp124Timing_binp4);
  h4Binp124Timing ->Project("numY_Binp4_RunBinp124Timing", "Y", numBinp124Timing_binp4);

  TGraphAsymmErrors* effX_Mib2_RunBinp124Timing = new TGraphAsymmErrors(numX_Mib2_RunBinp124Timing, denX_Mib2_RunBinp124Timing);
  TGraphAsymmErrors* effY_Mib2_RunBinp124Timing = new TGraphAsymmErrors(numY_Mib2_RunBinp124Timing, denY_Mib2_RunBinp124Timing);
  effX_Mib2_RunBinp124Timing->SetMarkerStyle(20);
  effX_Mib2_RunBinp124Timing->SetMarkerColor(1);
  effX_Mib2_RunBinp124Timing->SetLineColor(1);
  effY_Mib2_RunBinp124Timing->SetMarkerStyle(21);
  effY_Mib2_RunBinp124Timing->SetMarkerColor(2);
  effY_Mib2_RunBinp124Timing->SetLineColor(2);

  TGraphAsymmErrors* effX_Rm2_RunBinp124Timing = new TGraphAsymmErrors(numX_Rm2_RunBinp124Timing, denX_Rm2_RunBinp124Timing);
  TGraphAsymmErrors* effY_Rm2_RunBinp124Timing = new TGraphAsymmErrors(numY_Rm2_RunBinp124Timing, denY_Rm2_RunBinp124Timing);
  effX_Rm2_RunBinp124Timing->SetMarkerStyle(20);
  effX_Rm2_RunBinp124Timing->SetMarkerColor(1);
  effX_Rm2_RunBinp124Timing->SetLineColor(1);
  effY_Rm2_RunBinp124Timing->SetMarkerStyle(21);
  effY_Rm2_RunBinp124Timing->SetMarkerColor(2);
  effY_Rm2_RunBinp124Timing->SetLineColor(2);

  TGraphAsymmErrors* effX_Binp1_RunBinp124Timing = new TGraphAsymmErrors(numX_Binp1_RunBinp124Timing, denX_Binp1_RunBinp124Timing);
  TGraphAsymmErrors* effY_Binp1_RunBinp124Timing = new TGraphAsymmErrors(numY_Binp1_RunBinp124Timing, denY_Binp1_RunBinp124Timing);
  effX_Binp1_RunBinp124Timing->SetMarkerStyle(20);
  effX_Binp1_RunBinp124Timing->SetMarkerColor(1);
  effX_Binp1_RunBinp124Timing->SetLineColor(1);
  effY_Binp1_RunBinp124Timing->SetMarkerStyle(21);
  effY_Binp1_RunBinp124Timing->SetMarkerColor(2);
  effY_Binp1_RunBinp124Timing->SetLineColor(2);

  TGraphAsymmErrors* effX_Binp2_RunBinp124Timing = new TGraphAsymmErrors(numX_Binp2_RunBinp124Timing, denX_Binp2_RunBinp124Timing);
  TGraphAsymmErrors* effY_Binp2_RunBinp124Timing = new TGraphAsymmErrors(numY_Binp2_RunBinp124Timing, denY_Binp2_RunBinp124Timing);
  effX_Binp2_RunBinp124Timing->SetMarkerStyle(20);
  effX_Binp2_RunBinp124Timing->SetMarkerColor(1);
  effX_Binp2_RunBinp124Timing->SetLineColor(1);
  effY_Binp2_RunBinp124Timing->SetMarkerStyle(21);
  effY_Binp2_RunBinp124Timing->SetMarkerColor(2);
  effY_Binp2_RunBinp124Timing->SetLineColor(2);

  TGraphAsymmErrors* effX_Binp4_RunBinp124Timing = new TGraphAsymmErrors(numX_Binp4_RunBinp124Timing, denX_Binp4_RunBinp124Timing);
  TGraphAsymmErrors* effY_Binp4_RunBinp124Timing = new TGraphAsymmErrors(numY_Binp4_RunBinp124Timing, denY_Binp4_RunBinp124Timing);
  effX_Binp4_RunBinp124Timing->SetMarkerStyle(20);
  effX_Binp4_RunBinp124Timing->SetMarkerColor(1);
  effX_Binp4_RunBinp124Timing->SetLineColor(1);
  effY_Binp4_RunBinp124Timing->SetMarkerStyle(21);
  effY_Binp4_RunBinp124Timing->SetMarkerColor(2);
  effY_Binp4_RunBinp124Timing->SetLineColor(2);

  TCanvas* c410a = new TCanvas("c410a","c",1);
  c410a->Divide(2,1);
  c410a->cd(1); myHx->Draw(); effX_Mib2_RunBinp124Timing->Draw("Psame");
  c410a->cd(2); myHy->Draw(); effY_Mib2_RunBinp124Timing->Draw("Psame");
  c410a->SaveAs("EffMib2_VsCoord_runTim124.png");  

  TCanvas* c410b = new TCanvas("c410b","c",1);
  c410b->Divide(2,1);
  c410b->cd(1); myHx->Draw(); effX_Rm2_RunBinp124Timing->Draw("Psame");
  c410b->cd(2); myHy->Draw(); effY_Rm2_RunBinp124Timing->Draw("Psame");
  c410b->SaveAs("EffRm2_VsCoord_runTim124.png");  

  TCanvas* c410c = new TCanvas("c410c","c",1);
  c410c->Divide(2,1);
  c410c->cd(1); myHx->Draw(); effX_Binp1_RunBinp124Timing->Draw("Psame");
  c410c->cd(2); myHy->Draw(); effY_Binp1_RunBinp124Timing->Draw("Psame");
  c410c->SaveAs("EffBinp1_VsCoord_runTim124.png");  

  TCanvas* c410d = new TCanvas("c410d","c",1);
  c410d->Divide(2,1);
  c410d->cd(1); myHx->Draw(); effX_Binp2_RunBinp124Timing->Draw("Psame");
  c410d->cd(2); myHy->Draw(); effY_Binp2_RunBinp124Timing->Draw("Psame");
  c410d->SaveAs("EffBinp2_VsCoord_runTim124.png");  

  TCanvas* c410e = new TCanvas("c410e","c",1);
  c410e->Divide(2,1);
  c410e->cd(1); myHx->Draw(); effX_Binp4_RunBinp124Timing->Draw("Psame");
  c410e->cd(2); myHy->Draw(); effY_Binp4_RunBinp124Timing->Draw("Psame");
  c410e->SaveAs("EffBinp4_VsCoord_runTim124.png");  

  TH2F *den_Mib2_RunBinp124Timing  = new TH2F("den_Mib2_RunBinp124Timing", "den_Mib2_RunBinp124Timing", 16,-1.5,30.5, 16,-1.5,30.5);  
  TH2F *den_Rm2_RunBinp124Timing   = new TH2F("den_Rm2_RunBinp124Timing",  "den_Rm2_RunBinp124Timing",  16,-1.5,30.5, 16,-1.5,30.5);  
  TH2F *den_Binp1_RunBinp124Timing = new TH2F("den_Binp1_RunBinp124Timing","den_Binp1_RunBinp124Timing",16,-1.5,30.5, 16,-1.5,30.5);  
  TH2F *den_Binp2_RunBinp124Timing = new TH2F("den_Binp2_RunBinp124Timing","den_Binp2_RunBinp124Timing",16,-1.5,30.5, 16,-1.5,30.5);  
  TH2F *den_Binp4_RunBinp124Timing = new TH2F("den_Binp4_RunBinp124Timing","den_Binp4_RunBinp124Timing",16,-1.5,30.5, 16,-1.5,30.5);  
  TH2F *num_Mib2_RunBinp124Timing  = new TH2F("num_Mib2_RunBinp124Timing", "num_Mib2_RunBinp124Timing", 16,-1.5,30.5, 16,-1.5,30.5);  
  TH2F *num_Rm2_RunBinp124Timing   = new TH2F("num_Rm2_RunBinp124Timing",  "num_Rm2_RunBinp124Timing",  16,-1.5,30.5, 16,-1.5,30.5);  
  TH2F *num_Binp1_RunBinp124Timing = new TH2F("num_Binp1_RunBinp124Timing","num_Binp1_RunBinp124Timing",16,-1.5,30.5, 16,-1.5,30.5);  
  TH2F *num_Binp2_RunBinp124Timing = new TH2F("num_Binp2_RunBinp124Timing","num_Binp2_RunBinp124Timing",16,-1.5,30.5, 16,-1.5,30.5);  
  TH2F *num_Binp4_RunBinp124Timing = new TH2F("num_Binp4_RunBinp124Timing","num_Binp4_RunBinp124Timing",16,-1.5,30.5, 16,-1.5,30.5);  

  h4Binp124Timing ->Project("den_Mib2_RunBinp124Timing",  "Y:X", denBinp124Timing_ref);
  h4Binp124Timing ->Project("den_Rm2_RunBinp124Timing",   "Y:X", denBinp124Timing_ref);
  h4Binp124Timing ->Project("den_Binp1_RunBinp124Timing", "Y:X", denBinp124Timing_binp);
  h4Binp124Timing ->Project("den_Binp2_RunBinp124Timing", "Y:X", denBinp124Timing_binp);
  h4Binp124Timing ->Project("den_Binp4_RunBinp124Timing", "Y:X", denBinp124Timing_binp);
  h4Binp124Timing ->Project("num_Mib2_RunBinp124Timing",  "Y:X", numBinp124Timing_mib2);
  h4Binp124Timing ->Project("num_Rm2_RunBinp124Timing",   "Y:X", numBinp124Timing_rm2);
  h4Binp124Timing ->Project("num_Binp1_RunBinp124Timing", "Y:X", numBinp124Timing_binp1);
  h4Binp124Timing ->Project("num_Binp2_RunBinp124Timing", "Y:X", numBinp124Timing_binp2);
  h4Binp124Timing ->Project("num_Binp4_RunBinp124Timing", "Y:X", numBinp124Timing_binp4);

  TH2F *eff2dim_Mib2_RunBinp124Timing = (TH2F*)num_Mib2_RunBinp124Timing->Clone();
  eff2dim_Mib2_RunBinp124Timing->Divide(den_Mib2_RunBinp124Timing);
  TH2F *eff2dim_Rm2_RunBinp124Timing = (TH2F*)num_Rm2_RunBinp124Timing->Clone();
  eff2dim_Rm2_RunBinp124Timing->Divide(den_Rm2_RunBinp124Timing);
  TH2F *eff2dim_Binp1_RunBinp124Timing = (TH2F*)num_Binp1_RunBinp124Timing->Clone();
  eff2dim_Binp1_RunBinp124Timing->Divide(den_Binp1_RunBinp124Timing);
  TH2F *eff2dim_Binp2_RunBinp124Timing = (TH2F*)num_Binp2_RunBinp124Timing->Clone();
  eff2dim_Binp2_RunBinp124Timing->Divide(den_Binp2_RunBinp124Timing);
  TH2F *eff2dim_Binp4_RunBinp124Timing = (TH2F*)num_Binp4_RunBinp124Timing->Clone();
  eff2dim_Binp4_RunBinp124Timing->Divide(den_Binp4_RunBinp124Timing);

  TCanvas* c410a2 = new TCanvas("c410a2","c",1);
  eff2dim_Mib2_RunBinp124Timing->Draw("colz");
  c410a2->SaveAs("EffMib2_2dim_run124Timing.png");  
  TCanvas* c410b2 = new TCanvas("c410b2","c",1);
  eff2dim_Rm2_RunBinp124Timing->Draw("colz");
  c410b2->SaveAs("EffRm2_2dim_run124Timing.png");  
  TCanvas* c410c2 = new TCanvas("c410c2","c",1);
  eff2dim_Binp1_RunBinp124Timing->Draw("colz");
  c410c2->SaveAs("EffBinp1_2dim_run124Timing.png");  
  TCanvas* c410d2 = new TCanvas("c410d2","c",1);
  eff2dim_Binp2_RunBinp124Timing->Draw("colz");
  c410d2->SaveAs("EffBinp2_2dim_run124Timing.png");  
  TCanvas* c410e2 = new TCanvas("c410e2","c",1);
  eff2dim_Binp4_RunBinp124Timing->Draw("colz");
  c410e2->SaveAs("EffBinp4_2dim_run124Timing.png");  


  // Binp3 Timing
  TString denBinp3Timing_ref   = "adc_data>200 && adc_data<700 && n_hitsX>0 && n_hitsX<3 && n_hitsY>0 && n_hitsY<3";  
  TString denBinp3Timing_binp  = denBinp3Timing_ref + " && amp_max[MiB2]>200"; 
  TString numBinp3Timing_mib2  = denBinp3Timing_ref + " && amp_max[MiB2]>20";
  TString numBinp3Timing_binp3 = denBinp3Timing_binp + " && amp_max[BINP3]>20";

  TH1F *denX_Mib2_RunBinp3Timing  = new TH1F("denX_Mib2_RunBinp3Timing", "denX_Mib2_RunBinp3Timing", 16,-1.5,30.5);  
  TH1F *denY_Mib2_RunBinp3Timing  = new TH1F("denY_Mib2_RunBinp3Timing", "denY_Mib2_RunBinp3Timing", 16,-1.5,30.5);  
  TH1F *denX_binp3_RunBinp3Timing = new TH1F("denX_binp3_RunBinp3Timing","denX_binp3_RunBinp3Timing",16,-1.5,30.5);  
  TH1F *denY_binp3_RunBinp3Timing = new TH1F("denY_binp3_RunBinp3Timing","denY_binp3_RunBinp3Timing",16,-1.5,30.5);  
  TH1F *numX_Mib2_RunBinp3Timing  = new TH1F("numX_Mib2_RunBinp3Timing", "numX_Mib2_RunBinp3Timing", 16,-1.5,30.5);  
  TH1F *numY_Mib2_RunBinp3Timing  = new TH1F("numY_Mib2_RunBinp3Timing", "numY_Mib2_RunBinp3Timing", 16,-1.5,30.5);  
  TH1F *numX_binp3_RunBinp3Timing = new TH1F("numX_binp3_RunBinp3Timing","numX_binp3_RunBinp3Timing",16,-1.5,30.5);  
  TH1F *numY_binp3_RunBinp3Timing = new TH1F("numY_binp3_RunBinp3Timing","numY_binp3_RunBinp3Timing",16,-1.5,30.5);  

  h4Binp3Timing ->Project("denX_Mib2_RunBinp3Timing",  "X", denBinp3Timing_ref);
  h4Binp3Timing ->Project("denY_Mib2_RunBinp3Timing",  "Y", denBinp3Timing_ref);
  h4Binp3Timing ->Project("denX_binp3_RunBinp3Timing", "X", denBinp3Timing_binp);
  h4Binp3Timing ->Project("denY_binp3_RunBinp3Timing", "Y", denBinp3Timing_binp);
  h4Binp3Timing ->Project("numX_Mib2_RunBinp3Timing",  "X", numBinp3Timing_mib2);
  h4Binp3Timing ->Project("numY_Mib2_RunBinp3Timing",  "Y", numBinp3Timing_mib2);
  h4Binp3Timing ->Project("numX_binp3_RunBinp3Timing", "X", numBinp3Timing_binp3);
  h4Binp3Timing ->Project("numY_binp3_RunBinp3Timing", "Y", numBinp3Timing_binp3);

  TGraphAsymmErrors* effX_Mib2_RunBinp3Timing = new TGraphAsymmErrors(numX_Mib2_RunBinp3Timing, denX_Mib2_RunBinp3Timing);
  TGraphAsymmErrors* effY_Mib2_RunBinp3Timing = new TGraphAsymmErrors(numY_Mib2_RunBinp3Timing, denY_Mib2_RunBinp3Timing);
  effX_Mib2_RunBinp3Timing->SetMarkerStyle(20);
  effX_Mib2_RunBinp3Timing->SetMarkerColor(1);
  effX_Mib2_RunBinp3Timing->SetLineColor(1);
  effY_Mib2_RunBinp3Timing->SetMarkerStyle(21);
  effY_Mib2_RunBinp3Timing->SetMarkerColor(2);
  effY_Mib2_RunBinp3Timing->SetLineColor(2);

  TGraphAsymmErrors* effX_binp3_RunBinp3Timing = new TGraphAsymmErrors(numX_binp3_RunBinp3Timing, denX_binp3_RunBinp3Timing);
  TGraphAsymmErrors* effY_binp3_RunBinp3Timing = new TGraphAsymmErrors(numY_binp3_RunBinp3Timing, denY_binp3_RunBinp3Timing);
  effX_binp3_RunBinp3Timing->SetMarkerStyle(20);
  effX_binp3_RunBinp3Timing->SetMarkerColor(1);
  effX_binp3_RunBinp3Timing->SetLineColor(1);
  effY_binp3_RunBinp3Timing->SetMarkerStyle(21);
  effY_binp3_RunBinp3Timing->SetMarkerColor(2);
  effY_binp3_RunBinp3Timing->SetLineColor(2);

  TCanvas* c510a = new TCanvas("c510a","c",1);
  c510a->Divide(2,1);
  c510a->cd(1); myHx->Draw(); effX_Mib2_RunBinp3Timing->Draw("Psame");
  c510a->cd(2); myHy->Draw(); effY_Mib2_RunBinp3Timing->Draw("Psame");
  c510a->SaveAs("EffMib2_VsCoord_runTim3.png");  

  TCanvas* c510c = new TCanvas("c510c","c",1);
  c510c->Divide(2,1);
  c510c->cd(1); myHx->Draw(); effX_binp3_RunBinp3Timing->Draw("Psame");
  c510c->cd(2); myHy->Draw(); effY_binp3_RunBinp3Timing->Draw("Psame");
  c510c->SaveAs("EffBinp3_VsCoord_runTim3.png");  

  TH2F *den_Mib2_RunBinp3Timing  = new TH2F("den_Mib2_RunBinp3Timing", "den_Mib2_RunBinp3Timing", 16,-1.5,30.5, 16,-1.5,30.5);  
  TH2F *den_binp3_RunBinp3Timing = new TH2F("den_binp3_RunBinp3Timing","den_binp3_RunBinp3Timing",16,-1.5,30.5, 16,-1.5,30.5);  
  TH2F *num_Mib2_RunBinp3Timing  = new TH2F("num_Mib2_RunBinp3Timing", "num_Mib2_RunBinp3Timing", 16,-1.5,30.5, 16,-1.5,30.5);  
  TH2F *num_binp3_RunBinp3Timing = new TH2F("num_binp3_RunBinp3Timing","num_binp3_RunBinp3Timing",16,-1.5,30.5, 16,-1.5,30.5);  
  h4Binp3Timing ->Project("den_Mib2_RunBinp3Timing",  "Y:X", denBinp3Timing_ref);
  h4Binp3Timing ->Project("den_binp3_RunBinp3Timing", "Y:X", denBinp3Timing_binp);
  h4Binp3Timing ->Project("num_Mib2_RunBinp3Timing",  "Y:X", numBinp3Timing_mib2);
  h4Binp3Timing ->Project("num_binp3_RunBinp3Timing", "Y:X", numBinp3Timing_binp3);

  TH2F *eff2dim_Mib2_RunBinp3Timing = (TH2F*)num_Mib2_RunBinp3Timing->Clone();
  eff2dim_Mib2_RunBinp3Timing->Divide(den_Mib2_RunBinp3Timing);
  TH2F *eff2dim_binp3_RunBinp3Timing = (TH2F*)num_binp3_RunBinp3Timing->Clone();
  eff2dim_binp3_RunBinp3Timing->Divide(den_binp3_RunBinp3Timing);
  TCanvas* c510a2 = new TCanvas("c510a2","c",1);
  eff2dim_Mib2_RunBinp3Timing->Draw("colz");
  c510a2->SaveAs("EffMib2_2dim_runTim3.png");  
  TCanvas* c510b2 = new TCanvas("c510b2","c",1);
  eff2dim_binp3_RunBinp3Timing->Draw("colz");
  c510b2->SaveAs("EffBinp3_2dim_runTim3.png");  


  // ==========================================================
  // Now2: fraction of events passing the standard selection with 0hits
  cout << endl;
  TString den0hits   = "adc_data>200 && adc_data<700 && amp_max[MiB2]>200 && amp_max[Rm2]>200 && amp_max[Rm2]<1200";
  TString den0hits1  = "adc_data>200 && adc_data<700 && amp_max[MiB2]>200";   // for runs where Rm2 was off
  TString num0hitsX  = den0hits  + " && n_hitsX==0";
  TString num0hitsX1 = den0hits1 + " && n_hitsX==0";
  TString num0hitsY  = den0hits  + " && n_hitsY==0";
  TString num0hitsY1 = den0hits1 + " && n_hitsY==0";
  for (int ii=0; ii<5; ii++) {
    TH1F *Hden0hits  = new TH1F("Hden0hits",   "Hden0hits",      16,-1.5,30.5);  
    TH1F *Hnum0hitsX = new TH1F("Hnum0hitsX",  "Hnum0hitsX",     16,-1.5,30.5);
    TH1F *Hnum0hitsY = new TH1F("Hnum0hitsY",  "Hnum0hitsY",     16,-1.5,30.5);
    TTree* theTree;
    if (ii==0)  theTree = h4Binp1Hv;
    if (ii==1)  theTree = h4Binp24Hv;
    if (ii==2)  theTree = h4Binp3Hv;
    if (ii==3)  theTree = h4Binp124Timing;
    if (ii==4)  theTree = h4Binp3Timing;

    if (ii==1 || ii==2 || ii==3) {
      theTree ->Project("Hden0hits",  "X", den0hits);
      theTree ->Project("Hnum0hitsX", "X", num0hitsX);
      theTree ->Project("Hnum0hitsY", "Y", num0hitsY);
    } else if (ii==0 || ii==4) {
      theTree ->Project("Hden0hits",  "X", den0hits1);
      theTree ->Project("Hnum0hitsX", "X", num0hitsX1);
      theTree ->Project("Hnum0hitsY", "Y", num0hitsY1);
    }
    cout << "Runs " << ii << ": fraction of events with 0 hits in X = " << Hnum0hitsX->Integral()/Hden0hits->Integral() 
	 << ", in Y = " << Hnum0hitsY->Integral()/Hden0hits->Integral() << endl;
    delete Hden0hits;
    delete Hnum0hitsX;
    delete Hnum0hitsY;
  }

  // ==========================================================
  // Now3: hits vs scintillator
  cout << endl;
  for (int ii=0; ii<5; ii++) {

    TTree* theTree;
    if (ii==0)  theTree = h4Binp1Hv;
    if (ii==1)  theTree = h4Binp24Hv;
    if (ii==2)  theTree = h4Binp3Hv;
    if (ii==3)  theTree = h4Binp124Timing;
    if (ii==4)  theTree = h4Binp3Timing;

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
