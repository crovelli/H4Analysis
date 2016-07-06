#include "WFAnalyzer.h"

//----------Utils-------------------------------------------------------------------------
bool WFAnalyzer::Begin(CfgManager& opts, uint64* index)
{
    //---inputs---
    if(!opts.OptExist(instanceName_+".srcInstanceName"))
    {
        cout << ">>> FFTAnalyzer ERROR: no source plugin specified" << endl;
        return false;
    }
    srcInstance_ = opts.GetOpt<string>(instanceName_+".srcInstanceName");
    float nSamples = opts.GetOpt<int>(srcInstance_+".nSamples");
    channelsNames_ = opts.GetOpt<vector<string> >(instanceName_+".channelsNames");
    timeRecoTypes_ = opts.GetOpt<vector<string> >(instanceName_+".timeRecoTypes");

    //---channels setup
    string templateTag="";
    if(opts.OptExist(instanceName_+".templateTags"))
        for(auto& tag : opts.GetOpt<vector<string> >(instanceName_+".templateTags"))
            for(auto& run : opts.GetOpt<vector<string> >(tag+".runList"))
                if(run == opts.GetOpt<string>("h4reco.run"))
                    templateTag = tag;

    for(auto& channel : channelsNames_)
    {        
        if(opts.OptExist(channel+".templateFit.file"))
        {            
            TFile* templateFile = TFile::Open(opts.GetOpt<string>(channel+".templateFit.file", 0).c_str(), ".READ");
            TH1* wfTemplate=(TH1*)templateFile->Get((opts.GetOpt<string>(channel+".templateFit.file", 1)+
                                                     +"_"+templateTag).c_str());
            templateFile->Close();
        }
        //---keep track of all the possible time reco method requested
        for(auto type_name : timeRecoTypes_)
        {
            if(opts.OptExist(channel+"."+type_name))
                timeOpts_[channel+"."+type_name] = opts.GetOpt<vector<float> >(channel+"."+type_name);
        }
    }
    
    //---outputs---
    string recoTreeName = opts.OptExist(instanceName_+".recoTreeName") ?
        opts.GetOpt<string>(instanceName_+".recoTreeName") : "digi";
    bool storeTree = opts.OptExist(instanceName_+".storeTree") ?
        opts.GetOpt<bool>(instanceName_+".storeTree") : true;
    RegisterSharedData(new TTree(recoTreeName.c_str(), "digi_tree"), "digi_tree", storeTree);
    recoTree_ = DigiTree(index, (TTree*)data_.back().obj);
    recoTree_.Init(channelsNames_, timeRecoTypes_);
    if(opts.GetOpt<int>(instanceName_+".fillWFtree"))
    {
        string wfTreeName = opts.OptExist(instanceName_+".wfTreeName") ?
            opts.GetOpt<string>(instanceName_+".wfTreeName") : "wf";
        RegisterSharedData(new TTree(wfTreeName.c_str(), "wf_tree"), "wf_tree", true);
        outWFTree_ = WFTree(channelsNames_.size(), nSamples, index, (TTree*)data_.back().obj);
        outWFTree_.Init();
    }

    return true;
}

