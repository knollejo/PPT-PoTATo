#include <iostream>
#include <vector>

#include <TAttFill.h>
#include <TAttLine.h>
#include <TAttMarker.h>
#include <TCanvas.h>
#include <TChain.h>
#include <TFile.h>
#include <TH1.h>
#include <THStack.h>
#include <TLatex.h>
#include <TLegend.h>
#include <TLegendEntry.h>
#include <TObject.h>
#include <TString.h>
#include <TStyle.h>
#include <TTree.h>
#include <TTreeReader.h>
#include <TTreeReaderArray.h>
#include <TTreeReaderValue.h>

/*$#{INCLUDES}#$*/

class /*$#{NAME}#$*/ {
public:
    /*$#{NAME}#$*/();

    typedef bool (/*$#{NAME}#$*/::*Condition)();
    typedef double (/*$#{NAME}#$*/::*Weight)();
    typedef TTree* (/*$#{NAME}#$*/::*Open)();
    typedef void (/*$#{NAME}#$*/::*Close)();
    typedef void (/*$#{NAME}#$*/::*Style)(TAttLine*, TAttMarker*, TAttFill*);

    struct PlotContainer {
        TH1** hists;
        TString name;
        bool addOverflow;
        TString xtitle;
        TString ytitle;
        bool largelabels;
        int xdivisions;
        PlotContainer() :
            hists(nullptr), name(""), addOverflow(true), xtitle(""), ytitle(""),
            largelabels(false), xdivisions(0)
        {}
    };

    struct StreamContainer {
        Open open;
        Close close;
        Condition condition;
        Weight weight;
        bool forStack;
        Style style;
        TString title;
        StreamContainer() :
            open(nullptr), close(nullptr), condition(nullptr), weight(nullptr),
            forStack(false), style(nullptr), title("")
        {}
    };

    void run();

// protected:
    TTreeReader _reader;
    TLatex _text;
    PlotContainer* _plots;
    StreamContainer* _streams;
    int _n_plots, _n_streams;
    TString _luminosity;
    TFile* _file;
    TChain* _chain;

    void CloseFile() { _file->Close(); }
    void checkAndFill(int, double);

    /*$#{DEFINITIONS}#$*/

};

/*$#{NAME}#$*/::/*$#{NAME}#$*/() :
    _n_plots(/*$#{NPLOTS}#$*/),
    _n_streams(/*$#{NSTREAMS}#$*/),
    _luminosity(/*$#{LUMINOSITY}#$*/),
    _plots(new PlotContainer[/*$#{NPLOTS}#$*/]),
    _streams(new StreamContainer[/*$#{NSTREAMS}#$*/])
    /*$#{INITIALIZATIONS}#$*/
{
    gStyle->SetOptStat(0);
    _text.SetNDC();

    /*$#{CONSTRUCTIONS}#$*/
}

void /*$#{NAME}#$*/::checkAndFill(int nStream, double weight) {
    double selweight, catweight, evweight;

    /*$#{FILLCOMMANDS}#$*/
}

