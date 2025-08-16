const maxn=500000;
type link=^node;
     node=record
       next:link;
       len,num:longint;
     end;
var n,root,i,j,k:longint;
    g:array[1..maxn]of link;
    t:array[1..3]of longint;
    leaf:array[1..maxn]of longint;
    cost,growson:array[1..maxn]of int64;
    tmp:link;
procedure dfs(now,father:longint);
var t1:link;
begin
  t1:=g[now];
  while t1<>nil do
    begin
      if t1^.num<>father then
        begin
          dfs(t1^.num,now);
          if growson[now]<growson[t1^.num]+t1^.len then
            growson[now]:=growson[t1^.num]+t1^.len;
          inc(cost[now],cost[t1^.num]);
          inc(leaf[now],leaf[t1^.num]);
        end;
      t1:=t1^.next;
    end;
  if leaf[now]=0 then
    begin
      leaf[now]:=1;
      exit;
    end;
  t1:=g[now];
  while t1<>nil do
    begin
      if t1^.num<>father then
        inc(cost[now],(growson[now]-growson[t1^.num]-int64(t1^.len))*int64(leaf[t1^.num]));
      t1:=t1^.next;
    end;
end;
begin
  assign(input,'synch.in');
  reset(input);
  assign(output,'synch.out');
  rewrite(output);
  readln(n);
  readln(root);
  fillchar(g,sizeof(g),0);
  for i:=1 to n-1 do
    begin
      readln(t[1],t[2],t[3]);
      new(tmp);
      tmp^.next:=g[t[1]];
      tmp^.len:=t[3];
      tmp^.num:=t[2];
      g[t[1]]:=tmp;
      new(tmp);
      tmp^.next:=g[t[2]];
      tmp^.len:=t[3];
      tmp^.num:=t[1];
      g[t[2]]:=tmp;
    end;
  fillchar(cost,sizeof(Cost),0);
  fillchar(growson,sizeof(growson),0);
  dfs(root,0);
  writeln(cost[root]);
  close(input);
  close(output);
end.