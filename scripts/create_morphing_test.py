import ROOT

f = ROOT.TFile.Open("test_morph.root","recreate")
f.cd()
f.mkdir("test")
f.cd("test")
data = ROOT.TH1D("data_obs","data_obs",25,0.0,25.0)
signatures = {
     5 : [4.0,0.0,0.0,0.0,1.0],
    20 : [4.0,0.0,0.0,0.0,1.0],
}
norms = {
     5 : 1.0,
    20 : 1.0,
}
sighists = {}
for p,m in zip(signatures,signatures):
    sighists[m] = data.Clone()
    sighists[m].SetName("H%s"%str(m))
    sighists[m].SetTitle("H%s"%str(m))
    bins = range(p-2,p+3)
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
