#include "TFile.h" 
#include "TTree.h" 
#include "TStyle.h" 
#include "TH1.h" 
#include "TH2.h" 
#include "TCanvas.h"
#include "TLegend.h"
#include "TGraphAsymmErrors.h" 

void EfficiencySyst() {

  gStyle->SetOptStat(0);

  TFile* inFileBinp1 = new TFile("btf2016_HVscanBinp1.root");
  // Binp1 (HV+3700), Binp2 (HV+3700), Binp3 (HV+3700, but timing configuration)                                    --> use binp1 / binp2 only

  TFile* inFileBinp2 = new TFile("btf2016_RU1_2339.root");
  // Binp2 (only run 2339 with HV+3700), Binp3 (only run 2339 with HV+3700), 
  // Binp4 (only run 2339 with HV+3700 but strange results and HV-=0 in the run after => probably can't be used)    --> use binp2 / binp3  run 2339 only
                                                                              

  TFile* inFileBinp3 = new TFile("btf2016_HVscanBinp3.root");
  // Binp3 (HV+3700), Binp4 (HV+3700), Binp1 (HV+3700)                                                              --> use binp3 / 4 / 1

  TFile* inFileBinp4 = new TFile("btf2016_HVscanBinp4.root");
  // Binp4 (HV+3700), Binp1 (HV+3700), Binp2 (HV+3700)                                                              --> use binp4 / 1 / 2
  

  TTree* h4binp1_fir = (TTree*)inFileBinp1->Get("h4");
  TTree* h4binp1_sec = (TTree*)inFileBinp4->Get("h4");
  TTree* h4binp1_thi = (TTree*)inFileBinp3->Get("h4");

  TTree* h4binp2_fir = (TTree*)inFileBinp2->Get("h4");
  TTree* h4binp2_sec = (TTree*)inFileBinp1->Get("h4");
  TTree* h4binp2_thi = (TTree*)inFileBinp4->Get("h4");

  TTree* h4binp3_fir = (TTree*)inFileBinp3->Get("h4");
  TTree* h4binp3_sec = (TTree*)inFileBinp2->Get("h4");

  TTree* h4binp4_fir = (TTree*)inFileBinp4->Get("h4");
  TTree* h4binp4_sec = (TTree*)inFileBinp3->Get("h4");
  

  // histos
  TH1F* num1_fir = new TH1F("num1_fir","",2500,0.,2500.);
  TH1F* num1_sec = new TH1F("num1_sec","",2500,0.,2500.);
  TH1F* num1_thi = new TH1F("num1_thi","",2500,0.,2500.);
  TH1F* num2_fir = new TH1F("num2_fir","",2500,0.,2500.);
  TH1F* num2_sec = new TH1F("num2_sec","",2500,0.,2500.);
  TH1F* num2_thi = new TH1F("num2_thi","",2500,0.,2500.);
  TH1F* num3_fir = new TH1F("num3_fir","",2500,0.,2500.);
  TH1F* num3_sec = new TH1F("num3_sec","",2500,0.,2500.);
  TH1F* num4_fir = new TH1F("num4_fir","",2500,0.,2500.);
  TH1F* num4_sec = new TH1F("num4_sec","",2500,0.,2500.);
  /////////////////
  TH1F* den1_fir = new TH1F("den1_fir","",2500,0.,2500.);
  TH1F* den1_sec = new TH1F("den1_sec","",2500,0.,2500.);
  TH1F* den1_thi = new TH1F("den1_thi","",2500,0.,2500.);
  TH1F* den2_fir = new TH1F("den2_fir","",2500,0.,2500.);
  TH1F* den2_sec = new TH1F("den2_sec","",2500,0.,2500.);
  TH1F* den2_thi = new TH1F("den2_thi","",2500,0.,2500.);
  TH1F* den3_fir = new TH1F("den3_fir","",2500,0.,2500.);
  TH1F* den3_sec = new TH1F("den3_sec","",2500,0.,2500.);
  TH1F* den4_fir = new TH1F("den4_fir","",2500,0.,2500.);
  TH1F* den4_sec = new TH1F("den4_sec","",2500,0.,2500.);

  
  // denominators
  TString commonDen = "adc_data>200 && adc_data<700 && amp_max[MiB2]>200";
  TString commonDenAndRm2 = commonDen + "&& amp_max[Rm2]>200 && amp_max[Rm2]<1200";
  TString denBinp2 = commonDenAndRm2 + "&& (run==2339)";

  h4binp1_fir->Project("den1_fir","HVBINP1",commonDen);    
  h4binp1_sec->Project("den1_sec","HVBINP1",commonDenAndRm2);
  h4binp1_thi->Project("den1_thi","HVBINP1",commonDenAndRm2);

  h4binp2_fir->Project("den2_fir","HVBINP2",denBinp2);   
  h4binp2_sec->Project("den2_sec","HVBINP2",commonDen);   
  h4binp2_thi->Project("den2_thi","HVBINP2",commonDenAndRm2);   

  h4binp3_fir->Project("den3_fir","HVBINP3",commonDenAndRm2);
  h4binp3_sec->Project("den3_sec","HVBINP3",denBinp2);

  h4binp4_fir->Project("den4_fir","HVBINP4",commonDenAndRm2);
  h4binp4_sec->Project("den4_sec","HVBINP4",commonDenAndRm2);

  // numerators
  h4binp1_fir->Project("num1_fir","HVBINP1",commonDen+"&& amp_max[BINP1]>20");    
  h4binp1_sec->Project("num1_sec","HVBINP1",commonDenAndRm2+"&& amp_max[BINP1]>20");
  h4binp1_thi->Project("num1_thi","HVBINP1",commonDenAndRm2+"&& amp_max[BINP1]>20");

  h4binp2_fir->Project("num2_fir","HVBINP2",denBinp2+"&& amp_max[BINP2]>20");   
  h4binp2_sec->Project("num2_sec","HVBINP2",commonDen+"&& amp_max[BINP2]>20");   
  h4binp2_thi->Project("num2_thi","HVBINP2",commonDenAndRm2+"&& amp_max[BINP2]>20");   

  h4binp3_fir->Project("num3_fir","HVBINP3",commonDenAndRm2+"&& amp_max[BINP3]>20");
  h4binp3_sec->Project("num3_sec","HVBINP3",denBinp2+"&& amp_max[BINP3]>20");

  h4binp4_fir->Project("num4_fir","HVBINP4",commonDenAndRm2+"&& amp_max[BINP4]>20");
  h4binp4_sec->Project("num4_sec","HVBINP4",commonDenAndRm2+"&& amp_max[BINP4]>20");


  // efficiencies
  TGraphAsymmErrors* eff1_fir = new TGraphAsymmErrors(num1_fir,den1_fir);
  TGraphAsymmErrors* eff1_sec = new TGraphAsymmErrors(num1_sec,den1_sec);
  TGraphAsymmErrors* eff1_thi = new TGraphAsymmErrors(num1_thi,den1_thi);

  TGraphAsymmErrors* eff2_fir = new TGraphAsymmErrors(num2_fir,den2_fir);
  TGraphAsymmErrors* eff2_sec = new TGraphAsymmErrors(num2_sec,den2_sec);
  TGraphAsymmErrors* eff2_thi = new TGraphAsymmErrors(num2_thi,den2_thi);

  TGraphAsymmErrors* eff3_fir = new TGraphAsymmErrors(num3_fir,den3_fir);
  TGraphAsymmErrors* eff3_sec = new TGraphAsymmErrors(num3_sec,den3_sec);

  TGraphAsymmErrors* eff4_fir = new TGraphAsymmErrors(num4_fir,den4_fir);
  TGraphAsymmErrors* eff4_sec = new TGraphAsymmErrors(num4_sec,den4_sec);

  eff1_fir->SetMarkerStyle(20);
  eff1_fir->SetMarkerColor(1);
  eff1_fir->SetLineColor(1);
  eff2_fir->SetMarkerStyle(20);
  eff2_fir->SetMarkerColor(1);
  eff2_fir->SetLineColor(1);
  eff3_fir->SetMarkerStyle(20);
  eff3_fir->SetMarkerColor(1);
  eff3_fir->SetLineColor(1);
  eff4_fir->SetMarkerStyle(20);
  eff4_fir->SetMarkerColor(1);
  eff4_fir->SetLineColor(1);

  eff1_sec->SetMarkerStyle(21);
  eff1_sec->SetMarkerColor(2);
  eff1_sec->SetLineColor(2);
  eff2_sec->SetMarkerStyle(21);
  eff2_sec->SetMarkerColor(2);
  eff2_sec->SetLineColor(2);
  eff3_sec->SetMarkerStyle(21);
  eff3_sec->SetMarkerColor(2);
  eff3_sec->SetLineColor(2);
  eff4_sec->SetMarkerStyle(21);
  eff4_sec->SetMarkerColor(2);
  eff4_sec->SetLineColor(2);

  eff1_thi->SetMarkerStyle(22);
  eff1_thi->SetMarkerColor(3);
  eff1_thi->SetLineColor(3);
  eff2_thi->SetMarkerStyle(22);
  eff2_thi->SetMarkerColor(3);
  eff2_thi->SetLineColor(3);

  TLegend *leg;
  leg = new TLegend(0.1,0.5,0.4,0.8);
  leg->SetFillStyle(0);
  leg->SetBorderSize(0);
  leg->SetTextSize(0.05);
  leg->SetFillColor(0);
  leg->AddEntry(eff1_fir, "first", "p");
  leg->AddEntry(eff1_sec, "second", "p");
  leg->AddEntry(eff1_thi, "third", "p");

  TLegend *leg2;
  leg2 = new TLegend(0.1,0.5,0.4,0.8);
  leg2->SetFillStyle(0);
  leg2->SetBorderSize(0);
  leg2->SetTextSize(0.05);
  leg2->SetFillColor(0);
  leg2->AddEntry(eff1_fir, "first", "p");
  leg2->AddEntry(eff1_sec, "second", "p");

  TH2F* H2 = new TH2F("H2","",2500,0.,2500.,100,0.,1.);
  H2->GetXaxis()->SetTitle("Bias voltage [V]");
  H2->GetYaxis()->SetTitle("Efficiency");

  TCanvas* c1 = new TCanvas("c1","c",1);
  c1->SetGrid();
  H2->SetTitle("binp1");
  H2->Draw();
  eff1_fir->Draw("Plsame"); 
  eff1_sec->Draw("Plsame"); 
  eff1_thi->Draw("Plsame"); 
  leg->Draw();
  c1->SaveAs("eff1.png");

  TCanvas* c2 = new TCanvas("c2","c",1);
  c2->SetGrid();
  H2->SetTitle("binp2");
  H2->Draw();
  eff2_fir->Draw("Plsame"); 
  eff2_sec->Draw("Plsame"); 
  eff2_thi->Draw("Plsame"); 
  leg->Draw();
  c2->SaveAs("eff2.png");

  TCanvas* c3 = new TCanvas("c3","c",1);
  c3->SetGrid();
  H2->SetTitle("binp3");
  H2->Draw();
  eff3_fir->Draw("Plsame"); 
  eff3_sec->Draw("Plsame"); 
  leg2->Draw();
  c3->SaveAs("eff3.png");

  TCanvas* c4 = new TCanvas("c4","c",1);
  c4->SetGrid();
  H2->SetTitle("binp4");
  H2->Draw();
  eff4_fir->Draw("Plsame"); 
  eff4_sec->Draw("Plsame"); 
  leg2->Draw();
  c4->SaveAs("eff4.png");
}
	
