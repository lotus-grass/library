Program bowl;

{$APPTYPE CONSOLE}

Const
  Inf='bowl.in';
  Ouf='bowl.out';
  MaxN=10;
  Zero=1e-8;

Var
  R1,R2,H,Now                   :Array[0..MaxN] Of Real;
  N                             :Longint;
  Ans                           :Real;

  Procedure Init;
  Var
    I                           :Longint;
  Begin
    Assign(Input,Inf);
    Assign(Output,ouf);
    Reset(Input);
    Readln(N);
    For I:=1 To N Do
      Readln(H[I],R1[I],R2[I]);
    Close(Input);
    Ans:=1e20;
  End;

  Procedure Work;
  Var
    A                           :Array[0..MaxN] Of Longint;
    B                           :Array[0..MaxN] Of Boolean;

    Procedure Search(K:Longint);
    Var
      I,J                       :Longint;
      Max                       :Real;

      Procedure Put(K:Longint);
      Var
        I                       :Longint;
        Max,S                   :Real;

        Function Calc(X,Y:Longint):Real;
        Var
          S,V,E                 :Real;
        Begin
          S:=Now[X];
          If R1[A[Y]]-Zero>R2[A[X]] Then Begin
            Calc:=Now[X]+H[A[X]];
            Exit;
          End;
          If R1[A[Y]]>R1[A[X]] Then Begin
            V:=(R2[A[X]]-R1[A[X]])/H[A[X]];
            E:=(R1[A[Y]]-R1[A[X]])/V;
            If Now[X]+E>S Then S:=Now[X]+E;
          End;
          If R2[A[Y]]>R2[A[X]] Then Begin
            V:=(R2[A[Y]]-R1[A[Y]])/H[A[Y]];
            E:=H[A[X]]-(R2[A[X]]-R1[A[Y]])/V;
            If Now[X]+E>S Then S:=Now[X]+E;
          End
          Else If R2[A[Y]]>R1[A[X]] Then Begin
            V:=(R2[A[X]]-R1[A[X]])/H[A[X]];
            E:=H[A[X]]-H[A[Y]]-(R2[A[X]]-R2[A[Y]])/V;
            If Now[X]+E>S Then S:=Now[X]+E;
          End;
          Calc:=S;
        End;

      Begin
        Max:=0;
        For I:=1 To K-1 Do Begin
          S:=Calc(I,K);
          If S>Max Then
            Max:=S;
        End;
        Now[K]:=Max;
      End;

    Begin
      If K>N Then Begin
        Max:=0;
        For J:=1 To N Do
          If Max<Now[J]+H[A[J]] Then Max:=Now[J]+H[A[J]];
        If Ans>Max Then
          Ans:=Max;
        Exit;
      End;
      If K<>1 Then
        If Now[K-1]+H[A[K-1]]>=Ans Then Exit;
      For I:=1 To N Do
        If B[I]=False Then Begin
          B[I]:=True;A[K]:=I;
          Put(K);
          Search(K+1);
          A[K]:=0;
          B[I]:=False;
        End;
    End;

  Begin
    Fillchar(A,Sizeof(A),0);
    Fillchar(B,Sizeof(B),False);
    Search(1);
    Rewrite(Output);
    Writeln(Round(Ans));
    Close(Output);
  End;

Begin
  Init;
  Work;
End.