bool WFAnalyzer::ProcessEvent(const H4Tree& event, map<string, PluginBase*>& plugins, CfgManager& opts)
{
    //---setup output event 
    int outCh=0;
    bool fillWFtree=false;
    if(opts.GetOpt<int>(instanceName_+".fillWFtree"))
        fillWFtree = *recoTree_.index % opts.GetOpt<int>(instanceName_+".WFtreePrescale") == 0;

    //---load WFs from source instance shared data
    if(WFs_.size() == 0)
    {
        for(auto& channel : channelsNames_)
            WFs_[channel] = (WFClass*)plugins[srcInstance_]->GetSharedData(srcInstance_+"_"+channel, "", false).at(0).obj;
    }
    
    //---compute reco variables
    for(auto& channel : channelsNames_)
    {        
        //---subtract a specified channel if requested
        if(opts.OptExist(channel+".subtractChannel"))
            *WFs_[channel] -= *WFs_[opts.GetOpt<string>(channel+".subtractChannel")];        
        WFs_[channel]->SetBaselineWindow(opts.GetOpt<int>(channel+".baselineWin", 0), 
                                        opts.GetOpt<int>(channel+".baselineWin", 1));
        WFs_[channel]->SetSignalWindow(opts.GetOpt<int>(channel+".signalWin", 0), 
                                      opts.GetOpt<int>(channel+".signalWin", 1));
        WFBaseline baselineInfo = WFs_[channel]->SubtractBaseline();
        WFFitResults interpolAmpMax = WFs_[channel]->GetInterpolatedAmpMax(-1,-1,opts.GetOpt<int>(channel+".signalWin", 2));
        recoTree_.b_charge[outCh] = WFs_[channel]->GetIntegral(opts.GetOpt<int>(channel+".baselineInt", 0), 
                                                             opts.GetOpt<int>(channel+".baselineInt", 1));        
        recoTree_.b_slope[outCh] = baselineInfo.slope;
        recoTree_.b_rms[outCh] = baselineInfo.rms;
        recoTree_.maximum[outCh] = WFs_[channel]->GetAmpMax();
        recoTree_.time_maximum[outCh] = WFs_[channel]->GetTimeCF(1).first;
        recoTree_.amp_max[outCh] = interpolAmpMax.ampl;
        recoTree_.time_max[outCh] = interpolAmpMax.time;
        recoTree_.chi2_max[outCh] = interpolAmpMax.chi2;
        recoTree_.charge_tot[outCh] = WFs_[channel]->GetModIntegral(opts.GetOpt<int>(channel+".baselineInt", 1), 
                                                                   WFs_[channel]->GetNSample());
        recoTree_.charge_sig[outCh] = WFs_[channel]->GetSignalIntegral(opts.GetOpt<int>(channel+".signalInt", 0), 
                                                                     opts.GetOpt<int>(channel+".signalInt", 1));
        //---compute time with all the requested time reconstruction method
        for(int iT=0; iT<timeRecoTypes_.size(); ++iT)
        {
            //---compute time with selected method or store default value (-99)
            if(timeOpts_.find(channel+"."+timeRecoTypes_[iT]) != timeOpts_.end())
            {
                pair<float, float> timeInfo = WFs_[channel]->GetTime(timeRecoTypes_[iT], timeOpts_[channel+"."+timeRecoTypes_[iT]]);
                recoTree_.time[outCh+iT*channelsNames_.size()] = timeInfo.first;
                recoTree_.time_chi2[outCh+iT*channelsNames_.size()] = timeInfo.second;
            }
            else
            {
                recoTree_.time[outCh+iT*channelsNames_.size()] = -99;
                recoTree_.time_chi2[outCh+iT*channelsNames_.size()] = -99;
            }
        }
        
        //---template fit (only specified channels)
        WFFitResults fitResults{-1, -1000, -1};
        if(opts.OptExist(channel+".templateFit.file"))
        {
            WFs_[channel]->SetTemplate(templates_[channel]);
            fitResults = WFs_[channel]->TemplateFit(opts.GetOpt<float>(channel+".templateFit.fitWin", 0),
                                                   opts.GetOpt<int>(channel+".templateFit.fitWin", 1),
                                                   opts.GetOpt<int>(channel+".templateFit.fitWin", 2));
            recoTree_.fit_ampl[outCh] = fitResults.ampl;
            recoTree_.fit_time[outCh] = fitResults.time;
            recoTree_.fit_chi2[outCh] = fitResults.chi2;
        }            
	//---calibration constant for each channel if needed
	if(opts.OptExist(channel+".calibration.calibrationConst"))
	  recoTree_.calibration[outCh]=opts.GetOpt<float>(channel+".calibration.calibrationConst");
	else
	  recoTree_.calibration[outCh]=1;
	
        //---WFs---
        if(fillWFtree)
        {
            vector<double>* analizedWF = WFs_[channel]->GetSamples();
            int nSamples = analizedWF->size();
            float tUnit = WFs_[channel]->GetTUnit();
            for(int jSample=0; jSample<analizedWF->size(); ++jSample)
            {
                outWFTree_.WF_ch[jSample+outCh*nSamples] = outCh;
                outWFTree_.WF_time[jSample+outCh*nSamples] = jSample*tUnit;
                outWFTree_.WF_val[jSample+outCh*nSamples] = analizedWF->at(jSample);
            }
        }
        //---increase output tree channel counter
        ++outCh;
    }

    //---fill the output trees 
    //---reco var
    recoTree_.Fill();
    //---WFs
    if(fillWFtree)
        outWFTree_.Fill();

    return true;
}