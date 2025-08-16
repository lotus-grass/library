const maxn=30{00};
      big=10000000;
var min,w,now,s,t,m,i,j,k,n:longint;
    suit:array[1..maxn]of longint;
    f,c:array[1..maxn,1..maxn]of longint;
    e,h:array[1..maxn]of longint;
    tem:array[1..2]of longint;
    ok,change:boolean;
begin
  assign(input,'winner.in');
  assign(output,'winner.out');
  reset(input);
  rewrite(output);
  readln(n,m);
  for i:=1 to n do
    read(suit[i]);
  s:=n+1;
  t:=n+2;
  for i:=1 to n do c[s,i]:=1;
  now:=n+2;
  for i:=1 to m do
    begin
      read(tem[1],tem[2]);
      inc(now);
      if now>maxn then break;
      if suit[tem[1]]<>suit[tem[2]] then
        begin
          c[now,t]:=1;
          c[tem[1],now]:=0;
          c[tem[2],now]:=0;
        end else
        begin
          c[tem[1],now]:=1;
          c[tem[2],now]:=1;
        end;
    end;
  if now>maxn then writeln(n) else
    begin
      fillchar(h,sizeoF(h),0);
      fillchar(e,sizeof(e),0);
      h[s]:=n+1;
      for i:=1 to now do
        if c[s,i]>0 then
          begin
            inc(e[i],c[s,i]);
            f[s,i]:=c[s,i];
          end;
      change:=true;
      while change do
        begin
          change:=false;
          for i:=1 to now do
            if e[i]>0 then
              begin
                change:=true;
                min:=maxlongint;
                ok:=false;
                for j:=1 to now do
                  if h[i]=h[j]+1 then
                    begin
                      if c[i,j]-f[i,j]>0 then
                        begin
                          ok:=true;
                          if c[i,j]-f[i,j]>e[i] then w:=e[i] else w:=c[i,j]-f[i,j];
                          dec(e[i],w);
                          inc(e[j],w);
                          inc(f[i,j],w);
                          dec(f[j,i],w);
                        end;
                    end else
                  if min>h[j] then h[i]:=h[j];
                if not ok then h[i]:=min+1;
              end;
        end;
    end;
  writeln(e[t]);
  close(input);
  close(output);
end.