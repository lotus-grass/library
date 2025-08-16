{$A8,B-,C+,D+,E-,F-,G+,H+,I+,J-,K-,L+,M-,N+,O+,P+,Q-,R-,S-,T-,U-,V+,W-,X+,Y+,Z1}
{$MINSTACKSIZE $00004000}
{$MAXSTACKSIZE $20000000}

Program treep;

{$APPTYPE CONSOLE}

uses
  SysUtils;

Const Inf='tree.in';
      Ouf='tree.out';
      Maxn=100005;
      Maxrank=100000;
      Maxrankv=100000;
Type Gnode              =^Pnode;
     Pnode              =Record
                           Num:Integer;
                           Next:Gnode;
                         End;
     Fnode              =Array [0..Maxn] Of Integer;
     Trnode             =^Pnode2;
     Pnode2             =Record
                           Key:Integer;
                           Sum:Integer;
                           Rank:Integer;
                           Lc,Rc:Trnode;
                         End;
Var N,Len,Ranp,Pos      :Integer;
    Ar,Pa               :Fnode;
    G                   :Array [0..Maxn] Of Gnode;
    Ranar               :Array [0..Maxrank] Of Integer;
    List                :Array [0..Maxn] Of Integer;
    Fa,Fb,Fc,F          :Fnode;
    Niltree,Tree        :Trnode;

Procedure Add(X,Y       :Integer);
Var Tmp                 :Gnode;
Begin
  New(Tmp);
  Tmp^.Num:=Y;
  Tmp^.Next:=G[X];
  G[X]:=Tmp;
End;

Procedure Init;
Var P                   :Integer;
Begin
  Randomize;
  For P:=1 To Maxrank Do
    Ranar[P]:=Random(Maxrankv);
  Ranp:=0;
  New(Niltree);
  Niltree^.Sum:=0;
  Niltree^.Rank:=Maxrankv;
  Assign(Input,Inf);
  Reset(Input);
  Readln(N);
  Pa[1]:=0;
  For P:=2 To N Do Readln(Pa[P]);
  For P:=1 To N Do Readln(Ar[P]);
  Close(Input);
End;

Procedure Updata(Now    :Trnode);
Begin
  Now^.Sum:=Now^.Lc^.Sum+Now^.Rc^.Sum+1;
End;

Procedure TurnR(Fa,Son  :Trnode);
Var Tmp                 :Trnode;
Begin
  Tmp:=Son^.Lc;
  Son^.Lc:=Tmp^.Rc;
  Tmp^.Rc:=Son;
  Updata(Son);
  Updata(Tmp);
  If Fa=Niltree Then Tree:=Tmp Else
    If Fa^.Lc=Son Then
      Fa^.Lc:=Tmp
    Else
      Fa^.Rc:=Tmp;
End;

Procedure TurnL(Fa,Son  :Trnode);
Var Tmp                 :Trnode;
Begin
  Tmp:=Son^.Rc;
  Son^.Rc:=Tmp^.Lc;
  Tmp^.Lc:=Son;
  Updata(Son);
  Updata(Tmp);
  If Fa=Niltree Then Tree:=Tmp Else
    If Fa^.Lc=Son Then
      Fa^.Lc:=Tmp
    Else
      Fa^.Rc:=Tmp;
End;

Procedure Insert(Fa:Trnode; Var Son,Add:Trnode);
Begin
  If Son=Niltree Then Begin
    Son:=Add;
    Exit;
  End Else Begin
    Inc(Son^.Sum);
    If Add^.Key>Son^.Key Then Begin
      Insert(Son,Son^.Lc,Add);
      If Son^.Lc^.Rank<Son^.Rank Then TurnR(Fa,Son);
    End Else Begin
      Pos:=Pos+Son^.Lc^.Sum+1;
      Insert(Son,Son^.Rc,Add);
      If Son^.Rc^.Rank<Son^.Rank Then TurnL(Fa,Son);
    End;
  End;
End;

Procedure Addtr(Num       :Integer);
Var Tmp                 :Trnode;
Begin
  New(Tmp);
  Tmp^.Key:=Ar[Num];
  Tmp^.Sum:=1;
  If Ranp=Maxrank Then Ranp:=1 Else Inc(Ranp);
  Tmp^.Rank:=Ranar[Ranp];
  Tmp^.Lc:=Niltree;
  Tmp^.Rc:=Niltree;
  Pos:=0;
  Insert(Niltree,Tree,Tmp);
End;

Procedure Find(Now:Trnode; Var Fa,Son:Trnode);
Begin
  Fa:=Now;
  Son:=Now^.Rc;
  While Son^.Lc<>Niltree Do Begin
    Dec(Son^.Sum);
    Fa:=Son;
    Son:=Son^.Lc;
  End;
End;

