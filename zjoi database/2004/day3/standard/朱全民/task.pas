Program task;

Const Inf='task.in';
      Ouf='task.out';
      Maxl=180;
      Mo=10;
Type Lnode              =Record
                           Len:Integer;
                           Lis:Array [1..Maxl] Of Integer;
                         End;
     Gnode              =^Pnode;
     Pnode              =Record
                           Num:Integer;
                           Next:Gnode;
                         End;
Var F                   :Array [0..100] Of Lnode;
    Ok                  :Array [0..100] Of Boolean;
    G                   :Array [0..100] Of Gnode;
    Ans,Nowl            :Lnode;
    N                   :Integer;
Procedure Add(X,Y       :Integer);
Var Tmp                 :Gnode;
Begin
  New(Tmp);
  Tmp^.Num:=Y;
  Tmp^.Next:=G[X];
  G[X]:=Tmp;
End;
Procedure Multi(X:Integer; Var A,B:Lnode);
Var U,V,W               :Integer;
Begin
{  Fillchar(B,Sizeof(B),0);}
  U:=0;
  V:=0;
  While (U<A.Len) Or (V<>0) Do Begin
    Inc(U);
    W:=A.Lis[U]*X+V;
    B.Lis[U]:=W Mod Mo;
    V:=W Div Mo;
  End;
  B.Len:=U;
  For U:=B.Len+1 To B.Len+6 Do B.Lis[U]:=0;
End;
Procedure Init;
Var P,Q                 :Integer;
Begin
  Assign(Input,Inf);
  Reset(Input);
  Readln(N);
  For P:=1 To N Do Begin
    G[P]:=Nil;
    While (Not Eoln(Input)) And (Not Eof(Input)) Do Begin
      Read(Q);
      Add(P,Q);
    End;
    Readln;
  End;
  Close(Input);
  Fillchar(F,Sizeof(F),0);
  F[0].Len:=1;
  F[0].Lis[1]:=1;
  For P:=1 To N Do
    Multi(P,F[P-1],F[P]);
  Ans:=F[N];
  Fillchar(Ok,Sizeof(Ok),True);
End;
Procedure Plus(Var A,B  :Lnode);
Var U,V,W               :Integer;
Begin
  U:=0;
  V:=0;
  While (U<A.Len) Or (V<>0) Do Begin
    Inc(U);
    W:=A.Lis[U]+B.Lis[U]+V;
    B.Lis[U]:=W Mod Mo;
    V:=W Div Mo;
  End;
  If U>B.Len Then B.Len:=U;
End;
Procedure Minus(Var A,B :Lnode);
Var U,V,W               :Integer;
Begin
  U:=0;
  V:=0;
  While (U<A.Len) Or (V<>0) Do Begin
    Inc(U);
    W:=B.Lis[U]-A.Lis[U]+V;
    If W<0 Then Begin
      W:=W+Mo;
      V:=-1;
    End Else V:=0;
    B.Lis[U]:=W;
  End;
  While (B.Len>0) And (B.Lis[B.Len]=0) Do Dec(B.Len);
End;
Procedure Search(Now,Step:Integer);
Var Tmp                 :Gnode;
    I                   :Integer;
Begin
  If Step>N Then Exit;
  I:=0;
  Tmp:=G[Step];
  While Tmp<>Nil Do Begin
    If Ok[Tmp^.Num] Then Begin
      Inc(I);
      Ok[Tmp^.Num]:=False;
      Search(Now-1,Step+1);
      Ok[Tmp^.Num]:=True;
    End;
    Tmp:=Tmp^.Next;
  End;
  Multi(I,F[Now-1],Nowl);
  If I<>0 Then
    If (N-Now+1) Mod 2=1 Then
      Minus(Nowl,Ans)
    Else
      Plus(Nowl,Ans);
  Search(Now,Step+1);
End;
Procedure Out;
Var P                   :Integer;
Begin
  Assign(Output,Ouf);
  Rewrite(Output);
  For P:=Ans.Len Downto 1 Do
    Write(Ans.Lis[P]);
  Writeln;
  Close(Output);
End;
Begin
  Init;
  Search(N,1);
  Out;
End.
