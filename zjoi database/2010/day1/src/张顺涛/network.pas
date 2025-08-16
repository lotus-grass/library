var
  i,k,m,n,num,tot,ans1,ans2:longint;
  tmp:array[0..5555]of record x,y,c,w:longint;end;
  e:array[0..55555]of record x,y,c,w,z,next:longint;end;
  d,f,first,next:array[0..1111]of longint;
  v:array[0..1111]of boolean;
  q:array[0..1111111]of longint;
function min(a,b:longint):longint;
  begin if a<b then exit(a);exit(b);end;
procedure addedge(x,y,c,w,z:longint);
  begin
    inc(tot);e[tot].x:=x;e[tot].y:=y;e[tot].c:=c;e[tot].w:=w;
    e[tot].z:=z+tot;e[tot].next:=first[x];first[x]:=tot;
  end;
function spfa:boolean;
  var s,t,num,x,y:longint;
  begin
    fillchar(v,sizeof(v),false);
    fillchar(d,sizeof(d),50);d[1]:=0;
    s:=1;t:=1;q[1]:=1;next[n]:=0;f[1]:=maxlongint;f[n]:=0;
    while s<=t do
      begin
        x:=q[s];v[x]:=false;num:=first[x];
        while num>0 do
          begin
            y:=e[num].y;
            if (e[num].c>0)and(d[y]>d[x]+e[num].w) then
              begin
                d[y]:=d[x]+e[num].w;
                f[y]:=min(f[x],e[num].c);
                next[y]:=num;
                if not v[y] then
                  begin v[y]:=true;inc(t);q[t]:=y;end;
              end;
            num:=e[num].next;
          end;
        inc(s);
      end;
    exit(f[n]>0);
  end;
begin
  assign(input,'network.in');
  assign(output,'network.out');
  reset(input);
  rewrite(output);
  readln(n,m,k);tot:=0;
  fillchar(first,sizeof(first),0);
  for i:=1 to m do with tmp[i] do
    begin
      readln(x,y,c,w);
      addedge(x,y,c,0,1);
      addedge(y,x,0,0,-1);
    end;
  ans1:=0;
  while spfa do
    begin
      ans1:=ans1+f[n];
      num:=next[n];
      while num>0 do
        begin
          e[num].c:=e[num].c-f[n];
          e[e[num].z].c:=e[e[num].z].c+f[n];
          num:=next[e[num].x];
        end;
    end;
  write(ans1,' ');tot:=0;
  fillchar(first,sizeof(first),0);
  fillchar(next,sizeof(next),0);
  for i:=1 to m do with tmp[i] do
    begin
      addedge(x,y,c,0,1);
      addedge(y,x,0,0,-1);
      addedge(x,y,k+ans1,w,1);
      addedge(y,x,0,-w,-1);
    end;
  inc(n);addedge(n-1,n,k+ans1,0,1);addedge(n,n-1,0,0,-1);
  ans2:=0;
  while spfa do
    begin
      ans2:=ans2+f[n]*d[n];
      num:=next[n];
      while num>0 do
        begin
          e[num].c:=e[num].c-f[n];
          e[e[num].z].c:=e[e[num].z].c+f[n];
          num:=next[e[num].x];
        end;
    end;
  writeln(ans2);
  close(input);
  close(output);
end.    
