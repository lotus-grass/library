const maxn=2010;
var rec,sq,aa,bb,x,y,m,n,i,j,k:longint;
    a:array[0..maxn,0..maxn]of boolean;
    last:array[0..1,0..maxn]of longint;
    pre,nex,r,l:array[0..maxn]of longint;
function min(a,b:longint):longint;
begin
  if a>b then exit(b) else exit(a);
end;
function max(a,b:longint):Longint;
begin
  if a>b then exit(a) else exit(b);
end;
begin
  assign(input,'chess.in');
  reset(input);
  assign(output,'chess.out');
  rewrite(output);
  readln(n,m);
  sq:=0;
  rec:=0;
  for i:=1 to n do
    for j:=1 to m do
      begin
        read(k);
        a[i,j]:=k=1;
      end;
  fillchar(last,sizeof(last),0);
  for i:=1 to m do last[1,i]:=1;
  x:=1;y:=0;
  for i:=2 to n do
    begin
      x:=(x+1) mod 2;
      y:=1-y;
      for j:=1 to m do
        if a[i-1,j] xor a[i,j] then
          last[x,j]:=last[y,j]+1 else last[x,j]:=1;
      a[i,0]:=a[i,1];
      for j:=1 to m do
        if a[i,j] xor a[i,j-1] then pre[j]:=pre[j-1] else pre[j]:=j;
      a[i,m+1]:=a[i,m];
      for j:=m downto 1 do
        if a[i,j] xor a[i,j+1] then nex[j]:=nex[j+1] else nex[j]:=j;
      last[x,0]:=0;
      for j:=1 to m do
        begin
          k:=j-1;
          while last[x,k]>=last[x,j] do k:=r[k];
          r[j]:=k;
        end;
      last[x,m+1]:=0;
      for j:=m downto 1 do
        begin
          k:=j+1;
          while last[x,k]>=last[x,j] do k:=l[k];
          l[j]:=k;
        end;
      for j:=1 to m do
        begin
          aa:=min(l[j]-1,nex[j])-max(pre[j],r[j]+1)+1;
          bb:=last[x,j];
          if sq<sqr(min(aa,bb)) then sq:=sqr(min(aa,bb));
          if rec<aa*bb then rec:=aa*bb;
        end;
    end;
  writeln(sq);
  writeln(rec);
  close(input);
  close(output);
end.
