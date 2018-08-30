//----------------------------------------------------------------------------//
// PoTATo's a Top Analysis Tool
// Project: common
// File:    PostProcessor.cpp
// Author:  Joscha Knolle
// Date:    2018-05-14
//----------------------------------------------------------------------------//

/*$#{BEGIN_INCLUDES}#$*/
#include <vector>

#include <TAttFill.h>
#include <TAttLine.h>
#include <TAttMarker.h>
#include <TCanvas.h>
#include <TH1.h>
#include <THStack.h>
#include <TLatex.h>
#include <TLegend.h>
#include <TLegendEntry.h>
#include <TObject.h>
#include <TStyle.h>
/*$#{END_INCLUDES}#$*/

/*$#{BEGIN_DEFINITIONS}#$*/
    enum Status { WorkInProgress, Preliminary, Final };
    Status _status;

    struct StyleContainer {
        short markercolor;
        short markerstyle;
        short linecolor;
        short linestyle;
        short fillcolor;
        short fillstyle;
        StyleContainer() :
            markercolor(0), markerstyle(0), linecolor(0), linestyle(0),
            fillcolor(0), fillstyle(0) {}
    };
    typedef TLegendEntry* (/*$#{NAME}#$*/::*LegendEntry)();
    StyleContainer* _stylecontainers;
    LegendEntry* _legendentries;
    bool* _forStack;

    typedef void (/*$#{NAME}#$*/::*Style)(TH1*, StyleContainer*);
    struct PlotContainer {
        TH1** hists;
        TString name;
        bool addOverflow;
        TString xtitle;
        TString ytitle;
        bool largelabels;
        int xdivisions;
        Style style;
        PlotContainer() :
            hists(nullptr), name(""), addOverflow(true), xtitle(""), ytitle(""),
            largelabels(false), xdivisions(0), style(nullptr) {}
        };
    int _n_plots;
    PlotContainer* _plots;

    TLatex _text;
    TString _luminosity;
/*$#{END_DEFINITIONS}#$*/

/*$#{BEGIN_INITIALIZATIONS}#$*/,
    _status(Status::/*$#{STATUS}#$*/),
    _stylecontainers(new StyleContainer[/*$#{NSTREAMS}#$*/]),
    _legendentries(new LegendEntry[/*$#{NSTREAMS}#$*/]),
    _forStack(new bool[/*$#{NSTREAMS}#$*/]),
    _n_plots(/*$#{NPLOTS}#$*/),
    _plots(new PlotContainer[/*$#{NPLOTS}#$*/]),
    _luminosity(/*$#{LUMINOSITY}#$*/)
/*$#{END_INITIALIZATIONS}#$*/

/*$#{BEGIN_CONSTRUCTIONS}#$*/
    gStyle->SetOptStat(0);
    _text.SetNDC();
/*$#{END_CONSTRUCTIONS}#$*/

/*$#{BEGIN_ACTION}#$*/
    double selweight, catweight, evweight;
/*$#{END_ACTION}#$*/

/*$#{BEGIN_OUTPUTS}#$*/
    // Create the legend
    std::vector<TLegendEntry*> legend_stacked;
    std::vector<TLegendEntry*> legend_unstacked;
    for(int nStream=0; nStream<_n_streams; nStream++) {
        StreamContainer* stream = _streams+nStream;
        if(stream->title.Length()>0) {
            TLegendEntry* entry = new TLegendEntry();
            entry->SetLabel(stream->title);
            entry->SetOption(_forStack[nStream] ? "F" : "PLE");
            entry->SetTextSize(0.04);
            entry->SetTextFont(42);
            entry->SetMarkerColor(_stylecontainers[nStream].markercolor);
            entry->SetMarkerStyle(_stylecontainers[nStream].markerstyle);
            entry->SetLineColor(_stylecontainers[nStream].linecolor);
            entry->SetLineStyle(_stylecontainers[nStream].linestyle);
            entry->SetFillColor(_stylecontainers[nStream].fillcolor);
            entry->SetFillStyle(_stylecontainers[nStream].fillstyle);
            if(_forStack[nStream])
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
        Style style = (_plots+nPlot)->style;
        THStack* stack = new THStack(plot->name+"_stack", "");
        std::vector<int> unstacked;
        double maxi = -1.0e99;
        for(int nStream=0; nStream<_n_streams; nStream++) {
            StreamContainer* stream = _streams+nStream;
            TH1* hist = plot->hists[nStream];
            if(style!=nullptr) (this->*style)(hist, _stylecontainers+nStream);
            if(_forStack[nStream]) {
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
        switch(_status) {
            case Status::Preliminary:
                _text.SetTextFont(52);
                _text.SetTextSize(0.04);
                _text.DrawLatex(0.18, 0.83, "Preliminary");
            case Status::Final:
                _text.SetTextFont(62);
                _text.SetTextSize(0.05);
                _text.DrawLatex(0.18, 0.88, "CMS");
                break;
            case Status::WorkInProgress:
                _text.SetTextFont(52);
                _text.SetTextSize(0.04);
                _text.DrawLatex(0.18, 0.88, "Work in Progress");
                break;
        }
        canv->SaveAs("plots/"+plot->name+".pdf");
        canv->SaveAs("plots/"+plot->name+".C");
        canv->Close();
    }
/*$#{END_OUTPUTS}#$*/
