{$R-,S-,Q-,I-}
type
  Stype = array[1..50,1..50] of longint;
var
  E,A,B,II  : Stype;
  get     : array[0..12] of Stype;
  n,m,Nfish,t,start,finish
          : longint;
  fish    : array[1..20,1..4] of integer;
  d       : array[1..20] of integer;

Procedure getinfo;
 var i,j,k : longint;
  begin
    readln(n,m,start,finish,t);
    start := start+1; finish := finish+1;
    fillchar(E,sizeof(E),0);
    for i := 1 to m do
      begin
        readln(j,k);
        E[j+1,k+1] := 1;
        E[k+1,j+1] := 1;
      end;
    readln(Nfish);
    for i := 1 to Nfish do
      begin
        read(d[i]);
        for j := 1 to d[i] do read(fish[i,j]);
        for j := 1 to d[i] do inc(fish[i,j]);
        readln;
      end;
  end;

Function save(j,k : longint) : boolean;
 var i : longint;
  begin
    for i := 1 to Nfish do if fish[i,k mod d[i]+1]=j then exit(false);
    save := true;
  end;

Procedure prepare;
 var i,j,k,l : longint;
  begin
    fillchar(get,sizeof(get),0);
    for i := 1 to n do
      for j := 1 to n do if E[i,j]=1 then
        if save(j,1) then get[1,i,j] := 1;
    for k := 2 to 12 do
      for i := 1 to n do
        for j := 1 to n do if save(j,k) then
          for l := 1 to n do
            get[k,i,j] := (get[k,i,j]+get[k-1,i,l]*E[j,l]) mod 10000;
  end;

Procedure Multiply(A,B : Stype; Var C : Stype);
 var i,j,k : longint;
  begin
    fillchar(C,sizeof(C),0);
    for i := 1 to n do
      for j := 1 to n do
        for k := 1 to n do
          C[i,j] := (C[i,j] + (A[i,k]*B[k,j]) mod 10000) mod 10000;
  end;

Procedure bipate(Var A : Stype; k : longint);
 var B : Stype;
  begin
    if k = 0 then begin A := II; exit; end;
    B := A;
    bipate(A,k div 2);
    Multiply(A,A,A);
    if odd(k) then Multiply(B,A,A);
  end;

Procedure solve;
 var i : longint;
  begin
    fillchar(II,sizeof(II),0);
    for i := 1 to n do II[i,i] := 1;
    A := get[12];
    bipate(A,(t-1) div 12);
    t := t - (t-1) div 12 *12;
    Multiply(A,get[t],A);
    writeln(A[start,finish] mod 10000);
  end;

begin
  assign(input,'swamp.in'); reset(input);
  assign(output,'swamp.out'); rewrite(output);
  getinfo;
  prepare;
  solve;
  close(input); close(output);
end.
