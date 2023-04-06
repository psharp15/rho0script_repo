#echo Are you running data or simulation?
#read DATATYPE
#if DATATYPE = 'data'
#then
#  root -b -q 'analysis_rho0data.C("flattree_F4_gd_pippimprotmn_wAcc.root","output_wAcc.root")'
#fii


#if DATATYPE = 'simulation'

  root -b -q 'analysis_rho0_2p.C("~/Research/analysis/fromifarm/simulation/flattree_gc12__protprot_AV18_inc_0bg.root","output_c12_protprot_AV18_inc_0bg.root")'

# root -b -q 'analysis_rho0_2p.C("~/Research/analysis/fromifarm/simulation/flattree_gc12__protprot_AV4_inc_0bg.root","output_c12_protprot_AV4_inc_0bg.root")'

# root -b -q 'analysis_rho0_2p.C("~/Research/analysis/fromifarm/simulation/flattree_gc12__protprot_N2LO_inc_0bg.root","output_c12_protprot_N2LO_inc_0bg.root")'
  
#root output_d_prot_AV18_inc_0bg.root

#fi

#./ hist2text/export_th1d


#open output_wAcc.pdf
