const
  MaxN = 20;
type
  treetype = record
               lch,rch : integer;
             end;
var
  cost,value : array[1..MaxN,1..MaxN] of integer;
  name,fa    : array[1..MaxN] of string;
  L,d        : array[1..MaxN] of integer;
  tree       : array[0..MaxN] of treetype;
  f          : array[1..MaxN,0..MaxN*MaxN] of integer;
  n,i,j,p    : integer;

Procedure bfsbuildtree;
 var i,j,st,sf : integer;
     queue     : array[1..MaxN+1] of integer;
     str       : array[1..MaxN+1] of string;
  begin
    st := 1; sf := 1;
    str[1] := ''; queue[1] := 0;
    fillchar(tree,sizeof(tree),0);
    repeat
      for i := 1 to n do if fa[i] = str[st] then
        begin
          inc(sf);
          str[sf] := name[i]; queue[sf] := i;
          if tree[queue[st]].lch = 0 then
            tree[queue[st]].lch := i
          else
            begin
              j := tree[queue[st]].lch;
              while tree[j].rch <> 0 do j := tree[j].rch;
              tree[j].rch := i;
            end;
        end;
      inc(st);
    until st > sf;
  end;

Function max(a,b : integer) : integer;
  begin
    if a > b then max := a else max := b;
  end;

Function solve(nod,p : integer) : integer;
 var i,j,ans,sum,k,tmp : integer;
  begin
    if (nod = 0) then begin solve := 0; exit; end;
    if f[nod,p] <> -1 then begin solve := f[nod,p]; exit; end;
    tmp := p;
    ans := solve(tree[nod].rch,p);
    if d[nod] <> 0 then
      for k := 1 to p do
        ans := max(ans,solve(tree[nod].lch,k)+solve(tree[nod].rch,p-k));
    sum := 0;
    for i := d[nod]+1 to L[nod] do if p >= cost[nod,i] then
      begin
        p := p - cost[nod,i]; sum := sum + value[nod,i];
        for k := 0 to p do
          ans := max(ans,sum+solve(tree[nod].lch,k)+solve(tree[nod].rch,p-k));
      end else break;
    f[nod,tmp] := ans;
    solve := ans;
  end;

begin
  assign(input,'skill.in'); reset(input);
  assign(output,'skill.out'); rewrite(output);
  readln(n);
  for i := 1 to n do
    begin
      readln(name[i]);
      readln(fa[i]);
      readln(L[i]);
      for j := 1 to L[i] do read(cost[i,j]); readln;
      for j := 1 to L[i] do read(value[i,j]); readln;
    end;
  readln(p);
  for i := 1 to n do read(d[i]); readln;
  bfsbuildtree;
  fillchar(f,sizeof(f),255);
  writeln(solve(tree[0].lch,p));
  close(output); close(input);
end.
