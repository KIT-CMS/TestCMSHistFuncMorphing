#!/usr/bin/env python
# -*- coding: utf-8 -*-

import ROOT
import glob

ROOT.gROOT.SetBatch()
ROOT.gStyle.SetOptStat(0)

c = ROOT.TCanvas("c","c",1000,500)
c.cd()

hists = {}
files = {}

#masses = [10,20,30,40,50,60,70,80,90,100,110,120,130,140,150]
masses = [5,7,10,12.5,13,15,20]
flist = ["output_testMorph/prefit_shapes_%s.root"%str(m) for m in masses]
for i,f in enumerate(flist):
    files[f] = ROOT.TFile.Open(f,"read")
    hists[f] = files[f].Get("test_morph_prefit/H")
    if i == 9:
        hists[f].SetLineColor(ROOT.kRed+3)
    else:
        hists[f].SetLineColor(i+1)
    if i == 0:
        #hists[f].GetCumulative().Draw("hist")
        hists[f].Draw("hist")
        print "Drawing",f
    else:
        #hists[f].GetCumulative().Draw("hist same")
        hists[f].Draw("hist same")
        print "Drawing",f
    
c.SaveAs("morphed_shapes.pdf")
    
