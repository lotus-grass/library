Program genbowl;

Const
  Ouf='bowl.in';
  N=9;
  Range=1000;

Var
  I,R1,R2                       :Longint;

Begin
  Randomize;
  Assign(Output,Ouf);
  Rewrite(Output);
  Writeln(N);
  For I:=1 To N Do Begin
    Repeat
      R1:=Random(Range)+1;
      R2:=Random(Range)+1;
    Until R1<R2;
    Writeln(Random(Range)+1,' ',R1,' ',R2);
  End;
  Close(Output);
End.
