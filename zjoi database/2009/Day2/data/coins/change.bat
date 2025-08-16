fpc change.pas
for /L %%x in (0,1,9) do (
change.exe <coins.out%%x >coins.tmp
del coins.out%%x
ren coins.tmp coins.out%%x
)
