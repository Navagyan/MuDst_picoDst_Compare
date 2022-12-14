mu_tree=RawTree_MuDst.root
pico_tree=RawTree_picoDst.root

mu_ReadTree=MuDst_ReadTree.root
pico_ReadTree=picoDst_ReadTree.root

root4star -l -q -b "ReadTree_Data.C(\"$mu_tree\",\"$mu_ReadTree\")"
root4star -l -q -b "ReadTree_Data.C(\"$pico_tree\",\"$pico_ReadTree\")"

