#!/usr/bin/env python
# -*- coding: utf-8 -*-

import ROOT

f = ROOT.TFile.Open("test_morph.root","recreate")
f.cd()
f.mkdir("test")
f.cd("test")
data = ROOT.TH1D("data_obs","data_obs",25,0.0,25.0)
signatures = {
     5 : [0.0,0.0,4.0,8.0,4.0,0.0,0.0],
    20 : [1.0,2.0,3.0,4.0,3.0,2.0,1.0],
}
norms = {
     5 : 3.0,
    20 : 1.0,
}
sighists = {}
for m in signatures:
    sighists[m] = data.Clone()
    sighists[m].SetName("H%s"%str(m))
    sighists[m].SetTitle("H%s"%str(m))
    nsig = len(signatures[m])
    bins = range(m-nsig/2,m+nsig/2+1)
    for b,sig in zip(bins,signatures[m]):
        sighists[m].SetBinContent(b,sig)
    sighists[m].Scale(norms[m])
    sighists[m].Write()

for b in range(1,data.GetNbinsX()+1):
    data.SetBinContent(b,10)
data.Scale(1.0)
data.Write()
bg = data.Clone()
bg.SetName("bg")
bg.SetTitle("bg")
bg.Write()
f.Close()
