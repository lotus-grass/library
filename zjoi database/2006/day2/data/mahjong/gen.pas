program gen;


Var Cas:Integer;
    I,J:integer;
    A:Array [1..100] Of Integer;
    Time:Integer;
Begin
  Randomize;
  Cas:=90;
  Time:=2000;
  Assign(Output,'mahjong.in9');
  rewrite(Output);
  Writeln(cas);
  While Cas>0 Do Begin
    Dec(Cas);
    Fillchar(A,Sizeof(A),0);
    For I:=1 To Time Do
      If Random(2)=0 Then Begin
        Repeat
          J:=Random(100)+1;
          If A[J]<=97 Then Begin
            if (a[J]<97) and (random(3)=0) then A[J]:=A[J]+4 else a[j]:=a[j]+3;
            Break;
          End;
        Until False;
      End Else Begin
        Repeat
          J:=Random(98)+1;
          If (A[J]<100) And (A[J+1]<100) And (A[J+2]<100) Then Begin
            Inc(A[J]);
            Inc(A[J+1]);
            Inc(A[J+2]);
            Break;
          End;
        Until False;
      End;
    if random(2)=1 then begin
      Repeat
        J:=random(100)+1;
        If A[J]<=98 then begin
          a[J]:=A[J]+2;
          break;
        end;
      until false;
    end else begin
      for I:=1 to 100 do
        a[i]:=random(15);
    end;
    For I:=1 to 100 do write(A[I],' ');
    writeln;
  end;
  Close(Output);
End.
