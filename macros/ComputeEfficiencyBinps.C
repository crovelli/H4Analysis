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

void ComputeEfficiency() {

  gStyle->SetOptStat(0);

  // inputs - here each mcp is in 1st position (for 2corr it is not)
  TFile* inFileBinp1 = new TFile("/cmsrm/pc28_2/crovelli/data/imcp/binps/btf2016_HVscanBinp1.root");
  TFile* inFileBinp2 = new TFile("/cmsrm/pc28_2/crovelli/data/imcp/binps/btf2016_HVscanBinp4.root");   // in btf2016_HVscanBinp2.root binp2 was probably partly off
  TFile* inFileBinp3 = new TFile("/cmsrm/pc28_2/crovelli/data/imcp/binps/btf2016_HVscanBinp3.root");
  TFile* inFileBinp4 = new TFile("/cmsrm/pc28_2/crovelli/data/imcp/binps/btf2016_HVscanBinp4.root");
  //
  TFile* inFileTiming124 = new TFile("/cmsrm/pc28_2/crovelli/data/imcp/binps/btf2016_RU5_2378.root");
  TFile* inFileTiming3   = new TFile("/cmsrm/pc28_2/crovelli/data/imcp/binps/btf2016_RU4_2364.root");
  
  TTree* h4binp1 = (TTree*)inFileBinp1->Get("h4");
  TTree* h4binp2 = (TTree*)inFileBinp2->Get("h4");
  TTree* h4binp3 = (TTree*)inFileBinp3->Get("h4");
  TTree* h4binp4 = (TTree*)inFileBinp4->Get("h4");
  //
  TTree* h4timing124 = (TTree*)inFileTiming124->Get("h4");
  TTree* h4timing3   = (TTree*)inFileTiming3->Get("h4");

  // histos
  TH1F* num1 = new TH1F("num1","",2500,0.,2500.);
  TH1F* num2 = new TH1F("num2","",2500,0.,2500.);
  TH1F* num3 = new TH1F("num3","",2500,0.,2500.);
  TH1F* num4 = new TH1F("num4","",2500,0.,2500.);
  TH1F* den1 = new TH1F("den1","",2500,0.,2500.);
  TH1F* den2 = new TH1F("den2","",2500,0.,2500.);
  TH1F* den3 = new TH1F("den3","",2500,0.,2500.);
  TH1F* den4 = new TH1F("den4","",2500,0.,2500.);


  // -------------------------------------
  // Denominator: selection based on ref-mcp amplitudes and scintillators
  TString commonDenAmp = "adc_data>200 && adc_data<700 && n_hitsX>0 && n_hitsY>0 && n_hitsX<3 && n_hitsY<3 && amp_max[MiB2]>200 && fabs(time_max[MiB2])<150";
  TString commonDenAndRm2Amp = commonDenAmp + " && amp_max[Rm2]>200 && amp_max[Rm2]<1200 && fabs(time_max[Rm2])<150";

  // Compute mean timing distance between Mib2 and Rm2 (not for Binp1 runs, RM2 OFF) - to be added to denominator
  TH1F* tim2_rm2mib2 = new TH1F("tim2_rm2mib2","tim2_rm2mib2",4000,-20.,20.);
  TH1F* tim3_rm2mib2 = new TH1F("tim3_rm2mib2","tim3_rm2mib2",4000,-20.,20.);
  TH1F* tim4_rm2mib2 = new TH1F("tim4_rm2mib2","tim4_rm2mib2",4000,-20.,20.);
  h4binp2->Project("tim2_rm2mib2","time_max[Rm2]-time_max[MiB2]",commonDenAndRm2Amp);
  h4binp3->Project("tim3_rm2mib2","time_max[Rm2]-time_max[MiB2]",commonDenAndRm2Amp);
  h4binp4->Project("tim4_rm2mib2","time_max[Rm2]-time_max[MiB2]",commonDenAndRm2Amp);

  char mean2_rm2mib2[100];
  char mean3_rm2mib2[100];
  char mean4_rm2mib2[100];
  sprintf(mean2_rm2mib2,"%f",tim2_rm2mib2->GetMean());
  sprintf(mean3_rm2mib2,"%f",tim3_rm2mib2->GetMean());
  sprintf(mean4_rm2mib2,"%f",tim4_rm2mib2->GetMean());
  std::string sMean2_rm2mib2 = std::string(mean2_rm2mib2);
  std::string sMean3_rm2mib2 = std::string(mean3_rm2mib2);
  std::string sMean4_rm2mib2 = std::string(mean4_rm2mib2);
  
  TString denAmpTim1 = commonDenAmp;

  TString denAndRm2AmpTim2;
  if(tim2_rm2mib2->GetMean() < 0.){
    sMean2_rm2mib2.erase(sMean2_rm2mib2.begin(),sMean2_rm2mib2.begin()+1);
    denAndRm2AmpTim2 = commonDenAndRm2Amp+std::string(" && fabs(time_max[Rm2]-time_max[MiB2]+")+std::string(sMean2_rm2mib2)+std::string(")<1");
    } else { 
    denAndRm2AmpTim2 = commonDenAndRm2Amp+std::string(" && fabs(time_max[Rm2]-time_max[MiB2]-")+std::string(sMean2_rm2mib2)+std::string(")<1");
  }

  TString denAndRm2AmpTim3;
  if(tim3_rm2mib2->GetMean() < 0.){
    sMean3_rm2mib2.erase(sMean3_rm2mib2.begin(),sMean3_rm2mib2.begin()+1);
    denAndRm2AmpTim3 = commonDenAndRm2Amp+std::string(" && fabs(time_max[Rm2]-time_max[MiB2]+")+std::string(sMean3_rm2mib2)+std::string(")<1");
    } else { 
    denAndRm2AmpTim3 = commonDenAndRm2Amp+std::string(" && fabs(time_max[Rm2]-time_max[MiB2]-")+std::string(sMean3_rm2mib2)+std::string(")<1");
  }

  TString denAndRm2AmpTim4;
  if(tim4_rm2mib2->GetMean() < 0.){
    sMean4_rm2mib2.erase(sMean4_rm2mib2.begin(),sMean4_rm2mib2.begin()+1);
    denAndRm2AmpTim4 = commonDenAndRm2Amp+std::string(" && fabs(time_max[Rm2]-time_max[MiB2]+")+std::string(sMean4_rm2mib2)+std::string(")<1");
    } else { 
    denAndRm2AmpTim4 = commonDenAndRm2Amp+std::string(" && fabs(time_max[Rm2]-time_max[MiB2]-")+std::string(sMean4_rm2mib2)+std::string(")<1");
  }

  // denominators
  TString den1s = denAmpTim1;
  TString den2s = denAndRm2AmpTim2;
  TString den3s = denAndRm2AmpTim3;
  TString den4s = denAndRm2AmpTim4;
  h4binp1->Project("den1","HVBINP1",den1s);
  h4binp2->Project("den2","HVBINP2",den2s);
  h4binp3->Project("den3","HVBINP3",den3s);
  h4binp4->Project("den4","HVBINP4",den4s);


  // Compute mean timing distance between Binps and Mib2 - to be added to numerator
  TH1F* timmax1mib2binp = new TH1F("timmax1mib2binp", "timmax1mib2binp",  4000,-20.,20.);
  TH1F* timmax2mib2binp = new TH1F("timmax2mib2binp", "timmax2mib2binp",  4000,-20.,20.);
  TH1F* timmax3mib2binp = new TH1F("timmax3mib2binp", "timmax3mib2binp",  4000,-20.,20.);
  TH1F* timmax4mib2binp = new TH1F("timmax4mib2binp", "timmax4mib2binp",  4000,-20.,20.);
  h4binp1->Project("timmax1mib2binp","time_max[BINP1]-time_max[MiB2]",den1s+" && amp_max[BINP1]<3000 && amp_max[BINP1]>20");
  h4binp2->Project("timmax2mib2binp","time_max[BINP2]-time_max[MiB2]",den2s+" && amp_max[BINP2]<3000 && amp_max[BINP2]>20");
  h4binp3->Project("timmax3mib2binp","time_max[BINP3]-time_max[MiB2]",den3s+" && amp_max[BINP3]<3000 && amp_max[BINP3]>20");
  h4binp4->Project("timmax4mib2binp","time_max[BINP4]-time_max[MiB2]",den4s+" && amp_max[BINP4]<3000 && amp_max[BINP4]>20");

  TH1F* tim1mib2binp = new TH1F("tim1mib2binp", "tim1mib2binp",  4000,-20.,20.);
  TH1F* tim2mib2binp = new TH1F("tim2mib2binp", "tim2mib2binp",  4000,-20.,20.);
  TH1F* tim3mib2binp = new TH1F("tim3mib2binp", "tim3mib2binp",  4000,-20.,20.);
  TH1F* tim4mib2binp = new TH1F("tim4mib2binp", "tim4mib2binp",  4000,-20.,20.);
  h4binp1->Project("tim1mib2binp","time[BINP1]-time[MiB2]",den1s+" && amp_max[BINP1]<3000 && amp_max[BINP1]>20");
  h4binp2->Project("tim2mib2binp","time[BINP2]-time[MiB2]",den2s+" && amp_max[BINP2]<3000 && amp_max[BINP2]>20");
  h4binp3->Project("tim3mib2binp","time[BINP3]-time[MiB2]",den3s+" && amp_max[BINP3]<3000 && amp_max[BINP3]>20");
  h4binp4->Project("tim4mib2binp","time[BINP4]-time[MiB2]",den4s+" && amp_max[BINP4]<3000 && amp_max[BINP4]>20");

  char mean1max_mib2binp[100];
  char mean2max_mib2binp[100];
  char mean3max_mib2binp[100];
  char mean4max_mib2binp[100];
  sprintf(mean1max_mib2binp,"%f",timmax1mib2binp->GetMean());
  sprintf(mean2max_mib2binp,"%f",timmax2mib2binp->GetMean());
  sprintf(mean3max_mib2binp,"%f",timmax3mib2binp->GetMean());
  sprintf(mean4max_mib2binp,"%f",timmax4mib2binp->GetMean());
  std::string sMean1max_mib2binp = std::string(mean1max_mib2binp);
  std::string sMean2max_mib2binp = std::string(mean2max_mib2binp);
  std::string sMean3max_mib2binp = std::string(mean3max_mib2binp);
  std::string sMean4max_mib2binp = std::string(mean4max_mib2binp);

  char mean1_mib2binp[100];
  char mean2_mib2binp[100];
  char mean3_mib2binp[100];
  char mean4_mib2binp[100];
  sprintf(mean1_mib2binp,"%f",tim1mib2binp->GetMean());
  sprintf(mean2_mib2binp,"%f",tim2mib2binp->GetMean());
  sprintf(mean3_mib2binp,"%f",tim3mib2binp->GetMean());
  sprintf(mean4_mib2binp,"%f",tim4mib2binp->GetMean());
  std::string sMean1_mib2binp = std::string(mean1_mib2binp);
  std::string sMean2_mib2binp = std::string(mean2_mib2binp);
  std::string sMean3_mib2binp = std::string(mean3_mib2binp);
  std::string sMean4_mib2binp = std::string(mean4_mib2binp);

  TString numAmpTim1max;
  if(timmax1mib2binp->GetMean() < 0.){
    sMean1max_mib2binp.erase(sMean1max_mib2binp.begin(),sMean1max_mib2binp.begin()+1);
    numAmpTim1max = den1s+std::string(" && (amp_max[BINP1]>3000 || (amp_max[BINP1]<3000 && fabs(time_max[BINP1]-time_max[MiB2]+")+std::string(sMean1max_mib2binp)+std::string(")<1))");
    } else { 
    numAmpTim1max = den1s+std::string(" && (amp_max[BINP1]>3000 || (amp_max[BINP1]<3000 && fabs(time_max[BINP1]-time_max[MiB2]-")+std::string(sMean1max_mib2binp)+std::string(")<1))");
  }

  TString numAmpTim1;
  if(tim1mib2binp->GetMean() < 0.){
    sMean1_mib2binp.erase(sMean1_mib2binp.begin(),sMean1_mib2binp.begin()+1);
    numAmpTim1 = numAmpTim1max+std::string(" && (amp_max[BINP1]>3000 || (amp_max[BINP1]<3000 && fabs(time[BINP1]-time[MiB2]+")+std::string(sMean1_mib2binp)+std::string(")<1))");
    } else { 
    numAmpTim1 = numAmpTim1max+std::string(" && (amp_max[BINP1]>3000 || (amp_max[BINP1]<3000 && fabs(time[BINP1]-time[MiB2]-")+std::string(sMean1_mib2binp)+std::string(")<1))");
  }

  TString numAndRm2AmpTim2max;
  if(timmax2mib2binp->GetMean() < 0.){
    sMean2max_mib2binp.erase(sMean2max_mib2binp.begin(),sMean2max_mib2binp.begin()+1);
    numAndRm2AmpTim2max = den2s+std::string(" && (amp_max[BINP2]>3000 || (amp_max[BINP2]<3000 && fabs(time_max[BINP2]-time_max[MiB2]+")+std::string(sMean2max_mib2binp)+std::string(")<1))");
    } else { 
    numAndRm2AmpTim2max = den2s+std::string(" && (amp_max[BINP2]>3000 || (amp_max[BINP2]<3000 && fabs(time_max[BINP2]-time_max[MiB2]-")+std::string(sMean2max_mib2binp)+std::string(")<1))");
  }

  TString numAndRm2AmpTim2;
  if(tim2mib2binp->GetMean() < 0.){
    sMean2_mib2binp.erase(sMean2_mib2binp.begin(),sMean2_mib2binp.begin()+1);
    numAndRm2AmpTim2 = numAndRm2AmpTim2max+std::string(" && (amp_max[BINP2]>3000 || (amp_max[BINP2]<3000 && fabs(time[BINP2]-time[MiB2]+")+std::string(sMean2_mib2binp)+std::string(")<1))");
    } else { 
    numAndRm2AmpTim2 = numAndRm2AmpTim2max+std::string(" && (amp_max[BINP2]>3000 || (amp_max[BINP2]<3000 && fabs(time[BINP2]-time[MiB2]-")+std::string(sMean2_mib2binp)+std::string(")<1))");
  }

  TString numAndRm2AmpTim3max;
  if(timmax3mib2binp->GetMean() < 0.){
    sMean3max_mib2binp.erase(sMean3max_mib2binp.begin(),sMean3max_mib2binp.begin()+1);
    numAndRm2AmpTim3max = den3s+std::string(" && (amp_max[BINP3]>3000 || (amp_max[BINP3]<3000 && fabs(time_max[BINP3]-time_max[MiB2]+")+std::string(sMean3max_mib2binp)+std::string(")<1))");
    } else { 
    numAndRm2AmpTim3max = den3s+std::string(" && (amp_max[BINP3]>3000 || (amp_max[BINP3]<3000 && fabs(time_max[BINP3]-time_max[MiB2]-")+std::string(sMean3max_mib2binp)+std::string(")<1))");
  }

  TString numAndRm2AmpTim3;
  if(tim3mib2binp->GetMean() < 0.){
    sMean3_mib2binp.erase(sMean3_mib2binp.begin(),sMean3_mib2binp.begin()+1);
    numAndRm2AmpTim3 = numAndRm2AmpTim3max+std::string(" && (amp_max[BINP3]>3000 || (amp_max[BINP3]<3000 && fabs(time[BINP3]-time[MiB2]+")+std::string(sMean3_mib2binp)+std::string(")<1))");
    } else { 
    numAndRm2AmpTim3 = numAndRm2AmpTim3max+std::string(" && (amp_max[BINP3]>3000 || (amp_max[BINP3]<3000 && fabs(time[BINP3]-time[MiB2]-")+std::string(sMean3_mib2binp)+std::string(")<1))");
  }

  TString numAndRm2AmpTim4max;
  if(timmax4mib2binp->GetMean() < 0.){
    sMean4max_mib2binp.erase(sMean4max_mib2binp.begin(),sMean4max_mib2binp.begin()+1);
    numAndRm2AmpTim4max = den4s+std::string(" && (amp_max[BINP4]>3000 || (amp_max[BINP4]<3000 && fabs(time_max[BINP4]-time_max[MiB2]+")+std::string(sMean4max_mib2binp)+std::string(")<1))");
    } else { 
    numAndRm2AmpTim4max = den4s+std::string(" && (amp_max[BINP4]>3000 || (amp_max[BINP4]<3000 && fabs(time_max[BINP4]-time_max[MiB2]-")+std::string(sMean4max_mib2binp)+std::string(")<1))");
  }

  TString numAndRm2AmpTim4;
  if(tim4mib2binp->GetMean() < 0.){
    sMean4_mib2binp.erase(sMean4_mib2binp.begin(),sMean4_mib2binp.begin()+1);
    numAndRm2AmpTim4 = numAndRm2AmpTim4max+std::string(" && (amp_max[BINP4]>3000 || (amp_max[BINP4]<3000 && fabs(time[BINP4]-time[MiB2]+")+std::string(sMean4_mib2binp)+std::string(")<1))");
    } else { 
    numAndRm2AmpTim4 = numAndRm2AmpTim4max+std::string(" && (amp_max[BINP4]>3000 || (amp_max[BINP4]<3000 && fabs(time[BINP4]-time[MiB2]-")+std::string(sMean4_mib2binp)+std::string(")<1))");
  }

  // numerators
  TString snum1 = numAmpTim1       + " && amp_max[BINP1]>20";
  TString snum2 = numAndRm2AmpTim2 + " && amp_max[BINP2]>20";
  TString snum3 = numAndRm2AmpTim3 + " && amp_max[BINP3]>20";
  TString snum4 = numAndRm2AmpTim4 + " && amp_max[BINP4]>20";
  h4binp1->Project("num1","HVBINP1",snum1); 
  h4binp2->Project("num2","HVBINP2",snum2); 
  h4binp3->Project("num3","HVBINP3",snum3); 
  h4binp4->Project("num4","HVBINP4",snum4); 

  cout << endl;
  cout << "-------------------------------------" << endl;
  cout << "check chiara: " << endl;
  cout << "den1 = " << den1s << endl;
  cout << "den2 = " << den2s << endl;
  cout << "den3 = " << den3s << endl;
  cout << "den4 = " << den4s << endl;
  cout << endl;
  cout << "num1 = " << snum1 << endl;
  cout << "num2 = " << snum2 << endl;
  cout << "num3 = " << snum3 << endl;
  cout << "num4 = " << snum4 << endl;
  cout << "-------------------------------------" << endl;


  // efficiencies
  TGraphAsymmErrors* eff1 = new TGraphAsymmErrors(num1,den1);
  TGraphAsymmErrors* eff2 = new TGraphAsymmErrors(num2,den2);
  TGraphAsymmErrors* eff3 = new TGraphAsymmErrors(num3,den3);
  TGraphAsymmErrors* eff4 = new TGraphAsymmErrors(num4,den4);
  eff1->SetMarkerStyle(20);
  eff1->SetMarkerColor(1);
  eff1->SetLineColor(1);
  eff2->SetMarkerStyle(21);
  eff2->SetMarkerColor(2);
  eff2->SetLineColor(2);
  eff3->SetMarkerStyle(22);
  eff3->SetMarkerColor(3);
  eff3->SetLineColor(3);
  eff4->SetMarkerStyle(23);
  eff4->SetMarkerColor(4);
  eff4->SetLineColor(4);

  TLegend *leg;
  leg = new TLegend(0.1,0.5,0.4,0.8);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.05);
  leg->SetFillColor(0);
  leg->AddEntry(eff1, "40x2+40x2 (Binp1)", "pl");
  leg->AddEntry(eff2, "40x1+40x2 (Binp2)", "pl");
  leg->AddEntry(eff3, "90x1+40x2 (Binp3)", "pl");
  leg->AddEntry(eff4, "90x2+40x2 (Binp4)", "pl");

  TCanvas* c1c = new TCanvas("c1c","c",1);
  c1c->SetGrid();
  TH2F* H2 = new TH2F("H2","",2500,0.,2500.,100,0.,1.);
  H2->GetXaxis()->SetTitle("Bias voltage [V]");
  H2->GetYaxis()->SetTitle("Efficiency");
  H2->Draw();
  eff1->Draw("Plsame"); 
  eff2->Draw("Plsame"); 
  eff3->Draw("Plsame"); 
  eff4->Draw("Plsame");
  leg->Draw();
  c1c->SaveAs("eff_binp2corr.png");
  

  // Spectra comparison
  TH1F *amp1 = new TH1F("amp1","amp1",100,0.,4000);
  TH1F *amp2 = new TH1F("amp2","amp2",100,0.,4000);
  TH1F *amp3 = new TH1F("amp3","amp3",100,0.,4000);
  TH1F *amp4 = new TH1F("amp4","amp4",100,0.,4000);
  amp1->SetLineColor(1);
  amp2->SetLineColor(2);
  amp3->SetLineColor(3);
  amp4->SetLineColor(4);
  amp1->SetLineWidth(2);
  amp2->SetLineWidth(2);
  amp3->SetLineWidth(2);
  amp4->SetLineWidth(2);
  h4binp1 -> Project("amp1","amp_max[BINP1]",den1s+" && HVBINP1==2400");
  h4binp2 -> Project("amp2","amp_max[BINP2]",den2s+" && HVBINP2==1400"); 
  h4binp3 -> Project("amp3","amp_max[BINP3]",den3s+" && HVBINP3==1400");
  h4binp4 -> Project("amp4","amp_max[BINP4]",den4s+" && HVBINP4==2400");

  TCanvas* c1b = new TCanvas("cb","c",1);
  c1b->SetGrid();
  amp1->DrawNormalized(); 
  amp2->DrawNormalized("same"); 
  amp3->DrawNormalized("same"); 
  amp4->DrawNormalized("same"); 
  leg->Draw();
  c1b->SetLogy();
  c1b->SaveAs("amplitude.png");

  TH1F *amp1z = new TH1F("amp1z","amp1z",20,0.,100);
  TH1F *amp2z = new TH1F("amp2z","amp2z",20,0.,100);
  TH1F *amp3z = new TH1F("amp3z","amp3z",20,0.,100);
  TH1F *amp4z = new TH1F("amp4z","amp4z",20,0.,100);
  amp1z->SetLineColor(1);
  amp2z->SetLineColor(2);
  amp3z->SetLineColor(3);
  amp4z->SetLineColor(4);
  amp1z->SetLineWidth(2);
  amp2z->SetLineWidth(2);
  amp3z->SetLineWidth(2);
  amp4z->SetLineWidth(2);
  h4binp1 -> Project("amp1z","amp_max[BINP1]",den1s+" && HVBINP1==2400");
  h4binp2 -> Project("amp2z","amp_max[BINP2]",den2s+" && HVBINP2==1400"); 
  h4binp3 -> Project("amp3z","amp_max[BINP3]",den3s+" && HVBINP3==1400");
  h4binp4 -> Project("amp4z","amp_max[BINP4]",den4s+" && HVBINP4==2400");

  TCanvas* c1bz = new TCanvas("cbz","c",1);
  c1bz->SetGrid();
  amp1z->DrawNormalized(); 
  amp2z->DrawNormalized("same"); 
  amp3z->DrawNormalized("same"); 
  amp4z->DrawNormalized("same"); 
  //leg->Draw();
  c1bz->SetLogy();
  c1bz->SaveAs("amplitudeZoom.png");



  // -------------------------------------------------------------------------------

  // Efficiency in timing runs
  TH1F* num124tim1 = new TH1F("num124tim1","",2500,-2500.,2500.);
  TH1F* num124tim2 = new TH1F("num124tim2","",2500,-2500.,2500.);
  TH1F* num124tim4 = new TH1F("num124tim4","",2500,-2500.,2500.);
  TH1F* num3tim    = new TH1F("num3tim",   "",2500,-2500.,2500.);
  TH1F* den124tim  = new TH1F("den124tim","", 2500,-2500.,2500.);
  TH1F* den3tim    = new TH1F("den3tim",  "", 2500,-2500.,2500.);

  // Compute mean timing distance between Mib2 and Rm2 (not for Binp3 timing runs, RM2 OFF) - to be added to denominator
  TH1F* tim124_rm2mib2 = new TH1F("tim124_rm2mib2","tim124_rm2mib2",4000,-20.,20.);
  h4timing124->Project("tim124_rm2mib2","time_max[Rm2]-time_max[MiB2]",commonDenAndRm2Amp);
  char mean124_rm2mib2[100];
  sprintf(mean124_rm2mib2,"%f",tim124_rm2mib2->GetMean());
  std::string sMean124_rm2mib2 = std::string(mean124_rm2mib2);
  
  // Denominators for timing runs
  TString den3_timingRuns = commonDenAmp;
  TString den124_timingRuns;
  if(tim124_rm2mib2->GetMean() < 0.){
    sMean124_rm2mib2.erase(sMean124_rm2mib2.begin(),sMean124_rm2mib2.begin()+1);
    den124_timingRuns = commonDenAndRm2Amp+std::string(" && fabs(time_max[Rm2]-time_max[MiB2]+")+std::string(sMean124_rm2mib2)+std::string(")<1");
    } else { 
    den124_timingRuns = commonDenAndRm2Amp+std::string(" && fabs(time_max[Rm2]-time_max[MiB2]-")+std::string(sMean124_rm2mib2)+std::string(")<1");
  }
  h4timing124->Project("den124tim","X",den124_timingRuns);
  h4timing3  ->Project("den3tim",  "X",den3_timingRuns);

  // Compute mean timing distance between Binps and Mib2 - to be added to numerator
  TH1F* tim124_mib2binp1 = new TH1F("tim124_mib2binp1", "tim124_mib2binp1",  4000,-20.,20.);
  TH1F* tim124_mib2binp2 = new TH1F("tim124_mib2binp2", "tim124_mib2binp2",  4000,-20.,20.);
  TH1F* tim124_mib2binp4 = new TH1F("tim124_mib2binp4", "tim124_mib2binp4",  4000,-20.,20.);
  TH1F* tim3_mib2binp3   = new TH1F("tim3_mib2binp3",   "tim3_mib2binp3",    4000,-20.,20.);

  TH1F* timmax124_mib2binp1 = new TH1F("timmax124_mib2binp1", "timmax124_mib2binp1",  4000,-20.,20.);
  TH1F* timmax124_mib2binp2 = new TH1F("timmax124_mib2binp2", "timmax124_mib2binp2",  4000,-20.,20.);
  TH1F* timmax124_mib2binp4 = new TH1F("timmax124_mib2binp4", "timmax124_mib2binp4",  4000,-20.,20.);
  TH1F* timmax3_mib2binp3   = new TH1F("timmax3_mib2binp3",   "timmax3_mib2binp3",    4000,-20.,20.);

  h4timing124->Project("tim124_mib2binp1","time[BINP1]-time[MiB2]",den124_timingRuns+" && amp_max[BINP1]<3000 && amp_max[BINP1]>20");
  h4timing124->Project("tim124_mib2binp2","time[BINP2]-time[MiB2]",den124_timingRuns+" && amp_max[BINP2]<3000 && amp_max[BINP2]>20");
  h4timing124->Project("tim124_mib2binp4","time[BINP4]-time[MiB2]",den124_timingRuns+" && amp_max[BINP4]<3000 && amp_max[BINP4]>20");
  h4timing3->Project("tim3_mib2binp3","time[BINP3]-time[MiB2]",den3_timingRuns+" && amp_max[BINP3]<3000 && amp_max[BINP3]>20");

  h4timing124->Project("timmax124_mib2binp1","time_max[BINP1]-time_max[MiB2]",den124_timingRuns+" && amp_max[BINP1]<3000 && amp_max[BINP1]>20");
  h4timing124->Project("timmax124_mib2binp2","time_max[BINP2]-time_max[MiB2]",den124_timingRuns+" && amp_max[BINP2]<3000 && amp_max[BINP2]>20");
  h4timing124->Project("timmax124_mib2binp4","time_max[BINP4]-time_max[MiB2]",den124_timingRuns+" && amp_max[BINP4]<3000 && amp_max[BINP4]>20");
  h4timing3  ->Project("timmax3_mib2binp3","time_max[BINP3]-time_max[MiB2]",den3_timingRuns+" && amp_max[BINP3]<3000 && amp_max[BINP3]>20");

  char mean1tim_mib2binp[100];
  char mean2tim_mib2binp[100];
  char mean3tim_mib2binp[100];
  char mean4tim_mib2binp[100];
  sprintf(mean1tim_mib2binp,"%f",tim124_mib2binp1->GetMean());
  sprintf(mean2tim_mib2binp,"%f",tim124_mib2binp2->GetMean());
  sprintf(mean3tim_mib2binp,"%f",tim3_mib2binp3->GetMean());
  sprintf(mean4tim_mib2binp,"%f",tim124_mib2binp4->GetMean());
  std::string sMean1tim_mib2binp = std::string(mean1tim_mib2binp);
  std::string sMean2tim_mib2binp = std::string(mean2tim_mib2binp);
  std::string sMean3tim_mib2binp = std::string(mean3tim_mib2binp);
  std::string sMean4tim_mib2binp = std::string(mean4tim_mib2binp);

  char mean1timmax_mib2binp[100];
  char mean2timmax_mib2binp[100];
  char mean3timmax_mib2binp[100];
  char mean4timmax_mib2binp[100];
  sprintf(mean1timmax_mib2binp,"%f",timmax124_mib2binp1->GetMean());
  sprintf(mean2timmax_mib2binp,"%f",timmax124_mib2binp2->GetMean());
  sprintf(mean3timmax_mib2binp,"%f",timmax3_mib2binp3->GetMean());
  sprintf(mean4timmax_mib2binp,"%f",timmax124_mib2binp4->GetMean());
  std::string sMean1timmax_mib2binp = std::string(mean1timmax_mib2binp);
  std::string sMean2timmax_mib2binp = std::string(mean2timmax_mib2binp);
  std::string sMean3timmax_mib2binp = std::string(mean3timmax_mib2binp);
  std::string sMean4timmax_mib2binp = std::string(mean4timmax_mib2binp);

  TString num1max_timingRuns;
  if(timmax124_mib2binp1->GetMean() < 0.){
    sMean1timmax_mib2binp.erase(sMean1timmax_mib2binp.begin(),sMean1timmax_mib2binp.begin()+1);
    num1max_timingRuns = den124_timingRuns+std::string(" && (amp_max[BINP1]>3000 || (amp_max[BINP1]<3000 && fabs(time_max[BINP1]-time_max[MiB2]+")+std::string(sMean1timmax_mib2binp)+std::string(")<1))");
    } else { 
    num1max_timingRuns = den124_timingRuns+std::string(" && (amp_max[BINP1]>3000 || (amp_max[BINP1]<3000 && fabs(time_max[BINP1]-time_max[MiB2]-")+std::string(sMean1timmax_mib2binp)+std::string(")<1))");
  }					       
  TString num1_timingRuns;
  if(tim124_mib2binp1->GetMean() < 0.){
    sMean1tim_mib2binp.erase(sMean1tim_mib2binp.begin(),sMean1tim_mib2binp.begin()+1);
    num1_timingRuns = num1max_timingRuns+std::string(" && (amp_max[BINP1]>3000 || (amp_max[BINP1]<3000 && fabs(time[BINP1]-time[MiB2]+")+std::string(sMean1tim_mib2binp)+std::string(")<1))");
    } else { 
    num1_timingRuns = num1max_timingRuns+std::string(" && (amp_max[BINP1]>3000 || (amp_max[BINP1]<3000 && fabs(time[BINP1]-time[MiB2]-")+std::string(sMean1tim_mib2binp)+std::string(")<1))");
  }					       

  TString num2max_timingRuns;
  if(timmax124_mib2binp2->GetMean() < 0.){
    sMean2timmax_mib2binp.erase(sMean2timmax_mib2binp.begin(),sMean2timmax_mib2binp.begin()+1);
    num2max_timingRuns = den124_timingRuns+std::string(" && (amp_max[BINP2]>3000 || (amp_max[BINP2]<3000 && fabs(time_max[BINP2]-time_max[MiB2]+")+std::string(sMean2timmax_mib2binp)+std::string(")<1))");
    } else { 
    num2max_timingRuns = den124_timingRuns+std::string(" && (amp_max[BINP2]>3000 || (amp_max[BINP2]<3000 && fabs(time_max[BINP2]-time_max[MiB2]-")+std::string(sMean2timmax_mib2binp)+std::string(")<1))");
  }					       
  TString num2_timingRuns;
  if(tim124_mib2binp2->GetMean() < 0.){
    sMean2tim_mib2binp.erase(sMean2tim_mib2binp.begin(),sMean2tim_mib2binp.begin()+1);
    num2_timingRuns = num2max_timingRuns+std::string(" && (amp_max[BINP2]>3000 || (amp_max[BINP2]<3000 && fabs(time[BINP2]-time[MiB2]+")+std::string(sMean2tim_mib2binp)+std::string(")<1))");
    } else { 
    num2_timingRuns = num2max_timingRuns+std::string(" && (amp_max[BINP2]>3000 || (amp_max[BINP2]<3000 && fabs(time[BINP2]-time[MiB2]-")+std::string(sMean2tim_mib2binp)+std::string(")<1))");
  }					       

  TString num3max_timingRuns;
  if(timmax3_mib2binp3->GetMean() < 0.){
    sMean3timmax_mib2binp.erase(sMean3timmax_mib2binp.begin(),sMean3timmax_mib2binp.begin()+1);
    num3max_timingRuns = den3_timingRuns+std::string(" && (amp_max[BINP3]>3000 || (amp_max[BINP3]<3000 && fabs(time_max[BINP3]-time_max[MiB2]+")+std::string(sMean3timmax_mib2binp)+std::string(")<1))");
    } else { 
    num3max_timingRuns = den3_timingRuns+std::string(" && (amp_max[BINP3]>3000 || (amp_max[BINP3]<3000 && fabs(time_max[BINP3]-time_max[MiB2]-")+std::string(sMean3timmax_mib2binp)+std::string(")<1))");
  }					       
  TString num3_timingRuns;
  if(tim3_mib2binp3->GetMean() < 0.){
    sMean3tim_mib2binp.erase(sMean3tim_mib2binp.begin(),sMean3tim_mib2binp.begin()+1);
    num3_timingRuns = num3max_timingRuns+std::string(" && (amp_max[BINP3]>3000 || (amp_max[BINP3]<3000 && fabs(time[BINP3]-time[MiB2]+")+std::string(sMean3tim_mib2binp)+std::string(")<1))");
    } else { 
    num3_timingRuns = num3max_timingRuns+std::string(" && (amp_max[BINP3]>3000 || (amp_max[BINP3]<3000 && fabs(time[BINP3]-time[MiB2]-")+std::string(sMean3tim_mib2binp)+std::string(")<1))");
  }					       

  TString num4max_timingRuns;
  if(timmax124_mib2binp4->GetMean() < 0.){
    sMean4timmax_mib2binp.erase(sMean4timmax_mib2binp.begin(),sMean4timmax_mib2binp.begin()+1);
    num4max_timingRuns = den124_timingRuns+std::string(" && (amp_max[BINP4]>3000 || (amp_max[BINP4]<3000 && fabs(time_max[BINP4]-time_max[MiB2]+")+std::string(sMean4timmax_mib2binp)+std::string(")<1))");
    } else { 
    num4max_timingRuns = den124_timingRuns+std::string(" && (amp_max[BINP4]>3000 || (amp_max[BINP4]<3000 && fabs(time_max[BINP4]-time_max[MiB2]-")+std::string(sMean4timmax_mib2binp)+std::string(")<1))");
  }					       
  TString num4_timingRuns;
  if(tim124_mib2binp4->GetMean() < 0.){
    sMean4tim_mib2binp.erase(sMean4tim_mib2binp.begin(),sMean4tim_mib2binp.begin()+1);
    num4_timingRuns = num4max_timingRuns+std::string(" && (amp_max[BINP4]>3000 || (amp_max[BINP4]<3000 && fabs(time[BINP4]-time[MiB2]+")+std::string(sMean4tim_mib2binp)+std::string(")<1))");
    } else { 
    num4_timingRuns = num4max_timingRuns+std::string(" && (amp_max[BINP4]>3000 || (amp_max[BINP4]<3000 && fabs(time[BINP4]-time[MiB2]-")+std::string(sMean4tim_mib2binp)+std::string(")<1))");
  }					       

  // numerators for timing runs
  TString snum1_timing = num1_timingRuns + " && amp_max[BINP1]>20";
  TString snum2_timing = num2_timingRuns + " && amp_max[BINP2]>20";
  TString snum3_timing = num3_timingRuns + " && amp_max[BINP3]>20";
  TString snum4_timing = num4_timingRuns + " && amp_max[BINP4]>20";
  h4timing124->Project("num124tim1","X",snum1_timing);
  h4timing124->Project("num124tim2","X",snum2_timing);
  h4timing3->Project("num3tim","X",snum3_timing);
  h4timing124->Project("num124tim4","X",snum4_timing);

  cout << "-----------------------------------------" << endl;
  cout << "Timing runs" << endl;
  cout << "den124: " << den124_timingRuns << endl;
  cout << "den3: "   << den3_timingRuns << endl;
  cout << "num1: "   << snum1_timing << endl;
  cout << "num2: "   << snum2_timing << endl;
  cout << "num3: "   << snum3_timing << endl;
  cout << "num4: "   << snum4_timing << endl;

  float numT1 = num124tim1->Integral();
  float numT2 = num124tim2->Integral();
  float numT4 = num124tim4->Integral();
  float denT124 = den124tim->Integral();
  //
  float numT3 = num3tim->Integral();
  float denT3 = den3tim->Integral();

  cout << "Efficiencies in timing runs: " << endl;
  cout << "Binp1 = " << numT1/denT124 << endl;
  cout << "Binp2 = " << numT2/denT124 << endl;
  cout << "Binp3 = " << numT3/denT3 << endl;
  cout << "Binp4 = " << numT4/denT124 << endl;


  // Spectra comparison on timing runs
  TH1F *amp1T = new TH1F("amp1T","amp1T",100,0.,4000);
  TH1F *amp2T = new TH1F("amp2T","amp2T",100,0.,4000);
  TH1F *amp3T = new TH1F("amp3T","amp3T",100,0.,4000);
  TH1F *amp4T = new TH1F("amp4T","amp4T",100,0.,4000);
  amp1T->SetLineColor(1);
  amp2T->SetLineColor(2);
  amp3T->SetLineColor(3);
  amp4T->SetLineColor(4);
  amp1T->SetLineWidth(2);
  amp2T->SetLineWidth(2);
  amp3T->SetLineWidth(2);
  amp4T->SetLineWidth(2);
  h4timing124 ->Project("amp1T","amp_max[BINP1]",den124_timingRuns);
  h4timing124 ->Project("amp2T","amp_max[BINP2]",den124_timingRuns);
  h4timing3   ->Project("amp3T","amp_max[BINP3]",den3_timingRuns);
  h4timing124 ->Project("amp4T","amp_max[BINP4]",den124_timingRuns);

  TCanvas* c2a = new TCanvas("c2a","c",1);
  c2a->SetGrid();
  amp1T->DrawNormalized(); 
  amp2T->DrawNormalized("same"); 
  amp3T->DrawNormalized("same"); 
  amp4T->DrawNormalized("same"); 
  leg->Draw();
  c2a->SetLogy();
  c2a->SaveAs("amplitude_timingRuns.png");

}
	
