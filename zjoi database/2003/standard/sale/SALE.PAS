type
  Node = array [1..100, 1..100] of record
    A, B: Integer;
  end;
var
  m, n, i, j, k: Integer;
  A, B, T: LongInt;
  V: array [1..10] of LongInt;
  P: array [1..10] of ^Node;
procedure Solve(Depth, A, B: Integer);
var
  i, T1, T2, T3, T4, V1, V2: Integer;
begin
  if P[Depth]^[A, B].A >= 0 then Exit;
  if Depth = m then
  begin
    if (A >= V[Depth]) and (B >= V[Depth]) or (A < V[Depth]) and (B < V[Depth]) then
    begin
      P[Depth]^[A, B].A := 0;
      P[Depth]^[A, B].B := 0;
    end
    else if (A >= V[Depth]) and (B < V[Depth]) then
    begin
      if B < 10 then T := 10
      else T := B;
      P[Depth]^[A, B].A := V[Depth] - T;
      P[Depth]^[A, B].B := 0;
    end
    else if (A < V[Depth]) and (B >= V[Depth]) then
    begin
      T := A + 1;
      if T < 10 then T := 10;
      P[Depth]^[A, B].A := 0;
      P[Depth]^[A, B].B := V[Depth] - T;
    end;
  end
  else begin
    Solve(Depth + 1, A, B);
    V1 := P[Depth + 1]^[A, B].A;
    V2 := P[Depth + 1]^[A, B].B;
    if B >= 10 then
    begin
      Solve(Depth + 1, A, B - 10);
      T1 := P[Depth + 1]^[A, B - 10].A;
      T2 := P[Depth + 1]^[A, B - 10].B + V[Depth] - 10;
      if (T2 > V2) or (T2 = V2) and (T1 < V1) then
      begin
        V1 := T1;
        V2 := T2;
      end;
    end;
    for i := 10 to V[Depth] do
    begin
      if i > A then Break;
      Solve(Depth + 1, B, A - i);
      T1 := P[Depth + 1]^[B, A - i].B + V[Depth] - i;
      T2 := P[Depth + 1]^[B, A - i].A;
      if (B >= i + 1) and (i < V[Depth]) then
      begin
        Solve(Depth + 1, A, B - i - 1);
        T3 := P[Depth + 1]^[A, B - i - 1].A;
        T4 := P[Depth + 1]^[A, B - i - 1].B + V[Depth] - i - 1;
        if (T4 > T2) or (T4 = T2) and (T3 < T1) then
        begin
          T1 := T3;
          T2 := T4;
        end;
      end;
      if (T1 > V1) or (T1 = V1) and (T2 < V2) then
      begin
        V1 := T1;
        V2 := T2;
      end;
    end;
    P[Depth]^[A, B].A := V1;
    P[Depth]^[A, B].B := V2;
  end;
end;

begin
  Assign(Input, 'sale.in');
  Reset(Input);
  Assign(Output, 'sale.out');
  Rewrite(Output);
  for i := 1 to 10 do
    New(P[i]);
  Readln(n);
  for i := 1 to n do
  begin
    Readln(A, B);
    A := A div 10000;
    B := B div 10000;
    Readln(m);
    for j := 1 to m do
    begin
      Read(V[j]);
      V[j] := V[j] div 10000;
    end;
    k := 0;
    for j := 1 to m do
      if V[j] > 10 then
      begin
        Inc(k);
        V[k] := V[j];
      end;
    m := k;
    for j := 1 to m do
      FillChar(P[j]^, sizeof(Node), 255);
    if m = 0 then Writeln(0)
    else begin
      Solve(1, A, B);
      Writeln(LongInt(P[1]^[A, B].A) * 10000);
    end;
  end;
  Close(Input);
  Close(Output);
end.