Procedure Del(Fa,Son    :Trnode);
Var Ftmp,Tmp            :Trnode;
Begin
  If (Son^.Lc=Niltree) Or (Son^.Rc=Niltree) Then Begin
    If Son^.Rc=Niltree Then
      Tmp:=Son^.Lc
    Else
      Tmp:=Son^.Rc;
    If Fa=Niltree Then Tree:=Tmp Else
      If Fa^.Lc=Son Then
        Fa^.Lc:=Tmp
      Else
        Fa^.Rc:=Tmp;
    Dispose(Son);
  End Else Begin
    Find(Son,Ftmp,Tmp);
    If Ftmp^.Lc=Tmp Then
      Ftmp^.Lc:=Tmp^.Rc
    Else
      Ftmp^.Rc:=Tmp^.Rc;
    Son^.Key:=Tmp^.Key;
    Son^.Rank:=Tmp^.Rank;
    Dispose(Tmp);
    Repeat
      If (Son^.Lc=Niltree) And (Son^.Rc=Niltree) Then Break;
      If Son^.Lc^.Rank<=Son^.Rc^.Rank Then
        If Son^.Lc^.Rank<Son^.Rank Then Begin
          Tmp:=Fa;
          Fa:=Son^.Lc;
          TurnR(Tmp,Son);
        End Else Break
      Else
        If Son^.Rc^.Rank<son^.Rank Then Begin
          Tmp:=Fa;
          Fa:=Son^.Rc;
          TurnL(Tmp,Son);
        End Else Break;
    Until False;
  End;
End;

Procedure Deltr(Num     :Integer);
Var Pre,Now             :Trnode;
    U                   :Integer;
Begin
  U:=0;
  Pre:=Niltree;
  Now:=Tree;
  Repeat
    Dec(Now^.Sum);
    Inc(U,Now^.Lc^.Sum);
    If Num<=U Then Begin
      Pre:=Now;
      Now:=Now^.Lc;
      Dec(U,Now^.Sum);
    End Else Begin
      Inc(U);
      If U=Num Then Break;
      Pre:=Now;
      Now:=Now^.Rc;
    End;
  Until False;
  Del(Pre,Now);
End;

Procedure Search(U      :Integer);
Var Tmp                 :Gnode;
Begin
  Inc(Len);
  List[Len]:=U;
  Tmp:=G[U];
  While Tmp<>Nil Do Begin
    Search(Tmp^.Num);
    Tmp:=Tmp^.Next;
  End;
End;

Procedure Getf(Var Func :Fnode);
Var I                   :Integer;
Begin
  Len:=0;
  Search(1);
  Tree:=Niltree;
  For I:=1 To Len Do Begin
    Addtr(List[I]);
    Func[List[I]]:=Pos;
  End;
  For I:=Len Downto 1 Do Deltr(I);
End;

Procedure Work(Num      :Integer);
Var Tmp                 :Gnode;
    X                   :Integer;
Begin
  Addtr(Num);
  Fb[Num]:=Pos;
  X:=Pos;
  Tmp:=G[Num];
  While Tmp<>Nil Do Begin
    Work(Tmp^.Num);
    Tmp:=Tmp^.Next;
  End;
  Deltr(X+1);
End;

Procedure Sort(L,R      :Integer);
Var I,J                 :Integer;
    Key,Change          :Integer;
Begin
  I:=L;
  J:=R;
  Key:=Ar[List[(L+R) Shr 1]];
  Repeat
    While Ar[List[I]]>Key Do Inc(I);
    While Ar[List[J]]<Key Do Dec(J);
    If I<=J Then Begin
      Change:=List[I];
      List[I]:=List[J];
      List[J]:=Change;
      Inc(I);
      Dec(J);
    End;
  Until J<I;
  If L<J Then Sort(L,J);
  If I<R Then Sort(I,R);
End;

Procedure Main;
Var I                   :Integer;
Begin
  For I:=1 To N Do
    G[I]:=Nil;
  For I:=2 To N Do
    Add(Pa[I],I);
  Getf(Fa);
  For I:=1 To N Do
    Dispose(G[I]);
  For I:=1 To N Do
    G[I]:=Nil;
  For I:=N Downto 2 Do
    Add(Pa[I],I);
  Getf(Fc);
  Tree:=Niltree;
  Work(1);
  For I:=1 To N Do
    List[I]:=I;
  Sort(1,N);
  For I:=1 To N Do
    F[List[I]]:=I-1;
End;

Procedure Out;
Var P                   :Integer;
Begin
  Assign(Output,Ouf);
  Rewrite(Output);
  For P:=1 To N Do
    Writeln(F[P]-Fa[P]-Fc[P]+Fb[P],' ',Fa[P]+Fc[P]-Fb[P],' ',Fb[P]);
  Close(Output);
End;

Begin
  Init;
  Main;
  Out;
End.


