# MuDst_picoDst_Compare
1.  Before you do anything make StRoot folder in working directory and get StSpinPool from $STAR/StRoot/StSpinPool for desired library
2.  Make IFF trees for the same file for picoDst and MuDsts running bash RawTree_pico_MuDst.sh
3.  Read the output IFF trees running ReadTree_pico_MuDst.sh
4.  Plot the comparision between picoDst and MuDst running root4star -l -q -b Data_Embed_Comp.C





===========================Thing to Notice in run17pp510MuDst_GP.C====================

In picoDst the nHitFits and nHitsFitPoss are defined from the global track, so to make same effect as in picoDst, in MuDst code we need to get the 
nHitsFit and nHitFitPoss from global track associated with the primary track

======================================================================================
