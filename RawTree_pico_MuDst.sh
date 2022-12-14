
mufile=/star/data110/GRID/mudst/pp500_production_2017_physics_P20ic.SL22b/st_physics_18149017_raw_2000027.MuDst.root
picofile=/star/data102/reco/pp500_production_2017/ReversedFullField/P20ic.SL22b/2017/149/18149017/st_physics_18149017_raw_2000027.picoDst.root

mu_tree=RawTree_MuDst.root
pico_tree=RawTree_picoDst.root

root4star -l -q -b "run17pp510MuDst_GP.C(\"$mufile\",\"$mu_tree\")"
root4star -l -q -b "run17pp510.C(\"$picofile\",\"$pico_tree\")"






