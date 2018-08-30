/*$#{BEGIN_REMOVENEGATIVE}#$*/
    for(int nBin=1; nBin<=hist->GetNbinsX(); nBin++)
        if(hist->GetBinContent(nBin)<0.0)
            hist->SetBinContent(nBin, 0.0);
/*$#{END_REMOVENEGATIVE}#$*/

/*$#{BEGIN_ADDOVERFLOW}#$*/
    hist->SetBinContent(1, hist->GetBinContent(0)+hist->GetBinContent(1));
    hist->SetBinContent(0, 0);
    int lastBin = hist->GetNbinsX();
    hist->SetBinContent(lastBin, hist->GetBinContent(lastBin)+hist->GetBinContent(lastBin+1));
    hist->SetBinContent(lastBin+1, 0);
/*$#{END_ADDOVERFLOW}#$*/

/*$#{BEGIN_SETSTYLE}#$*/
    hist->SetMarkerColor(style.markercolor);
    hist->SetMarkerStyle(style.markerstyle);
    hist->SetLineColor(style.linecolor);
    hist->SetLineStyle(style.linestyle);
    hist->SetFillColor(style.fillcolor);
    hist->SetFillStyle(style.fillstyle);
/*$#{END_SETSTYLE}#$*/
