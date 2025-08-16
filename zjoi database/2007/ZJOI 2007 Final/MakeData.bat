cd Data
cd chess
chess_gen
for /L %%1 in (0,1,9) do chess_std<chess.%%1.in>chess.%%1.out
echo Chess DONE ==================================
cd..
cd matrix
matrix_gen
for /L %%1 in (0,1,9) do matrix_std<matrix.%%1.in>matrix.%%1.out
echo Matrix DONE ==================================
cd..
cd synch
synch_gen
for /L %%1 in (0,1,9) do synch_std<synch.%%1.in>synch.%%1.out
echo Synch DONE ==================================
cd..
cd form
form_gen
for /L %%1 in (0,1,9) do form_std<form.%%1.in>form.%%1.out
echo Form DONE ==================================
cd..
cd..
cd..
@tree
@echo ALL DATA FOR ZJOI 2007 GENERATED , PRESS ANY KEY TO EXIT
@pause