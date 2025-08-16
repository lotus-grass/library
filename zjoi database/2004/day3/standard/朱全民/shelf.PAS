Program ex;
Const Inf='shelf.in';
      Ouf='shelf.out';
      Maxn=1010;
Type Node               =Record
                           Key,Num:Integer;
                         End;
Var Ar                  :Array [0..Maxn] Of Node;
    Pos                 :Array [0..Maxn] Of Integer;
    Sum,Now             :Array [0..1] Of Integer;
    Ok                  :Array [0..Maxn] Of Boolean;
    N                   :Integer;
    Change              :Node;
    Ans                 :Integer;
Procedure Sort(L,R      :Integer);
Var I,J                 :Integer;
    X                   :Integer;
Begin
  I:=L;
  J:=R;
  X:=Ar[(L+R) Shr 1].Key;
  Repeat
    While Ar[I].Key<X Do Inc(I);
    While Ar[J].Key>X Do Dec(J);
    If I<=J Then Begin
      Change:=Ar[I];
      Ar[I]:=Ar[J];
      Ar[J]:=Change;
      Inc(I);
      Dec(J);
    End;
  Until J<I;
  If L<J Then Sort(L,J);
  If I<R Then Sort(I,R);
End;
Procedure Init;
Var P                   :Integer;
Begin
  Assign(Input,Inf);
  Reset(Input);
  Readln(N);
  For P:=1 To N Do Begin
    Read(Ar[P].Key);
    Ar[P].Num:=P;
  End;
  Close(Input);
  Sort(1,N);
End;
Procedure Main;
Var I,J                 :Integer;
Begin
  Fillchar(Pos,Sizeof(Pos),0);
  For I:=1 To N Do
    Pos[Ar[I].Num]:=I;
  Fillchar(Ok,Sizeof(Ok),True);
  Ans:=0;
  Sum[0]:=0;
  Sum[1]:=0;
  For I:=1 To N Do
    If Ok[I] And (I<>Pos[I]) Then Begin
      Now[0] := 0;
      Now[1] := 0;
      J:=I;
      Repeat
        Ok[J]:=False;
        Inc(Now[J Mod 2]);
        J:=Pos[J];
      Until J=I;
      If (Now[0]<>0) And (Now[1]<>0) Then
        Ans:=Ans+(Now[0]+Now[1]-1)
      Else Begin
        Inc(Sum[0],Now[0]);
        Inc(Sum[1],Now[1]);
      End;
    End;
  If Sum[0]+Sum[1]=0 Then Exit;
  If Sum[0]=0 Then Sum[0]:=1;
  If Sum[1]=0 Then Sum[1]:=1;
  Ans:=Ans+Sum[0]+Sum[1];
End;
Begin
  Init;
  Main;
  Assign(Output,Ouf);
  Rewrite(Output);
  Writeln(Ans);
  Close(Output);
End.