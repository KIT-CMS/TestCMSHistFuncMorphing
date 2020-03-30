#include "CombineHarvester/CombinePdfs/interface/MorphFunctions.h"
#include "CombineHarvester/CombinePdfs/interface/CMSHistFuncFactory.h"
#include "CombineHarvester/CombineTools/interface/Algorithm.h"
#include "CombineHarvester/CombineTools/interface/AutoRebin.h"
#include "CombineHarvester/CombineTools/interface/BinByBin.h"
#include "CombineHarvester/CombineTools/interface/CardWriter.h"
#include "CombineHarvester/CombineTools/interface/CombineHarvester.h"
#include "CombineHarvester/CombineTools/interface/Observation.h"
#include "CombineHarvester/CombineTools/interface/Process.h"
#include "CombineHarvester/CombineTools/interface/Systematics.h"
#include "CombineHarvester/CombineTools/interface/Utilities.h"
#include "CombineHarvester/MSSMvsSMRun2Legacy/interface/HttSystematics_MSSMvsSMRun2.h"
#include "CombineHarvester/MSSMvsSMRun2Legacy/interface/BinomialBinByBin.h"
#include "RooRealVar.h"
#include "RooWorkspace.h"
#include "TF1.h"
#include "TH2.h"
#include "boost/algorithm/string/predicate.hpp"
#include "boost/algorithm/string/split.hpp"
#include "boost/lexical_cast.hpp"
#include "boost/program_options.hpp"
#include "boost/regex.hpp"
#include <cstdlib>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include <math.h>

using namespace std;
using boost::starts_with;
namespace po = boost::program_options;

int main(int argc, char **argv) {
  typedef vector<string> VString;
  typedef vector<pair<int, string>> Categories;
  using ch::syst::bin_id;
  using ch::JoinStr;

  // Define program options
  string output_folder = "output_testMorph";
  string base_path = string(getenv("CMSSW_BASE")) + "/src/CombineHarvester/MSSMvsSMRun2Legacy/shapes/";

  // Create combine harverster object
  ch::CombineHarvester cb;
  cb.SetFlag("workspaces-use-clone", true);
  Categories cats = {{1,"test"}};

  cb.AddObservations({""}, {""}, {""}, {""}, cats );
  cb.AddProcesses({""}, {""}, {""}, {""}, {"bg"}, cats, false);
  cb.AddProcesses({"5","20"}, {""}, {""}, {""}, {"H"}, cats, true);
  cb.cp().backgrounds().ExtractShapes((base_path+"test_morph.root").c_str(),"$BIN/$PROCESS","$BIN/$PROCESS");
  cb.cp().process({"H"}).ExtractShapes((base_path+"test_morph.root").c_str(),"$BIN/$PROCESS$MASS","$BIN/$PROCESS$MASS");

  // Setup morphed mssm signals for model-independent case
  RooWorkspace ws("htt", "htt");
  RooRealVar MH("MH", "MH", 10., 0., 25.);

  std::map<std::string, RooAbsReal *> mass_var = {
    {"H", &MH},
  };

  std::map<std::string, std::string> process_norm_map = {
    {"H", "norm"},
  };

  auto morphFactory = ch::CMSHistFuncFactory();
  morphFactory.SetHorizontalMorphingVariable(mass_var);
  morphFactory.Run(cb, ws, process_norm_map);

  cb.AddWorkspace(ws);
  cb.ExtractPdfs(cb, "htt", "$BIN_$PROCESS_morph");
  cb.ExtractData("htt", "$BIN_data_obs");
  ch::CardWriter writer(output_folder + "/test_morph.txt",
                        output_folder + "/morphed.root");
  writer.SetWildcardMasses({});
  writer.WriteCards("", cb);
}
