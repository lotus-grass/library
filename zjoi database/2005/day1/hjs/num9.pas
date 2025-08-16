{$R-,S-,Q-,I-}
const
  MaxN = 400000;
  finish = 12345678;
  prime = 578487;
var
  queue : array[1..2,1..MaxN] of longint;
  S,H   : array[1..2,0..prime] of longint;
  pre   : array[1..2,1..MaxN] of longint;
  st,sf : array[1..2] of longint;
  a     : array[1..9] of integer;
  ans   : array[1..2] of longint;
  i,j,k,start,step : longint;
  find  : boolean;

Function hash(k : longint) : longint;
  begin
    hash := k mod prime;
  end;

Function locate(typ,k : longint; Var sign : longint) : longint;
 var i,tmp : longint;
  begin
    tmp := hash(k);
    i := 0;
    while (S[typ,(tmp+i) mod prime]<>k)and(S[typ,(tmp+i) mod prime]<>-1) do inc(i);
    locate := (tmp+i) mod prime;
    sign := H[typ,(tmp+i) mod prime];
  end;

Function member(typ,k : longint) : longint;
 var tmp,i : longint;
  begin
    tmp := locate(typ,k,i);
    if S[typ,tmp] = -1 then member := -1 else member := i;
  end;

Procedure insert(typ,k,sign : longint);
 var tmp,i : longint;
  begin
    tmp := locate(typ,k,i);
    S[typ,tmp] := k;
    H[typ,tmp] := sign;
  end;

Procedure Change(sign,typ,habi : longint ; Var k : longint);
 var i,tmp : longint;
  begin
    for i := 9 downto 1 do
      begin
        a[i] := habi mod 10;
        habi := habi div 10;
      end;
    if sign = 1 then
      begin
        if typ = 1 then
          begin
            tmp := a[1]; a[1] := a[4]; a[4] := a[7]; a[7] := a[8]; a[8] := a[9];
            a[9] := a[6];a[6] := a[3]; a[3] := a[2]; a[2] := tmp;
          end
        else
          begin
            tmp := a[4]; a[4] := a[6]; a[6] := a[5]; a[5] := tmp;
          end;
      end
    else
      begin
        if typ = 1 then
          begin
            tmp := a[1]; a[1] := a[2]; a[2] := a[3]; a[3] := a[6]; a[6] := a[9];
            a[9] := a[8]; a[8] := a[7]; a[7] :=a[4]; a[4] := tmp;
          end
        else
          begin
            tmp := a[4]; a[4] := a[5]; a[5] := a[6]; a[6] := tmp;
          end;
      end;
    k := 0;
    for i := 1 to 9 do
      k := k*10 + a[i];
  end;

Procedure kuozhan(typ : integer);
 var i,j,k : longint;
  begin
    for i := st[typ] to sf[typ] do
      begin
        Change(typ,1,queue[typ,i],k);
        if member(typ,k) = -1 then
          begin
            inc(sf[typ]);
            queue[typ,sf[typ]] := k;
            insert(typ,k,sf[typ]); pre[typ,sf[typ]] := i;
            j := member(3-typ,k);
            if j<>-1 then begin find := true; ans[typ] := i; ans[3-typ] := j; exit; end;
          end;
        Change(typ,2,queue[typ,i],k);
        if member(typ,k) = -1 then
          begin
            inc(sf[typ]);
            queue[typ,sf[typ]] := k;
            insert(typ,k,sf[typ]); pre[typ,sf[typ]] := i;
            j := member(3-typ,k);
            if j<>-1 then begin find := true; ans[typ] := i; ans[3-typ] := j; exit; end;
          end;
      end;
  end;

Procedure solve;
 var i,j : longint;
  begin
    insert(1,queue[1,1],0);
    insert(2,queue[2,1],0);
    st[1] := 1; sf[1] := 1;
    st[2] := 1; sf[2] := 1;
    step := 0; find := false;
    repeat
      inc(step); j := sf[1];
      kuozhan(1); if find then break;
      st[1] := j + 1;
      inc(step); j := sf[2];
      kuozhan(2); if find then break;
      st[2] := j + 1;
    until (st[1]>sf[1])and(st[2]>sf[2]);
  end;

Procedure error;
  begin
    writeln('UNSOLVABLE');
    close(output); close(input);
    halt;
  end;

Procedure print1(k : longint);
 var i,j : longint;
  begin
    if k = 0 then exit;
    print1(pre[1,k]);
    for i := 9 downto 1 do
      begin
        a[i] := queue[1,k] mod 10;
        queue[1,k] := queue[1,k] div 10;
      end;
    for i := 1 to 3 do
      begin
        for j := 1 to 2 do write(a[(i-1)*3+j],' ');
        writeln(a[i*3]);
      end;
    writeln;
  end;

Procedure print2(k : longint);
 var i,j : longint;
  begin
    if k = 0 then exit;
    for i := 9 downto 1 do
      begin
        a[i] := queue[2,k] mod 10;
        queue[2,k] := queue[2,k] div 10;
      end;
    for i := 1 to 3 do
      begin
        for j := 1 to 2 do write(a[(i-1)*3+j],' ');
        writeln(a[i*3]);
      end;
    writeln;
    print2(pre[2,k]);
  end;

begin
  assign(input,'num9.in'); reset(input);
  assign(output,'num9.out'); rewrite(output);
  start := 0;
  for i := 1 to 3 do
    for j := 1 to 3 do
      begin
        read(k);
        start := start*10+k;
      end;
  queue[1,1] := start;
  queue[2,1] := finish;
  fillchar(S,sizeof(S),255);
  fillchar(pre,sizeof(pre),0);
  if start = finish then
    begin
      writeln(0);
      for i := 9 downto 1 do
        begin
          a[i] := start mod 10;
          start := start div 10;
        end;
      for i := 1 to 3 do
        begin
          for j := 1 to 2 do write(a[(i-1)*3+j],' ');
          writeln(a[i*3]);
        end;
      close(input); close(output);
      halt;
    end;
  solve;
  if find = false then error;
  writeln(step);
  print1(ans[1]);
  print2(ans[2]);
  if step = 1 then
    begin
      start := finish;
      for i := 9 downto 1 do
        begin
          a[i] := start mod 10;
          start := start div 10;
        end;
      for i := 1 to 3 do
        begin
          for j := 1 to 2 do write(a[(i-1)*3+j],' ');
          writeln(a[i*3]);
        end;
    end;
  close(input); close(output);
end.