void /*$#{NAME}#$*/::run() {
    // Fill the histograms
    for(int nStream=0; nStream<_n_streams; nStream++) {
        StreamContainer* stream = _streams+nStream;
        TTree* tree = (this->*stream->open)();
        _reader.SetTree(tree);
        while(_reader.Next()) {
            if(!(this->*stream->condition)())
                continue;
            double weight = (this->*stream->weight)();
            checkAndFill(nStream, weight);
        }
        (this->*stream->close)();
    }

    // Set negative bins to zero
    for(int nPlot=0; nPlot<_n_plots; nPlot++)
        for(int nStream=0; nStream<_n_streams; nStream++) {
            int nBins = (_plots+nPlot)->hists[nStream]->GetNbinsX();
            for(int nBin=1; nBin<=nBins; nBin++)
                if((_plots+nPlot)->hists[nStream]->GetBinContent(nBin)<0.0)
                    (_plots+nPlot)->hists[nStream]->SetBinContent(nBin, 0.0);
        }

    // Create the legend
    std::vector<TLegendEntry*> legend_stacked;
    std::vector<TLegendEntry*> legend_unstacked;
    for(int nStream=0; nStream<_n_streams; nStream++) {
        StreamContainer* stream = _streams+nStream;
        if(stream->title.Length()>0) {
            TLegendEntry* entry = new TLegendEntry();
            entry->SetLabel(stream->title);
            entry->SetOption(stream->forStack ? "F" : "PLE");
            entry->SetTextSize(0.04);
            entry->SetTextFont(42);
            (this->*stream->style)(entry, entry, entry);
            if(stream->forStack)
                legend_stacked.push_back(entry);
            else
                legend_unstacked.push_back(entry);
        }
    }
    TLegend* legend = new TLegend(0.5, 0.7, 0.95, 0.935);
    for(std::vector<TLegendEntry*>::iterator entry=legend_unstacked.begin(); entry!=legend_unstacked.end(); ++entry)
        legend->GetListOfPrimitives()->Add(*entry);
    for(std::vector<TLegendEntry*>::reverse_iterator entry=legend_stacked.rbegin(); entry!=legend_stacked.rend(); ++entry)
        legend->GetListOfPrimitives()->Add(*entry);
    legend->SetNColumns(3);
    legend->SetBorderSize(0);
    while(legend->GetNRows()<5)
        legend->AddEntry((TObject*)0, "", "");

    // Create the plots
    for(int nPlot=0; nPlot<_n_plots; nPlot++) {
        PlotContainer* plot = _plots+nPlot;
        THStack* stack = new THStack(plot->name+"_stack", "");
        std::vector<int> unstacked;
        double maxi = -1.0e99;
        for(int nStream=0; nStream<_n_streams; nStream++) {
            StreamContainer* stream = _streams+nStream;
            TH1* hist = plot->hists[nStream];
            if(plot->addOverflow) {
                hist->SetBinContent(1, hist->GetBinContent(0)+hist->GetBinContent(1));
                hist->SetBinContent(0, 0);
                int lastBin = hist->GetNbinsX();
                hist->SetBinContent(lastBin, hist->GetBinContent(lastBin)+hist->GetBinContent(lastBin+1));
                hist->SetBinContent(lastBin+1, 0);
            }
            (this->*stream->style)(hist, hist, hist);
            if(stream->forStack) {
                stack->Add(hist);
            } else {
                double histmaxi = hist->GetBinContent(hist->GetMaximumBin())+hist->GetBinErrorUp(hist->GetMaximumBin());
                if(histmaxi>maxi)
                    maxi = histmaxi;
                unstacked.push_back(nStream);
            }
        }

        double stackmaxi = stack->GetMaximum();
        if(stackmaxi>maxi)
            maxi = stackmaxi;
        TH1* firstHist = plot->hists[unstacked.at(0)];
        firstHist->GetXaxis()->SetTitle(plot->xtitle);
        firstHist->GetXaxis()->SetTitleSize(0.05);
        firstHist->GetXaxis()->SetTitleOffset(1.2);
        firstHist->GetYaxis()->SetTitle(plot->ytitle);
        firstHist->GetYaxis()->SetTitleSize(0.05);
        firstHist->GetYaxis()->SetTitleOffset(1.35);
        firstHist->GetXaxis()->SetLabelSize(plot->largelabels ? 0.06 : 0.04);
        firstHist->GetXaxis()->SetLabelOffset(plot->largelabels ? 0.005 : 0.01);
        if(plot->xdivisions>0)
            firstHist->GetXaxis()->SetNdivisions(plot->xdivisions);
        firstHist->GetYaxis()->SetLabelSize(0.04);
        firstHist->GetYaxis()->SetLabelOffset(0.01);
        firstHist->GetYaxis()->SetRangeUser(0.0, 1.45*maxi);
        TCanvas* canv = new TCanvas(plot->name, "", 700, 600);
        canv->SetMargin(0.13, 0.03, 0.13, 0.05);
        firstHist->Draw("PE");
        stack->Draw("AHIST SAME");
        for(std::vector<int>::iterator index=unstacked.begin(); index!=unstacked.end(); ++index)
            plot->hists[*index]->Draw("APE SAME");
        firstHist->Draw("AXIS SAME");
        firstHist->Draw("AXIS Y+ SAME");
        legend->Draw();
        _text.SetTextFont(42);
        _text.SetTextSize(0.04);
        _text.SetTextAlign(31);
        _text.DrawLatex(0.97, 0.96, _luminosity);
        _text.SetTextAlign(11);
        _text.SetTextFont(52);
        _text.SetTextSize(0.04);
        _text.DrawLatex(0.18, 0.83, "Hamburg, 2018");
        _text.SetTextFont(62);
        _text.SetTextSize(0.05);
        _text.DrawLatex(0.18, 0.88, "PPT");
        canv->SaveAs("plots/"+plot->name+".pdf");
        canv->SaveAs("plots/"+plot->name+".C");
        canv->Close();
    }
}

void /*$#{NAME}#$*/_main() {
    /*$#{NAME}#$*/ manager;
    manager.run();
}
