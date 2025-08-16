program mahjong;


Const Inf='Mahjong.in9';
      Ouf='Mahjong.ou9';
      Maxn=101;
Var Cas:Integer;
    F,G:Array [0..Maxn,0..Maxn,0..Maxn] Of Boolean;
    A:Array [-1..Maxn] Of Integer;
Procedure Init;
Var P:Integer;
Begin
  Fillchar(A,Sizeof(A),0);
  For P:=1 To 100 Do
    Read(A[P]);
  Readln;
End;
Procedure Main;
Var I,J,K:Integer;
Begin
  Fillchar(F,Sizeof(F),False);
  Fillchar(G,Sizeof(G),False);
  G[0,0,0]:=True;
  For I:=1 To 100 Do
    For J:=0 To A[I-1] Do
      For K:=0 To A[I] Do Begin
        If K>=2 Then
          F[I,J,K]:=F[I,J,K] Or G[I,J,K-2];
        If K>=3 Then
          F[I,J,K]:=F[I,J,K] Or F[I,J,K-3];
        If K>=4 Then
          F[I,J,K]:=F[I,J,K] Or F[I,J,K-4];
        If (A[I-2]>=K) And (J>=K) Then
          F[I,J,K]:=F[I,J,K] Or F[I-1,A[I-2]-K,J-K];
        If K>=3 Then
          G[I,J,K]:=G[I,J,K] Or G[I,J,K-3];
        If K>=4 Then
          G[I,J,K]:=G[I,J,K] Or G[I,J,K-4];
        If (A[I-2]>=K) And (J>=K) Then
          G[I,J,K]:=G[I,J,K] Or G[I-1,A[I-2]-K,J-K];
      End;
End;
Begin
  Assign(Output,Ouf);
  Rewrite(Output);
  Assign(Input,Inf);
  Reset(Input);
  Readln(Cas);
  While Cas>0 Do Begin
    Dec(Cas);
    Init;
    Main;
    If F[100,A[99],A[100]] Then Writeln('Yes') Else Writeln('No');
  End;
  Close(Input);
  Close(Output);
End.
