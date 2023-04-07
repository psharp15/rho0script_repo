#echo Are you running data or simulation?
#read DATATYPE
#if DATATYPE = 'data'
#then
#  root -b -q 'analysis_rho0data.C("flattree_F4_gd_pippimprotmn_wAcc.root","output_wAcc.root")'
#fii


#if DATATYPE = 'simulation'

#  root -b -q 'analysis_rho0_1p.C("~/Research/analysis/fromifarm/simulation/flattree_gd__prot_AV18_inc_0bg.root","output_d2_prot_AV18_inc_0bg_new.root")'

#  root -b -q 'analysis_rho0_1p.C("~/Research/analysis/fromifarm/simulation/flattree_ghe__prot_AV18_inc_0bg.root","output_he4_prot_AV18_inc_0bg.root")'

 root -b -q 'analysis_rho0_1p.C("~/Research/analysis/fromifarm/simulation/flattree_gc12__prot_AV18_inc_0bg.root","output_c12_prot_AV18_inc_0bg_new.root")'
   
#   root -b -q 'analysis_rho0_1p.C("~/Research/analysis/fromifarm/simulation/flattree_gc12__prot_AV4_inc_0bg.root","output_c12_prot_AV4_inc_0bg.root")'

#  root -b -q 'analysis_rho0_1p.C("~/Research/analysis/fromifarm/simulation/flattree_gc12__prot_N2LO_inc_0bg.root","output_c12_prot_N2LO_inc_0bg.root")'
  
#root output_d_prot_AV18_inc_0bg.root

#fi

#./ hist2text/export_th1d


#open output_wAcc.pdf
