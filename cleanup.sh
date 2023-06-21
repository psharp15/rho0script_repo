#hadd -f ~/work/analysis/simulation/thrown/rho0_AV18_C12_thrown.root /volatile/halld/home/psharp/simulation/halld_sim_swif/AV18_C12/thrown/rho0*.root
#hadd -f ~/work/analysis/simulation/thrown/rho0_N2LO_C12_thrown.root /volatile/halld/home/psharp/simulation/halld_sim_swif/N2LO_C12/thrown/rho0*.root
#hadd -f ~/work/analysis/simulation/thrown/rho0_AV4_C12_thrown.root /volatile/halld/home/psharp/simulation/halld_sim_swif/AV4_C12/thrown/rho0*.root

~/work/analysis/hist2text/export_th1d p_AV18_C12_thrown.txt h_pmiss_p rho0_AV18_C12_thrown.root
~/work/analysis/hist2text/export_th1d p_N2LO_C12_thrown.txt h_pmiss_p rho0_N2LO_C12_thrown.root
~/work/analysis/hist2text/export_th1d p_AV4_C12_thrown.txt h_pmiss_p rho0_AV4_C12_thrown.root
~/work/analysis/hist2text/export_th1d pp_AV18_C12_thrown.txt h_pmiss_pp rho0_AV18_C12_thrown.root
~/work/analysis/hist2text/export_th1d pp_N2LO_C12_thrown.txt h_pmiss_pp rho0_N2LO_C12_thrown.root
~/work/analysis/hist2text/export_th1d pp_AV4_C12_thrown.txt h_pmiss_pp rho0_AV4_C12_thrown.root



